/* 
 * Ну типо поехали связанные списки ядра изучать!
 * main.c - собственно загрузка модуля, настройка 
 * на работу с sysfs
*/

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <stack.h>
#include <kernel_stack.h>


static int __init listmod_init(void)
{
	stack_init();
	mod_sysfs_init();
	pr_info("Init\n");

	return 0;
}

static void __exit listmod_exit(void)
{
	mod_sysfs_close();
	stack_clear();
	pr_info("Exit\n");
}

module_init(listmod_init);
module_exit(listmod_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Smolovoy Sergey");
MODULE_DESCRIPTION("My next module");
