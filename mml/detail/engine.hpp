//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#define _MML_ENGINE_N BOOST_PP_ITERATION()
#define _MML_ENGINE_N_DEC BOOST_PP_DEC(_MML_ENGINE_N)

#define _MML_FORMAL_PARAM_LIST                                              \
    BOOST_PP_ENUM_BINARY_PARAMS(_MML_ENGINE_N, A, a)                        \
    /**/

#define _MML_FACT_PARAM_LIST                                                \
    BOOST_PP_ENUM_PARAMS(_MML_ENGINE_N, a)                                  \
    /**/


template <
      typename Disp
    , long IArg
    , BOOST_PP_ENUM_PARAMS(_MML_ENGINE_N, typename A)
    , long Errors
    >
class BOOST_PP_CAT(engine, _MML_ENGINE_N)
{
    typedef typename Disp::result_type result_type;
    typedef typename Disp::refineries refineries;

    typedef typename boost::mpl::at_c<refineries, IArg>::type refinery;
    typedef pointer_traits_ex<A0> arg0_traits;
    typedef typename arg0_traits::pointer_type fact_pointer_type;

public:
    template <bool Error>
    static
    result_type
    next_arg(Disp& disp, _MML_FORMAL_PARAM_LIST)
    {
        using namespace boost::mpl;

        long const i_next_arg = IArg + 1;
        long const next_errors = Errors | (Error << IArg);
        typedef typename if_c<
              i_next_arg == _MML_ENGINE_N
            , typename if_c<
                  bool(next_errors)
                , disp_arg_handle_err_tag
                , typename if_<
                      boost::is_void<result_type>
                    , disp_arg_invoke_void_tag
                    , disp_arg_invoke_tag
                    >::type
                >::type
            , disp_arg_refine_tag
            >::type disp_arg_tag;

        return BOOST_PP_CAT(engine, _MML_ENGINE_N)<
              Disp
            , i_next_arg
            , BOOST_PP_ENUM_SHIFTED_PARAMS(_MML_ENGINE_N, A)
              BOOST_PP_COMMA_IF(_MML_ENGINE_N_DEC) A0
            , next_errors
            >::dispatch_arg(
                  disp_arg_tag()
                , disp
                , BOOST_PP_ENUM_SHIFTED_PARAMS(_MML_ENGINE_N, a)
                  BOOST_PP_COMMA_IF(_MML_ENGINE_N_DEC) a0
                );
    }

    static
    result_type
    dispatch_arg(disp_arg_refine_tag, Disp& disp, _MML_FORMAL_PARAM_LIST)
    {
        using namespace boost::mpl;

        typedef typename if_<
              and_<
                  less<long_<IArg>, size<refineries> >
                , not_<empty<refinery> >
                , pointer_traits_specified<A0>
                >
            , disp_arg_start_refine_tag
            , disp_arg_skip_refine_tag
            >::type disp_arg_tag;

        return do_refine(disp_arg_tag(), disp, _MML_FACT_PARAM_LIST);
    }

    static
    result_type
    dispatch_arg(disp_arg_invoke_tag, Disp& disp, _MML_FORMAL_PARAM_LIST)
    {
        return disp.dispatched()
            _MML_EXPLICIT_CALL_OPERATOR(_MML_FACT_PARAM_LIST);
    }

    static
    void
    dispatch_arg(disp_arg_invoke_void_tag, Disp& disp, _MML_FORMAL_PARAM_LIST)
    {
        disp.dispatched()
            _MML_EXPLICIT_CALL_OPERATOR(_MML_FACT_PARAM_LIST);
    }

    static
    result_type
    dispatch_arg(disp_arg_handle_err_tag, Disp& disp, _MML_FORMAL_PARAM_LIST)
    {
        MML_TRACE(1, "Not all of arguments were casted. Performing err_handler")
        return disp.err_handler()(
              disp
            , boost::mpl::long_<Errors>()
            , _MML_FACT_PARAM_LIST
            );
    }

private:
    static
    result_type
    do_refine(disp_arg_start_refine_tag, Disp& disp, _MML_FORMAL_PARAM_LIST)
    {
        return next_type<-1>(
              disp
            , static_cast<boost::mpl::na const&>(boost::mpl::na())
            , _MML_FACT_PARAM_LIST
            );
    }

    static
    result_type
    do_refine(disp_arg_skip_refine_tag, Disp& disp, _MML_FORMAL_PARAM_LIST)
    {
        return next_arg<false>(disp, _MML_FACT_PARAM_LIST);
    }

    template <long IType, typename Caster>
    static
    result_type
    next_type(Disp& disp, Caster& prev_caster, _MML_FORMAL_PARAM_LIST)
    {
        using namespace boost::mpl;

        long const i_next_type = IType + 1;
        typedef typename if_c<
              i_next_type == size<refinery>::value
            , disp_type_end_of_types_tag
            , disp_type_refine_tag
            >::type disp_type_tag;

        return dispatch_type<i_next_type>(
              disp_type_tag()
            , disp
            , prev_caster
            , _MML_FACT_PARAM_LIST
            );
    }

    template <long IType, typename Caster>
    static result_type dispatch_type(
          disp_type_refine_tag
        , Disp& disp
        , Caster& prev_caster
        , _MML_FORMAL_PARAM_LIST
        )
    {
        using namespace boost::mpl;

        typedef typename
            get_desired_pointer_type<IType>::type desired_pointer_type;

        typedef typename if_<
              typename refinery::template is_static_castable<
                  fact_pointer_type
                , desired_pointer_type
                >::type
            , disp_type_static_refine_tag
            , typename if_<
                  typename refinery::template is_dynamic_castable<
                      fact_pointer_type
                    , desired_pointer_type
                    >::type
                , disp_type_dynamic_refine_tag
                , disp_type_no_refine_tag
                >::type
            >::type disp_type_tag;

        return refine_type<IType>(
              disp_type_tag()
            , disp
            , prev_caster
            , _MML_FACT_PARAM_LIST
            );
    }

    template <long, typename Caster>
    static result_type dispatch_type(
          disp_type_end_of_types_tag
        , Disp& disp
        , Caster&
        , _MML_FORMAL_PARAM_LIST
        )
    {
        return next_arg<true>(disp, _MML_FACT_PARAM_LIST);
    }

    template <long IType, typename Caster>
    static result_type refine_type(
          disp_type_static_refine_tag
        , Disp& disp
        , Caster& prev_caster
        , _MML_FORMAL_PARAM_LIST
        )
    {
        typedef typename
            get_desired_pointer_type<IType>::type desired_pointer_type;
        typedef typename
            refinery::template static_caster<
                  fact_pointer_type
                , desired_pointer_type
                >::type new_caster_type;

        caster_ex<new_caster_type, Caster> caster(prev_caster);

        return BOOST_PP_CAT(engine, _MML_ENGINE_N)<
              Disp
            , IArg
            , typename pointer_traits_ex<desired_pointer_type>::param_type
              BOOST_PP_COMMA_IF(_MML_ENGINE_N_DEC)
              BOOST_PP_ENUM_SHIFTED_PARAMS(_MML_ENGINE_N, A)
            , Errors
            >::template next_arg<false>(
                  disp
                , caster.cast(a0)
                  BOOST_PP_COMMA_IF(_MML_ENGINE_N_DEC)
                  BOOST_PP_ENUM_SHIFTED_PARAMS(_MML_ENGINE_N, a)
                );
    }

    template <long IType, typename Caster>
    static result_type refine_type(
          disp_type_dynamic_refine_tag
        , Disp& disp
        , Caster& prev_caster
        , _MML_FORMAL_PARAM_LIST
        )
    {
        typedef typename
            get_desired_pointer_type<IType>::type desired_pointer_type;
        typedef typename
            refinery::template dynamic_caster<
                  fact_pointer_type
                , desired_pointer_type
                >::type new_caster_type;

        caster_ex<new_caster_type, Caster> caster(prev_caster);
        if (caster.cast(a0))
            return BOOST_PP_CAT(engine, _MML_ENGINE_N)<
                  Disp
                , IArg
                , typename pointer_traits_ex<desired_pointer_type>::param_type
                  BOOST_PP_COMMA_IF(_MML_ENGINE_N_DEC)
                  BOOST_PP_ENUM_SHIFTED_PARAMS(_MML_ENGINE_N, A)
                , Errors
                >::template next_arg<false>(
                      disp
                    , caster.result()
                      BOOST_PP_COMMA_IF(_MML_ENGINE_N_DEC)
                      BOOST_PP_ENUM_SHIFTED_PARAMS(_MML_ENGINE_N, a)
                    );
        else
            return refine_type<IType>(
                  disp_type_no_refine_tag()
                , disp
                , static_cast<new_caster_type&>(caster)
                , _MML_FACT_PARAM_LIST
                );
    }

    template <long IType, typename Caster>
    static result_type refine_type(
          disp_type_no_refine_tag
        , Disp& disp
        , Caster& prev_caster
        , _MML_FORMAL_PARAM_LIST
        )
    {
        return next_type<IType>(disp, prev_caster, _MML_FACT_PARAM_LIST);
    }

    // utils
    template <long IType>
    struct get_desired_pointer_type
    {
    private:
        typedef typename add_same_qualifiers_as<
              typename arg0_traits::element_type
            , typename boost::mpl::at_c<refinery, IType>::type
            >::type desired_type;
    public:
        typedef typename arg0_traits
            ::template rebind<desired_type>::other type;
    };
};


// undefs
#undef _MML_ENGINE_N
#undef _MML_ENGINE_N_DEC
#undef _MML_FORMAL_PARAM_LIST
#undef _MML_FACT_PARAM_LIST
