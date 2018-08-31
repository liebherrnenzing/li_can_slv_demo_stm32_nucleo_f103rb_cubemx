/****************************************************************************/
/*                                                                          */
/*                     Copyright (c) 2018, Liebherr PME1                    */
/*                         ALL RIGHTS RESERVED                              */
/*                                                                          */
/* This file is part of li_can_slv stack which is free software: you can    */
/* redistribute it and/or modify it under the terms of the GNU General      */
/* Public License as published by the Free Software Foundation, either      */
/* version 3 of the License, or (at your option) any later version.         */
/*                                                                          */
/* The li_can_slv stack is distributed in the hope that it will be useful,  */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General */
/* Public License for more details.                                         */
/*                                                                          */
/* You should have received a copy of the GNU General Public License which  */
/* should be located in the the root of the Stack. If not, contact Liebherr */
/* to obtain a copy.                                                        */
/****************************************************************************/

/**
 * @file io_app_port.h
 * @brief header to io_app_port.h module
 * @addtogroup app
 * @{
 */

#ifndef IO_APP_PORT_H_
#define IO_APP_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

/*--------------------------------------------------------------------------*/
/* included files                                                           */
/*--------------------------------------------------------------------------*/
#include "io_app_config.h"
#include <li_can_slv/api/li_can_slv_api.h>
//#include "io_intrins.h"
#include <stdint.h>
#ifdef TUPLE
#include "io_tuple.h"
#endif // #ifdef TUPLE

#include "li_can_slv_port.h"

#ifdef TESTSYS_SYSTEM
#include "io_testsys.h"
#include "io_var.h"
#endif // #ifdef TESTSYS_SYSTEM



//#include "li_can_slv_api.h"
//#include "li_can_slv_port.h"
//#include <stdint.h>
//#include <stddef.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#ifdef IO_DEBUG
//#include "io_debug.h"
//#endif // #ifdef IO_DEBUG
//
//#include "io_intrins.h"
//
//#if defined (APP_MAIN) || defined (APP_MON)
//#include "io_app_config_main_mon.h"
//#endif

/*--------------------------------------------------------------------------*/
/* general definitions                                                      */
/*--------------------------------------------------------------------------*/
#define HUGE /* define to nothing not used on STM32 */
#define INLINE inline
#define CALL(func) func /* define to func only not used on STM32 */
#define FAR

//#define APP_CONV_ROTL16 _IROL_
//#define APP_CONV_ROTL32 _LROL_

/*--------------------------------------------------------------------------*/
/* structure/type definitions                                               */
/*--------------------------------------------------------------------------*/
#ifdef APP_MAIN_MON
typedef enum
{
	APP_MAINMON_UNDEF = 0,
	APP_MAINMON_MAIN = 1,
	APP_MAINMON_MON = 2
} app_mainmon_t;
#endif // #ifdef APP_MAIN_MON

/*--------------------------------------------------------------------------*/
/* global variables                                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* function prototypes                                                      */
/*--------------------------------------------------------------------------*/
#define app_port_memory_set(ptr, value, num)	memset(ptr, value, num)
#ifdef APP_MAIN_MON
/**
 * @brief Returns the module main/monitor identification
 * @ingroup	modhw
 * @return modhw_main_mon
 */
app_mainmon_t app_get_mainmon_type(void);

app_mainmon_t app_get_mainmon_type_old(void);
#endif // #ifdef APP_MAIN_MON

#define app_port_get_system_tick()	get_system_tick()

#ifdef __cplusplus
}
// closing brace for extern "C"
#endif // #ifdef __cplusplus

#endif // #ifndef IO_APP_PORT_H_

/** @} */

