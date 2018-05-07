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
 * @file li_can_slv_xload_handler.h
 * @brief header to li_can_slv_xload_handler.h module
 * @addtogroup
 * @{
 */

#ifndef LI_CAN_SLV_XLOAD_HANDLER_H_
#define LI_CAN_SLV_XLOAD_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif // #ifdef __cplusplus

/*--------------------------------------------------------------------------*/
/* included files                                                           */
/*--------------------------------------------------------------------------*/
#include "li_can_slv_api.h"

/*--------------------------------------------------------------------------*/
/* general definitions                                                      */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* structure/type definitions                                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* global variables                                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* function prototypes                                                      */
/*--------------------------------------------------------------------------*/
#ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD
extern lcsa_errorcode_t li_can_slv_dload_start_handle(li_can_slv_xload_component_t *dload_component);
extern lcsa_errorcode_t li_can_slv_dload_version_request_handle(li_can_slv_xload_component_t *dload_component, li_can_slv_xload_end_handle_status_t *status);
extern lcsa_errorcode_t li_can_slv_dload_start_request_handle(li_can_slv_xload_component_t *dload_component);
extern lcsa_errorcode_t li_can_slv_dload_data_block_end_handle(li_can_slv_xload_component_t *dload_component);
extern lcsa_errorcode_t li_can_slv_dload_end_handle(li_can_slv_xload_component_t *dload_component, li_can_slv_xload_end_handle_status_t *status);
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD

#ifdef LI_CAN_SLV_USE_ASYNC_UPLOAD
extern lcsa_errorcode_t li_can_slv_uload_info_request_handle(li_can_slv_xload_component_t *dload_component, uint32_t *size_of_component, li_can_slv_xload_end_handle_status_t *status);
extern lcsa_errorcode_t li_can_slv_uload_start_request_handle(li_can_slv_xload_component_t *dload_component);
extern lcsa_errorcode_t li_can_slv_uload_block_ack_handle(li_can_slv_xload_component_t *dload_component);
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_UPLOAD

#ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD_BUFFER_EXTERNAL
extern lcsa_errorcode_t add_byte_to_buffer(uint8_t data);
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD_BUFFER_EXTERNAL

#ifdef __cplusplus
} // closing brace for extern "C"
#endif // #ifdef __cplusplus

#endif // #ifndef LI_CAN_SLV_XLOAD_HANDLER_H_

/** @} */
