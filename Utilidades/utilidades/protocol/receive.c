/*
 * receive.c
 * Generado automaticamente por ProtoCool
*/

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "types.h"
#include "unpackers.h"

void* receive(int socket,HEADER_T* cabecera){
    void* payload;
    HEADER_T header;
    int status = recv(socket,&header,sizeof(HEADER_T),0);
    if(!status){
         (*cabecera) = FIN_COMUNICACION;
         return NULL;
    }
    switch(header){
        case SOLICITUD_PROCESAMIENTO:
        payload = unpack_SOLICITUD_PROCESAMIENTO(socket);
        break;
        case SOLICITUD_REDUCCIONLOCAL:
        /* Carece de Payload */
        break;
        case SOLICITUD_REDUCCIONGLOBAL:
        /* Carece de Payload */
        break;
        case SOLICITUD_ALMACENAMIENTO:
        /* Carece de Payload */
        break;
        case ORDEN_TRANSFORMACION:
        payload = unpack_ORDEN_TRANSFORMACION(socket);
        break;
        case ORDEN_REDUCCIONLOCAL:
        payload = unpack_ORDEN_REDUCCIONLOCAL(socket);
        break;
        case ORDEN_REDUCCIONGLOBAL:
        payload = unpack_ORDEN_REDUCCIONGLOBAL(socket);
        break;
        case ORDEN_ALMACENAMIENTO:
        payload = unpack_ORDEN_ALMACENAMIENTO(socket);
        break;
        case INFO_TRANSFORMACION:
        payload = unpack_INFO_TRANSFORMACION(socket);
        break;
        case INFO_REDUCCIONLOCAL:
        payload = unpack_INFO_REDUCCIONLOCAL(socket);
        break;
        case INFO_REDUCCIONGLOBAL:
        payload = unpack_INFO_REDUCCIONGLOBAL(socket);
        break;
        case INFO_ALMACENAMIENTO:
        payload = unpack_INFO_ALMACENAMIENTO(socket);
        break;
        case PETICION_NODO:
        payload = unpack_PETICION_NODO(socket);
        break;
        case NODO:
        payload = unpack_NODO(socket);
        break;
        case FIN_LISTA:
        /* Carece de Payload */
        break;
        case FIN_COMUNICACION:
        /* Carece de Payload */
        break;
        case ARCHIVO:
        payload = unpack_ARCHIVO(socket);
        break;
        case BLOQUE:
        payload = unpack_BLOQUE(socket);
        break;
        case PRESENTACION_DATANODE:
        payload = unpack_PRESENTACION_DATANODE(socket);
        break;
    }
    (*cabecera) = header;
    return payload;
}
