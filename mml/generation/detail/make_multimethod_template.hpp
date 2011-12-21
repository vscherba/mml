//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


// boost::preprocessor
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>

#include <mml/config.hpp>
#include <mml/function_types/result_type.hpp>


namespace mml {

#define _MML_MAKE_MULTIMETHOD(z, n, _)                                      \
    template <BOOST_PP_ENUM_PARAMS(n, typename F)>                          \
    inline                                                                  \
    _MML_FACADE_NAME<BOOST_PP_ENUM_PARAMS(n, F)>                            \
    BOOST_PP_CAT(make_, _MML_FACADE_NAME)(                                  \
        BOOST_PP_ENUM_BINARY_PARAMS(n, F, f)                                \
        )                                                                   \
    {                                                                       \
        return                                                              \
        _MML_FACADE_NAME<BOOST_PP_ENUM_PARAMS(n, F)>(                       \
            BOOST_PP_ENUM_PARAMS(n, f)                                      \
            );                                                              \
    }                                                                       \
                                                                            \
    template <                                                              \
          template<typename, typename> class DynCaster                      \
        , BOOST_PP_ENUM_PARAMS(n, typename F)                               \
        >                                                                   \
    inline                                                                  \
    _MML_FACADE_NAME<                                                       \
          with_policies<                                                    \
              typename function_types::result_type<F0>::type                \
            , DynCaster                                                     \
            >                                                               \
        , BOOST_PP_ENUM_PARAMS(n, F)                                        \
        >                                                                   \
    BOOST_PP_CAT(make_, _MML_FACADE_NAME)(                                  \
        BOOST_PP_ENUM_BINARY_PARAMS(n, F, f)                                \
        )                                                                   \
    {                                                                       \
        return                                                              \
        _MML_FACADE_NAME<                                                   \
              with_policies<                                                \
                  typename function_types::result_type<F0>::type            \
                , DynCaster                                                 \
                >                                                           \
            , BOOST_PP_ENUM_PARAMS(n, F)                                    \
            >(                                                              \
                BOOST_PP_ENUM_PARAMS(n, f)                                  \
                );                                                          \
    }                                                                       \
                                                                            \
    template <                                                              \
          template<typename, typename> class DynCaster                      \
        , template<typename, typename> class DynCastablePred                \
        , BOOST_PP_ENUM_PARAMS(n, typename F)                               \
    >                                                                       \
    inline                                                                  \
    _MML_FACADE_NAME<                                                       \
          with_policies<                                                    \
              typename function_types::result_type<F0>::type                \
            , DynCaster                                                     \
            , DynCastablePred                                               \
            >                                                               \
        , BOOST_PP_ENUM_PARAMS(n, F)                                        \
        >                                                                   \
    BOOST_PP_CAT(make_, _MML_FACADE_NAME)(                                  \
        BOOST_PP_ENUM_BINARY_PARAMS(n, F, f)                                \
        )                                                                   \
    {                                                                       \
        return                                                              \
        _MML_FACADE_NAME<                                                   \
              with_policies<                                                \
                  typename function_types::result_type<F0>::type            \
                , DynCaster                                                 \
                , DynCastablePred                                           \
                >                                                           \
            , BOOST_PP_ENUM_PARAMS(n, F)                                    \
            >(                                                              \
                BOOST_PP_ENUM_PARAMS(n, f)                                  \
                );                                                          \
    }                                                                       \
                                                                            \
    template <                                                              \
          template<typename, typename> class DynCaster                      \
        , template<typename, typename> class DynCastablePred                \
        , template<typename, typename> class StatCaster                     \
        , BOOST_PP_ENUM_PARAMS(n, typename F)                               \
    >                                                                       \
    inline                                                                  \
    _MML_FACADE_NAME<                                                       \
          with_policies<                                                    \
              typename function_types::result_type<F0>::type                \
            , DynCaster                                                     \
            , DynCastablePred                                               \
            , StatCaster                                                    \
            >                                                               \
        , BOOST_PP_ENUM_PARAMS(n, F)                                        \
        >                                                                   \
    BOOST_PP_CAT(make_, _MML_FACADE_NAME)(                                  \
        BOOST_PP_ENUM_BINARY_PARAMS(n, F, f)                                \
        )                                                                   \
    {                                                                       \
        return                                                              \
        _MML_FACADE_NAME<                                                   \
              with_policies<                                                \
                  typename function_types::result_type<F0>::type            \
                , DynCaster                                                 \
                , DynCastablePred                                           \
                , StatCaster                                                \
              >                                                             \
            , BOOST_PP_ENUM_PARAMS(n, F)                                    \
            >(                                                              \
                BOOST_PP_ENUM_PARAMS(n, f)                                  \
                );                                                          \
    }                                                                       \
                                                                            \
    template <                                                              \
          template<typename, typename> class DynCaster                      \
        , template<typename, typename> class DynCastablePred                \
        , template<typename, typename> class StatCaster                     \
        , template<typename, typename> class StatCastablePred               \
        , BOOST_PP_ENUM_PARAMS(n, typename F)                               \
    >                                                                       \
    inline                                                                  \
    _MML_FACADE_NAME<                                                       \
          with_policies<                                                    \
              typename function_types::result_type<F0>::type                \
            , DynCaster                                                     \
            , DynCastablePred                                               \
            , StatCaster                                                    \
            , StatCastablePred                                              \
            >                                                               \
        , BOOST_PP_ENUM_PARAMS(n, F)                                        \
        >                                                                   \
    BOOST_PP_CAT(make_, _MML_FACADE_NAME)(                                  \
        BOOST_PP_ENUM_BINARY_PARAMS(n, F, f)                                \
        )                                                                   \
    {                                                                       \
        return                                                              \
        _MML_FACADE_NAME<                                                   \
              with_policies<                                                \
                  typename function_types::result_type<F0>::type            \
                , DynCaster                                                 \
                , DynCastablePred                                           \
                , StatCaster                                                \
                , StatCastablePred                                          \
                >                                                           \
            , BOOST_PP_ENUM_PARAMS(n, F)                                    \
            >(                                                              \
                BOOST_PP_ENUM_PARAMS(n, f)                                  \
                );                                                          \
    }                                                                       \
                                                                            \
    template <                                                              \
          template<typename, typename> class DynCaster                      \
        , template<typename, typename> class DynCastablePred                \
        , template<typename, typename> class StatCaster                     \
        , template<typename, typename> class StatCastablePred               \
        , template<typename, typename> class OrderingPred                   \
        , BOOST_PP_ENUM_PARAMS(n, typename F)                               \
    >                                                                       \
    inline                                                                  \
    _MML_FACADE_NAME<                                                       \
          with_policies<                                                    \
              typename function_types::result_type<F0>::type                \
            , DynCaster                                                     \
            , DynCastablePred                                               \
            , StatCaster                                                    \
            , StatCastablePred                                              \
            , OrderingPred                                                  \
            >                                                               \
        , BOOST_PP_ENUM_PARAMS(n, F)                                        \
        >                                                                   \
    BOOST_PP_CAT(make_, _MML_FACADE_NAME)(                                  \
        BOOST_PP_ENUM_BINARY_PARAMS(n, F, f)                                \
        )                                                                   \
    {                                                                       \
        return                                                              \
        _MML_FACADE_NAME<                                                   \
              with_policies<                                                \
                  typename function_types::result_type<F0>::type            \
                , DynCaster                                                 \
                , DynCastablePred                                           \
                , StatCaster                                                \
                , StatCastablePred                                          \
                , OrderingPred                                              \
                >                                                           \
            , BOOST_PP_ENUM_PARAMS(n, F)                                    \
            >(                                                              \
                BOOST_PP_ENUM_PARAMS(n, f)                                  \
                );                                                          \
    }                                                                       \
    /**/


BOOST_PP_REPEAT_FROM_TO(
      1
    , BOOST_PP_INC(MML_MAX_FUNCTION_OVERLOADS)
    , _MML_MAKE_MULTIMETHOD
    ,
    )


// undef temporaries
#undef _MML_MAKE_MULTIMETHOD

} // namespace mml
