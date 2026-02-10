/* 
Ну типо поехали связанные списки ядра изучать!
*/

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/kobject.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include "../lib/inc/stack.h"
#include "../inc/kernel_stack.h"


/*extern ssize_t push_show(struct device *dev, struct device_attribute *attr, char *buf);
extern ssize_t push_store(struct device *dev, struct device_attribute *attr, 
                          const char *buf, size_t count);*/

static struct kobject *kobj;

DEVICE_ATTR_RW(push);


static int __init listmod_init(void)
{
    pr_info("Init\n");
//    stack_pop();
//    struct device *dev;
    int ret;


    kobj = kobject_create_and_add("kernel_stack", kernel_kobj);
    ret = sysfs_create_file(kobj, &dev_attr_push.attr);

    return 0;
}

static void __exit listmod_exit(void)
{
    kobject_put(kobj);
    pr_info("Exit\n");
}

module_init(listmod_init);
module_exit(listmod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smolovoy Sergey");
MODULE_DESCRIPTION("My next module");
