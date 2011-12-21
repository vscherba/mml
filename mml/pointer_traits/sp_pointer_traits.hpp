//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_POINTER_TRAITS_SP_POINTER_TRAITS_HPP_INCLUDED_
#define _MML_POINTER_TRAITS_SP_POINTER_TRAITS_HPP_INCLUDED_


#include <boost/shared_ptr.hpp>
#include <mml/pointer_traits/pointer_traits.hpp>


namespace mml {

template <typename T>
struct pointer_traits<boost::shared_ptr<T> >
{
    typedef typename boost::shared_ptr<T>
        ::element_type element_type;

    template <typename U>
    struct rebind
    {
        typedef boost::shared_ptr<U> other;
    };
};

} // namespace mml


#endif // _MML_POINTER_TRAITS_SP_POINTER_TRAITS_HPP_INCLUDED_
