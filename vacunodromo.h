//
// Created by Pablo Seijo on 3/10/23.
//

#ifndef VACUNODROMO_VACUNODROMO_H
#define VACUNODROMO_VACUNODROMO_H

#include "TADs/abb.h"
#include "TADs/cola.h"

typedef struct vacunodromo {
    char nombreVacuna[50];
    TCOLA colaPacientes;
    int numPacientes;
} VACUNODROMO;

/**
 * Añade un paciente al arbol de pacientes con sus correspondientes vacunas
 * @param *arbol - puntero arbol binario en el cual añadiremos los pacientes (debe estar creado previamente)
 */
void anhadirPacienteArbol (TABB *arbol);

/**
* Elimina un paciente del arbol de pacientes con sus correspondientes vacunas
* @param *arbol - puntero arbol binario en el cual eliminaremos los pacientes (debe estar creado previamente)
*/
void eliminarPaciente(TABB *arbol);

/**
* Imprime la informacion de las vacunas de la lista
* @param lista - lista donde se almacenan las vacunas de los pacientes
*/
void imprimirVacunas(TLISTA l);

/**
* Imprime la informacion del paciente
* @param paciente - tipoelementoabb que almacena la informacion del paciente y la lista de vacunas
*/
void imprimirPaciente(TIPOELEMENTOABB paciente);

/**
* Imprime la informacion del paciente
* @param arbol - arbol binario que recorreremos para obtener los pacientes
*/
void listarPacientes(TABB arbol);

/**
* Carga los datos del archivo en el arbol
* @param *A - arbol binario en el que guardaremos los pacientes del archivo
* @param nparam - numero parametros que se pasaron por linea de comandos
* @param argv - puntero a array que contiene la informacion pasada por linea de comandos
*/
void cargarArchivo ( TABB *A , int nparam , char ** argv );

/**
* Actualiza los datos del archivo en funcion de los del arbol
* @param A - arbol binario del que cogeremos los datos de los pacientes
* @param nparam - numero parametros que se pasaron por linea de comandos
* @param argv - puntero a array que contiene la informacion pasada por linea de comandos
*/
void actualizarArchivo (TABB arbol, int nparam , char ** argv);

/**
 * Crea la cola de vacunacion
 * @param colavacunacion - cola donde se almacenaran los pacientes que se van a vacunar
 * @param arbol - arbol que contiene la informacion del paciente
 */
void crearColaVacunacion(TABB arbol, VACUNODROMO *vacunodromo);

/**
 * Vacuna a un paciente. Si quedan vacunas por administrar lo devolvemos al final de la cola, si no lo eliminamos
 * @param colaVacunacion - cola donde se almacenaran los pacientes que se van a vacunar
 * @param arbol - arbol que contiene la informacion del paciente
 */
void vacunar(VACUNODROMO *vacunodromo, TABB *arbol);

#endif //VACUNODROMO_VACUNODROMO_H
