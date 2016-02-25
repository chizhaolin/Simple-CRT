#include "my_crt.h"

char* _strtok(char* string, const char* control)
{
    static char* sRest = NULL;
    unsigned char map[32];
    const char *ctr;
    char *str;
    int i;

    for (i = 0; i < sizeof(map); i++)
        map[i] = 0;

    ctr = control;
    while(*ctr) {
        map[*ctr>>3] |= (1 << (*ctr&7));
        ctr++;
    }

    if (string == NULL)
        str = sRest;
    else
        str = string;

    while (*str && (map[*str>>3] & (1<<(*str&7)))) {
        str++;
    }

    string = str;

    while(*str) {
        if (map[*str>>3] & (1<<(*str&7))) {
            *str++ = '\0';
            break;
        }
        str++;
    }

    sRest = str;

    if (string == str)
        return NULL;
    else
        return string;
}

int strcmp(const char* src, const char* dst)
{
    int ret = 0 ;

    while( ! (ret = *(unsigned char *)src - *(unsigned char *)dst) && *dst)
        ++src, ++dst;

    if ( ret < 0 )
        ret = -1 ;
    else if ( ret > 0 )
        ret = 1 ;

    return( ret );
}

char* strcpy(char* dst, const char* src)
{
    char * cp = dst;

    while( *cp++ = *src++ )
            ;               /* Copy src over dst */

    return( dst );
}

char* strcat (char * dst, const char * src)
{
    char * cp = dst;

    while( *cp )
            cp++;                   /* find end of dst */

    while( *cp++ = *src++ ) ;       /* Copy src to end of dst */

    return( dst );                  /* return dst */
}

unsigned int strlen (const char * str)
{
    const char *eos = str;

    while( *eos++ ) ;

    return( eos - str - 1 );
}
