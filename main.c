#include <stdio.h>
#include "vacunodromo.h"

int main(int argc , char **argv) {

    char opcion = '\0', opcionPrincipal = '\0', opcion2 = '\0';

    //Creo el arbol donde metere a los pacientes
    TABB arbol;
    crearAbb(&arbol);

    VACUNODROMO vacunodromo;

    cargarArchivo(&arbol, argc, argv);

    while (opcionPrincipal != 's' && opcionPrincipal != 'S') {
        printf("\nBienvenido al programa de gestión PacVac\n");
        printf("A. Gestión de la base de datos\n");
        printf("B. Gestión del vacunódromo\n");
        printf("S. Salir\n");
        printf("Seleccione una opción: ");
        scanf(" %c", &opcionPrincipal);

        switch (opcionPrincipal) {
            case 'A':
            case 'a':
                //Menú de gestión de la base de datos
                opcion = '\0';  // Reiniciar la variable 'opcion' para este menú
                while (opcion != 's' && opcion != 'S') {
                    printf("\nBienvenido al programa de la Base de datos\n");
                    printf("A. Añadir paciente\n");
                    printf("L. Listar pacientes\n");
                    printf("E. Eliminar paciente\n");
                    printf("S. Salir\n");
                    printf("Seleccione una opción: ");
                    scanf(" %c", &opcion);

                    switch (opcion) {
                        case 'A':
                        case 'a':
                            anhadirPacienteArbol(&arbol); // Asegúrate de que esta función esté definida en alguna parte de tu código
                            break;

                        case 'L':
                        case 'l':
                            listarPacientes(arbol); // Asegúrate de que esta función esté definida en alguna parte de tu código
                            break;

                        case 'E':
                        case 'e':
                            eliminarPaciente(&arbol); // Asegúrate de que esta función esté definida en alguna parte de tu código
                            break;

                        case 'S':
                        case 's':
                            // No es necesario ningún break aquí, ya que queremos salir del bucle
                            continue;

                        default:
                            printf("Opción incorrecta, inténtelo de nuevo\n");
                    }
                }

                break;

            case 'B':
            case 'b':
                //Menú gestión del vacunódromo
                opcion2 = '\0';  // Reiniciar la variable 'opcion2' para este menú
                while (opcion2 != 's' && opcion2 != 'S') {
                    printf("\nBienvenido al programa de gestión del Vacunódromo\n");
                    printf("C. Crear cola de vacunación\n");
                    printf("V. Vacunar\n");
                    printf("S. Salir\n");
                    printf("Seleccione una opción: ");
                    scanf(" %c", &opcion2);

                    switch (opcion2) {
                        case 'C':
                        case 'c':
                            crearColaVacunacion(arbol, &vacunodromo); // Asegúrate de que esta función esté definida en alguna parte de tu código
                            break;

                        case 'V':
                        case 'v':
                            vacunar(&vacunodromo, &arbol); // Asegúrate de que esta función esté definida en alguna parte de tu código
                            break;

                        case 'S':
                        case 's':
                            // No es necesario ningún break aquí, ya que queremos salir del bucle
                            continue;

                        default:
                            printf("Opción incorrecta, inténtelo de nuevo\n");
                            break;
                    }
                }

                break;

            case 'S':
            case 's':
                // No es necesario ningún break aquí, ya que queremos salir del bucle
                continue;

            default:
                printf("Opción incorrecta, inténtelo de nuevo\n");
                break;
        }
    }

    //La funcion hace las comprobaciones necesarias y actualiza el archivo
    actualizarArchivo(arbol, argc, argv);

    //destruimos el arbol
    destruirAbb(&arbol);
}

