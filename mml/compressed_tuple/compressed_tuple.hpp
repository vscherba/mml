//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_COMPRESSED_TUPLE_COMPRESSED_TUPLE_HPP_INCLUDED_
#define _MML_COMPRESSED_TUPLE_COMPRESSED_TUPLE_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/tuple/to_seq.hpp>
#include <boost/preprocessor/seq/remove.hpp>
#include <boost/preprocessor/seq/enum.hpp>

// boost::mpl
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/long.hpp>

// boost::type_traits
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_empty.hpp>

// boost::call_traits
#include <boost/call_traits.hpp>

// boost::fusion
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>

#include <mml/config.hpp>
#include <mml/detail/replace_na_to_void.hpp>


#define _MML_CTUPLE_TEMPLATE_FORMAL_PARAMS                                  \
    BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, typename T)            \
    /**/

#define _MML_CTUPLE_TEMPLATE_FACT_PARAMS                                    \
    BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, T)                     \
    /**/

#define _MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAM(z, n, _)                       \
    typename boost::call_traits<T##n>::param_type a##n                      \
    /**/

#define _MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAMS                               \
    BOOST_PP_ENUM(                                                          \
          MML_MAX_FUNCTION_OVERLOADS                                        \
        , _MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAM                              \
        ,                                                                   \
        )                                                                   \
    /**/


namespace mml {

namespace detail {

    template <long I, _MML_CTUPLE_TEMPLATE_FORMAL_PARAMS>
    struct empty_ejector;


    template <long I, _MML_CTUPLE_TEMPLATE_FORMAL_PARAMS>
    struct sequence_holder
    {
    private:
        typedef boost::mpl::vector<
            _MML_CTUPLE_TEMPLATE_FACT_PARAMS
            > types;

    public:
        sequence_holder()
        {
        }

        sequence_holder(_MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAMS)
            : contained(
                BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, a)
                )
        {
        }

        template <typename N>
        typename boost::call_traits<
            typename boost::mpl::at<types, N>::type
            >::reference
        get(N)
        {
            return contained.get(N());
        }

    private:
        typedef empty_ejector<
              I
            , _MML_CTUPLE_TEMPLATE_FACT_PARAMS
            > ejector_type;

        typedef sequence_holder<
              I-1
            , _MML_CTUPLE_TEMPLATE_FACT_PARAMS
            > holder_type;

        typename boost::mpl::if_<
              boost::is_empty<
                typename boost::mpl::at_c<types, I>::type
                >
            , ejector_type
            , holder_type
            >::type contained;
    };


#define _MML_SEQ_HOLDER_REPLACE_NA_TO_VOID(z, n, _)                         \
    typename replace_na_to_void<T##n>::type                                 \
    /**/

#define _MML_SEQ_HOLDER_CONSTRUCTOR(z, n, _)                                \
    template <BOOST_PP_ENUM_PARAMS(n, typename A)>                          \
    sequence_holder(                                                        \
        BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)                               \
        BOOST_PP_ENUM_TRAILING_PARAMS(                                      \
              BOOST_PP_SUB(MML_MAX_FUNCTION_OVERLOADS, n)                   \
            , boost::mpl::na BOOST_PP_INTERCEPT                             \
            )                                                               \
        )                                                                   \
        : contained(BOOST_PP_ENUM_PARAMS(n, a))                             \
    {                                                                       \
    }                                                                       \
    /**/


    template <_MML_CTUPLE_TEMPLATE_FORMAL_PARAMS>
    struct sequence_holder<-1, _MML_CTUPLE_TEMPLATE_FACT_PARAMS>
    {
    private:
        typedef boost::mpl::vector<
            _MML_CTUPLE_TEMPLATE_FACT_PARAMS
            > types;

    public:
        sequence_holder()
        {
        }

        sequence_holder(
            BOOST_PP_ENUM_PARAMS(
                  MML_MAX_FUNCTION_OVERLOADS
                , boost::mpl::na BOOST_PP_INTERCEPT
                )
            )
        {
        }

        BOOST_PP_REPEAT_FROM_TO(
              1
            , BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
            , _MML_SEQ_HOLDER_CONSTRUCTOR
            ,
            )

        template <typename N>
        typename boost::call_traits<
            typename boost::mpl::at<types, N>::type
            >::reference
        get(N)
        {
            return boost::fusion::at<N>(contained);
        }

    private:
        boost::fusion::vector<
            BOOST_PP_ENUM(
                  MML_MAX_FUNCTION_OVERLOADS
                , _MML_SEQ_HOLDER_REPLACE_NA_TO_VOID
                ,
                )
            > contained;
    };


    template <long I, _MML_CTUPLE_TEMPLATE_FORMAL_PARAMS>
    struct empty_ejector_base
        : T0
    {
    private:
        typedef boost::mpl::vector<
            _MML_CTUPLE_TEMPLATE_FACT_PARAMS
            > types;

    public:
        empty_ejector_base()
        {
        }

        empty_ejector_base(_MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAMS)
            : T0(a0)
            , contained(
                  BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, a)
                , boost::mpl::na()
                )
        {
        }

#if defined(_MSC_VER) && _MSC_VER < 1500
#   define _MML_CTUPLE_N_CONSTANT                                           \
    boost::mpl::if_c<                                                       \
          (N < I)                                                           \
        , boost::mpl::long_<N + 1>                                          \
        , boost::mpl::long_<N>                                              \
        >::type::value                                                      \
        /**/
#else
#   define _MML_CTUPLE_N_CONSTANT ((N < I) ? N + 1 : N)
#endif // defined(_MSC_VER) && _MSC_VER < 1500

        template <long N>
        typename boost::call_traits<
            typename boost::mpl::at_c<
                  types
                , _MML_CTUPLE_N_CONSTANT
                >::type
            >::reference
        get(boost::mpl::long_<N>)
        {
            long const nth = (N < I) ? N : N - 1;
            return contained.get(boost::mpl::long_<nth>());
        }

#undef _MML_CTUPLE_N_CONSTANT

        typename boost::call_traits<T0>::reference
        get(boost::mpl::long_<I>)
        {
            return *this;
        }

        sequence_holder<
              I - 1
            , BOOST_PP_ENUM_SHIFTED_PARAMS(MML_MAX_FUNCTION_OVERLOADS, T)
            , boost::mpl::na
            > contained;
    };


#define _MML_ENUM_PARAMS_SKIP_N(count, name, n)                             \
    BOOST_PP_SEQ_ENUM(                                                      \
        BOOST_PP_SEQ_REMOVE(                                                \
              BOOST_PP_TUPLE_TO_SEQ(                                        \
                  count                                                     \
                , (BOOST_PP_ENUM_PARAMS(count, name))                       \
                )                                                           \
            , n                                                             \
            )                                                               \
        )                                                                   \
    /**/

#define _MML_EMPTY_EJECTOR_BASE_CLASS(n)                                    \
    empty_ejector_base<                                                     \
          n                                                                 \
        , T##n                                                              \
        , _MML_ENUM_PARAMS_SKIP_N(                                          \
              MML_MAX_FUNCTION_OVERLOADS                                    \
            , T                                                             \
            , n                                                             \
            )                                                               \
        >                                                                   \
    /**/

#define _MML_EJECTOR_CLASS_SPEC(z, n, _)                                    \
    template <_MML_CTUPLE_TEMPLATE_FORMAL_PARAMS>                           \
    struct empty_ejector<n, _MML_CTUPLE_TEMPLATE_FACT_PARAMS>               \
        : _MML_EMPTY_EJECTOR_BASE_CLASS(n)                                  \
    {                                                                       \
        empty_ejector()                                                     \
        {                                                                   \
        }                                                                   \
                                                                            \
        empty_ejector(_MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAMS)                \
            : _MML_EMPTY_EJECTOR_BASE_CLASS(n)(                             \
                  a##n                                                      \
                , _MML_ENUM_PARAMS_SKIP_N(                                  \
                      MML_MAX_FUNCTION_OVERLOADS                            \
                    , a                                                     \
                    , n                                                     \
                    )                                                       \
                )                                                           \
        {                                                                   \
        }                                                                   \
    };                                                                      \
    /**/


    BOOST_PP_REPEAT(
          MML_MAX_FUNCTION_OVERLOADS
        , _MML_EJECTOR_CLASS_SPEC
        ,
        )

} // namespace detail


#define _MML_COMPRESSED_TUPLE_CONSTRUCTOR(z, n, _)                          \
    explicit compressed_tuple(                                              \
        BOOST_PP_ENUM(n, _MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAM, )            \
        )                                                                   \
        : _seq(                                                             \
            BOOST_PP_ENUM_PARAMS(n, a)                                      \
            BOOST_PP_ENUM_TRAILING_PARAMS(                                  \
                  BOOST_PP_SUB(MML_MAX_FUNCTION_OVERLOADS, n)               \
                , boost::mpl::na() BOOST_PP_INTERCEPT                       \
                )                                                           \
            )                                                               \
    {                                                                       \
    }                                                                       \
    /**/


template <
    BOOST_PP_ENUM_BINARY_PARAMS(
          MML_MAX_FUNCTION_OVERLOADS
        , typename T
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
class compressed_tuple
{
public:
    typedef boost::mpl::vector<
        _MML_CTUPLE_TEMPLATE_FACT_PARAMS
        > types;

    compressed_tuple()
    {
    }

    BOOST_PP_REPEAT_FROM_TO(
          1
        , BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
        , _MML_COMPRESSED_TUPLE_CONSTRUCTOR
        ,
        )

    template <long N>
    typename boost::call_traits<
        typename boost::mpl::at_c<types, N>::type
        >::reference
    get()
    {
        return _seq.get(boost::mpl::long_<N>());
    }

    template <long N>
    typename boost::call_traits<
        typename boost::mpl::at_c<types, N>::type
        >::const_reference
    get() const
    {
        return const_cast<compressed_tuple*>(this)->get<N>();
    }

private:
    detail::sequence_holder<
          boost::mpl::size<types>::value - 1
        , _MML_CTUPLE_TEMPLATE_FACT_PARAMS
        > _seq;
};

} // namespace mml


// undefs
#undef _MML_CTUPLE_TEMPLATE_FORMAL_PARAMS
#undef _MML_CTUPLE_TEMPLATE_FACT_PARAMS
#undef _MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAM
#undef _MML_CTUPLE_CONSTRUCTOR_FORMAL_PARAMS
#undef _MML_SEQ_HOLDER_REPLACE_NA_TO_VOID
#undef _MML_SEQ_HOLDER_CONSTRUCTOR
#undef _MML_ENUM_PARAMS_SKIP_N
#undef _MML_EMPTY_EJECTOR_BASE_CLASS
#undef _MML_EJECTOR_CLASS_SPEC
#undef _MML_COMPRESSED_TUPLE_CONSTRUCTOR


#endif // _MML_COMPRESSED_TUPLE_COMPRESSED_TUPLE_HPP_INCLUDED_
