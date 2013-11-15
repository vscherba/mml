//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/comparison/equal.hpp>

// boost::type_traits
#include <boost/type_traits/is_convertible.hpp>

// boost::call_traits
#include <boost/call_traits.hpp>

#include <mml/config.hpp>
#include <mml/inline_overloaded_fn/inline_overloaded_fn.hpp>
#include <mml/util/dispatched_to_refineries.hpp>
#include <mml/facade/detail/with_policies.hpp>
#include <mml/function_types/result_type.hpp>


namespace mml {

#define _MML_MULTIMETHOD_TEMPLATE_FACT_PARAM_LIST                           \
    BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, F)                     \
    /**/

#define _MML_MULTIMETHOD_CONSTRUCTOR_FORMAL_PARAM(z, n, _)                  \
    typename boost::call_traits<F##n>::param_type f##n                      \
    /**/

#define _MML_MULTIMETHOD_CONSTRUCTOR(z, n, _)                               \
    BOOST_PP_IF(BOOST_PP_EQUAL(n, 1), explicit, )                           \
    _MML_FACADE_NAME(                                                       \
        BOOST_PP_ENUM(n, _MML_MULTIMETHOD_CONSTRUCTOR_FORMAL_PARAM, )       \
        )                                                                   \
        : base_class(_dispatched_type(BOOST_PP_ENUM_PARAMS(n, f)))          \
    {                                                                       \
    }                                                                       \
    /**/


template <
    BOOST_PP_ENUM_BINARY_PARAMS(
          BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
        , typename F
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
class _MML_FACADE_NAME
    : public _MML_FACADE_BASE_CLASS_NAME<
          inline_overloaded_fn<_MML_MULTIMETHOD_TEMPLATE_FACT_PARAM_LIST>
        , typename function_types::result_type<F0>::type
        , typename dispatched_to_refineries<
              inline_overloaded_fn<_MML_MULTIMETHOD_TEMPLATE_FACT_PARAM_LIST>
            , dynamic_caster
            , dynamic_downcast_allowed
            , implicit_caster
            , boost::is_convertible
            , most_derived
            , _MML_FACADE_PARAM_FILTER
            >::type
        >
{
    typedef _MML_FACADE_BASE_CLASS_NAME<
          typename _MML_FACADE_NAME::dispatched_type
        , typename _MML_FACADE_NAME::result_type
        , typename _MML_FACADE_NAME::refineries
        > base_class;

    typedef typename base_class::dispatched_type _dispatched_type;

public:
    _MML_FACADE_NAME(base_class const& other)
        : base_class(other)
    {
    }

    template <typename R_, typename RFs_, typename EH_>
    explicit _MML_FACADE_NAME(
        _MML_FACADE_BASE_CLASS_NAME<
            _dispatched_type, R_, RFs_, EH_
            > const& other
        )
        : base_class(other)
    {
    }

    BOOST_PP_REPEAT(
          BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
        , _MML_MULTIMETHOD_CONSTRUCTOR
        ,
        )
};


template <
      typename R
    , template<typename, typename> class DynCaster
    , template<typename, typename> class DynCastablePred
    , template<typename, typename> class StatCaster
    , template<typename, typename> class StatCastablePred
    , template<typename, typename> class OrderingPred
    , BOOST_PP_ENUM_PARAMS(MML_MAX_FUNCTION_OVERLOADS, typename F)
>
class _MML_FACADE_NAME<
      with_policies<
          R
        , DynCaster
        , DynCastablePred
        , StatCaster
        , StatCastablePred
        , OrderingPred
        >
    , _MML_MULTIMETHOD_TEMPLATE_FACT_PARAM_LIST
    >
    : public _MML_FACADE_BASE_CLASS_NAME<
          inline_overloaded_fn<_MML_MULTIMETHOD_TEMPLATE_FACT_PARAM_LIST>
        , R
        , typename dispatched_to_refineries<
              inline_overloaded_fn<_MML_MULTIMETHOD_TEMPLATE_FACT_PARAM_LIST>
            , DynCaster
            , DynCastablePred
            , StatCaster
            , StatCastablePred
            , OrderingPred
            , _MML_FACADE_PARAM_FILTER
            >::type
        >
{
    typedef _MML_FACADE_BASE_CLASS_NAME<
          typename _MML_FACADE_NAME::dispatched_type
        , typename _MML_FACADE_NAME::result_type
        , typename _MML_FACADE_NAME::refineries
        > base_class;

    typedef typename base_class::dispatched_type _dispatched_type;

public:
    _MML_FACADE_NAME(base_class const& other)
        : base_class(other)
    {
    }

    template <typename R_, typename RFs_, typename EH_>
    explicit _MML_FACADE_NAME(
        _MML_FACADE_BASE_CLASS_NAME<
            _dispatched_type, R_, RFs_, EH_
            > const& other
        )
        : base_class(other)
    {
    }

    BOOST_PP_REPEAT(
          BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
        , _MML_MULTIMETHOD_CONSTRUCTOR
        ,
        )
};


// undefs
#undef _MML_MULTIMETHOD_TEMPLATE_FACT_PARAM_LIST
#undef _MML_MULTIMETHOD_CONSTRUCTOR_FORMAL_PARAM
#undef _MML_MULTIMETHOD_CONSTRUCTOR

} // namespace mml
