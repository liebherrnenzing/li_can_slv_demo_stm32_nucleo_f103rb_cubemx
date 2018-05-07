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
 * @file io_app_demo_hw.c
 * @addtogroup app
 * @{
 */

/*--------------------------------------------------------------------------*/
/* include files                                                            */
/*--------------------------------------------------------------------------*/
#include "io_app_config.h"
#include "io_app_demo_hw.h"

#ifdef APP_MA_W
#include "io_app_ma_w.h"
#endif

#ifdef LI_CAN_SLV_USE_SYS_CHANGE_MODULE_NUMBER
#include "io_app_module_change.h"
#endif

/*--------------------------------------------------------------------------*/
/* general definitions (private/not exported)                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* structure/type definitions (private/not exported)                        */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* global variables (public/exported)                                       */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* function prototypes (private/not exported)                               */
/*--------------------------------------------------------------------------*/
#ifdef LI_CAN_SLV_RECONNECT_ONLINE_CHANGE_BAUDRATE_CBK
static void reconnect_online_change_baudrate_start(void);
static void reconnect_online_change_baudrate_stop(lcsa_bdr_t baudrate);
#endif /* #ifdef LI_CAN_SLV_RECONNECT_ONLINE_CHANGE_BAUDRATE_CBK */

#ifdef LI_CAN_SLV_RECONNECT_STARTUP_CHANGE_BAUDRATE_CBK
static void reconnect_startup_change_baudrate_start(void);
static void reconnect_startup_change_baudrate_stop(lcsa_bdr_t baudrate);
#endif /* #ifdef LI_CAN_SLV_RECONNECT_STARTUP_CHANGE_BAUDRATE_CBK */

//static volatile uint32_t status_one = 0;
static void first_process_req_callback(void);
static void process_req_whole_image_ok_callback(void);

/*--------------------------------------------------------------------------*/
/* global variables (private/not exported)                                  */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* function prototypes (private/not exported)                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* function definition (public/exported)                                    */
/*--------------------------------------------------------------------------*/
void app_main(void)
{
	lcsa_errorcode_t err = LCSA_ERROR_OK;

	err = app_init();
	printf("\napp init: %04X", err);

	if (err == LCSA_ERROR_OK)
	{
		err = app_start();
		printf("\napp start: %04X", err);
	}

	(void) lcsa_start();
}

lcsa_errorcode_t app_init(void)
{
	lcsa_bdr_t baudrate;
	lcsa_errorcode_t err = LCSA_ERROR_OK;
	lcsa_errorcode_t err2 = LCSA_ERROR_OK;
#ifdef APP_MA_W
	lcsa_module_number_t module_number;
#endif

#ifdef LI_CAN_SLV_DLOAD
	(void)lcsa_dload_set_start_handle(li_can_slv_dload_start_handle);
	(void)lcsa_dload_set_version_request_handle(li_can_slv_dload_version_request_handle);
	(void)lcsa_dload_set_start_request_handle(li_can_slv_dload_start_request_handle);
	(void)lcsa_dload_set_data_block_end_handle(li_can_slv_dload_data_block_end_handle);
	(void)lcsa_dload_set_end_handle(li_can_slv_dload_end_handle);
#endif

#ifdef LI_CAN_SLV_ULOAD
	(void)lcsa_uload_set_info_request_handle(li_can_slv_uload_info_request_handle);
	(void)lcsa_uload_set_start_request_handle(li_can_slv_uload_start_request_handle);
	(void)lcsa_uload_set_uload_block_ack_handle(li_can_slv_uload_block_ack_handle);
#endif

#ifdef LI_CAN_SLV_RECONNECT_ONLINE_CHANGE_BAUDRATE_CBK
	lcsa_reconnect_set_online_change_baudrate_start_cbk(reconnect_online_change_baudrate_start);
	lcsa_reconnect_set_online_change_baudrate_stop_cbk(reconnect_online_change_baudrate_stop);
#endif

#ifdef LI_CAN_SLV_RECONNECT_STARTUP_CHANGE_BAUDRATE_CBK
	lcsa_reconnect_set_startup_change_baudrate_start_cbk(reconnect_startup_change_baudrate_start);
	lcsa_reconnect_set_startup_change_baudrate_stop_cbk(reconnect_startup_change_baudrate_stop);
#endif

	(void)lcsa_sync_set_first_process_request_cbk(first_process_req_callback);
	(void)lcsa_sync_set_whole_process_image_valid_cbk(process_req_whole_image_ok_callback);

#ifdef LI_CAN_SLV_USE_SYS_CHANGE_MODULE_NUMBER
	lsca_set_module_nr_change_cbk_voter(&app_module_change_vote_module_nr_change_valid);
#endif

	/* read baudrate, and module numbers from eeprom, flash or file_sytem or use fixed values */

	// baudrate = LCSA_BAUD_RATE_125K;
	baudrate = LCSA_BAUD_RATE_250K;
	// baudrate = LCSA_BAUD_RATE_500k;
	// baudrate = LCSA_BAUD_RATE_1M;
	module_number = APP_MA_W_MODULE_NR_DEF;

	err = lcsa_init(baudrate);
	if (err != ERR_OK)
	{
		printf("\nlcsa_init err:%08x", err);
	}

#ifdef APP_MA_W
	/*-------------------------------------------------------------------*/
	/* Initialization of the MA_W module if the tuple is available       */
	/*-------------------------------------------------------------------*/
	if (err == ERR_OK)
	{
		err = app_ma_w_init(0, module_number);

		if (err != ERR_OK)
		{
			lcsa_send_sensor_error(err, ERR_LVL_CRITICAL, module_number);
			lcsa_send_sensor_error(ERR_APP_NOT_VALID, ERR_LVL_CRITICAL, module_number);
			err2 = lcsa_set_module_critical(APP_MA_W_MODULE_TYPE);
			if ((err2 != ERR_OK) && (err2 != LCSA_ERROR_CONFIG_MODULE_TYPE_NOT_FOUND))
			{
#ifdef APP_DEBUG
				printf("\n set critical not possible");
#endif
			}
		}
	}
#endif // #ifdef APP_MA_W
	return LCSA_ERROR_OK;
}

lcsa_errorcode_t app_start(void)
{
	return LCSA_ERROR_OK;
}

void app_process_5msec(void)
{
	/* trigger the li_can_slv stack */
	lcsa_trigger_5msec();

#ifdef APP_MA_W
	app_ma_w_process_input();
	app_ma_w_process_output();
#endif

}

/*--------------------------------------------------------------------------*/
/* function definition (private/not exported)                               */
/*--------------------------------------------------------------------------*/
#ifdef LI_CAN_SLV_RECONNECT_ONLINE_CHANGE_BAUDRATE_CBK
static void reconnect_online_change_baudrate_start(void)
{
#ifdef APP_DEBUG
	printf("\nreconnect_online_change_baudrate_start");
#endif
}

static void reconnect_online_change_baudrate_stop(lcsa_bdr_t baudrate)
{
#ifdef APP_DEBUG
	printf("\nreconnect_online_change_baudrate_stop: %d", baudrate);
#endif
}
#endif /* #ifdef LI_CAN_SLV_RECONNECT_ONLINE_CHANGE_BAUDRATE_CBK */

#ifdef LI_CAN_SLV_RECONNECT_STARTUP_CHANGE_BAUDRATE_CBK
static void reconnect_startup_change_baudrate_start(void)
{
#ifdef APP_DEBUG
	printf("\nreconnect_startup_change_baudrate_start");
#endif
}

static void reconnect_startup_change_baudrate_stop(lcsa_bdr_t baudrate)
{
#ifdef APP_DEBUG
	printf("\nreconnect_startup_change_baudrate_stop: %d", baudrate);
#endif
}
#endif /* #ifdef LI_CAN_SLV_RECONNECT_STARTUP_CHANGE_BAUDRATE_CBK */

static void first_process_req_callback(void)
{
#ifdef APP_DEBUG
	printf("\nfirst_process_req");
#endif
}

static void process_req_whole_image_ok_callback(void)
{
#ifdef APP_DEBUG
	printf("\nprocess req whole image okay");
#endif
}

/** @} */
