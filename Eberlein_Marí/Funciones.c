#include "EyM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void destruirJudoca(void *judoca){
  if(judoca){

    free(((Judoca)judoca)->nombre);
    free(((Judoca)judoca)->apellido);
    free((Judoca)judoca);
  }
}

void destruirPareja(void *pareja){
  if(pareja){
    destruirJudoca(((Pareja)pareja)->participante1);
    destruirJudoca(((Pareja)pareja)->participante2);
    free(pareja);
  }
}

Judoca crearJudoca(FILE *file){
    char nombre[100], apellido[100];
    int edad;

    if((fscanf(file,"%[^,:], %[^,], %d",nombre,apellido,&edad))==3){
    fgetc(file);
      Judoca judoca = malloc(sizeof(_Judoca));
      judoca->nombre = malloc((sizeof(char)*strlen(nombre))+1);
      judoca->apellido = malloc((sizeof(char)*strlen(apellido))+1);

      strcpy(judoca->nombre,nombre);
      strcpy(judoca->apellido,apellido);
      judoca->edad = edad;

      return judoca;
    }

    return NULL;
}

Arbol eliminarArbol(Arbol arbol,Destruir destruir){
  if(arbol){
    arbol->izq=eliminarArbol(arbol->izq,destruir);
    arbol->der=eliminarArbol(arbol->der,destruir);
    destruir(arbol->dato);
    free(arbol);
  }
  return NULL;
}

int definirEstado(Judoca judoca1, Judoca judoca2){
      if(judoca1->edad >= 18 && judoca2->edad >= 18){
          if(abs(judoca1->edad - judoca2->edad) <= 2){
            return 0;
          } else return 3;
      }else if(judoca1->edad < 18 && judoca2->edad < 18){
          if(abs(judoca1->edad - judoca2->edad) <= 1){
            return 0;
          } else return 2;
      }else return 1;
}

Pareja crearPareja(Judoca judoca1, Judoca judoca2){
    Pareja pareja=malloc(sizeof(_Pareja));
    pareja->participante1=judoca1;
    pareja->participante2=judoca2;
    pareja->estadoPareja=definirEstado(judoca1,judoca2);
    return pareja;
}

int compararJudoca(void *judoca1, void* judoca2){
        if(((Judoca)judoca1)->edad < ((Judoca)judoca2)->edad) return -1;
        if(((Judoca)judoca1)->edad > ((Judoca)judoca2)->edad) return 1;
        return 0;
}

int compararPareja(void *pareja1, void *pareja2){
    return ((Pareja)pareja1)->estadoPareja < ((Pareja)pareja2)->estadoPareja;
}

Arbol crearNodo(Arbol arbol,void *dato,Comparar comparar){
    if(!arbol){
      arbol=malloc(sizeof(TNodo));
      arbol->dato=dato;
      arbol->izq=NULL;
      arbol->der=NULL;
    }else{
      if(comparar(dato,arbol->dato)>0){
        (arbol->der)=crearNodo(arbol->der,dato,comparar);
      }else{
        (arbol->izq)=crearNodo(arbol->izq,dato,comparar);
      }
    }
    return arbol;
}

Arbol leerIngreso(FILE *file,Arbol arbol){
  char basura[16];
  fscanf(file,"%[^\n]",basura);
  fgetc(file);

  Judoca judoca=crearJudoca(file);

    while(judoca){
      arbol=crearNodo(arbol,judoca,compararJudoca);
      judoca=crearJudoca(file);
    }
    return     arbol;
}

Judoca buscarParejaJudoca(Arbol Equipo1,Judoca judoca){
  if(definirEstado(Equipo1->dato,judoca)!=0){
    if(compararJudoca(judoca,Equipo1)<0){
      return buscarParejaJudoca(Equipo1->izq,judoca);
    }else return buscarParejaJudoca(Equipo1->izq,judoca);
  }else return Equipo1->dato;
}

Arbol mayorMenores(Arbol arbol){
    if((arbol->izq)==NULL){
      return NULL;
    } else {
      Arbol nodo=arbol->izq;
      while(nodo->der){
        nodo=nodo->der;
      }
      return nodo;
    }
}

Arbol eliminarNodo(Arbol arbol, void *dato,Comparar comparar){
    if (!arbol) return NULL;
    if (comparar(dato,arbol->dato)!=0) {
        if (comparar(dato,arbol->dato)==-1)
            arbol->izq = eliminarNodo(arbol->izq, dato, comparar);
        else
            arbol->der = eliminarNodo(arbol->der, dato, comparar);
      }
      else {
          if (!(arbol->izq) && !(arbol->der))    {
              free(arbol);
              arbol = NULL;
              return arbol;
          }
          else if (!(arbol->izq) || !(arbol->der)) {
              Arbol nuevoArbol = !(arbol->izq)? arbol->der : arbol->izq;
        free(arbol);
              arbol = nuevoArbol;
              return arbol;
          }
          else {
              Arbol nodo = mayorMenores(arbol);
              arbol->dato = nodo->dato;
              arbol->izq=eliminarNodo(arbol->izq, nodo->dato,comparar);
          }

      }
      return arbol;
}

Arbol crearLista(Arbol *Equipo1,Arbol *Equipo2,Arbol Parejas){
      Pareja pareja;
      Judoca aux=buscarParejaJudoca((*Equipo1),(*Equipo2)->dato);
      pareja=crearPareja(aux,(*Equipo2)->dato);
      (*Equipo1)=eliminarNodo((*Equipo1), aux, compararJudoca);
      (*Equipo2)=eliminarNodo((*Equipo2),(*Equipo2)->dato,compararJudoca);
      Parejas=crearNodo(Parejas,pareja,compararPareja);


    return Parejas;
}

void mostrarEstadoPareja(int estado,FILE *salida){
    if(estado==0) fprintf(salida,"Pareja valida");
    if(estado==1) fprintf(salida,"Menor y mayor");
    if(estado==2) fprintf(salida,"Menores con mas de un año de diferencia");
    if(estado==3) fprintf(salida,"Mayores con mas de dos años de diferencia");
}

void imprimirPareja(void *dato,FILE *salida){
    fprintf(salida,"%s ",((Pareja)dato)->participante1->nombre);
    fprintf(salida,"%s - ",((Pareja)dato)->participante1->apellido);
    fprintf(salida,"%s ",((Pareja)dato)->participante2->nombre);
    fprintf(salida,"%s - ",((Pareja)dato)->participante2->apellido);
    mostrarEstadoPareja((((Pareja)dato)->estadoPareja),salida);             //guimpel gei
    fprintf(salida,"\n");
}

void imprimirJudoca(void *dato,FILE *salida){
    fprintf(salida,"%s ",((Judoca)dato)->nombre);
    fprintf(salida,"%s ",((Judoca)dato)->apellido);
    fprintf(salida,"No tiene pareja\n");
}

void imprimirArbol(Arbol parejas,Imprimir imprimir,FILE *salida){
    if(parejas){
      imprimirArbol(parejas->izq,imprimir,salida);
      imprimir(parejas->dato,salida);
      imprimirArbol(parejas->der,imprimir,salida);
    }
}
