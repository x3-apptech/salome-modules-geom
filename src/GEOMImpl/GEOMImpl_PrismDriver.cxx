
using namespace std;
#include "GEOMImpl_PrismDriver.hxx"
#include "GEOMImpl_IPrism.hxx"
#include "GEOMImpl_Types.hxx"
#include "GEOM_Function.hxx"

#include <BRepPrimAPI_MakePrism.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopAbs.hxx>
#include <TopExp.hxx>

#include <Precision.hxx>
#include <gp_Pnt.hxx>
#include <Standard_ConstructionError.hxx>

//=======================================================================
//function : GetID
//purpose  :
//======================================================================= 
const Standard_GUID& GEOMImpl_PrismDriver::GetID()
{
  static Standard_GUID aPrismDriver("FF1BBB17-5D14-4df2-980B-3A668264EA16");
  return aPrismDriver; 
}


//=======================================================================
//function : GEOMImpl_PrismDriver
//purpose  : 
//=======================================================================
GEOMImpl_PrismDriver::GEOMImpl_PrismDriver() 
{
}

//=======================================================================
//function : Execute
//purpose  :
//======================================================================= 
Standard_Integer GEOMImpl_PrismDriver::Execute(TFunction_Logbook& log) const
{
  if (Label().IsNull()) return 0;    
  Handle(GEOM_Function) aFunction = GEOM_Function::GetFunction(Label());

  GEOMImpl_IPrism aCI (aFunction);
  Standard_Integer aType = aFunction->GetType();

  TopoDS_Shape aShape;

  if (aType == PRISM_BASE_VEC_H) {
    Handle(GEOM_Function) aRefBase = aCI.GetBase();
    Handle(GEOM_Function) aRefVector = aCI.GetVector();
    TopoDS_Shape aShapeBase = aRefBase->GetValue();
    TopoDS_Shape aShapeVec = aRefVector->GetValue();
    if (aShapeVec.ShapeType() == TopAbs_EDGE) {
      TopoDS_Edge anE = TopoDS::Edge(aShapeVec);
      TopoDS_Vertex V1, V2;
      TopExp::Vertices(anE, V1, V2, Standard_True);
      if (!V1.IsNull() && !V2.IsNull()) {
        gp_Vec aV (BRep_Tool::Pnt(V1), BRep_Tool::Pnt(V2));
        if (Abs(aCI.GetH()) < Precision::Confusion()) {
          Standard_ConstructionError::Raise("Absolute value of prism height is too small");
        }
        if (aV.Magnitude() > Precision::Confusion()) {
          aV.Normalize();
          aShape = BRepPrimAPI_MakePrism(aShapeBase, aV * aCI.GetH(), Standard_False).Shape();
        }
      }
    }
  } else if (aType == PRISM_BASE_TWO_PNT) {
    Handle(GEOM_Function) aRefBase = aCI.GetBase();
    Handle(GEOM_Function) aRefPnt1 = aCI.GetFirstPoint();
    Handle(GEOM_Function) aRefPnt2 = aCI.GetLastPoint();
    TopoDS_Shape aShapeBase = aRefBase->GetValue();
    TopoDS_Shape aShapePnt1 = aRefPnt1->GetValue();
    TopoDS_Shape aShapePnt2 = aRefPnt2->GetValue();
    if (aShapePnt1.ShapeType() == TopAbs_VERTEX &&
        aShapePnt2.ShapeType() == TopAbs_VERTEX) {
      TopoDS_Vertex V1 = TopoDS::Vertex(aShapePnt1);
      TopoDS_Vertex V2 = TopoDS::Vertex(aShapePnt2);
      if (!V1.IsNull() && !V2.IsNull()) {
        gp_Vec aV (BRep_Tool::Pnt(V1), BRep_Tool::Pnt(V2));
        if (aV.Magnitude() > gp::Resolution()) {
          aShape = BRepPrimAPI_MakePrism(aShapeBase, aV, Standard_False).Shape();
        }
      }
    }
  } else {
  }

  if (aShape.IsNull()) return 0;

  aFunction->SetValue(aShape);

  log.SetTouched(Label()); 

  return 1;    
}


//=======================================================================
//function :  GEOMImpl_PrismDriver_Type_
//purpose  :
//======================================================================= 
Standard_EXPORT Handle_Standard_Type& GEOMImpl_PrismDriver_Type_()
{

  static Handle_Standard_Type aType1 = STANDARD_TYPE(TFunction_Driver);
  if ( aType1.IsNull()) aType1 = STANDARD_TYPE(TFunction_Driver);
  static Handle_Standard_Type aType2 = STANDARD_TYPE(MMgt_TShared);
  if ( aType2.IsNull()) aType2 = STANDARD_TYPE(MMgt_TShared); 
  static Handle_Standard_Type aType3 = STANDARD_TYPE(Standard_Transient);
  if ( aType3.IsNull()) aType3 = STANDARD_TYPE(Standard_Transient);
 

  static Handle_Standard_Transient _Ancestors[]= {aType1,aType2,aType3,NULL};
  static Handle_Standard_Type _aType = new Standard_Type("GEOMImpl_PrismDriver",
			                                 sizeof(GEOMImpl_PrismDriver),
			                                 1,
			                                 (Standard_Address)_Ancestors,
			                                 (Standard_Address)NULL);

  return _aType;
}

//=======================================================================
//function : DownCast
//purpose  :
//======================================================================= 
const Handle(GEOMImpl_PrismDriver) Handle(GEOMImpl_PrismDriver)::DownCast(const Handle(Standard_Transient)& AnObject)
{
  Handle(GEOMImpl_PrismDriver) _anOtherObject;

  if (!AnObject.IsNull()) {
     if (AnObject->IsKind(STANDARD_TYPE(GEOMImpl_PrismDriver))) {
       _anOtherObject = Handle(GEOMImpl_PrismDriver)((Handle(GEOMImpl_PrismDriver)&)AnObject);
     }
  }

  return _anOtherObject ;
}