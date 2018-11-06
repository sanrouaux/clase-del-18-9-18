#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

int validaLargoCadena(char cadena[], int largoMaximo);

int validaRangoEntero(int, int, int);
float validaRangoFlotante(float, float, float);

int validaSoloNumeros(char*);
int validaSoloLetras(char*);
int validaSoloAlfanumericos(char*);

int validaSiNo(char);

#endif // VALIDACIONES_H_INCLUDED
