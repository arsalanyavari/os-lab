#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>

#define DEVICE_NAME "iut_device"
#define INIT_BALANCE 2000000
#define ACCOUNT_COUNT 100
#define MAJOR_NUMBER 282
MODULE_LICENSE("GPL");

static int dev_open(struct inode*, struct file*);
static int dev_release(struct inode*, struct file*);
static ssize_t dev_read(struct file*, char*, size_t, loff_t*);
static ssize_t dev_write(struct file*, const char*, size_t, loff_t*);

static struct file_operations fops = {
   .open = dev_open,
   .read = dev_read,
   .write = dev_write,
   .release = dev_release,
};

static int major; // device major number. driver reacts to this major number.

struct bank {
    int acc[ACCOUNT_COUNT];
};

static struct bank bal;

int atoi(char* data)
{
    printk(KERN_ALERT "atoi working...\n");
    printk(KERN_ALERT "atoi input: %s\n", data);
    int sum, i;
    sum = 0;

    for (i=0; data[i] >= '0' && data[i] <= '9' ; i++)
    {
        sum *= 10;
        sum += (data[i] - '0');
    }

    printk(KERN_ALERT "atoi result: %d\n", sum);
    return sum;
}

int int_len(int data)
{
    int len = 0;

    if (!data)
        len++; // In case of data=0

    while(data)
    {
        len++;
        data/=10;
    }

    return len;
}

void decode_input(char* data, int* out)
{
    // out: from, to, amount (-1 if '-')
    int temp;

    // from
    if (data[2] == '-')
        temp = -1;

    else
        temp = atoi(&(data[2]));
    out[0] = temp;
    printk(KERN_ALERT "out[0] set to %d and its len is %d.\n", out[0],int_len(out[0]));

    // to
    if (data[2+int_len(out[0])+1] == '-')
        temp = -1;

    else
        temp = atoi(&(data[2+int_len(out[0])+1]));

    out[1] = temp;
    printk(KERN_ALERT "out[1] set to %d and its len is %d.\n", out[1],int_len(out[1]));

    // amount
    temp = atoi(&(data[2+int_len(out[0])+1+int_len(out[1])+1]));
    out[2] = temp;
    printk(KERN_ALERT "out[2] set to %d and its len is %d.\n", out[2],int_len(out[2]));
    printk(KERN_ALERT "decoded input: %d,%d,%d\n", out[0],out[1],out[2]);
}

static int __init iut_init(void)
{
    major = register_chrdev(MAJOR_NUMBER, DEVICE_NAME, &fops); // 0: auto major ||| name is displayed in /proc/devices ||| fops.

    if (major < 0)
    {
        printk(KERN_ALERT "Device001 load failed!\n");
        return major;
    }

    int i;

    for (i=0; i<ACCOUNT_COUNT; i++)
        bal.acc[i] = INIT_BALANCE;

    printk(KERN_INFO "Device001 module has been loaded: %d\n", major);
    return 0;
}

static void __exit iut_exit(void)
{
    unregister_chrdev(MAJOR_NUMBER, DEVICE_NAME);
    printk(KERN_INFO "Device001 module has been unloaded.\n");
}

static int dev_open(struct inode *inodep, struct file *filep)
{
   printk(KERN_INFO "Device001 opened.\n");
   return 0;
}

static ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset)
{
    char data[200];
    int bnc; // number of bytes that could not be copied
    bnc = copy_from_user(data, buffer, len);

    if (bnc)
    {
        printk(KERN_INFO "Sorry, Device001 couldn't read the input (bad format).\n");
        return -EFAULT;
    }

    int decoded_data[3];
    decode_input(data, decoded_data);
    printk(KERN_INFO "input data: %s\n", data);

    if (decoded_data[0]<0
         || decoded_data[0]>ACCOUNT_COUNT-1
         || decoded_data[1]<0
         || decoded_data[1]>ACCOUNT_COUNT-1)
    {
        printk(KERN_INFO "Sorry, Device001 couldn't read the input (index out of bounds).\n");
        printk(KERN_INFO "Input: %s\n", data);
        return -EFAULT;
    }

    // Variz
    if (data[0] == 'd')
    {
        printk(KERN_INFO "amount _v_: %d\n", decoded_data[2]);
        bal.acc[decoded_data[1]] += decoded_data[2];
    }

    // Bardasht
    else if (data[0] == 'w')
    {
        printk(KERN_INFO "amount _b_: %d\n", decoded_data[2]);

        if (bal.acc[decoded_data[0]] >= decoded_data[2])
            bal.acc[decoded_data[0]] -= decoded_data[2];
    }

    // Enteghaal
    else if (data[0] == 't')
    {
        printk(KERN_INFO "amount _e_: %d\n", decoded_data[2]);

        if (bal.acc[decoded_data[0]] >= decoded_data[2])
        {
            bal.acc[decoded_data[0]] -= decoded_data[2];
            bal.acc[decoded_data[1]] += decoded_data[2];
        }
    }

    // Bad trx type
    else
    {
        printk(KERN_INFO "Sorry, Device001 couldn't read the input (bad trx type).\n");
        printk(KERN_INFO "Input: %s\n", data);
        return -EFAULT;
    }
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
   printk(KERN_INFO "Device001 closed.\n");
   return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{
    printk("reading\n");
    int errors = 0;
    char message[ (ACCOUNT_COUNT+10) * (int_len(INIT_BALANCE)+1) ]; message[0] = '\0';

    int i;
    // 20 digit number!
    char str_buf[20];

    for (i=0; i<ACCOUNT_COUNT; i++)
    {
        sprintf(str_buf, "%d,", bal.acc[i]);
        strncat(message, str_buf, strlen(str_buf));
    }
    int message_len = strlen(message);
    errors = copy_to_user(buffer, message, message_len);
    return errors == 0 ? message_len : -EFAULT;
}

module_init(iut_init);
module_exit(iut_exit);
