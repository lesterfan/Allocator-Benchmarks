#ifndef INCLUDED_BSLS_PLATFORM
#include <bsls_platform.h>
#endif

// This logic is required to block the g++ warning triggered by including
// a "deprecated" header.  The warning is generated by g++'s internal
// backward/backward_warning.h header, so we block its effect by defining its
// include guard.

#if defined(BSLS_PLATFORM_OS_SOLARIS) || defined(BSLS_PLATFORM_OS_LINUX)
#if defined(BSLS_PLATFORM_CMP_GNU) || defined(BSLS_PLATFORM_CMP_CLANG)
#define _BACKWARD_BACKWARD_WARNING_H 1
#endif
#endif

#undef BSL_OVERRIDES_STD

// Include all standard headers in reverse alphabetical order in dual STL mode.

#include <vector>
#include <valarray>
#include <utility>
#include <unordered_set>
#include <unordered_map>
#include <typeinfo>
#include <strstream>
#include <string>
#include <streambuf>
#include <stdexcept>
#include <stack>
#include <sstream>
#ifndef BDE_OMIT_INTERNAL_DEPRECATED
// #include <slist>
#endif  // BDE_OMIT_INTERNAL_DEPRECATED
#include <set>
#include <queue>
#include <ostream>
#include <numeric>
#include <new>
#include <memory>
#include <map>
#include <locale>
#include <list>
#include <limits>
#include <iterator>
#include <istream>
#include <iostream>
#include <iosfwd>
#include <ios>
#include <iomanip>
#ifndef BDE_OMIT_INTERNAL_DEPRECATED
// #include <hash_set>
// #include <hash_map>
#endif  // BDE_OMIT_INTERNAL_DEPRECATED
#include <functional>
#include <fstream>
#include <exception>
#include <deque>
#include <cwctype>
#include <cwchar>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstddef>
#include <cstdarg>
#include <csignal>
#include <csetjmp>
#include <complex>
#include <cmath>
#include <clocale>
#include <climits>
#include <ciso646>
#include <cfloat>
#include <cerrno>
#include <cctype>
#include <cassert>
#include <bitset>
#include <algorithm>

#ifdef std
# error std was not expected to be a macro
#endif
int main()
{
    std::size_t a = 0;
    std::pair<std::size_t,int> b(a, 0);
    return 0;
}

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
