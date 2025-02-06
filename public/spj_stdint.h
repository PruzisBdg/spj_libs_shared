/*******************************************************************

                  Sized-Type Definitions

   This Wrapper translates the sized types in <stdint.h> <stdbool.h> into the libraies'
   local dialect U8, U16 etc. The libraries predate C99 (when uint8_t, uint16_t etc were
   defined).

   If no <stdint> then U8, U16 etc are defined directly in terms of base C types which
   should (nearly always) be the intended size.

   *** It's 2024. Are there any pre-C99 tools left? ****

*******************************************************************/

#ifndef SPJ_STDINT_H
#define SPJ_STDINT_H

/* Specify an extension for GCC based compilers */
#if defined(__GNUC__)
#define __EXTENSION __extension__
#else
#define __EXTENSION
#endif

/* ---------------- Sized Integer Types --------------------------------------

   C99 and later supplies sized integer types in <stdint.h>. For older/other compilers
   assume 32bit ints and 16bit shorts.
*/
#ifndef __STDC_VERSION__
   #define __STDC_VERSION__ 0L
#endif // __STDC_VERSION__

// C99 and above; use <stdint> & <stdbool>.
#if __STDC_VERSION__ >= 199900L
#include <stdint.h>
typedef int8_t    S8;
typedef uint8_t   U8;
typedef int16_t   S16;
typedef uint16_t  U16;
typedef int32_t   S32;
typedef uint32_t  U32;
typedef int64_t   S64;
typedef uint64_t  U64;

#include <stdbool.h>
typedef bool BOOL;
#define FALSE false
#define TRUE true
#else
typedef signed char        S8;
typedef unsigned char      U8;
typedef signed short int   S16;
typedef unsigned short int U16;
typedef signed long int    S32;
typedef unsigned long int  U32;
typedef signed long long   S64;
typedef unsigned long long U64;

// If no <stdint> make uintptr_t 32bit; good for any legacy non-GCC.
typedef U32 uintptr_t;

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;    /* Undefined size */
typedef  unsigned char bool;
#endif

typedef char               C8;

// ---------------- ends: Sized Integer types ---------------------------------


#if !defined(__PACKED)
    #define __PACKED
#endif

#define _S16(n)  ((S16)(n))

/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
#if !defined(__18CXX)
__EXTENSION typedef signed long long    INT64;
#endif

#define _U8(n)  ((U8)(n))
#define _U16(n)  ((U16)(n))

//typedef enum _BIT { CLEAR = 0, SET } BIT;

typedef U8 BIT;

#define _ToBool(n) ((n) == 0 ? FALSE : TRUE)

/* ------------ Legacy Extrema for sized integer types --------------------------------

   Again these are now supported by <stdint>; but keep for legacy code.
*/
#define MIN_U8 0
#define MAX_U8 0xFF
#define MIN_S8 (-128)
#define MAX_S8 127
#define MIN_C8 0
#define MAX_C8 127

#define MIN_U16 0
#define MAX_U16 0xFFFF
#define MAX_S16 32767
#define MIN_S16 (-32768)

#define MIN_U32 0
#define MAX_U32 0xFFFFFFFF

#define MAX_S32  ((S32)( 2147483647LL))
#define MIN_S32  ((S32)(-2147483648LL))

#define MAX_U64 0xFFFFFFFFFFFFFFFFULL
#define MIN_U64 0

#define MAX_S64 0x7FFFFFFFFFFFFFFFLL
#define MIN_S64 (-MAX_S64-1)


#define HIGH_BYTE(n) ((U8)((n) >> 8))
#define LOW_BYTE(n)  ((U8)((n) & 0xFF))

#define LOW_NIBBLE(b)  ((U8)((b) & 0x0F))
#define HIGH_NIBBLE(b)   ((U8)(((b) >> 4) & 0x0F))

#define HIGH_WORD(n) ((U16)((n) >> 16))
#define LOW_WORD(n)  ((U16)((n) & 0xFFFF))

#define HIGH_DWORD(n) ((U32)((n) >> 32))
#define LOW_DWORD(n)  ((U32)((n) & 0xFFFFFFFF))


/* 24-bit type only available on C18 */
#if defined(__18CXX)
typedef unsigned short long UINT24;
#endif
//typedef unsigned long int   UINT32;     /* other name for 32-bit integer */

/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
#if !defined(__18CXX)
__EXTENSION typedef unsigned long long  UINT64;
#endif

// Records in an array
#define RECORDS_IN(a)  (sizeof(a)/sizeof(a[0]))

// Offset of an element in a struct
#define OFFSET_OF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))

#define MAX(a,b)  ((a) > (b) ? (a) : (b))
#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define ABS(n)    ((n) < 0 ? -(n) : (n))

#define CONST const

// -------------------------------- Function attributes ------------------------------
#define PUBLIC
#define PROTECTED
#define PRIVATE static


/* ------------------- Token Pasting --------------------------------------

   When a token paste is used directly in a macro, an argument is not checked
   for further expansion before being pasted (unlike when the argument is
   concatentated). Embedding the paste itself in macro allows expansion prior
   to pasting.
*/
#define CAT(x,y)  x##y
#define XCAT(x,y)  CAT(x,y)

#endif /* SPJ_STDINT_H */
