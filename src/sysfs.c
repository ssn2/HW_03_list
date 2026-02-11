/*
 * sysfs.c
 * Работа с sysfs
 */

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/sysfs.h>

#include "../inc/kernel_stack.h"
#include "../lib/inc/stack.h"

/* Всё для работы через push */
//struct device_attribute dev_attr_push;
DEVICE_ATTR_WO(push);
ssize_t push_store(struct device *dev, struct device_attribute *attr, 
                    const char *buf, size_t count){

	/* Времянка, которая потом будет передана для добавления в стек */
	int _value;
	int ret;

	if (kstrtoint(buf, 10, &_value))
        	return -EINVAL;

	pr_info("Got new value: %d\n", _value);
	ret = stack_push(_value);
	if (ret != STACK_OK){ 
		printk(KERN_ERR "Ошибка добавления элемента %d, error: %d\n", 
				_value, ret);
	}
////// Тут надо возвращать количество обработанный байт, а не 0 как обычно!!!!
	return count;
}

/* Всё для работы через pop */
DEVICE_ATTR_RO(pop);
//struct device_attribute dev_attr_pop;
ssize_t pop_show(struct device *dev, 
		struct device_attribute *attr, char *buf){
	return 0;
}

/* Всё для работы через peek */
//struct device_attribute dev_attr_peek;
DEVICE_ATTR_RO(peek);
ssize_t peek_show(struct device *dev,
		struct device_attribute *attr, char *buf){
	return 0;
}

/* Всё для работы через size */
//struct device_attribute dev_attr_size;
DEVICE_ATTR_RO(size);
ssize_t size_show(struct device *dev,
		struct device_attribute *attr, char *buf){
	return sprintf(buf, "%d\n", stack_size());
}

/* Всё для работы через is_empty */
//struct device_attribute dev_attr_is_empty;
DEVICE_ATTR_RO(is_empty);
ssize_t is_empty_show(struct device *dev, 
		struct device_attribute *attr, char *buf){
	return 0;
}

/* Всё для работы через clear */
//struct device_attribute dev_attr_clear;
DEVICE_ATTR_WO(clear);
ssize_t clear_store(struct device *dev, struct device_attribute *attr, 
                    const char *buf, size_t count){
	return 0;
}


