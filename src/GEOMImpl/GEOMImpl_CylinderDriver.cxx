
using namespace std;
#include "GEOMImpl_CylinderDriver.hxx"
#include "GEOMImpl_ICylinder.hxx"
#include "GEOMImpl_Types.hxx"
#include "GEOM_Function.hxx"

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRep_Tool.hxx>

#include <TopAbs.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopExp.hxx>

#include <Standard_TypeMismatch.hxx>
#include <Standard_NullObject.hxx>
#include <StdFail_NotDone.hxx>
#include <gp_Pnt.hxx>
#include <gp.hxx>

//=======================================================================
//function : GetID
//purpose  :
//=======================================================================
const Standard_GUID& GEOMImpl_CylinderDriver::GetID()
{
  static Standard_GUID aCylinderDriver("FF1BBB14-5D14-4df2-980B-3A668264EA16");
  return aCylinderDriver;
}


//=======================================================================
//function : GEOMImpl_CylinderDriver
//purpose  :
//=======================================================================
GEOMImpl_CylinderDriver::GEOMImpl_CylinderDriver()
{
}

//=======================================================================
//function : Execute
//purpose  :
//=======================================================================
Standard_Integer GEOMImpl_CylinderDriver::Execute(TFunction_Logbook& log) const
{
  if (Label().IsNull()) return 0;
  Handle(GEOM_Function) aFunction = GEOM_Function::GetFunction(Label());

  GEOMImpl_ICylinder aCI (aFunction);
  Standard_Integer aType = aFunction->GetType();

  gp_Pnt aP;
  gp_Vec aV;

  if (aType == CYLINDER_R_H) {
    aP = gp::Origin();
    aV = gp::DZ();
  }
  else if (aType == CYLINDER_PNT_VEC_R_H) {
    Handle(GEOM_Function) aRefPoint  = aCI.GetPoint();
    Handle(GEOM_Function) aRefVector = aCI.GetVector();
    TopoDS_Shape aShapePnt = aRefPoint->GetValue();
    TopoDS_Shape aShapeVec = aRefVector->GetValue();
    if (aShapePnt.IsNull() || aShapeVec.IsNull()) {
      Standard_NullObject::Raise("Cylinder creation aborted: point or vector is not defined");
    }
    if (aShapePnt.ShapeType() != TopAbs_VERTEX ||
        aShapeVec.ShapeType() != TopAbs_EDGE) {
      Standard_TypeMismatch::Raise("Cylinder creation aborted: point or vector shapes has wrong type");
    }

    aP = BRep_Tool::Pnt(TopoDS::Vertex(aShapePnt));

    TopoDS_Edge anE = TopoDS::Edge(aShapeVec);
    TopoDS_Vertex V1, V2;
    TopExp::Vertices(anE, V1, V2, Standard_True);
    if (V1.IsNull() || V2.IsNull()) {
      Standard_NullObject::Raise("Cylinder creation aborted: vector is not defined");
    }
    aV = gp_Vec(BRep_Tool::Pnt(V1), BRep_Tool::Pnt(V2));
  }
  else {
    return 0;
  }

  if (aCI.GetH() < 0.0) aV.Reverse();
  gp_Ax2 anAxes (aP, aV);

  BRepPrimAPI_MakeCylinder MC (anAxes, aCI.GetR(), Abs(aCI.GetH()));
  MC.Build();
  if (!MC.IsDone()) {
    StdFail_NotDone::Raise("Cylinder can't be computed from the given parameters");
  }

  TopoDS_Shape aShape = MC.Shape();
  if (aShape.IsNull()) return 0;

  aFunction->SetValue(aShape);

  log.SetTouched(Label());

  return 1;
}


//=======================================================================
//function :  GEOMImpl_CylinderDriver_Type_
//purpose  :
//=======================================================================
Standard_EXPORT Handle_Standard_Type& GEOMImpl_CylinderDriver_Type_()
{

  static Handle_Standard_Type aType1 = STANDARD_TYPE(TFunction_Driver);
  if ( aType1.IsNull()) aType1 = STANDARD_TYPE(TFunction_Driver);
  static Handle_Standard_Type aType2 = STANDARD_TYPE(MMgt_TShared);
  if ( aType2.IsNull()) aType2 = STANDARD_TYPE(MMgt_TShared);
  static Handle_Standard_Type aType3 = STANDARD_TYPE(Standard_Transient);
  if ( aType3.IsNull()) aType3 = STANDARD_TYPE(Standard_Transient);


  static Handle_Standard_Transient _Ancestors[]= {aType1,aType2,aType3,NULL};
  static Handle_Standard_Type _aType = new Standard_Type("GEOMImpl_CylinderDriver",
			                                 sizeof(GEOMImpl_CylinderDriver),
			                                 1,
			                                 (Standard_Address)_Ancestors,
			                                 (Standard_Address)NULL);

  return _aType;
}

//=======================================================================
//function : DownCast
//purpose  :
//=======================================================================
const Handle(GEOMImpl_CylinderDriver) Handle(GEOMImpl_CylinderDriver)::DownCast(const Handle(Standard_Transient)& AnObject)
{
  Handle(GEOMImpl_CylinderDriver) _anOtherObject;

  if (!AnObject.IsNull()) {
     if (AnObject->IsKind(STANDARD_TYPE(GEOMImpl_CylinderDriver))) {
       _anOtherObject = Handle(GEOMImpl_CylinderDriver)((Handle(GEOMImpl_CylinderDriver)&)AnObject);
     }
  }

  return _anOtherObject ;
}