// bslmf_addpointer.h                                                 -*-C++-*-
#ifndef INCLUDED_BSLMF_ADDPOINTER
#define INCLUDED_BSLMF_ADDPOINTER

#ifndef INCLUDED_BSLS_IDENT
#include <bsls_ident.h>
#endif
BSLS_IDENT("$Id: $")

//@PURPOSE: Provide meta-function to transform a type to pointer to that type.
//
//@CLASSES:
//  bsl::add_pointer: meta-function to transform a type to a pointer type
//
//@SEE_ALSO: bslmf_removepointer
//
//@AUTHOR:
//
//@DESCRIPTION: This component defines a meta-function, 'bsl::add_pointer',
// that may be used to transform a type to a pointer to that type.
//
// 'bsl::add_pointer' meets the requirements of the 'add_pointer' template
// defined in the C++11 standard [meta.trans.ptr].
//
///Usage
///-----
// In this section we show intended use of this component.
//
///Example 1: Transform Type to Pointer Type to that Type
/// - - - - - - - - - - - - - - - - - - - - - - - - - - -
// Suppose that we want to transform a type to a pointer type to that type.
//
// First, we create two 'typedef's -- a pointer type ('MyPtrType') and the type
// pointed to by the pointer type ('MyType'):
//..
//  typedef int   MyType;
//  typedef int * MyPtrType;
//..
// Now, we transform 'MyType' to a pointer type to 'MyType' using
// 'bsl::add_pointer' and verify that the resulting type is the same as
// 'MyPtrType':
//..
//  assert((bsl::is_same<bsl::add_pointer<MyType>::type,
//                       MyPtrType>::value));
//..

#ifndef INCLUDED_BSLSCM_VERSION
#include <bslscm_version.h>
#endif

#ifndef INCLUDED_BSLS_COMPILERFEATURES
#include <bsls_compilerfeatures.h>
#endif

#ifndef INCLUDED_BSLS_PLATFORM
#include <bsls_platform.h>
#endif

#ifndef INCLUDED_BSLS_STDDEF_H
#include <stddef.h>
#endif

#ifndef BDE_DONT_ALLOW_TRANSITIVE_INCLUDES

#ifndef INCLUDED_BSLMF_REMOVEREFERENCE
#include <bslmf_removereference.h>
#endif

#endif // BDE_DONT_ALLOW_TRANSITIVE_INCLUDES

namespace BloombergLP {
namespace bslmf {


struct AddPointer_Compute {
    // This utility 'struct' is a private implementation detail that hosts an
    // overloaded pair of functions that, through SFINAE, can determine whether
    // it is legal to form a pointer to a specified 'TYPE'.

    struct LargeResult {
        char d_dummy[99];
    };

    template <class TYPE>
    static LargeResult canFormPointer(TYPE *);

    template <class TYPE>
    static char canFormPointer(...);
};

template <class TYPE,
          size_t = sizeof(AddPointer_Compute::canFormPointer<TYPE>(0))>
struct AddPointer_Impl {
    // For the majority of types, it is perfectly reasonable to form the type
    // 'TYPE *'.

    typedef TYPE * type;        // A pointer to the original 'TYPE'.
};

template <class TYPE>
struct AddPointer_Impl<TYPE, 1u> {
    // For special cases, such as references and "abominable" functions, it is
    // not legal to form a pointer, and this parital specialization will be
    // chosen by the computed default template parameter.

    typedef TYPE type;  // Do not modify the type if a pointer is not valid.
};

#if defined(BSLS_PLATFORM_CMP_IBM)
template <class TYPE>
struct AddPointer_Impl<TYPE[], 1u> {
    // IBM miscomputes the SFINAE condition for arrays of unknown bound, so we
    // provide an additional partial specialization for this platform.

    typedef TYPE (*type)[];     // A pointer to the original 'TYPE[]'.
};
#endif


}  // close package namespace
}  // close enterprise namespace


namespace bsl {

                         // ==================
                         // struct add_pointer
                         // ==================

template <class TYPE>
struct add_pointer {
    // This 'struct' template implements the 'add_pointer' meta-function
    // defined in the C++11 standard [meta.trans.ptr], providing an alias,
    // 'type', that returns the result.  If the (template parameter) 'TYPE' is
    // not a reference type, then 'type' is an alias to a pointer type that
    // points to 'TYPE'; otherwise, 'type' is an alias to a pointer type that
    // points to the type referred to by the reference 'TYPE', unless it is not
    // legal to form such a pointer type, in which case 'type' is an alias for
    // 'TYPE'.

    typedef typename BloombergLP::bslmf::AddPointer_Impl<TYPE>::type type;
        // This 'typedef' is an alias to a pointer type that points to the
        // (template parameter) 'TYPE' if it is not a reference type;
        // otherwise, this 'typedef' is an alias to a pointer type that points
        // to the type referred to by the reference 'TYPE'.
};

template <class TYPE>
struct add_pointer<TYPE &> {
    // If we can form a reference to 'TYPE', then we can also form a pointer to
    // it.  In particular, we know that it is not 'void' (which should still
    // work) or an "abominable" function type with a trailing cv-qualifier.
    // Note that this partial specialization is necessary to avoid falling into
    // degenerate (non-compiling) cases in the implementation meta-program.

    typedef TYPE * type;
};

#if defined(BSLS_COMPILERFEATURES_SUPPORT_RVALUE_REFERENCES)
template <class TYPE>
struct add_pointer<TYPE &&> {
    // If we can form a reference to 'TYPE', then we can also form a pointer to
    // it.  In particular, we know that it is not 'void' (which should still
    // work) or an "abominable" function type with a trailing cv-qualifier.
    // Note that this partial specialization is necessary to avoid falling into
    // degenerate (non-compiling) cases in the implementation meta-program.

    typedef TYPE * type;
};
#endif

}  // close namespace bsl

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
