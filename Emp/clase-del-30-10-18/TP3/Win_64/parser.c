#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int r;
    int cantidad;
    int cantidadRechazados = 0;
    int cantidadAceptados = 0;

    char idStr[4];
    char nombreStr[128];
    char horasStr[4];
    char sueldoStr[6];
    Employee* pEmployee;
    Employee* auxPEmployee;

    fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", idStr, nombreStr, horasStr, sueldoStr);
    while(!feof(pFile))
    {
        r = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", idStr, nombreStr, horasStr, sueldoStr);
        if(r == 4)
        {
            pEmployee = (Employee*) malloc(sizeof(Employee));

            pEmployee->id = atoi(idStr);
            strcpy(pEmployee->nombre, nombreStr);
            pEmployee->horasTrabajadas = atoi(horasStr);
            pEmployee->sueldo = atoi(sueldoStr);

            cantidad = ll_len(pArrayListEmployee);

            int i;
            int flag = 0;
            for(i=0; i<cantidad; i++)
            {
                auxPEmployee = ll_get(pArrayListEmployee, i);
                if(pEmployee->id == auxPEmployee->id)
                {
                    flag = 1;
                }
            }

            if(flag == 0)
            {
                ll_add(pArrayListEmployee, pEmployee);
                cantidadAceptados++;
            }
            else
            {
                cantidadRechazados++;
            }
        }
        else
        {
            break;
        }
    }
    fclose(pFile);

    printf("\nSE CARGARON %d NUEVOS EMPLEADOS A LA LISTA\n", cantidadAceptados);
    if(cantidadRechazados != 0)
    {
        printf("\n%d EMPLEADOS FUERON RECHAZADOS POR INCOMPATIBILIDAD DE ID\n", cantidadRechazados);
    }

    return 1;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile, LinkedList* pArrayListEmployee)
{
    int i;
    int bandera = 0;
    int largoLista;
    int cantidadEmpleadosRechazados = 0;
    int cantidadEmpleadosIncluidos = 0;

    int cantidadDatosLeidos;
    Employee* pEmployee;

    Employee* auxUnoEmpleado;
    auxUnoEmpleado = (Employee*) malloc(sizeof(Employee));
    Employee* auxDosEmpleado;
    auxDosEmpleado = (Employee*) malloc(sizeof(Employee));

    largoLista = ll_len(pArrayListEmployee);


    while(!feof(pFile))
    {
        cantidadDatosLeidos = fread(auxUnoEmpleado, sizeof(Employee), 1, pFile);
        if(cantidadDatosLeidos == 1)
        {
            for(i=0; i<largoLista; i++)
            {
                auxDosEmpleado = ll_get(pArrayListEmployee, i);
                if(auxUnoEmpleado->id == auxDosEmpleado->id)
                {
                    cantidadEmpleadosRechazados++;
                    bandera = 1;
                    break;
                }
            }

            if(bandera == 0)
            {
                pEmployee = (Employee*) malloc(sizeof(Employee));
                *pEmployee = *auxUnoEmpleado;
                ll_add(pArrayListEmployee, pEmployee);
                cantidadEmpleadosIncluidos++;
            }
        }
    }

    fclose(pFile);

    printf("\nSE CARGARON %d NUEVOS EMPLEADOS A LA LISTA\n", cantidadEmpleadosIncluidos);
    if(cantidadEmpleadosRechazados != 0)
    {
        printf("\n%d EMPLEADOS FUERON RECHAZADOS POR INCOMPATIBILIDAD DE ID\n", cantidadEmpleadosRechazados);
    }

    return 1;
}
