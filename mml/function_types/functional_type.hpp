//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FUNCTION_TYPES_FUNCTIONAL_TYPE_HPP_INCLUDED_
#define _MML_FUNCTION_TYPES_FUNCTIONAL_TYPE_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>

// boost::type_traits
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>

// boost::function_types
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/is_callable_builtin.hpp>

#include <mml/function_types/detail/functor_components_over_traits.hpp>


namespace mml {
namespace function_types {

namespace detail {

    template <typename F>
    struct functional_type_over_traits
        : boost::function_types::function_type<
            functor_components_over_traits<F>
            >
    {
    };


    template <typename F>
    struct functional_type_impl
        : boost::mpl::eval_if<
              boost::function_types::is_callable_builtin<F>
            , boost::mpl::identity<F>
            , get_functional_type<
                  F
                , functional_type_over_traits<F>
                >
            >
    {
    };

} // namespace detail


template <typename F>
struct functional_type
    : detail::functional_type_impl<
        typename boost::remove_pointer<
            typename boost::remove_reference<F>::type
            >::type
        >
{
};

} // namespace function_types
} // namespace mml


#endif // _MML_FUNCTION_TYPES_FUNCTIONAL_TYPE_HPP_INCLUDED_
