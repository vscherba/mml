//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_RESULT_OF_SUPPORT_RESULT_OF_SUPPORT_HPP_INCLUDED_
#define _MML_RESULT_OF_SUPPORT_RESULT_OF_SUPPORT_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>

// boost::static_assert
#include <boost/static_assert.hpp>

// boost::utility
#include <boost/utility/declval.hpp>

#include <mml/config.hpp>


namespace mml {

namespace detail {

template <typename T>
struct not_na_filter
{
    typedef T type;
};


#define _MML_RESULT_OF_SUPP_NA(z, n, _)                                     \
    class na##n{};                                                          \
                                                                            \
    template <>                                                             \
    struct not_na_filter<na##n>{};                                          \
    /**/


    BOOST_PP_REPEAT(
          MML_MAX_FUNCTION_OVERLOADS
        , _MML_RESULT_OF_SUPP_NA
        ,
        )

} // namespace detail


template <
      typename R0
    , BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(
          MML_MAX_FUNCTION_OVERLOADS
        , typename R
        , = detail::na
        )
    >
class result_of_support
{
    template <long N>
    struct _sizer
    {
        char value[N + 1];
    };


    template <long N, typename Dummy>
    struct _result_types{};


#define _MML_RESULT_OF_SUPP_TYPE_MAPPING(z, n, _)                           \
    static _sizer<n> _size(R##n);                                           \
                                                                            \
    template <typename Dummy>                                               \
    struct _result_types<n, Dummy>                                          \
    {                                                                       \
        typedef R##n type;                                                  \
    };                                                                      \
    /**/


    BOOST_PP_REPEAT(
          MML_MAX_FUNCTION_OVERLOADS
        , _MML_RESULT_OF_SUPP_TYPE_MAPPING
        ,
        )


    template <bool Condition>
    struct _assertion
    {
        BOOST_STATIC_ASSERT_MSG(Condition,
    "Tested functor signature returns type not present in 'result_of_support'"
    "template parameters. Please correct 'result_of_support'"
    "template parameters according to operator() return types."
        );
    };


    template <typename UnknownType>
    static _assertion<false> _size(UnknownType);

public:
    template <long N>
    struct result_types
        : detail::not_na_filter<typename _result_types<N, void>::type>
    {
    };


    template <typename>
    struct result;


#define _MML_RESULT_OF_SUPP_DECLVAL_OF_A(z, n, _)                           \
    boost::declval<A##n>()                                                  \
    /**/

#define _MML_RESULT_OF_SUPP_RESULT(z, n, _)                                 \
    template <typename F BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)>      \
    struct result<F(BOOST_PP_ENUM_PARAMS(n, A))>                            \
        : result_types<                                                     \
            sizeof(                                                         \
                _size(                                                      \
                    boost::declval<F>().operator()(                         \
                        BOOST_PP_ENUM(n, _MML_RESULT_OF_SUPP_DECLVAL_OF_A, )\
                        )                                                   \
                    ).value                                                 \
                )                                                           \
            /                                                               \
            sizeof(char)                                                    \
            - 1                                                             \
            >                                                               \
    {                                                                       \
    };                                                                      \
    /**/


    BOOST_PP_REPEAT(MML_MAX_ARITY, _MML_RESULT_OF_SUPP_RESULT, )
};


// undef temporaries
#undef _MML_RESULT_OF_SUPP_NA
#undef _MML_RESULT_OF_SUPP_TYPE_MAPPING
#undef _MML_RESULT_OF_SUPP_DECLVAL_OF_A
#undef _MML_RESULT_OF_SUPP_RESULT

} // namespace mml


#endif // _MML_RESULT_OF_SUPPORT_RESULT_OF_SUPPORT_HPP_INCLUDED_
