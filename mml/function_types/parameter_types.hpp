//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FUNCTION_TYPES_PARAMETER_TYPES_HPP_INCLUDED_
#define _MML_FUNCTION_TYPES_PARAMETER_TYPES_HPP_INCLUDED_


#include <mml/function_types/components.hpp>


namespace mml {
namespace function_types {

template <typename F>
struct parameter_types
    : boost::mpl::pop_front<
        typename components<F>::types
        >
{
};

} // namespace mml
} // namespace function_types


#endif // _MML_FUNCTION_TYPES_PARAMETER_TYPES_HPP_INCLUDED_
