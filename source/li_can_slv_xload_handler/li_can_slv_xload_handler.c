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
 * @file li_can_slv_xload_handler.c
 * @brief
 * @addtogroup
 * @{
 */

/*--------------------------------------------------------------------------*/
/* include files                                                            */
/*--------------------------------------------------------------------------*/
#include "li_can_slv_xload_handler.h"
#include "li_can_slv_xload_buffer.h"
#include "li_can_slv_port.h"

#ifdef DEBUG_DLOAD
#include "io_debug.h"
#endif // #ifdef DEBUG_DLOAD

#ifdef IO_DEBUG
#include "io_debug.h"
#endif // #ifdef IO_DEBUG

#include "main.h"
#ifdef MAIN_MON
#include "main_mon_uart.h"
#endif // #ifdef MAIN_MON

/*--------------------------------------------------------------------------*/
/* general definitions (private/not exported)                               */
/*--------------------------------------------------------------------------*/
#ifdef IO_DEBUG
#define TIME_DELAY_BETWEEN_OBJECTS (10) // delay between can objects in msec
#else
#define TIME_DELAY_BETWEEN_OBJECTS (0) // delay between can objects in msec
#endif

#define DLOAD_CPU1			"CPU1"
#define DLOAD_CPU1_SIZE		(4)
#ifdef MAIN_MON
#define DLOAD_CPU2			"CPU2"
#define DLOAD_CPU2_SIZE		(4)
#endif // #ifdef MAIN_MON

#define DLOAD_USER			"USER"
#define DLOAD_USER_SIZE		(4)

/*--------------------------------------------------------------------------*/
/* structure/type definitions (private/not exported)                        */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* global variables (public/exported)                                       */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* function prototypes (private/not exported)                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* global variables (private/not exported)                                  */
/*--------------------------------------------------------------------------*/
static uint8_t tmp_data_for_upload[] = "Some text for Testing!";

/*--------------------------------------------------------------------------*/
/* function prototypes (private/not exported)                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* function definition (public/exported)                                    */
/*--------------------------------------------------------------------------*/
#ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD
/**
 * @param dload_component
 * @return LCSA_ERROR_OK or LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT
 */
lcsa_errorcode_t li_can_slv_dload_start_handle(li_can_slv_xload_component_t *dload_component)
{
	dload_component = dload_component;
	return LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT;
}

/**
 * @param dload_component
 * @param status
 * @return LCSA_ERROR_OK or LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT
 */
lcsa_errorcode_t li_can_slv_dload_version_request_handle(li_can_slv_xload_component_t *dload_component, li_can_slv_xload_end_handle_status_t *status)
{
	lcsa_errorcode_t err;
	*status = LI_CAN_SLV_XLOAD_STACK_END_HANDLING;

	if (li_can_slv_port_string_n_cmp(dload_component->name, DLOAD_CPU1, DLOAD_CPU1_SIZE) == 0)
	{
		dload_component->crc = *((uint16_t *) (BOOT_NVM_CRC_START));
		dload_component->download_id = *((uint32_t *) (BOOT_NVM_DOWNLOAD_ID_START));
		err = LCSA_ERROR_OK;
	}
#ifdef MAIN_MON
	else if (li_can_slv_port_string_n_cmp(dload_component->name, DLOAD_CPU2, DLOAD_CPU2_SIZE) == 0)
	{
		dload_component->crc = *((uint16_t *)(BOOT_NVM_CRC_START_MON));
		dload_component->download_id = *((uint32_t *)(BOOT_NVM_DOWNLOAD_ID_START_MON));
		err = LCSA_ERROR_OK;
	}
#endif // #ifdef MAIN_MON
	else if (li_can_slv_port_string_n_cmp(dload_component->name, DLOAD_USER, DLOAD_USER_SIZE) == 0)
	{
#ifdef IO_DEBUG
		DEBUG_PRINT("\nli_can_slv_dload_version_request_handle");
#endif // #ifdef IO_DEBUG
		dload_component->crc = DLOAD_CRC_DEFAULT;
		dload_component->download_id = DLOAD_DATE_DEFAULT;
		err = LCSA_ERROR_OK;
	}
	else
	{
		err = LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT;
	}

#ifdef IO_DEBUG
	DEBUG_PRINT("\nli_can_slv_dload_version_request_handle");
	DEBUG_PRINT("\nname: %s", dload_component->name);
	DEBUG_PRINT("\ncrc: %d", dload_component->crc);
	DEBUG_PRINT("\ndownload_id: %ld", dload_component->download_id);
#endif // #ifdef IO_DEBUG
	return err;
}

/**
 * @param dload_component
 * @return LCSA_ERROR_OK or LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT
 */
lcsa_errorcode_t li_can_slv_dload_start_request_handle(li_can_slv_xload_component_t *dload_component)
{
	lcsa_errorcode_t err;
	lcsa_bdr_t baudrate;
#ifdef MAIN_MON
	uint8_t tmp_u8;
#endif // #ifdef MAIN_MON

	if (li_can_slv_port_string_n_cmp(dload_component->name, DLOAD_CPU1, DLOAD_CPU1_SIZE) == 0)
	{
		baudrate = lcsa_get_baudrate();
		li_can_slv_xload_info_set_can_baudrate(baudrate);
		/* bring download info to sysinfo structure */
		li_can_slv_xload_info_set_dload_component(dload_component);
		/* go to download mode and reset */
		li_can_slv_xload_info_set_mode(LI_CAN_SLV_XLOAD_INFO_MODE_DOWNLOAD_INN);
#ifdef DEBUG_DLOAD
		DEBUG_PRINT("\nmodule hardware reset wait");
#endif // #ifdef DEBUG_DLOAD
		/* module hardware reset */

#ifdef LI_CAN_SLV_MAIN_MON
		if (app_get_mainmon_type() == APP_MAINMON_MAIN)
		{
			tmp_u8 = 0x01;
			SBP_MSG(sbp_state, SBP_MSG_RESET_WITH_INFO_VALUE, tmp_u8);
			SBP_MSG(sbp_state, SBP_MSG_RESET_WITH_INFO_VALUE, tmp_u8);
		}
#endif // #ifdef LI_CAN_SLV_MAIN_MON

		li_can_slv_port_sw_reset();
		/* download start acknowledge will be send after reboot in download mode */
	}
#ifdef MAIN_MON
	else if (li_can_slv_port_string_n_cmp(dload_component->name, DLOAD_CPU2, DLOAD_CPU2_SIZE) == 0)
	{
		baudrate = lcsa_get_baudrate();
		li_can_slv_xload_info_set_can_baudrate(baudrate);
		/* bring download info to xload info structure */
		li_can_slv_xload_info_set_dload_component(dload_component);
		/* go to download mode and reset */
		li_can_slv_xload_info_set_mode(LI_CAN_SLV_XLOAD_INFO_MODE_DOWNLOAD_INN);
#ifdef DEBUG_DLOAD
		DEBUG_PRINT("\nmodule hardware reset wait");
#endif // #ifdef DEBUG_DLOAD
		/* module hardware reset */

#ifdef LI_CAN_SLV_MAIN_MON
		if (app_get_mainmon_type() == APP_MAINMON_MAIN)
		{
			tmp_u8 = 0x02;
			SBP_MSG(sbp_state, SBP_MSG_RESET_WITH_INFO_VALUE, tmp_u8);
			SBP_MSG(sbp_state, SBP_MSG_RESET_WITH_INFO_VALUE, tmp_u8);
		}
#endif // #ifdef LI_CAN_SLV_MAIN_MON

		li_can_slv_port_sw_reset();
		/* download start acknowledge send after new booting in download mode */
	}
#endif // #ifdef MAIN_MON

	else if (li_can_slv_port_string_n_cmp(dload_component->name, DLOAD_USER, DLOAD_USER_SIZE) == 0)
	{
		/* send download start acknowledge for fpga files */
		err = li_can_slv_dload_start_ackn(dload_component->module_nr, LI_CAN_SLV_XLOAD_MAX_BYTES_PER_BLOCK_DLOAD, TIME_DELAY_BETWEEN_OBJECTS);
	}
	else
	{
		err = LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT;
	}
	return err;
}

/**
 * @param dload_component
 * @return LCSA_ERROR_OK or LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT
 */
lcsa_errorcode_t li_can_slv_dload_data_block_end_handle(li_can_slv_xload_component_t *dload_component)
{
	lcsa_errorcode_t err;
#ifdef LI_CAN_SLV_DLOAD_BUFFER_INTERNAL
	uint16_t number_of_bytes;
	uint8_t data_byte;
	uint16_t i;
#endif // #ifdef LI_CAN_SLV_DLOAD_BUFFER_INTERNAL

#ifdef IO_DEBUG
	DEBUG_PRINT("\nli_can_slv_dload_data_block_end_handle");
#endif // #ifdef IO_DEBUG

	if (li_can_slv_port_string_n_cmp(dload_component->name, DLOAD_USER, DLOAD_USER_SIZE) == 0)
	{
#ifdef LI_CAN_SLV_DLOAD_BUFFER_INTERNAL
		xload_buffer_get_len(&number_of_bytes);
#ifdef IO_DEBUG
		DEBUG_PRINT("\nnr_bytes: %u", number_of_bytes);
		DEBUG_PRINT("\n\n");
#endif // #ifdef IO_DEBUG
#endif // #ifdef LI_CAN_SLV_DLOAD_BUFFER_INTERNAL

#ifdef LI_CAN_SLV_DLOAD_BUFFER_INTERNAL
		for (i = 0; i < number_of_bytes; ++i)
		{
			if (xload_buffer_get_byte(&data_byte) != ERR_DLOAD_BUF_UNDERFLOW)
			{
//#ifdef IO_DEBUG
				printf("%c", data_byte);
//#endif // #ifdef IO_DEBUG
			}
		}
#ifdef IO_DEBUG
		DEBUG_PRINT("\n\n");
#endif // #ifdef IO_DEBUG
#endif // #ifdef LI_CAN_SLV_DLOAD_BUFFER_INTERNAL
		err = LCSA_ERROR_OK;
	}
	else
	{
		err = LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT;
	}
	return err;
}

/**
 * @param dload_component
 * @param status
 * @return LCSA_ERROR_OK or LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT
 */
lcsa_errorcode_t li_can_slv_dload_end_handle(li_can_slv_xload_component_t *dload_component, li_can_slv_xload_end_handle_status_t *status)
{
	lcsa_errorcode_t err = LCSA_ERROR_OK;
	*status = LI_CAN_SLV_XLOAD_STACK_END_HANDLING;

	if (li_can_slv_port_string_n_cmp(dload_component->name, DLOAD_USER, DLOAD_USER_SIZE) == 0)
	{
		// crc berechnen und speichern, falls nicht ok
		// im Fehlerfall
		// err = LCSA_ERROR_DLOAD_UNKNOWN_COMPONENT
		err = LCSA_ERROR_OK;
	}

#ifdef IO_DEBUG
	DEBUG_PRINT("\nli_can_slv_dload_end_handle");
#endif // #ifdef IO_DEBUG
	return err;
}

#ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD_BUFFER_EXTERNAL
lcsa_errorcode_t add_byte_to_buffer(uint8_t data)
{
#ifdef IO_DEBUG
	xputc(data);
#else
	data = data;
#endif // #ifdef IO_DEBUG
	return (LCSA_ERROR_OK);
}
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD_BUFFER_EXTERNAL
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_DOWNLOAD

#ifdef LI_CAN_SLV_USE_ASYNC_UPLOAD
lcsa_errorcode_t li_can_slv_uload_info_request_handle(li_can_slv_xload_component_t *dload_component, uint32_t *size_of_component, li_can_slv_xload_end_handle_status_t *status)
{
	lcsa_errorcode_t err = LCSA_ERROR_OK;
	*size_of_component = 259;
	return (err);
}

lcsa_errorcode_t li_can_slv_uload_start_request_handle(li_can_slv_xload_component_t *dload_component)
{
	lcsa_errorcode_t err = LCSA_ERROR_OK;
	err = li_can_slv_uload_data_from_buffer(&tmp_data_for_upload[0], 256);
	return (err);
}

lcsa_errorcode_t li_can_slv_uload_block_ack_handle(li_can_slv_xload_component_t *dload_component)
{
	lcsa_errorcode_t err = li_can_slv_uload_end(dload_component->module_nr);
	return err;
}
#endif // #ifdef LI_CAN_SLV_USE_ASYNC_UPLOAD

/*--------------------------------------------------------------------------*/
/* function definition (private/not exported)                               */
/*--------------------------------------------------------------------------*/

/** @} */

