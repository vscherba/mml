//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_UTIL_SIGNATURES_TO_REFINERIES_HPP_INCLUDED_
#define _MML_UTIL_SIGNATURES_TO_REFINERIES_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/transform.hpp>
#include <boost/mpl/inherit.hpp>

// boost::type_traits
#include <boost/type_traits/is_convertible.hpp>

// boost::function_types
#include <boost/function_types/parameter_types.hpp>

#include <mml/util/policy_set.hpp>
#include <mml/detail/zip_parameter_types.hpp>
#include <mml/pointer_traits/pointer_traits.hpp>
#include <mml/casting/dynamic_caster.hpp>
#include <mml/casting/implicit_caster.hpp>
#include <mml/meta_predicate/dynamic_downcast_allowed.hpp>
#include <mml/meta_predicate/most_derived.hpp>


namespace mml {

template <
      typename Signatures
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
struct signatures_to_refineries
    : boost::mpl::transform<
          typename detail::zip_parameter_types<
              typename boost::mpl::transform<
                  Signatures
                , boost::function_types::parameter_types<boost::mpl::_>
                >::type
            , OrderingPred
            , Filter
            >::type
        , boost::mpl::inherit2<
              boost::mpl::_
            , policy_set<
                  DynCaster
                , DynCastablePred
                , StatCaster
                , StatCastablePred
                >
            >
        >::type
{
    typedef signatures_to_refineries type;
};

} // namespace mml


#endif // _MML_UTIL_SIGNATURES_TO_REFINERIES_HPP_INCLUDED_
