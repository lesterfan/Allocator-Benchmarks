// bslstp_alloc.h                                                     -*-C++-*-
#ifndef INCLUDED_BSLSTP_ALLOC
#define INCLUDED_BSLSTP_ALLOC

//@PURPOSE: Provide facilities for STLPort implementation.
//
//@INTERNAL_DEPRECATED: Do not use directly.
//
//@CLASSES:
//
//@SEE_ALSO: bslstp_hashmap, bslstp_hashtable, bslstp_slist
//
//@AUTHOR: Steven Breitstein (sbreitstein)
//
//@DESCRIPTION: This component is for internal use only.
//
// Note that the functions in this component are based on STLPort's
// implementation, with copyright notice as follows:
//..
/*
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1997
 * Moscow Center for SPARC Technology
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
//..
//
///Usage
///-----
// This component is for internal use only.

#ifdef BDE_OPENSOURCE_PUBLICATION // STP
#error "bslstp_alloc is not for publication"
#endif

#ifndef INCLUDED_BSLALG_CONTAINERBASE
#include <bslalg_containerbase.h>
#endif

namespace bsl {

typedef void (* __oom_handler_type)();

enum {_ALIGN = 8, _ALIGN_SHIFT=3, _MAX_BYTES = 128};

// The fully general version.
template <class _Tp, class _Allocator>
struct _Alloc_traits
{
  typedef _Allocator _Orig;
  typedef typename _Allocator::template rebind<_Tp> _Rebind_type;
  typedef typename _Rebind_type::other  allocator_type;
  static allocator_type create_allocator(const _Orig& __a) { return allocator_type(__a); }
};

// inheritance is being used for EBO optimization
template <class _Value, class _Tp, class _MaybeReboundAlloc>
class _STLP_alloc_proxy
    : public BloombergLP::bslalg::ContainerBase<_MaybeReboundAlloc> {
private:
  typedef BloombergLP::bslalg::ContainerBase<_MaybeReboundAlloc> _Base;

  typedef _STLP_alloc_proxy<_Value, _Tp, _MaybeReboundAlloc> _Self;
public:
  _Value _M_data;
  inline _STLP_alloc_proxy(const _MaybeReboundAlloc& __a, _Value __p) : _Base(__a), _M_data(__p) {}

};

}  // close namespace bsl

#endif  // INCLUDED_BSLSTP_ALLOC
