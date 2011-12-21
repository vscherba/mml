//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_EXAMPLE_FAST_CASTER_HPP_INCLUDED_
#define _MML_EXAMPLE_FAST_CASTER_HPP_INCLUDED_


// boost::smart_ptr
#include <boost/shared_ptr.hpp>

#include <mml/casting/detail/pointer_caster_base.hpp>


namespace mml {

// common
template <typename From, typename To>
class fast_caster;


// builtin
template <typename From, typename To>
class fast_caster<From*, To*>
    : public detail::pointer_caster_base<To*>
{
public:
    fast_caster()
        : _ti(0)
    {
    }

    template <typename T>
    fast_caster(T const& other)
        : _ti(other._ti)
    {
    }

    bool cast(From* from)
    {
        if (!_ti && from)
            _ti = from->get_type_id();

        this->_to
            = (_ti && (_ti & To::type_id) == To::type_id)
            ? static_cast<To*>(from)
            : 0;

        return this->_to != 0;
    }

    long _ti;
};


// boost::shared_ptr
template <typename From, typename To>
class fast_caster<boost::shared_ptr<From>, boost::shared_ptr<To> >
    : public detail::pointer_caster_base<boost::shared_ptr<To> >
{
public:
    fast_caster()
        : _ti(0)
    {
    }

    template <typename T>
    fast_caster(T const& other)
        : _ti(other._ti)
    {
    }

    bool cast(boost::shared_ptr<From> const& from)
    {
        if (!_ti && from)
            _ti = from->get_type_id();

        if (_ti && (_ti & To::type_id) == To::type_id)
            this->_to = boost::static_pointer_cast<To>(from);
        else
            this->_to.reset();

        return this->_to;
    }

    long _ti;
};

} // namespace mml


#endif // _MML_EXAMPLE_FAST_CASTER_HPP_INCLUDED_
