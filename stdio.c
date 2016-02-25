#include <windows.h>
#include "my_crt.h"

FILE* fopen(const char* filename, const char* mode)
{
    HANDLE hFile = 0;
    int access = 0;
    int creation = 0;

    if (strcmp(mode, "w") == 0) {
        access |= GENERIC_WRITE;
        creation += CREATE_ALWAYS;
    }
    else if (strcmp(mode, "w+") == 0) {
        access |= GENERIC_WRITE | GENERIC_READ;
        creation += CREATE_ALWAYS;
    }
    else if (strcmp(mode, "r") == 0) {
        access |= GENERIC_READ;
        creation += OPEN_EXISTING;
    }

    hFile = CreateFileA(filename, access, 0, 0, creation, 0, 0);
    if (hFile == INVALID_HANDLE_VALUE)
        return NULL;

    return (FILE*)hFile;
}

int fread(void* buffer, int size, int count, FILE* stream)
{
    int read = 0;
    if (!ReadFile((HANDLE)stream, buffer, size * count, &read, 0))
        return 0;
    return read;
}

int fwrite(const void* buffer, int size, int count , FILE* stream)
{
    int written = 0;
    if (!WriteFile((HANDLE)stream, buffer, size*count, &written, 0))
        return 0;
    return written;
}

int fclose(FILE* fp)
{
    return CloseHandle((HANDLE)fp);
}

int fputc(int c, FILE*stream)
{
    if (fwrite(&c, 1, 1, stream) != 1)
        return EOF;
    return c;
}

int fputs(const char* str, FILE* stream)
{
    int len = strlen(str);
    if (fwrite(str, 1, len, stream) != len)
        return EOF;
    return len;
}

int vfprintf(FILE* stream, const char* format, va_list arglist)
{
    int translating = 0;
    int ret = 0;
    const char* p = format;

    while (*p) {
        switch(*p) {
            case '%':
                if (!translating)
                    translating = 1;
                else {
                    if (fputc('%', stream) < 0)
                        return EOF;
                    ret++;
                    translating = 0;
                }
                break;
            case 's':
                if (translating) {
                    const char* str;
                    str = va_arg(arglist, const char*);
                    if (fputs(str, stream) < 0)
                        return EOF;
                    ret += strlen(str);
                    translating = 0;
                }
                else {
                    if (fputc(*p, stream) < 0)
                        return EOF;
                    ret++;
                }
                break;
            default:
                if (translating)
                    translating = 0;
                if (fputc(*p, stream) < 0)
                    return EOF;
                ret++;
                break;
        }
        p++;
    }

    return ret;
}

int printf(const char* format, ...)
{
    va_list arglist;
    va_start(arglist, format);
    return vfprintf(stdout, format, arglist);
}