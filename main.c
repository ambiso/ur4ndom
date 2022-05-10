#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

static int ur4ndom_open(struct inode* inode, struct file* file);

static int ur4ndom_release(struct inode* inode, struct file* file);

static long ur4ndom_ioctl(struct file* file, unsigned int cmd, unsigned long arg);

static ssize_t ur4ndom_read(struct file* file, char __user* buf, size_t count, loff_t* offset);

static ssize_t ur4ndom_write(struct file* file, const char __user* buf, size_t count, loff_t* offset);

static const struct file_operations ur4ndom_fops = { 
    .owner = THIS_MODULE,
    .open = ur4ndom_open,
    .release = ur4ndom_release,
    .unlocked_ioctl = ur4ndom_ioctl,
    .read = ur4ndom_read,
    .write = ur4ndom_write 
};

struct mychar_device_data {
  struct cdev cdev;
};

static int dev_major = 0;
static struct class* ur4ndom_class = NULL;
static struct mychar_device_data ur4ndom_data;

static int ur4ndom_uevent(struct device* dev, struct kobj_uevent_env* env) {
  add_uevent_var(env, "DEVMODE=%#o", 0666);
  return 0;
}

static int __init ur4ndom_init(void) {
  int err;
  dev_t dev;

  err = alloc_chrdev_region(&dev, 0, 1, "ur4ndom");

  dev_major = MAJOR(dev);

  ur4ndom_class = class_create(THIS_MODULE, "ur4ndom");
  ur4ndom_class->dev_uevent = ur4ndom_uevent;

  cdev_init(&ur4ndom_data.cdev, &ur4ndom_fops);
  ur4ndom_data.cdev.owner = THIS_MODULE;

  cdev_add(&ur4ndom_data.cdev, MKDEV(dev_major, 0), 1);

  device_create(ur4ndom_class, NULL, MKDEV(dev_major, 0), NULL, "ur4ndom");

  return 0;
}

static void __exit ur4ndom_exit(void) {

  device_destroy(ur4ndom_class, MKDEV(dev_major, 0));

  class_unregister(ur4ndom_class);
  class_destroy(ur4ndom_class);

  unregister_chrdev_region(MKDEV(dev_major, 0), MINORMASK);
}

static int ur4ndom_open(struct inode* inode, struct file* file) {
  return 0;
}

static int ur4ndom_release(struct inode* inode, struct file* file) {
  return 0;
}

static long ur4ndom_ioctl(struct file* file, unsigned int cmd, unsigned long arg) {
  return 0;
}

static ssize_t ur4ndom_read(struct file* file, char __user* buf, size_t count, loff_t* offset) {
  uint8_t* data = kmalloc(count, GFP_KERNEL);
  uint64_t i;

  for (i = 0; i < count; ++i) {
    data[i] = ((i & 1) == 0) ? '4' : '\n';
  }

  if (copy_to_user(buf, data, count)) {
    kfree(data);
    return -EFAULT;
  }

  kfree(data);
  return count;
}

static ssize_t ur4ndom_write(struct file* file, const char __user* buf, size_t count, loff_t* offset) {
  return count;
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nobody");

module_init(ur4ndom_init);
module_exit(ur4ndom_exit);