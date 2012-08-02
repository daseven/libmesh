// $Id: mesh_common.h,v 1.9 2003-02-24 14:35:49 benkirk Exp $

// The Next Great Finite Element Library.
// Copyright (C) 2002  Benjamin S. Kirk, John W. Peterson
  
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
  
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
  
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef __mesh_common_h__
#define __mesh_common_h__


// C++ includes everyone should know about
#include <iostream>
#include <complex>
#include <assert.h>
#include <stdlib.h>

// The library configuration options
#include "mesh_config.h"
#include "libmesh_base.h"



// Undefine any existing macros
#ifdef Real
#  undef Real
#endif

#ifdef REAL
#  undef REAL
#endif

#ifdef Complex
#  undef Complex
#endif

#ifdef COMPLEX
#  undef COMPLEX
#endif

// Check to see if TOLERANCE has been defined by another
// package, if so we might want to change the name...
#ifdef TOLERANCE
   DIE A HORRIBLE DEATH HERE...
#  undef TOLERANCE
#endif


   
// Define the type to use for real numbers
#ifndef SINGLE_PRECISION
  typedef double Real;
  typedef double REAL;
#else
  typedef float Real;
  typedef float REAL;
#endif

// Define the type to use for complex numbers
// Always use std::complex<double>, as required by Petsc
typedef std::complex<double> Complex;
typedef std::complex<double> COMPLEX;


// Define the value type for unknowns in simulations.
// This is either Real or Complex, depending on how
// the library was configures
#if   defined (USE_REAL_NUMBERS)
  typedef Real Number;
#elif defined (USE_COMPLEX_NUMBERS)
  typedef Complex Number;
#else
  DIE A HORRIBLE DEATH HERE...
#endif



// These are useful macros that behave lilke functions in the code.
// If you want to make sure you are accessing a section of code just
// stick a here(); in it, for example
#undef here
#define here()     { std::cout << "[" << libMeshBase::processor_id() << "] " << __FILE__ << ", line " << __LINE__ << ", compiled on " << __DATE__ << " at " << __TIME__ << std::endl; }

#undef error
#define error()    { std::cerr << "[" << libMeshBase::processor_id() << "] " << __FILE__ << ", line " << __LINE__ << ", compiled on " << __DATE__ << " at " << __TIME__ << std::endl; abort(); }

#undef untested
#define untested() { std::cout << "*** Using untested code: " << __FILE__ << ", line " << __LINE__ << ", compiled on " << __DATE__ << " at " << __TIME__ << " ***" << std::endl; }


// 3D spatial dimension unless otherwise specified
#ifndef DIM
#  define DIM 3
#endif

// Define a tolerance.  This is what should be considered "good enough"
// when doing floating point comparisons.  For example, v == 0 is
// changed to fabs(v) < TOLERANCE.
#define TOLERANCE 1.e-6



#endif // #define __mesh_common_h__