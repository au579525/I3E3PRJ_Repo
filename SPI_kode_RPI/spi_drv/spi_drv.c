#include <linux/cdev.h>   // cdev_add, cdev_init
#include <linux/uaccess.h>  // copy_to_user
#include <linux/module.h> // module_init, GPL
#include <linux/spi/spi.h> // spi_sync,
#include <linux/gpio.h>
#include <linux/wait.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>

#define GPIO_NUM 25
#define IRQF_TRIGGER_RISING 0x00000001
#define MAXLEN 32
#define MODULE_DEBUG 1   // Enable/Disable Debug messages

static DECLARE_WAIT_QUEUE_HEAD(wq);
int IRQ_NUM;
int spi_req_flag;

static irqreturn_t spi_req_handler(int irq, void *dev_id);

struct mutex Mut;

/* Char Driver Globals */
static struct spi_driver spi_drv_spi_driver;
struct file_operations spi_drv_fops;
static struct class *spi_drv_class;
static dev_t devno;
static struct cdev spi_drv_cdev;

/* Definition of SPI devices */
struct Myspi {
  struct spi_device *spi; // Pointer to SPI device
  int channel;            // channel, ex. adc ch 0
};
/* Array of SPI devices */
/* Minor used to index array */
struct Myspi spi_devs; //laves til array hvis flere devices
const int spi_devs_len = 0;  // Max nbr of devices
static int spi_devs_cnt = 0; // Nbr devices present = kun en PSoC

/* Macro to handle Errors */
#define ERRGOTO(label, ...)                     \
  {                                             \
    printk (__VA_ARGS__);                       \
    goto label;                                 \
  } while(0)

/**********************************************************
 * CHARACTER DRIVER METHODS
 **********************************************************/
int PSoC_spi_read_8(struct Myspi *spi_devs,u8 * data){
struct spi_transfer t[1]; //Only one spi_transfer
struct spi_message m;

memset(t,0,sizeof(t));  //Init memory
spi_message_init(&m);   //SPI message init
m.spi = spi_devs->spi;            // use current SPI I/for

t[0].tx_buf = NULL;     //Transmit NO data;
t[0].rx_buf = data;     //Recieve data;
t[0].len = 1;           //Transfer 1 byte
spi_message_add_tail(&t[0],&m);   //add Msg to queue

int err = spi_sync(m.spi, &m);  //Transmit data;
return err;
}

int PSoC_spi_write_8(struct Myspi *spi_devs, u8 data){
struct spi_transfer t[1]; //Only one spi_transfer
struct spi_message m;

memset(t,0,sizeof(t));  //Init memory
spi_message_init(&m);   //SPI message init
m.spi = spi_devs->spi;            // use current SPI I/for

t[0].tx_buf = &data;     //Transmit data;
t[0].rx_buf = NULL;     //Recieve NO;
t[0].len = 1;           //Transfer 1 byte
spi_message_add_tail(&t[0],&m);   //add Msg to queue

int err = spi_sync(m.spi, &m);  //Transmit data;
return err;
}

int spi_req_init(void){
  int err = 0;
  err = gpio_request(GPIO_NUM,"GPIO 25 request");
  if (err < 0){
    goto err_exit;
  }

  err = gpio_direction_input(GPIO_NUM);
  if (err < 0){
    goto err_GPIO;
  }

  IRQ_NUM = gpio_to_irq(GPIO_NUM);

  err = request_irq(IRQ_NUM, spi_req_handler,
  IRQF_TRIGGER_RISING, "spi_req_irq", NULL);
  if (err < 0){
    goto err_free_buff;
  }

  err_free_buff:

  err_GPIO:
    gpio_free(GPIO_NUM);
  err_exit:
    //Do Nothing

  return err;
}

/*
 * Character Driver Module Init Method
 */
static int __init spi_drv_init(void)
{
  mutex_init(&Mut);
  int err=0;

  spi_req_init();

  printk("spi_drv driver initializing\n");

  /* Allocate major number and register fops*/
  err = alloc_chrdev_region(&devno, 0, 255, "spi_drv driver");
  if(MAJOR(devno) <= 0)
    ERRGOTO(err_no_cleanup, "Failed to register chardev\n");
  printk(KERN_ALERT "Assigned major no: %i\n", MAJOR(devno));

  cdev_init(&spi_drv_cdev, &spi_drv_fops);
  err = cdev_add(&spi_drv_cdev, devno, 255);
  if (err)
    ERRGOTO(err_cleanup_chrdev, "Failed to create class");

  /* Polulate sysfs entries */
  spi_drv_class = class_create(THIS_MODULE, "spi_drv_class");
  if (IS_ERR(spi_drv_class))
    ERRGOTO(err_cleanup_cdev, "Failed to create class");

  /* Register SPI Driver */
  /* THIS WILL INVOKE PROBE, IF DEVICE IS PRESENT!!! */
  err = spi_register_driver(&spi_drv_spi_driver);
  if(err)
    ERRGOTO(err_cleanup_class, "Failed SPI Registration\n");

  /* Success */
  return 0;

  /* Errors during Initialization */
 err_cleanup_class:
  class_destroy(spi_drv_class);

 err_cleanup_cdev:
  cdev_del(&spi_drv_cdev);

 err_cleanup_chrdev:
  unregister_chrdev(MAJOR(devno), "spi_drv");

 err_no_cleanup:
  return err;
}

/*
 * Character Driver Module Exit Method
 */
static void __exit spi_drv_exit(void)
{
  printk("spi_drv driver Exit\n");

  spi_unregister_driver(&spi_drv_spi_driver);
  class_destroy(spi_drv_class);
  cdev_del(&spi_drv_cdev);
  unregister_chrdev(MAJOR(devno), "spi_drv");
}

/*
 * Character Driver Write File Operations Method
 */
ssize_t spi_drv_write(struct file *filep, const char __user *ubuf,
                      size_t count, loff_t *f_pos)
{
  int minor, len, value;
  char kbuf[MAXLEN];
  minor = iminor(filep->f_inode);

  printk(KERN_ALERT "Writing to spi_drv [Minor] %i \n", minor);

  /* Limit copy length to MAXLEN allocated andCopy from user */
  len = count < MAXLEN ? count : MAXLEN;
  if(copy_from_user(kbuf, ubuf, len))
    return -EFAULT;

  /* Pad null termination to string */
  kbuf[len] = '\0';

  if(MODULE_DEBUG)
    printk("string from user: %s\n", kbuf);

  /* Convert string to int */
  sscanf(kbuf,"%i", &value);
  if(MODULE_DEBUG)
    printk("value %i\n", value);

  /*
    Do something with value ....

  */
  mutex_lock(&Mut);
  struct spi_transfer t[1]; //Only one spi_transfer
  struct spi_message m;

  memset(t,0,sizeof(t));  //Init memory
  spi_message_init(&m);   //SPI message init
  m.spi = spi_devs.spi;  // use current SPI I/for

  t[0].tx_buf = &value;     //Transmit data;
  t[0].rx_buf = NULL;     //Recieve NO;
  t[0].len = 1;           //Transfer 1 byte
  spi_message_add_tail(&t[0],&m);   //add Msg to queue


  spi_sync(m.spi, &m);  //Transmit data;

  /* Legacy file ptr f_pos. Used to support
   * random access but in char drv we dont!
   * Move it the length actually  written
   * for compability */
  *f_pos += len;
  mutex_unlock(&Mut);
  /* return length actually written */
  return len;
}

/*
 * Character Driver Read File Operations Method
 */
ssize_t spi_drv_read(struct file *filep, char __user *ubuf,
                     size_t count, loff_t *f_pos)
{
  int minor, len;
  char resultBuf[MAXLEN];
  //s16 result=1234;
  u8 data;

  wait_event_interruptible(wq,spi_req_flag == 1);
  mutex_lock(&Mut);
  spi_req_flag = 0;
  minor = iminor(filep->f_inode);
  /*
    Provide a result to write to user space
  */
  PSoC_spi_read_8(&spi_devs,&data);


  if(MODULE_DEBUG)
    printk(KERN_ALERT "%s-%i read: %i\n",
           spi_devs.spi->modalias, spi_devs.channel, data);

  /* Convert integer to string limited to "count" size. Returns
   * length excluding NULL termination */
  len = snprintf(resultBuf, count, "%d\n", data);

  /* Append Length of NULL termination */
  len++;

  /* Copy data to user space */
  if(copy_to_user(ubuf, resultBuf, len)){
        return -EFAULT;
  }

    mutex_unlock(&Mut);
  /* Move fileptr */
  *f_pos += len;

  return len;
}

/*
 * Character Driver File Operations Structure
 */
struct file_operations spi_drv_fops =
  {
    .owner   = THIS_MODULE,
    .write   = spi_drv_write,
    .read    = spi_drv_read,
  };

/**********************************************************
 * LINUX DEVICE MODEL METHODS (spi)
 **********************************************************/

/*
 * spi_drv Probe
 * Called when a device with the name "spi_drv" is
 * registered.
 */
static int spi_drv_probe(struct spi_device *sdev)
{
  int err = 0;
  struct device *spi_drv_device;

  printk(KERN_DEBUG "New SPI device: %s using chip select: %i\n",
         sdev->modalias, sdev->chip_select);

  /* Check we are not creating more
     devices than we have space for */
  if (spi_devs_cnt > spi_devs_len) {
    printk(KERN_ERR "Too many SPI devices for driver\n");
    return -ENODEV;
  }

  /* Configure bits_per_word, always 8-bit for RPI!!! */
  sdev->bits_per_word = 8;
  spi_setup(sdev);

  /* Create devices, populate sysfs and
     active udev to create devices in /dev */

  /* We map spi_devs index to minor number here */
  spi_drv_device = device_create(spi_drv_class, NULL,
                                 MKDEV(MAJOR(devno), spi_devs_cnt),
                                 NULL, "spi_drv%d", spi_devs_cnt);

  if (IS_ERR(spi_drv_device))
    printk(KERN_ALERT "FAILED TO CREATE DEVICE\n");
  else
    printk(KERN_ALERT "Using spi_devs%i on major:%i, minor:%i\n",
           spi_devs_cnt, MAJOR(devno), spi_devs_cnt);

  /* Update local array of SPI devices */
  spi_devs.spi = sdev;
  spi_devs.channel = 0x00; // channel address
  ++spi_devs_cnt;

  return err;
}

/*
 * spi_drv Remove
 * Called when the device is removed
 * Can deallocate data if needed
 */
static int spi_drv_remove(struct spi_device *sdev)
{
  int its_minor = 0;

  printk (KERN_ALERT "Removing spi device\n");

  /* Destroy devices created in probe() */
  device_destroy(spi_drv_class, MKDEV(MAJOR(devno), its_minor));

  return 0;
}

/*
 * spi Driver Struct
 * Holds function pointers to probe/release
 * methods and the name under which it is registered
 */

 static irqreturn_t spi_req_handler(int irq,void *dev_id)
 {
   spi_req_flag = 1;
   wake_up_interruptible(&wq);
   return IRQ_HANDLED;
 }

static const struct of_device_id of_spi_drv_spi_device_match[] = {
  { .compatible = "ase, spi_drv", }, {},
};

static struct spi_driver spi_drv_spi_driver = {
  .probe      = spi_drv_probe,
  .remove           = spi_drv_remove,
  .driver     = {
    .name   = "spi_drv",
    .bus    = &spi_bus_type,
    .of_match_table = of_spi_drv_spi_device_match,
    .owner  = THIS_MODULE,
  },
};

/**********************************************************
 * GENERIC LINUX DEVICE DRIVER STUFF
 **********************************************************/

/*
 * Assignment of module init/exit methods
 */
module_init(spi_drv_init);
module_exit(spi_drv_exit);

/*
 * Assignment of author and license
 */
MODULE_AUTHOR("Peter Hoegh Mikkelsen <phm@ase.au.dk>");
MODULE_LICENSE("GPL");
