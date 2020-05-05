///////////////////////////////////////////////////////////////
//  Copyright 2020 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_ADD_UNSIGNED_HPP
#define BOOST_MP_ADD_UNSIGNED_HPP
//
// Select which actual implementation header to use:
//
#ifdef __has_include
#if __has_include(<immintrin.h>)
#define BOOST_MP_HAS_IMMINTRIN_H
#include <immintrin.h>
#endif
#endif

#ifdef BOOST_MP_HAS_IMMINTRIN_H

#if defined(__AVX__) && defined(BOOST_HAS_INT128)
#include <boost/multiprecision/cpp_int/addition/add_unsigned_adxc_64.hpp>
#elif defined(__AVX__)
#include <boost/multiprecision/cpp_int/addition/add_unsigned_adxc_32.hpp>
#elif defined(BOOST_HAS_INT128)
#include <boost/multiprecision/cpp_int/addition/add_unsigned_addc_64.hpp>
#else
#include <boost/multiprecision/cpp_int/addition/add_unsigned_addc_32.hpp>
#endif

#else
#include <boost/multiprecision/cpp_int/addition/add_unsigned_generic.hpp>
#endif

#endif

