//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

// Examines using of simple approach (lower threshold)

#include <iostream>
#include <vector>
#include <functional>

#include <boost/function.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <mml/generation/make_multimethod.hpp>
#include <mml/generation/make_ref_multimethod.hpp>
#include <mml/util/static_function.hpp>

#include "game_hierarchy.hpp"

using namespace std;
using namespace mml;

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

// We set different overloaded functions names for convenient taking pointers of them

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

// collide_tester applies collide function for each combination of pairs of game_object*
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

    cout << '\t' << collide(objs[1], objs[2]) << endl;
}

void multimethod_use()
{
    collide_tester(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collide_sh_as
            , collide_as_sh
            , collide_as_as
            )
        , get_obj_pointers()
        );

    boost::function<const char*(game_object*, game_object*)>
    /*auto*/ // use auto if compiler supports
        collide = make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collide_sh_as
            , collide_as_sh
            , collide_as_as
            );

    collide_tester(
          collide
        , get_obj_pointers()
        );
}

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

void ref_multimethod_use()
{
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

    boost::function<const char*(game_object&, game_object&)>
    /*auto*/ // use auto if compiler supports
        collide = make_ref_multimethod(
              collide_ref_go_go
            , collide_ref_sh_sh
            , collide_ref_sh_as
            , collide_ref_as_sh
            , collide_ref_as_as
            );

    collide_tester(
          collide
        , get_objs_refs()
        );
}

struct collider2
    : binary_function<space_ship*, asteroid*, const char*>
{
    const char* operator()(space_ship*, asteroid*) const
    {
        return "Space ship collides with asteroid";
    }
};

void multimethod_functor_use()
{
    collide_tester(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collider2()
            , collide_as_sh
            , collide_as_as
            )
        , get_obj_pointers()
        );
}

void multimethod_functor_wrapper_use()
{
    typedef static_function<
          const char*(asteroid*, space_ship*)
        , collide_as_sh
        > collider3;

    collide_tester(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collider2()
            , collider3()
            , collide_as_as
            )
        , get_obj_pointers()
        );
}

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

template <typename F, typename Objs>
void collide_tester2(F collide, Objs& objs)
{
    cout << '\t' << collide() << endl;

    cout << '\t' << collide(objs[0]) << endl;
    cout << '\t' << collide(objs[1]) << endl;

    cout << '\t' << collide(objs[0], objs[0]) << endl;
    cout << '\t' << collide(objs[0], objs[1]) << endl;

    cout << '\t' << collide(objs[0], objs[1], objs[1]) << endl;
    cout << '\t' << collide(objs[0], objs[1], objs[2]) << endl;

}

void multimethod_var_arg_use()
{
#if defined(_MSC_VER) && _MSC_VER < 1400
#   pragma message( \
    "Warning: there is too many template source code for VC 7.0-7.1 in this cpp file, " \
    __FUNCTION__ \
    " example is disabled. You could place it into separate cpp file to compile and test." \
    )
#else
    collide_tester2(
          make_multimethod(
              collide_go_go
            , collide_sh_sh
            , collide_sh_as
            , collide_void
            , collide_go
            , collide_sh
            , collide_as
            , collide_go_go_go
            , collide_sh_as_st
            , collide_sh_as_as
            )
        , get_obj_pointers()
        );
#endif
}

const char* collide_go_go_int(game_object*, game_object*, int)
{
    return "Unsupported colliding with extra int parameter!";
}

const char* collide_sh_as_int(space_ship*, asteroid*, int)
{
    return "Space ship collides with asteroid with extra int parameter";
}

template <typename F, typename Objs>
void collide_tester3(F collide, Objs& objs)
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
    collide_tester3(
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
void collide_tester4(F collide, Objs& objs)
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
    collide_tester4(
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

template <typename F, typename Objs>
void collide_tester5(F collide, Objs& objs)
{
    space_ship ship;
    asteroid ast;

    cout << '\t' << collide(objs[0], &ast) << endl;
    cout << '\t' << collide(&ship, &ast) << endl;
}

void compile_time_disp_optimization_use()
{
    collide_tester5(
          make_multimethod(
              collide_go_go
            , collide_sh_as
            , collide_as_as
            )
        , get_obj_pointers()
        );
}

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

    return 0;
}
