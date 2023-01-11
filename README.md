# ShellBehaviour

Este programa simula una shell, con comandos internos y externos. Los comandos internos incluyen:
- `cd`: para cambiar de directorio
- `echo`: para imprimir en pantalla
- `cp`: para copiar archivos
- `move`: para mover archivos
- `exit`: para salir del programa

Los comandos externos se ejecutan utilizando `execvp` y `fork`, y se pueden ejecutar tanto en primer como en segundo plano utilizando `&`.

## Compilación

Para compilar el programa, utilice el archivo Makefile incluido:

$ make

## Ejecución

Una vez compilado, puede ejecutar el programa de la siguiente manera:

$ ./shell

## Uso

Una vez en el programa, puede ingresar comandos internos y externos para su ejecución. 
Ejemplos de uso:
$ cd /home/user/
$ echo "Hola mundo"
$ cp archivo1 archivo2
$ move archivo3 archivo4

Para salir del programa puede usar el comando interno exit.