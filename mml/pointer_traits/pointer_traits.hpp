//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_POINTER_TRAITS_POINTER_TRAITS_HPP_INCLUDED_
#define _MML_POINTER_TRAITS_POINTER_TRAITS_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>

// boost::type_traits
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace mml {

namespace detail
{
    struct not_pointer_tag{};
}


// common
template <typename P>
struct pointer_traits
    : detail::not_pointer_tag
{
    typedef P element_type;
};


// builtin
template <typename T>
struct pointer_traits<T*>
{
    typedef T element_type;

    template <typename U>
    struct rebind
    {
        typedef U* other;
    };
};


template <typename P>
struct pointer_traits_specified
    : boost::mpl::not_<
        boost::is_convertible<
              pointer_traits<
                typename boost::remove_cv<
                    typename boost::remove_reference<P>::type
                    >::type
                >
            , detail::not_pointer_tag
            >
        >
{
};


template <typename T>
struct param_optimization
{
    typedef boost::mpl::or_<
          boost::mpl::bool_<(sizeof(T) > 2*sizeof(void*))>
        , boost::mpl::not_<boost::is_pod<T> >
        > pass_by_ref;
};

} // namespace mml


#endif // _MML_POINTER_TRAITS_POINTER_TRAITS_HPP_INCLUDED_
