//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

// Test for <mml/result_of_support/result_of_support.hpp>

#include <boost/config.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/static_assert.hpp>

#include <mml/result_of_support/result_of_support.hpp>


#define CALL_CHECK(call, result)                                            \
    BOOST_STATIC_ASSERT((is_same<result_of<call>::type, result>::value));   \
    /**/

using namespace boost;


// test without rvalue references >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

struct Functor
    : mml::result_of_support<float&, const float&, double, long double>
{
    float& operator()(char*);
    const float& operator()(char*) const;

    double operator()(short, long) const;
    
    long double operator()();
    long double operator()(long);
};


// strong match:
CALL_CHECK(Functor(char*), float&);
CALL_CHECK(const Functor(char*), const float&);
CALL_CHECK(const Functor(short, long), double);
CALL_CHECK(Functor(), void);
CALL_CHECK(Functor(long), long double);


// match with implicit argument conversion:
CALL_CHECK(const Functor(char, int), double); // -> overloads to double operator()(short, long) const
CALL_CHECK(Functor(unsigned short), long double); // -> overloads to long double operator()(long)

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< test without rvalue references


// test with rvalue references >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

#ifndef BOOST_NO_RVALUE_REFERENCES

struct Functor2
    : mml::result_of_support<float&, const float&, float&&, double, long double>
{
    float& operator()(char*);
    const float& operator()(char*) const;

    float&& operator()(short, char);
    double operator()(short, long) const;
    
    long double operator()();
    long double operator()(long);
};


// strong match:
CALL_CHECK(Functor2(char*), float&);
CALL_CHECK(const Functor2(char*), const float&);
CALL_CHECK(Functor2(short, char), float&&);
CALL_CHECK(const Functor2(short, long), double);
CALL_CHECK(Functor2(), void);
CALL_CHECK(Functor2(long), long double);


// match with implicit argument conversion:
CALL_CHECK(Functor2(char, char), float&&); // -> overloads to float&& operator()(short, char)
CALL_CHECK(const Functor2(char, int), double); // -> overloads to double operator()(short, long) const
CALL_CHECK(Functor2(unsigned short), long double); // -> overloads to long double operator()(long)

#endif // #ifndef BOOST_NO_RVALUE_REFERENCES

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< test with rvalue references
