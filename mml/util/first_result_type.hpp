//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_UTIL_FIRST_RESULT_TYPE_HPP_INCLUDED_
#define _MML_UTIL_FIRST_RESULT_TYPE_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/front.hpp>

// boost::type_traits
#include <boost/type_traits/remove_reference.hpp>

// boost::function_types
#include <boost/function_types/result_type.hpp>


namespace mml {

template <typename Signatures>
struct first_result_type_from_signatures
    : boost::function_types::result_type<
        typename boost::mpl::front<
            Signatures
            >::type
        >
{
};


template <typename OF>
struct first_result_type
    : first_result_type_from_signatures<
        typename boost::remove_reference<
            OF
            >::type::signatures
        >
{
};

} // namespace mml


#endif // _MML_UTIL_FIRST_RESULT_TYPE_HPP_INCLUDED_
