//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FACADE_MULTIMETHOD_HPP_INCLUDED_
#define _MML_FACADE_MULTIMETHOD_HPP_INCLUDED_


#include <mml/basic_dispatcher.hpp>
#include <mml/pointer_traits/pointer_traits.hpp>


#define _MML_FACADE_NAME multimethod
#define _MML_FACADE_BASE_CLASS_NAME dispatcher_base
#define _MML_FACADE_PARAM_FILTER pointer_traits_specified

#include <mml/facade/detail/multimethod_template.hpp>

#undef _MML_FACADE_NAME
#undef _MML_FACADE_BASE_CLASS_NAME
#undef _MML_FACADE_PARAM_FILTER


#endif // _MML_FACADE_MULTIMETHOD_HPP_INCLUDED_
