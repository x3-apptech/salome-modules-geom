#####################################################################################
#Created                :17/02/2005
#Auhtor                 :KOVALTCHUK Alexey 
#GUI test scenario      :PAL-MESH-019 (geometry part), PAL-MESH-020 (geometry part)
#####################################################################################

import geompy
import salome

#Points creation (2.2)
Vertex_1 = geompy.MakeVertex(0, 0, 0)
geompy.addToStudy(Vertex_1, "Vertex_1")

Vertex_2 = geompy.MakeVertex(20, 0, 0)
geompy.addToStudy(Vertex_2, "Vertex_2")

Vertex_3 = geompy.MakeVertex(10, 10, 0)
geompy.addToStudy(Vertex_3, "Vertex_3")

Vertex_4 = geompy.MakeVertex(0, 100, 0)
geompy.addToStudy(Vertex_4, "Vertex_4")

Vertex_5 = geompy.MakeVertex(0, 80, 20)
geompy.addToStudy(Vertex_5, "Vertex_5")

#Curve creation (2.21)
Curve_1 = geompy.MakeInterpol([Vertex_1, Vertex_3, Vertex_2])
geompy.addToStudy(Curve_1, "Curve_1")

#Line creation (2.29)
Line_1 = geompy.MakeLineTwoPnt(Vertex_4, Vertex_5)
geompy.addToStudy(Line_1, "Line_1")

salome.sg.updateObjBrowser(1)