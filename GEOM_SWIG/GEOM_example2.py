#  GEOM GEOM_SWIG : binding of C++ omplementaion with Python
#
#  Copyright (C) 2003  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
#  CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS 
# 
#  This library is free software; you can redistribute it and/or 
#  modify it under the terms of the GNU Lesser General Public 
#  License as published by the Free Software Foundation; either 
#  version 2.1 of the License. 
# 
#  This library is distributed in the hope that it will be useful, 
#  but WITHOUT ANY WARRANTY; without even the implied warranty of 
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
#  Lesser General Public License for more details. 
# 
#  You should have received a copy of the GNU Lesser General Public 
#  License along with this library; if not, write to the Free Software 
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA 
# 
#  See http://www.opencascade.org/SALOME/ or email : webmaster.salome@opencascade.org 
#
#
#
#  File   : GEOM_example2.py
#  Author : Paul RASCLE, EDF
#  Module : GEOM
#  $Header$

import salome
import geompy
import math

geom = salome.lcc.FindOrLoadComponent("FactoryServer", "Geometry")
myBuilder = salome.myStudy.NewBuilder()

point0  = geom.MakePointStruct(0.,0.,0.)
pointz1 = geom.MakePointStruct(0.,0.,1.)
dirz = geom.MakeDirection(pointz1)

torus1 = geompy.MakeTorus(point0,dirz,150.,25.)
id_torus1 = geompy.addToStudy(torus1,"torus1")

torus2 = geom.MakeCopy(torus1)
torus2 = geom.MakeTranslation(torus2,0.,0.,100.)
id_torus2 = geompy.addToStudy(torus2,"torus2")

cylz1 = geompy.MakeCylinder(point0,dirz,25.,100.)

ind = 0
cyllist = []
while ind < 6:
    acyl = geom.MakeCopy(cylz1)
    x = 150. * math.cos(ind * math.pi/3.)
    y = 150. * math.sin(ind * math.pi/3.)
    z = 0.
    name = "cyl%d"%(ind)
    acyl = geompy.MakeTranslation(acyl,x,y,z)
    id_acyl = geompy.addToStudy(acyl,name)
    cyllist.append(acyl)
    ind = ind +1



                                  