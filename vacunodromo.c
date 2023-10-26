//
// Created by Pablo Seijo on 3/10/23.
//

#include <string.h>
#include <stdlib.h>
#include "stdio.h"
#include "vacunodromo.h"
#include "TADs/abb.h"
#include "TADs/cola.h"

/**
 * Añade un paciente al arbol de pacientes con sus correspondientes vacunas
 * @param *arbol - puntero arbol binario en el cual añadiremos los pacientes (debe estar creado previamente)
 */
void anhadirPacienteArbol (TABB *arbol){

    TIPOELEMENTOABB paciente;
    TIPOELEMENTOLISTA vacuna;

    printf("Introduzca el nombre del paciente: ");
    scanf(" %[^\r\n]", paciente.ApellidosNombre); //Me permite coger todos los caracteres hasta el cambio de linea

    //Comprobamos si el paciente se encuentra en el arbol
    if(esMiembroAbb(*arbol, paciente)){
        printf("El paciente ya esta en nuestra base de datos\n");
        return;
    }
    else {
        crearLista(&paciente.ListaVacunas);

        printf("Introduzca el nombre de las vacunas (fin para finalizar): ");
        scanf(" %[^\r\n]", vacuna.nombreVacuna);

        //Hacemos un bucle para añadirle las vacunas al paciente
        while (strcmp(vacuna.nombreVacuna, "fin") != 0) {
            printf("Introduzca el numero maximo de dosis: ");
            scanf(" %d", &vacuna.maxDosis);

            // Inicializamos las vacunas a 0
            vacuna.dosisAdministradas = 0;

            // Insertamos la vacuina en la lista de vacunas
            insertarElementoLista(&paciente.ListaVacunas, finLista(paciente.ListaVacunas), vacuna);

            printf("Introduzca el nombre de las vacunas (fin para finalizar): ");
            scanf(" %[^\r\n]", vacuna.nombreVacuna);
        }

        //finalmente añadimos la lista de vacunas al paciente y lo metemos en el arbol binario

        insertarElementoAbb(arbol, paciente);
        printf("El paciente ha sido añadido a la base de datos\n");
    }
}

/**
* Elimina un paciente del arbol de pacientes con sus correspondientes vacunas
* @param *arbol - puntero arbol binario en el cual eliminaremos los pacientes (debe estar creado previamente)
*/
void eliminarPaciente(TABB *arbol){

    TIPOELEMENTOABB paciente;

    printf("Introduzca el nombre del paciente: ");
    scanf(" %[^\r\n]",paciente.ApellidosNombre);

    //Destruimos la lista y suprimimos el nodo del arbol
    if(esMiembroAbb(*arbol,paciente)){
        suprimirElementoAbb(arbol, paciente);
    }
    else{
        printf("Algo ha fallado. El paciente no se encuentra en la base de datos. Compruebe las credenciales\n");
    }
}

/**
* Imprime la informacion de las vacunas de la lista
* @param lista - lista donde se almacenan las vacunas de los pacientes
*/
void imprimirVacunas(TLISTA l){

    //Ponemos la posicion en el primero de la lista
    TPOSICION posicion = primeroLista(l);
    TIPOELEMENTOLISTA listaVacunas;

    while(posicion != finLista(l)){
        //Recuperamos el elemento de la lista
        recuperarElementoLista(l,posicion,&listaVacunas);

        //Imprimimos la informacion sobre la vacuna del paciente
        printf("    VACUNA: %s DOSIS %d de %d\n",
               listaVacunas.nombreVacuna, listaVacunas.dosisAdministradas, listaVacunas.maxDosis );

        //Movemos la posicion al sigueitne de la lista
        posicion = siguienteLista(l, posicion);
    }
}

/**
* Imprime la informacion del paciente
* @param paciente - tipoelementoabb que almacena la informacion del paciente y la lista de vacunas
*/
void imprimirPaciente(TIPOELEMENTOABB paciente){

    printf("\nNombre: %s\n", paciente.ApellidosNombre);

    //Comprobamos si la lista de vacunas esta vacia
    if(!esListaVacia(paciente.ListaVacunas)){
        imprimirVacunas(paciente.ListaVacunas);
    }
    else{
        printf("No vacunado\n");
    }

}

/**
* Imprime la informacion del paciente
* @param arbol - arbol binario que recorreremos para obtener los pacientes
*/
void listarPacientes(TABB arbol){
    TIPOELEMENTOABB paciente;

    if(esAbbVacio(arbol)){
        return;
    }
    else{
        //Recorremos recursivamente el arbol izquierdo hasta la hoja
        listarPacientes(izqAbb(arbol));

        //Imprimimos el paciente
        leerElementoAbb(arbol,&paciente);
        imprimirPaciente(paciente);

        //Recorremos el arbol derecho
        listarPacientes(derAbb(arbol));
    }
}

/**
 * Elimina el retorno de carro y la nueva línea de la cadena de texto ingresada
 * @param linea - Cadena de caracteres que se va a procesar
 */
void _strip_line (char *linea ) {
    linea [ strcspn ( linea ,"\r\n" ) ] = 0;
}

/**
* Carga los datos del archivo en el arbol
* @param *A - arbol binario en el que guardaremos los pacientes del archivo
* @param nparam - numero parametros que se pasaron por linea de comandos
* @param argv - puntero a array que contiene la informacion pasada por linea de comandos
*/
void cargarArchivo ( TABB *A , int nparam , char ** argv ) {
    char linea[100]; // variable temporal para almacenar una linea completa del archivo

    //Revisamos el numero de parametros y que el primero sea -f
    if (nparam < 3 || strcmp(argv[1], "-f") != 0) {
        return;
    }
    else {
        FILE *file = fopen(argv[2], "r"); // Abre el archivo para lectura
        if (file == NULL) {
            printf("Error al abrir el archivo %s\n", argv[2]);
            exit(0); // Salir con un código de error
        }

        while (fgets(linea, 100, file) != NULL) { // mientras hay lineas en el archivo
            _strip_line(linea);

            // Creo la lista de vacunas
            TIPOELEMENTOLISTA vacuna;
            TIPOELEMENTOABB paciente;

            crearLista(&paciente.ListaVacunas);

            // Primera llamada a strtok para extraer hasta "|"
            strcpy(paciente.ApellidosNombre, strtok(linea, "|"));

            // Segunda llamada a strtok para extraer desde "|"
            char *listaVacunas = strtok(NULL, "|");

            // AHORA SEPARAMOS LAS VACUNAS CON strtok ()
            // La primera llamada a strtok recibe listaVacunas y el separador
            char *token = strtok(listaVacunas, ";");

            // Para cada vacuna tengo dos valores , el nombre y maxDosis , voy a llevar un contador y diferencio los casos
            // con un switch

            while (token != NULL) {
                strcpy(vacuna.nombreVacuna, token); // Primero es el nombre de la vacuna

                token = strtok(NULL, ";"); // Segundo token, dosis administradas
                if (token) {
                    vacuna.dosisAdministradas = atoi(token);
                }

                token = strtok(NULL, ";"); // Tercer token, dosis máximas
                if (token) {
                    vacuna.maxDosis = atoi(token);
                }

                // Insertar vacuna en la lista aquí
                insertarElementoLista(&paciente.ListaVacunas, finLista(paciente.ListaVacunas), vacuna);

                token = strtok(NULL, ";"); // Siguiente vacuna, si existe
            }

            // inserto el paciente en el arbol
            insertarElementoAbb(A, paciente);


        }

        fclose(file);
    }
}

/**
 * Funcion auxiliar para realizar el recorrido preorden en el arbol e imprimirlo en el archivo
 * @param arbol - arbol que contiene la informacion del paciente
 * @param file - archivo donde cargar los pacientes del arbol
 */
void preordenArchivo(TABB arbol, FILE *file) {
    //Declaramos el tipoelemento donde cargar el paciente
    TIPOELEMENTOABB paciente;

    //Como es preorden imprimimos -> izquierda -> derecha
    if (!esAbbVacio(arbol)) {
        //leemos el nodo y lo cargamos
        leerElementoAbb(arbol, &paciente);
        fprintf(file, "%s|", paciente.ApellidosNombre);

        if (!esListaVacia(paciente.ListaVacunas)) {
            //Imprimimos las vacunas

            //Ponemos la posicion en el primero de la lista
            TPOSICION posicion = primeroLista(paciente.ListaVacunas);
            TIPOELEMENTOLISTA listaVacunas;

            while (posicion != finLista(paciente.ListaVacunas)) {
                //Recuperamos el elemento de la lista
                recuperarElementoLista(paciente.ListaVacunas, posicion, &listaVacunas);

                //Imprimimos la informacion sobre la vacuna del paciente
                fprintf(file, "%s;%d;%d;",
                        listaVacunas.nombreVacuna, listaVacunas.dosisAdministradas, listaVacunas.maxDosis);

                //Movemos la posicion al sigueitne de la lista
                posicion = siguienteLista(paciente.ListaVacunas, posicion);
            }
            fprintf(file,"\n");
        }

        //Llamamos izquierda y derecha
        preordenArchivo(izqAbb(arbol), file);
        preordenArchivo(derAbb(arbol), file);
    }
}

/**
* Actualiza los datos del archivo en funcion de los del arbol
* @param A - arbol binario del que cogeremos los datos de los pacientes
* @param nparam - numero parametros que se pasaron por linea de comandos
* @param args - puntero a array que contiene la informacion pasada por linea de comandos
*/
void actualizarArchivo (TABB arbol, int nparam , char **argv){
    char nArchivo[20];
    FILE *file;
    //Si tenemos 3 parametros significa que se le pasa un archivo por terminal
    if (nparam == 3) {
        file = fopen(argv[2], "w+"); // Abre el archivo para escritura, sobrescribe el archivo existente
        if (file == NULL) {
            printf("Error al abrir el archivo %s\n", argv[2]);
            return;
        }
    } else {
        //Si no se le pasa ningun archivo se le pregunta por un archivo de salida
       printf("Introduzca el nombre del archivo de salida: ");
       scanf(" %s", nArchivo);

       file = fopen(nArchivo, "w"); // Abre el archivo para escritura, sobrescribe el archivo existente
       if (file == NULL) {
           printf("Error al abrir el archivo %s\n", nArchivo);
           return;
       }
    }
    if(!esAbbVacio(arbol)) {
        preordenArchivo(arbol, file);
    }

    fclose(file);
}

/**
 * Añade los pacientes que se van a vacunar a la cola de vacunacion y retorna el numero
 * @param arbol - arbol que contiene la informacion del paciente
 * @param nombreVacuna - nombre de la vacuna que se va a administrar
 * @param colaVacunacion - cola donde se almacenaran los pacientes que se van a vacunar
 * @return numero de pacientes que se van a vacunar
 */
int anhadirPacienteCola(TABB arbol, char* nombreVacuna, TCOLA *colaVacunacion) {
    int numeroPacientes = 0;

    // Si el árbol está vacío, retornamos
    if (arbol == NULL || esAbbVacio(arbol)) {
        return numeroPacientes;
    }

    // Declaramos el paciente y lo leemos
    TIPOELEMENTOABB paciente;
    leerElementoAbb(arbol, &paciente);

    if (paciente.ListaVacunas) {
        // Recorremos la lista de vacunas del paciente
        TPOSICION posicion = primeroLista(paciente.ListaVacunas);
        while (posicion != finLista(paciente.ListaVacunas)) {
            // Recuperamos la vacuna
            TIPOELEMENTOLISTA vacuna;
            recuperarElementoLista(paciente.ListaVacunas, posicion, &vacuna);

            // Si la vacuna coincide con la que se va a administrar, añadimos el paciente a la cola
            if (strcmp(vacuna.nombreVacuna, nombreVacuna) == 0) {
                anadirElementoCola(colaVacunacion, paciente);
                numeroPacientes++;  // Aumentamos el número de pacientes
                printf("        -> %s\n", paciente.ApellidosNombre);
                break;  // Salimos del bucle si se encuentra la vacuna, no hay necesidad de seguir buscando
            }
            // Movemos la posición a la siguiente vacuna en la lista
            posicion = siguienteLista(paciente.ListaVacunas, posicion);
        }
    }

    // Recorrido del subárbol izquierdo y derecho, acumulando el número de pacientes
    numeroPacientes += anhadirPacienteCola(izqAbb(arbol), nombreVacuna, colaVacunacion);
    numeroPacientes += anhadirPacienteCola(derAbb(arbol), nombreVacuna, colaVacunacion);

    return numeroPacientes;
}


/**
 * Crea la cola de vacunacion
 * @param colaVacunacion - cola donde se almacenaran los pacientes que se van a vacunar
 * @param arbol - arbol que contiene la informacion del paciente
 */
void crearColaVacunacion(TABB arbol, VACUNODROMO *vacunodromo) {
    char nombreVacuna[30];

    TCOLA colaVacunacion;

    // Pedimos el nombre de la vacuna
    printf("    Introduzca la vacuna a administrar: ");
    scanf(" %[^\r\n]", nombreVacuna);

    printf("    Nombre del vacunodromo: %s\n", nombreVacuna);

    // Creamos la cola de vacunacion
    crearCola(&colaVacunacion);

    // Añadimos los pacientes a la cola
    int numeroPacientes = anhadirPacienteCola(arbol, nombreVacuna, &colaVacunacion);

    // Guardamos el nombre de la vacuna en el vacunodromo
    strcpy(vacunodromo->nombreVacuna, nombreVacuna);

    //Guardamos el numero de pacientes en el vacunodromo
    vacunodromo->numPacientes = numeroPacientes;

    //Metemos la cola de vacunacion en el vacunodromo
    vacunodromo->colaPacientes = colaVacunacion;

}

/**
 * Vacuna a un paciente. Si quedan vacunas por administrar lo devolvemos al final de la cola, si no lo eliminamos
 * @param colaVacunacion - cola donde se almacenaran los pacientes que se van a vacunar
 * @param arbol - arbol que contiene la informacion del paciente
 */
void vacunar(VACUNODROMO *vacunodromo, TABB *arbol) {

    TIPOELEMENTOABB paciente;
    TIPOELEMENTOLISTA vacuna;

    if(vacunodromo == NULL || esColaVacia(vacunodromo->colaPacientes)){
        if(vacunodromo == NULL){
            printf("ERROR, vacunodromo inexistente\n");
        }
        else{
            printf("La cola de vacunacion de %s esta vacia\n", vacunodromo->nombreVacuna);
        }
        return;
    }
    else{
        consultarPrimerElementoCola(vacunodromo->colaPacientes, &paciente);

        /*   BUSQUEDA SOBRE LA LISTA DEL PACIENTE    */

        //Declaramos el TPOSICION para recorrer la lista de vacunas del paciente
        TPOSICION posicion = primeroLista(paciente.ListaVacunas);
        recuperarElementoLista(paciente.ListaVacunas, posicion, &vacuna);

        //Mientras el nombre de la vacuna no sea igual al nombre de la vacuna del vacunodromo iteramos
        while(strcmp(vacuna.nombreVacuna, vacunodromo->nombreVacuna) != 0 && posicion != NULL){
            //Recuperamos la vacuna
            recuperarElementoLista(paciente.ListaVacunas, posicion, &vacuna);
            //Si el nombre de la vacuna es el mismo salimos del bucle
            if(strcmp(vacuna.nombreVacuna, vacunodromo->nombreVacuna) == 0){
                break;
            }
            //Si no pasamos a la siguiente posicion de la lista
            else {
                posicion = siguienteLista(paciente.ListaVacunas, posicion);
                //Comprobamos que la posicion no sea NULL
                if(posicion == NULL){
                    //Si lo es significa que el paciente no tiene la vacuna
                    printf("El paciente no tiene la vacuna %s\n", vacunodromo->nombreVacuna);
                    return;
                }
            }
        }

        /*   VACUNACION DEL PACIENTE    */

        //Primero comprobamos que efectivamente el numero de dosis administradas es menor al maximo
        if(vacuna.dosisAdministradas < vacuna.maxDosis){
            vacuna.dosisAdministradas++;
            //Vacunamos al paciente y subimos el numero de dosis administradas
            printf("    Vacunando a %s con %s (dosis %d de %d)\n", paciente.ApellidosNombre, vacuna.nombreVacuna,
                   vacuna.dosisAdministradas, vacuna.maxDosis);

            //Si una vez aumentado el numero de dosis administradas estas son iguales al maximo, eliminamos al paciente de la cola
            if(vacuna.dosisAdministradas == vacuna.maxDosis){
                suprimirElementoCola(&vacunodromo->colaPacientes);
                vacunodromo->numPacientes--;

                //Eliminamos la vacuna del paciente
                suprimirElementoLista(&paciente.ListaVacunas, posicion);

                if(esListaVacia(paciente.ListaVacunas)){
                    //Si la lista de vacunas esta vacia, eliminamos al paciente del arbol
                    suprimirElementoAbb(arbol, paciente);
                }
            }

            else {
                modificarElementoLista(&paciente.ListaVacunas, posicion, vacuna);
                //Si no, lo eliminamos y lo volvemos a añadir al final de la cola para su posterior vacunacion
                suprimirElementoCola(&vacunodromo->colaPacientes);
                anadirElementoCola(&vacunodromo->colaPacientes, paciente);
            }

        }
    }
}







