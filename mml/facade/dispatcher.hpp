//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FACADE_DISPATCHER_HPP_INCLUDED_
#define _MML_FACADE_DISPATCHER_HPP_INCLUDED_


// boost::call_traits
#include <boost/call_traits.hpp>

#include <mml/basic_dispatcher.hpp>
#include <mml/error_handling/no_err_handler.hpp>
#include <mml/util/first_result_type.hpp>
#include <mml/util/dispatched_to_refineries.hpp>


namespace mml {

template <
      typename OF
    , typename R = typename first_result_type<OF>::type
    , typename RFs = typename dispatched_to_refineries<OF>::type
    , typename EH = no_err_handler<R>
>
class dispatcher
    : public dispatcher_base<OF, R, RFs, EH>
{
    typedef dispatcher_base<OF, R, RFs, EH> base_class;

public:
    typedef typename base_class::dispatched_type dispatched_type;
    typedef typename base_class::err_handler_type err_handler_type;

    dispatcher()
    {
    }

    dispatcher(base_class const& other)
        : base_class(other)
    {
    }

    template <typename R_, typename RFs_, typename EH_>
    explicit dispatcher(dispatcher_base<OF, R_, RFs_, EH_>const& other)
        : base_class(other)
    {
    }

    explicit dispatcher(
        typename boost::call_traits<dispatched_type>::param_type of
        )
        : base_class(of)
    {
    }

    explicit dispatcher(
        typename boost::call_traits<err_handler_type>::param_type eh
        )
        : base_class(eh)
    {
    }

    dispatcher(
          typename boost::call_traits<dispatched_type>::param_type of
        , typename boost::call_traits<err_handler_type>::param_type eh
        )
        : base_class(of, eh)
    {
    }
};

} // namespace mml


#endif // _MML_FACADE_DISPATCHER_HPP_INCLUDED_
