//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_DETAIL_REPLACE_NA_TO_VOID_HPP_INCLUDED_
#define _MML_DETAIL_REPLACE_NA_TO_VOID_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/if.hpp>

// boost::fusion
#include <boost/fusion/include/vector.hpp>


namespace mml {
namespace detail {

template <typename T>
struct replace_na_to_void
    : boost::mpl::if_<
          boost::mpl::is_na<T>
        , boost::fusion::void_
        , T
        >
{
};

} // namespace detail
} // namespace mml


#endif // _MML_DETAIL_REPLACE_NA_TO_VOID_HPP_INCLUDED_
