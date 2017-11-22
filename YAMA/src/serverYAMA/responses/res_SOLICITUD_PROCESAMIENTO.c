/*
 * res_SOLICITUD_PROCESAMIENTO.c
 */
#include <stdio.h>
#include <commons/collections/dictionary.h>
#include <utilidades/protocol/senders.h>

#include "../../serverYAMA/responses/responses.h"

YAMA_STATUS res_SOLICITUD_PROCESAMIENTO  (int socket,void*  data, t_dictionary* diccionario){
	payload_SOLICITUD_PROCESAMIENTO* payload = data;
	printf("SOLICITUD_PROCESAMIENTO recibida\n");
	printf("Archivo: %s, enviando informacion sobre workers\n",payload->nombreArchivo);

	send_JOB(socket,1,2);

	//DUMMIE WORKERS
	send_INFO_TRANSFORMACION(socket,9095,"127.0.0.1",38,10180,"/tmp/Master1-temp38");
	send_INFO_TRANSFORMACION(socket,9095,"127.0.0.1",39,10180,"/tmp/Master1-temp39");
	send_INFO_TRANSFORMACION(socket,9095,"127.0.0.1",44,10180,"/tmp/Master1-temp44");

	send_INFO_REDUCCIONLOCAL(socket,9095,"127.0.0.1","/tmp/Master1-temp38","/tmp/Master1-tempredLoc38");
	send_INFO_REDUCCIONLOCAL(socket,9095,"127.0.0.1","/tmp/Master1-temp39","/tmp/Master1-tempredLoc39");
	send_INFO_REDUCCIONLOCAL(socket,9095,"127.0.0.1","/tmp/Master1-temp44","/tmp/Master1-tempredLoc44");

	send_INFO_REDUCCIONGLOBAL(socket,9095,"127.0.0.1","/tmp/Master1-tempredLoc38"," ",0);
	send_INFO_REDUCCIONGLOBAL(socket,9095,"127.0.0.1","/tmp/Master1-tempredLoc39"," ",0);
	send_INFO_REDUCCIONGLOBAL(socket,9095,"127.0.0.1","/tmp/Master1-tempredLoc44","/tmp/Master1-tempredGlob44",1);
	send_FIN_LISTA(socket);

	send_INFO_ALMACENAMIENTO(socket,9095,"127.0.0.1","/tmp/Master1-tempredGlob44");

	return EXITO;
};
