//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_META_PREDICATE_MOST_DERIVED_HPP_INCLUDED_
#define _MML_META_PREDICATE_MOST_DERIVED_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/if.hpp>

// boost::type_traits
#include <boost/type_traits/integral_constant.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/is_same.hpp>


namespace mml {

template <typename D, typename B>
struct most_derived
    : boost::mpl::if_<
          boost::is_same<typename boost::remove_cv<B>::type, void>
        , boost::true_type
        , boost::is_base_and_derived<B, D>
        >::type
{
};

} // namespace mml


#endif // _MML_META_PREDICATE_MOST_DERIVED_HPP_INCLUDED_
