//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_CASTING_SP_TYPEID_CASTER_HPP_INCLUDED_
#define _MML_CASTING_SP_TYPEID_CASTER_HPP_INCLUDED_


// boost::smart_ptr
#include <boost/shared_ptr.hpp>

#include <mml/casting/typeid_caster.hpp>
#include <mml/casting/detail/pointer_caster_base.hpp>


namespace mml {

template <typename From, typename To>
class typeid_caster<
      boost::shared_ptr<From>
    , boost::shared_ptr<To>
    >
    : public detail::pointer_caster_base<boost::shared_ptr<To> >
{
    template <typename From_, typename To_>
    friend class typeid_caster;
public:
    typeid_caster()
        : _ti(0)
    {
    }

    template <typename To_>
    typeid_caster(
        typeid_caster<
              boost::shared_ptr<From>
            , boost::shared_ptr<To_>
            > const& other
        )
        : _ti(other._ti)
    {
    }

    bool cast(boost::shared_ptr<From> const& from)
    {
        if (!_ti && from)
            _ti = &typeid(*from);

        if (_ti && *_ti == typeid(To))
            this->_to = boost::static_pointer_cast<To>(from);
        else
            this->_to.reset();

        return this->_to;
    }

private:
    std::type_info const* _ti;
};


template <typename From, typename To>
class typeid_caster_mi<
      boost::shared_ptr<From>
    , boost::shared_ptr<To>
    >
    : public detail::pointer_caster_base<boost::shared_ptr<To> >
{
    template <typename From_, typename To_>
    friend class typeid_caster_mi;

public:
    typeid_caster_mi()
        : _ti(0)
    {
    }

    template <typename To_>
    typeid_caster_mi(
        typeid_caster_mi<
              boost::shared_ptr<From>
            , boost::shared_ptr<To_>
            > const& other
        )
        : _ti(other._ti)
    {
    }

    bool cast(boost::shared_ptr<From> const& from)
    {
        if (!_ti && from)
            _ti = &typeid(*from);

        if (_ti && *_ti == typeid(To))
            this->_to = boost::dynamic_pointer_cast<To>(from);
        else
            this->_to.reset();

        return this->_to;
    }

private:
    std::type_info const* _ti;
};

} // namespace mml


#endif // _MML_CASTING_SP_TYPEID_CASTER_HPP_INCLUDED_
