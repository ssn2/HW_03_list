/*
 * А чо оно ругается на коммент?
 *
 *
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#ifndef _KERNEL_STACK_H
#define _KERNEL_STACK_H

#include <linux/kernel.h>
#include <linux/device.h>

/* Добавить элемент, передав целое число */
//static int push;

/* Получить элемент и удалить его из стека */
//static int read;

/* Получить значение вершины стека */
//static int peek;

/* Получить текущее количество элементов стека */
//static int size;

/* Проверить наполненность стека. 0 - пуст, 1 - нет */
//static unsigned char is_empty;

/* Очистить стек передав любое значние */
//static char write;


/* Функции для sysfs */
ssize_t push_show(struct device *dev, struct device_attribute *attr, char *buf);
ssize_t push_store(struct device *dev, struct device_attribute *attr, 
                    const char *buf, size_t count);


#endif /* _KERNEL_STACK_H */