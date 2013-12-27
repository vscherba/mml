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
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

// boost::mpl
#include <boost/mpl/at.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/find.hpp>

// boost::call_traits
#include <boost/call_traits.hpp>

#include <mml/config.hpp>
#include <mml/inline_overloaded_fn/detail/inline_overloaded_fn_base.hpp>


#ifdef MML_RESULT_OF_SUPPORT_ON
#   include <mml/result_of_support/result_of_support.hpp>
#   include <mml/function_types/function_type.hpp>

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


#   define _MML_IOF_CREATE_SIGNATURE(z, n, _)                               \
        typename detail::create_signature<F##n>::type                       \
    /**/

} // namespace detail
} // namespace mml
#endif // MML_RESULT_OF_SUPPORT_ON


namespace mml {

#define _MML_IOF_CONSTRUCTOR_FORMAL_PARAM(z, n, _)                          \
    typename boost::call_traits<F##n>::param_type f##n                      \
    /**/

#define _MML_IOF_CONSTRUCTOR(z, n, _)                                       \
    explicit inline_overloaded_fn(                                          \
        BOOST_PP_ENUM(                                                      \
              n                                                             \
            , _MML_IOF_CONSTRUCTOR_FORMAL_PARAM                             \
            ,                                                               \
            )                                                               \
        )                                                                   \
        : _targets(BOOST_PP_ENUM_PARAMS(n, f))                              \
    {                                                                       \
    }                                                                       \
    /**/


#define _MML_IOF_TEMPLATE_FACT_PARAM_LIST                                   \
    BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, F)                     \
    /**/


template <
    BOOST_PP_ENUM_BINARY_PARAMS(
          MML_MAX_FUNCTION_OVERLOADS
        , typename F
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
class inline_overloaded_fn
    : private detail::inline_overloaded_fn_base<
          inline_overloaded_fn<_MML_IOF_TEMPLATE_FACT_PARAM_LIST>
        , _MML_IOF_TEMPLATE_FACT_PARAM_LIST
        >
#ifdef MML_RESULT_OF_SUPPORT_ON
    , public mml::result_of_support<
        BOOST_PP_ENUM(MML_MAX_FUNCTION_OVERLOADS, _MML_IOF_CREATE_SIGNATURE, )
        >
#   undef _MML_IOF_CREATE_SIGNATURE
#endif // MML_RESULT_OF_SUPPORT_ON
{
    template <typename Derived, typename Targets, long N, long Arity>
    friend class detail::target_invoker;

    typedef detail::inline_overloaded_fn_base<
          inline_overloaded_fn<_MML_IOF_TEMPLATE_FACT_PARAM_LIST>
        , _MML_IOF_TEMPLATE_FACT_PARAM_LIST
        > base_class;

public:
    typedef typename base_class::types types;
    using base_class::signatures;
    using base_class::operator();

    BOOST_PP_REPEAT(
          BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
        , _MML_IOF_CONSTRUCTOR
        ,
        )

    template <long N>
    typename boost::call_traits<
        typename boost::mpl::at_c<types, N>::type
        >::reference
    target()
    {
#ifdef MML_COMPRESSION_OFF
        return boost::fusion::at_c<N>(_targets);
#else
        return _targets.template get<N>();
#endif
    }

    template <long N>
    typename boost::call_traits<
        typename boost::mpl::at_c<types, N>::type
        >::const_reference
    target() const
    {
        return const_cast<inline_overloaded_fn*>(this)
            ->template target<N>();
    }

    template <typename F>
    typename boost::call_traits<F>::reference
    target()
    {
        namespace _bmpl = boost::mpl;
        return target<
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
    target() const
    {
        return const_cast<inline_overloaded_fn*>(this)
            ->template target<F>();
    }

private:
    typename base_class::tuple_type _targets;
};

} // namespace mml


// undef temporaries
#undef _MML_IOF_CONSTRUCTOR_FORMAL_PARAM
#undef _MML_IOF_CONSTRUCTOR
#undef _MML_IOF_TEMPLATE_FACT_PARAM_LIST


#endif // _MML_INLINE_OVERLOADED_FN_INLINE_OVERLOADED_FN_HPP_INCLUDED_
