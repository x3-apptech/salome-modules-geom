//  GEOM GEOMDS : implementation of Geometry component data structure and Geometry documents management
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
//  File   : GEOMDS_DataMapOfIntegerTransient.hxx
//  Module : GEOM

#ifndef _GEOMDS_DataMapOfIntegerTransient_HeaderFile
#define _GEOMDS_DataMapOfIntegerTransient_HeaderFile

#ifndef _TCollection_BasicMap_HeaderFile
#include <TCollection_BasicMap.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_Standard_Transient_HeaderFile
#include <Handle_Standard_Transient.hxx>
#endif
#ifndef _Handle_GEOMDS_DataMapNodeOfDataMapOfIntegerTransient_HeaderFile
#include "Handle_GEOMDS_DataMapNodeOfDataMapOfIntegerTransient.hxx"
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
class Standard_DomainError;
class Standard_NoSuchObject;
class Standard_Transient;
class TColStd_MapIntegerHasher;
class GEOMDS_DataMapNodeOfDataMapOfIntegerTransient;
class GEOMDS_DataMapIteratorOfDataMapOfIntegerTransient;


#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

class GEOMDS_DataMapOfIntegerTransient  : public TCollection_BasicMap {

public:

    inline void* operator new(size_t,void* anAddress) 
      {
        return anAddress;
      }
    inline void* operator new(size_t size) 
      { 
        return Standard::Allocate(size); 
      }
    inline void  operator delete(void *anAddress) 
      { 
        if (anAddress) Standard::Free((Standard_Address&)anAddress); 
      }
//    inline void  operator delete(void *anAddress, size_t size) 
//      { 
//        if (anAddress) Standard::Free((Standard_Address&)anAddress,size); 
//      }
 // Methods PUBLIC
 // 
Standard_EXPORT GEOMDS_DataMapOfIntegerTransient(const Standard_Integer NbBuckets = 1);
Standard_EXPORT GEOMDS_DataMapOfIntegerTransient& Assign(const GEOMDS_DataMapOfIntegerTransient& Other) ;
GEOMDS_DataMapOfIntegerTransient& operator =(const GEOMDS_DataMapOfIntegerTransient& Other) 
{
  return Assign(Other);
}

Standard_EXPORT   void ReSize(const Standard_Integer NbBuckets) ;
Standard_EXPORT   void Clear() ;
~GEOMDS_DataMapOfIntegerTransient()
{
  Clear();
}

Standard_EXPORT   Standard_Boolean Bind(const Standard_Integer& K,const Handle(Standard_Transient)& I) ;
Standard_EXPORT   Standard_Boolean IsBound(const Standard_Integer& K) const;
Standard_EXPORT   Standard_Boolean UnBind(const Standard_Integer& K) ;
Standard_EXPORT  const Handle_Standard_Transient& Find(const Standard_Integer& K) const;
 const Handle_Standard_Transient& operator()(const Standard_Integer& K) const
{
  return Find(K);
}

Standard_EXPORT   Handle_Standard_Transient& ChangeFind(const Standard_Integer& K) ;
  Handle_Standard_Transient& operator()(const Standard_Integer& K) 
{
  return ChangeFind(K);
}


protected:
  
  // Methods PROTECTED
  // 
  
  
  // Fields PROTECTED
  //
  
  
private: 
  
  // Methods PRIVATE
  // 
  Standard_EXPORT GEOMDS_DataMapOfIntegerTransient(const GEOMDS_DataMapOfIntegerTransient& Other);


// Fields PRIVATE
//


};


// other inline functions and methods (like "C++: function call" methods)
//


#endif