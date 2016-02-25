# Simple-CRT
A simple implementation of the CRT based on win32

It's implemented to understand the CRT deeply, currently it supports the functions:
  1. One entry for the CRT, which contains the initialization of the heap and IO
  2. Support malloc/free for heap allocation/de-allocation
  3. Support IO, only printf() and only support output string with format "%s"
  4. Support some functions for string, such as strcpy(), strtok(), strcat(), strlen()

The library mycrt.lib will be generated followed the command:
  compile: >cl /c /DWIN32 /GS- my_crt.c malloc.c stdio.c string.c
  link:    >lib my_crt.obj malloc.obj stdio.obj string.obj /OUT:mycrt.lib
  
Test to utilising the mycrt.lib:
  1. first include the header file "my_crt.h" in the test file
  2. write your own main function in the test file
  3. compile: >cl /c /DWIN32 /GS- test.c
  4. link:    >link test.obj mycrt.lib kernel32.lib /NODEFAULTLIB /entry:my_crt_entry
  5. run the generated test.ext, you will realize that the size of generated text.exe is very small.

Reference:
  程序员的自我修养--俞甲子，石凡，潘爱民
  