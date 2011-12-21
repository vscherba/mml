//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_DETAIL_POINTER_TRAITS_EX_HPP_INCLUDED_
#define _MML_DETAIL_POINTER_TRAITS_EX_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/if.hpp>

// boost::type_traits
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>

#include <mml/pointer_traits/pointer_traits.hpp>


namespace mml {
namespace detail {

template <typename P>
struct pointer_traits_ex
    : pointer_traits<
        typename boost::remove_cv<
            typename boost::remove_reference<P>::type
            >::type
        >
{
    typedef typename
        boost::remove_cv<
            typename boost::remove_reference<P>::type
            >::type pointer_type;

    typedef typename
        boost::mpl::if_<
              typename param_optimization<pointer_type>::pass_by_ref
            , pointer_type const&
            , pointer_type
            >::type param_type;
};

} // namespace mml
} // namespace detail


#endif // _MML_DETAIL_POINTER_TRAITS_EX_HPP_INCLUDED_
