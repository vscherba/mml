//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

// Examines using of simple approach (lower threshold)

// For common simple using you need only one library function
// which creates and returns multimethod<...> as functional object:
// make_multimethod(f1, ..., fn), where f1, ..., fn - function pointers or
// functional objects which will be dynamicly overloaded.

// In 90% cases there are no need any extra requirements, restrictions
// or any special library support for user hierarchy.

// First example "void multimethod_use()" demonstrate it,
// rest examples show some variations of simple using.

// multimethod template is only facade for basic_dispatcher template class,
// its functionality is more wider, but it examines in other example source file.

// Library is "header only".

#include <iostream>
#include <vector>
#include <functional>

#include <boost/function.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

// multimethod creator for pointer arguments (main header for this example)
#include <mml/generation/make_multimethod.hpp>

// multimethod creator for reference arguments
#include <mml/generation/make_ref_multimethod.hpp>

// utility helper
#include <mml/util/static_function.hpp>

// header to enable boost::shared_ptr arguments dispatching
#include <mml/casting/sp_dynamic_caster.hpp>

// contains example hierarchy
#include "game_hierarchy.hpp"

using namespace std;
using namespace mml;


// helpers >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// helper which returns vector of three polymorphic object pointers
vector<game_object*>& get_obj_pointers()
{
    static space_ship ship;
    static asteroid ast;
    static space_station station;

    static vector<game_object*> objs; // vector of polymorphic objects

    if (objs.empty())
    {
        objs.push_back(&ship);
        objs.push_back(&ast);
        objs.push_back(&station);
    }

    return objs;
}

// helper which returns vector of three polymorphic object references
boost::ptr_vector<game_object>& get_objs_refs()
{
    static boost::ptr_vector<game_object> objs;

    if (objs.empty())
    {
        objs.push_back(new space_ship);
        objs.push_back(new asteroid);
        objs.push_back(new space_station);
    }

    return objs;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< helpers


// multimethod_use() example >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// multimethod dispatches closed hierarchies, so no need to modify its
// thus, multimethod can dispatch any old hierarchy you have ever made
// without modifications and recompilations

// target set of overloaded functions with poiner arguments
// we set different overloaded functions names for convenient taking pointers of them

const char* collide_go_go(game_object*, game_object*)
{
    return "Unsupported colliding!";
}

const char* collide_sh_sh(space_ship*, space_ship*)
{
    return "Space ship collides with space ship";
}

const char* collide_sh_as(space_ship*, asteroid*)
{
    return "Space ship collides with asteroid";
}

const char* collide_as_sh(asteroid*, space_ship*)
{
    return "Asteroid collides with space ship";
}

const char* collide_as_as(asteroid*, asteroid*)
{
    return "Asteroid collides with asteroid";
}

// collide_tester applies collide function for each combination of pairs of objs elements
template <typename F, typename Objs>
void collide_tester(F collide, Objs& objs)
{
    for (size_t i = 0; i < 2; ++i)
    {
        for (size_t j = 0; j < 2; ++j)
        {
            cout << '\t' << collide(objs[i], objs[j]) << endl;
        }
    }
}

// first simple example function
void multimethod_use()
{
    // call tester
    collide_tester(
          make_multimethod( // creates multimethod based on function pointers
              collide_go_go
            , collide_sh_sh
            , collide_sh_as
            , collide_as_sh
            , collide_as_as
            )
        , get_obj_pointers()
        );

    // save multimethod in temporary variable
    boost::function<const char*(game_object*, game_object*)>
    /*auto*/ // use auto if compiler supports
        collide = make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collide_sh_as
            , collide_as_sh
            , collide_as_as
            );

    // call tester
    collide_tester(
          collide
        , get_obj_pointers()
        );
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< multimethod_use() example


// ref_multimethod_use() example >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// target set of overloaded functions with reference arguments

const char* collide_ref_go_go(game_object&, game_object&)
{
    return "Unsupported colliding!";
}

const char* collide_ref_sh_sh(space_ship&, space_ship&)
{
    return "Space ship collides with space ship";
}

const char* collide_ref_sh_as(space_ship&, asteroid&)
{
    return "Space ship collides with asteroid";
}

const char* collide_ref_as_sh(asteroid&, space_ship&)
{
    return "Asteroid collides with space ship";
}

const char* collide_ref_as_as(asteroid&, asteroid&)
{
    return "Asteroid collides with asteroid";
}


// reference multimethod example
void ref_multimethod_use()
{
    // call tester
    collide_tester(
          make_ref_multimethod(
              collide_ref_go_go
            , collide_ref_sh_sh
            , collide_ref_sh_as
            , collide_ref_as_sh
            , collide_ref_as_as
            )
        , get_objs_refs()
        );

    // save multimethod in temporary variable
    boost::function<const char*(game_object&, game_object&)>
    /*auto*/ // use auto if compiler supports
        collide = make_ref_multimethod(
              collide_ref_go_go
            , collide_ref_sh_sh
            , collide_ref_sh_as
            , collide_ref_as_sh
            , collide_ref_as_as
            );

    // call tester
    collide_tester(
          collide
        , get_objs_refs()
        );
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< ref_multimethod_use() example


// multimethod_functor_wrapper_use() example >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// we can also use functors as target overloads
struct collider_sh_as
    : binary_function<space_ship*, asteroid*, const char*>
{
    const char* operator()(space_ship*, asteroid*) const
    {
        return "Space ship collides with asteroid";
    }
};


// example of multimethod with functor using
void multimethod_functor_use()
{
    collide_tester(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collider_sh_as()
            , collide_as_sh
            , collide_as_as
            )
        , get_obj_pointers()
        );
}

// example of using static_function template utility
void multimethod_functor_wrapper_use()
{
    // static_function represents function pointer wrapper
    // it allows to optimizing compiler make inlining instead of call function pointer
    // static_function takes function reference with external linkage as second template parameter
    typedef static_function<
          const char*(asteroid*, space_ship*)
        , collide_as_sh
        > collider_as_sh;

    collide_tester(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collider_sh_as()
            , collider_as_sh()
            , collide_as_as
            )
        , get_obj_pointers()
        );
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< multimethod_functor_wrapper_use() example


/*
// I give C++ code equivalent for first four examples
// it is equivalent of generated code after template instantiation and inlining
// call of collide(objs[i], objs[j]) generates:
inline const char* collide(game_object* obj1, game_object* obj2)
{
    if (space_ship* sh1 = dynamic_cast<space_ship*>(obj1))
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            return collide_sh_sh(sh1, sh2);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            return collide_sh_as(sh1, as2);
        else
            return collide_go_go(sh1, obj2);
    else if (asteroid* as1 = dynamic_cast<asteroid*>(obj1))
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            return collide_as_sh(as1, sh2);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            return collide_as_as(as1, as2);
        else
            return collide_go_go(as1, obj2);
    else
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            return collide_go_go(obj1, sh2);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            return collide_go_go(obj1, as2);
        else
            return collide_go_go(obj1, obj2);
}
// runtime overhead:
// min 2 casts
// max 4 casts
*/


// multimethod_var_arg_use() example >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// multimethod works with arbitary number of parameters

const char* collide_void()
{
    return "Nothing collides";
}

const char* collide_go(game_object*)
{
    return "Unsupported colliding!";
}

const char* collide_sh(space_ship*)
{
    return "Space ship collides with what?!";
}

const char* collide_as(asteroid*)
{
    return "Asteroid collides with what?!";
}

const char* collide_go_go_go(game_object*, game_object*, game_object*)
{
    return "Unsupported colliding!";
}

const char* collide_sh_as_as(space_ship*, asteroid*, asteroid*)
{
    return "Space ship collides with two asteroids";
}

const char* collide_sh_as_st(space_ship*, asteroid*, space_station*)
{
    return "Space ship collides with asteroid and space_station";
}


// tester for multimethod with variable number of arguments
template <typename F, typename Objs>
void collide_tester_var_arg(F collide, Objs& objs)
{
    // no parameter
    cout << '\t' << collide() << endl;

    // 1 parameter
    cout << '\t' << collide(objs[0]) << endl;
    cout << '\t' << collide(objs[1]) << endl;

    // 2 parameters
    cout << '\t' << collide(objs[0], objs[0]) << endl;
    cout << '\t' << collide(objs[0], objs[1]) << endl;

    // 3 parameters
    cout << '\t' << collide(objs[0], objs[1], objs[1]) << endl;
    cout << '\t' << collide(objs[0], objs[1], objs[2]) << endl;

}

// example of using variable number of arguments
void multimethod_var_arg_use()
{
#if defined(_MSC_VER) && _MSC_VER < 1400
#   pragma message( \
    "Warning: there is too many template source code for VC 7.0-7.1 in this cpp file, " \
    __FUNCTION__ \
    " example is disabled. You could place it into separate cpp file to compile and test." \
    )
#else
    collide_tester_var_arg(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collide_sh_as
            , collide_void
            , collide_go
            , collide_sh
            , collide_as
            , collide_go_go_go
            , collide_sh_as_as
            , collide_sh_as_st
            )
        , get_obj_pointers()
        );
#endif
}

/*
// C++ code equivalent for collide_tester_var_arg instantiation

// collide()
inline const char* collide()
{
    return collide_void();
}
// no runtime overhead!


// collide(objs[0])
// collide(objs[1])
inline const char* collide(game_object* obj)
{
    if (space_ship* sh = dynamic_cast<space_ship*>(obj))
        return collide_sh(sh);
    else if (asteroid* as = dynamic_cast<asteroid*>(obj))
        return collide_as(as);
    else
        return collide_go(obj);
}
// runtime overhead:
// min 1 casts
// max 2 casts

// collide(objs[0], objs[0])
// collide(objs[0], objs[1])
// as shown above: inline const char* collide(game_object* obj1, game_object* obj2) {...}

// collide(objs[0], objs[1], objs[1])
// collide(objs[0], objs[1], objs[2])
inline const char* collide(game_object* obj1, game_object* obj2, game_object* obj3)
{
    if (space_ship* sh1 = dynamic_cast<space_ship*>(obj1))
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_go_go_go(sh1, sh2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_go_go_go(sh1, sh2, st3);
            else
                return collide_go_go_go(sh1, sh2, obj3);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_sh_as_as(sh1, as2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_sh_as_st(sh1, as2, st3);
            else
                return collide_go_go_go(sh1, as2, obj3);
        else
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_go_go_go(sh1, obj2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_go_go_go(sh1, obj2, st3);
            else
                return collide_go_go_go(sh1, obj2, obj3);
    else if (asteroid* as1 = dynamic_cast<asteroid*>(obj1))
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_go_go_go(as1, sh2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_go_go_go(as1, sh2, st3);
            else
                return collide_go_go_go(as1, sh2, obj3);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_go_go_go(as1, as2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_go_go_go(as1, as2, st3);
            else
                return collide_go_go_go(as1, as2, obj3);
        else
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_go_go_go(as1, obj2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_go_go_go(as1, obj2, st3);
            else
                return collide_go_go_go(as1, obj2, obj3);
    else
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_go_go_go(obj1, sh2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_go_go_go(obj1, sh2, st3);
            else
                return collide_go_go_go(obj1, sh2, obj3);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_go_go_go(obj1, as2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_go_go_go(obj1, as2, st3);
            else
                return collide_go_go_go(obj1, as2, obj3);
        else
            if (asteroid* as3 = dynamic_cast<asteroid*>(obj3))
                return collide_go_go_go(obj1, obj2, as3);
            else if (space_station* st3 = dynamic_cast<space_station*>(obj3))
                return collide_go_go_go(obj1, obj2, st3);
            else
                return collide_go_go_go(obj1, obj2, obj3);
}
// runtime overhead:
// min 3 casts
// max 6 casts
*/

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< multimethod_var_arg_use() example


// multimethod_non_polymorphic_arg_use() example >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

const char* collide_go_go_int(game_object*, game_object*, int)
{
    return "Unsupported colliding with extra int parameter!";
}

const char* collide_sh_as_int(space_ship*, asteroid*, int)
{
    return "Space ship collides with asteroid with extra int parameter";
}

template <typename F, typename Objs>
void collide_tester_non_polymorphic_arg(F collide, Objs& objs)
{
    cout << '\t' << collide(objs[0], objs[1]) << endl;
    cout << '\t' << collide(objs[0], objs[1], objs[2]) << endl;
    cout << '\t' << collide(objs[0], objs[1], 1) << endl;
}

void multimethod_non_polymorphic_arg_use()
{
#if defined(_MSC_VER) && _MSC_VER < 1400
#   pragma message( \
    "Warning: there is too many template source code for VC 7.0-7.1 in this cpp file, " \
    __FUNCTION__ \
    " example is disabled. You could place it into separate cpp file to compile and test." \
    )
#else
    collide_tester_non_polymorphic_arg(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collide_sh_as
            , collide_as_sh
            , collide_as_as
            , collide_go_go_go
            , collide_sh_as_st
            , collide_sh_as_as
            , collide_go_go_int
            , collide_sh_as_int
            )
        , get_obj_pointers()
        );
#endif
}

/*
// C++ code equivalent for collide_tester_non_polymorphic_arg instantiation

// collide(objs[0], objs[1])
// as shown above: inline const char* collide(game_object* obj1, game_object* obj2) {...}

// collide(objs[0], objs[1], objs[2])
// as shown above: inline const char* collide(game_object* obj1, game_object* obj2, game_object* obj3) {...}

// collide(objs[0], objs[1], 1)
inline const char* collide(game_object* obj1, game_object* obj2, int n)
{
    if (space_ship* sh1 = dynamic_cast<space_ship*>(obj1))
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            return collide_go_go_int(sh1, sh2, n);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            return collide_sh_as_int(sh1, as2, n);
        else
            return collide_go_go_int(sh1, obj2, n);
    else if (asteroid* as1 = dynamic_cast<asteroid*>(obj1))
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            return collide_go_go_int(as1, sh2, n);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            return collide_go_go_int(as1, as2, n);
        else
            return collide_go_go_int(as1, obj2, n);
    else
        if (space_ship* sh2 = dynamic_cast<space_ship*>(obj2))
            return collide_go_go_int(obj1, sh2, n);
        else if (asteroid* as2 = dynamic_cast<asteroid*>(obj2))
            return collide_go_go_int(obj1, as2, n);
        else
            return collide_go_go_int(obj1, obj2, n);
}
// runtime overhead:
// min 2 casts
// max 4 casts
*/

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< multimethod_non_polymorphic_arg_use() example


// multimethod_cv_use() example >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

const char* collide_go_cvgo(game_object*, const volatile game_object*)
{
    return "Unsupported colliding!";
}

const char* collide_sh_cas(space_ship*, const asteroid*)
{
    return "Space ship collides with const asteroid";
}

const char* collide_sh_vas(space_ship*, volatile asteroid*)
{
    return "Space ship collides with volatile asteroid";
}

const char* collide_sh_cvas(space_ship*, const volatile asteroid*)
{
    return "Space ship collides with const volatile asteroid";
}

template <typename F, typename Objs>
void collide_tester_cv(F collide, Objs& objs)
{
    game_object* object = objs[1];
    const game_object* c_object = objs[1];
    const volatile game_object* cv_object = objs[1];

    cout << '\t' << collide(objs[0], object) << endl;
    cout << '\t' << collide(objs[0], c_object) << endl;
    cout << '\t' << collide(objs[0], cv_object) << endl;
}

void multimethod_cv_use()
{
    collide_tester_cv(
          make_multimethod(
              collide_sh_as
            , collide_go_cvgo
            , collide_sh_cas
            , collide_sh_vas
            , collide_sh_cvas
            )
        , get_obj_pointers()
        );
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< multimethod_cv_use() example


// compile_time_disp_optimization_use() example >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

template <typename F, typename Objs>
void collide_tester_compile_time_optim(F collide, Objs& objs)
{
    space_ship ship;
    asteroid ast;

    cout << '\t' << collide(objs[0], &ast) << endl;
    cout << '\t' << collide(&ship, &ast) << endl;
}

void compile_time_disp_optimization_use()
{
    collide_tester_compile_time_optim(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collide_sh_as
            , collide_as_sh
            , collide_as_as
            )
        , get_obj_pointers()
        );
}

/*
// C++ code equivalent for collide_tester_compile_time_optim instantiation

// collide(objs[0], &ast)
inline const char* collide(game_object* obj1, asteroid* as2)
{
    if (space_ship* sh1 = dynamic_cast<space_ship*>(obj1))
        return collide_sh_as(sh1, as2);
    else if (asteroid* as1 = dynamic_cast<asteroid*>(obj1))
        return collide_as_as(as1, as2);
    else
        return collide_go_go(obj1, as2);
}
// runtime overhead:
// min 1 casts
// max 2 casts

// collide(&ship, &ast)
inline const char* collide(space_ship* sh1, asteroid* as2)
{
    return collide_sh_as(sh1, as2);
}
// no runtime overhead! direct call to collide_sh_as!
*/

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< compile_time_disp_optimization_use() example


// multimethod_sp_use() example >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

// <mml/casting/sp_dynamic_caster.hpp> involves code
// that allows to dispatch boost::shared_ptr<T> such as built-in pointer

const char* sp_collide_go_go(game_object*, boost::shared_ptr<game_object>)
{
    return "Unsupported colliding!";
}

const char* sp_collide_sh_sh(space_ship*, boost::shared_ptr<space_ship>)
{
    return "Space ship collides with smart_ptr space ship";
}

struct sp_collider_sh_as
    : binary_function<space_ship*, boost::shared_ptr<asteroid>, const char*>
{
    const char* operator()(space_ship*, boost::shared_ptr<asteroid>) const
    {
        return "Space ship collides with smart_ptr asteroid";
    }
};

template <typename F, typename Objs>
void sp_collide_tester(F collide, Objs& objs)
{
    boost::shared_ptr<game_object> obj1(new space_ship);
    boost::shared_ptr<game_object> obj2(new asteroid);

    cout << '\t' << collide(objs[0], obj1) << endl;
    cout << '\t' << collide(objs[0], obj2) << endl;
}

void multimethod_sp_use()
{
#if defined(_MSC_VER) && _MSC_VER < 1400
#   pragma message( \
    "Warning: there is too many template source code for VC 7.0-7.1 in this cpp file, " \
    __FUNCTION__ \
    " example is disabled. You could place it into separate cpp file to compile and test." \
    )
#else
    sp_collide_tester(
          make_multimethod(
              sp_collide_go_go
            , sp_collide_sh_sh
            , sp_collider_sh_as()
            )
        , get_obj_pointers()
        );
#endif
}

/*
// C++ code equivalent for sp_collide_tester instantiation

// collide(objs[0], obj1)
// collide(objs[0], obj2)
inline const char* collide(game_object* obj1, const boost::shared_ptr<game_object>& sp_obj2)
{
    if (space_ship* sh1 = dynamic_cast<space_ship*>(obj1))
        if (boost::shared_ptr<space_ship> sp_sh2 = boost::shared_dynamic_cast<space_ship>(sp_obj2))
            return sp_collide_sh_sh(sh1, sp_sh2);
        else if (boost::shared_ptr<asteroid> sp_as2 = boost::shared_dynamic_cast<asteroid>(sp_obj2))
            return sp_collider_sh_as()(sh1, sp_as2);
        else
            return sp_collide_go_go(obj1, sp_obj2);
    else
        if (boost::shared_ptr<space_ship> sp_sh2 = boost::shared_dynamic_cast<space_ship>(sp_obj2))
            return sp_collide_go_go(obj1, sp_sh2);
        else if (boost::shared_ptr<asteroid> sp_as2 = boost::shared_dynamic_cast<asteroid>(sp_obj2))
            return sp_collide_go_go(obj1, sp_as2);
        else
            return sp_collide_go_go(obj1, sp_obj2);
}
// runtime overhead:
// min 2 casts
// max 3 casts
*/

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< multimethod_sp_use() example


int main(int argc, char* argv[])
{
    multimethod_use();
    ref_multimethod_use();
    multimethod_functor_use();
    multimethod_functor_wrapper_use();
    multimethod_var_arg_use();
    multimethod_non_polymorphic_arg_use();
    multimethod_cv_use();
    compile_time_disp_optimization_use();
    multimethod_sp_use();

    return 0;
}
