//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_REFINERY_CUSTOM_REFINE_TO_HPP_INCLUDED_
#define _MML_REFINERY_CUSTOM_REFINE_TO_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

// boost::mpl
#include <boost/mpl/vector.hpp>

#include <mml/config.hpp>
#include <mml/util/policy_set.hpp>


namespace mml {

template <
      template<typename, typename> class DynCaster
    , template<typename, typename> class DynCastablePred
    , template<typename, typename> class StatCaster
    , template<typename, typename> class StatCastablePred
    , BOOST_PP_ENUM_BINARY_PARAMS(
          MML_MAX_REFINERY_SIZE
        , typename T
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
struct custom_refine_to
    : boost::mpl::vector<BOOST_PP_ENUM_PARAMS(MML_MAX_REFINERY_SIZE, T)>
    , policy_set<
          DynCaster
        , DynCastablePred
        , StatCaster
        , StatCastablePred
        >
{
};

} // namespace mml


#endif // _MML_REFINERY_CUSTOM_REFINE_TO_HPP_INCLUDED_
