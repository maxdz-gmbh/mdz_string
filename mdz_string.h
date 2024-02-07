/**
 * \ingroup mdz_string library
 *
 * \author maxdz Software GmbH
 *
 * \par license
 * This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part of this source code package.
 *
 * \par description
 * mdz_string initialization functions.
 *
 * \par portability
 * Source code of library conforms to ANSI C 89/90 Standard.
 *
 * \version 0.4
 *
 * \date 2021-04
 *
 */

#ifndef MDZ_STRING_H
#define MDZ_STRING_H

#include "mdz_types.h"

#include <stdint.h>

/**
 * Handle of ANSI string in mdz_string library
 */
struct mdz_Ansi
{
  /**
   * Pointer to data of string. Do not change it directly.
   */
  char* m_pData;

  /**
   * Error code if operation failed or there are some inconsistences.
   */
  enum mdz_error m_enErrorCode;
};

/**
 * Handle of "wide"-character string in mdz_string library
 */
struct mdz_Wchar
{
  /**
   * Pointer to data of string. Do not change it directly.
   */
  const wchar_t* m_pData;

  /**
   * Error code if operation failed or there are some inconsistences.
   */
  enum mdz_error m_enErrorCode;
};

/**
 * Handle of utf8 string in mdz_string library
 */
struct mdz_Utf8
{
  /**
   * Pointer to data of string. Do not change it directly.
   */
  unsigned char* m_pData;

  /**
   * Error code if operation failed or there are some inconsistences.
   */
  enum mdz_error m_enErrorCode;
};

/**
 * Handle of UTF-16 string in mdz_string library
 */
struct mdz_Utf16
{
  /**
   * Pointer to data of string. Do not change it directly.
   */
  const uint16_t* m_pData;

  /**
   * Error code if operation failed or there are some inconsistences.
   */
  enum mdz_error m_enErrorCode;
};

/**
 * Handle of UTF-32 string in mdz_string library
 */
struct mdz_Utf32
{
  /**
   * Pointer to data of string. Do not change it directly.
   */
  const uint32_t* m_pData;

  /**
   * Error code if operation failed or there are some inconsistences.
   */
  enum mdz_error m_enErrorCode;
};

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \defgroup Init functions
 */

/**
 * Initializes mdz_string library. This function should be called before any other function of the library.
 * \param pFirstNameHash - user first name hash code
 * \param pLastNameHash - user last name hash code
 * \param pEmailHash - user e-mail hash code
 * \param pLicenseHash - license hash code
 * \return:
 * mdz_true - if the initialization has succeed, otherwise false
 */
mdz_bool mdz_string_init(const uint32_t* pFirstNameHash, const uint32_t* pLastNameHash, const uint32_t* pEmailHash, const uint32_t* pLicenseHash);

/**
 * Initializes mdz_string library. This function should be caled before any other function of the library.
 * Memory for license data starts at position pStart. Size of internal initialization structure is returned in pSize.
 * \param pFirstNameHash - user first name hash code
 * \param pLastNameHash - user last name hash code
 * \param pEmailHash - user e-mail hash code
 * \param pLicenseHash - license hash code
 * \param pStart - memory start position of license data
 * \param nAreaSize - size of available memory from pStart in bytes. Should be large enough for license data (> 500 bytes)
 * \param pOutSize - actual size of placed license data in bytes
 * \return:
 * mdz_true - if the initialization has succeed, otherwise false
 */
mdz_bool mdz_string_init_attached(const uint32_t* pFirstNameHash, const uint32_t* pLastNameHash, const uint32_t* pEmailHash, const uint32_t* pLicenseHash, const char* pStart, size_t nAreaSize, size_t* pOutSize);

/**
 * Un-initializes mdz_string library and frees corresponding memory allocations.
 */
void mdz_string_uninit(void);

#ifdef __cplusplus
}
#endif

#endif
