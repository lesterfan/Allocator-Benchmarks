// bslstl_vector_test.h                                               -*-C++-*-
#ifndef INCLUDED_BSLSTL_VECTOR_TEST
#define INCLUDED_BSLSTL_VECTOR_TEST

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide support for the 'bslstl_vector.t.cpp' test driver.
//
//@CLASSES:
//
//@SEE_ALSO: bslstl_vector
//
//@AUTHOR: Pablo Halpern (phalpern), Herve Bronnimann (hbronnim),
//         Alisdair Meredith (ameredit)
//
//@DESCRIPTION: This component provides a second translation unit to spread the
// load of building and running the 'vector' test cases.  As the number of test
// concerns grows, and the number of types to instantiate 'vector' with in
// order to gain complete code coverage grows, we have exceeded the limits of
// certain compilers.  For example, gcc will not produce a valid '.o' file as
// the number of template instantiations exceeds some internal tables.  In
// order to continue providing full coverage, the standard value-semantic type
// test cases 1-10 are handled by the primary component test driver, and the
// tests for all remaining functionality are moved into this component, that
// comprises only a test driver.

#ifndef INCLUDED_BSLSTL_VECTOR
#include <bslstl_vector.h>
#endif

#endif
// ----------------------------------------------------------------------------
// Copyright 2017 Bloomberg Finance L.P.
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
