//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_ADAPTER_BASIC_REF_DISPATCHER_HPP_INCLUDED_
#define _MML_ADAPTER_BASIC_REF_DISPATCHER_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

// boost::call_traits
#include <boost/call_traits.hpp>

#include <mml/config.hpp>
#include <mml/basic_dispatcher.hpp>
#include <mml/error_handling/no_err_handler.hpp>


namespace mml {

namespace detail {

#define _MML_MAX_ARITY_INC BOOST_PP_INC(MML_MAX_ARITY)

#if defined(_MSC_VER)
#   define _MML_EXPLICIT_CALL_OPERATOR .operator()
#else
#   define _MML_EXPLICIT_CALL_OPERATOR
#endif

#define _MML_REF_OFUNCTION_ADAPTER_CALL_OP(z, n, _)                         \
    template <BOOST_PP_ENUM_PARAMS(n, typename A)>                          \
    R operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, * a))                    \
    {                                                                       \
        return OF::operator()(BOOST_PP_ENUM_PARAMS(n, *a));                 \
    }                                                                       \
                                                                            \
    template <BOOST_PP_ENUM_PARAMS(n, typename A)>                          \
    R operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, * a)) const              \
    {                                                                       \
        return OF::operator()(BOOST_PP_ENUM_PARAMS(n, *a));                 \
    }                                                                       \
    /**/


    template <typename OF, typename R>
    struct overloaded_function_ref_adapter
        : OF
    {
        overloaded_function_ref_adapter()
        {
        }

        overloaded_function_ref_adapter(
            typename boost::call_traits<OF>::param_type of
            )
            : OF(of)
        {
        }

        R operator()()
        {
            return OF::operator()();
        }

        R operator()() const
        {
            return OF::operator()();
        }

        BOOST_PP_REPEAT_FROM_TO(
              1
            , _MML_MAX_ARITY_INC
            , _MML_REF_OFUNCTION_ADAPTER_CALL_OP
            ,
            )
    };


#define _MML_REF_OFUNCTION_ADAPTER_CALL_OP_VOID(z, n, _)                    \
    template <BOOST_PP_ENUM_PARAMS(n, typename A)>                          \
    void operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, * a))                 \
    {                                                                       \
        OF::operator()(BOOST_PP_ENUM_PARAMS(n, *a));                        \
    }                                                                       \
                                                                            \
    template <BOOST_PP_ENUM_PARAMS(n, typename A)>                          \
    void operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, * a)) const           \
    {                                                                       \
        OF::operator()(BOOST_PP_ENUM_PARAMS(n, *a));                        \
    }                                                                       \
    /**/


    template <typename OF>
    struct overloaded_function_ref_adapter<OF, void>
        : OF
    {
        overloaded_function_ref_adapter()
        {
        }

        overloaded_function_ref_adapter(
            typename boost::call_traits<OF>::param_type of
            )
            : OF(of)
        {
        }

        void operator()()
        {
            OF::operator()();
        }

        void operator()() const
        {
            OF::operator()();
        }

        BOOST_PP_REPEAT_FROM_TO(
              1
            , _MML_MAX_ARITY_INC
            , _MML_REF_OFUNCTION_ADAPTER_CALL_OP_VOID
            ,
            )
    };

} // namespace detail


#define _MML_REF_DISPATCHER_CALL_OP(z, n, _)                                \
    template <BOOST_PP_ENUM_PARAMS(n, typename A)>                          \
    R operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a))                    \
    {                                                                       \
        return _contained(BOOST_PP_ENUM_PARAMS(n, &a));                     \
    }                                                                       \
                                                                            \
    template <BOOST_PP_ENUM_PARAMS(n, typename A)>                          \
    R operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const              \
    {                                                                       \
        return _contained(BOOST_PP_ENUM_PARAMS(n, &a));                     \
    }                                                                       \
    /**/


// fwd
template <
      typename OF
    , typename R
    , typename RFs
    , typename EH = no_err_handler<R>
>
class basic_ref_dispatcher;


template <
      typename OF
    , typename R
    , typename RFs
    , typename EH = no_err_handler<R>
>
class ref_dispatcher_base
{
public:
    typedef basic_dispatcher<
          detail::overloaded_function_ref_adapter<OF, R>
        , R
        , RFs
        , EH
        > dispatcher_type;

    typedef OF dispatched_type;
    typedef typename dispatcher_type::result_type result_type;
    typedef typename dispatcher_type::refineries refineries;
    typedef typename dispatcher_type::err_handler_type err_handler_type;

    dispatcher_type as_dispatcher()
    {
        return _contained;
    }

    typename boost::call_traits<dispatched_type>::reference
    dispatched()
    {
        return _contained.dispatched();
    }

    typename boost::call_traits<dispatched_type>::const_reference
    dispatched() const
    {
        return const_cast<ref_dispatcher_base*>(this)->dispatched();
    }

    typename boost::call_traits<err_handler_type>::reference
    err_handler()
    {
        return _contained.err_handler();
    }

    typename boost::call_traits<err_handler_type>::const_reference
    err_handler() const
    {
        return const_cast<ref_dispatcher_base*>(this)->err_handler();
    }

    template <typename R_>
    basic_ref_dispatcher<
          dispatched_type
        , R_
        , refineries
        , err_handler_type
        >
    switch_ret() const
    {
        return
        basic_ref_dispatcher<
              dispatched_type
            , R_
            , refineries
            , err_handler_type
            >(*this);
    }

    template <typename RFs_>
    basic_ref_dispatcher<
          dispatched_type
        , result_type
        , RFs_
        , err_handler_type
        >
    switch_refineries() const
    {
        return
        basic_ref_dispatcher<
              dispatched_type
            , result_type
            , RFs_
            , err_handler_type
            >(*this);
    }

    template <typename EH_>
    basic_ref_dispatcher<
          dispatched_type
        , result_type
        , refineries
        , EH_
        >
    switch_err_handler() const
    {
        return
        basic_ref_dispatcher<
              dispatched_type
            , result_type
            , refineries
            , EH_
            >(*this);
    }

    template <typename EH_>
    basic_ref_dispatcher<
          dispatched_type
        , result_type
        , refineries
        , EH_
        >
    switch_err_handler(EH_ const& eh) const
    {
        return
        basic_ref_dispatcher<
              dispatched_type
            , result_type
            , refineries
            , EH_
            >(dispatched(), eh);
    }

    result_type operator()()
    {
        return _contained();
    }

    result_type operator()() const
    {
        return _contained();
    }

    BOOST_PP_REPEAT_FROM_TO(
          1
        , _MML_MAX_ARITY_INC
        , _MML_REF_DISPATCHER_CALL_OP
        ,
        )

protected:
    ref_dispatcher_base()
    {
    }

    template <typename R_, typename RFs_>
    explicit ref_dispatcher_base(
        ref_dispatcher_base<
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
    explicit ref_dispatcher_base(
        ref_dispatcher_base<
              dispatched_type
            , R_
            , RFs_
            , EH_
            > const& other
        )
        : _contained(other.dispatched())
    {
    }

    explicit ref_dispatcher_base(
        typename boost::call_traits<dispatched_type>::param_type of
        )
        : _contained(of)
    {
    }

    explicit ref_dispatcher_base(
        typename boost::call_traits<err_handler_type>::param_type eh
        )
        : _contained(eh)
    {
    }

    ref_dispatcher_base(
          typename boost::call_traits<dispatched_type>::param_type of
        , typename boost::call_traits<err_handler_type>::param_type eh
        )
        : _contained(of, eh)
    {
    }

private:
    dispatcher_type _contained;
};


template <
      typename OF
    , typename R
    , typename RFs
    , typename EH
>
class basic_ref_dispatcher
    : public ref_dispatcher_base<OF, R, RFs, EH>
{
    typedef ref_dispatcher_base<OF, R, RFs, EH> base_class;

public:
    typedef typename base_class::dispatched_type dispatched_type;
    typedef typename base_class::err_handler_type err_handler_type;

    basic_ref_dispatcher()
    {
    }

    basic_ref_dispatcher(const base_class& other)
        : base_class(other)
    {
    }

    template <typename R_, typename RFs_, typename EH_>
    explicit basic_ref_dispatcher(
        ref_dispatcher_base<OF, R_, RFs_, EH_> const& other
        )
        : base_class(other)
    {
    }

    explicit basic_ref_dispatcher(
        typename boost::call_traits<dispatched_type>::param_type of
        )
        : base_class(of)
    {
    }

    explicit basic_ref_dispatcher(
        typename boost::call_traits<err_handler_type>::param_type eh
        )
        : base_class(eh)
    {
    }

    basic_ref_dispatcher(
          typename boost::call_traits<dispatched_type>::param_type of
        , typename boost::call_traits<err_handler_type>::param_type eh
        )
        : base_class(of, eh)
    {
    }
};

} // namespace mml


// undefs
#undef _MML_MAX_ARITY_INC
#undef _MML_EXPLICIT_CALL_OPERATOR
#undef _MML_REF_OFUNCTION_ADAPTER_CALL_OP
#undef _MML_REF_OFUNCTION_ADAPTER_CALL_OP_VOID
#undef _MML_REF_DISPATCHER_CALL_OP


#endif // _MML_ADAPTER_BASIC_REF_DISPATCHER_HPP_INCLUDED_
