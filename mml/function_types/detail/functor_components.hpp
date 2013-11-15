//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FUNCTION_TYPES_DETAIL_FUNCTOR_COMPONENTS_HPP_INCLUDED_
#define _MML_FUNCTION_TYPES_DETAIL_FUNCTOR_COMPONENTS_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

// boost::mpl
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/always.hpp>

// boost::type_traits
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>

// boost::function_types
#include <boost/function_types/components.hpp>

// boost::typeof
#include <boost/typeof/typeof.hpp>

#include <mml/config.hpp>


namespace mml {
namespace function_types {
namespace detail {

#define _MML_DECLARE_GET_TRAIT(name, def)                                   \
    BOOST_MPL_HAS_XXX_TRAIT_DEF(name);                                      \
                                                                            \
    template <typename T, typename DefF def>                                \
    struct get_##name                                                       \
    {                                                                       \
    private:                                                                \
        struct trait_accessor                                               \
            : boost::mpl::identity<typename T::name>                        \
        {                                                                   \
        };                                                                  \
                                                                            \
    public:                                                                 \
        typedef typename boost::mpl::eval_if<                               \
              has_##name<T>                                                 \
            , trait_accessor                                                \
            , DefF                                                          \
            >::type type;                                                   \
    }                                                                       \
    /**/

#define _MML_DECLARE_GET_TRAIT_FOR_ARGN(z, n, _)                            \
    _MML_DECLARE_GET_TRAIT(arg##n##_type, = boost::mpl::na);                \
    /**/


BOOST_PP_REPEAT_FROM_TO(
      1
    , BOOST_PP_INC(MML_MAX_ARITY)
    , _MML_DECLARE_GET_TRAIT_FOR_ARGN
    ,
    )


_MML_DECLARE_GET_TRAIT(argument_type, = boost::mpl::na);
_MML_DECLARE_GET_TRAIT(first_argument_type, );
_MML_DECLARE_GET_TRAIT(second_argument_type, = boost::mpl::na);
_MML_DECLARE_GET_TRAIT(signature, = boost::mpl::na);


#define _MML_GET_ARGN_TYPE(z, n, _)                                         \
    , typename get_arg##n##_type<F>::type                                   \
    /**/


template <typename F>
struct functor_components_over_traits
    : boost::mpl::vector<
          typename F::result_type
        , typename get_first_argument_type<
              F
            , get_arg1_type<
                  F
                , get_argument_type<F>
                >
            >::type
        , typename get_second_argument_type<
              F
            , get_arg2_type<F>
            >::type
        BOOST_PP_REPEAT_FROM_TO(
              3
            , BOOST_PP_INC(MML_MAX_ARITY)
            , _MML_GET_ARGN_TYPE
            ,
            )
        >
{
};


template <typename F>
struct functor_components_over_signature
    : boost::function_types::components<
        typename F::signature
        >::types
{
};


struct _this_marker{};

template <typename F>
struct functor_components_over_call_op_type
    : boost::mpl::remove< // todo: check perfomance and compare with mpl::erase
          typename boost::function_types::components<
              BOOST_TYPEOF_TPL(&F::operator())
            , boost::mpl::always<_this_marker>
            >::types
        , _this_marker
        >::type
{
};


template <typename F>
struct functor_components_impl
    : boost::mpl::if_<
          has_signature<F>
        , functor_components_over_signature<F>
        , typename boost::mpl::if_<
              boost::mpl::or_<
                  has_first_argument_type<F>
                , has_arg1_type<F>
                , has_argument_type<F>
                >
            , functor_components_over_traits<F>
            , functor_components_over_call_op_type<F>
            >::type
        >::type
{
    typedef typename
        functor_components_impl::type types;
    typedef typename boost::mpl::prior<
        boost::mpl::size<types>
        >::type function_arity;
};


template <typename F>
struct functor_components
    : functor_components_impl<
        typename boost::remove_pointer<
            typename boost::remove_reference<F>::type
            >::type
        >
{
    typedef functor_components type;
};


// undef temporaries
#undef _MML_DECLARE_GET_TRAIT
#undef _MML_DECLARE_GET_TRAIT_FOR_ARGN
#undef _MML_GET_ARGN_TYPE

} // namespace detail
} // namespace function_types
} // namespace mml


#endif // _MML_FUNCTION_TYPES_DETAIL_FUNCTOR_COMPONENTS_HPP_INCLUDED_
