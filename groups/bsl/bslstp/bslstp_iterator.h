// bslstp_iterator.h                                                  -*-C++-*-
#ifndef INCLUDED_BSLSTP_ITERATOR
#define INCLUDED_BSLSTP_ITERATOR

//@PURPOSE: Provide facility for STLPort implementation.
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
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Copyright (c) 1996-1998
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
#error "bslstp_iterator is not for publication"
#endif

#ifndef INCLUDED_CSTDDEF
#include <cstddef>
#define INCLUDED_CSTDDEF
#endif

namespace bsl {

template <class _Tp>
struct _Nonconst_traits;

template <class _Tp>
struct _Const_traits {
  typedef _Tp value_type;
  typedef const _Tp&  reference;
  typedef const _Tp*  pointer;
  typedef _Nonconst_traits<_Tp> _Non_const_traits;
};

template <class _Tp>
struct _Nonconst_traits {
  typedef _Tp value_type;
  typedef _Tp& reference;
  typedef _Tp* pointer;
  typedef _Nonconst_traits<_Tp> _Non_const_traits;
};

}  // close namespace bsl

#endif /* INCLUDED_BSLSTP_ITERATOR */

// Local Variables:
// mode:C++
// End:
