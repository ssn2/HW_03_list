/* 
 * Ну типо поехали связанные списки ядра изучать!
 * main.c - собственно загрузка модуля, настройка 
 * на работу с sysfs
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



static struct kobject *kobj;
static struct attribute *attrs[] = {
	&dev_attr_push.attr,
	&dev_attr_pop.attr,
	&dev_attr_peek.attr,
	&dev_attr_size.attr,
	&dev_attr_is_empty.attr,
	&dev_attr_clear.attr,
	NULL,
};
    
static struct attribute_group attr_group = {
	.attrs = attrs,
};


static int __init listmod_init(void)
{
	stack_init();
	int ret;


	kobj = kobject_create_and_add("kernel_stack", kernel_kobj);

	ret = sysfs_create_group(kobj, &attr_group);

	pr_info("Init\n");

    return 0;
}

static void __exit listmod_exit(void)
{
	sysfs_remove_group(kobj, &attr_group);
	kobject_put(kobj);
	stack_clear();
	pr_info("Exit\n");
}

module_init(listmod_init);
module_exit(listmod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smolovoy Sergey");
MODULE_DESCRIPTION("My next module");
