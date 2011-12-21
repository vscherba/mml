//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FACADE_REF_MULTIMETHOD_HPP_INCLUDED_
#define _MML_FACADE_REF_MULTIMETHOD_HPP_INCLUDED_


// boost::type_traits
#include <boost/type_traits/is_reference.hpp>

#include <mml/adapter/basic_ref_dispatcher.hpp>


#define _MML_FACADE_NAME ref_multimethod
#define _MML_FACADE_BASE_CLASS_NAME ref_dispatcher_base
#define _MML_FACADE_PARAM_FILTER boost::is_reference

#include <mml/facade/detail/multimethod_template.hpp>

#undef _MML_FACADE_NAME
#undef _MML_FACADE_BASE_CLASS_NAME
#undef _MML_FACADE_PARAM_FILTER


#endif // _MML_FACADE_REF_MULTIMETHOD_HPP_INCLUDED_
