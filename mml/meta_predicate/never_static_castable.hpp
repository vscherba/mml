//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_META_PREDICATE_NEVER_STATIC_CASTABLE_HPP_INCLUDED_
#define _MML_META_PREDICATE_NEVER_STATIC_CASTABLE_HPP_INCLUDED_


// boost::type_traits
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_same.hpp>


namespace mml {

template <typename From, typename To>
struct never_static_castable
    : boost::is_same<
          typename boost::remove_cv<From>::type
        , typename boost::remove_cv<To>::type
        >
{
};

} // namespace mml


#endif // _MML_META_PREDICATE_NEVER_STATIC_CASTABLE_HPP_INCLUDED_
