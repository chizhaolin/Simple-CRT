#ifndef _my_crt_h
#define _my_crt_h

typedef int FILE;

#define EOF     (-1)

#ifndef NULL
#define NULL 0
#endif

#define stdin  ((FILE*)GetStdHandle(STD_INPUT_HANDLE))
#define stdout ((FILE*)GetStdHandle(STD_OUTPUT_HANDLE))
#define stderr ((FILE*)GetStdHandle(STD_ERROR_HANDLE))

extern char* _strtok(char* string, const char* control);
extern int strcmp(const char* src, const char* dst);
extern char* strcpy(char* dst, const char* src);
extern char* strcat (char * dst, const char * src);
extern unsigned int strlen (const char * str);

extern void free(void * _Memory);
extern void * malloc(unsigned int _Size);
extern unsigned int getFreeHeapSize();
extern int heap_init();

extern FILE* fopen(const char* filename, const char* mode);
extern int fread(void* buffer, int size, int count, FILE* stream);
extern int fwrite(const void* buffer, int size, int count , FILE* stream);
extern int fclose(FILE* fp);

#endif