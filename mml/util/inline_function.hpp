//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_UTIL_INLINE_FUNCTION_HPP_INCLUDED_
#define _MML_UTIL_INLINE_FUNCTION_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>

#include <mml/config.hpp>


namespace mml {

template <
      typename F
    , F& f
    >
struct inline_function;


#define _MML_IFUNCTION_ARG_N_TYPE_TYPEDEF(z, n, _)                          \
    typedef A##n BOOST_PP_CAT(arg, BOOST_PP_CAT(BOOST_PP_INC(n), _type));   \
    /**/

#define _MML_INLINE_FUNCTION(z, n, _)                                       \
    template <                                                              \
          typename R                                                        \
          BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)                      \
        , R(&f)(BOOST_PP_ENUM_PARAMS(n, A))                                 \
        >                                                                   \
    struct inline_function<R(BOOST_PP_ENUM_PARAMS(n, A)), f>                \
    {                                                                       \
        typedef R signature(BOOST_PP_ENUM_PARAMS(n, A));                    \
                                                                            \
        BOOST_PP_IF(                                                        \
              BOOST_PP_EQUAL(n, 1)                                          \
            , typedef A0 argument_type;                                     \
            ,                                                               \
            )                                                               \
                                                                            \
        BOOST_PP_IF(                                                        \
              BOOST_PP_EQUAL(n, 2)                                          \
            , typedef A0 first_argument_type;                               \
              typedef A1 second_argument_type;                              \
            ,                                                               \
            )                                                               \
                                                                            \
        typedef R result_type;                                              \
                                                                            \
        BOOST_PP_REPEAT(n, _MML_IFUNCTION_ARG_N_TYPE_TYPEDEF, )             \
                                                                            \
        R operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const            \
        {                                                                   \
            return f(BOOST_PP_ENUM_PARAMS(n, a));                           \
        }                                                                   \
    };                                                                      \
    /**/


BOOST_PP_REPEAT(
      BOOST_PP_INC(MML_MAX_ARITY)
    , _MML_INLINE_FUNCTION
    ,
    )


// undef temporaries
#undef _MML_IFUNCTION_ARG_N_TYPE_TYPEDEF
#undef _MML_INLINE_FUNCTION

} // namespace mml


#endif // _MML_UTIL_INLINE_FUNCTION_HPP_INCLUDED_
