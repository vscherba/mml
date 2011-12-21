//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_CASTING_DETAIL_POINTER_CASTER_BASE_HPP_INCLUDED_
#define _MML_CASTING_DETAIL_POINTER_CASTER_BASE_HPP_INCLUDED_


#include <mml/detail/pointer_traits_ex.hpp>


namespace mml {
namespace detail {

template <typename To>
class pointer_caster_base
{
public:
    typename pointer_traits_ex<To>::param_type result()
    {
        return _to;
    }

protected:
    To _to;

    pointer_caster_base()
    {
    }

    ~pointer_caster_base()
    {
    }
};

} // namespace mml
} // namespace detail


#endif // _MML_CASTING_DETAIL_POINTER_CASTER_BASE_HPP_INCLUDED_
