#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "ingresoDatos.h"
#include "validaciones.h"
#include "Employee.h"
#include "parser.h"
#include "Controller.h"


/** \brief Desplega el menu de opciones y pide al usuario una opcion
 *
 * \return int Opcion seleccionada por el usuario
 *
 */
int menuDeOpciones()
{
    int option;

    printf("-------------------MENU DE OPCIONES--------------------------\n");
    printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
    printf("2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n");
    printf("3. Alta de empleado\n");
    printf("4. Modificar datos de empleado\n");
    printf("5. Baja de empleado\n");
    printf("6. Listar empleados\n");
    printf("7. Ordenar empleados\n");
    printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
    printf("9. Guardar los datos de los empleados en el archivo data.bin (modo binario).\n");
    printf("10. Salir\n");
    printf("Introduzca una opcion: ");
    fflush(stdin);
    scanf("%d", &option);

    return option;
}


/** \brief
 *
 * \return int
 *
 */
char menuModificacionEmpleado()
{
    char option;

    puts("Que dato desea cambiar?");
    puts("a. Nombre");
    puts("b. Horas trabajadas");
    puts("c. Sueldo");
    option = ingresaCaracter("Ingrese una opcion: ");

    return option;
}


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char* Ruta del archivo que contiene los datos
 * \param pArrayListEmployee LinkedList* Puntero a la lista en que seran cargados los datos
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    pArchivo = fopen(path, "r");

    parser_EmployeeFromText(pArchivo, pArrayListEmployee);

    return 1;
}


/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    pArchivo = fopen(path, "rb");

    if(pArchivo == NULL)
    {
        puts("Error. No se pudo abrir el archivo\n");
    }
    else
    {
        parser_EmployeeFromBinary(pArchivo, pArrayListEmployee);
    }
    return 1;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    Employee* pEmployee;
    pEmployee = (Employee*) malloc(sizeof(Employee));

    pEmployee->id = controller_calculaNuevoId(pArrayListEmployee);

    char auxNombre[128];
    ingresaCadenaSoloLetras(auxNombre, "Ingrese el nombre del empleado: ", 128);
    ubicaMayusculasYMinusculas(auxNombre);
    strcpy(pEmployee->nombre, auxNombre);

    pEmployee->horasTrabajadas = ingresaEntero("Ingrese las horas trabajadas", 720, 0);

    pEmployee->sueldo = ingresaEntero("Ingrese el sueldo del empleado: ", 2000000, 0);

    ll_add(pArrayListEmployee, pEmployee);

    puts("\nSE DIO EL ALTA A UN EMPLEADO\n");

    return 1;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    controller_ListEmployee(pArrayListEmployee);

    int id;
    id = ingresaEntero("Ingrese el ID del empleado: ", 1000000, 0);

    Employee* pEmployee;
    int largo;
    largo = ll_len(pArrayListEmployee);
    int flag = 0;
    int i;
    for(i=0; i<largo; i++)
    {
        pEmployee = ll_get(pArrayListEmployee, i);
        if(pEmployee->id == id)
        {
            flag = 1;
            break;
        }
    }

    char confirma;
    char opcionModificacion;
    char auxNombre[128];
    int auxHoras;
    int auxSueldo;

    if(flag==0)
    {
        puts("No se encontro un empleado con ese ID");
    }
    else
    {
        printf("Se encontro al empleado: %s\n", pEmployee->nombre);
        puts("Es correcto? s/n");
        confirma = pideYValidaSiNo();
        if(confirma == 's')
        {
            opcionModificacion = menuModificacionEmpleado();
            switch(opcionModificacion)
            {
            case 'a':
                ingresaCadenaSoloLetras(auxNombre, "Ingrese el nuevo nombre: ", 128);
                employee_setNombre(pEmployee, auxNombre);
                puts("\nSE MODIFICARON LOS DATOS DE UN EMPLEADO\n");
                break;

            case 'b':
                auxHoras = ingresaEntero("Ingrese las nuevas horas trabajadas", 720, 0);
                employee_setHorasTrabajadas(pEmployee, auxHoras);
                puts("Se modificaron los datos del empleado");
                break;

            case 'c':
                auxSueldo = ingresaEntero("Ingrese el nuevo sueldo: ", 2000000, 0);
                employee_setSueldo(pEmployee, auxSueldo);
                puts("Se modificaron los datos del empleado");
                break;

            default:
                puts("No se ingreso una opcion valida");
            }
        }
        else
        {
            puts("Accion cancelada");
        }
    }

    return 1;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    Employee* pEmployee;
    int i;
    int id;
    int index = -1;
    int largo;
    char confirma;

    controller_ListEmployee(pArrayListEmployee);

    puts("Ingrese el ID del empleado a eliminar");
    scanf("%d", &id);

    largo = ll_len(pArrayListEmployee);
    for(i=0; i<largo; i++)
    {
        pEmployee = ll_get(pArrayListEmployee, i);
        if(pEmployee->id == id)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        puts("No se encontro al empleado");
    }
    else
    {
        printf("Se encontro al empleado: %s\n", pEmployee->nombre);
        puts("Es correcto?");
        confirma = pideYValidaSiNo();
        if(confirma == 's')
        {
            ll_remove(pArrayListEmployee, index);
            puts("\nSE DIO DE BAJA A UN EMPLEADO\n");
        }
        else
        {
            puts("Accion cancelada");
        }
    }
    return 1;
}


/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    if(ll_isEmpty(pArrayListEmployee))
    {
        puts("No hay empleados para mostrar");
    }
    else
    {
        Employee* auxEmployee;

        int largo;
        largo = ll_len(pArrayListEmployee);

        puts("ID      NOMBRE         HORAS TRABAJADAS   SUELDO");

        int i;
        for(i=0; i <largo; i++)
        {
            auxEmployee = ll_get(pArrayListEmployee, i);
            printf("%-8d%-15s%-19d%-d\n", auxEmployee->id, auxEmployee->nombre, auxEmployee->horasTrabajadas,
                   auxEmployee->sueldo);
        }
    }
    return 1;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    puts("Procesando. . .");
    ll_sort(pArrayListEmployee, controller_comparaEmployees, 1);
    puts("\nSE ORDENO ALFABETICAMENTE LA LISTA\n");

    return 1;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    pArchivo = fopen(path, "w");

    Employee* pEmployee;

    int len;
    len = ll_len(pArrayListEmployee);

    int i;
    for(i=0; i<len; i++)
    {
        pEmployee = ll_get(pArrayListEmployee, i);

        fprintf(pArchivo, "%d,%s,%d,%d\n", pEmployee->id, pEmployee->nombre, pEmployee->horasTrabajadas,
                pEmployee->sueldo);
    }

    fclose(pArchivo);

    puts("\nSE GUARDARON LOS DATOS EN EL ARCHIVO DE TEXTO(data.csv)\n");

    return 1;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo;
    pArchivo = fopen(path, "wb");

    if(pArchivo == NULL)
    {
        puts("No se pudo crear el archivo");
    }
    else
    {
        Employee* pEmployee;

        int len;
        len = ll_len(pArrayListEmployee);

        int i;
        for(i=0; i<len; i++)
        {
            pEmployee = ll_get(pArrayListEmployee, i);

            fwrite(pEmployee, sizeof(Employee), 1, pArchivo);
        }
    }
    fclose(pArchivo);

    puts("\nSE GUARDARON LOS DATOS EN EL ARCHIVO BINARIO(data.bin)\n");

    return 1;
}


int controller_calculaNuevoId(LinkedList* lista)
{
    int idMayor = 0;
    int i;
    int largo;
    Employee* pEmployee;
    int bandera = 0;

    largo = ll_len(lista);

    for(i=0; i<largo; i++)
    {
        pEmployee = ll_get(lista, i);
        if(bandera == 0)
        {
            idMayor = pEmployee->id;
            bandera = 1;
        }

        if(pEmployee->id > idMayor)
        {
            idMayor = pEmployee->id;
        }
    }
    return idMayor+1;
}


int controller_comparaEmployees(void* punteroUno, void* punteroDos)
{
    int retorno = 0;

    Employee* pEmployeeUno;
    Employee* pEmployeeDos;

    pEmployeeUno = (Employee*) punteroUno;
    pEmployeeDos = (Employee*) punteroDos;

    if(stricmp(pEmployeeUno->nombre, pEmployeeDos->nombre)<0)
    {
        retorno = -1;
    }
    else if(stricmp(pEmployeeUno->nombre, pEmployeeDos->nombre)>0)
    {
        retorno = 1;
    }
    return retorno;
}
