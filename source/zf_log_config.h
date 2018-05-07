#ifndef ZF_LOG_CONFIG_H_
#define ZF_LOG_CONFIG_H_

#ifdef __cplusplus
extern "C"
{
#endif // #ifdef __cplusplus

#define ZF_LOG_BUF_SZ 32

#if 0
#define ZF_LOG_MESSAGE_CTX_FORMAT \
     (F_INIT((unsigned get_system_tick(); )), \
      F_UINT(5, get_system_tick()), S(" "), LEVEL, S(" "))
#endif

#if 1
//#define ZF_LOG_MESSAGE_CTX_FORMAT \
//     (F_INIT((unsigned get_system_tick(); )), \
//      F_UINT(5, get_system_tick()), S(ZF_LOG_DEF_DELIMITER))

#define ZF_LOG_MESSAGE_CTX_FORMAT (S(ZF_LOG_DEF_DELIMITER))

//#define ZF_LOG_MESSAGE_SRC_FORMAT	(FUNCTION, S(ZF_LOG_DEF_DELIMITER))
//#define ZF_LOG_MESSAGE_SRC_FORMAT	(FUNCTION, S("@"), FILENAME, S(":"), FILELINE, S(ZF_LOG_DEF_DELIMITER))
#endif


#if 1
#define ZF_LOG_MESSAGE_SRC_FORMAT (S(ZF_LOG_DEF_DELIMITER))
#endif

#define ZF_LOG_USE_CUSTOM_FORMATTING_FUNCTIONS
//#define ZF_LOG_OPTIMIZE_SIZE
#include "printf.h"
#ifdef ZF_LOG_OPTIMIZE_SIZE
#define ZF_LOG_SNPRINTF snprintf
#endif
#define ZF_LOG_VSNPRINTF vsnprintf

#ifdef __cplusplus
}// closing brace for extern "C"
#endif // #ifdef __cplusplus

#endif // #ifndef ZF_LOG_CONFIG_H_
