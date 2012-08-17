//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FUNCTION_TYPES_FUNCTION_TYPE_HPP_INCLUDED_
#define _MML_FUNCTION_TYPES_FUNCTION_TYPE_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/is_sequence.hpp>

// boost::type_traits
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_pointer.hpp>

// boost::function_types
#include <boost/function_types/function_type.hpp>
#include <boost/function_types/is_callable_builtin.hpp>

#include <mml/function_types/detail/functor_components.hpp>


namespace mml {
namespace function_types {

namespace detail {

    template <typename F>
    struct function_type_over_functor
        : boost::function_types::function_type<
            functor_components<F>
            >
    {
    };


    template <typename T>
    struct function_type_impl
        : boost::mpl::if_<
              boost::function_types::is_callable_builtin<T>
            , boost::mpl::identity<T>
            , typename boost::mpl::if_<
                  boost::mpl::is_sequence<T>
                , boost::function_types::function_type<T>
                , get_signature<
                      T
                    , function_type_over_functor<T>
                    >
                >::type
            >::type
    {
    };

} // namespace detail


template <typename T>
struct function_type
    : detail::function_type_impl<
        typename boost::remove_pointer<
            typename boost::remove_reference<T>::type
            >::type
        >
{
};

} // namespace function_types
} // namespace mml


#endif // _MML_FUNCTION_TYPES_FUNCTION_TYPE_HPP_INCLUDED_
