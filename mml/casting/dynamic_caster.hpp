//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_CASTING_DYNAMIC_CASTER_HPP_INCLUDED_
#define _MML_CASTING_DYNAMIC_CASTER_HPP_INCLUDED_


#include <mml/casting/detail/pointer_caster_base.hpp>


namespace mml {

// common
template <typename From, typename To>
class dynamic_caster;


// builtin
template <typename From, typename To>
class dynamic_caster<From*, To*>
    : public detail::pointer_caster_base<To*>
{
public:
    bool cast(From* from)
    {
        this->_to = dynamic_cast<To*>(from);
        return this->_to != 0;
    }
};

} // namespace mml


#endif // _MML_CASTING_DYNAMIC_CASTER_HPP_INCLUDED_
