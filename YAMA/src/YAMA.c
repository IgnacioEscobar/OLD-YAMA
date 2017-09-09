/*
 ============================================================================
 Name        : YAMA.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <parser/metadata_program.h>
#include <commons/log.h>
#include <commons/collections/list.h>
#include <commons/config.h>
#include <commons/string.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int puertoFs = 0;
char* ipFs = "";
int retardoPlanificacion = 0;
char* algoritmoBalanceo = "";

t_log* log;

void leerConfiguracion(){
	char* path = "/home/utnso/workspace/tp-2017-2c-Grupo-1---K3525/YAMA/src/yama-config.cfg";
	t_config* archivo_configuracion = config_create(path);
	puertoFs = config_get_int_value(archivo_configuracion, "FS_PUERTO");
	printf("El puerto FS es: %i \n", puertoFs);
	ipFs = config_get_string_value(archivo_configuracion, "FS_IP");
	printf("La IP FS es: %s \n", ipFs);
	retardoPlanificacion = config_get_int_value(archivo_configuracion, "RETARDO_PLANIFICACION");
	printf("El retardo de la Planificacion es: %i \n", retardoPlanificacion);
	algoritmoBalanceo = config_get_string_value(archivo_configuracion, "ALGORITMO_BALANCEO");
	printf("El Algoritmo de Balanceo es: %s \n", algoritmoBalanceo);

	config_destroy(archivo_configuracion);
}

int main(void) {
	puts("Comienza el proceso YAMA");

	log = log_create("yama.log", "YAMA", false, LOG_LEVEL_TRACE);

	log_trace(log, "Leyendo configuracion");
	leerConfiguracion();
	log_trace(log, "Configuracion leida");

	struct sockaddr_in direccionServidor;
			direccionServidor.sin_family = AF_INET;
			direccionServidor.sin_addr.s_addr = INADDR_ANY;
			direccionServidor.sin_port = htons(5040);

			int cliente = socket(AF_INET, SOCK_STREAM, 0);
			if (connect(cliente, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
				perror("No se pudo conectar");
				return 1;
			}

			//------- Mensaje de bienvenida del FileSystem ---------------
			char buf[256];
			char* buffer = malloc(1000);
			int bytesRecibidos = recv(cliente, buffer, sizeof(buf), 0);
			buffer[bytesRecibidos] = '\0';
			printf("%d dice: %s\n", cliente, buffer);
			//------------------------------------------------------------

			while (1) {
				char mensaje[1000];
				scanf("%s", mensaje);
				send(cliente, mensaje, strlen(mensaje), 0);
			}


	return EXIT_SUCCESS;
}


