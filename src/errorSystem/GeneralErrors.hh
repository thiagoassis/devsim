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

#ifndef DS_GENERAL_ERRORS_HH
#define DS_GENERAL_ERRORS_HH
namespace dsErrors {
namespace ModelInfo {
enum ModelType {
  NODE = 0,
  EDGE,
  ELEMENTEDGE,
  INTERFACE
};

extern const char *ModelTypeStrings[]; 
}

}
#endif
