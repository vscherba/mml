//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_DETAIL_ZIP_PARAMETER_TYPES_HPP_INCLUDED_
#define _MML_DETAIL_ZIP_PARAMETER_TYPES_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/vector.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/less_equal.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/not.hpp>

// boost::type_traits
#include <boost/type_traits/is_same.hpp>

#include <mml/detail/pointer_traits_ex.hpp>
#include <mml/mpl/topological_sort.hpp>


namespace mml {
namespace detail {

template <typename T>
struct extract_pointed_type
    : boost::remove_cv<
        typename pointer_traits_ex<T>::element_type
        >
{
};


template <typename Seq>
struct extract_pointed_types
    : boost::mpl::transform<
          Seq
        , extract_pointed_type<boost::mpl::_>
        >
{
};


template <typename Matrix>
struct front_column
    : boost::mpl::fold<
          Matrix
        , boost::mpl::vector0<>
        , boost::mpl::if_<
              boost::mpl::empty<boost::mpl::_2>
            , boost::mpl::_1
            , boost::mpl::push_back<
                  boost::mpl::_1
                , boost::mpl::front<boost::mpl::_2>
                >
            >
        >
{
};


template <typename Matrix>
struct pop_front_column
    : boost::mpl::fold<
          Matrix
        , boost::mpl::vector0<>
        , boost::mpl::if_<
              boost::mpl::less_equal<
                  boost::mpl::size<boost::mpl::_2>
                , boost::mpl::long_<1>
                >
            , boost::mpl::_1
            , boost::mpl::push_back<
                  boost::mpl::_1
                , boost::mpl::pop_front<boost::mpl::_2>
                >
            >
        >
{
};


template <
      typename ParamTypes
    , template<typename, typename> class OrderingPred
    , template<typename> class Filter
    >
struct zip_parameter_types;


template <
      typename ParamTypes
    , template<typename, typename> class OrderingPred
    , template<typename> class Filter
    , bool Empty
    >
struct zip_parameter_types_impl
{
private:
    typedef typename boost::mpl::unique<
          typename extract_pointed_types<
            typename boost::mpl::remove_if<
                  typename front_column<ParamTypes>::type
                , boost::mpl::not_<Filter<boost::mpl::_> >
                >::type
            >::type
        , boost::is_same<boost::mpl::_1, boost::mpl::_2>
        >::type f_column;
public:
    typedef typename boost::mpl::push_front<
          typename zip_parameter_types<
              typename pop_front_column<ParamTypes>::type
            , OrderingPred
            , Filter
            >::type
        , typename mpl::topological_sort<f_column, OrderingPred>::type
        >::type type;

};


template <
      typename ParamTypes
    , template<typename, typename> class OrderingPred
    , template<typename> class Filter
    >
struct zip_parameter_types_impl<
      ParamTypes
    , OrderingPred
    , Filter
    , true
    >
    : boost::mpl::identity<ParamTypes>
{
};


template <
      typename ParamTypes
    , template<typename, typename> class OrderingPred
    , template<typename> class Filter
    >
struct zip_parameter_types
    : zip_parameter_types_impl<
          ParamTypes
        , OrderingPred
        , Filter
        , boost::mpl::empty<ParamTypes>::type::value
        >
{
};

} // namespace detail
} // namespace mml


#endif // _MML_DETAIL_ZIP_PARAMETER_TYPES_HPP_INCLUDED_
