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
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

// boost::static_assert
#include <boost/static_assert.hpp>

// boost::utility
#include <boost/utility/declval.hpp>

// boost::mpl
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>

#include <mml/config.hpp>


namespace mml {

template <typename Sig>
struct const_signature {};

template <typename Sig>
struct nonconst_signature {};

template <typename Sig>
struct signature {};


namespace detail {

    template <long N>
    struct sizer
    {
        char value[N + 1];
    };


    template <bool Condition>
    struct _assertion
    {
        BOOST_STATIC_ASSERT_MSG(Condition,
    "Tested functor signature returns type not present in 'result_of_support'"
    "template parameters. Please correct 'result_of_support'"
    "template parameters according to operator() return types."
        );
    };


    template <
          typename BaseFunctor
        , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, typename R)
        >
    struct synthetic_functor;


    template <typename BaseFunctor>
    struct synthetic_functor<
          BaseFunctor
        , BOOST_PP_ENUM_PARAMS(
              MML_MAX_FUNCTION_OVERLOADS
            , boost::mpl::na BOOST_PP_INTERCEPT
            )
        >
        : BaseFunctor
    {
        using BaseFunctor::operator();
        BOOST_STATIC_CONSTANT(long, _n = -1);

        template <typename UnknownType>
        static _assertion<false> _size(UnknownType);

        template <long N>
        struct nth_result_type
        {
        };
    };


#define _MML_RESULT_OF_SUPP_SYNTHETIC_FUNCTOR(z, n, const_flag)             \
    template <                                                              \
          typename BaseFunctor                                              \
        , typename R                                                        \
          BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)                      \
        , BOOST_PP_ENUM_SHIFTED_PARAMS(                                     \
              MML_MAX_FUNCTION_OVERLOADS                                    \
            , typename R                                                    \
            )                                                               \
        >                                                                   \
    struct synthetic_functor<                                               \
          BaseFunctor                                                       \
        , BOOST_PP_IF(const_flag, const_signature, nonconst_signature)      \
            <R(BOOST_PP_ENUM_PARAMS(n, A))>                                 \
        , BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)       \
        >                                                                   \
        : synthetic_functor<                                                \
              BaseFunctor                                                   \
            , BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)   \
            , boost::mpl::na                                                \
            >                                                               \
    {                                                                       \
        typedef synthetic_functor<                                          \
              BaseFunctor                                                   \
            , BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)   \
            , boost::mpl::na                                                \
            > base_class;                                                   \
                                                                            \
        BOOST_STATIC_CONSTANT(long, _n = base_class::_n + 1);               \
        using base_class::_size;                                            \
        static detail::sizer<_n> _size(detail::sizer<_n>);                  \
                                                                            \
        template <long N>                                                   \
        struct nth_result_type                                              \
            : boost::mpl::eval_if_c<                                        \
                  N == _n                                                   \
                , boost::mpl::identity<R>                                   \
                , typename base_class::template nth_result_type<N>          \
                >                                                           \
        {                                                                   \
        };                                                                  \
                                                                            \
        using base_class::operator();                                       \
        sizer<_n> operator()                                                \
            (BOOST_PP_ENUM_PARAMS(n, A)) BOOST_PP_IF(const_flag, const, );  \
                                                                            \
    };                                                                      \
    /**/


    BOOST_PP_REPEAT(
          MML_MAX_ARITY
        , _MML_RESULT_OF_SUPP_SYNTHETIC_FUNCTOR
        , 0
        )


    BOOST_PP_REPEAT(
          MML_MAX_ARITY
        , _MML_RESULT_OF_SUPP_SYNTHETIC_FUNCTOR
        , 1
        )


    template <
          typename BaseFunctor
        , typename Sig
        , BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, typename R)
        >
    struct synthetic_functor<
          BaseFunctor
        , signature<Sig>
        , BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)
        >
        : synthetic_functor<
              BaseFunctor
            , const_signature<Sig>
            , nonconst_signature<Sig>
            , BOOST_PP_ENUM_SHIFTED_PARAMS
                (BOOST_PP_DEC(MML_MAX_FUNCTION_OVERLOADS), R)
            >
    {
    };


    template <
          typename BaseFunctor
        , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, typename R)
        >
    struct synthetic_functor
        : synthetic_functor<
              BaseFunctor
            , BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)
            , boost::mpl::na
            >
    {
        typedef synthetic_functor<
              BaseFunctor
            , BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)
            , boost::mpl::na
            > base_class;

        BOOST_STATIC_CONSTANT(long, _n = base_class::_n + 1);

        using base_class::_size;
        static detail::sizer<_n> _size(R0);

        template <long N>
        struct nth_result_type
            : boost::mpl::eval_if_c<
                  N == _n
                , boost::mpl::identity<R0>
                , typename base_class::template nth_result_type<N>
                >
        {
        };
    };


    template <
          typename F
        , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, typename R)
        >
    struct synthesize
    {
        typedef synthetic_functor<
              F
            , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)
            > type;
    };


    template <
          typename F
        , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, typename R)
        >
    struct synthesize<
          const F
        , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)
        >
    {
        typedef const typename synthesize<
              F
            , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)
            >::type type;
    };

} // namespace detail


template <
      typename R0
    , BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(
          MML_MAX_FUNCTION_OVERLOADS
        , typename R
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
struct result_of_support
{
    template <typename>
    struct result;


#define _MML_RESULT_OF_SUPP_DECLVAL_OF_A(z, n, _)                           \
    boost::declval<A##n>()                                                  \
    /**/

#define _MML_RESULT_OF_SUPP_RESULT(z, n, _)                                 \
    template <typename F BOOST_PP_ENUM_TRAILING_PARAMS(n, typename A)>      \
    struct result<F(BOOST_PP_ENUM_PARAMS(n, A))>                            \
    {                                                                       \
        typedef typename detail::synthesize<                                \
              F                                                             \
            , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, R)           \
            >::type synth_fn;                                               \
                                                                            \
    public:                                                                 \
        typedef typename synth_fn::template nth_result_type<                \
            sizeof(                                                         \
                boost::declval<synth_fn>()._size(                           \
                    boost::declval<synth_fn>().operator()(                  \
                        BOOST_PP_ENUM(n, _MML_RESULT_OF_SUPP_DECLVAL_OF_A, )\
                        )                                                   \
                    ).value                                                 \
                )                                                           \
            /                                                               \
            sizeof(char)                                                    \
            - 1                                                             \
            >::type type;                                                   \
    };                                                                      \
    /**/


    BOOST_PP_REPEAT(BOOST_PP_INC(MML_MAX_ARITY), _MML_RESULT_OF_SUPP_RESULT, )
};


// undef temporaries
#undef _MML_RESULT_OF_SUPP_SYNTHETIC_FUNCTOR
#undef _MML_RESULT_OF_SUPP_DECLVAL_OF_A
#undef _MML_RESULT_OF_SUPP_RESULT

} // namespace mml


#endif // _MML_RESULT_OF_SUPPORT_RESULT_OF_SUPPORT_HPP_INCLUDED_
