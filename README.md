**NOTE:** All 0.x releases are kind of "alpha-versions" without expectations of interface backward-compatibility.

## Table of Contents
[mdz_string Overview](#mdz_string-Overview)<br>
[mdz_string Advantages](#mdz_string-Advantages)<br>
[Performance Comparison](#performance-comparison)<br>
[mdz_string Usage](#mdz_string-Usage)<br>
[mdz_ansi Overview](#mdz_ansi-Overview)<br>
[mdz_wchar Overview](#mdz_wchar-Overview)<br>
[mdz_utf8 Overview](#mdz_utf8-Overview)<br>
[mdz_utf16 Overview](#mdz_utf16-Overview)<br>
[mdz_utf32 Overview](#mdz_utf32-Overview)<br>
[Licensing info](#Licensing-info)<br>

## mdz_string Overview

Wiki: [mdz_string Wiki]<br>
file: *"mdz_string.h"*

Please take a look at *"mdz_string.h"* file or [mdz_string Wiki] site for detailed functions descriptions.

[mdz_string Wiki]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_string-overview

[mdz_string] - very lightweight and versatile C library for handling single-byte (ASCII/ANSI) strings and Unicode strings, developed by [maxdz Software GmbH].The library supports ASCII/ANSI, UTF8, UTF16, UTF32, wchar strings. Source code of library is highly-portable, conforms to ANSI C 89/90 Standard. Builds for Win32/Win64, Linux, FreeBSD, Android, macOS are available.

Only shared/dynamically loaded libraries (*.so* and *.dll* files with import libraries) are available for evaluation testing purposes. Static libraries/source code are covered by our commercial licenses.

**Linux** binaries are built against Linux Kernel 2.6.18 - and thus should be compatible with Debian (from ver. 4.0), Ubuntu (from ver. 8.04), Fedora (from ver. 9)

**FreeBSD** binaries - may be used from FreeBSD ver. 7.0

**Win32** binaries are built using Visual Studio Platform Toolset "v90", thus are compatible with Windows versions from Windows 2000.<br>
**Win64** binaries are built using Visual Studio Platform Toolset "v100", thus are compatible with Windows versions from Windows XP.<br>

**Android** x86/armeabi-v7a binaries - may be used from Android API level 16 ("Jelly Bean" ver. 4.1.x)<br>
**Android** x86_64/arm64-v8a binaries - may be used from Android API level 21 ("Lollipop" ver. 5.0)

**macOS** binaries - x86_64, from *MacOS X v10.6.0*

[mdz_string]: https://github.com/maxdz-gmbh/mdz_string
[maxdz Software GmbH]: https://maxdz.com/

## mdz_string Advantages

**1. High portability:** the whole code conforms to ANSI C 89/90 Standard. Multithreading/asynchronous part is POSIX compatible (under UNIX/Linux).

**2. Little dependencies:** basically *mdz_string* functions are only dependend on standard C-library memory-management/access functions. Multithreading part is dependend on POSIX *pthreads* API (under UNIX/Linux) and old process control/synchronization API (from Windows 2000). It means you can use library in your code withouth any further dependencies except standard platform libraries/APIs.

**3. Fast:** Our single-byte (ASCII/ANSI) strings are very fast, concerning operations like searching, insertion, deletion, etc. especially for very large (like hundreds of megabytes or gigabytes) strings.

**4. Flexibilty:** nearly all functions our single-byte (ASCII/ANSI) strings, contain not only "left position" but also "right position" parameters to limit processed area from right. Also library contains more string functions than according STL, boost or glib analogs have.

**5. Extended error-checking:** all functions preserve internal error-code pointing the problem. It is possible to use strict error-checking (when all preserved error-codes should be *MDZ_ERROR_NONE*) or "relaxed"-checking - when only returned *mdz_false* will indicate error.

**6. Extended control:** strings do only explicit operations. It means for example, when "insert" function is called with auto-reservation flag set in *mdz_false* - it will return error if there is not enough capacity in string. No implicit reservations will be made.

**7. Attached usage:** strings should not necessarily use dynamically-allocated memory - which may be not available on your embedded system (or if malloc()/free() are forbidden to use in your safety-critical software). Just attach string/data to your statically-allocated memory and use all strings functionality.

**8. Cache-friendly:** it is possible to keep controlling and data parts together in memory using "embedded part".

**9. Unicode support:** UTF-8, UTF-16, UTF-32 are supported.

**10. wchar_t support:** also wchar_t strings are supported, with 2 and 4 bytes-large *wchar_t* characters.

**11. Endianness-aware strings:** wchar, utf16 and utf32 strings are endiannes-aware thus may be used to produce and manipulate strings with pre-defined endianness even if endianness of host differs.

**12. Unicode "surrogate-pairs" awareness:** 2-byte Unicode strings correctly process/distinguish "surrogate-pairs" as 1 Unicode symbol.

**13. Asynchronous execution:** almost all functions of single-byte (ASCII/ANSI) strings and *insert* functions can be executed asynchronously

## Performance Comparison

Performance comparison tables for *[mdz_ansi_find]*() and *[mdz_ansi_firstOf]*() give an idea about *mdz_ansi* library overall performance on different platforms compared to STL and standard C library. Modern implementationsof STL and standard C library are pretty fast, using optimized versions of memory-access functions.

- **[mdz_ansi_find]() Test**

Following tests are executed:

- Test *1/100M*": Find 1 byte - in the end of 100M bytes long string<br>
- Test *5/100M*": Find 5 bytes long string - in the end of 100M bytes long string<br>
- Test *10/100M*": Find 10 bytes long string - in the end of 100M bytes long string<br>
- Test *100/100M*": Find 100 bytes long string - in the end of 100M bytes long string<br>
- Test *1K/100M*": Find 1K bytes long string - in the end of 100M bytes long string<br>
- Test *500K/1M*": Find 500K bytes long string - in the end of 1M bytes long string<br>
- Test *100M-100/100M*": Find "100M minus 100" bytes long string - in the end of 100M bytes long string<br>
- Test *100M/100M*": Find 100M bytes long string - in 100M bytes long string<br>

For **Windows 10 (64-bit)** on *Intel i5-6600 @ 3.30GHz (4 cores/4 threads)*<br>

**Monotone test** : "long string" and "string to find" are both filled with '1's; on the last position of both strings is '2'

monotone = MDZ_FIND_MONOTONE method<br>
clib = MDZ_FIND_CLIB method (standard C library)<br>
brute = MDZ_FIND_BRUTE method<br>
bmh = MDZ_FIND_BMH method

- VC++ toolset v140 (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi, monotone | mdz_ansi, clib | mdz_ansi, brute |  mdz_ansi, bmh |std::string.find() | clib (strstr())|
| :---:| ---: | ---: | ---: | ---: | ---: | ---: |
| 1/100M| **70,351** |  |  |  | 162,681 | 70,579 |
| 5/100M| **407,668** | 460,052 | 3,045,869 | 781,655 | 3,381,061 | 482,075 |
| 10/100M| 1,334,782 | **707,712** | 4,394,022 | 780,128 | 4,206,329 | 731,395 |
| 100/100M| 1,333,516 | 10,914,646 | 15,779,350 | **781,370** | 15,652,407 | 11,253,026 |
| 1K/100M| 1,332,838 | 70,179,989 | 139,398,637 | **781,439** | 139,808,212 | 75,808,535 |
| 500K/1M| 13,202 | 166,409,422 | 323,375,345 | **9,411** | 324,276,637 | 178,302,908 |
| 100M-100/100M| 1,262,919 | 10,884,012 | 14,182,350 | **1,066,737** | 14,150,110 | 10,383,086 |
| 100M/100M| 117,970 | |  |  | 144,573 | **114,565** |

- MinGW/gcc toolset (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi, monotone | mdz_ansi, clib | mdz_ansi, brute |  mdz_ansi, bmh |
| :---:| ---: | ---: | ---: | ---: |
| 1/100M| 148,067 |  |  |  |
| 5/100M| **534,070** | 1,599,882 | 6,825,862 | 784,326 |
| 10/100M| **551,404** | 3,635,378 | 7,898,385 | 783,832 |
| 100/100M| **550,701** | 32,447,796 | 20,451,496 | 786,006 |
| 1K/100M| **551,213** | 348,052,489 | 117,762,194 | 784,335 |
| 500K/1M| 7,851 | 814,620,053 | 246,574,213 | **6,263** |
| 100M-100/100M| 997,729 | 33,028,357 | 11,705,985| **456,680** |
| 100M/100M| 328,564 | |  |  |

- **[mdz_ansi_firstOf]() Test**

Following tests are executed:

- Test *1/100M*": Find first of 1 byte - in the end of 100M bytes long string<br>
- Test *5/100M*": Find first of 5 bytes - in the end of 100M bytes long string<br>
- Test *20/100M*": Find first of 20 bytes - in the end of 100M bytes long string<br>
- Test *50/100M*": Find first of 50 bytes - in the end of 100M bytes long string<br>
- Test *100/100M*": Find first of 100 bytes - in the end of 100M bytes long string<br>

For **Windows 10 (64-bit)** on *Intel i5-6600 @ 3.30GHz (4 cores/4 threads)*<br>

- VC++ toolset v140 (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi| std::string.find_first_of() | clib (strcspn())|
| :---:| ---: | ---: | ---: |
| 1/100M| **70,078** | 163,666 | 2,085,714 |
| 5/100M| **370,204** | 3,719,660 | 2,077,677 |
| 20/100M| **369,162** | 5,714,212 | 2,076,031 |
| 50/100M| **368,994** | 10,965,401 | 2,078,038 |
| 100/100M| **369,360** | 18,727,283 | 2,076,740 |

- MinGW/gcc toolset (32-bit)<br>
(all numbers are in microseconds measured using *QueryPerformanceCounter()* in main execution thread)

| Test  | mdz_ansi|
| :---:| ---: |
| 1/100M| 153,511 |
| 5/100M| 278,387 |
| 20/100M| 276,389 |
| 50/100M| 275,956 |
| 100/100M| 277,709 |

[mdz_ansi_find]: https://github.com/maxdz-gmbh/mdz_ansi/wiki/mdz_ansi_find_async
[mdz_ansi_firstOf]: https://github.com/maxdz-gmbh/mdz_ansi/wiki/mdz_ansi_firstOf_async

## mdz_string Usage

**mdz_string** is implemented with strict input parameters checking. It means *mdz_false* or some other error indication will be returned if one or several input parameters are invalid - even if such an invalidity doesn't lead to inconsistence (for example adding or removing 0 items).

**Test license generation:** - in order to get free test-license, please proceed to our Shop page [maxdz Shop] and register an account. After registration you will be able to obtain free 30-days test-licenses for our products using "Obtain for free" button. 
Test license data should be used in *mdz_string_init()* call for library initialization.

**NOTE:** All 0.x releases are kind of "beta-versions" and can be used 1) only with test-license (during test period of 30 days, with necessity to re-generate license for the next 30 days test period) and 2) without expectations of interface backward-compatibility.

[mdz_string Wiki]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_string-overview
[maxdz Shop]: https://maxdz.com/shop.php

#### Code Example

*mdz_string_init()* with license information should be called for library initialization before any subsequent calls:

```
#include <mdz_string.h>

int main(int argc, char* argv[])
{
  /* mdz_string library initialization using test info retrieved after license generation (see "Test license generation" above) */
  
  mdz_bool bRet = mdz_string_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  ...

  mdz_string_uninit(); /* call for un-initialization of library */
  
  return 0;  
}
```

[mdz_utf8_create]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_utf8_create
[mdz_utf8_destroy]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_utf8_destroy

After library initialization call *[mdz_utf8_create]*() for **utf8** string creation. There should be also symmetric *[mdz_utf8_destroy]*() call for every create, otherwise allocated for string memory remains occupied:

```
#include <mdz_string.h>
#include <mdz_utf8.h>

int main(int argc, char* argv[])
{
  mdz_bool bRet = mdz_string_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  
  // initialize pAnsi
  
  mdz_Utf8* pUtf8 = mdz_utf8_create(0); // create utf8-string
  ...
  ...
  // use pUtf8
  ...
  ...
  // destroy pUtf8
  
  mdz_utf8_destroy(&pUtf8); // after this pUtf8 should be NULL
  
  mdz_string_uninit();
  ...
}
```

Use *mdz_Utf8** pointer for subsequent library calls:

```
#include <mdz_string.h>
#include <mdz_utf8.h>

int main(int argc, char* argv[])
{
  mdz_bool bRet = mdz_string_init("<first-name-hash>", "<last-name-hash>", "<email-hash>", "<license-hash>");
  
  mdz_Utf8* pUtf8 = mdz_utf8_create(0); // create utf8-string

  // reserve memory for 5 elements
  
  bRet = mdz_utf8_reserve(pUtf8, 5);
  
  // insert 'b' in front position with auto-reservation if necessary
  
  bRet = mdz_utf8_insertAnsi(pUtf8, 0, "b", 1, mdz_true); // "b" after this call
  
  // append string with "cde" with auto-reservation if necessary
  
  bRet = mdz_utf8_insert(pUtf8, (size_t) -1, "cde", 3, mdz_true); // "bcde" after this call
  
  ...
  
  mdz_utf8_destroy(&pUtf8);
  
  mdz_string_uninit();
  ...
}
```

## mdz_ansi Overview
Wiki: [mdz_ansi Wiki]<br>
file: *"mdz_ansi.h"*

Please take a look at *"mdz_ansi.h"* file or [mdz_ansi Wiki] site for detailed functions descriptions.

[mdz_ansi Wiki]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_ansi-overview

## mdz_wchar Overview
Wiki: [mdz_wchar Wiki]<br>
file: *"mdz_wchar.h"*

Please take a look at *"mdz_wchar.h"* file or [mdz_wchar Wiki] site for detailed functions descriptions.

[mdz_wchar Wiki]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_wchar-overview

## mdz_utf8 Overview
Wiki: [mdz_utf8 Wiki]<br>
file: *"mdz_utf8.h"*

Please take a look at *"mdz_utf8.h"* file or [mdz_utf8 Wiki] site for detailed functions descriptions.

[mdz_utf8 Wiki]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_utf8-overview

## mdz_utf16 Overview
Wiki: [mdz_utf16 Wiki]<br>
file: *"mdz_utf16.h"*

Please take a look at *"mdz_utf16.h"* file or [mdz_utf16 Wiki] site for detailed functions descriptions.

[mdz_utf16 Wiki]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_utf16-overview

## mdz_utf32 Overview
Wiki: [mdz_utf32 Wiki]<br>
file: *"mdz_utf32.h"*

Please take a look at *"mdz_utf32.h"* file or [mdz_utf32 Wiki] site for detailed functions descriptions.

[mdz_utf32 Wiki]: https://github.com/maxdz-gmbh/mdz_string/wiki/mdz_utf32-overview

## Licensing info

Use of **mdz_string** library is regulated by license agreement in *LICENSE.txt*

Basically private non-commercial "test" usage is unrestricted. Commercial usage of library (incl. its source code) will be regulated by according license agreement.
