#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ingresoDatos.h"
#include "validaciones.h"


/** \brief pide un numero al usuario, valida que esté dentro del rango de un int, que no haya caracteres
 *         que no sean numericos y que el numero entre dentro de un rango establecido por el usuario
 *
 * \param mensaje[] char mensaje que será mostrado al usuario
 * \param max int Numero maximo que puede aceptar la funcion
 * \param min int Numero minimo que acepta la funcion
 * \return int número ingresado por el usuario
 *
 */
int ingresaEntero(char mensaje[], int max, int min)
{
    int numero;
    char buffer[11];

    int banderaLargo;
    int banderaSoloNumeros;
    int banderaRango;

    puts(mensaje);
    fflush(stdin);
    gets(buffer);

    do
    {
        banderaSoloNumeros = 0;
        banderaLargo = 0;
        banderaRango = 0;

        if(validaSoloNumeros(buffer) == 0)
        {
            puts("Error. Ingreso caracteres invalidos.");
            banderaSoloNumeros = 1;
        }

        if(banderaSoloNumeros == 0 && validaLargoCadena(buffer, 11) != 1)
        {
            if(validaLargoCadena(buffer, 11)==0)
            {
                 puts("Error. Demasiados digitos.");
                 banderaLargo = 1;
            }
            else
            {
                puts("Error. No se introdujo ningun digito.");
                banderaLargo = 1;
            }
        }

        numero = atoi(buffer);
        if(banderaSoloNumeros == 0 && banderaLargo == 0 && validaRangoEntero(numero, max, min) == 0)
        {
            puts("Error. Numero fuera de rango.");
            banderaRango = 1;
        }

        if(banderaSoloNumeros == 1 || banderaLargo == 1 || banderaRango == 1)
        {
            puts("Ingrese el numero nuevamente: ");
            fflush(stdin);
            gets(buffer);
        }
    }
    while(banderaSoloNumeros == 1 || banderaLargo == 1 || banderaRango == 1);

    return numero;
}


/** \brief pide un numero al usuario y lo retorna
 *
 * \param mensaje[] char mensaje que será mostrado al usuario
 * \return float número ingresado por el usuario
 *
 */
float ingresaFlotante(char mensaje[])
{
    float numero;
    char buffer[15];

    printf("%s", mensaje);
    fflush(stdin);
    gets(buffer);

    while(validaSoloNumeros(buffer) == 0)
    {
        puts("Ingreso caracteres invalidos. Reingrese el numero: ");
        fflush(stdin);
        gets(buffer);
    }

    numero = atof(buffer);

    return numero;
}


/** \brief pide un carcater al usuario y lo retorna
 *
 * \param mensaje[] char mensaje que será mostrado al usuario
 * \return char caracter ingresado por el usuario
 *
 */
char ingresaCaracter(char mensaje[])
{
    char caracter;
    printf("%s", mensaje);
    fflush(stdin);
    scanf("%c", &caracter);
    return caracter;
}


/** \brief
 *
 * \return char
 *
 */
char pideYValidaSiNo()
{
    char letra;
    fflush(stdin);
    letra = getchar();

    while(letra != 's' && letra != 'n')
    {
        puts("Ingrese una opcion correcta: s/n");
        fflush(stdin);
        letra = getchar();
    }
    return letra;
}


int ingresaCadena(char cadena[], char mensaje[], int largo)
{
    char buffer[1024];
    int validacion;

    puts(mensaje);
    gets(buffer);

    validacion = validaLargoCadena(buffer, largo);

    while(validacion != 1)
    {
        if(validacion == 0)
        {
            puts("Demasiados carcateres. Ingrese nuevamente");
            fflush(stdin);
            gets(buffer);
            validacion = validaLargoCadena(buffer, largo);
        }
        else
        {
            puts("No ingreso ningun caracter. Ingrese nuevamente");
            fflush(stdin);
            gets(buffer);
            validacion = validaLargoCadena(buffer, largo);
        }
    }
    strcpy(cadena, buffer);
    return 0;
}


int ingresaCadenaSoloLetras(char cadena[], char mensaje[], int largo)
{
    char buffer[1024];
    int validacionLargo;
    int validacionCaracteres;

    puts(mensaje);
    fflush(stdin);
    gets(buffer);

    validacionLargo = validaLargoCadena(buffer, largo);
    validacionCaracteres = validaSoloLetras(buffer);

    while(validacionLargo != 1 || validacionCaracteres != 1)
    {
        if(validacionLargo == 0)
        {
            puts("Demasiados carcateres");
        }

        if(validacionLargo == -1)
        {
            puts("No ingreso ningun caracter");
        }

        if(validacionCaracteres == 0)
        {
            puts("Ingreso caracteres invalidos");
        }

        puts("Ingrese nuevamente: ");
        fflush(stdin);
        gets(buffer);
        validacionLargo = validaLargoCadena(buffer, largo);
        validacionCaracteres = validaSoloLetras(buffer);
    }

    strcpy(cadena, buffer);
    return 0;
}


/** \brief
 *
 * \param arrayLetras[] char
 * \return int
 *
 */
int ubicaMayusculasYMinusculas(char cadena[])
{
    int i;
    if(cadena != NULL)
    {
        strlwr(cadena);
        cadena[0] = toupper(cadena[0]);
        for(i = strlen(cadena); i > 1; i--)
        {
            if(cadena[i - 1] == ' ')
            {
                cadena[i] = toupper(cadena[i]);
            }
        }
        return 0;
    }
    return -1;
}
