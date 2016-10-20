# iothubc
## Setup
### provide the connection string of the iot hub device in the main.c 
## Info 
The compiled libraries here are for armhf. Compile them by yourself and replace them (lib subfolder) for other platforms.

You get the libraries linked by this sample by compiling the [azure-iot-sdks](https://github.com/Azure/azure-iot-sdks/tree/master/c "azure-iot-sdks c"). 

Look how to [prepare your development environment](https://github.com/Azure/azure-iot-sdks/blob/master/c/doc/devbox_setup.md#linux).

After building the sdk the path of the here used libraries is:

azure-iot-sdks/c/cmake/iotsdk_linux
  * /azure-uamqp-c -> libuamqp.a
  * /azure-c-shared-utility -> libaziotsharedutil.a
  * /iothub_client -> libiothub_client_amqp_transport.a, libiothub_client.a

The path of the here used header files is:

/azure-iot-sdks/c
  * /azure-c-shared-utility/inc
  * /iothub_client/inc
