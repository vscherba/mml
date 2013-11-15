//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_CONFIG_HPP_INCLUDED_
#define _MML_CONFIG_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/limits/vector.hpp>


#ifndef MML_MAX_ARITY
#   define MML_MAX_ARITY 5
#endif
#if MML_MAX_ARITY > BOOST_MPL_LIMIT_VECTOR_SIZE
#   undef MML_MAX_ARITY
#   define MML_MAX_ARITY BOOST_MPL_LIMIT_VECTOR_SIZE
#endif


#ifndef MML_MAX_REFINERY_SIZE
#   define MML_MAX_REFINERY_SIZE 10
#endif
#if MML_MAX_REFINERY_SIZE > BOOST_MPL_LIMIT_VECTOR_SIZE
#   undef MML_MAX_REFINERY_SIZE
#   define MML_MAX_REFINERY_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif


#ifndef MML_MAX_FUNCTION_OVERLOADS
#   define MML_MAX_FUNCTION_OVERLOADS 10
#endif


// MML_COMPRESSION_OFF - define this macro to disable tuple compression

// MML_RESULT_OF_SUPPORT_ON - define this macro to enable
// result_of protocol support by inline_overloaded_fn template


#endif // _MML_CONFIG_HPP_INCLUDED_
