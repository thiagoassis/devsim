/***
DEVSIM
Copyright 2013 Devsim LLC

This file is part of DEVSIM.

DEVSIM is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, version 3.

DEVSIM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with DEVSIM.  If not, see <http://www.gnu.org/licenses/>.
***/

#ifndef INTERFACE_HH
#define INTERFACE_HH
#include "MathEnum.hh"
#include "dsmemory.hh"
#include <string>
#include <vector>
#include <map>
#include <set>

template <typename T> class ObjectCache;
namespace IMEE {
class InterfaceModelExprData;
}
typedef ObjectCache<IMEE::InterfaceModelExprData> InterfaceModelExprDataCache;
typedef std::tr1::weak_ptr<InterfaceModelExprDataCache >   WeakInterfaceModelExprDataCachePtr;
typedef std::tr1::shared_ptr<InterfaceModelExprDataCache > InterfaceModelExprDataCachePtr;

class Node;
class Edge;
class Triangle;

class Region;
typedef Region *RegionPtr;
typedef const Region *ConstRegionPtr;

class InterfaceNodeModel;
typedef std::tr1::shared_ptr<InterfaceNodeModel>       InterfaceNodeModelPtr;
typedef std::tr1::shared_ptr<const InterfaceNodeModel> ConstInterfaceNodeModelPtr;

class InterfaceEquation;
typedef InterfaceEquation *InterfaceEquationPtr;

class PermutationEntry;
typedef std::map<size_t, PermutationEntry> PermutationMap;
namespace dsMath {
template <typename T> class RowColVal;
typedef std::vector<RowColVal<double> > RealRowColValueVec;
typedef std::pair<int, double> RHSEntry;
typedef std::vector<RHSEntry> RHSEntryVec;
}



/// All nodes on an interface share the same nodes
/// todo: somehow regions must signal when they are deleted so the Interface knows it is invalid (perhaps using callback)
class Interface {
    public:
        typedef std::map<std::string, InterfaceEquationPtr> InterfaceEquationPtrMap_t;
        typedef std::vector<const Node *>     ConstNodeList_t;
        typedef std::vector<const Edge *>     ConstEdgeList_t;
        typedef std::vector<const Triangle *> ConstTriangleList_t;
        typedef std::map<std::string, InterfaceNodeModelPtr> NameToInterfaceNodeModelMap_t;
        typedef std::map<std::string, std::set<std::string> > DependencyMap_t;

        ~Interface();

        Interface(const std::string &, Region *, Region *, const ConstNodeList_t &, const ConstNodeList_t &);

        ConstRegionPtr GetRegion0() const {
            return rp0;
        }
        ConstRegionPtr GetRegion1() const {
            return rp1;
        }

        const std::string &GetDeviceName() const;

        const ConstNodeList_t &GetNodes0() const {
          return nodes0;
        }

        const ConstNodeList_t &GetNodes1() const {
          return nodes1;
        }

        const ConstEdgeList_t &GetEdges0() const;
        const ConstEdgeList_t &GetEdges1() const;

        const ConstTriangleList_t &GetTriangles0() const;
        const ConstTriangleList_t &GetTriangles1() const;

        const std::string &GetName() const {
            return name;
        }

        void AddInterfaceEquation(InterfaceEquationPtr);
        const InterfaceEquationPtrMap_t &GetInterfaceEquationList() const;

        // try using a multimap first
        void RegisterCallback(const std::string &, const std::string &);
        // model can signal dependencies, passing this
        // Note that a NodeModelPtr can signal both EdgeModels and NodeModels
        void SignalCallbacks(const std::string &);

        void SignalCallbacks(const std::string &, ConstRegionPtr /*rp*/);

        // unregister a model when it is destructed
        void UnregisterCallback(const std::string &);


        /// passes ownership
        void AddInterfaceNodeModel(InterfaceNodeModel *);
        ConstInterfaceNodeModelPtr GetInterfaceNodeModel(const std::string &) const;

        void DeleteInterfaceNodeModel(const std::string &);

        const NameToInterfaceNodeModelMap_t &GetInterfaceNodeModelList() const;

        void Assemble(dsMath::RealRowColValueVec &, dsMath::RHSEntryVec &, PermutationMap &, dsMathEnum::WhatToLoad, dsMathEnum::TimeMode);

        bool operator==(const Interface &oi) const
        {
          return (&oi) == this;
        }

        std::string GetSurfaceAreaModel() const;

        InterfaceModelExprDataCachePtr GetInterfaceModelExprDataCache();
        void SetInterfaceModelExprDataCache(InterfaceModelExprDataCachePtr);

    private:
        void FindEdges() const;
        void FindTriangles() const;

        Interface();
        Interface(const Interface &);
        Interface & operator=(const Interface &);

        std::string name;
        RegionPtr rp0; 
        RegionPtr rp1;
        ConstNodeList_t     nodes0;  // Pointers to nodes in region 0
        ConstNodeList_t     nodes1;  // Pointers to nodes in region 1
        //// Note the edges and triangles don't necessarily have the same ordering
        //// on both sides of the interface
        mutable ConstEdgeList_t     edges0;  // Pointers to edges in region 0
        mutable ConstEdgeList_t     edges1;  // Pointers to edges in region 1
        mutable ConstTriangleList_t triangles0;  // Pointers to triangles in region 0
        mutable ConstTriangleList_t triangles1;  // Pointers to triangles in region 1
        InterfaceEquationPtrMap_t interfaceEquationList;
        NameToInterfaceNodeModelMap_t interfaceNodeModels;

        DependencyMap_t DependencyMap;

        WeakInterfaceModelExprDataCachePtr interfaceModelExprDataCache;

};
#endif
