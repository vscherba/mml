//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_CASTING_TYPEID_CASTER_HPP_INCLUDED_
#define _MML_CASTING_TYPEID_CASTER_HPP_INCLUDED_


// std
#include <typeinfo>

#include <mml/casting/detail/pointer_caster_base.hpp>


namespace mml {

// common
template <typename From, typename To>
class typeid_caster;


template <typename From, typename To>
class typeid_caster_mi;


// builtin
template <typename From, typename To>
class typeid_caster<From*, To*>
    : public detail::pointer_caster_base<To*>
{
    template <typename From_, typename To_>
    friend class typeid_caster;

public:
    typeid_caster()
        : _ti(0)
    {
    }

    template <typename To_>
    typeid_caster(typeid_caster<From*, To_*> const& other)
        : _ti(other._ti)
    {
    }

    bool cast(From* from)
    {
        if (!_ti && from)
            _ti = &typeid(*from);

        this->_to =
            (_ti && *_ti == typeid(To))
                ? static_cast<To*>(from)
                : 0;

        return this->_to != 0;
    }

private:
    std::type_info const* _ti;
};


template <typename From, typename To>
class typeid_caster_mi<From*, To*>
    : public detail::pointer_caster_base<To*>
{
    template <typename From_, typename To_>
    friend class typeid_caster_mi;

public:
    typeid_caster_mi()
        : _ti(0)
    {
    }

    template <typename To_>
    typeid_caster_mi(typeid_caster_mi<From*, To_*> const& other)
        : _ti(other._ti)
    {
    }

    bool cast(From* from)
    {
        if (!_ti && from)
            _ti = &typeid(*from);

        this->_to =
            (_ti && *_ti == typeid(To))
                ? dynamic_cast<To*>(from)
                : 0;

        return this->_to != 0;
    }

private:
    std::type_info const* _ti;
};

} // namespace mml


#endif // _MML_CASTING_TYPEID_CASTER_HPP_INCLUDED_
