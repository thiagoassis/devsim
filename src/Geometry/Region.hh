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

#ifndef REGION_HH
#define REGION_HH
#include "MathEnum.hh"

#include "dsmemory.hh"

#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <complex>
class Vector;
class GradientField;
class TriangleElementField;
class TetrahedronElementField;

template <typename T> class ObjectCache;
namespace MEE {
class ModelExprData;
}
typedef ObjectCache<MEE::ModelExprData> ModelExprDataCache;
typedef std::tr1::weak_ptr<ModelExprDataCache >   WeakModelExprDataCachePtr;
typedef std::tr1::shared_ptr<ModelExprDataCache > ModelExprDataCachePtr;

class Device;
typedef Device *DevicePtr;
typedef const Device *ConstDevicePtr;

class NodeModel;
typedef std::tr1::weak_ptr<NodeModel>         WeakNodeModelPtr;
typedef std::tr1::shared_ptr<NodeModel>       NodeModelPtr;
typedef std::tr1::shared_ptr<const NodeModel> ConstNodeModelPtr;

class EdgeModel;
typedef std::tr1::weak_ptr<EdgeModel>         WeakEdgeModelPtr;
typedef std::tr1::shared_ptr<EdgeModel>       EdgeModelPtr;
typedef std::tr1::shared_ptr<const EdgeModel> ConstEdgeModelPtr;

class TriangleEdgeModel;
typedef std::tr1::weak_ptr<TriangleEdgeModel>         WeakTriangleEdgeModelPtr;
typedef std::tr1::shared_ptr<TriangleEdgeModel>       TriangleEdgeModelPtr;
typedef std::tr1::shared_ptr<const TriangleEdgeModel> ConstTriangleEdgeModelPtr;

class TetrahedronEdgeModel;
typedef std::tr1::weak_ptr<TetrahedronEdgeModel>         WeakTetrahedronEdgeModelPtr;
typedef std::tr1::shared_ptr<TetrahedronEdgeModel>       TetrahedronEdgeModelPtr;
typedef std::tr1::shared_ptr<const TetrahedronEdgeModel> ConstTetrahedronEdgeModelPtr;

class Edge;
typedef Edge *EdgePtr;
typedef const Edge *ConstEdgePtr;
typedef std::vector<ConstEdgePtr> ConstEdgeList;


class Node;
typedef Node *NodePtr;
typedef const Node *ConstNodePtr;
typedef std::vector<NodePtr> NodeList;
typedef std::vector<ConstNodePtr> ConstNodeList;

class Triangle;
typedef Triangle *TrianglePtr;
typedef const Triangle *ConstTrianglePtr;
typedef std::vector<ConstTrianglePtr> ConstTriangleList;

//// Used for knowing the two Triangles on each Tetrahedron edge
class EdgeData;
typedef const EdgeData *ConstEdgeDataPtr;
typedef std::vector<ConstEdgeDataPtr> ConstEdgeDataList;


class Tetrahedron;
typedef Tetrahedron *TetrahedronPtr;
typedef const Tetrahedron *ConstTetrahedronPtr;
typedef std::vector<ConstTetrahedronPtr> ConstTetrahedronList;

#if 0
class Contact;
typedef Contact *ContactPtr;
typedef const Contact *ConstContactPtr;
#endif

class Equation;
typedef Equation *EquationPtr;
typedef const Equation *ConstEquationPtr;

class ContactEquation;
typedef ContactEquation *ContactEquationPtr;
typedef const ContactEquation *ConstContactEquationPtr;

typedef std::map<std::string, size_t> EquationIndMap_t;
// keep private from most things
typedef std::map<std::string, EquationPtr> EquationPtrMap_t;
// Variable to equation
typedef std::map<std::string, std::string> VariableEqnMap_t;

#if 0
typedef std::multimap<std::string, ContactEquationPtr> ContactEquationPtrMap_t;
#endif

typedef std::vector<std::string> VariableList_t;


class PermutationEntry;
typedef std::map<size_t, PermutationEntry> PermutationMap;
namespace dsMath {
template <typename T> class RowColVal;
typedef std::vector<RowColVal<double> > RealRowColValueVec;
typedef std::pair<int, double> RHSEntry;
typedef std::vector<RHSEntry> RHSEntryVec;
}
#if 0
namespace dsMath {
template <typename T> class RowColVal;
typedef std::vector<RowColVal<double> > RealRowColValueVec;
typedef std::pair<int, double> RHSEntry;
typedef std::vector<RHSEntry> RHSEntryVec;
}
#endif

/**
   A Region knows which mesh it belongs to.  A mesh may contain a shared_ptr to
   it.  A node may contain a weak_ptr pointing back to the region which
   contains it.

   if the numberNodes_ < maxNodeIndex_, then we will recycle free node indexes
   for reuse      
*/
class Region
{
      enum {DEFAULT_NUMBER_NODES=1024};
   public:

#if 0
      typedef std::multimap<std::string, ContactEquationPtr> ContactEquationPtrMap_t;
#endif

      typedef std::vector<ConstEdgeList> NodeToConstEdgeList_t;

      typedef std::vector<ConstTriangleList> NodeToConstTriangleList_t;
      typedef std::vector<ConstTriangleList> EdgeToConstTriangleList_t;
      typedef std::vector<ConstEdgeList>     TriangleToConstEdgeList_t;

      typedef std::vector<ConstTetrahedronList> NodeToConstTetrahedronList_t;
      typedef std::vector<ConstTetrahedronList> EdgeToConstTetrahedronList_t;
      typedef std::vector<ConstEdgeDataList>    TetrahedronToConstEdgeDataList_t;
      typedef std::vector<ConstTriangleList>    TetrahedronToConstTriangleList_t;
      typedef std::vector<ConstTetrahedronList> TriangleToConstTetrahedronList_t;

      typedef std::map<std::string, TriangleEdgeModelPtr> TriangleEdgeModelList_t;
      typedef std::map<std::string, TetrahedronEdgeModelPtr> TetrahedronEdgeModelList_t;
      typedef std::map<std::string, EdgeModelPtr> EdgeModelList_t;
      typedef std::map<std::string, NodeModelPtr> NodeModelList_t;
      typedef std::map<std::string, std::set<std::string> > DependencyMap_t;

//      typedef std::map<NodePtr, ContactPtr> NodeToContactList_t;
//      typedef std::map<NodePtr, ConstContactPtr> NodeToConstContactList_t;

      Region(std::string, std::string, size_t, ConstDevicePtr);
      ~Region();
      void AddNode(const NodePtr &);
      void AddNodeList(ConstNodeList &);

      void AddEdge(const EdgePtr &);
      void AddEdgeList(ConstEdgeList &);

      void AddTriangle(const TrianglePtr &);
      void AddTriangleList(ConstTriangleList &);

      void AddTetrahedron(const TetrahedronPtr &);
      void AddTetrahedronList(ConstTetrahedronList &);


      void FinalizeMesh();

      size_t GetNumberNodes() const {
         return nodeList.size();
      }

      size_t GetNumberEdges() const {
         return edgeList.size();
      }

      size_t GetNumberTriangles() const {
         return triangleList.size();
      }

      size_t GetNumberTetrahedrons() const {
         return tetrahedronList.size();
      }

      size_t GetDimension() const {
          return dimension;
      }
      const std::string &GetName() const {
          return regionName;
      }

      const std::string &GetDeviceName() const;

      const std::string &GetMaterialName() const {
          return materialName;
      }

      void SetMaterial(const std::string &/*material_name*/);

      const ConstEdgeList &GetEdgeList() const {
        return edgeList;
      }

      const ConstNodeList &GetNodeList() const {
        return nodeList;
      }

      const ConstTriangleList &GetTriangleList() const {
        return triangleList;
      }

      const ConstTetrahedronList &GetTetrahedronList() const {
        return tetrahedronList;
      }

      const NodeToConstEdgeList_t  &GetNodeToEdgeList() const {
        return nodeToEdgeList;
      }

      const NodeToConstTriangleList_t &GetNodeToTriangleList() const {
        return nodeToTriangleList;
      }

      const EdgeToConstTriangleList_t &GetEdgeToTriangleList() const {
        return edgeToTriangleList;
      }

      const TriangleToConstEdgeList_t &GetTriangleToEdgeList() const {
        return triangleToEdgeList;
      }

      const NodeToConstTetrahedronList_t &GetNodeToTetrahedronList() const {
        return nodeToTetrahedronList;
      }

      const EdgeToConstTetrahedronList_t &GetEdgeToTetrahedronList() const {
        return edgeToTetrahedronList;
      }

      const TetrahedronToConstEdgeDataList_t &GetTetrahedronToEdgeDataList() const {
        return tetrahedronToEdgeDataList;
      }

      const TriangleToConstTetrahedronList_t &GetTriangleToTetrahedronList() const {
        return triangleToTetrahedronList;
      }

      const TetrahedronToConstTriangleList_t &GetTetrahedronToTriangleList() const {
        return tetrahedronToTriangleList;
      }


      // try using a multimap first
      void RegisterCallback(const std::string &, const std::string &);
      // model can signal dependencies, passing this
      // Note that a NodeModelPtr can signal both EdgeModels and NodeModels
      void SignalCallbacks(const std::string &);

      // unregister a model when it is destructed
      void UnregisterCallback(const std::string &);

      // note that these can be used to alias the same model with multiple names
      NodeModelPtr AddNodeModel(NodeModel *);
      EdgeModelPtr AddEdgeModel(EdgeModel *);
      TriangleEdgeModelPtr AddTriangleEdgeModel(TriangleEdgeModel *);
      TetrahedronEdgeModelPtr  AddTetrahedronEdgeModel(TetrahedronEdgeModel *);
      // given a models name, spit out a pointer to it

      ConstNodeModelPtr            GetNodeModel(const std::string &) const;
      ConstEdgeModelPtr            GetEdgeModel(const std::string &) const;
      ConstTriangleEdgeModelPtr    GetTriangleEdgeModel(const std::string &) const;
      ConstTetrahedronEdgeModelPtr GetTetrahedronEdgeModel(const std::string &) const;

      void DeleteNodeModel(const std::string &);

      void DeleteEdgeModel(const std::string &);

      void DeleteTriangleEdgeModel(const std::string &);

      void DeleteTetrahedronEdgeModel(const std::string &);

      const EdgeModelList_t &GetEdgeModelList() const {
        return edgeModels;
      }

      const NodeModelList_t &GetNodeModelList() const {
        return nodeModels;
      }

      const TriangleEdgeModelList_t &GetTriangleEdgeModelList() const {
        return triangleEdgeModels;
      }

      const TetrahedronEdgeModelList_t &GetTetrahedronEdgeModelList() const {
        return tetrahedronEdgeModels;
      }

#if 0
      void AddContactEquation(ContactEquationPtr);
      // Restrict access to device at some point
      const ContactEquationPtrMap_t &GetContactEquationList() const;
#endif

      void AddEquation(EquationPtr);
      void DeleteEquation(EquationPtr);
      size_t GetEquationIndex(const std::string &) const;
      // Is access control worth it?
      // Fix this
      EquationPtrMap_t &GetEquationPtrList();
      const EquationPtrMap_t &GetEquationPtrList() const;
      // also create Get equation names
      std::string GetEquationNameFromVariable(const std::string &) const;

      size_t GetEquationNumber(size_t /*equation index*/, ConstNodePtr) const;
      void SetBaseEquationNumber(size_t);
      size_t GetBaseEquationNumber() const;
      size_t GetNumberEquations() const;
      size_t GetMaxEquationNumber() const;

      bool operator==(const Region &) const;

      ConstDevicePtr GetDevice() const;

      VariableList_t GetVariableList() const;

    double GetAbsError() const
    {
        return absError;
    }

    double GetRelError() const
    {
        return relError;
    }

    void Update(const std::vector<double> &/*result*/);
    void ACUpdate(const std::vector<std::complex<double> > &/*result*/);
    void NoiseUpdate(const std::string &/*output*/, const std::vector<size_t> &/*permvec*/, const std::vector<std::complex<double> > &/*result*/);

    void Assemble(dsMath::RealRowColValueVec &, dsMath::RHSEntryVec &, dsMathEnum::WhatToLoad, dsMathEnum::TimeMode);

    void BackupSolutions(const std::string &);
    void RestoreSolutions(const std::string &);

    const GradientField &GetGradientField() const;

    const TriangleElementField &GetTriangleElementField() const;

    const TetrahedronElementField &GetTetrahedronElementField() const;

    size_t GetEdgeIndexOnTriangle(const Triangle &, ConstEdgePtr) const;

    size_t GetEdgeIndexOnTetrahedron(const Tetrahedron &, ConstEdgePtr) const;

    const std::vector<Vector> & GetTriangleCenters() const
    {
      return triangleCenters;
    }
    const std::vector<Vector> & GetTetrahedronCenters() const
    {
      return tetrahedronCenters;
    }

    std::string GetNodeVolumeModel() const;
    std::string GetEdgeCoupleModel() const;
    std::string GetElementEdgeCoupleModel() const;
    std::string GetElementNode0VolumeModel() const;
    std::string GetElementNode1VolumeModel() const;


    //// const in the sense we are not changing the region
    //// however the cache is changeable
    ModelExprDataCachePtr GetModelExprDataCache();
    void SetModelExprDataCache(ModelExprDataCachePtr);

   private:
      Region();
      Region (const Region &);
      Region &operator= (const Region &);

      void SetNodeIndexes();
      void SetEdgeIndexes();
      void SetTriangleIndexes();
      void SetTetrahedronIndexes();

      void CreateNodeToEdgeList();

      void CreateNodeToTriangleList();
      void CreateEdgeToTriangleList();
      void CreateTriangleToEdgeList();

      void CreateNodeToTetrahedronList();
      void CreateEdgeToTetrahedronList();
      void CreateTetrahedronToEdgeDataList();
      void CreateTetrahedronToTriangleList();
      void CreateTriangleToTetrahedronList();
      void SetTriangleCenters();
      void SetTetrahedronCenters();

      std::string materialName;
      std::string regionName;
      size_t dimension; //1D, 2D, or 3D mesh

      EquationIndMap_t equationIndexMap;
      EquationPtrMap_t equationPointerMap;
      VariableEqnMap_t variableEquationMap;

#if 0
      ContactEquationPtrMap_t contactEquationPtrMap;
#endif

      ConstNodeList        nodeList;
      ConstEdgeList        edgeList;
      ConstTriangleList    triangleList;
      ConstTetrahedronList tetrahedronList;

      // one for one correspondence with nodeList
      NodeToConstEdgeList_t     nodeToEdgeList; 

      NodeToConstTriangleList_t nodeToTriangleList; 
      EdgeToConstTriangleList_t edgeToTriangleList; 
      TriangleToConstEdgeList_t triangleToEdgeList; 

      NodeToConstTetrahedronList_t     nodeToTetrahedronList; 
      EdgeToConstTetrahedronList_t     edgeToTetrahedronList; 
      TetrahedronToConstEdgeDataList_t tetrahedronToEdgeDataList; 
      TetrahedronToConstTriangleList_t tetrahedronToTriangleList; 
      TriangleToConstTetrahedronList_t triangleToTetrahedronList; 

//      NodeToConstContactList_t  nodeToContactList; 

      NodeModelList_t            nodeModels;
      EdgeModelList_t            edgeModels;
      TriangleEdgeModelList_t    triangleEdgeModels;
      TetrahedronEdgeModelList_t tetrahedronEdgeModels;

      DependencyMap_t DependencyMap;

      size_t baseeqnnum; // base equation number for this region
      size_t numequations;
      bool   finalized;
      ConstDevicePtr device;
      const   std::string deviceName;
      double  relError;
      double  absError;
      mutable GradientField           *gradientField_;
      mutable TriangleElementField    *triangleElementField_;
      mutable TetrahedronElementField *tetrahedronElementField_;

      std::vector<Vector>       triangleCenters;
      std::vector<Vector>       tetrahedronCenters;
      WeakModelExprDataCachePtr modelExprDataCache;
};


#endif
