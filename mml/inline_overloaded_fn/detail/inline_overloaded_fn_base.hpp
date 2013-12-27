//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_INLINE_OVERLOADED_FN_DETAIL_INLINE_OVERLOADED_FN_BASE_HPP_INCLUDED_
#define _MML_INLINE_OVERLOADED_FN_DETAIL_INLINE_OVERLOADED_FN_BASE_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

// boost::mpl
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>

// boost::function_types
#include <boost/function_types/parameter_types.hpp>

#include <mml/config.hpp>
#include <mml/function_types/components.hpp>
#include <mml/function_types/function_arity.hpp>
#include <mml/function_types/function_type.hpp>


#ifdef MML_COMPRESSION_OFF
#   include <boost/fusion/include/vector.hpp>
#   include <boost/fusion/include/at_c.hpp>
#   include <mml/detail/replace_na_to_void.hpp>
#   define _MML_IOFB_GET_ITEM_FROM_SEQ(seq, n) (boost::fusion::at_c<n>(seq))
#else
#   include <mml/compressed_tuple/compressed_tuple.hpp>
#   define _MML_IOFB_GET_ITEM_FROM_SEQ(seq, n) (seq.template get<n>())
#endif // MML_COMPRESSION_OFF


namespace mml {
namespace detail {

class root_invoker
{
    struct dummy;
public:
    void operator()(dummy) const;
};


template <
      typename Derived
    , typename Targets
    , long N
    , long Arity =
        function_types::function_arity<
            typename boost::mpl::at_c<Targets, N>::type
            >::value
    >
class target_invoker;


template <
      typename Derived
    , typename Targets
    , long N = boost::mpl::size<Targets>::value
    >
struct get_invoker_base
{
    typedef target_invoker<Derived, Targets, N - 1> type;
};


template <typename Derived, typename Targets>
struct get_invoker_base<Derived, Targets, 0>
{
    typedef root_invoker type;
};


#define _MML_TARGET_INVOKER_ARG_TYPEDEF(z, n, _)                            \
    typedef typename                                                        \
        boost::mpl::at_c<component_types, n + 1>::type arg_type##n;         \
/**/

#define _MML_TARGET_INVOKER_CALL_OPERATOR(n, const_kw)                      \
    r_type  operator()(                                                     \
        BOOST_PP_ENUM_BINARY_PARAMS(                                        \
              n                                                             \
            , arg_type                                                      \
            , a                                                             \
            )                                                               \
        ) const_kw                                                          \
    {                                                                       \
        return                                                              \
        _MML_IOFB_GET_ITEM_FROM_SEQ                                         \
        (static_cast<Derived const_kw*>(this)->_targets, N)(                \
            BOOST_PP_ENUM_PARAMS(n, a)                                      \
            );                                                              \
    }                                                                       \
    /**/

#if defined(_MSC_VER) && _MSC_VER < 1400
#   define _MML_TARGET_INVOKER_CALL_OPERATOR_DEF(n)                         \
        /*workaround for old MSVC: only const operator() without nonconst*/ \
        _MML_TARGET_INVOKER_CALL_OPERATOR(n, const)                         \
        /**/
#else
#   define _MML_TARGET_INVOKER_CALL_OPERATOR_DEF(n)                         \
        _MML_TARGET_INVOKER_CALL_OPERATOR(n, )                              \
        _MML_TARGET_INVOKER_CALL_OPERATOR(n, const)                         \
        /**/
#endif // defined(_MSC_VER) && _MSC_VER < 1400

#define _MML_TARGET_INVOKER(z, n, _)                                        \
    template <typename Derived, typename Targets, long N>                   \
    class target_invoker<Derived, Targets, N, n>                            \
        : public get_invoker_base<Derived, Targets, N>::type                \
    {                                                                       \
        typedef typename                                                    \
            get_invoker_base<Derived, Targets, N>::type base_class;         \
                                                                            \
        typedef typename                                                    \
            boost::mpl::at_c<Targets, N>::type target_type;                 \
                                                                            \
        typedef typename                                                    \
            function_types::components<target_type>::types component_types; \
                                                                            \
        typedef typename                                                    \
            boost::mpl::front<component_types>::type r_type;                \
                                                                            \
        BOOST_PP_REPEAT(                                                    \
              n                                                             \
            , _MML_TARGET_INVOKER_ARG_TYPEDEF                               \
            ,                                                               \
            )                                                               \
                                                                            \
    public:                                                                 \
        using base_class::operator();                                       \
        _MML_TARGET_INVOKER_CALL_OPERATOR_DEF(n)                            \
    };                                                                      \
    /**/


BOOST_PP_REPEAT(
      BOOST_PP_INC(MML_MAX_ARITY)
    , _MML_TARGET_INVOKER
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


template <
      typename Derived
    , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, typename F)
    >
class inline_overloaded_fn_base
    : protected get_invoker_base<
          Derived
        , boost::mpl::vector<
            BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, F)
            >
        >::type
{
protected:
    typedef
#ifdef MML_COMPRESSION_OFF
#   define _MML_IOFB_REPLACE_NA_TO_VOID(z, n, _)                            \
        typename replace_na_to_void<F##n>::type                             \
        /**/

    boost::fusion::vector<
        BOOST_PP_ENUM(
              MML_MAX_FUNCTION_OVERLOADS
            , _MML_IOFB_REPLACE_NA_TO_VOID
            ,
            )
        >
#   undef _MML_IOFB_REPLACE_NA_TO_VOID
#else
    compressed_tuple<BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, F)>
#endif // MML_COMPRESSION_OFF
    tuple_type;

    typedef typename tuple_type::types types;
    typedef typename boost::mpl::transform<
          types
        , function_types::function_type<boost::mpl::_>
        >::type signatures;

private:
    BOOST_MPL_ASSERT_MSG(
          (is_unique<
            typename boost::mpl::transform<
                  types
                , boost::function_types::parameter_types<boost::mpl::_>
                >::type
            >::value)
        , TWO_OR_MORE_OVERLOADED_FUNCTIONS_HAVE_EQUAL_PARAMETER_LISTS
        , (typename inline_overloaded_fn_base::signatures)
        );
};

} // namespace detail
} // namespace mml


// undef temporaries
#undef _MML_IOFB_GET_ITEM_FROM_SEQ
#undef _MML_TARGET_INVOKER_ARG_TYPEDEF
#undef _MML_TARGET_INVOKER_CALL_OPERATOR
#undef _MML_TARGET_INVOKER_CALL_OPERATOR_DEF
#undef _MML_TARGET_INVOKER


#endif//_MML_INLINE_OVERLOADED_FN_DETAIL_INLINE_OVERLOADED_FN_BASE_HPP_INCLUDED_
