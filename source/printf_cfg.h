#ifndef PRINTF_CONFIG_H_
#define PRINTF_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus

// buffer size used for printf (created on stack)
#define PRINTF_BUFFER_SIZE	64U

// ntoa conversion buffer size, this must be big enough to hold one converted numeric number (created on stack)
#define NTOA_BUFFER_SIZE	16U

// ftoa conversion buffer size, this must be big enough to hold one converted float number (created on stack)
//#define FTOA_BUFFER_SIZE      32U

// define this to support floating point (%f)
//#define PRINTF_FLOAT_SUPPORT

// define this to support long long types (%llu or %p)
//#define PRINTF_LONG_LONG_SUPPORT


#ifdef __cplusplus
}// closing brace for extern "C"
#endif // #ifdef __cplusplus

#endif // #ifndef PRINTF_CONFIG_H_
