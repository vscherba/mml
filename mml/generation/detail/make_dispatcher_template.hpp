//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


// boost::preprocessor
#include <boost/preprocessor/cat.hpp>

// boost::utility
#include <boost/utility/enable_if.hpp>

#include <mml/util/first_result_type.hpp>
#include <mml/generation/detail/with_traits.hpp>


namespace mml {

#define _MML_DISPATCHER_NAME                                                \
    BOOST_PP_CAT(_MML_DISP_PREFIX, dispatcher)                              \
    /**/
#define _MML_DISP_MAKER_NAME                                                \
    BOOST_PP_CAT(make_, _MML_DISPATCHER_NAME)                               \
    /**/
#define _MML_DISP_TYPE_MAKER_NAME                                           \
    BOOST_PP_CAT(_MML_DISP_MAKER_NAME, _type)                               \
    /**/
#define _MML_OF_TO_RFS                                                      \
    BOOST_PP_CAT(_MML_DISP_PREFIX, dispatched_to_refineries)                \
    /**/


namespace detail {

    template <typename OF, typename EH = boost::mpl::na>
    struct _MML_DISP_TYPE_MAKER_NAME
    {
        typedef _MML_DISPATCHER_NAME<
              OF
            , typename first_result_type<OF>::type
            , typename _MML_OF_TO_RFS<OF>::type
            , EH
            > type;
    };


    template <typename OF>
    struct _MML_DISP_TYPE_MAKER_NAME<OF, boost::mpl::na>
    {
        typedef _MML_DISPATCHER_NAME<OF> type;
    };

} // namespace detail


template <typename OF>
inline
typename boost::lazy_disable_if<
      detail::is_with_traits<OF>
    , detail::_MML_DISP_TYPE_MAKER_NAME<OF>
    >::type
_MML_DISP_MAKER_NAME(OF const& of)
{
    return _MML_DISPATCHER_NAME<OF>(of);
}


template <typename Traits, typename OF>
inline
_MML_DISPATCHER_NAME<
      OF
    , typename Traits::_mml_wt1_result_type
    >
_MML_DISP_MAKER_NAME(OF const& of)
{
    return _MML_DISPATCHER_NAME<
          OF
        , typename Traits::_mml_wt1_result_type
        >(of);
}


template <typename Traits, typename OF>
inline
_MML_DISPATCHER_NAME<
      OF
    , typename Traits::_mml_wt2_result_type
    , typename Traits::_mml_wt2_refineries
    >
_MML_DISP_MAKER_NAME(OF const& of)
{
    return _MML_DISPATCHER_NAME<
          OF
        , typename Traits::_mml_wt2_result_type
        , typename Traits::_mml_wt2_refineries
        >(of);
}


template <typename Traits, typename OF>
inline
_MML_DISPATCHER_NAME<
      OF
    , typename Traits::_mml_wt3_result_type
    , typename Traits::_mml_wt3_refineries
    , typename Traits::_mml_wt3_err_handler_type
    >
_MML_DISP_MAKER_NAME(OF const& of)
{
    return _MML_DISPATCHER_NAME<
          OF
        , typename Traits::_mml_wt3_result_type
        , typename Traits::_mml_wt3_refineries
        , typename Traits::_mml_wt3_err_handler_type
        >(of);
}


template <typename OF, typename EH>
inline
typename boost::lazy_disable_if<
      detail::is_with_traits<OF>
    , detail::_MML_DISP_TYPE_MAKER_NAME<OF, EH>
    >::type
_MML_DISP_MAKER_NAME(OF const& of, EH const& eh)
{
    return
    _MML_DISPATCHER_NAME<
          OF
        , typename first_result_type<OF>::type
        , typename _MML_OF_TO_RFS<OF>::type
        , EH
        >(of, eh);
}


template <typename Traits, typename OF, typename EH>
inline
_MML_DISPATCHER_NAME<
      OF
    , typename Traits::_mml_wt1_result_type
    , typename _MML_OF_TO_RFS<OF>::type
    , EH
    >
_MML_DISP_MAKER_NAME(OF const& of, EH const& eh)
{
    return _MML_DISPATCHER_NAME<
          OF
        , typename Traits::_mml_wt1_result_type
        , typename _MML_OF_TO_RFS<OF>::type
        , EH
        >(of, eh);
}


template <typename Traits, typename OF, typename EH>
inline
_MML_DISPATCHER_NAME<
      OF
    , typename Traits::_mml_wt2_result_type
    , typename Traits::_mml_wt2_refineries
    , EH
    >
_MML_DISP_MAKER_NAME(OF const& of, EH const& eh)
{
    return _MML_DISPATCHER_NAME<
          OF
        , typename Traits::_mml_wt2_result_type
        , typename Traits::_mml_wt2_refineries
        , EH
        >(of, eh);
}


// undefs
#undef _MML_DISPATCHER_NAME
#undef _MML_DISP_MAKER_NAME
#undef _MML_DISP_TYPE_MAKER_NAME
#undef _MML_OF_TO_RFS

} // namespace mml
