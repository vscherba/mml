//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FACADE_DETAIL_WITH_POLICIES_HPP_INCLUDED_
#define _MML_FACADE_DETAIL_WITH_POLICIES_HPP_INCLUDED_


// boost::type_traits
#include <boost/type_traits/is_convertible.hpp>

#include <mml/casting/dynamic_caster.hpp>
#include <mml/casting/implicit_caster.hpp>
#include <mml/meta_predicate/dynamic_downcast_allowed.hpp>
#include <mml/meta_predicate/most_derived.hpp>


namespace mml {

template <
      typename R
    , template<typename, typename>
        class DynCaster = dynamic_caster
    , template<typename, typename>
        class DynCastablePred = dynamic_downcast_allowed
    , template<typename, typename>
        class StatCaster = implicit_caster
    , template<typename, typename>
        class StatCastablePred = boost::is_convertible
    , template<typename, typename>
        class OrderingPred = most_derived
>
struct with_policies
{
};

} // namespace mml


#endif // _MML_FACADE_DETAIL_WITH_POLICIES_HPP_INCLUDED_
