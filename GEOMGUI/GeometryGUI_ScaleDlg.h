//  GEOM GEOMGUI : GUI for Geometry component
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
//  File   : GeometryGUI_ScaleDlg.h
//  Author : Lucien PIGNOLONI
//  Module : GEOM
//  $Header$

#ifndef DIALOGBOX_SCALE_H
#define DIALOGBOX_SCALE_H

#include "SALOME_Selection.h"
#include "GEOM_ShapeTypeFilter.hxx"

#include <gp_Pnt.hxx>

#include <qvariant.h>
#include <qdialog.h>

class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout;
class QButtonGroup;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class GeometryGUI;


//=================================================================================
// class    : GeometryGUI_ScaleDlg
// purpose  :
//=================================================================================
class GeometryGUI_ScaleDlg : public QDialog
{ 
    Q_OBJECT

public:
    GeometryGUI_ScaleDlg( QWidget* parent = 0, const char* name = 0, SALOME_Selection* Sel = 0, bool modal = FALSE, WFlags fl = 0 );
    ~GeometryGUI_ScaleDlg();

private :
 
    void closeEvent( QCloseEvent* e ) ;
    void enterEvent( QEvent* e );
    void Init(SALOME_Selection* Sel) ;
    void MakeScaleSimulationAndDisplay( const TopoDS_Shape& S ) ;

    GEOM::GEOM_Gen_var myGeom ;                /* Current GeomI object */
    GeometryGUI*          myGeomGUI ;             /* Current GeomGUI object */
    TopoDS_Shape          mySimulationTopoDs ;    /* Shape used for simulation display */
    SALOME_Selection*     mySelection ;           /* User shape selection */    
    gp_Pnt                myPoint1 ;              /* Points containing the vector */
    TopoDS_Shape          myBaseTopo ;
    GEOM::GEOM_Shape_var        myGeomShape ;           /* is myBaseTopo */
    Standard_Real         myFactor ;
    bool                  myOkPoint1 ;            /* true when myPoint1 is defined */
    bool                  myOkBaseTopo ;          /* true when myBaseTopo is defined */
    int                   myConstructorId ;       /* Current constructor id = radio button id */ 
    QLineEdit*            myEditCurrentArgument;  /* Current LineEdit */
    Handle(GEOM_ShapeTypeFilter) myVertexFilter;  /* filter for selection */

    QButtonGroup* GroupConstructors;
    QRadioButton* Constructor1;
    QGroupBox* GroupC1;
    QLabel* TextLabelC1A1;
    QLabel* TextLabelC1A2;
    QPushButton* SelectButtonC1A1;
    QPushButton* SelectButtonC1A2;
    QLineEdit* LineEditC1A1;
    QLineEdit* LineEditC1A2;
    QLineEdit* LineEditC1A3;
    QLabel* TextLabelC1A3;
    QGroupBox* GroupButtons;
    QPushButton* buttonApply;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

private slots :
    
    void ConstructorsClicked(int constructorId);
    void ClickOnOk();
    void ClickOnCancel();
    void ClickOnApply();
    void SetEditCurrentArgument() ;
    void SelectionIntoArgument() ;
    void LineEditReturnPressed() ;
    void DeactivateActiveDialog() ;
    void ActivateThisDialog() ; 
    void TextChangedInLineEdit(const QString& newText) ;

protected:
    QGridLayout* GeometryGUI_ScaleDlgLayout;
    QGridLayout* GroupConstructorsLayout;
    QGridLayout* GroupC1Layout;
    QGridLayout* GroupButtonsLayout;
};

#endif // DIALOGBOX_SCALE_H