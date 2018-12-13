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
 * @file li_can_slv_port.h
 * @brief header to li_can_slv_port.h module
 * @addtogroup li_can_slv_port
 * @{
 */

#ifndef LI_CAN_SLV_PORT_H_
#define LI_CAN_SLV_PORT_H_

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

/*--------------------------------------------------------------------------*/
/* included files                                                           */
/*--------------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

#ifdef LI_CAN_SLV_USE_ASYNC_TUNNEL
#include "com_echo_example.h"
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_TUNNEL

#include "main.h"
#include <string.h>

#ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD
#include "li_can_slv_xload_handler.h"
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD

#include <core_cm3.h>

/*--------------------------------------------------------------------------*/
/* general definitions                                                      */
/*--------------------------------------------------------------------------*/
#define LI_CAN_SLV_PORT_STATIC_INLINE __STATIC_INLINE

#define li_can_slv_port_nop()	__NOP()

#define li_can_slv_port_get_system_ticks()	HAL_GetTick()
#define li_can_slv_port_msec_2_ticks(a)		(a)
#define li_can_slv_port_ticks_2_msec(a)		(a)

#define li_can_slv_port_disable_irq()	__disable_irq()
#define li_can_slv_port_enable_irq()	__enable_irq()

#define li_can_slv_port_memory_cmp(ptr1, ptr2, size)	memcmp(ptr1, ptr2, size)
#define li_can_slv_port_memory_cpy(dest, source, size)	memcpy(dest, source, size)
#define li_can_slv_port_memory_set(ptr, value, num)		memset(ptr, value, num)

#define li_can_slv_port_string_cmp(str1, str2)				strcmp(str1, str2)
#define li_can_slv_port_string_n_cmp(str1, str2, num)		strncmp(str1, str2, num)
#define li_can_slv_port_string_cpy(dest, source)			strcpy(dest, source)
#define li_can_slv_port_string_n_cpy(dest, source, size) 	strncpy(dest, source, size)

#define li_can_slv_port_get_boot_kernel_version_major()		(9)
#define li_can_slv_port_get_boot_kernel_version_minor()		(999)

#define li_can_slv_port_get_modul_software_version_major()	(9)
#define li_can_slv_port_get_modul_software_version_minor()	(999)

#define li_can_slv_port_get_identnumber()	(99999999)
#define li_can_slv_port_get_changeindex()	(9)
#define li_can_slv_port_get_serialnumber()	(9999999)

#if defined (LI_CAN_SLV_USE_RECONNECT) && defined (LI_CAN_SLV_USE_MAIN_MON)
#define li_can_slv_port_sync_baudrate(baudrate) main_mon_sync_baudrate(baudrate)
#endif // #if defined (LI_CAN_SLV_USE_RECONNECT) && defined (LI_CAN_SLV_USE_MAIN_MON)

#ifdef LI_CAN_SLV_USE_MAIN_MON
#define li_can_slv_port_get_mainmon_type() app_get_mainmon_type()
#endif // #ifdef LI_CAN_SLV_USE_MAIN_MON

#define li_can_slv_port_sw_reset() NVIC_SystemReset()

#ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD_BUFFER_EXTERNAL
#define li_can_slv_port_dload_add_byte_to_buffer(a) add_byte_to_buffer(a)
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD_BUFFER_EXTERNAL

#ifdef LI_CAN_SLV_USE_ASYNC_TUNNEL
#define li_can_slv_port_async_tunnel_xon_rx_handle() com_xon_rx();
#define li_can_slv_port_async_tunnel_xoff_rx_handle()  com_xoff_rx();
#define li_can_slv_port_async_tunnel_open_handle(pputc, pxon, pxoff) com_chan_init(pputc, pxon, pxoff);
#define li_can_slv_port_async_tunnel_free_handle() com_chan_close();
#define li_can_slv_port_async_tunnel_clear_rx_buffer_handle() com_clear_rx_buffer();
#define li_can_slv_port_async_tunnel_data_rx_handle(pdata, len) com_data_rx(pdata, len);
#ifdef SPS_MONITOR_CONNECTION_TYPE_LP
#define li_can_slv_start_sps_monitor_handle() out_start_monitor_server();
#endif // #ifdef SPS_MONITOR_CONNECTION_TYPE_LP
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_TUNNEL

/*--------------------------------------------------------------------------*/
/* structure/type definitions                                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* global variables                                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* function prototypes                                                      */
/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}// closing brace for extern "C"
#endif // #ifdef __cplusplus

#endif // #ifndef LI_CAN_SLV_PORT_H_

/** @} */
