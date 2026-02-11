/*
 * kernel_stack.h
 * описание переменных и функций
 * extern для того, чтобы можно было пользоваться в двух файлах .c
 * натягивал на структуру файлов домашнего задания.
 * Сам я не очень понимаю такую структуру и вот это вот всё :(
 * Но иначе не компилируется *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#ifndef _KERNEL_STACK_H
#define _KERNEL_STACK_H

#include <linux/kernel.h>
#include <linux/device.h>

/*
 * Аттрибуты модуля в sysfs и функции для работы с ними
 *
 * push:     добавить элемент передав целое число
 * pop:      получить элемент и удалить его из стека
 * peek:     получить значение из вершины стека
 * size:     получить текущее количество элеменов стека
 * is_empty: проверить наполененность стека. 0 - пуст, 1 - нет
 * clear:    очистить передав любое значение
 * 
 */
extern struct device_attribute dev_attr_push;
extern ssize_t push_store(struct device *dev, struct device_attribute *attr, 
		const char *buf, size_t count);

extern struct device_attribute dev_attr_pop;
extern ssize_t pop_show(struct device *dev, struct device_attribute *attr, 
		char *buf);

extern struct device_attribute dev_attr_peek;
extern ssize_t peek_show(struct device *dev, struct device_attribute *attr, 
		char *buf);

extern struct device_attribute dev_attr_size;
extern ssize_t size_show(struct device *dev, struct device_attribute *attr, 
		char *buf);

extern struct device_attribute dev_attr_is_empty;
extern ssize_t is_empty_show(struct device *dev, struct device_attribute *attr,
		char *buf);

extern struct device_attribute dev_attr_clear;
extern ssize_t clear_store(struct device *dev, struct device_attribute *attr, 
                    const char *buf, size_t count);


#endif /* _KERNEL_STACK_H */
