// File generated by CPPExt (Transient)
//
//                     Copyright (C) 1991 - 2000 by  
//                      Matra Datavision SA.  All rights reserved.
//  
//                     Copyright (C) 2001 - 2004 by
//                     Open CASCADE SA.  All rights reserved.
// 
// This file is part of the Open CASCADE Technology software.
//
// This software may be distributed and/or modified under the terms and
// conditions of the Open CASCADE Public License as defined by Open CASCADE SA
// and appearing in the file LICENSE included in the packaging of this file.
//  
// This software is distributed on an "AS IS" basis, without warranty of any
// kind, and Open CASCADE SA hereby disclaims all such warranties,
// including without limitation, any warranties of merchantability, fitness
// for a particular purpose or non-infringement. Please see the License for
// the specific terms and conditions governing rights and limitations under the
// License.

#include <BlockFix_SphereSpaceModifier.jxx>

#ifndef _Standard_TypeMismatch_HeaderFile
#include <Standard_TypeMismatch.hxx>
#endif

BlockFix_SphereSpaceModifier::~BlockFix_SphereSpaceModifier() {}
 


Standard_EXPORT Handle_Standard_Type& BlockFix_SphereSpaceModifier_Type_()
{

    static Handle_Standard_Type aType1 = STANDARD_TYPE(BRepTools_Modification);
  if ( aType1.IsNull()) aType1 = STANDARD_TYPE(BRepTools_Modification);
  static Handle_Standard_Type aType2 = STANDARD_TYPE(MMgt_TShared);
  if ( aType2.IsNull()) aType2 = STANDARD_TYPE(MMgt_TShared);
  static Handle_Standard_Type aType3 = STANDARD_TYPE(Standard_Transient);
  if ( aType3.IsNull()) aType3 = STANDARD_TYPE(Standard_Transient);
 

  static Handle_Standard_Transient _Ancestors[]= {aType1,aType2,aType3,NULL};
  static Handle_Standard_Type _aType = new Standard_Type("BlockFix_SphereSpaceModifier",
			                                 sizeof(BlockFix_SphereSpaceModifier),
			                                 1,
			                                 (Standard_Address)_Ancestors,
			                                 (Standard_Address)NULL);

  return _aType;
}


// DownCast method
//   allow safe downcasting
//
const Handle(BlockFix_SphereSpaceModifier) Handle(BlockFix_SphereSpaceModifier)::DownCast(const Handle(Standard_Transient)& AnObject) 
{
  Handle(BlockFix_SphereSpaceModifier) _anOtherObject;

  if (!AnObject.IsNull()) {
     if (AnObject->IsKind(STANDARD_TYPE(BlockFix_SphereSpaceModifier))) {
       _anOtherObject = Handle(BlockFix_SphereSpaceModifier)((Handle(BlockFix_SphereSpaceModifier)&)AnObject);
     }
  }

  return _anOtherObject ;
}
const Handle(Standard_Type)& BlockFix_SphereSpaceModifier::DynamicType() const 
{ 
  return STANDARD_TYPE(BlockFix_SphereSpaceModifier) ; 
}
Standard_Boolean BlockFix_SphereSpaceModifier::IsKind(const Handle(Standard_Type)& AType) const 
{ 
  return (STANDARD_TYPE(BlockFix_SphereSpaceModifier) == AType || BRepTools_Modification::IsKind(AType)); 
}
Handle_BlockFix_SphereSpaceModifier::~Handle_BlockFix_SphereSpaceModifier() {}
