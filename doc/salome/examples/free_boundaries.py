# Check Free Boundaries

import salome
salome.salome_init_without_session()
from salome.geom import geomBuilder
geompy = geomBuilder.New()

# create a shape
box1 = geompy.MakeBox(0,   0,   0, 100, 100, 100)
box2 = geompy.MakeBox(20, 20, -20,  80,  80, 120)
cut  = geompy.MakeCut(box1, box2)
sid = geompy.addToStudy(cut, "Shape")

# get all faces
faces = geompy.SubShapeAllSortedCentres(cut, geompy.ShapeType["FACE"])

# for each face, get free boundaries
for fi in range(len(faces)):
    fid = geompy.addToStudyInFather(cut, faces[fi], "Face %d" % (fi+1))
    isSuccess, closedWires, openWires = geompy.GetFreeBoundary(faces[fi])
    if isSuccess:
        print("Check free boundaries in face %d: OK" % (fi+1))
        print("-- Nb of closed boundaries = %d" % len(closedWires))
        for wi in range(len(closedWires)):
            wid = geompy.addToStudyInFather(faces[fi], closedWires[wi], "Closed wire %d" % (wi+1))
            pass
        print("-- Nb of open boundaries = %d" % len(openWires))
        for wi in range(len(openWires)):
            wid = geompy.addToStudyInFather(faces[fi], openWires[wi], "Open wire %d" % (wi+1))
            pass
        pass
    else:
        print("Check free boundaries in face %d: KO" % (fi+1))
        pass
    pass
