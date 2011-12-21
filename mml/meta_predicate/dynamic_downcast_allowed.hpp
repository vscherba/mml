//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_META_PREDICATE_DYNAMIC_DOWNCAST_ALLOWED_HPP_INCLUDED_
#define _MML_META_PREDICATE_DYNAMIC_DOWNCAST_ALLOWED_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/and.hpp>

// boost::type_traits
#include <boost/type_traits/is_base_and_derived.hpp>
#include <boost/type_traits/is_polymorphic.hpp>

#include <mml/detail/pointer_traits_ex.hpp>


namespace mml {

template <typename PBase, typename PDerived>
struct dynamic_downcast_allowed
    : boost::mpl::and_<
          boost::is_base_and_derived<
              typename detail::pointer_traits_ex<PBase>::element_type
            , typename detail::pointer_traits_ex<PDerived>::element_type
            >
        , boost::is_polymorphic<
            typename detail::pointer_traits_ex<PBase>::element_type
            >
        >
{
};

} // namespace mml


#endif // _MML_META_PREDICATE_DYNAMIC_DOWNCAST_ALLOWED_HPP_INCLUDED_
