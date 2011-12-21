//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_GENERATION_DETAIL_WITH_TRAITS_HPP_INCLUDED_
#define _MML_GENERATION_DETAIL_WITH_TRAITS_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/aux_/na_fwd.hpp>

// boost::type_traits
#include <boost/type_traits/integral_constant.hpp>


namespace mml {

template <
      typename R
    , typename RFs = boost::mpl::na
    , typename EH = boost::mpl::na
>
struct with_traits
{
    typedef R _mml_wt3_result_type;
    typedef RFs _mml_wt3_refineries;
    typedef EH _mml_wt3_err_handler_type;
};


template <
      typename R
    , typename RFs
    >
struct with_traits<
      R
    , RFs
    , boost::mpl::na
    >
{
    typedef R _mml_wt2_result_type;
    typedef RFs _mml_wt2_refineries;
};


template <
    typename R
    >
struct with_traits<
      R
    , boost::mpl::na
    , boost::mpl::na
    >
{
    typedef R _mml_wt1_result_type;
};


namespace detail {

    template <typename T>
    struct is_with_traits
        : boost::false_type
    {
    };


    template <typename R, typename RFs, typename EH>
    struct is_with_traits<with_traits<R, RFs, EH> >
        : boost::true_type
    {
    };

} // namespace detail

} // namespace mml


#endif // _MML_GENERATION_DETAIL_WITH_TRAITS_HPP_INCLUDED_
