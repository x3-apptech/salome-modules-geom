using namespace std;

#include "GEOM_Function.hxx"
#include "GEOM_Object.hxx"
#include "GEOM_Solver.hxx"

#include "utilities.h"

#include <TDF.hxx>
#include <TDF_Data.hxx>
#include <TDF_ChildIterator.hxx>
#include <TDF_Reference.hxx>
#include <TDataStd_Integer.hxx>
#include <TDataStd_IntegerArray.hxx>
#include <TDataStd_Real.hxx>
#include <TDataStd_RealArray.hxx>
#include <TDataStd_Comment.hxx>
#include <TDataStd_TreeNode.hxx>
#include <TDataStd_UAttribute.hxx>
#include <TDataStd_ChildNodeIterator.hxx>
#include <TDataStd_ExtStringArray.hxx>
#include <TDocStd_Owner.hxx>
#include <TDocStd_Document.hxx>
#include <TFunction_Function.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_Builder.hxx>

#include <TColStd_HArray1OfReal.hxx>
#include <TColStd_HArray1OfInteger.hxx>
#include <TColStd_HSequenceOfTransient.hxx>
#include <TCollection_AsciiString.hxx>
#include <TCollection_ExtendedString.hxx>

#include <Standard_ErrorHandler.hxx> // CAREFUL ! position of this file is critic : see Lucien PIGNOLONI / OCC

#define ARGUMENT_LABEL 1
#define RESULT_LABEL 2
#define DESCRIPTION_LABEL 3
#define ARGUMENTS _label.FindChild((ARGUMENT_LABEL))
#define ARGUMENT(thePosition) _label.FindChild((ARGUMENT_LABEL)).FindChild((thePosition))
#define SUB_ARGUMENT(thePos1, thePos2) _label.FindChild((ARGUMENT_LABEL)).FindChild((thePos1)).FindChild((thePos2))

//=======================================================================
//function : GetFunctionTreeID
//purpose  :
//=======================================================================
const Standard_GUID& GEOM_Function::GetFunctionTreeID()
{
  static Standard_GUID aFunctionTreeID("FF1BBB00-5D14-4df2-980B-3A668264EA16");
  return aFunctionTreeID;
}


//=======================================================================
//function : GetDependencyID
//purpose  :
//=======================================================================
const Standard_GUID& GEOM_Function::GetDependencyID()
{
  static Standard_GUID aDependencyID("E2620650-2354-41bd-8C2C-210CFCD00948");
  return aDependencyID;
}

//=============================================================================
/*!
 *  GetFunction:
 */
//=============================================================================
Handle(GEOM_Function) GEOM_Function::GetFunction(const TDF_Label& theEntry)
{
  if(!theEntry.IsAttribute(TFunction_Function::GetID())) return NULL;

  return new GEOM_Function(theEntry);
}

//=============================================================================
/*!
 *  Constructor:
 */
//=============================================================================
GEOM_Function::GEOM_Function(const TDF_Label& theEntry, const Standard_GUID& theGUID, int theType)
: _label(theEntry)
{
  TFunction_Function::Set(theEntry, theGUID);
  TDataStd_Integer::Set(theEntry, theType);

  //Add function to a function tree
  Handle(TDocStd_Document) aDoc = TDocStd_Owner::GetDocument(theEntry.Data());
  Handle(TDataStd_TreeNode) aRoot, aNode;
  if(!aDoc->Main().FindAttribute(GetFunctionTreeID(), aRoot))
    aRoot = TDataStd_TreeNode::Set(aDoc->Main(), GetFunctionTreeID());

  aNode = TDataStd_TreeNode::Set(theEntry, GetFunctionTreeID());
  aRoot->Append(aNode);
}

//=============================================================================
/*!
 *  GetOwner
 */
//=============================================================================
TDF_Label GEOM_Function::GetOwnerEntry()
{
  TDF_Label aFather = _label.Father();
  while(!aFather.IsRoot()) {
    if(aFather.IsAttribute(GEOM_Object::GetObjectID())) return aFather;
    aFather = aFather.Father();
  }

  return TDF_Label();
}

//=============================================================================
/*!
 *  GetType
 */
//=============================================================================
int GEOM_Function::GetType()
{
  _isDone = false;
  Handle(TDataStd_Integer) aType;
  if(!_label.FindAttribute(TDataStd_Integer::GetID(), aType)) return 0;
  _isDone = true;
  return aType->Get();
}

//=============================================================================
/*!
 *  GetValue
 */
//=============================================================================
TopoDS_Shape GEOM_Function::GetValue()
{
  _isDone = false;

  TopoDS_Shape aShape;
  TDF_Label aLabel = GetOwnerEntry();
  if(aLabel.IsRoot()) return aShape;
  Handle(GEOM_Object) anObject = GEOM_Object::GetObject(aLabel);
  if(anObject.IsNull()) return aShape;
  if(!anObject->IsMainShape()) {
    try {
      GEOM_Solver aSolver(GEOM_Engine::GetEngine());
      if (!aSolver.ComputeFunction(this)) {
	MESSAGE("GEOM_Object::GetValue Error : Can't build a sub shape");
	return aShape;
      }
    }
    catch (Standard_Failure) {
      Handle(Standard_Failure) aFail = Standard_Failure::Caught();
      MESSAGE("GEOM_Function::GetValue Error: " << aFail->GetMessageString());
      return aShape;
    }
  }

  TDF_Label aResultLabel = _label.FindChild(RESULT_LABEL);
  Handle(TNaming_NamedShape) aNS;
  if(!aResultLabel.FindAttribute(TNaming_NamedShape::GetID(), aNS)) return aShape;

  aShape = aNS->Get();

  _isDone = true;
  return aShape;
}

//=============================================================================
/*!
 *  GetValue
 */
//=============================================================================
void GEOM_Function::SetValue(TopoDS_Shape& theShape)
{
  _isDone = false;
  TDF_Label aResultLabel = _label.FindChild(RESULT_LABEL);
  TNaming_Builder aBuilder(aResultLabel);

  aBuilder.Generated(theShape);

  _isDone = true;
}

//=============================================================================
/*!
 *  GetDriverGUID
 */
//=============================================================================
Standard_GUID GEOM_Function::GetDriverGUID()
{
  Handle(TFunction_Function) aFunction;
  if(!_label.FindAttribute(TFunction_Function::GetID(), aFunction)) {
    return TDF::LowestID();
  }

  return aFunction->GetDriverGUID();
}

//=============================================================================
/*!
 *  GetDescription
 */
//=============================================================================
TCollection_AsciiString GEOM_Function::GetDescription()
{
  Handle(TDataStd_Comment) aComment;
  TDF_Label aChild = _label.FindChild(DESCRIPTION_LABEL);
  if(!aChild.FindAttribute(TDataStd_Comment::GetID(), aComment)) return TCollection_AsciiString();
  TCollection_AsciiString aDescr(aComment->Get());
  return aDescr;
}

//=============================================================================
/*!
 *  SetDescription
 */
//=============================================================================
void GEOM_Function::SetDescription(TCollection_AsciiString& theDescription)
{
  TDF_Label aChild = _label.FindChild(DESCRIPTION_LABEL);
  Handle(TDataStd_Comment) aComment = TDataStd_Comment::Set(aChild, TCollection_ExtendedString(theDescription));
}

//=============================================================================
/*!
 *  SetReal
 */
//=============================================================================
void GEOM_Function::SetReal(int thePosition, double theValue)
{
  _isDone = false;
  if(thePosition <= 0) return;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  TDataStd_Real::Set(anArgLabel, theValue);
  _isDone = true;
}

//=============================================================================
/*!
 *  SetRealArray
 */
//=============================================================================
void GEOM_Function::SetRealArray (int thePosition,
                                  const Handle(TColStd_HArray1OfReal)& theArray)
{
  _isDone = false;
  if(thePosition <= 0) return;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  Handle(TDataStd_RealArray) anAttr =
    TDataStd_RealArray::Set(anArgLabel, theArray->Lower(), theArray->Upper());
  anAttr->ChangeArray(theArray);
  _isDone = true;
}

//=============================================================================
/*!
 *  GetReal
 */
//=============================================================================
double GEOM_Function::GetReal(int thePosition)
{
  _isDone = false;
  if(thePosition <= 0) return 0.0;
  Handle(TDataStd_Real) aReal;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  if(!anArgLabel.FindAttribute(TDataStd_Real::GetID(), aReal)) return 0.0;

  _isDone = true;
  return aReal->Get();
}

//=============================================================================
/*!
 *  GetRealArray
 */
//=============================================================================
Handle(TColStd_HArray1OfReal) GEOM_Function::GetRealArray(int thePosition)
{
  _isDone = false;
  if(thePosition <= 0) return NULL;
  Handle(TDataStd_RealArray) aRealArray;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  if(!anArgLabel.FindAttribute(TDataStd_RealArray::GetID(), aRealArray)) return NULL;

  _isDone = true;
  return aRealArray->Array();
}

//=============================================================================
/*!
 *  SetInteger
 */
//=============================================================================
void GEOM_Function::SetInteger(int thePosition, int theValue)
{
  _isDone = false;
  if(thePosition <= 0) return;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  TDataStd_Integer::Set(anArgLabel, theValue);
  _isDone = true;
}

//=============================================================================
/*!
 *  SetIntegerArray
 */
//=============================================================================
void GEOM_Function::SetIntegerArray (int thePosition,
                                     const Handle(TColStd_HArray1OfInteger)& theArray)
{
  _isDone = false;
  if(thePosition <= 0) return;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  Handle(TDataStd_IntegerArray) anAttr =
    TDataStd_IntegerArray::Set(anArgLabel, theArray->Lower(), theArray->Upper());
  anAttr->ChangeArray(theArray);
  _isDone = true;
}

//=============================================================================
/*!
 *  GetInteger
 */
//=============================================================================
int GEOM_Function::GetInteger(int thePosition)
{
  _isDone = false;
  if(thePosition <= 0) return 0;
  Handle(TDataStd_Integer) anInteger;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  if(!anArgLabel.FindAttribute(TDataStd_Integer::GetID(), anInteger)) return 0;

  _isDone = true;
  return anInteger->Get();
}

//=============================================================================
/*!
 *  GetIntegerArray
 */
//=============================================================================
Handle(TColStd_HArray1OfInteger) GEOM_Function::GetIntegerArray(int thePosition)
{
  _isDone = false;
  if(thePosition <= 0) return 0;
  Handle(TDataStd_IntegerArray) anIntegerArray;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  if(!anArgLabel.FindAttribute(TDataStd_IntegerArray::GetID(), anIntegerArray)) return 0;

  _isDone = true;
  return anIntegerArray->Array();
}

//=============================================================================
/*!
 *  SetString
 */
//=============================================================================
void GEOM_Function::SetString(int thePosition, const TCollection_AsciiString& theValue)
{
  _isDone = false;
  if(thePosition <= 0) return;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  TDataStd_Comment::Set(anArgLabel, theValue);
  _isDone = true;
}

//=============================================================================
/*!
 *  GetString
 */
//=============================================================================
TCollection_AsciiString GEOM_Function::GetString(int thePosition)
{
  _isDone = false;
  TCollection_AsciiString aRes;
  if(thePosition <= 0) return aRes;
  Handle(TDataStd_Comment) aString;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  if(!anArgLabel.FindAttribute(TDataStd_Comment::GetID(), aString)) return aRes;

  _isDone = true;
  aRes = TCollection_AsciiString(aString->Get());
  return aRes;
}

//=============================================================================
/*!
 *  SetReference
 */
//=============================================================================
void GEOM_Function::SetReference(int thePosition, Handle(GEOM_Function) theReference)
{
  _isDone = false;
  if(thePosition <= 0) return;
  if(theReference.IsNull()) return;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  TDF_Reference::Set(anArgLabel, theReference->GetEntry());
  TDataStd_UAttribute::Set(anArgLabel, GetDependencyID());
  _isDone = true;
  return;
}

//=============================================================================
/*!
 *  GetReference
 */
//=============================================================================
Handle(GEOM_Function) GEOM_Function::GetReference(int thePosition)
{
  _isDone = false;
  if(thePosition <= 0) return NULL;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  Handle(TDF_Reference) aRef;
  if(!anArgLabel.FindAttribute(TDF_Reference::GetID(), aRef)) return NULL;

  _isDone = true;
  return GetFunction(aRef->Get());
}


//=============================================================================
/*!
 *  SetStringArray
 */
//=============================================================================
void GEOM_Function::SetStringArray(int thePosition, const Handle(TColStd_HArray1OfExtendedString)& theArray)
{
  _isDone = false;
  if(thePosition <= 0 || theArray.IsNull()) return;
  TDF_Label anArgLabel = ARGUMENT(thePosition);

  Handle(TDataStd_ExtStringArray) anArray = new TDataStd_ExtStringArray;
  anArray->ChangeArray(theArray);
  anArgLabel.AddAttribute(anArray);

  _isDone = true;
}


//=============================================================================
/*!
 *  GetStringArray
 */
//=============================================================================
Handle(TColStd_HArray1OfExtendedString) GEOM_Function::GetStringArray(int thePosition)
{
  _isDone = false;
  if(thePosition <= 0) return NULL;
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  Handle(TDataStd_ExtStringArray) anArray;
  if(!anArgLabel.FindAttribute(TDataStd_ExtStringArray::GetID(), anArray)) return NULL;

  _isDone = true;
  return anArray->Array();
}

//=======================================================================
//function : GetReferencesTreeID
//purpose  :
//=======================================================================
const Standard_GUID& GEOM_Function::GetReferencesTreeID()
{
  static Standard_GUID aReferencesTreeID("FF1BBB10-5D14-4df2-980B-3A668264EA16");
  return aReferencesTreeID;
}

//=============================================================================
/*!
 *  SetReferenceList
 */
//=============================================================================
void GEOM_Function::SetReferenceList (int thePosition,
                                      const Handle(TColStd_HSequenceOfTransient)& theRefList)
{
  _isDone = false;
  if(thePosition <= 0) return;

  // parent label for the list of references
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  anArgLabel.ForgetAllAttributes();

  // set TreeNode on the parent label
  Handle(TDataStd_TreeNode) aRoot, aNode;
  aRoot = TDataStd_TreeNode::Set(anArgLabel, GetReferencesTreeID());

  // store references on sub-labels of the parent label
  Handle(GEOM_Function) aFunc;
  Standard_Integer ind, len = theRefList->Length();
  for (ind = 1; ind <= len; ind++) {
    aFunc = Handle(GEOM_Function)::DownCast(theRefList->Value(ind));
    if (aFunc.IsNull()) continue;
    TDF_Label anArgLabel_i = SUB_ARGUMENT(thePosition, ind);
    TDF_Reference::Set(anArgLabel_i, aFunc->GetEntry());
    TDataStd_UAttribute::Set(anArgLabel_i, GetDependencyID());

    // set TreeNode on the child label
    aNode = TDataStd_TreeNode::Set(anArgLabel_i, GetReferencesTreeID());
    aRoot->Append(aNode);
  }

  _isDone = true;
  return;
}

//=============================================================================
/*!
 *  GetReferenceList
 */
//=============================================================================
Handle(TColStd_HSequenceOfTransient) GEOM_Function::GetReferenceList(int thePosition)
{
  Handle(TColStd_HSequenceOfTransient) aResult = new TColStd_HSequenceOfTransient;
  _isDone = false;
  if(thePosition <= 0) return aResult;

  // parent label for the list of references
  TDF_Label anArgLabel = ARGUMENT(thePosition);
  Handle(TDF_Reference) aRef;

  // get TreeNode on the parent label
  Handle(TDataStd_TreeNode) aRoot, aNode;
  if(!anArgLabel.FindAttribute(GetReferencesTreeID(), aRoot))
    return aResult;

  // get references, stored on sub-labels of the parent label
  TDF_Label aLabel_i;
  TDataStd_ChildNodeIterator anIter (aRoot);
  for (; anIter.More(); anIter.Next()) {
    aNode = anIter.Value();
    aLabel_i = aNode->Label();
    if (!aLabel_i.FindAttribute(TDF_Reference::GetID(), aRef)) continue;
    Handle(GEOM_Function) aFunc_i = GetFunction(aRef->Get());
    if (aFunc_i.IsNull()) continue;
    aResult->Append(aFunc_i);
  }

  _isDone = true;
  return aResult;
}

//=============================================================================
/*!
 *  SetShape
 */
//=============================================================================
void GEOM_Function::SetShape(int thePosition, const TopoDS_Shape& theShape)
{
  _isDone = false;
  if(thePosition <= 0 || theShape.IsNull()) return;

  TDF_Label anArgLabel = ARGUMENT(thePosition);
  TNaming_Builder aBuilder(anArgLabel);
  aBuilder.Generated(theShape);

  _isDone = true;
  return;
}

//=============================================================================
/*!
 *  GetShape
 */
//=============================================================================
TopoDS_Shape GEOM_Function::GetShape(int thePosition)
{
  _isDone = false;
  TopoDS_Shape aShape;
  if(thePosition <= 0) return aShape;

  TDF_Label anArgLabel = ARGUMENT(thePosition);
  Handle(TNaming_NamedShape) aNS;
  if(!anArgLabel.FindAttribute(TNaming_NamedShape::GetID(), aNS)) return aShape;

  aShape = aNS->Get();
  _isDone = true;
  return aShape;
}


//=============================================================================
/*!
 *  GetDependency
 */
//=============================================================================
void GEOM_Function::GetDependency(TDF_LabelSequence& theSeq)
{
  TDF_ChildIterator anIterator(ARGUMENTS, Standard_True);
  for(; anIterator.More(); anIterator.Next()) {
    if(anIterator.Value().IsAttribute(GetDependencyID())) theSeq.Append(anIterator.Value());
  }
}

//=======================================================================
//function :  GEOM_Function_Type_
//purpose  :
//=======================================================================
Standard_EXPORT Handle_Standard_Type& GEOM_Function_Type_()
{

  static Handle_Standard_Type aType1 = STANDARD_TYPE(MMgt_TShared);
  if ( aType1.IsNull()) aType1 = STANDARD_TYPE(MMgt_TShared);
  static Handle_Standard_Type aType2 = STANDARD_TYPE(Standard_Transient);
  if ( aType2.IsNull()) aType2 = STANDARD_TYPE(Standard_Transient);


  static Handle_Standard_Transient _Ancestors[]= {aType1,aType2,NULL};
  static Handle_Standard_Type _aType = new Standard_Type("GEOM_Function",
			                                 sizeof(GEOM_Function),
			                                 1,
			                                 (Standard_Address)_Ancestors,
			                                 (Standard_Address)NULL);

  return _aType;
}

//=======================================================================
//function : DownCast
//purpose  :
//=======================================================================

const Handle(GEOM_Function) Handle(GEOM_Function)::DownCast(const Handle(Standard_Transient)& AnObject)
{
  Handle(GEOM_Function) _anOtherObject;

  if (!AnObject.IsNull()) {
     if (AnObject->IsKind(STANDARD_TYPE(GEOM_Function))) {
       _anOtherObject = Handle(GEOM_Function)((Handle(GEOM_Function)&)AnObject);
     }
  }

  return _anOtherObject ;
}