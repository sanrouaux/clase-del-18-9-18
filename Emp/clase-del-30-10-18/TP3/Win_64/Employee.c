#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"


/** \brief
 *
 * \return Employee*
 *
 */
Employee* employee_new()
{
    Employee* pEmployee;
    pEmployee = (Employee*) malloc(sizeof(Employee));

    return pEmployee;
}

/** \brief
 *
 * \param idStr char*
 * \param nombreStr char*
 * \param horasTrabajadasStr char*
 * \return Employee*
 *
 */
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr)
{
    Employee* pEmployee;
    pEmployee = (Employee*) malloc(sizeof(Employee));

    pEmployee->id = atoi(idStr);
    strcpy(pEmployee->nombre, nombreStr);
    pEmployee->horasTrabajadas = atoi(horasTrabajadasStr);
    pEmployee->sueldo = 0;

    return pEmployee;
}


/** \brief
 *
 * \return void
 *
 */
void employee_delete(Employee* this)
{
    free(this);
    this = NULL;
}

/** \brief
 *
 * \param this Employee*
 * \param id int
 * \return int
 *
 */
int employee_setId(Employee* this,int id)
{
    this->id = id;
    return 0;
}

/** \brief
 *
 * \param this Employee*
 * \param id int*
 * \return int
 *
 */
int employee_getId(Employee* this,int* id)
{
    *id = this->id;
    return 0;
}

/** \brief
 *
 * \param this Employee*
 * \param nombre char*
 * \return int
 *
 */
int employee_setNombre(Employee* this,char* nombre)
{
    strcpy(this->nombre, nombre);
    return 0;
}

/** \brief
 *
 * \param this Employee*
 * \param nombre char*
 * \return int
 *
 */
int employee_getNombre(Employee* this,char* nombre)
{
    strcpy(nombre, this->nombre);
    return 0;
}

/** \brief
 *
 * \param this Employee*
 * \param horasTrabajadas int
 * \return int
 *
 */
int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    this->horasTrabajadas = horasTrabajadas;
    return 0;
}

/** \brief
 *
 * \param this Employee*
 * \param horasTrabajadas int*
 * \return int
 *
 */
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    *horasTrabajadas = this->horasTrabajadas;
    return 0;
}

/** \brief
 *
 * \param this Employee*
 * \param sueldo int
 * \return int
 *
 */
int employee_setSueldo(Employee* this,int sueldo)
{
    this->sueldo = sueldo;
    return 0;
}

/** \brief
 *
 * \param this Employee*
 * \param sueldo int*
 * \return int
 *
 */
int employee_getSueldo(Employee* this,int* sueldo)
{
    *sueldo = this->sueldo;
    return 0;
}
