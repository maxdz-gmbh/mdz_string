/**
 * \ingroup mdz libraries
 *
 * \author maxdz Software GmbH
 *
 * \par license
 * This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part of this source code package.
 *
 * \par description
 * Public types of different mdz libraries
 *
 */

#ifndef MDZ_TYPES_H
#define MDZ_TYPES_H

#include <stddef.h>

#include <stdint.h>
#include <limits.h>

#ifndef _WIN32
#include <pthread.h>
#endif

/**
 * Boolean type of mdz_containers library.
 */
#define mdz_false (unsigned char) 0
#define mdz_true (unsigned char) 1
typedef unsigned char mdz_bool;

#ifdef _WIN32
typedef void* HANDLE;
#endif

/**
 * Shared data for asynchronous calls
 */
struct mdz_asyncData
{
  /**
   * Pointer to mdz-container instance
   */
  void* m_pContainer;

  /**
   * Result of call. Invalid if call is not completely finished (m_bFinished is mdz_false)
   */
  size_t m_nResult;

  /**
   * Additional data returned by call (if any). Invalid if call is not completely finished (m_bFinished is mdz_false)
   */
  void* m_pData;

  /**
   * Thread on which the call is executed. May be used by client for wait operations
   */
#ifdef _WIN32
  HANDLE m_hThread;
#else
  pthread_t m_hThread;
#endif

  /**
   * mdz_true if the call is completely finished. Otherwise mdz_false (if interrupted/cancelled)
   */
  mdz_bool m_bFinished;

  /**
   * Should be set in mdz_true during call execution, to cancel the call. Otherwise mdz_false
   */
  mdz_bool m_bCancel;
};

/**
 * Progress callback function type. nPercent is current percent of progress [1..100]
 */
typedef void (*mdz_ProgressCallbackFunc)(unsigned char nPercent);

/**
 * Attachment type
 */
enum mdz_attach_type
{
  /**
   * Size is 0 after attachment
   */
  MDZ_ATTACH_ZEROSIZE = 0,

  /**
   * Size is Capacity minus 1 after attachment; 0-terminator is present
   */
  MDZ_ATTACH_SIZE_TERMINATOR /*= 1*/,

  /**
   * Size is Capacity after attachment; without 0-terminator
   */
  MDZ_ATTACH_SIZE_NO_TERMINATOR /*= 2*/
};

/**
 * Data endianness
 */
enum mdz_endianness
{
  /**
   * Undefined endianness
   */
  MDZ_ENDIAN_UNDEFINED = 0,

  /**
   * Little-endian
   */
  MDZ_ENDIAN_LITTLE /*= 1*/,

  /**
   * Big-endian
   */
  MDZ_ENDIAN_BIG /*= 2*/,

  /**
   * Error endianness
   */
  MDZ_ENDIAN_ERROR /*= 3*/
};

/**
 * String type
 */
enum mdz_string_type
{
  /**
   * ASCII/ANSI single-byte string
   */
  MDZ_STRING_ANSI = 0,

  /**
   * UTF-8 string
   */
  MDZ_STRING_UTF8 /*= 1*/,

  /**
   * UTF-16 string, platform endianness
   */
  MDZ_STRING_UTF16 /*= 2*/,

  /**
   * UTF-16 string, little endianness
   */
  MDZ_STRING_UTF16_LE /*= 3*/,

  /**
   * UTF-16 string, big endianness
   */
  MDZ_STRING_UTF16_BE /*= 4*/,

  /**
   * UTF-32 string, platform endianness
   */
  MDZ_STRING_UTF32 /*= 5*/,

  /**
   * UTF-32 string, little endianness
   */
  MDZ_STRING_UTF32_LE /*= 6*/,

  /**
   * UTF-32 string, big endianness
   */
  MDZ_STRING_UTF32_BE /*= 7*/,

  /**
   * wchar_t string, 2-bytes wide
   */
  MDZ_STRING_WCHAR_2 /*= 8*/,

  /**
   * wchar_t string, 4-bytes wide
   */
  MDZ_STRING_WCHAR_4 /*= 9*/
};

/**
 * Result of comparison
 */
enum mdz_compare_result
{
  /**
   * Equal
   */
  MDZ_COMPARE_EQUAL = 0,

  /**
   * Non-equal
   */
  MDZ_COMPARE_NONEQUAL /*= 1*/,

  /**
   * Greater
   */
  MDZ_COMPARE_GREATER /*= 2*/,

  /**
   * Smaller
   */
  MDZ_COMPARE_SMALLER /*= 3*/,

  /**
   * Comparison ended with error
   */
  MDZ_COMPARE_ERROR /*= 4*/
};

/**
 * Method of find
 */
enum mdz_find_method
{
  /**
   * standard C-library implementation
   */
  MDZ_FIND_CLIB = 0,
  
  /**
   * Optimized Boyer-Moore-Horspool search
   */
  MDZ_FIND_BMH /*= 1*/,

  /**
   * Improved "brute-force" search
   */
  MDZ_FIND_BRUTE /*= 2*/,

  /**
   * Optimized search for monotone sub-string in monotone string
   */
  MDZ_FIND_MONOTONE /*= 3*/
};

enum mdz_error
{
  /**
   * No error
   */
  MDZ_ERROR_NONE = 0,

  /**
   * Invalid "data" parameter
   */
  MDZ_ERROR_DATA /*= 1*/,

  /**
   * Not enough capacity
   */
  MDZ_ERROR_CAPACITY /*= 2*/,

  /**
   * Invalid "offset" parameter
   */
  MDZ_ERROR_OFFSET /*= 3*/,

  /**
   * "Count" parameter is zero
   */
  MDZ_ERROR_ZEROCOUNT /*= 4*/,

  /**
   * "Count" parameter is too big
   */
  MDZ_ERROR_BIGCOUNT /*= 5*/,

  /**
   * "Left" parameter is too big
   */
  MDZ_ERROR_BIGLEFT /*= 6*/,

  /**
   * "Right" parameter is too big
   */
  MDZ_ERROR_BIGRIGHT /*= 7*/,

  /**
   * Invalid "items" parameter
   */
  MDZ_ERROR_ITEMS /*= 8*/,

  /**
   * Container is empty
   */
  MDZ_ERROR_EMPTY /*= 9*/,

  /**
   * Container is not empty
   */
  MDZ_ERROR_NONEMPTY /*= 10*/,

  /**
   * Invalid "sub-container" parameter
   */
  MDZ_ERROR_SUBCONTAINER /*= 11*/,

  /**
   * Container is attached
   */
  MDZ_ERROR_ATTACHED /*= 12*/,

  /**
   * Memory allocation error
   */
  MDZ_ERROR_ALLOCATION /*= 13*/,

  /**
   * Data content error
   */
  MDZ_ERROR_CONTENT /*= 14*/,

  /**
   * Invalid endiannes type
   */
  MDZ_ERROR_ENDIANNESS /*= 15*/,

  /**
   * Invalid attach type
   */
  MDZ_ERROR_ATTACH_TYPE /*= 16*/,

  /**
   * Invalid find method
   */
  MDZ_ERROR_FIND_METHOD /*= 17*/,

  /**
   * Memory allocation for thread error
   */
  MDZ_ERROR_THREAD_ALLOC /*= 18*/,

  /**
   * Thread start error
   */
  MDZ_ERROR_THREAD_START /*= 19*/,

  /**
   * Invalid "source string" parameter
   */
  MDZ_ERROR_SOURCE /*= 20*/,

  /**
   * Invalid attach terminator
   */
  MDZ_ERROR_ATTACH_TERMINATOR /*= 21*/,

  /**
   * Invalid wchar_t size (expected is 2 or 4 bytes)
   */
  MDZ_ERROR_WCHAR_SIZE /*= 22*/,

  /**
   * Overlappend areas error
   */
  MDZ_ERROR_OVERLAP /*= 23*/
};

#endif
