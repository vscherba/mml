//
// (C) Copyright Victor Scherba 2011-2012.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//


#ifndef _MML_GENERATION_MAKE_REF_DISPATCHER_HPP_INCLUDED_
#define _MML_GENERATION_MAKE_REF_DISPATCHER_HPP_INCLUDED_


#include <mml/facade/ref_dispatcher.hpp>
#include <mml/util/ref_dispatched_to_refineries.hpp>

#define _MML_DISP_PREFIX ref_
#include <mml/generation/detail/make_dispatcher_template.hpp>
#undef _MML_DISP_PREFIX


#endif // _MML_GENERATION_MAKE_REF_DISPATCHER_HPP_INCLUDED_
