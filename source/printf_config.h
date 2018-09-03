#ifndef PRINTF_CONFIG_H_
#define PRINTF_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus

// ntoa conversion buffer size, this must be big enough to hold
// one converted numeric number including padded zeros (dynamically created on stack)
// 32 byte is a good default
#define PRINTF_NTOA_BUFFER_SIZE    32U

// ftoa conversion buffer size, this must be big enough to hold
// one converted float number including padded zeros (dynamically created on stack)
// 32 byte is a good default
//#define PRINTF_FTOA_BUFFER_SIZE    32U

// define this to support floating point (%f)
//#define PRINTF_SUPPORT_FLOAT

// define this to support long long types (%llu or %p)
//#define PRINTF_SUPPORT_LONG_LONG

// define this to support the ptrdiff_t type (%t)
// ptrdiff_t is normally defined in <stddef.h> as long or long long type
//#define PRINTF_SUPPORT_PTRDIFF_T


#ifdef __cplusplus
}// closing brace for extern "C"
#endif // #ifdef __cplusplus

#endif // #ifndef PRINTF_CONFIG_H_
