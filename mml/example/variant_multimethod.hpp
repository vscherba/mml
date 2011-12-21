//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_EXAMPLE_VARIANT_MULTIMETHOD_HPP_INCLUDED_
#define _MML_EXAMPLE_VARIANT_MULTIMETHOD_HPP_INCLUDED_


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>

//boost::type_traits
#include <boost/type_traits/is_convertible.hpp>

// ATL
#include <atlcomcli.h>

#include <mml/config.hpp>
#include <mml/pointer_traits/pointer_traits.hpp>
#include <mml/refinery/custom_refine_to.hpp>
#include <mml/meta_predicate/always_dynamic_castable.hpp>
#include <mml/casting/implicit_caster.hpp>


namespace mml {

template <>
struct pointer_traits<ATL::CComVariant>
{
    typedef ATL::CComVariant element_type;

    template <typename U>
    struct rebind
    {
        typedef U other;
    };
};


template <typename, typename To>
class variant_caster
{
    typedef ATL::CVarTypeInfo<To> var_type_info;

public:
    bool cast(ATL::CComVariant const& from)
    {
        _hr = _var_to.ChangeType(var_type_info::VT, &from);
        return SUCCEEDED(_hr);
    }

    To result()
    {
        return _var_to.*(var_type_info::pmField);
    }

private:
    ATL::CComVariant _var_to;
    HRESULT _hr;
};


template <
    BOOST_PP_ENUM_BINARY_PARAMS(
          MML_MAX_REFINERY_SIZE
        , typename T
        , = boost::mpl::na BOOST_PP_INTERCEPT
        )
    >
struct variant_refine_to
    : custom_refine_to<
          variant_caster
        , always_dynamic_castable
        , implicit_caster
        , boost::is_convertible
        , BOOST_PP_ENUM_PARAMS(MML_MAX_REFINERY_SIZE, T)
        >
{
};

} // mml


#endif // _MML_EXAMPLE_VARIANT_MULTIMETHOD_HPP_INCLUDED_
