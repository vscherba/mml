//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_OVERLOADED_FUNCTION_MAKE_OVERLOADED_FUNCTION_HPP_INCLUDED_
#define _MML_OVERLOADED_FUNCTION_MAKE_OVERLOADED_FUNCTION_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

#include <mml/overloaded_function/overloaded_function.hpp>


namespace mml {

#define _MML_MAKE_OVERLOADED_FUNCTION(z, n, _)                              \
    template <                                                              \
        BOOST_PP_ENUM_PARAMS(n, typename F)                                 \
        >                                                                   \
    inline                                                                  \
    overloaded_function<BOOST_PP_ENUM_PARAMS(n, F)>                         \
    make_overloaded_function(BOOST_PP_ENUM_BINARY_PARAMS(n, F, f))          \
    {                                                                       \
        return                                                              \
        overloaded_function<BOOST_PP_ENUM_PARAMS(n, F)>(                    \
            BOOST_PP_ENUM_PARAMS(n, f)                                      \
            );                                                              \
    }                                                                       \
    /**/


BOOST_PP_REPEAT_FROM_TO(
      1
    , BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
    , _MML_MAKE_OVERLOADED_FUNCTION
    ,
    )


// undef temporaries
#undef _MML_MAKE_OVERLOADED_FUNCTION

} // namespace mml


#endif // _MML_OVERLOADED_FUNCTION_MAKE_OVERLOADED_FUNCTION_HPP_INCLUDED_
