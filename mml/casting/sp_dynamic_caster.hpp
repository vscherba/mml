//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_CASTING_SP_DYNAMIC_CASTER_HPP_INCLUDED_
#define _MML_CASTING_SP_DYNAMIC_CASTER_HPP_INCLUDED_


// boost::smart_ptr
#include <boost/shared_ptr.hpp>

#include <mml/pointer_traits/sp_pointer_traits.hpp>
#include <mml/casting/dynamic_caster.hpp>
#include <mml/casting/detail/pointer_caster_base.hpp>


namespace mml {

template <typename From, typename To>
class dynamic_caster<
      boost::shared_ptr<From>
    , boost::shared_ptr<To>
    >
    : public detail::pointer_caster_base<boost::shared_ptr<To> >
{
public:
    bool cast(boost::shared_ptr<From> const& from)
    {
        return this->_to = boost::dynamic_pointer_cast<To>(from);
    }
};

} // namespace mml


#endif // _MML_CASTING_SP_DYNAMIC_CASTER_HPP_INCLUDED_
