// File generated by CPPExt (Transient)
//
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

#ifndef _GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape_HeaderFile
#define _GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Handle_GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape_HeaderFile
#include <Handle_GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape.hxx>
#endif

#ifndef _GEOMAlgo_PassKey_HeaderFile
#include <GEOMAlgo_PassKey.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _TopTools_ListOfShape_HeaderFile
#include <TopTools_ListOfShape.hxx>
#endif
#ifndef _TCollection_MapNodePtr_HeaderFile
#include <TCollection_MapNodePtr.hxx>
#endif
#ifndef _TCollection_MapNode_HeaderFile
#include <TCollection_MapNode.hxx>
#endif
class GEOMAlgo_PassKey;
class TopTools_ListOfShape;
class GEOMAlgo_PassKeyMapHasher;
class GEOMAlgo_IndexedDataMapOfPassKeyListOfShape;


class GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape : public TCollection_MapNode {

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
 // Methods PUBLIC
 // 
GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape(const GEOMAlgo_PassKey& K1,const Standard_Integer K2,const TopTools_ListOfShape& I,const TCollection_MapNodePtr& n1,const TCollection_MapNodePtr& n2);
  GEOMAlgo_PassKey& Key1() const;
  Standard_Integer& Key2() const;
  TCollection_MapNodePtr& Next2() const;
  TopTools_ListOfShape& Value() const;
Standard_EXPORT ~GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape();




 // Type management
 //
 Standard_EXPORT friend Handle_Standard_Type& GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape_Type_();
 Standard_EXPORT const Handle(Standard_Type)& DynamicType() const;
 Standard_EXPORT Standard_Boolean	       IsKind(const Handle(Standard_Type)&) const;

protected:

 // Methods PROTECTED
 // 


 // Fields PROTECTED
 //


private: 

 // Methods PRIVATE
 // 


 // Fields PRIVATE
 //
GEOMAlgo_PassKey myKey1;
Standard_Integer myKey2;
TopTools_ListOfShape myValue;
TCollection_MapNodePtr myNext2;


};

#define TheKey GEOMAlgo_PassKey
#define TheKey_hxx <GEOMAlgo_PassKey.hxx>
#define TheItem TopTools_ListOfShape
#define TheItem_hxx <TopTools_ListOfShape.hxx>
#define Hasher GEOMAlgo_PassKeyMapHasher
#define Hasher_hxx <GEOMAlgo_PassKeyMapHasher.hxx>
#define TCollection_IndexedDataMapNode GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape
#define TCollection_IndexedDataMapNode_hxx <GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape.hxx>
#define Handle_TCollection_IndexedDataMapNode Handle_GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape
#define TCollection_IndexedDataMapNode_Type_() GEOMAlgo_IndexedDataMapNodeOfIndexedDataMapOfPassKeyListOfShape_Type_()
#define TCollection_IndexedDataMap GEOMAlgo_IndexedDataMapOfPassKeyListOfShape
#define TCollection_IndexedDataMap_hxx <GEOMAlgo_IndexedDataMapOfPassKeyListOfShape.hxx>

#include <TCollection_IndexedDataMapNode.lxx>

#undef TheKey
#undef TheKey_hxx
#undef TheItem
#undef TheItem_hxx
#undef Hasher
#undef Hasher_hxx
#undef TCollection_IndexedDataMapNode
#undef TCollection_IndexedDataMapNode_hxx
#undef Handle_TCollection_IndexedDataMapNode
#undef TCollection_IndexedDataMapNode_Type_
#undef TCollection_IndexedDataMap
#undef TCollection_IndexedDataMap_hxx


// other Inline functions and methods (like "C++: function call" methods)
//


#endif