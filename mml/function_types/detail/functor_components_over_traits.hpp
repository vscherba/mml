//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FUNCTION_TYPES_DETAIL_FUNCTOR_COMPONENTS_OVER_TRAITS_HPP_INCLUDED_
#define _MML_FUNCTION_TYPES_DETAIL_FUNCTOR_COMPONENTS_OVER_TRAITS_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

// boost::mpl
#include <boost/mpl/has_xxx.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/eval_if.hpp>

// boost::type_traits
#include <boost/type_traits/remove_reference.hpp>

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
_MML_DECLARE_GET_TRAIT(functional_type, = boost::mpl::na);


#define _MML_GET_ARGN_TYPE(z, n, _)                                         \
    , typename get_arg##n##_type<F>::type                                   \
    /**/


template <typename F>
struct functor_components_over_traits_impl
{
private:
    typedef typename boost::remove_reference<F>::type functor_type;

public:
    typedef boost::mpl::vector<
          typename functor_type::result_type
        , typename get_arg1_type<
              functor_type
            , get_first_argument_type<
                  functor_type
                , get_argument_type<functor_type>
                >
            >::type
        , typename get_arg2_type<
              functor_type
            , get_second_argument_type<functor_type>
            >::type
        BOOST_PP_REPEAT_FROM_TO(
              3
            , BOOST_PP_INC(MML_MAX_ARITY)
            , _MML_GET_ARGN_TYPE
            ,
            )
        > types;
};


template <typename F>
struct functor_components_over_traits
    : functor_components_over_traits_impl<F>::types
{
    typedef typename
        functor_components_over_traits_impl<F>::types types;
    typedef typename boost::mpl::prior<
        boost::mpl::size<types>
        >::type function_arity;
};


// undef temporaries
#undef _MML_DECLARE_GET_TRAIT
#undef _MML_DECLARE_GET_TRAIT_FOR_ARGN
#undef _MML_GET_ARGN_TYPE

} // namespace detail
} // namespace function_types
} // namespace mml


#endif // _MML_FUNCTION_TYPES_DETAIL_FUNCTOR_COMPONENTS_OVER_TRAITS_HPP_INCLUDED_
