# Trabajo Practico Inicial de Sistemas Operativos y Redes II
## Device Drivers - Char Device

*******************************************************************************

				TRABAJO PRACTICO  0


ALUMNO: RAMOS BORIS

*******************************************************************************


En la primera parte del trabajo practico 0 se realiza un kernel module

1° Se compila y convierte el archivo-objeto (miModulo.c) en c
con el comendo #gcc miModulo.c -o miModulo

2° Para compilar el makefile (que es un archivo que compila cosas) 
primero ejecuto el comando #make clean (para borrar los archivos que se generan 
con el make) luego ejecuto el comando #make (que ejecuta el archivo makefile para 
crear los archivos del modulo).

Para poder visualizar si funciona el kernel module se busca el el log del kernel
utilizando el comando #dmesg
