# Trabajo Practico Inicial de Sistemas Operativos y Redes II
## Device Drivers - Char Device

*******************************************************************************

				TRABAJO PRACTICO  0


ALUMNO: RAMOS BORIS

*******************************************************************************


## >_ En la primera parte del trabajo practico 0 se realiza un kernel module

1° Se compila y convierte el archivo-objeto (miModulo.c) en c
con el comendo #gcc miModulo.c -o miModulo

2° Para compilar el makefile (que es un archivo que compila cosas) 
primero ejecuto el comando #make clean (para borrar los archivos que se generan 
con el make) luego ejecuto el comando #make (que ejecuta el archivo makefile para 
crear los archivos del modulo).

Para poder visualizar si funciona el kernel module se busca el el log del kernel
utilizando el comando #dmesg

## >_ En la segunda parte del trabajo se pide elaborar un kernel modulo para un char device

* Aclaraciones de la funcionalidad de algunos metodos.

"Init module" es la función principal que se ejecuta al cargar un nuevo módulo
en el Kernel. Este método sirve para cargar un módulo del driver en el kernel.
En él se registra el dispositivo con Major y Minor. Además indica dónde
encontrar la función de inicialización del módulo. En caso de que todo salga
correctamente retorna 0. Desde la terminal se lo invoca con
$ sudo insmod nombreModulo.ko

"Cleanup module" sirve para quitar el módulo del Kernel y se libera a Major.
Además se indica dónde encontrar la función de “limpieza” del módulo. Y esta
es llamada antes de quitar el módulo. Desde la terminal se lo invoca con
$ sudo rmmod nombreModulo

"Device open" sirve para abrir el dispositivo (módulo) y poder utilizar las
funciones del mismo.

"Device release" sirve para cerrar el dispositivo como un archivo.

"Device_read" sirve para ver cómo se manejan los parámetros que les
pasa y con eso nosotros tenemos que leer de nuestro dispositivo y mostrarle
al usuario.

"Device_write" sirve para cuando queremos escribir sobre nuestro char
device y lo queremos guardar en algun lado para que cuando alguien nos
haga un read se puedan leer esos caracteres.

"encryptCaesar" Metodo encargado de realizar la encriptacion Cesar (+2 a la izquierda) del mensaje que se guarda.

** Los ultimos 4 metodos pertenecen al fileSystem.Esta segunda parte del trabajo, maneja diferentes memorias, el de usuario y el de kernel.


--------------<<< SECUENCIA DE COMANDOS UTILIZADOS DESDE EL TERMINAL >>>----------------

_Apertura

    *Limpia -> make clean
    *Crea -> make
    *Carga el modulo -> sudo insmod miModuloCharDevice.ko
    *Lista los modulos (checking) -> lsmod | grep miModuloCharDevice
    *Ver el log del kernel -> dmesg

>_Observar el major (N°) asignado al device y crearlo con la sig.
instruccion.

    *Crear charDevice, con xxx = major -> sudo mknod /dev/UNGS c xxx 0

>_El device necesita los permisos necesarios para realizar las 
operaciones.

    *Dar permisos -> sudo chmod 666 /dev/UNGS

>_Operaciones read/write.

    *Escritura, se escribe un mensaje -> echo "Hola Mundo" > /dev/UNGS
    *Lectura, se muestra el ultimo mensaje ingresado -> cat /dev/UNGS  

>_Cierre

    *Descargar/'Eliminar' el modulo -> sudo rmmod miModuloCharDevice.ko
    *Eliminar charDevice -> sudo rm /dev/UNGS
    

