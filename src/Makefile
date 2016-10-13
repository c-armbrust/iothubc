bbb-iothub-deviceclient:
	gcc main.c -I "../inc" -L "../lib" -liothub_client -liothub_client_amqp_transport -laziotsharedutil -luamqp -lm -lcurl -lssl -lcrypto -lpthread -o bbb-iothub-deviceclient

clean:
	rm bbb-iothub-deviceclient
