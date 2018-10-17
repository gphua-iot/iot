
#ifndef _APP_H
#define _APP_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "system_config.h"
#include "system_definitions.h"

#include "wolfmqttsdk/wolfmqtt/mqtt_client.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************

#define APP_HARDWARE  "iot_ethernet_dm990004"
#define APP_TITLE       "iot_ethernet"
#define APP_PART_NUMBER "dm990004"
#define APP_FIRMWARE_VERSION "2.0.0"

// String literals for debugging

#define AWS_IOT_PORT 8883

#define NVM_CLIENT_CERTIFICATE_SPACE    (64 * 1024)
#define NVM_CLIENT_KEY_SPACE            (48 * 1024)
#define NVM_HOST_ADDRESS_SPACE          (32 * 1024)

/* Application Codes */
enum AppCodes {
    APP_CODE_ERROR_BAD_ARG = -255,
    APP_CODE_ERROR_OUT_OF_BUFFER,
    APP_CODE_ERROR_SSL_FATAL,
    APP_CODE_ERROR_INVALID_SOCKET,
    APP_CODE_ERROR_FAILED_TO_BEGIN_DNS_RESOLUTION,
    APP_CODE_ERROR_DNS_FAILED,
    APP_CODE_ERROR_FAILED_SSL_NEGOTIATION,
    APP_CODE_ERROR_TIMEOUT,
    APP_CODE_ERROR_CMD_TIMEOUT,
    APP_CODE_SUCCESS = 0,
};

// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behavior of the application at various times.
*/

typedef enum
{
	/* Application's state machine's initial state. */
	APP_STATE_INIT=0,
    APP_NVM_ERASE_CONFIGURATION,
    APP_NVM_LOAD_CONFIGURATION,
    APP_NVM_WRITE_CONFIGURATION,
    APP_TCPIP_WAIT_INIT,
    APP_TCPIP_WAIT_FOR_IP,
    APP_TCPIP_WAIT_CONFIGURATION,
    APP_TCPIP_MQTT_INIT,
    APP_TCPIP_MQTT_NET_CONNECT,
    APP_TCPIP_MQTT_PROTOCOL_CONNECT,
    APP_TCPIP_MQTT_SUBSCRIBE,
    APP_TCPIP_MQTT_LOOP,
    APP_TCPIP_ERROR,
    APP_FATAL_ERROR

} APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
 */

typedef struct
{
    /* The application's current state */
    APP_STATES state;

    // MAC Address of board
    char macAddress[12 + 1];

    // Client certificate location
    __attribute__ ((aligned(4))) unsigned char clientCert[2048];

    // Client key location
    __attribute__ ((aligned(4))) unsigned char clientKey[2048];

    // Network handles
    NET_PRES_SKT_HANDLE_T socket;
    TCP_PORT port;
    NET_PRES_SKT_ERROR_T error;
    void* ctx;
    void* ssl;

    // Is board commissioned boolean flag
    bool isCommissioned;
    bool writeToNVM;

    // The AWS endpoint to access the AWS IoT Service
    __attribute__ ((aligned(4))) unsigned char host[256];

    // The AWS endpoint IP address location
    IP_MULTI_ADDRESS  host_ipv4;

    // NVM Driver
    DRV_HANDLE nvmHandle;
    DRV_NVM_COMMAND_HANDLE      nvmCommandHandle[10];
    SYS_FS_MEDIA_GEOMETRY       *gAppNVMMediaGeometry;
    DRV_NVM_COMMAND_STATUS      nvmStatus;

    /* Counter to track the number of successful command
    complete events */
    uint8_t                     eventCount;

    /* Counter to track the number of unsuccessful command
    complete events */
    uint8_t                     errorEventCount;

    // Timers
    uint32_t genericUseTimer;
    uint32_t timerTCPIP;
    uint32_t mqttKeepAlive;

    // Mqtt Client
    MqttNet myNet;
    MqttClient myClient;

    // Value for light show
    uint32_t lightShowVal;

    // LED Values
    bool led1;
    bool led2;
    bool led3;
    bool led4;

    bool led1val;
    bool led2val;
    bool led3val;
    bool led4val;

    // Debug Variables
    bool socket_connected;
    bool mqtt_connected;
    bool debugSet;
    IP_MULTI_ADDRESS  board_ipAddr;

} APP_DATA;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Routines
// *****************************************************************************
// *****************************************************************************
/* These routines are called by drivers when certain events occur.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     MPLAB Harmony application initialization routine.

  Description:
    This function initializes the Harmony application.  It places the
    application in its initial state and prepares it to run so that its
    APP_Tasks function can be called.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    MPLAB Harmony Demo application tasks function

  Description:
    This routine is the Harmony Demo application's tasks function.  It
    defines the application's state machine and core logic.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
 */

void APP_Tasks( void );

bool APP_TIMER_Expired(uint32_t * timer, uint32_t seconds);
bool APP_TIMER_Expired_ms(uint32_t * timer, uint32_t mseconds);
bool APP_TIMER_Set(uint32_t * timer);
void APP_DebugMessage(int DebugMessage);

#endif /* _APP_H */

//DOM-IGNORE-BEGIN
#ifdef __cplusplus
}
#endif
//DOM-IGNORE-END

/*******************************************************************************
 End of File
 */
