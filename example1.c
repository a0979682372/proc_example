#include <linux/module.h>    /* Needed by all modules */
#include <linux/kernel.h>    /* Needed for KERN_INFO */
#include <linux/init.h>      /* Needed for the macros */
#include <linux/moduleparam.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/uaccess.h>

#define BUFSIZE  100
static struct proc_dir_entry *ent;
static char mess[100];


static ssize_t mywrite(struct file *file, const char __user *ubuf,size_t count, loff_t *ppos) 
{
	printk( KERN_DEBUG "write handler\n");
    int num,c;
	char buf[BUFSIZE];
    memset(buf,0,100);
	if(*ppos > 0 || count > BUFSIZE)
		return -EFAULT;
    memset(mess,0,100);
	if(copy_from_user(mess, ubuf, count))
		return -EFAULT;
    
	//num = sscanf(buf,"%s",mess);
    printk( KERN_INFO "mess: %s\n",mess);    
	c = strlen(mess);
	*ppos = c;
    printk( KERN_INFO "c: %d\n",c);
	return c;
}

static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
	printk( KERN_DEBUG "read handler\n");
    char buf[BUFSIZE];
	int len=0;
	if(*ppos > 0 || count < BUFSIZE)
		return 0;
	//len += sprintf(buf,"irq = %d\n",irq);
    memset(buf,0,100);
    len += sprintf(buf,"%s",mess);
	if(copy_to_user(ubuf,buf,strlen(buf)))
		return -EFAULT;
    //len = strlen(mess);
    printk( KERN_INFO "len: %d\n",len);
	*ppos = len;
	return len;
	
}

static struct file_operations myops = 
{
	.owner = THIS_MODULE,
	.read = myread,
	.write = mywrite,
};

static int __init example1_init(void)
{
    printk(KERN_INFO "Hello, this is a kernel module learning example.\n");
    ent=proc_create("mydev",0666,NULL,&myops);
    return 0;
}

static void __exit example1_exit(void)
{
    printk(KERN_INFO "Goodbye!\n");
    proc_remove(ent);
}

module_init(example1_init);
module_exit(example1_exit);