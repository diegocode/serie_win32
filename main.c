/*

 - Abre un port serie.
 - lo configura.
 - recibe mensaje ascii terminado en \n y lo muestra.

*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "seriewin32.h"

int main() {
    FILE *f;

    /* HANDLE para el port serie */
    HANDLE port_serie;

    BYTE numport;
    DWORD baudios;
    BYTE parid;
    BYTE databits;
    BYTE stopbit;

    int timout;

    int numerr = 0;

    char buff[30];
    int pb = 0;
    unsigned char cr;

    numport = 1; /* <=====================================  Cambiar por el número de port que corresponda */
    baudios = 9600;
    databits = 8;
    parid = NOPARITY; /* 2-EVENPARITY 1-ODDPARITY 0-NOPARITY */
    stopbit = ONESTOPBIT; /* 2-TWOSTOPBITS 1-ONE5STOPBITS 0-ONESTOPBIT */
    timout = 3000;

    port_serie = abrir_port(numport);

    if (port_serie == INVALID_HANDLE_VALUE) /* Verifica si se pudo abrir port */
    {
        printf("No se puede abrir puerto.\n\n");
        printf("Presione <ESC> para salir.\n");

        return(1);
    }

    /* configura port y verifica si hubo error */
    if (configurar_port(port_serie,baudios,databits,parid,stopbit,timout) == 0)
    {
        printf("error configurando port\n\n");
        return(1);
    }

    f = fopen("log.txt", "w");

    do {
        if (leer_char(port_serie,&cr) == 0) {
            numerr++;
            printf("Err -> %d\n", numerr);
        } else {
            if (cr != '\n') {
                buff[pb++] = cr;
            } else {
                buff[pb] = '\0';
                pb = 0;
                printf("Rec -> %s\n", buff);
                fprintf(f, "Rec -> %s\n", buff);
            }
        }
    } while( numerr < 10 );

    fclose(f);

    /* -- cierra el port serie -- */
    cerrar_port(port_serie);

    return 0;
}


