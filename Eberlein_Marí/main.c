#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EyM.h"

int main(){
  Arbol Equipo1=crearArbol();

  Arbol Equipo2=crearArbol();

  Arbol Parejas=crearArbol();

  FILE *ingreso = fopen( "ingreso.txt", "r");
  FILE *salida = fopen( "salida.txt", "w");

  Equipo1=leerIngreso(ingreso,Equipo1);
  Equipo2=leerIngreso(ingreso,Equipo2);

  fclose(ingreso );

  while(Equipo1&&Equipo2){
    Parejas=crearLista(&Equipo1,&Equipo2,Parejas);
  }


  imprimirArbol(Parejas,imprimirPareja,salida);
  imprimirArbol(Equipo1,imprimirJudoca,salida);
  imprimirArbol(Equipo2,imprimirJudoca,salida);

  Parejas=eliminarArbol(Parejas,destruirPareja);
  Equipo1=eliminarArbol(Equipo1,destruirJudoca);
  Equipo2=eliminarArbol(Equipo2,destruirJudoca);

  fclose(salida );

  return 0;

