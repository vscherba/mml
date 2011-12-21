//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_FUNCTION_TYPES_COMPONENTS_HPP_INCLUDED_
#define _MML_FUNCTION_TYPES_COMPONENTS_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/if.hpp>

// boost::function_types
#include <boost/function_types/components.hpp>
#include <boost/function_types/is_callable_builtin.hpp>

#include <mml/function_types/detail/functor_components_over_traits.hpp>


namespace mml {
namespace function_types {

namespace detail {

    template <typename F>
    struct functor_components_over_fn_type
        : boost::function_types::components<
            typename F::functional_type
            >
    {
    };

    template <typename F>
    struct functor_components
        : boost::mpl::if_<
              has_functional_type<F>
            , functor_components_over_fn_type<F>
            , functor_components_over_traits<F>
            >::type
    {
    };

} // namespace detail

template <typename F>
struct components
    : boost::mpl::if_<
          boost::function_types::is_callable_builtin<F>
        , boost::function_types::components<F>
        , detail::functor_components<F>
        >::type
{
    typedef components type;
};

} // namespace function_types
} // namespace mml


#endif // _MML_FUNCTION_TYPES_COMPONENTS_HPP_INCLUDED_
