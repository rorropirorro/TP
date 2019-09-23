#ifndef __EyM_H__
#define __EyM_H__

#include <stddef.h>

typedef struct {
  char * nombre , * apellido ;
  int edad ;
} _Judoca ;

typedef _Judoca * Judoca ;

typedef struct {
  Judoca participante1 , participante2 ;
  int estadoPareja ;
} _Pareja ;

typedef _Pareja * Pareja ;

typedef struct _TNodo {
  void * dato ;
  struct _TNodo * izq , * der ;
} TNodo ;

typedef TNodo * Arbol;

Arbol crearArbol(){
  return NULL;
}

typedef void (*Destruir) (void *d);
typedef int (*Comparar) (void *d1, void *d2);
typedef void (*Imprimir) (void *d1,FILE *file);

void destruirJudoca(void *judoca);

void destruirPareja(void *pareja);

Judoca crearJudoca(FILE *file);

Arbol eliminarArbol(Arbol arbol,Destruir destruir);

int definirEstado(Judoca judoca1, Judoca judoca2);

Pareja crearPareja(Judoca judoca1, Judoca judoca2);

int compararJudoca(void *judoca1, void* judoca2);

int compararPareja(void *pareja1, void *pareja2);

Arbol crearNodo(Arbol arbol,void *dato,Comparar comparar);

Arbol leerIngreso(FILE *file,Arbol arbol);

Judoca buscarParejaJudoca(Arbol Equipo1,Judoca judoca);

Arbol mayorMenores(Arbol arbol);

Arbol eliminarNodo(Arbol arbol, void *dato,Comparar comparar);

Arbol crearLista(Arbol *Equipo1,Arbol *Equipo2,Arbol Parejas);

void mostrarEstadoPareja(int estado,FILE *salida);

void imprimirPareja(void *dato,FILE *salida);

void imprimirJudoca(void *dato,FILE *salida);

void imprimirArbol(Arbol parejas,Imprimir imprimir,FILE *salida);
#endif
