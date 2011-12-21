//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_MPL_TOPOLOGICAL_SORT_HPP_INCLUDED_
#define _MML_MPL_TOPOLOGICAL_SORT_HPP_INCLUDED_


// boost::mpl
#include <boost/mpl/front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/remove.hpp>


namespace mml {
namespace mpl {

template <
      typename Types
    , template<typename, typename> class Pred
    >
struct topological_sort;


namespace detail {

    template <
          typename Types
        , template<typename, typename> class Pred
        , typename StartT = typename boost::mpl::front<Types>::type
        >
    struct least_of;


    template <
          typename Types
        , template<typename, typename> class Pred
        , typename StartT
        , bool Empty
        >
    struct least_of_impl
    {
    private:
        typedef typename
            boost::mpl::front<Types>::type head;
        typedef typename
            boost::mpl::pop_front<Types>::type tail;

    public:
        typedef typename boost::mpl::if_<
              Pred<head, StartT>
            , typename least_of<tail, Pred, head>::type
            , typename least_of<tail, Pred, StartT>::type
            >::type type;
    };


    template <
          typename Types
        , template<typename, typename> class Pred
        , typename StartT
        >
    struct least_of_impl<Types, Pred, StartT, true>
        : boost::mpl::identity<StartT>
    {
    };


    template <
          typename Types
        , template<typename, typename> class Pred
        , typename StartT
        >
    struct least_of
        : least_of_impl<
              Types
            , Pred
            , StartT
            , boost::mpl::empty<Types>::type::value
            >
    {
    };


    template <
          typename Types
        , template<typename, typename> class Pred
        , bool Empty
        >
    struct topological_sort_impl
    {
    private:
        typedef typename
            boost::mpl::front<Types>::type head;
        typedef typename
            boost::mpl::pop_front<Types>::type tail;
        typedef typename
            least_of<tail, Pred, head>::type least_of_type;

    public:
        typedef typename boost::mpl::push_front<
              typename topological_sort<
                  typename boost::mpl::remove<
                      Types
                    , least_of_type
                    >::type
                , Pred
                >::type
            , least_of_type
            >::type type;
    };


    template <
          typename Types
        , template<typename, typename> class Pred
        >
    struct topological_sort_impl<Types, Pred, true>
        : boost::mpl::identity<Types>
    {
    };

} // namespace detail


template <
      typename Types
    , template<typename, typename> class Pred
    >
struct topological_sort
    : detail::topological_sort_impl<
          Types
        , Pred
        , boost::mpl::empty<Types>::type::value
        >
{
};

} // namespace mpl
} // namespace mml


#endif // _MML_MPL_TOPOLOGICAL_SORT_HPP_INCLUDED_
