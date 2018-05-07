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
 * @brief Liebherr CAN Slave Stack configuration
 * @file li_can_slv_config.h
 * @addtogroup li_can_slv_config
 * @{
 */

#ifndef LI_CAN_SLV_CONFIG_H_
#define LI_CAN_SLV_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

/*--------------------------------------------------------------------------*/
/* general definitions                                                      */
/*--------------------------------------------------------------------------*/
//#define LI_CAN_SLV_DEBUG
#define LI_CAN_SLV_BASIC

#define LI_CAN_SLV_USE_UNKNOWN_MODULE
#define LI_CAN_SLV_SET_MAX_NR_OF_LOGICAL_MODULES (2u)

//#define LI_CAN_SLV_XLOAD_INFO_USER
//#define LI_CAN_SLV_XLOAD_INFO_BACKWARD_COMPATIBILITY

/*--------------------------------------------------------------------------*/
/* special definitions                                                      */
/*--------------------------------------------------------------------------*/
//#define LI_CAN_SLV_USE_MODULE_IO_CONFIG
//#define LI_CAN_SLV_USE_TUPLE

#ifdef MAIN_MON
/*--------------------------------------------------------------------------*/
/* main/monitor definitions                                                 */
/*--------------------------------------------------------------------------*/
#define LI_CAN_SLV_USE_MAIN_MON
#ifdef XLOAD_INFO
#define LI_CAN_SLV_XLOAD_INFO_USER
#endif // #ifdef XLOAD_INFO
#endif // #ifdef MAIN_MON

/*--------------------------------------------------------------------------*/
/* reconnect definitions                                                    */
/*--------------------------------------------------------------------------*/
//#define LI_CAN_SLV_USE_RECONNECT_ON_MAIN_NODE
//#define LI_CAN_SLV_USE_RECONNECT_CHANGE_BAUDRATE_CALLBACK

/*--------------------------------------------------------------------------*/
/* LI_CAN_SLV System protocol definitions                                   */
/*--------------------------------------------------------------------------*/
#define LI_CAN_SLV_USE_SYS_ERROR_16_BIT
#define LI_CAN_SLV_USE_SYS_CHANGE_MODULE_NUMBER

/*--------------------------------------------------------------------------*/
/* LI_CAN_SLV Synchronous protocol definitions                              */
/*--------------------------------------------------------------------------*/
#define LI_CAN_SLV_SET_SYNC_PROCESS_PERIODE_MAX (50)

/*--------------------------------------------------------------------------*/
/* LI_CAN_SLV Asynchronous protocol definitions                             */
/*--------------------------------------------------------------------------*/
#define LI_CAN_SLV_USE_ASYNC
//#define LI_CAN_SLV_USE_ASYNC_DOWNLOAD
////#define LI_CAN_SLV_USE_ASYNC_DOWNLOAD_BUFFER_EXTERNAL
//#define LI_CAN_SLV_USE_ASYNC_DOWNLOAD_BUFFER_SIZE (20*7)
////#define LI_CAN_SLV_USE_ASYNC_TUNNEL
//
//#define LI_CAN_SLV_USE_ASYNC_UPLOAD

/*--------------------------------------------------------------------------*/
/* HW/architecture definitions                                              */
/*--------------------------------------------------------------------------*/
#define LI_CAN_SLV_ARCH_SET_BYTE_ORDER_LITTLE_ENDIAN
#define LI_CAN_SLV_ARCH_USE_CANPIE_CH1_FOR_MAIN_NODE
#define LI_CAN_SLV_ARCH_MAIN_NODE_MAX_NOF_MSG_OBJ (32)

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

#endif // #ifndef LI_CAN_SLV_CONFIG_H_

/** @} */
