# serie_win32

HANDLE abrir_port(unsigned char port);

void cerrar_port(HANDLE);

int configurar_port(HANDLE ports,
                    DWORD, /* baud rate */
                    BYTE , /* bits dato */
                    BYTE , /* paridad: 2-EVENPARITY 1-ODDPARITY 0-NOPARITY */
                    BYTE , /* bits stop: 2-TWOSTOPBITS 1-ONE5STOPBITS 0-ONESTOPBIT */
                    unsigned int); /* time out - en ms */
                    
int escribir_char(HANDLE,unsigned char);

int leer_char(HANDLE ports, unsigned char*);

int escribir_chars(HANDLE ports,unsigned char*, unsigned char);

int leer_chars(HANDLE ports, unsigned char*, unsigned char);

int escribir_string(HANDLE ports,unsigned char*);

int leer_string(HANDLE ports, unsigned char*);
