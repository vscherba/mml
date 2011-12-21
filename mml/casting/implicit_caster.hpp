//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_CASTING_IMPLICIT_CASTER_HPP_INCLUDED_
#define _MML_CASTING_IMPLICIT_CASTER_HPP_INCLUDED_


#include <mml/detail/pointer_traits_ex.hpp>


namespace mml {

template <typename From, typename /*To*/>
class implicit_caster
{
    typedef typename
        detail::pointer_traits_ex<From>::param_type param_type;
public:
    static param_type cast(param_type from)
    {
        return from;
    }
};

} // namespace mml


#endif // _MML_CASTING_IMPLICIT_CASTER_HPP_INCLUDED_
