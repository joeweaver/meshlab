/****************************************************************************
* VCGLib                                                            o o     *
* Visual and Computer Graphics Library                            o     o   *
*                                                                _   O  _   *
* Copyright(C) 2009                                                \/)\/    *
* Pablo Castellano García-Saavedra                                /\/|      *
*                                                                    |      *
*                                                                    \      *
* All rights reserved.                                                      *
*                                                                           *
* This program is free software; you can redistribute it and/or modify      *
* it under the terms of the GNU General Public License as published by      *
* the Free Software Foundation; either version 2 of the License, or         *
* (at your option) any later version.                                       *
*                                                                           *
* This program is distributed in the hope that it will be useful,           *
* but WITHOUT ANY WARRANTY; without even the implied warranty of            *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
* GNU General Public License (http://www.gnu.org/licenses/gpl.txt)          *
* for more details.                                                         *
*                                                                           *
****************************************************************************/

#ifndef __VCGLIB_ARCHIMEDEAN_H
#define __VCGLIB_ARCHIMEDEAN_H

#include <vcg/math/base.h>
#include <vcg/complex/trimesh/allocate.h>
#include <vcg/complex/trimesh/refine.h>
#include <vcg/complex/trimesh/update/flag.h>

namespace vcg {
namespace tri {

template <class MeshType>
void Truncated_Tetrahedron(MeshType &in)
{
    //F = 8, V = 12
    // 4 triangles and 4 hexagons
    /* (+3,+1,+1), (+1,+3,+1), (+1,+1,+3)
    (−3,−1,+1), (−1,−3,+1), (−1,−1,+3)
    (−3,+1,−1), (−1,+3,−1), (−1,+1,−3)
    (+3,−1,−1), (+1,−3,−1), (+1,−1,−3)
    */

 typedef typename MeshType::CoordType CoordType;
 typedef typename MeshType::VertexPointer  VertexPointer;
 typedef typename MeshType::VertexIterator VertexIterator;
 typedef typename MeshType::FaceIterator   FaceIterator;

 in.Clear();
 Allocator<MeshType>::AddVertices(in, 12);
 Allocator<MeshType>::AddFaces(in, 4*4+4); //20 triangles

 VertexPointer ivp[12];
 VertexIterator vi;

 int vertexes[36] = {
     3, 1, 1,       1, 3, 1,        1, 1, 3,        -3,-1, 1,
    -1,-3, 1,      -1,-1, 3,       -3, 1,-1,        -1, 3,-1,
    -1, 1,-3,       3,-1,-1,        1,-3,-1,         1,-1,-3 };

 int triangles[12] = {
     3, 4, 5,       0, 1, 2,        8, 6, 7,         9,10,11 };

 int hexagons[24] = {
     3, 5, 2, 1, 7, 6,      9, 0, 2, 5, 4,10,
     8,11,10, 4, 3, 6,      0, 9,11, 8, 7, 1 };

 int i;
 for(i=0, vi=in.vert.begin(); vi!=in.vert.end(); i++, vi++) {
    ivp[i]=&*vi; (*vi).P()=CoordType  ( vertexes[3*i], vertexes[3*i+1], vertexes[3*i+2]);
 }

 FaceIterator fi=in.face.begin();

 for(int i=0; i<4; i++) {
     (*fi).V(0)=ivp[triangles[i*3]];  (*fi).V(1)=ivp[triangles[i*3+1]];  (*fi).V(2)=ivp[triangles[i*3+2]]; ++fi;
 }

 for(int i=0; i<4; i++) {
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+1]];  (*fi).V(2)=ivp[hexagons[i*6+2]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+2]];  (*fi).V(2)=ivp[hexagons[i*6+3]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+3]];  (*fi).V(2)=ivp[hexagons[i*6+4]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+4]];  (*fi).V(2)=ivp[hexagons[i*6+5]]; ++fi;
 }

  if (in.HasPerFaceFlags()) {
    FaceIterator fi=in.face.begin();
    for (int k=0; k<20; k++) {
      (*fi).SetF(1); fi++;
    }
  }

}

template <class MeshType>
void Cuboctahedron(MeshType &in)
{
    //F = 14, V = 12
    //8 triangles and 6 squares
    /*
        (±1,±1,0)
        (±1,0,±1)
        (0,±1,±1)
    */

 typedef typename MeshType::CoordType CoordType;
 typedef typename MeshType::VertexPointer  VertexPointer;
 typedef typename MeshType::VertexIterator VertexIterator;
 typedef typename MeshType::FaceIterator   FaceIterator;

 in.Clear();
 Allocator<MeshType>::AddVertices(in, 12);
 Allocator<MeshType>::AddFaces(in, 6*2+8); //20 triangles

 VertexPointer ivp[12];
 VertexIterator vi;

 int vertexes[36] = {
     1, 1, 0,       1,-1, 0,       -1,-1, 0,        -1, 1, 0,
     1, 0, 1,      -1, 0, 1,       -1, 0,-1,         1, 0,-1,
     0, 1, 1,       0, 1,-1,        0,-1, 1,         0,-1,-1 };

 int triangles[24] = {
     5, 8, 3,       4, 0, 8,        7, 9, 0,        1,11, 7,
    10, 1, 4,       5, 2,10,        9, 6, 3,        6,11, 2 };

 int squares[24] = {
    3, 6, 2, 5,     7, 0, 4, 1,     0, 9, 3, 8,     11, 1,10, 2,
    9, 7,11, 6,     4, 8, 5,10 };

 int i;
 for(i=0, vi=in.vert.begin(); vi!=in.vert.end(); i++, vi++) {
    ivp[i]=&*vi; (*vi).P()=CoordType  ( vertexes[3*i], vertexes[3*i+1], vertexes[3*i+2]);
 }

 FaceIterator fi=in.face.begin();

 for(int i=0; i<8; i++) {
     (*fi).V(0)=ivp[triangles[i*3]];  (*fi).V(1)=ivp[triangles[i*3+1]];  (*fi).V(2)=ivp[triangles[i*3+2]]; ++fi;
 }

 for(int i=0; i<6; i++) {
     (*fi).V(0)=ivp[squares[i*4]];  (*fi).V(1)=ivp[squares[i*4+1]];  (*fi).V(2)=ivp[squares[i*4+2]]; ++fi;
     (*fi).V(0)=ivp[squares[i*4]];  (*fi).V(1)=ivp[squares[i*4+2]];  (*fi).V(2)=ivp[squares[i*4+3]]; ++fi;
 }

  if (in.HasPerFaceFlags()) {
    FaceIterator fi=in.face.begin();
    for (int k=0; k<20; k++) {
      (*fi).SetF(1); fi++;
    }
  }

}


template <class MeshType>
void Truncated_Cube(MeshType &in)
{
    // F = 14, V = 24
    // 8 triangles and 6 octagons
    /*  Perm(±ξ, ±1, ±1)
        where ξ = √2 - 1
    */

 typedef typename MeshType::CoordType CoordType;
 typedef typename MeshType::VertexPointer  VertexPointer;
 typedef typename MeshType::VertexIterator VertexIterator;
 typedef typename MeshType::FaceIterator   FaceIterator;

 in.Clear();
 Allocator<MeshType>::AddVertices(in, 24);
 Allocator<MeshType>::AddFaces(in, 6*6+8); //44 faces

 VertexPointer ivp[24];
 VertexIterator vi=in.vert.begin();

 double E = sqrt(2)-1;
 double vertexes[72] = {
     E, 1, 1,     E, 1,-1,      E,-1, 1,       E,-1,-1,
    -E, 1, 1,    -E, 1,-1,     -E,-1, 1,      -E,-1,-1,
     1, E, 1,     1, E,-1,      1,-E, 1,       1,-E,-1,
    -1, E, 1,    -1, E,-1,     -1,-E, 1,      -1,-E,-1,
     1, 1, E,     1, 1,-E,      1,-1, E,       1,-1,-E,
    -1, 1, E,    -1, 1,-E,     -1,-1, E,      -1,-1,-E };

 int i;
 for(i=0, vi=in.vert.begin(); vi!=in.vert.end(); i++, vi++) {
    ivp[i]=&*vi; (*vi).P()=CoordType  ( vertexes[3*i], vertexes[3*i+1], vertexes[3*i+2]);
 }

 int triangles[24] = {
    18,10, 2,   6,14,22,    0, 8,16,    13,21, 5,
     9, 1,17,  19, 3,11,   23,15, 7,    12, 4,20 };

 int octagons[48] = {
    12,20,21,13,15,23,22,14,        22,23, 7, 3,19,18, 2, 6,
    10, 8, 0, 4,12,14, 6, 2,        19,11, 9,17,16, 8,10,18,
    11, 3, 7,15,13, 5, 1, 9,        17, 1, 5,21,20, 4, 0,16 };

 FaceIterator fi=in.face.begin();

 for(int i=0; i<8; i++) {
     (*fi).V(0)=ivp[triangles[i*3]];  (*fi).V(1)=ivp[triangles[i*3+1]];  (*fi).V(2)=ivp[triangles[i*3+2]]; ++fi;
 }

 for(int i=0; i<6; i++) {
     (*fi).V(0)=ivp[octagons[i*8]];  (*fi).V(1)=ivp[octagons[i*8+1]];  (*fi).V(2)=ivp[octagons[i*8+2]]; ++fi;
     (*fi).V(0)=ivp[octagons[i*8]];  (*fi).V(1)=ivp[octagons[i*8+2]];  (*fi).V(2)=ivp[octagons[i*8+3]]; ++fi;
     (*fi).V(0)=ivp[octagons[i*8]];  (*fi).V(1)=ivp[octagons[i*8+3]];  (*fi).V(2)=ivp[octagons[i*8+4]]; ++fi;
     (*fi).V(0)=ivp[octagons[i*8]];  (*fi).V(1)=ivp[octagons[i*8+4]];  (*fi).V(2)=ivp[octagons[i*8+5]]; ++fi;
     (*fi).V(0)=ivp[octagons[i*8]];  (*fi).V(1)=ivp[octagons[i*8+5]];  (*fi).V(2)=ivp[octagons[i*8+6]]; ++fi;
     (*fi).V(0)=ivp[octagons[i*8]];  (*fi).V(1)=ivp[octagons[i*8+6]];  (*fi).V(2)=ivp[octagons[i*8+7]]; ++fi;
 }

  if (in.HasPerFaceFlags()) {
    FaceIterator fi=in.face.begin();
    for (int k=0; k<44; k++) {
      (*fi).SetF(1); fi++;
    }
  }

}

template <class MeshType>
void Truncated_Octahedron(MeshType &in)
{
    // 6 squares and 8 hexagons
    /* F = 14, V = 24
       Perm(0, ±1, ±2)
    */

 typedef typename MeshType::CoordType CoordType;
 typedef typename MeshType::VertexPointer  VertexPointer;
 typedef typename MeshType::VertexIterator VertexIterator;
 typedef typename MeshType::FaceIterator   FaceIterator;

 in.Clear();
 Allocator<MeshType>::AddVertices(in, 24);
 Allocator<MeshType>::AddFaces(in, 6*2+8*4); // 44 faces

 VertexPointer ivp[24];
 VertexIterator vi;

 int vertexes[72] = {
     0, 1, 2,     0, 1,-2,      0,-1, 2,       0,-1,-2,
     0, 2, 1,     0, 2,-1,      0,-2, 1,       0,-2,-1,
     1, 0, 2,     1, 0,-2,      1, 2, 0,       1,-2, 0,
    -1, 0, 2,    -1, 0,-2,     -1, 2, 0,      -1,-2, 0,
     2, 0, 1,     2, 0,-1,     -2, 0, 1,      -2, 0,-1,
     2, 1, 0,     2,-1, 0,     -2, 1, 0,      -2,-1, 0 };

 int i;
 for(i=0, vi=in.vert.begin(); vi!=in.vert.end(); i++, vi++) {
    ivp[i]=&*vi; (*vi).P()=CoordType  ( vertexes[3*i], vertexes[3*i+1], vertexes[3*i+2]);
 }

 int squares[24] = {
    10, 5,14, 4,        6,15, 7,11,     21,17,20,16,
    18,22,19,23,        8, 0,12, 2,      3,13, 1, 9 };

 int hexagons[48] = {
    20,10, 4, 0, 8,16,      12,18,23,15, 6, 2,      23,19,13, 3, 7,15,
     4,14,22,18,12, 0,      11, 7, 3, 9,17,21,      17, 9, 1, 5,10,20,
    21,16, 8, 2, 6,11,      14, 5, 1,13,19,22 };

 FaceIterator fi=in.face.begin();

 for(int i=0; i<6; i++) {
     (*fi).V(0)=ivp[squares[i*4]];  (*fi).V(1)=ivp[squares[i*4+1]];  (*fi).V(2)=ivp[squares[i*4+2]]; ++fi;
     (*fi).V(0)=ivp[squares[i*4]];  (*fi).V(1)=ivp[squares[i*4+2]];  (*fi).V(2)=ivp[squares[i*4+3]]; ++fi;
 }

 for(int i=0; i<8; i++) {
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+1]];  (*fi).V(2)=ivp[hexagons[i*6+2]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+2]];  (*fi).V(2)=ivp[hexagons[i*6+3]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+3]];  (*fi).V(2)=ivp[hexagons[i*6+4]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+4]];  (*fi).V(2)=ivp[hexagons[i*6+5]]; ++fi;
 }

  if (in.HasPerFaceFlags()) {
    FaceIterator fi=in.face.begin();
    for (int k=0; k<44; k++) {
      (*fi).SetF(1); fi++;
    }
  }

}

template <class MeshType>
void Rhombicuboctahedron(MeshType &in)
{
    // 8 triangles and 18 squares
    /* F = 26, V = 24
       Perm(±1, ±1, ±(1+√2))
    */

 typedef typename MeshType::CoordType CoordType;
 typedef typename MeshType::VertexPointer  VertexPointer;
 typedef typename MeshType::VertexIterator VertexIterator;
 typedef typename MeshType::FaceIterator   FaceIterator;

 double E = 1 + sqrt(2);

 in.Clear();
 Allocator<MeshType>::AddVertices(in, 24);
 Allocator<MeshType>::AddFaces(in, 18*2+8); //44 faces

 VertexPointer ivp[24];
 VertexIterator vi;

 double vertexes[72] = {
     1, 1, E,     1, 1,-E,      1,-1, E,       1,-1,-E,
     1, E, 1,     1, E,-1,      1,-E, 1,       1,-E,-1,
    -1, 1, E,    -1, 1,-E,     -1,-1, E,      -1,-1,-E,
    -1, E, 1,    -1, E,-1,     -1,-E, 1,      -1,-E,-1,
     E, 1, 1,     E, 1,-1,      E,-1, 1,       E,-1,-1,
    -E, 1, 1,    -E, 1,-1,     -E,-1, 1,      -E,-1,-1 };

 int i;
 for(i=0, vi=in.vert.begin(); vi!=in.vert.end(); i++, vi++) {
    ivp[i]=&*vi; (*vi).P()=CoordType  ( vertexes[3*i], vertexes[3*i+1], vertexes[3*i+2]);
 }

 FaceIterator fi=in.face.begin();
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];  ++fi;
 (*fi).V(0)=ivp[2];  (*fi).V(1)=ivp[11];  (*fi).V(2)=ivp[1];

  if (in.HasPerFaceFlags()) {
    FaceIterator fi=in.face.begin();
    for (int k=0; k<44; k++) {
      (*fi).SetF(1); fi++;
    }
  }
}

template <class MeshType>
void Truncated_cuboctahedron(MeshType &in)
{
    // 12 squares, 8 hexagons and 6 octagons
    /* F = 26, V = 48
       Perm(±1, ±(1+√2), ±(1+√8))
    */
}


template <class MeshType>
void Snub_Cube(MeshType &in)
{
    // 32 triangles and 6 squares
    /* F = 38, V = 24
       Perm(±1, ±ξ, ±1/ξ)
       where ξ3+ξ2+ξ=1
    */

}


template <class MeshType>
void Icosidodecahedron(MeshType &in)
{
    // 20 triangles and 12 pentagons
    /* F = 32, V = 30
       (0,0,±τ), (±1/2, ±τ/2, ±(1+τ)/2)
       where τ is the golden ratio, (1+√5)/2
    */

}


template <class MeshType>
void Truncated_Dodecahedron(MeshType &in)
{
    // 20 triangles and 12 decagons
    /* F = 32, V = 60
        (0, ±1/τ, ±(2+τ))
        (±(2+τ), 0, ±1/τ)
        (±1/τ, ±(2+τ), 0)
        (±1/τ, ±τ, ±2τ)
        (±2τ, ±1/τ, ±τ)
        (±τ, ±2τ, ±1/τ)
        (±τ, ±2, ±τ2)
        (±τ2, ±τ, ±2)
        (±2, ±τ2, ±τ)
        where τ = (1+√5)/2 is the golden ratio
    */

}

// (soccer ball, for friends)
template <class MeshType>
void Truncated_Icosahedron(MeshType &in)
{
    // 12 pentagons and 20 hexagons
    /* F = 32, V = 60
        (0,±1,±3φ), (±1,±3φ,0), (±3φ,0,±1)
        (±2,±(1+2φ),±φ), (±(1+2φ),±φ,±2), (±φ,±2,±(1+2φ))
        (±1,±(2+φ),±2φ), (±(2+φ),±2φ,±1), (±2φ,±1,±(2+φ))
        where φ = (1+√5)/2
    */

 typedef typename MeshType::CoordType CoordType;
 typedef typename MeshType::VertexPointer  VertexPointer;
 typedef typename MeshType::VertexIterator VertexIterator;
 typedef typename MeshType::FaceIterator   FaceIterator;

 //Why isn't golden ratio defined in math.h ?!?!
 double G = (1 + sqrt(5))/2;
 //double G3 = 3*G; double G2 = 2*G; double A = 1+G2;

 in.Clear();
 Allocator<MeshType>::AddVertices(in, 60);
 Allocator<MeshType>::AddFaces(in, 12*3+20*4); //116 faces!!!

 int pentagons[5*12]= {
     16,  6, 17, 49, 48,        0, 28, 36, 40, 32,
     39, 43, 35,  3, 31,       55, 53, 21,  9, 23,
     15, 47, 46, 14,  5,       29,  1, 33, 41, 37,
     24, 10, 26, 58, 56,       22,  8, 20, 52, 54,
     42, 38, 30,  2, 34,       19,  7, 18, 50, 51,
     59, 27, 11, 25, 57,       44, 45, 13,  4, 12 };

 int hexagons[20*6]= {
      3,  1, 29, 53, 55, 31,        56, 32, 40, 16, 48, 24,
     24, 48, 49, 25, 11, 10,        2,  0, 32, 56, 58, 34,
     18, 42, 34, 58, 26, 50,        43, 19, 51, 27, 59, 35,
     49, 17, 41, 33, 57, 25,        21, 53, 29, 37, 13, 45,
     52, 20, 44, 12, 36, 28,        35, 59, 57, 33,  1,  3,
     15, 39, 31, 55, 23, 47,        46, 47, 23,  9,  8, 22,
     38, 14, 46, 22, 54, 30,         4, 13, 37, 41, 17,  6,
     12,  4,  6, 16, 40, 36,        54, 52, 28,  0,  2, 30,
      8,  9, 21, 45, 44, 20,         7,  5, 14, 38, 42, 18,
     43, 39, 15,  5,  7, 19,        10, 11, 27, 51, 50, 26 };

 double vertexes[180] = {
     0, 1, 3*G,         0, 1,-3*G,          0,-1, 3*G,          0,-1,-3*G,
     1, 3*G, 0,         1,-3*G, 0,         -1, 3*G, 0,         -1,-3*G, 0,
     3*G, 0, 1,         3*G, 0,-1,         -3*G, 0, 1,         -3*G, 0,-1,
     2, 1+2*G, G,       2, 1+2*G,-G,        2,-1-2*G, G,        2,-1-2*G,-G,
    -2, 1+2*G, G,      -2, 1+2*G,-G,       -2,-1-2*G, G,       -2,-1-2*G,-G,
     1+2*G, G, 2,       1+2*G, G,-2,        1+2*G,-G, 2,       1+2*G,-G,-2,
    -1-2*G, G, 2,      -1-2*G, G,-2,       -1-2*G,-G, 2,      -1-2*G,-G,-2,
     G, 2, 1+2*G,       G, 2,-1-2*G,        G,-2, 1+2*G,       G,-2,-1-2*G,
    -G, 2, 1+2*G,      -G, 2,-1-2*G,       -G,-2, 1+2*G,      -G,-2,-1-2*G,
     1, 2+G, 2*G,       1, 2+G,-2*G,        1,-2-G, 2*G,       1,-2-G,-2*G,
    -1, 2+G, 2*G,      -1, 2+G,-2*G,       -1,-2-G, 2*G,      -1,-2-G,-2*G,
     2+G, 2*G, 1,       2+G, 2*G,-1,        2+G,-2*G, 1,       2+G,-2*G,-1,
    -2-G, 2*G, 1,      -2-G, 2*G,-1,       -2-G,-2*G, 1,      -2-G,-2*G,-1,
     2*G, 1, 2+G,       2*G, 1,-2-G,        2*G,-1, 2+G,       2*G,-1,-2-G,
    -2*G, 1, 2+G,      -2*G, 1,-2-G,       -2*G,-1, 2+G,      -2*G,-1,-2-G };

 VertexPointer ivp[60];
 VertexIterator vi;
 int i;

 for(i=0, vi=in.vert.begin(); vi!=in.vert.end(); i++, vi++) {
    ivp[i]=&*vi; (*vi).P()=CoordType  ( vertexes[3*i], vertexes[3*i+1], vertexes[3*i+2]);
 }

 FaceIterator fi=in.face.begin();

 for(int i=0; i<12; i++) {
     (*fi).V(0)=ivp[pentagons[i*5]];  (*fi).V(1)=ivp[pentagons[i*5+1]];  (*fi).V(2)=ivp[pentagons[i*5+2]]; ++fi;
     (*fi).V(0)=ivp[pentagons[i*5]];  (*fi).V(1)=ivp[pentagons[i*5+2]];  (*fi).V(2)=ivp[pentagons[i*5+3]]; ++fi;
     (*fi).V(0)=ivp[pentagons[i*5]];  (*fi).V(1)=ivp[pentagons[i*5+3]];  (*fi).V(2)=ivp[pentagons[i*5+4]]; ++fi;
 }

 for(int i=0; i<20; i++) {
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+1]];  (*fi).V(2)=ivp[hexagons[i*6+2]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+2]];  (*fi).V(2)=ivp[hexagons[i*6+3]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+3]];  (*fi).V(2)=ivp[hexagons[i*6+4]]; ++fi;
     (*fi).V(0)=ivp[hexagons[i*6]];  (*fi).V(1)=ivp[hexagons[i*6+4]];  (*fi).V(2)=ivp[hexagons[i*6+5]]; ++fi;
 }

  if (in.HasPerFaceFlags()) {
    FaceIterator fi=in.face.begin();
    for (int k=0; k<116; k++) {
      (*fi).SetF(1); fi++;
    }
  }

}

template <class MeshType>
void Rhombicosidodecahedron(MeshType &in)
{
    /*
    */

}

template <class MeshType>
void Truncated_Icosidodecahedron(MeshType &in)
{
    /*
    */

}

template <class MeshType>
void Snub_Dodecahedron(MeshType &in)
{
    /*
    */

}

} // End Namespace TriMesh
} // End Namespace vcg

#endif // __VCGLIB_ARCHIMEDEAN_H
