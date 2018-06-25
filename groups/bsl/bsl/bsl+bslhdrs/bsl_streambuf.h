// bsl_streambuf.h                                                    -*-C++-*-
#ifndef INCLUDED_BSL_STREAMBUF
#define INCLUDED_BSL_STREAMBUF

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide functionality of the corresponding C++ Standard header.
//
//@SEE_ALSO: package bsl+stdhdrs
//
//@AUTHOR: Arthur Chiu (achiu21)
//
//@DESCRIPTION: Provide types, in the 'bsl' namespace, equivalent to those
// defined in the corresponding C++ standard header.  Include the native
// compiler-provided standard header, and also directly include Bloomberg's
// implementation of the C++ standard type (if one exists).  Finally, place the
// included symbols from the 'std' namespace (if any) into the 'bsl' namespace.

#ifndef INCLUDED_BSLS_NATIVESTD
#include <bsls_nativestd.h>
#endif

#include <streambuf>

#ifndef BDE_OMIT_INTERNAL_DEPRECATED
#if !defined(BDE_DONT_ALLOW_TRANSITIVE_INCLUDES) && \
     defined(BDE_BUILD_TARGET_STLPORT)

// Code in Robo depends on <ios> included transitively with <streambuf> and it
// fails to build otherwise in the stlport4 mode on Sun.
#include <bsl_ios.h>

#endif
#endif  // BDE_OMIT_INTERNAL_DEPRECATED

namespace bsl {
    // Import selected symbols into bsl namespace

    using native_std::basic_streambuf;
    using native_std::streambuf;
    using native_std::wstreambuf;

#ifndef BDE_OMIT_INTERNAL_DEPRECATED
    using native_std::bad_exception;
    using native_std::bidirectional_iterator_tag;
    using native_std::ctype;
    using native_std::ctype_byname;
    using native_std::exception;
    using native_std::forward_iterator_tag;
    using native_std::input_iterator_tag;
    using native_std::ios_base;
    using native_std::istreambuf_iterator;
    using native_std::iterator;
    using native_std::locale;
    using native_std::ostreambuf_iterator;
    using native_std::output_iterator_tag;
    using native_std::random_access_iterator_tag;
    using native_std::set_terminate;
    using native_std::set_unexpected;
    using native_std::swap;
    using native_std::terminate;
    using native_std::terminate_handler;
    using native_std::uncaught_exception;
    using native_std::unexpected;
    using native_std::unexpected_handler;
    using native_std::use_facet;
#endif  // BDE_OMIT_INTERNAL_DEPRECATED
}  // close package namespace

#endif

// ----------------------------------------------------------------------------
// Copyright 2013 Bloomberg Finance L.P.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ----------------------------- END-OF-FILE ----------------------------------
