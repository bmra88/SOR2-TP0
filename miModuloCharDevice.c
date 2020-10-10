// Bibliotecas utilizadas.
#include <linux/module.h> // try_module_get, cleanup_module, ...
#include <linux/kernel.h> // printk(), ...
#include <linux/fs.h> // register_filesystem, ...
#include <asm/uaccess.h> // put_user, get_user, ...

// Declaracion de metodos.
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
void encryptCaesar(char *msg, char *dest); //--

// Constantes.
#define SUCCESS 0
#define DEVICE_NAME "UNGS"
#define BUF_LEN 80
#define LENGHT_ALPHABET 26 //--
#define INIT_LOWERCASE_ALPHABET 65 //--
#define INIT_UPPERCASE_ALPHABET 97 //--

// Global variables.
static int Major;
static int Device_Open = 0;
static char msg[BUF_LEN]; // mensaje que dara el dispositivo cuando se lo solicite
static char *msg_Ptr;
static char *msg_Caesar; //--
const char *lowercase = "abcdefghijklmnopqrstuvwxyz"; //--
const char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //--

// Definimos las operaciones sobre el file.
static struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

// Se llama cuando el modulo es cargado. 
int init_module(void)
{   
    //Registra el char device con el nombre y operaciones que le asociamos 
    //y genera un Major number para el device UNGS que se creara e imprime 
    //esta informacion en el log del kernel para la creacion del mismo. 
    Major = register_chrdev(0, DEVICE_NAME, &fops);

    if (Major < 0) {
        printk(KERN_ALERT "Registrando char device con %d\n", Major);
        return Major;
    }

    printk(KERN_INFO "Tengo major number %d. Hablarle al driver,", Major);
    printk(KERN_INFO "crear un dev_file con \n");
    printk(KERN_INFO "sudo rm /dev/%s\n", DEVICE_NAME);
    printk(KERN_INFO "sudo mknod /dev/%s c %d 0\n", DEVICE_NAME, Major);
    printk(KERN_INFO "sudo chmod 666 /dev/%s\n", DEVICE_NAME);
    printk(KERN_INFO "Probar varios minor numbers.\n");
    printk(KERN_INFO "Probar cat y echo al device file.\n");
    printk(KERN_INFO "Eliminar el /dev/%s y bajar el modulo al terminar.\n", DEVICE_NAME);
    
    printk(KERN_INFO "CharDevice: Driver registrado.\n");
    return 0;
}

// Se lo llama cuando el modulo es descargado.
void cleanup_module(void)
{
    //Desregistra el char device e informa de esto imprimiendo 
    //en el log del kernel.
    unregister_chrdev(Major, DEVICE_NAME);
    printk(KERN_INFO "CharDevice: Driver desregistrado.\n");
}

static int device_open(struct inode *inode, struct file *file)
{    
    //Verifica si el device ya esta abierto, si no lo esta, lo informa 
    //escribiendo en el log del kernel que el char device se ha abierto.
    if (Device_Open)
        return -EBUSY;
    Device_Open++;
    printk(KERN_ALERT "------------ New apertura ------------.\n");
    printk(KERN_INFO "Se ABRIO el charDevice!!!");

    // inicializa el mensaje
    msg_Ptr = msg;

    // asigna permiso
    try_module_get(THIS_MODULE);
    
    return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{
    Device_Open--;

    // informa por el log del kernel que el char device se cerro.
    printk(KERN_INFO "Se CERRO el charDevice!!!");
    
    // quita permiso
    module_put(THIS_MODULE);

    return 0;
}

// Instruccion disparadora : cat /dev/UNGS 
static ssize_t device_read(struct file *filp, char *buffer, size_t length, loff_t * offset)
{
    // representa la cant. bytes que estan en el buffer 
    int bytes_read = 0;
    
    // si el mensaje leido es vacio retorna 0
    if (*msg_Ptr == 0)
        return 0;
    
    // copiamos los datos en el buffer
    while (length && *msg_Ptr) 
    {
        // copia los datos del kernel a datos de usuario. El buffer es del usuario.
        // put_user(valor, destino).
        put_user(*(msg_Ptr++), buffer++);
        // length, es el largo del mensaje.
        length--;
        bytes_read++;
    }

    printk(KERN_INFO "Se LEE el charDevice!!!");
    printk(KERN_INFO "Cant. byte read %d .\n", bytes_read);

    // retorna la cant. bytes que estan en el buffer
    return bytes_read;
}

// Instruccion disparadora : echo ">_hola mundo" > /dev/UNGS 
static ssize_t device_write(struct file *filp, const char *buffer, size_t length, loff_t * off)
{
    int i=0;
    for(i ; i<length&&i<BUF_LEN ; i++)
    {
        // copia de dato de usuario a kernel. get_user(kenel,usuario).
        get_user(msg[i], buffer+i);
    }

    msg_Caesar = msg; //--
  
    // Se llama al metodo de encriptacion -----

    encryptCaesar(msg, msg_Caesar); //--
		
    msg_Ptr = msg_Caesar; //--

    printk(KERN_INFO "Se ESCRIBE el charDevice encriptado!!!");
    	
    return i;
}


// Metodo de encriptacion de msjs. ----------------
void encryptCaesar(char *msg, char *msgCaesar) {
  int i = 0;
  while (msg[i]) {
    char actualChar = msg[i];
    int origPos = (int) actualChar; 
    if (!isalpha(actualChar)) {
      msgCaesar[i] = actualChar;
      i++;
      continue; 
    }
    if (isupper(actualChar)) {
      msgCaesar[i] = uppercase[(origPos - INIT_UPPERCASE_ALPHABET + 2) % LENGHT_ALPHABET];
    } else {
      msgCaesar[i] = lowercase[(origPos - INIT_UPPERCASE_ALPHABET + 2) % LENGHT_ALPHABET];
    }
    i++;
  }
}



MODULE_LICENSE("GPL");
MODULE_AUTHOR("Boris Ramos");
MODULE_DESCRIPTION("TP0-Sor2");