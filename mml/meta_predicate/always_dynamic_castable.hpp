//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_META_PREDICATE_ALWAYS_DYNAMIC_CASTABLE_HPP_INCLUDED_
#define _MML_META_PREDICATE_ALWAYS_DYNAMIC_CASTABLE_HPP_INCLUDED_


// boost::type_traits
#include <boost/type_traits/integral_constant.hpp>


namespace mml {

template <typename From, typename To>
struct always_dynamic_castable
    : boost::true_type
{
};

} // namespace mml


#endif // _MML_META_PREDICATE_ALWAYS_DYNAMIC_CASTABLE_HPP_INCLUDED_
