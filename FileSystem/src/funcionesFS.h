/*
 * funcionesFS.h
 *
 *  Created on: 16/10/2017
 *      Author: utnso
 */

#ifndef FUNCIONESFS_H_
#define FUNCIONESFS_H_

#include <utilidades/Sockets.c>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <commons/log.h>
#include <commons/config.h>
#include <pthread.h>
#include <sys/mman.h>
#include <commons/bitarray.h>
#include <commons/collections/list.h>


typedef struct {
    int32_t nroNodo;
    t_bitarray* bitmap;
} t_nodo;

static t_nodo *nodo_create(int32_t nroNodo, t_bitarray* bitmap) {
	t_nodo *new = malloc(sizeof(t_nodo));
    new->nroNodo = nroNodo;
    new->bitmap = bitmap;
    return new;
}

static void nodo_destroy(t_nodo *self) {
    free(self->nroNodo);
    free(self->bitmap);
    free(self);
}

#endif /* FUNCIONESFS_H_ */