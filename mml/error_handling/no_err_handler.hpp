//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_ERROR_HANDLING_NO_ERR_HANDLER_HPP_INCLUDED_
#define _MML_ERROR_HANDLING_NO_ERR_HANDLER_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>

// boost::call_traits
#include <boost/call_traits.hpp>

#include <mml/config.hpp>


namespace mml {

#if defined(_MSC_VER)
#   define _MML_EXPLICIT_CALL_OPERATOR .operator()
#else
#   define _MML_EXPLICIT_CALL_OPERATOR
#endif

#define _MML_NO_EH_CALL_OP(z, n, _)                                         \
    template <                                                              \
          typename Disp                                                     \
        , typename Err                                                      \
        , BOOST_PP_ENUM_PARAMS(n, typename A)                               \
        >                                                                   \
    R operator()(                                                           \
          Disp& disp                                                        \
        , Err /*err*/                                                       \
        , BOOST_PP_ENUM_BINARY_PARAMS(n, const A, & a)                      \
        ) const                                                             \
    {                                                                       \
        return disp.dispatched()                                            \
            _MML_EXPLICIT_CALL_OPERATOR(BOOST_PP_ENUM_PARAMS(n, a));        \
    }                                                                       \
    /**/


template <typename R>
class no_err_handler
{
public:
    BOOST_PP_REPEAT_FROM_TO(
          1
        , BOOST_PP_INC(MML_MAX_ARITY)
        , _MML_NO_EH_CALL_OP
        ,
        )
};


#define _MML_NO_EH_CALL_OP_VOID(z, n, _)                                    \
    template <                                                              \
          typename Disp                                                     \
        , typename Err                                                      \
        , BOOST_PP_ENUM_PARAMS(n, typename A)                               \
        >                                                                   \
    void operator()(                                                        \
          Disp& disp                                                        \
        , Err                                                               \
        , BOOST_PP_ENUM_BINARY_PARAMS(n, const A, & a)                      \
        ) const                                                             \
    {                                                                       \
        disp.dispatched()                                                   \
            _MML_EXPLICIT_CALL_OPERATOR(BOOST_PP_ENUM_PARAMS(n, a));        \
    }                                                                       \
    /**/


template <>
class no_err_handler<void>
{
public:
    BOOST_PP_REPEAT_FROM_TO(
          1
        , BOOST_PP_INC(MML_MAX_ARITY)
        , _MML_NO_EH_CALL_OP_VOID
        ,
        )
};


// undefs
#undef _MML_EXPLICIT_CALL_OPERATOR
#undef _MML_NO_EH_CALL_OP
#undef _MML_NO_EH_CALL_OP_VOID

} // namespace mml


#endif // _MML_ERROR_HANDLING_NO_ERR_HANDLER_HPP_INCLUDED_
