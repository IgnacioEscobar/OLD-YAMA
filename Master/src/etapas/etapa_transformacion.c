/*
 * etapa_transformacion.c
 */
#include <stdio.h>
#include <utilidades/protocol/senders.h>
#include <utilidades/protocol/types.h>
#include <utilidades/protocol/receive.h>
#include <commons/log.h>
#include "etapas.h"

MASTER_STATUS etapa_transformacion (int socketYAMA,t_log* logger, char* yamafs_archivo){
	log_trace(logger, "Iniciando etapa de transformacion...");

	HEADER_T header;
	payload_INFO_TRANSFORMACION* payload;
	void* data;

	send_SOLICITUD_PROCESAMIENTO(socketYAMA,yamafs_archivo);
	data = receive(socketYAMA,&header);

	if (header == FIN_COMUNICACION){ /*Si header es FIN_COMUNICACION es porque se cerro la conexion*/ }
	// Recibir todas las instrucciones
	// Hasta que termine la lista
	while(header != FIN_LISTA){
		if (header == INFO_TRANSFORMACION){
			payload = data;
			printf("Conectarse a nodo en %s:%d , bloque: %d , bytes:%d, nombreDelTemporal: %s\n",payload->IP_Worker,payload->PUERTO_Worker,payload->bloque,payload->bytesocupados,payload->nombreArchivoTemporal);
		}
		//
		data = receive(socketYAMA,&header);
		if (header == FIN_COMUNICACION){ /*Si header es FIN_COMUNICACION es porque se cerro la conexion */}
	}
	// IMPORTANTE! HAY UN LEAK DE MEMORIA
	// LA FUNCION DE RECOLECCION ESTA EN DESARROLLO
	// Codigo de transformacion
	return EXITO;
};
