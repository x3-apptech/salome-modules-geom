using namespace std;

#include "GEOM_ILocalOperations_i.hh"

#include "utilities.h"
#include "OpUtil.hxx"
#include "Utils_ExceptHandlers.hxx"

#include "GEOM_Engine.hxx"
#include "GEOM_Object.hxx"

//=============================================================================
/*!
 *   constructor:
 */
//=============================================================================
GEOM_ILocalOperations_i::GEOM_ILocalOperations_i (PortableServer::POA_ptr thePOA,
						  GEOM::GEOM_Gen_ptr theEngine,
						  ::GEOMImpl_ILocalOperations* theImpl)
     :GEOM_IOperations_i(thePOA, theEngine, theImpl)
{
  MESSAGE("GEOM_ILocalOperations_i::GEOM_ILocalOperations_i");
}

//=============================================================================
/*!
 *  destructor
 */
//=============================================================================
GEOM_ILocalOperations_i::~GEOM_ILocalOperations_i()
{
  MESSAGE("GEOM_ILocalOperations_i::~GEOM_ILocalOperations_i");
}


//=============================================================================
/*!
 *  MakeFilletAll
 */
//=============================================================================
GEOM::GEOM_Object_ptr GEOM_ILocalOperations_i::MakeFilletAll
                      (GEOM::GEOM_Object_ptr theShape, CORBA::Double theR)
{
  GEOM::GEOM_Object_var aGEOMObject;

  if (theShape == NULL) return aGEOMObject._retn();

  //Get the reference shape
  Handle(GEOM_Object) aShapeRef = GetOperations()->GetEngine()->GetObject
    (theShape->GetStudyID(), theShape->GetEntry());

  if (aShapeRef.IsNull()) return aGEOMObject._retn();

  //Create the Fillet
  Handle(GEOM_Object) anObject =
    GetOperations()->MakeFilletAll(aShapeRef, theR);
  if (!GetOperations()->IsDone() || anObject.IsNull())
    return aGEOMObject._retn();

  return GetObject(anObject);
}

//=============================================================================
/*!
 *  MakeFilletEdges
 */
//=============================================================================
GEOM::GEOM_Object_ptr GEOM_ILocalOperations_i::MakeFilletEdges
                      (GEOM::GEOM_Object_ptr theShape, CORBA::Double theR,
		       const GEOM::ListOfLong& theEdges)
{
  GEOM::GEOM_Object_var aGEOMObject;

  if (theShape == NULL) return aGEOMObject._retn();

  //Get the reference shape
  Handle(GEOM_Object) aShapeRef = GetOperations()->GetEngine()->GetObject
    (theShape->GetStudyID(), theShape->GetEntry());
  if (aShapeRef.IsNull()) return aGEOMObject._retn();

  //Get the reference edges
  int ind = 0;
  int aLen = theEdges.length();
  list<int> anEdges;
  for (; ind < aLen; ind++) {
    anEdges.push_back(theEdges[ind]);
  }

  //Create the Fillet
  Handle(GEOM_Object) anObject =
    GetOperations()->MakeFilletEdges(aShapeRef, theR, anEdges);
  if (!GetOperations()->IsDone() || anObject.IsNull())
    return aGEOMObject._retn();

  return GetObject(anObject);
}

//=============================================================================
/*!
 *  MakeFilletFaces
 */
//=============================================================================
GEOM::GEOM_Object_ptr GEOM_ILocalOperations_i::MakeFilletFaces
                      (GEOM::GEOM_Object_ptr theShape, CORBA::Double theR,
		       const GEOM::ListOfLong& theFaces)
{
  GEOM::GEOM_Object_var aGEOMObject;

  if (theShape == NULL) return aGEOMObject._retn();

  //Get the reference shape
  Handle(GEOM_Object) aShapeRef = GetOperations()->GetEngine()->GetObject
    (theShape->GetStudyID(), theShape->GetEntry());
  if (aShapeRef.IsNull()) return aGEOMObject._retn();

  //Get the reference faces
  int ind = 0;
  int aLen = theFaces.length();
  list<int> aFaces;
  for (; ind < aLen; ind++) {
    aFaces.push_back(theFaces[ind]);
  }

  //Create the Fillet
  Handle(GEOM_Object) anObject =
    GetOperations()->MakeFilletFaces(aShapeRef, theR, aFaces);
  if (!GetOperations()->IsDone() || anObject.IsNull())
    return aGEOMObject._retn();

  return GetObject(anObject);
}

//=============================================================================
/*!
 *  MakeChamferAll
 */
//=============================================================================
GEOM::GEOM_Object_ptr GEOM_ILocalOperations_i::MakeChamferAll
                      (GEOM::GEOM_Object_ptr theShape, CORBA::Double theD)
{
  GEOM::GEOM_Object_var aGEOMObject;

  if (theShape == NULL) return aGEOMObject._retn();

  //Get the reference shape
  Handle(GEOM_Object) aShapeRef = GetOperations()->GetEngine()->GetObject
    (theShape->GetStudyID(), theShape->GetEntry());

  if (aShapeRef.IsNull()) return aGEOMObject._retn();

  //Create the Chamfer
  Handle(GEOM_Object) anObject =
    GetOperations()->MakeChamferAll(aShapeRef, theD);
  if (!GetOperations()->IsDone() || anObject.IsNull())
    return aGEOMObject._retn();

  return GetObject(anObject);
}

//=============================================================================
/*!
 *  MakeChamferEdge
 */
//=============================================================================
GEOM::GEOM_Object_ptr GEOM_ILocalOperations_i::MakeChamferEdge
                      (GEOM::GEOM_Object_ptr theShape,
		       CORBA::Double theD1, CORBA::Double theD2,
		       CORBA::Long theFace1, CORBA::Long theFace2)
{
  GEOM::GEOM_Object_var aGEOMObject;

  if (theShape == NULL) return aGEOMObject._retn();

  //Get the reference shape
  Handle(GEOM_Object) aShapeRef = GetOperations()->GetEngine()->GetObject
    (theShape->GetStudyID(), theShape->GetEntry());
  if (aShapeRef.IsNull()) return aGEOMObject._retn();

  //Create the Chamfer
  Handle(GEOM_Object) anObject =
    GetOperations()->MakeChamferEdge(aShapeRef, theD1, theD2, theFace1, theFace2);
  if (!GetOperations()->IsDone() || anObject.IsNull())
    return aGEOMObject._retn();

  return GetObject(anObject);
}

//=============================================================================
/*!
 *  MakeChamferFaces
 */
//=============================================================================
GEOM::GEOM_Object_ptr GEOM_ILocalOperations_i::MakeChamferFaces
                      (GEOM::GEOM_Object_ptr theShape,
		       CORBA::Double theD1, CORBA::Double theD2,
		       const GEOM::ListOfLong& theFaces)
{
  GEOM::GEOM_Object_var aGEOMObject;

  if (theShape == NULL) return aGEOMObject._retn();

  //Get the reference shape
  Handle(GEOM_Object) aShapeRef = GetOperations()->GetEngine()->GetObject
    (theShape->GetStudyID(), theShape->GetEntry());
  if (aShapeRef.IsNull()) return aGEOMObject._retn();

  //Get the reference faces
  int ind = 0;
  int aLen = theFaces.length();
  list<int> aFaces;
  for (; ind < aLen; ind++) {
    aFaces.push_back(theFaces[ind]);
  }

  //Create the Chamfer
  Handle(GEOM_Object) anObject =
    GetOperations()->MakeChamferFaces(aShapeRef, theD1, theD2, aFaces);
  if (!GetOperations()->IsDone() || anObject.IsNull())
    return aGEOMObject._retn();

  return GetObject(anObject);
}

//=============================================================================
/*!
 *  MakeArchimede
 */
//=============================================================================
GEOM::GEOM_Object_ptr GEOM_ILocalOperations_i::MakeArchimede (GEOM::GEOM_Object_ptr theShape,
							      CORBA::Double theWeight,
							      CORBA::Double theWaterDensity,
							      CORBA::Double theMeshingDeflection)
{
  GEOM::GEOM_Object_var aGEOMObject;

  if (theShape == NULL) return aGEOMObject._retn();

  //Get the reference shape
  Handle(GEOM_Object) aShapeRef = GetOperations()->GetEngine()->GetObject
    (theShape->GetStudyID(), theShape->GetEntry());
  if (aShapeRef.IsNull()) return aGEOMObject._retn();

  //Create the Archimede
  Handle(GEOM_Object) anObject = GetOperations()->MakeArchimede
    (aShapeRef, theWeight, theWaterDensity, theMeshingDeflection);
  if (!GetOperations()->IsDone() || anObject.IsNull())
    return aGEOMObject._retn();

  return GetObject(anObject);
}

//=============================================================================
/*!
 *  GetSubShapeIndex
 */
//=============================================================================
CORBA::Long GEOM_ILocalOperations_i::GetSubShapeIndex
  (GEOM::GEOM_Object_ptr theShape, GEOM::GEOM_Object_ptr theSubShape)
{
  if (theShape == NULL || theSubShape == NULL) return -1;

  //Get the reference shapes
  Handle(GEOM_Object) aShapeRef = GetOperations()->GetEngine()->GetObject
    (theShape->GetStudyID(), theShape->GetEntry());
  Handle(GEOM_Object) aSubShapeRef = GetOperations()->GetEngine()->GetObject
    (theSubShape->GetStudyID(), theSubShape->GetEntry());
  if (aShapeRef.IsNull() || aSubShapeRef.IsNull()) return -1;

  //Get the unique ID of <theSubShape> inside <theShape>
  CORBA::Long anID = GetOperations()->GetSubShapeIndex(aShapeRef, aSubShapeRef);
  if (!GetOperations()->IsDone())
    return -1;

  return anID;
}