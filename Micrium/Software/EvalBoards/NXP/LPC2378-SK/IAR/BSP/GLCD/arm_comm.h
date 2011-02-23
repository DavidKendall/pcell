/***************************************************************************
 **
 **    Common definition for IAR EW ARM
 **
 **    Used with ARM IAR C/C++ Compiler and Assembler.
 **
 **    (c) Copyright IAR Systems 2006
 **
 **    $Revision: 1.4 $
 **
 ***************************************************************************/
#ifndef __ARM_COMM_DEF_H
#define __ARM_COMM_DEF_H

#define MHZ           *1000000l
#define KHZ           *1000l
#define HZ            *1l

#ifndef FALSE
#define FALSE (1 == 0)
#endif

#ifndef TRUE
#define TRUE (1==1)
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef double                Flo64;    // Double precision floating point
typedef double              * pFlo64;
typedef float                 Flo32;    // Single precision floating point
typedef float               * pFlo32;
typedef signed   long long    Int64S;   // Signed   64 bit quantity
typedef signed   long long  * pInt64S;
typedef unsigned long long    Int64U;   // Unsigned 64 bit quantity
typedef unsigned long long  * pInt64U;
typedef signed   int          Int32S;   // Signed   32 bit quantity
typedef signed   int        * pInt32S;
typedef unsigned int          Int32U;   // Unsigned 32 bit quantity
typedef unsigned int        * pInt32U;
typedef signed   short        Int16S;   // Signed   16 bit quantity
typedef signed   short      * pInt16S;
typedef unsigned short        Int16U;   // Unsigned 16 bit quantity
typedef unsigned short      * pInt16U;
typedef signed   char         Int8S;    // Signed    8 bit quantity
typedef signed   char       * pInt8S;
typedef unsigned char         Int8U;    // Unsigned  8 bit quantity
typedef unsigned char       * pInt8U;
typedef unsigned char         Boolean;  // Boolean
typedef unsigned char       * pBoolean;


#endif // __ARM_COMM_DEF_H