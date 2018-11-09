#include <linux/cdev.h>   // cdev_add, cdev_init
#include <linux/uaccess.h>  // copy_to_user
#include <linux/module.h> // module_init, GPL
#include <linux/spi/spi.h> // spi_sync,

#define MAXLEN 32
#define MODULE_DEBUG 1   // Enable/Disable Debug messages

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
struct Myspi spi_devs[4];
const int spi_devs_len = 4;  // Max nbr of devices
static int spi_devs_cnt = 0; // Nbr devices present

/* Macro to handle Errors */
#define ERRGOTO(label, ...)                     \
  {                                             \
    printk (__VA_ARGS__);                       \
    goto label;                                 \
  } while(0)

/**********************************************************
 * CHARACTER DRIVER METHODS
 **********************************************************/

/*
 * Character Driver Module Init Method
 */
static int __init spi_drv_init(void)
{
  int err=0;

  printk("spi_drv driver initializing\n");

  /* Allocate major number and register fops*/
  printk("Allocating chrdev region\n");
  err = alloc_chrdev_region(&devno, 0, 256, "spi_drv");
  if(MAJOR(devno) <= 0)
    ERRGOTO(err_no_cleanup, "Failed to register chardev\n");
  printk(KERN_ALERT "Assigned major no: %i\n", MAJOR(devno));

  printk("Attempting to init cdev\n");
  cdev_init(&spi_drv_cdev, &spi_drv_fops);
  err = cdev_add(&spi_drv_cdev, devno, 256);
  if (err)
    ERRGOTO(err_cleanup_chrdev, "Failed to create class");
  printk("Cdev init done\n");

  /* Polulate sysfs entries */
  printk("Attempting to create class");
  spi_drv_class = class_create(THIS_MODULE, "spi_drv_class");
  if (IS_ERR(spi_drv_class))
    ERRGOTO(err_cleanup_cdev, "Failed to create class");
  printk("Class creation done\n");

  /* Register SPI Driver */
  /* THIS WILL INVOKE PROBE, IF DEVICE IS PRESENT!!! */
  printk("Attempting to register driver\n");
  err = spi_register_driver(&spi_drv_spi_driver);
  if(err)
    ERRGOTO(err_cleanup_class, "Failed SPI Registration\n");
  printk("Driver registration done\n");

  /* Success */
  printk("Init success!\n");
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
  printk("spi_drv driver starting Exit\n");

  printk("Unregister driver...\n");
  spi_unregister_driver(&spi_drv_spi_driver);

  printk("Destroy class...\n");
  class_destroy(spi_drv_class);

  printk("Delete cdev...\n");
  cdev_del(&spi_drv_cdev);

  printk("Unregister chrdev...\n");
  unregister_chrdev(MAJOR(devno), "spi_drv");

  printk("Exit done\n");
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

  /* Convert sting to int */
  sscanf(kbuf,"%i", &value);
  if(MODULE_DEBUG)
    printk("value %i\n", value);

  struct spi_transfer t[1];
  struct spi_message m;
  memset(t, 0, sizeof(t));
  spi_message_init(&m);
  m.spi = spi_devs[minor].spi;

  t[0].tx_buf = &value;
  t[0].rx_buf =  NULL;
  t[0].len = 1;
  spi_message_add_tail(&t[0], &m);

  spi_sync(m.spi, &m);

  /* Legacy file ptr f_pos. Used to support
   * random access but in char drv we dont!
   * Move it the length actually  written
   * for compability */
  *f_pos += len;

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
  s16 result=1234;

  minor = iminor(filep->f_inode);

  struct spi_transfer t[1];
  struct spi_message m;
  memset(t, 0, sizeof(t));
  spi_message_init(&m);
  m.spi = spi_devs[minor].spi;


  t[0].tx_buf = NULL;
  t[0].rx_buf =  &result;
  t[0].len = 1;
  spi_message_add_tail(&t[0], &m);

  spi_sync(m.spi, &m);

  if(MODULE_DEBUG)
    printk(KERN_ALERT "%s-%i read: %i\n",
           spi_devs[minor].spi->modalias, spi_devs[minor].channel, result);

  /* Convert integer to string limited to "count" size. Returns
   * length excluding NULL termination */
  len = snprintf(resultBuf, count, "%d\n", result);

  /* Append Length of NULL termination */
  len++;

  /* Copy data to user space */
  if(copy_to_user(ubuf, resultBuf, len))
    return -EFAULT;

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
  spi_devs[spi_devs_cnt].spi = sdev;
  spi_devs[spi_devs_cnt].channel = 0x00; // channel address
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
  /* Destroy devices created in probe() */
  for (int i = 0; i<spi_devs_cnt; ++i) {
    printk (KERN_ALERT "Removing spi device %i\n", i);
    device_destroy(spi_drv_class, MKDEV(MAJOR(devno), i));
  }

  return 0;
}

/*
 * spi Driver Struct
 * Holds function pointers to probe/release
 * methods and the name under which it is registered
 */
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
MODULE_AUTHOR("Adaption by: Lasse Herold Krarup. Original version: Peter Hoegh Mikkelsen <phm@ase.au.dk>");
MODULE_LICENSE("GPL");
