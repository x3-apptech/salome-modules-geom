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

#ifndef _Handle_GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger_HeaderFile
#define _Handle_GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger_HeaderFile

#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif
#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif

#ifndef _Handle_TCollection_MapNode_HeaderFile
#include <Handle_TCollection_MapNode.hxx>
#endif

class Standard_Transient;
class Handle_Standard_Type;
class Handle(TCollection_MapNode);
class GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger;
Standard_EXPORT Handle_Standard_Type& STANDARD_TYPE(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger);

class Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger) : public Handle(TCollection_MapNode) {
  public:
    void* operator new(size_t,void* anAddress) 
      {
        return anAddress;
      }
    void* operator new(size_t size) 
      { 
        return Standard::Allocate(size); 
      }
    void  operator delete(void *anAddress) 
      { 
        if (anAddress) Standard::Free((Standard_Address&)anAddress); 
      }
    Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger)():Handle(TCollection_MapNode)() {} 
    Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger)(const Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger)& aHandle) : Handle(TCollection_MapNode)(aHandle) 
     {
     }

    Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger)(const GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger* anItem) : Handle(TCollection_MapNode)((TCollection_MapNode *)anItem) 
     {
     }

    Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger)& operator=(const Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger)& aHandle)
     {
      Assign(aHandle.Access());
      return *this;
     }

    Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger)& operator=(const GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger* anItem)
     {
      Assign((Standard_Transient *)anItem);
      return *this;
     }

    GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger* operator->() 
     {
      return (GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger *)ControlAccess();
     }

    GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger* operator->() const 
     {
      return (GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger *)ControlAccess();
     }

   Standard_EXPORT ~Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger)();
 
   Standard_EXPORT static const Handle(GEOMAlgo_DataMapNodeOfDataMapOfPassKeyInteger) DownCast(const Handle(Standard_Transient)& AnObject);
};
#endif