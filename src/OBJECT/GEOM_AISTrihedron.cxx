//  GEOM_AISTrihedron : Filter for VTK viewer
//
//  Copyright (C) 2003  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
//  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
//  See http://www.opencascade.org/SALOME/ or email : webmaster.salome@opencascade.org
//
//
//
//  File   : GEOM_AISTrihedron.cxx
//  Author : Sergey LITONIN
//  Module : SALOME

#include "GEOM_AISTrihedron.hxx"
#include <Geom_Axis2Placement.hxx>

IMPLEMENT_STANDARD_HANDLE(GEOM_AISTrihedron, AIS_Trihedron)
IMPLEMENT_STANDARD_RTTIEXT(GEOM_AISTrihedron, AIS_Trihedron)

/*
  Class       : GEOM_AISTrihedron
  Description : Interactive object for displaying local CS
*/

GEOM_AISTrihedron::GEOM_AISTrihedron( const Handle(Geom_Axis2Placement)& thePlc )
: AIS_Trihedron( thePlc )
{

}
Handle(SALOME_InteractiveObject) GEOM_AISTrihedron::getIO()
{
  return myObject;
}
Standard_Boolean GEOM_AISTrihedron::hasIO()
{
  return !myObject.IsNull();
}

Standard_CString GEOM_AISTrihedron::getName()
{
  return myName.ToCString();
}
void GEOM_AISTrihedron::setName( Standard_CString aName )
{
  myName = TCollection_AsciiString( aName );
}

void GEOM_AISTrihedron::setIO( const Handle(SALOME_InteractiveObject)& theIO )
{
  myObject = theIO;
}






  