//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_INLINE_OVERLOADED_FN_INLINE_OVERLOADED_FN_HPP_INCLUDED_
#define _MML_INLINE_OVERLOADED_FN_INLINE_OVERLOADED_FN_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

// boost::mpl
#include <boost/mpl/long.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/find.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

// boost::call_traits
#include <boost/call_traits.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/function_types/result_type.hpp>

#include <mml/config.hpp>
#include <mml/function_types/components.hpp>
#include <mml/function_types/function_arity.hpp>
#include <mml/function_types/function_type.hpp>


#ifdef MML_COMPRESSION_OFF
#   include <boost/fusion/include/vector.hpp>
#   include <boost/fusion/include/at_c.hpp>
#   include <mml/detail/replace_na_to_void.hpp>

#   define _MML_OF_REPLACE_NA_TO_VOID(z, n, _)                              \
        typename replace_na_to_void<f_type##n>::type                        \
        /**/
#else
#   include <mml/compressed_tuple/compressed_tuple.hpp>
#endif // MML_COMPRESSION_OFF


#ifdef MML_RESULT_OF_SUPPORT_ON
#   include <mml/result_of_support/result_of_support.hpp>

namespace mml {
namespace detail {

template <typename F>
    struct create_signature
    {
        typedef const_signature<
            typename function_types::function_type<F>::type
            > type;
    };

    template <>
    struct create_signature<boost::mpl::na>
        : boost::mpl::na
    {
    };


#   define _MML_OF_CREATE_SIGNATURE(z, n, _)                                \
        typename detail::create_signature<F##n>::type                       \
    /**/

} // namespace detail
} // namespace mml
#endif // MML_RESULT_OF_SUPPORT_ON


namespace mml {

namespace detail {

#define _MML_OF_INVOKER_CALL_OPERATOR_FORMAL_PARAM(z, n, _)                 \
    arg_type##n a##n                                                        \
    /**/


    class root_invoker
    {
        struct dummy;
    public:
        void operator()(dummy) const;
    };


    template <
          typename Seq
        , long N
        , long Arity =
            function_types::function_arity<
                typename boost::mpl::at_c<Seq, N>::type
                >::value
        >
    class of_invoker;


    // fwd
    template <typename Seq>
    class inline_overloaded_fn_over_seq;


    template <typename Seq, long N>
    struct get_invoker_base
    {
        typedef of_invoker<Seq, N - 1> type;
    };


    template <typename Seq>
    struct get_invoker_base<Seq, 0>
    {
        typedef root_invoker type;
    };


#define _MML_OF_INVOKER_ARG_TYPEDEF(z, n, _)                                \
    typedef typename                                                        \
        boost::mpl::at_c<component_types, n + 1>::type arg_type##n;         \
    /**/

#define _MML_OF_INVOKER_CALL_OPERATOR(n, const_kw)                          \
    r_type  operator()(                                                     \
        BOOST_PP_ENUM(                                                      \
                n                                                           \
            , _MML_OF_INVOKER_CALL_OPERATOR_FORMAL_PARAM                    \
            ,                                                               \
            )                                                               \
        ) const_kw                                                          \
    {                                                                       \
        return                                                              \
        static_cast<derived_class const_kw*>(this)->template get<N>()(      \
            BOOST_PP_ENUM_PARAMS(n, a)                                      \
            );                                                              \
    }                                                                       \
    /**/

#if defined(_MSC_VER) && _MSC_VER < 1400
#   define _MML_OF_INVOKER_CALL_OPERATOR_DEF(n)                             \
        /*workaround for old MSVC: only const operator() without nonconst*/ \
        _MML_OF_INVOKER_CALL_OPERATOR(n, const)                             \
        /**/
#else
#   define _MML_OF_INVOKER_CALL_OPERATOR_DEF(n)                             \
        _MML_OF_INVOKER_CALL_OPERATOR(n, )                                  \
        _MML_OF_INVOKER_CALL_OPERATOR(n, const)                             \
        /**/
#endif // defined(_MSC_VER) && _MSC_VER < 1400

#define _MML_OF_INVOKER(z, n, _)                                            \
    template <typename Seq, long N>                                         \
    class of_invoker<Seq, N, n>                                             \
        : public get_invoker_base<Seq, N>::type                             \
    {                                                                       \
        typedef typename                                                    \
            get_invoker_base<Seq, N>::type base_class;                      \
                                                                            \
        typedef                                                             \
            inline_overloaded_fn_over_seq<Seq> derived_class;               \
                                                                            \
        typedef typename                                                    \
            boost::mpl::at_c<Seq, N>::type f_type;                          \
                                                                            \
        typedef typename                                                    \
            function_types::components<f_type>::types component_types;      \
                                                                            \
        typedef typename                                                    \
            boost::mpl::front<component_types>::type r_type;                \
                                                                            \
        BOOST_PP_REPEAT(                                                    \
              n                                                             \
            , _MML_OF_INVOKER_ARG_TYPEDEF                                   \
            ,                                                               \
            )                                                               \
                                                                            \
    public:                                                                 \
        using base_class::operator();                                       \
        _MML_OF_INVOKER_CALL_OPERATOR_DEF(n)                                \
    };                                                                      \
    /**/


    BOOST_PP_REPEAT(
          BOOST_PP_INC(MML_MAX_ARITY)
        , _MML_OF_INVOKER
        ,
        )


    template <typename Seq, long Size = boost::mpl::size<Seq>::value>
    struct is_unique_impl
    {
    private:
        typedef typename boost::mpl::pop_front<Seq>::type tail;
        typedef typename boost::mpl::count<
              tail
            , typename boost::mpl::front<Seq>::type
            >::type count;

    public:
        typedef typename boost::mpl::and_<
              boost::mpl::not_<count>
            , is_unique_impl<tail>
            >::type type;
    };


    template <typename Seq>
    struct is_unique_impl<Seq, 0>
        : boost::mpl::true_
    {
    };


    template <typename Seq>
    struct is_unique
        : is_unique_impl<Seq>::type
    {
    };


    template <typename Seq, long N>
    struct safe_at_c
        : boost::mpl::eval_if_c<
              N < boost::mpl::size<Seq>::value
            , boost::mpl::at_c<Seq, N>
            , boost::mpl::na
            >
    {
    };


#define _MML_OF_TEMPLATE_FACT_PARAM_LIST                                    \
    BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, F)                     \
    /**/

#define _MML_OF_F_TYPEDEF(z, n, _)                                          \
    typedef typename safe_at_c<Seq, n>::type f_type##n;                     \
    /**/

#define _MML_OF_CONSTRUCTOR_FORMAL_PARAM(z, n, f_t)                         \
    typename boost::call_traits<f_t##n>::param_type f##n                    \
    /**/

#define _MML_OF_SEQ_CONSTRUCTOR(z, n, _)                                    \
    explicit inline_overloaded_fn_over_seq(                                 \
        BOOST_PP_ENUM(                                                      \
              n                                                             \
            , _MML_OF_CONSTRUCTOR_FORMAL_PARAM                              \
            , f_type                                                        \
            )                                                               \
        )                                                                   \
        : _funcs(BOOST_PP_ENUM_PARAMS(n, f))                                \
    {                                                                       \
    }                                                                       \
    /**/


    template <typename Seq>
    class inline_overloaded_fn_over_seq
        :
#ifdef __GNUC__
        protected   // GCC workaround of inaccessible base
#else
        private     // correct case
#endif
        get_invoker_base<
              Seq
            , boost::mpl::size<Seq>::value
            >::type
    {
        typedef typename get_invoker_base<
              Seq
            , boost::mpl::size<Seq>::value
            >::type base_class;

        BOOST_PP_REPEAT(
              MML_MAX_FUNCTION_OVERLOADS
            , _MML_OF_F_TYPEDEF
            ,
            )

        typedef
#ifdef MML_COMPRESSION_OFF
        boost::fusion::vector<
            BOOST_PP_ENUM(
                  MML_MAX_FUNCTION_OVERLOADS
                , _MML_OF_REPLACE_NA_TO_VOID
                ,
                )
            >
#   undef _MML_OF_REPLACE_NA_TO_VOID
#else
        compressed_tuple<
            BOOST_PP_ENUM_PARAMS(
                  MML_MAX_FUNCTION_OVERLOADS
                , f_type
                )
            >
#endif // MML_COMPRESSION_OFF
        tuple_type;

    public:
        using base_class::operator();

        typedef typename tuple_type::types types;
        typedef typename boost::mpl::transform<
              types
            , function_types::function_type<boost::mpl::_>
            >::type signatures;

        template <long N>
        typename boost::call_traits<
            typename boost::mpl::at_c<types, N>::type
            >::reference
        get()
        {
            return
#ifdef MML_COMPRESSION_OFF
            boost::fusion::at_c<N>(_funcs);
#else
            _funcs.template get<N>();
#endif // MML_COMPRESSION_OFF
        }

        template <long N>
        typename boost::call_traits<
            typename boost::mpl::at_c<types, N>::type
            >::const_reference
        get() const
        {
            return const_cast<inline_overloaded_fn_over_seq*>(this)
                ->template get<N>();
        }

        template <typename F>
        typename boost::call_traits<F>::reference
        get()
        {
            namespace _bmpl = boost::mpl;
            return get<
                _bmpl::distance<
                      typename _bmpl::begin<types>::type
                    , typename _bmpl::find<
                        types, F
                        >::type
                    >::value
                >();
        }

        template <typename F>
        typename boost::call_traits<F>::const_reference
        get() const
        {
            return const_cast<inline_overloaded_fn_over_seq*>(this)
                ->template get<F>();
        }

    protected:
        BOOST_PP_REPEAT(
              BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
            , _MML_OF_SEQ_CONSTRUCTOR
            ,
            )

        ~inline_overloaded_fn_over_seq()
        {
        }

    private:
        BOOST_MPL_ASSERT_MSG(
              (is_unique<
                typename boost::mpl::transform<
                      types
                    , boost::function_types::parameter_types<boost::mpl::_>
                    >::type
                >::value)
            , TWO_OR_MORE_OVERLOADED_FUNCTIONS_HAVE_EQUAL_PARAMETER_LISTS
            , (typename inline_overloaded_fn_over_seq::signatures)
            );

        tuple_type _funcs;
    };

} // namespace detail


#define _MML_OF_CONSTRUCTOR(z, n, _)                                        \
    explicit inline_overloaded_fn(                                          \
        BOOST_PP_ENUM(                                                      \
              n                                                             \
            , _MML_OF_CONSTRUCTOR_FORMAL_PARAM                              \
            , F                                                             \
            )                                                               \
        )                                                                   \
        : base_class(BOOST_PP_ENUM_PARAMS(n, f))                            \
    {                                                                       \
    }                                                                       \
    /**/


template <
    BOOST_PP_ENUM_BINARY_PARAMS(
          MML_MAX_FUNCTION_OVERLOADS
        , typename F
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
class inline_overloaded_fn
    : public detail::inline_overloaded_fn_over_seq<
        boost::mpl::vector<_MML_OF_TEMPLATE_FACT_PARAM_LIST>
        >
#ifdef MML_RESULT_OF_SUPPORT_ON
    , public mml::result_of_support<
        BOOST_PP_ENUM(MML_MAX_FUNCTION_OVERLOADS, _MML_OF_CREATE_SIGNATURE, )
        >
#   undef _MML_OF_CREATE_SIGNATURE
#endif // MML_RESULT_OF_SUPPORT_ON
{
    typedef detail::inline_overloaded_fn_over_seq<
        boost::mpl::vector<_MML_OF_TEMPLATE_FACT_PARAM_LIST>
        > base_class;

public:
    BOOST_PP_REPEAT(
          BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
        , _MML_OF_CONSTRUCTOR
        ,
        )
};

} // namespace mml


// undef temporaries
#undef _MML_OF_INVOKER_CALL_OPERATOR_FORMAL_PARAM
#undef _MML_OF_INVOKER_ARG_TYPEDEF
#undef _MML_OF_INVOKER_CALL_OPERATOR
#undef _MML_OF_INVOKER_CALL_OPERATOR_DEF
#undef _MML_OF_INVOKER
#undef _MML_OF_TEMPLATE_FACT_PARAM_LIST
#undef _MML_OF_F_TYPEDEF
#undef _MML_OF_CONSTRUCTOR_FORMAL_PARAM
#undef _MML_OF_SEQ_CONSTRUCTOR
#undef _MML_OF_CONSTRUCTOR


#endif // _MML_INLINE_OVERLOADED_FN_INLINE_OVERLOADED_FN_HPP_INCLUDED_
