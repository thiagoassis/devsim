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

#include "TriangleEdgeScalarData.hh"
#include "TriangleEdgeModel.hh"
#include "ScalarData.cc"

//// Manual Template Instantiation
template class ScalarData<TriangleEdgeModel>;

template class
ScalarData<TriangleEdgeModel>& ScalarData<TriangleEdgeModel>::op_equal<ScalarDataHelper::times_equal>(const double &, const ScalarDataHelper::times_equal &);

template class
ScalarData<TriangleEdgeModel>& ScalarData<TriangleEdgeModel>::op_equal<ScalarDataHelper::times_equal>(const ScalarData<TriangleEdgeModel> &, const ScalarDataHelper::times_equal &);

template class
ScalarData<TriangleEdgeModel>& ScalarData<TriangleEdgeModel>::op_equal<ScalarDataHelper::plus_equal>(const double &, const ScalarDataHelper::plus_equal &);

template class
ScalarData<TriangleEdgeModel>& ScalarData<TriangleEdgeModel>::op_equal<ScalarDataHelper::plus_equal>(const ScalarData<TriangleEdgeModel> &, const ScalarDataHelper::plus_equal &);

