/***************************************************************************//**
 * @file
 * @brief Core application logic.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/
#include "em_common.h"
#include "app_assert.h"
#include "sl_bluetooth.h"
#include "gatt_db.h"
#include "app.h"
#include "app_log.h"
#include "sl_simple_button_instances.h"
#include "sl_simple_led_instances.h"

#include "sl_sleeptimer.h"

#define CHAR_HANDLE       17
#define PAYLOAD_LENGTH    6
#define MAX_CONNECTIONS   32

#define CONN_INTERVAL     50//22 //Time = CONN_INTERVAL x 1.25 ms

#define SUP_TIMEOUT     10*CONN_INTERVAL//Time = CONN_INTERVAL x 1.25 ms

#define USE_WRITE_WITH_RESPONSE 0

#define CHANGE_MTU
#define MAX_MTU 255

//1s is 32768 tick
#define TIMER_1S_PERIOD 32768

#define SCANNING_TIMEOUT 10*TIMER_1S_PERIOD

#define TEST_TIMEOUT 10*TIMER_1S_PERIOD

#define DESIRED_PHY 2 //2M PHY



typedef struct conn_data{
  uint8_t conn_handle;
  uint8_t char_handle;
}conn_data;





static uint8_t conn_handles[MAX_CONNECTIONS];
static uint8_t num_of_connections = 0;

static uint16_t v_major, v_minor, v_patch;

volatile uint64_t tick_start_array[MAX_CONNECTIONS +1];
volatile uint64_t tick_end_array[MAX_CONNECTIONS + 1];
volatile uint16_t received_cnt_array[MAX_CONNECTIONS + 1];


static uint32_t latency_msec, elapsed_time;

static uint8_t connections_finished = 0;

static uint8_t Connection_Handle = 0;
static uint8_t Responses_received = 0;
static uint8_t Tx_count = 0;
static bool conn_in_progress = false;

uint8_t payload[PAYLOAD_LENGTH] = {3};

uint16_t payload_sent_len;

//for BRD4180A use gpioPortD, 2, For BRD4081B/C use gpioPortB, 0,
#define BUTTON_PORT gpioPortD
#define BUTTON_PIN 2

/// Type of System State Machine
typedef enum {
  //Scanning for Connectable Beacons state
  INIT = 0,
  SCANNING_AND_CONNECTING,
  SCAN_STOP,
  WAITING_FOR_TEST_TO_START,
  BEFORE_ENB_NOTIFY,
  ENB_NOTIFY,
  WAITING_FOR_RESPONSE,
  RESPONSE_RECEIVED,
  TEST_CONCLUDED

} SMType_t;

static SMType_t SM_status = 0;

typedef union{
        struct{
            uint8_t     byte_0;
            uint8_t     byte_1;
            uint8_t     byte_2;
            uint8_t     byte_3;
            }Bytes;
        uint32_t value;
    } _32_8bit;

volatile _32_8bit tick_count;

// Handle for sleeptimer
sl_sleeptimer_timer_handle_t my_sleeptimer_handle;

// Advertised service UUID
static const uint8_t advertised_service[2] = { 0xCC, 0xCC };

uint8_t app_get_next_connection_slot(void);
/**************************************************************************//**
 * Parse advertisements looking for  a service UUID of the peripheral device
 * @param[in] data: Advertisement packet
 * @param[in] len:  Length of the advertisement packet
 *****************************************************************************/
static uint8_t find_service_in_advertisement(uint8_t *data, uint8_t len)
{
  uint8_t ad_field_length;
  uint8_t ad_field_type;
  uint8_t i = 0;
  // Parse advertisement packet
  while (i < len) {
    ad_field_length = data[i];
    ad_field_type = data[i + 1];
    // Partial ($02) or complete ($03) list of 16-bit UUIDs
    if (ad_field_type == 0x02 || ad_field_type == 0x03) {
      // compare UUID to Health Thermometer service UUID
      if (memcmp(&data[i + 2], advertised_service, sizeof(advertised_service)) == 0) {
        return 1;
      }
    }
    // advance to the next AD struct
    i = i + ad_field_length + 1;
  }
  return 0;
}

/**************************************************************************//**
 * Application Init.
 *****************************************************************************/
SL_WEAK void app_init(void)
{
  /////////////////////////////////////////////////////////////////////////////
  // Put your additional application init code here!                         //
  // This is called once during start-up.                                    //
  /////////////////////////////////////////////////////////////////////////////
  GPIO_PinModeSet(BUTTON_PORT, BUTTON_PIN,  gpioModeInput, 0);

  sl_sleeptimer_init();

}
/**************************************************************************//**
 * @brief
 *   Generic Sleeptimer callback function. Each time sleeptimer reaches timeout value,
 *   this callback is executed.
 *****************************************************************************/
void my_timer_callback(sl_sleeptimer_timer_handle_t *handle, void *data)
{
//Time allocated for the test concluded
  app_log("Time allocated for the test concluded\r\n");
  SM_status = RESPONSE_RECEIVED;

}
 /**************************************************************************//**
 * @brief
 *   Function to start the generic timer
 *****************************************************************************/
 int start_timer(uint32_t timer_timeout)
{
  sl_status_t status;
  sl_sleeptimer_timer_handle_t my_timer;
 
  // We assume the sleeptimer is initialized properly
 
  status = sl_sleeptimer_start_timer(&my_timer,
                                     timer_timeout,
                                     my_timer_callback,
                                     (void *)NULL,
                                     0,
                                     0);
  if(status != SL_STATUS_OK) {
    return -1;
  }
  return 1;
}

/**************************************************************************//**
 * @brief
 *   Sleeptimer callback function. Each time sleeptimer reaches timeout value,
 *   this callback is executed.
 *****************************************************************************/
void sleeptimer_cb(sl_sleeptimer_timer_handle_t *handle, void *data)
{
  tick_count.value+=1;
  if(SM_status==SCANNING_AND_CONNECTING){
      SM_status = SCAN_STOP;
  }

  if(SM_status==WAITING_FOR_RESPONSE){
        SM_status = RESPONSE_RECEIVED;
        app_log("Time allocated for the test concluded\r\n");

    }

}

/**************************************************************************//**
 * Application Process Action.
 *****************************************************************************/
SL_WEAK void app_process_action(void)
{
  sl_status_t sc;

  switch(SM_status)
  {
    case INIT:
      break;
      case SCANNING_AND_CONNECTING:{

        break;
      }
      case SCAN_STOP:
        {

          app_log("Scanning Period concluded\n\rNumber of devices connected = %d\r\n", num_of_connections);
          app_log("Press PB0 to start the Test\r\n");
          sc = sl_bt_scanner_stop();
          app_assert_status(sc);
          SM_status = WAITING_FOR_TEST_TO_START;
          Connection_Handle = 0;
          break;
        }

      case WAITING_FOR_TEST_TO_START:{

          if(( GPIO_PinInGet(gpioPortD,2)==0))//&&(connections_finished == 1))
            {
              app_log("Button pressed, starting the test\r\n");

              Connection_Handle = 0;
              SM_status = BEFORE_ENB_NOTIFY;
           }
        }

        break;
      case BEFORE_ENB_NOTIFY:
        {
          Connection_Handle = 0;
          //Initializes received_cnt_array with Zeros
          for (uint8_t i = 0; i < MAX_CONNECTIONS; i++)
            {
              received_cnt_array[i] = 0;
              tick_start_array[i] = 0;

            }
          Responses_received = 0;
          Tx_count = 0;
          SM_status = ENB_NOTIFY;
          sl_sleeptimer_start_timer(&my_sleeptimer_handle,  TEST_TIMEOUT, sleeptimer_cb, (void *)NULL,0,0);
        }
         break;

      case ENB_NOTIFY:

        {

          for(uint8_t i = 0; i < num_of_connections; i++){
              if (conn_handles[i] != 0xFF){
                 //tick_start_array[conn_handles[i]] = sl_sleeptimer_get_tick_count64();
                 app_log("Subscribing to Notification on Connection#: %d\r\n", conn_handles[i]);

                 sl_bt_gatt_set_characteristic_notification(conn_handles[i], 20, 1);
                 app_assert_status(sc);
                 Tx_count++;
              }
          }
          SM_status = WAITING_FOR_RESPONSE;
        }

        break;
      case WAITING_FOR_RESPONSE:
              {
                //app_log("Connection_handle: %d\r\n", Connection_Handle);
              }
              break;

      case RESPONSE_RECEIVED:
        {



        for(uint8_t i = 0; i < num_of_connections; i++)
          {
            app_log("Results related to Connection#: %d\r\n", conn_handles[i]);
             elapsed_time = tick_end_array[conn_handles[i]] - tick_start_array[conn_handles[i]];
             //app_log("Elapsed time in ticks: %d\r\n", elapsed_time);
             latency_msec = sl_sleeptimer_tick_to_ms(elapsed_time);
             app_log("The elapsed time for all packets on Connection %d: %d msec\r\n",conn_handles[i], latency_msec);
             app_log("Total Amount of bytes received on Connection %d: %d bytes\r\n",conn_handles[i], received_cnt_array[conn_handles[i]]);
             app_log("Total Throughput on Connection %d: %d kbps\r\n",conn_handles[i], ((received_cnt_array[conn_handles[i]]*1000)/(latency_msec)));


          }
          SM_status = TEST_CONCLUDED;
          app_log(" Test Concluded\r\n");
         
            if(( GPIO_PinInGet(BUTTON_PORT, BUTTON_PIN)==0))
                       {
                         app_log("Button pressed, Test Concluded\r\n");
                         SM_status = TEST_CONCLUDED;
                       }

        }
        break;
      case TEST_CONCLUDED:
        {


        }
        break;

  }
}

/**************************************************************************//**
 * Bluetooth stack event handler.
 * This overrides the dummy weak implementation.
 *
 * @param[in] evt Event coming from the Bluetooth stack.
 *****************************************************************************/
void sl_bt_on_event(sl_bt_msg_t *evt)
{
  sl_status_t sc;
  bd_addr address;
  uint8_t address_type;
  uint8_t system_id[8];
  uint8_t conn_slot;

  switch (SL_BT_MSG_ID(evt->header)) {
    // -------------------------------
    // This event indicates the device has started and the radio is ready.
    // Do not call any stack command before receiving this boot event!
    case sl_bt_evt_system_boot_id:
      for (uint8_t i = 0; i < MAX_CONNECTIONS; i++){
          conn_handles[i] = 0xFF;
      }

      sl_bt_system_get_version(&v_major, &v_minor, &v_patch, NULL, NULL, NULL);
      app_log("Stack version: %d.%d.%d\r\n", v_major, v_minor, v_patch);

      // Extract unique ID from BT Address.
      sc = sl_bt_system_get_identity_address(&address, &address_type);
      app_assert_status(sc);
      // Pad and reverse unique ID to get System ID.
      system_id[0] = address.addr[5];
      system_id[1] = address.addr[4];
      system_id[2] = address.addr[3];
      system_id[3] = 0xFF;
      system_id[4] = 0xFE;
      system_id[5] = address.addr[2];
      system_id[6] = address.addr[1];
      system_id[7] = address.addr[0];
      app_log("BLE address: %02x:%02x:%02x:%02x:%02x:%02x\r\n", address.addr[5],
              address.addr[4], address.addr[3], address.addr[2],
                address.addr[1], address.addr[0]);


      sc = sl_bt_connection_set_default_parameters(CONN_INTERVAL, CONN_INTERVAL, 0, SUP_TIMEOUT, 0, 0xFFFF);
      app_assert_status(sc);

#ifdef CHANGE_MTU
      app_log("MAX MTU set to %d bytes\r\n", MAX_MTU );
      sc = sl_bt_gatt_set_max_mtu(MAX_MTU,0);
      app_assert_status(sc);
#endif

      app_log("Connection interval set to %d msec\r\n", (5*CONN_INTERVAL)/4 );

      sc = sl_bt_scanner_start(sl_bt_scanner_scan_phy_1m,
                               sl_bt_scanner_discover_generic);
      app_assert_status(sc);
      app_log("Scanning started\r\n");

      //Initiates Scanner Counter timer
      sc = sl_sleeptimer_start_timer(&my_sleeptimer_handle,  SCANNING_TIMEOUT, sleeptimer_cb, (void *)NULL,0,0);
      app_assert_status(sc);

      SM_status = SCANNING_AND_CONNECTING;
      break;

    case sl_bt_evt_scanner_legacy_advertisement_report_id:
      if(conn_in_progress == false){
        if(find_service_in_advertisement(evt->data.evt_scanner_legacy_advertisement_report.data.data, evt->data.evt_scanner_legacy_advertisement_report.data.len)){
            //app_log("Device found\r\n");
            conn_slot = app_get_next_connection_slot();
            if (conn_slot != 0xFF){
                sc = sl_bt_connection_open(evt->data.evt_scanner_legacy_advertisement_report.address,
                                      sl_bt_gap_public_address,
                                      sl_bt_gap_phy_1m,
                                      &conn_handles[conn_slot]);
                app_assert_status(sc);
                conn_in_progress = true;
                app_log("Connection request sent, handle: %d\r\n", conn_handles[conn_slot]);
            }
        }
      }
      break;

    case sl_bt_evt_gatt_procedure_completed_id:
    break;



    case sl_bt_evt_connection_parameters_id:

      app_log("Connection interval set %d on connection# %d\n\r",evt->data.evt_connection_parameters.interval, evt->data.evt_connection_parameters.connection);
      app_log("Connection Latency set %d on connection# %d \n\r",evt->data.evt_connection_parameters.latency, evt->data.evt_connection_parameters.connection);
      app_log("Connection Timeout set %d on connection# %d \n\r",evt->data.evt_connection_parameters.timeout, evt->data.evt_connection_parameters.connection);


      break;

    case sl_bt_evt_gatt_characteristic_value_id:

      if (tick_start_array[evt->data.evt_gatt_characteristic_value.connection] ==0)
        {
            tick_start_array[evt->data.evt_gatt_characteristic_value.connection] = sl_sleeptimer_get_tick_count64();
        }
      tick_end_array[evt->data.evt_gatt_server_attribute_value.connection] = sl_sleeptimer_get_tick_count64();
      received_cnt_array[evt->data.evt_gatt_server_attribute_value.connection] += evt->data.evt_gatt_characteristic_value.value.len;
     // app_log("Packet count: %d on connection %d, received array %d\r\n", evt->data.evt_gatt_characteristic_value.value.len,evt->data.evt_gatt_characteristic_value.connection,
           //   received_cnt_array[evt->data.evt_gatt_server_attribute_value.connection]);
    

    break;

    // -------------------------------
    // This event indicates that a new connection was opened.
    case sl_bt_evt_connection_opened_id:
      num_of_connections++;
      conn_in_progress = false;
      app_log("Connection opened, number of connections: %d, connection handle: %d\r\n", num_of_connections, evt->data.evt_connection_opened.connection);
      sl_bt_connection_set_preferred_phy(evt->data.evt_connection_opened.connection, DESIRED_PHY, DESIRED_PHY);
      if (num_of_connections >= MAX_CONNECTIONS){

          app_log("Max number of connections achieved -  %d Connections \r\n", num_of_connections);
          connections_finished = 1;
          sl_bt_scanner_stop();
      }
      break;

    case sl_bt_evt_connection_phy_status_id:
      app_log("connection %d, PHY: %d \n\r", evt->data.evt_connection_phy_status.connection, evt->data.evt_connection_phy_status.phy);
      break;
   
    // -------------------------------
    // This event indicates that a connection was closed.
    case sl_bt_evt_connection_closed_id:
      app_log("Connection: %d closed, reason: %x\r\n", evt->data.evt_connection_closed.connection, evt->data.evt_connection_closed.reason);
      if (evt->data.evt_connection_closed.reason == SL_STATUS_BT_CTRL_CONNECTION_FAILED_TO_BE_ESTABLISHED){
          conn_in_progress = false;
      }
      for (uint8_t i = 0; i < MAX_CONNECTIONS; i++){
         if (conn_handles[i] == evt->data.evt_connection_closed.connection){
             app_log("Connection ID %d removed\r\n", i);
             conn_handles[i] = 0xFF;
             break;
         }
       }
      num_of_connections--;
      app_log("Number of connections: %d\r\n", num_of_connections);
      if (num_of_connections < MAX_CONNECTIONS){
            sc = sl_bt_scanner_start(sl_bt_scanner_scan_phy_1m,
                                     sl_bt_scanner_discover_generic);
            if (sc == 0x0002){
                app_log("Scan is already running\r\n");
            }
       }


    ///////////////////////////////////////////////////////////////////////////
    // Add additional event handlers here as your application requires!      //
    ///////////////////////////////////////////////////////////////////////////

    // -------------------------------
    // Default event handler.
    default:
      break;
  }
}


uint8_t app_get_next_connection_slot(void)
{
 for (uint8_t i = 0; i < MAX_CONNECTIONS; i++){
     if (conn_handles[i] == 0xFF)
       {
         return i;
       }
 }
 return 0xFF;
}
