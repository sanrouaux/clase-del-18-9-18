#include <stdio.h>
#include <stdlib.h>

/** \brief busca espacio disponible
 *
 * \param int[] listado de enteros
 * \param int tamaño del listado
 * \param int valor ilogico
 * \return int [-1] si no hay espacio y [>=0], un índice donde guardar
 *
 */
int buscarLibre(int[], int, int);


int main()
{
    //CONSIGNA
    // crear vector de enteros
    //inicializarlo en un valor ilogico
    // do-while pidiendo datos

    int vector[10];
    char respuesta;
    int indice;


    int i;
    for(i = 0; i < 10; i++)
    {
        vector[i] = -1;
    }

    do
    {
        indice = buscarLibre(vector, 10, -1);

        if(indice != -1)
        {
            printf("Ingrese dato: ");
            scanf("%d", &vector[indice]);
        }
        else
        {
            printf("No hay mas espacio");
            break;
        }

        printf("Cargar otro dato? s/n");
        fflush(stdin);
        scanf("%c", &respuesta);

    }while(respuesta == 's');


    return 0;
}


int buscarLibre(int numeros[], int tam, int ilogico)
{
    int index = -1;
    int i;
    for(i = 0; i < 10; i++)
        {
            if(numeros[i] == ilogico)
            {
                index = i;
                break;
            }
        }

    return index;
}
