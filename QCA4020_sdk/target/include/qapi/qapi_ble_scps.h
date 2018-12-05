/*
 * Copyright (c) 2016-2018 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 */
// Copyright (c) 2018 Qualcomm Technologies, Inc.
// All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted (subject to the limitations in the disclaimer below) 
// provided that the following conditions are met:
// Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// Redistributions in binary form must reproduce the above copyright notice, 
// this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// Neither the name of Qualcomm Technologies, Inc. nor the names of its contributors may be used to endorse or promote products derived 
// from this software without specific prior written permission.
// NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE. 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
// OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/**
 * @file qapi_ble_scps.h
 *
 * @brief
 * QCA QAPI for Bluetopia Bluetooth Scan Parameters Service (SCPS)
 * (GATT based) API Type Definitions, Constants, and Prototypes.
 *
 * @details
 * The Scan Parameters Service programming interface defines the protocols
 * and procedures to be used to implement the Automation IO Service
 * capabilities.
 */

#ifndef __QAPI_BLE_SCPS_H__
#define __QAPI_BLE_SCPS_H__

#include "./qapi_ble_btapityp.h"  /* Bluetooth API Type Definitions.          */
#include "./qapi_ble_bttypes.h"   /* Bluetooth Type Definitions/Constants.    */
#include "./qapi_ble_gatt.h"      /* QAPI GATT prototypes.                    */
#include "./qapi_ble_scpstypes.h" /* QAPI SCPS prototypes.                    */

/**
 * @addtogroup qapi_ble_services
 * @{
 */

   /* Error Return Codes.                                               */

   /* Error Codes that are smaller than these (less than -1000) are     */
   /* related to the Bluetooth Protocol Stack itself (see               */
   /* qapi_ble_errors.h).                                               */
#define QAPI_BLE_SCPS_ERROR_INVALID_PARAMETER            (-1000)
/**< Invalid parameter. */
#define QAPI_BLE_SCPS_ERROR_INVALID_BLUETOOTH_STACK_ID   (-1001)
/**< Invalid Bluetooth Stack ID. */
#define QAPI_BLE_SCPS_ERROR_INSUFFICIENT_RESOURCES       (-1002)
/**< Insufficient resources. */
#define QAPI_BLE_SCPS_ERROR_SERVICE_ALREADY_REGISTERED   (-1003)
/**< Service is already registered. */
#define QAPI_BLE_SCPS_ERROR_INVALID_INSTANCE_ID          (-1004)
/**< Invalid service instance ID. */
#define QAPI_BLE_SCPS_ERROR_MALFORMATTED_DATA            (-1005)
/**< Malformatted data. */
#define QAPI_BLE_SCPS_ERROR_UNKNOWN_ERROR                (-1006)
/**< Unknown error. */

/**
 * Structure that represents the format of the SCPS Scan Interval Window
 * data.
 */
typedef struct qapi_BLE_SCPS_Scan_Interval_Window_Data_s
{
   /**
    * Scan interval.
    */
   uint16_t LE_Scan_Interval;

   /**
    * Scan window.
    */
   uint16_t LE_Scan_Window;
} qapi_BLE_SCPS_Scan_Interval_Window_Data_t;

#define QAPI_BLE_SCPS_SCAN_INTERVAL_WINDOW_DATA_SIZE     (sizeof(qapi_BLE_SCPS_Scan_Interval_Window_Data_t))
/**<
 * Size of the #qapi_BLE_SCPS_Scan_Interval_Window_Data_t structure.
 */

/**
 * Enumeration that represents the valid Read Request types that a server
 * may receive in a
 * QAPI_BLE_ET_SCPS_SERVER_READ_CLIENT_CONFIGURATION_REQUEST_E or
 * QAPI_BLE_ET_SCPS_SERVER_UPDATE_CLIENT_CONFIGURATION_REQUEST_E event is
 * used by the qapi_BLE_SCPS_Send_Notification() function to denote
 * the characteristic value to notify.
 *
 * For each event, it is up to the application to return (or
 * write) the correct Client Configuration descriptor based on this
 * value.
 */
typedef enum
{
   QAPI_BLE_CT_SCAN_REFRESH_E /**< Scan Refresh. */
} qapi_BLE_SCPS_Characteristic_Type_t;

/**
 * Enumeration that represents all the events generated by the SCPS
 * service. These are used to determine the type of each event
 * generated, and to ensure the proper union element is accessed for the
 * #qapi_BLE_SCPS_Event_Data_t structure.
 */
typedef enum
{
   QAPI_BLE_ET_SCPS_SERVER_READ_CLIENT_CONFIGURATION_REQUEST_E,
   /**< Read CCCD requet event. */
   QAPI_BLE_ET_SCPS_SERVER_UPDATE_CLIENT_CONFIGURATION_REQUEST_E,
   /**< Write CCCD requet event. */
   QAPI_BLE_ET_SCPS_SERVER_WRITE_SCAN_INTERVAL_WINDOW_REQUEST_E
   /**< Write Scan Interval/Window requet event. */
} qapi_BLE_SCPS_Event_Type_t;

/**
 * Structure that represents the format for the data that is dispatched
 * to an SCPS server when an SCPS client has sent a request to read an SCPS
 * characteristic's Client Characteristic Configuration Descriptor
 * (CCCD).
 *
 * Some of the structure fields will be required when responding to a
 * request using the
 * qapi_BLE_SCPS_Read_Client_Configuration_Response() function.
 */
typedef struct qapi_BLE_SCPS_Read_Client_Configuration_Data_s
{
   /**
    * SCPS instance that dispatched the event.
    */
   uint32_t                            InstanceID;

   /**
    * GATT connection ID for the connection with the SCPS client
    * that made the request.
    */
   uint32_t                            ConnectionID;

   /**
    * GATT transaction ID for the request.
    */
   uint32_t                            TransactionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the SCPS client.
    */
   qapi_BLE_GATT_Connection_Type_t     ConnectionType;

   /**
    * Bluetooth address of the SCPS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                  RemoteDevice;

   /**
    * Identifies the requested CCCD based on the SCPS Characteristic
    * type.
    */
   qapi_BLE_SCPS_Characteristic_Type_t ClientConfigurationType;
} qapi_BLE_SCPS_Read_Client_Configuration_Data_t;

#define QAPI_BLE_SCPS_READ_CLIENT_CONFIGURATION_DATA_SIZE  (sizeof(qapi_BLE_SCPS_Read_Client_Configuration_Data_t))
/**<
 * Size of the #qapi_BLE_SCPS_Read_Client_Configuration_Data_t structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an SCPS server when an SCPS client has sent a request to write an
 * SCPS characteristic's CCCD.
 */
typedef struct qapi_BLE_SCPS_Client_Configuration_Update_Data_s
{
   /**
    * SCPS instance that dispatched the event.
    */
   uint32_t                            InstanceID;

   /**
    * GATT connection ID for the connection with the SCPS client
    * that made the request.
    */
   uint32_t                            ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the SCPS client.
    */
   qapi_BLE_GATT_Connection_Type_t     ConnectionType;

   /**
    * Bluetooth address of the SCPS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                  RemoteDevice;

   /**
    * Identifies the requested CCCD based on the SCPS Characteristic
    * type.
    */
   qapi_BLE_SCPS_Characteristic_Type_t ClientConfigurationType;

   /**
    * CCCD value that has been requested to be written.
    */
   uint16_t                            ClientConfiguration;
} qapi_BLE_SCPS_Client_Configuration_Update_Data_t;

#define QAPI_BLE_SCPS_CLIENT_CONFIGURATION_UPDATE_DATA_SIZE  (sizeof(qapi_BLE_SCPS_Client_Configuration_Update_Data_t))
/**<
 * Size of the #qapi_BLE_SCPS_Client_Configuration_Update_Data_t
 * structure.
 */

/**
 * Structure that represents the format for the data that is dispatched
 * to an SCPS server when an SCPS client has sent a request to write the
 * SCPS Scan Interval and Window.
 */
typedef struct qapi_BLE_SCPS_Write_Scan_Interval_Window_Data_s
{
   /**
    * SCPS instance that dispatched the event.
    */
   uint32_t                                  InstanceID;

   /**
    * GATT connection ID for the connection with the SCPS client
    * that made the request.
    */
   uint32_t                                  ConnectionID;

   /**
    * GATT connection type, which identifies the transport used for
    * the connection with the SCPS client.
    */
   qapi_BLE_GATT_Connection_Type_t           ConnectionType;

   /**
    * Bluetooth address of the SCPS client that made the request.
    */
   qapi_BLE_BD_ADDR_t                        RemoteDevice;

   /**
    * Scan interval and window data.
    */
   qapi_BLE_SCPS_Scan_Interval_Window_Data_t ScanIntervalWindowData;
} qapi_BLE_SCPS_Write_Scan_Interval_Window_Data_t;

#define QAPI_BLE_SCPS_WRITE_SCAN_INTERVAL_WINDOW_DATA_SIZE  (sizeof(qapi_BLE_SCPS_Write_Scan_Interval_Window_Data_t))
/**<
 * Size of the #qapi_BLE_SCPS_Write_Scan_Interval_Window_Data_t structure.
 */

/**
 * Structure that represents the container structure for holding all the
 * event data for a SCPS instance.
 */
typedef struct qapi_BLE_SCPS_Event_Data_s
{
   /**
    * Event type used to determine the appropriate union member of
    * the Event_Data field to access.
    */
   qapi_BLE_SCPS_Event_Type_t Event_Data_Type;

   /**
    * Total size of the data contained in the event.
    */
   uint16_t                   Event_Data_Size;
   union
   {
      /**
       * SCPS Read CCCD event data.
       */
      qapi_BLE_SCPS_Read_Client_Configuration_Data_t   *SCPS_Read_Client_Configuration_Data;

      /**
       * SCPS Write CCCD event data.
       */
      qapi_BLE_SCPS_Client_Configuration_Update_Data_t *SCPS_Client_Configuration_Update_Data;

      /**
       * SCPS Write Scan Interval and Window event data.
       */
      qapi_BLE_SCPS_Write_Scan_Interval_Window_Data_t  *SCPS_Write_Scan_Interval_Window_Data;
   }
   /**
    * Event data.
    */
   Event_Data;
} qapi_BLE_SCPS_Event_Data_t;

#define QAPI_BLE_SCPS_EVENT_DATA_SIZE                    (sizeof(qapi_BLE_SCPS_Event_Data_t))
/**<
 * Size of the #qapi_BLE_SCPS_Event_Data_t structure.
 */

/**
 * Structure that contains the attribute handles that will need to be
 * cached by an SCPS client in order to only do service discovery once.
 */
typedef struct qapi_BLE_SCPS_Client_Information_s
{
   /**
    * SCPS Scan Interval and Window attribute handle.
    */
   uint16_t Scan_Interval_Window;

   /**
    * SCPS Scan Refresh attribute handle.
    */
   uint16_t Scan_Refresh;

   /**
    * SCPS Scan Refresh CCCD attribute handle.
    */
   uint16_t Scan_Refresh_Client_Configuration;
} qapi_BLE_SCPS_Client_Information_t;

#define QAPI_BLE_SCPS_CLIENT_INFORMATION_DATA_SIZE       (sizeof(qapi_BLE_SCPS_Client_Information_t))
/**<
 * Size of the #qapi_BLE_SCPS_Client_Information_t structure.
 */

/**
 * Structure that contains all of the per client data that will need to
 * be stored by a SCPS server.
 */
typedef struct qapi_BLE_SCPS_Server_Information_s
{
   /**
    * SCPS Scan Refresh CCCD.
    */
   uint16_t Scan_Refresh_Client_Configuration;
} qapi_BLE_SCPS_Server_Information_t;

#define QAPI_BLE_SCPS_SERVER_INFORMATION_DATA_SIZE       (sizeof(qapi_BLE_SCPS_Server_Information_t))
/**<
 * Size of the #qapi_BLE_SCPS_Server_Information_t structure.
 */

/**
 * @brief
 * This declared type represents the Prototype Function for an
 * SCPS Event Callback. This function will be called whenever a define
 * SCPS Event occurs within the Bluetooth Protocol Stack that is
 * specified with the specified Bluetooth Stack ID.
 *
 * @details
 * The event information is passed to the user in a #qapi_BLE_SCPS_Event_Data_t
 * structure. This structure contains all the information about the
 * event that occurred.
 *
 * The caller should use the contents of the SCPS Event Data
 * only in the context of this callback. If the caller requires
 * the data for a longer period of time, the callback function
 * must copy the data into another data buffer.
 *
 * This function is guaranteed not to be invoked more than once
 * simultaneously for the specified installed callback (i.e., this
 * function does not have be reentrant). It should be noted, however,
 * that if the same callback is installed more than once, the
 * callbacks will be called serially. Because of this, the processing
 * in this function should be as efficient as possible.
 *
 * It should also be noted that this function is called in the Thread
 * Context of a Thread that the user does not own. Therefore, processing
 * in this function should be as efficient as possible (this argument holds
 * anyway because another SCPS Event will not be processed while this
 * function call is outstanding).
 *
 * @note1hang
 * This function must not block and wait for events that can only be
 * satisfied by receiving other Bluetooth Stack Events. A Deadlock
 * will occur because other callbacks might not be issued while
 * this function is currently outstanding.
 *
 * @param[in]  BluetoothStackID      Unique identifier assigned to this
 *                                   Bluetooth Protocol Stack on which the
 *                                   event occurred.
 *
 * @param[in]  SCPS_Event_Data       Pointer to a structure that contains
 *                                   information about the event that has
 *                                   occurred.
 *
 * @param[in]  CallbackParameter     User-defined value that will be
 *                                   received with the SCPS Event data.
 *
 * @return None.
 */
typedef void (QAPI_BLE_BTPSAPI *qapi_BLE_SCPS_Event_Callback_t)(uint32_t BluetoothStackID, qapi_BLE_SCPS_Event_Data_t *SCPS_Event_Data, uint32_t CallbackParameter);

   /* SCPS server API.                                                  */

/**
 * @brief
 * Initializes an SCPS server on a specified Bluetooth Stack.
 *
 * @details
 * Only one SCPS server may be open at a time, per the Bluetooth Stack ID.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EventCallback        SCPS Event Callback that will
 *                                  receive SCPS server events.
 *
 * @param[in]  CallbackParameter    User-defined value that will be
 *                                  received with the specified
 *                                  EventCallback parameter.
 *
 * @param[out]  ServiceID           Unique GATT service ID of the
 *                                  registered SCPS service returned from
 *                                  qapi_BLE_GATT_Register_Service() API.
 *
 * @return      Positive, nonzero if successful. The return value will
 *              be the Service Instance ID of the SCPS server that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used in all subsequent function calls that
 *              require Instance ID.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_SCPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_SCPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_SERVICE_TABLE_FORMAT \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_SCPS_Initialize_Service(uint32_t BluetoothStackID, qapi_BLE_SCPS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID);

/**
 * @brief
 * Initializes an SCPS server on a specified Bluetooth Stack.
 *
 * @details
 * Unlike qapi_BLE_SCPS_Initialize_Service(), this function allows the
 * application to select a handle range in GATT to store the service.
 *
 * Only one SCPS server may be open at a time, per the Bluetooth Stack ID.
 *
 * @param[in]  BluetoothStackID     Unique identifier assigned to this
 *                                  Bluetooth Protocol Stack via a
 *                                  call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  EventCallback        SCPS Event Callback that will
 *                                  receive SCPS server events.
 *
 * @param[in]  CallbackParameter    User-defined value that will be
 *                                  received with the specified
 *                                  EventCallback parameter.
 *
 * @param[out]  ServiceID           Unique GATT service ID of the
 *                                  registered SCPS service returned from the
 *                                  qapi_BLE_GATT_Register_Service() API.
 *
 * @param[in,out]  ServiceHandleRange    Pointer that, on input, holds
 *                                       the handle range to store the
 *                                       service in GATT and, on output,
 *                                       contains the handle range for
 *                                       where the service is stored in
 *                                       GATT.
 *
 * @return      Positive, nonzero if successful. The return value will
 *              be the Service Instance ID of the SCPS server that was successfully
 *              opened on the specified Bluetooth Stack ID. This is the value
 *              that should be used in all subsequent function calls that
 *              require Instance ID.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_SCPS_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_SCPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_SERVICE_TABLE_FORMAT \n
 *                 QAPI_BLE_BTGATT_ERROR_INSUFFICIENT_RESOURCES \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_BTGATT_ERROR_INVALID_BLUETOOTH_STACK_ID \n
 *                 QAPI_BLE_BTGATT_ERROR_NOT_INITIALIZED
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_SCPS_Initialize_Service_Handle_Range(uint32_t BluetoothStackID, qapi_BLE_SCPS_Event_Callback_t EventCallback, uint32_t CallbackParameter, uint32_t *ServiceID, qapi_BLE_GATT_Attribute_Handle_Group_t *ServiceHandleRange);

/**
 * @brief
 * Cleans up and frees all resources
 * associated with a Scan Parameters Service (SCPS) Instance.
 *
 * @details
 * After this function is called, no other Device Information Service
 * function can be called until after a successful call to either of the
 * qapi_BLE_SCPS_Initialize_XXX() functions are performed.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from either of the qapi_BLE_SCPS_Initialize_XXX()
 *                                 functions.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_SCPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_SCPS_ERROR_INVALID_INSTANCE_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_SCPS_Cleanup_Service(uint32_t BluetoothStackID, uint32_t InstanceID);

/**
 * @brief
 * Queries the number of attributes
 * that are contained in the SCPS service that is registered with a
 * call to either the qapi_BLE_SCPS_Initialize_Service() or the
 * qapi_BLE_SCPS_Initialize_Service_Handle_Range() function.
 *
 * @return      Positive, nonzero if successful (represents the number of attributes
 *              for SCPS).
 *
 * @return      Zero for failure.
 */
QAPI_BLE_DECLARATION uint32_t QAPI_BLE_BTPSAPI qapi_BLE_SCPS_Query_Number_Attributes(void);

/**
 * @brief
 * Responds to a read
 * request from an SCPS client for an SCPS characteristic's CCCD.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from either of
 *                                 the qapi_BLE_SCPS_Initialize_XXX()
 *                                 functions.
 *
 * @param[in]  TransactionID       GATT transaction ID for the
 * request.
 *
 * @param[in]  Client_Configuration   Current value of the CCCD
 *                                    that will be sent.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_SCPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_SCPS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_GATT_ERROR_INVALID_TRANSACTION_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_SCPS_Read_Client_Configuration_Response(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t TransactionID, uint16_t Client_Configuration);

/**
 * @brief
 * Sends a Scan Refresh
 * notification to an SCPS client.
 *
 * @param[in]  BluetoothStackID    Unique identifier assigned to this
 *                                 Bluetooth Protocol Stack via a
 *                                 call to qapi_BLE_BSC_Initialize().
 *
 * @param[in]  InstanceID          Service instance ID to close.
 *                                 This is the value that was returned
 *                                 from either of
 *                                 the qapi_BLE_SCPS_Initialize_XXX()
 *                                 functions.
 *
 * @param[in]  ConnectionID        GATT connection ID for the
 *                                 connected remote device.
 *
 * @param[in]  ScanRefreshValue    Scan Refresh Value that will be
 *                                 notified to the SCPS client.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_SCPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_SCPS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_GATT_ERROR_INVALID_CONNECTION_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_SCPS_Notify_Scan_Refresh(uint32_t BluetoothStackID, uint32_t InstanceID, uint32_t ConnectionID, uint8_t ScanRefreshValue);

   /* SCPS client API                                                   */

/**
 * @brief
 * Formats a Scan
 * Interval Window Command into a user-specified buffer.
 *
 * @details
 * The BufferLength and Buffer parameter must point to a
 * buffer of at least QAPI_BLE_SCPS_SCAN_INTERVAL_WINDOW_SIZE in size.
 *
 * @param[in]  Scan_Interval_Window    Scan Interval Window to
 *                                     format into the user specified
 *                                     buffer.
 *
 * @param[in]  BufferLength            Length of the buffer that
 *                                     will receive the formatted Scan
 *                                     Interval Window.
 *
 * @param[out]  Buffer                 The buffer that will
 *                                     receive the formatted Scan
 *                                     Interval Window.
 *
 * @return      Zero if successful.
 *
 * @return      An error code if negative; one of the following values:
 *              @par
 *                 QAPI_BLE_SCPS_ERROR_INVALID_PARAMETER \n
 *                 QAPI_BLE_SCPS_ERROR_INVALID_INSTANCE_ID \n
 *                 QAPI_BLE_GATT_ERROR_INVALID_CONNECTION_ID
 */
QAPI_BLE_DECLARATION int QAPI_BLE_BTPSAPI qapi_BLE_SCPS_Format_Scan_Interval_Window(qapi_BLE_SCPS_Scan_Interval_Window_Data_t *Scan_Interval_Window, uint32_t BufferLength, uint8_t *Buffer);

/**
 * @}
 */

#endif
