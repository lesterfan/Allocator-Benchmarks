// iostream.h                                                         -*-C++-*-

//@PURPOSE: Provide backwards compatibility for STLPort header
//
//@SEE_ALSO: package bsl+stdhdrs
//
//@AUTHOR: Arthur Chiu (achiu21)
//
//@DESCRIPTION: This component provides backwards compatibility for Bloomberg
// libraries that depend on non-standard STLPort header files.  This header
// includes the corresponding C++ header and provides any additional symbols
// that the STLPort header would define via transitive includes.

#include <bsl_iostream.h>

#ifndef BDE_OMIT_INTERNAL_DEPRECATED
#ifndef BDE_DONT_ALLOW_TRANSITIVE_INCLUDES
    // Permit reliance on transitive includes within robo.
#include <ios.h>
#include <ostream.h>

// Transitive using - <ios.h> includes <ios>, which includes <iosfwd>, which
// then contains definition of 'ostream', 'istream', 'ifstream' and 'ofstream'.
using std::ifstream;
using std::istream;
using std::ofstream;
using std::ostream;
#endif
#endif // BDE_OMIT_INTERNAL_DEPRECATED

using std::cin;
using std::cout;
using std::cerr;
using std::clog;
using std::wcin;
using std::wcout;
using std::wcerr;
using std::wclog;

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
