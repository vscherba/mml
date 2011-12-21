//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_REFINERY_STRICT_REFINE_TO_HPP_INCLUDED_
#define _MML_REFINERY_STRICT_REFINE_TO_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

//boost::type_traits
#include <boost/type_traits/is_convertible.hpp>

#include <mml/config.hpp>
#include <mml/refinery/custom_refine_to.hpp>
#include <mml/casting/typeid_caster.hpp>
#include <mml/casting/implicit_caster.hpp>
#include <mml/meta_predicate/dynamic_downcast_allowed.hpp>


namespace mml {

template <
    BOOST_PP_ENUM_BINARY_PARAMS(
          MML_MAX_REFINERY_SIZE
        , typename T
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
struct strict_refine_to
    : custom_refine_to<
          typeid_caster
        , dynamic_downcast_allowed
        , implicit_caster
        , boost::is_convertible
        , BOOST_PP_ENUM_PARAMS(MML_MAX_REFINERY_SIZE, T)
        >
{
};

} // namespace mml


#endif // _MML_REFINERY_STRICT_REFINE_TO_HPP_INCLUDED_
