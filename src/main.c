#include <stdio.h>
#include <stdlib.h>

#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/threadapi.h"
#include "azure_c_shared_utility/crt_abstractions.h"
#include "iothub_client.h"
#include "iothub_message.h"
#include "iothubtransportamqp.h"

static const char* connectionString = "[device connection string]";

static char msgText[1024];

typedef struct EVENT_INSTANCE_TAG
{
    IOTHUB_MESSAGE_HANDLE messageHandle;
    size_t messageTrackingId;  // For tracking the messages within the user callback.
} EVENT_INSTANCE;



static void SendConfirmationCallback(IOTHUB_CLIENT_CONFIRMATION_RESULT result, void* userContextCallback)
{
    EVENT_INSTANCE* eventInstance = (EVENT_INSTANCE*)userContextCallback;
    (void)printf("SendConfirmationCallback: %s\r\n", ENUM_TO_STRING(IOTHUB_CLIENT_CONFIRMATION_RESULT, result));
    
    /* Some device specific action code goes here... */
    IoTHubMessage_Destroy(eventInstance->messageHandle);
}



static IOTHUBMESSAGE_DISPOSITION_RESULT ReceiveMessageCallback(IOTHUB_MESSAGE_HANDLE message, void* userContextCallback)
{
    const char* buffer;
    size_t size;
    if (IoTHubMessage_GetByteArray(message, (const unsigned char**)&buffer, &size) == IOTHUB_MESSAGE_OK)
    {
        (void)printf("Received Message with Data: <<<%.*s>>> & Size=%d\r\n", (int)size, buffer, (int)size);
    }

    /* Some device specific action code goes here... */
    return IOTHUBMESSAGE_ACCEPTED;
}

void run(){

platform_init();

IOTHUB_CLIENT_LL_HANDLE iotHubClientHandle;
iotHubClientHandle = IoTHubClient_LL_CreateFromConnectionString(connectionString, AMQP_Protocol);


sprintf_s(msgText, sizeof(msgText), "hello world from my device");
EVENT_INSTANCE message;
message.messageHandle = IoTHubMessage_CreateFromByteArray((const unsigned char*)msgText, strlen(msgText));
//MAP_HANDLE propMap = IoTHubMessage_Properties(message.messageHandle);
IoTHubClient_LL_DoWork(iotHubClientHandle);
ThreadAPI_Sleep(1);

IoTHubClient_LL_SetMessageCallback(iotHubClientHandle, ReceiveMessageCallback, NULL);

printf("sending a hello world message...\n");
IoTHubClient_LL_SendEventAsync(iotHubClientHandle, message.messageHandle, SendConfirmationCallback, &message);

IOTHUB_CLIENT_STATUS status;
while ((IoTHubClient_LL_GetSendStatus(iotHubClientHandle, &status) == IOTHUB_CLIENT_OK) && (status == IOTHUB_CLIENT_SEND_STATUS_BUSY))
{
    IoTHubClient_LL_DoWork(iotHubClientHandle);
    ThreadAPI_Sleep(1000);
}


IoTHubClient_LL_Destroy(iotHubClientHandle);
platform_deinit();
}

int main()
{
run();
return 0;
}
