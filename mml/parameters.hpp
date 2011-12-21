//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_PARAMETERS_HPP_INCLUDED_
#define _MML_PARAMETERS_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

// boost::mpl
#include <boost/mpl/vector.hpp>


namespace mml {

template <
    BOOST_PP_ENUM_BINARY_PARAMS(
          MML_MAX_ARITY
        , typename T
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
struct parameters
    : boost::mpl::vector<BOOST_PP_ENUM_PARAMS(MML_MAX_ARITY, T)>
{
};

} // namespace mml


#endif // _MML_PARAMETERS_HPP_INCLUDED_
