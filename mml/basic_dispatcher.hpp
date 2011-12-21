//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_DISPATCHER_HPP_INCLUDED_
#define _MML_DISPATCHER_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

// boost::mpl
#include <boost/mpl/front.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/less.hpp>

// boost::type_traits
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_volatile.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_void.hpp>

// boost::call_traits
#include <boost/call_traits.hpp>

// boost::compressed_pair
#include <boost/compressed_pair.hpp>

#include <mml/config.hpp>
#include <mml/pointer_traits/pointer_traits.hpp>
#include <mml/detail/pointer_traits_ex.hpp>
#include <mml/error_handling/no_err_handler.hpp>


#ifndef MML_ENABLE_TRACE
#   if defined(DEBUG) || defined(_DEBUG)
#       define MML_ENABLE_TRACE 1
#   else
#       define MML_ENABLE_TRACE 0
#   endif // defined(DEBUG) || defined(_DEBUG)
#endif // !defined MML_ENABLE_TRACE


#if MML_ENABLE_TRACE
#   define MML_TRACE(align, text) mml_trace(align, text);
#   include <string>

#   ifdef _MSC_VER
#       include <windows.h>
#   endif

    namespace mml {
    namespace detail {
        inline void mml_trace(std::size_t align, const std::string& text)
        {
            std::string out = "mml: ";
            out.append(align, '\t');
            out += text;
            out += '\n';
#   ifdef _MSC_VER
            ::OutputDebugStringA(out.c_str());
#   endif
        }
    } // namespace detail
    } // namespace mml

#else
#   define MML_TRACE(align, text)
#endif // MML_ENABLE_TRACE


namespace mml {

namespace detail {

    template <typename T, typename U>
    struct add_same_qualifiers_as
    {
    private:
        typedef typename
        boost::mpl::if_<
              boost::is_const<T>
            , U const
            , U
            >::type const_type;
    public:
        typedef typename
        boost::mpl::if_<
              boost::is_volatile<T>
            , volatile const_type
            , const_type
            >::type type;
    };


    template <
          typename Caster
        , typename SrcCaster
        , bool IsCastable
            = boost::is_convertible<SrcCaster, Caster>::value
        >
    struct caster_ex
        : Caster
    {
        caster_ex(SrcCaster const& /*other*/)
        {
        }
    };


    template <typename Caster>
    struct caster_ex<Caster, boost::mpl::na const, true>
        : Caster
    {
        caster_ex(boost::mpl::na /*other*/)
        {
        }
    };


    template <typename Caster, typename SrcCaster>
    struct caster_ex<Caster, SrcCaster, true>
        : Caster
    {
        caster_ex(SrcCaster const& other)
            : Caster(other)
        {
        }
    };


    struct disp_arg_refine_tag{};
    struct disp_arg_invoke_tag{};
    struct disp_arg_invoke_void_tag{};
    struct disp_arg_handle_err_tag{};
    struct disp_arg_start_refine_tag{};
    struct disp_arg_skip_refine_tag{};
    struct disp_type_static_refine_tag{};
    struct disp_type_dynamic_refine_tag{};
    struct disp_type_no_refine_tag{};
    struct disp_type_refine_tag{};
    struct disp_type_end_of_types_tag{};


#ifdef _MSC_VER
#   define _MML_EXPLICIT_CALL_OPERATOR .operator()
#else
#   define _MML_EXPLICIT_CALL_OPERATOR
#endif // _MSC_VER


#define BOOST_PP_ITERATION_PARAMS_1                                         \
    (3, (1, MML_MAX_ARITY, <mml/detail/engine.hpp>))                        \
    /**/

#include BOOST_PP_ITERATE()

} // namespace detail


#define _MML_MAX_ARITY_INC BOOST_PP_INC(MML_MAX_ARITY)

#define _MML_DISPATCHER_CORRECT_PARAM_TYPE(z, n, _)                         \
    typename detail::pointer_traits_ex<A##n>::param_type                    \
    /**/

#define _MML_DISPATCHER_CALL_OP(z, n, const_keyword)                        \
    template <BOOST_PP_ENUM_PARAMS(n, typename A)>                          \
    result_type operator()(                                                 \
        BOOST_PP_ENUM_BINARY_PARAMS(n, const A, & a)                        \
        ) const_keyword                                                     \
    {                                                                       \
        return                                                              \
        detail::engine##n<                                                  \
              dispatcher_base const_keyword                                 \
            , 0                                                             \
            , BOOST_PP_ENUM(n, _MML_DISPATCHER_CORRECT_PARAM_TYPE, )        \
            , 0x0                                                           \
            >::dispatch_arg(                                                \
                  detail::disp_arg_refine_tag()                             \
                , *this                                                     \
                , BOOST_PP_ENUM_PARAMS(n, a)                                \
                );                                                          \
    }                                                                       \
    /**/


// fwd
template <
      typename OF
    , typename R
    , typename RFs
    , typename EH = no_err_handler<R>
    >
class basic_dispatcher;


template <
      typename OF
    , typename R
    , typename RFs
    , typename EH = no_err_handler<R>
    >
class dispatcher_base
{
public:
    typedef OF dispatched_type;
    typedef R result_type;
    typedef RFs refineries;
    typedef EH err_handler_type;

    typename boost::call_traits<dispatched_type>::reference
    dispatched()
    {
        return _contained.first();
    }

    typename boost::call_traits<dispatched_type>::const_reference
    dispatched() const
    {
        return const_cast<dispatcher_base*>(this)->dispatched();
    }

    typename boost::call_traits<err_handler_type>::reference
    err_handler()
    {
        return _contained.second();
    }

    typename boost::call_traits<err_handler_type>::const_reference
    err_handler() const
    {
        return const_cast<dispatcher_base*>(this)->err_handler();
    }

    template <typename R_>
    basic_dispatcher<
          dispatched_type
        , R_
        , refineries
        , err_handler_type
        >
    switch_ret() const
    {
        return
        basic_dispatcher<
              dispatched_type
            , R_
            , refineries
            , err_handler_type
            >(*this);
    }

    template <typename RFs_>
    basic_dispatcher<
          dispatched_type
        , result_type
        , RFs_
        , err_handler_type
        >
    switch_refineries() const
    {
        return
        basic_dispatcher<
              dispatched_type
            , result_type
            , RFs_
            , err_handler_type
            >(*this);
    }

    template <typename EH_>
    basic_dispatcher<
          dispatched_type
        , result_type
        , refineries
        , EH_
        >
    switch_err_handler() const
    {
        return
        basic_dispatcher<
              dispatched_type
            , result_type
            , refineries
            , EH_
            >(*this);
    }

    template <typename EH_>
    basic_dispatcher<
          dispatched_type
        , result_type
        , refineries
        , EH_
        >
    switch_err_handler(EH_ const& eh) const
    {
        return
        basic_dispatcher<
              dispatched_type
            , result_type
            , refineries
            , EH_
            >(dispatched(), eh);
    }

    result_type operator()()
    {
        return invoke(typename boost::is_void<result_type>::type());
    }

    result_type operator()() const
    {
        return invoke(typename boost::is_void<result_type>::type());
    }

    BOOST_PP_REPEAT_FROM_TO(
          1
        , _MML_MAX_ARITY_INC
        , _MML_DISPATCHER_CALL_OP
        ,
        )

    BOOST_PP_REPEAT_FROM_TO(
          1
        , _MML_MAX_ARITY_INC
        , _MML_DISPATCHER_CALL_OP
        , const
        )

protected:
    dispatcher_base()
    {
    }

    template <typename R_, typename RFs_>
    explicit dispatcher_base(
        dispatcher_base<
              dispatched_type
            , R_
            , RFs_
            , err_handler_type
            > const& other
        )
        : _contained(other.dispatched(), other.err_handler())
    {
    }

    template <typename R_, typename RFs_, typename EH_>
    explicit dispatcher_base(
        dispatcher_base<
              dispatched_type
            , R_
            , RFs_
            , EH_
            > const& other
        )
        : _contained(other.dispatched())
    {
    }

    explicit dispatcher_base(
        typename boost::call_traits<dispatched_type>::param_type of
        )
        : _contained(of)
    {
    }

    explicit dispatcher_base(
        typename boost::call_traits<err_handler_type>::param_type eh
        )
        : _contained(eh)
    {
    }

    dispatcher_base(
          typename boost::call_traits<dispatched_type>::param_type of
        , typename boost::call_traits<err_handler_type>::param_type eh
        )
        : _contained(of, eh)
    {
    }

    ~dispatcher_base()
    {
    }

private:
    result_type invoke(boost::false_type)
    {
        return dispatched()();
    }

    result_type invoke(boost::false_type) const
    {
        return dispatched()();
    }

    void invoke(boost::true_type)
    {
        dispatched()();
    }

    void invoke(boost::true_type) const
    {
        dispatched()();
    }

    boost::compressed_pair<dispatched_type, err_handler_type> _contained;
};


template <
      typename OF
    , typename R
    , typename RFs
    , typename EH
    >
class basic_dispatcher
    : public dispatcher_base<OF, R, RFs, EH>
{
    typedef dispatcher_base<OF, R, RFs, EH> base_class;

public:
    typedef typename base_class::dispatched_type dispatched_type;
    typedef typename base_class::err_handler_type err_handler_type;

    basic_dispatcher()
    {
    }

    basic_dispatcher(base_class const& other)
        : base_class(other)
    {
    }

    template <typename R_, typename RFs_, typename EH_>
    explicit
    basic_dispatcher(dispatcher_base<OF, R_, RFs_, EH_> const& other)
        : base_class(other)
    {
    }

    explicit basic_dispatcher(
        typename boost::call_traits<dispatched_type>::param_type of
        )
        : base_class(of)
    {
    }

    explicit basic_dispatcher(
        typename boost::call_traits<err_handler_type>::param_type eh
        )
        : base_class(eh)
    {
    }

    basic_dispatcher(
          typename boost::call_traits<dispatched_type>::param_type of
        , typename boost::call_traits<err_handler_type>::param_type eh
        )
        : base_class(of, eh)
    {
    }
};

} // namespace mml


// undefs
#undef _MML_EXPLICIT_CALL_OPERATOR
#undef BOOST_PP_ITERATION_PARAMS_1
#undef _MML_MAX_ARITY_INC
#undef _MML_DISPATCHER_CORRECT_PARAM_TYPE
#undef _MML_DISPATCHER_CALL_OP


#endif // _MML_DISPATCHER_HPP_INCLUDED_
