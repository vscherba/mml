//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

// Example hierarchy from "More Effective C++" book by Scott Meyers
//
// Note hierarchy doesn't know anything about multimethod!
// Thus it could be a stable hierarchy


#ifndef _MML_EXAMPLE_GAME_HIERARCHY_HPP_INCLUDED_
#define _MML_EXAMPLE_GAME_HIERARCHY_HPP_INCLUDED_


// Abstract class for all game objects
struct game_object
{
    virtual ~game_object()
    {
    }
};


struct space_ship
    : game_object
{
};

struct space_station
    : game_object
{
};

struct asteroid
    : game_object
{
};

#endif // _MML_EXAMPLE_GAME_HIERARCHY_HPP_INCLUDED_
