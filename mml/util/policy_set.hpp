//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_UTIL_POLICY_SET_HPP_INCLUDED_
#define _MML_UTIL_POLICY_SET_HPP_INCLUDED_


// boost::type_traits
#include <boost/type_traits/is_convertible.hpp>

#include <mml/casting/dynamic_caster.hpp>
#include <mml/casting/implicit_caster.hpp>
#include <mml/meta_predicate/dynamic_downcast_allowed.hpp>


namespace mml {

template <
      template<typename, typename>
        class DynCaster = dynamic_caster
    , template<typename, typename>
        class DynCastablePred = dynamic_downcast_allowed
    , template<typename, typename>
        class StatCaster = implicit_caster
    , template<typename, typename>
        class StatCastablePred = boost::is_convertible
    >
struct policy_set
{
    template <typename From, typename To>
    struct dynamic_caster
    {
        typedef DynCaster<From, To> type;
    };

    template <typename From, typename To>
    struct is_dynamic_castable
    {
        typedef DynCastablePred<From, To> type;
    };

    template <typename From, typename To>
    struct static_caster
    {
        typedef StatCaster<From, To> type;
    };

    template <typename From, typename To>
    struct is_static_castable
    {
        typedef StatCastablePred<From, To> type;
    };
};

} // namespace mml


#endif // _MML_UTIL_POLICY_SET_HPP_INCLUDED_
