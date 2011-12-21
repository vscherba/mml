//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_UTIL_DISPATCHED_TO_REFINERIES_HPP_INCLUDED_
#define _MML_UTIL_DISPATCHED_TO_REFINERIES_HPP_INCLUDED_


// boost::type_traits
#include <boost/type_traits/remove_reference.hpp>

#include <mml/util/functional_types_to_refineries.hpp>


namespace mml {

template <
      typename OF
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
    , template<typename>
        class Filter = pointer_traits_specified
    >
struct dispatched_to_refineries
    : functional_types_to_refineries<
          typename boost::remove_reference<OF>::type::functional_types
        , DynCaster
        , DynCastablePred
        , StatCaster
        , StatCastablePred
        , OrderingPred
        , Filter
        >
{
};

} // namespace mml


#endif // _MML_UTIL_DISPATCHED_TO_REFINERIES_HPP_INCLUDED_
