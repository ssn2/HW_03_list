/*
 * sysfs.c
 * Работа с sysfs
 */

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#include <linux/kobject.h>
#include <linux/module.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

#include <kernel_stack.h>
#include <stack.h>


/* Всё для работы через push */
DEVICE_ATTR_WO(push);
ssize_t push_store(struct device *dev, struct device_attribute *attr, 
                    const char *buf, size_t count){

	/* Времянка, которая потом будет передана для добавления в стек */
	int _value;
	int ret;

	if (kstrtoint(buf, 10, &_value))
        	return -EINVAL;

/*
 * Тут можно (но нужно ли?) подтвердить, но в ДЗ написано что не надо
 * pr_info("Got new value: %d\n", _value);
 */
	ret = stack_push(_value);

/*
 * Надо ли делать вывод тут? Или достаточно выводить в функции
 * stack_push? Собственно дальше ответ я получил. Ядро в консоль кашлянёт
 * root@www:~/work/HW_03_list# cat /sys/kernel/kernel_stack/peek
 * cat: /sys/kernel/kernel_stack/peek: Операция не позволена
 *
 *	if (ret != STACK_OK) 
 *		pr_err("Ошибка добавления элемента %d, %d\n",
 *				_value, ret);
 */

////// Тут надо возвращать количество обработанный байт, а не 0 как обычно!!!!
	return count;
}

/* Всё для работы через pop */
DEVICE_ATTR_RO(pop);
ssize_t pop_show(struct device *dev, 
		struct device_attribute *attr, char *buf){
	int ret;
	ret = stack_pop();
	if (ret == STACK_EMPTY)
		return -EPERM;
	
	return sysfs_emit(buf,
		"%d\n",
		ret);
}

/* Всё для работы через peek */
DEVICE_ATTR_RO(peek);
ssize_t peek_show(struct device *dev,
		struct device_attribute *attr, char *buf){
	int ret;
	ret = stack_peek();
	if (ret == STACK_EMPTY)
		return -EPERM;
	
	return sprintf(buf, "%d\n", ret);
}

/* Всё для работы через size */
DEVICE_ATTR_RO(size);
ssize_t size_show(struct device *dev,
		struct device_attribute *attr, char *buf){
	return sprintf(buf, "%d\n", stack_size());
}

/* Всё для работы через is_empty */
DEVICE_ATTR_RO(is_empty);
ssize_t is_empty_show(struct device *dev, 
		struct device_attribute *attr, char *buf){
	int ret = stack_is_empty();
	return sprintf(buf, "%d\n", ret);
}

/* Всё для работы через clear */
DEVICE_ATTR_WO(clear);
ssize_t clear_store(struct device *dev, struct device_attribute *attr, 
                    const char *buf, size_t count){
	stack_clear();
	return count;
}


/* 
 * Тут мы инициализируем переменные для групповой регистрации 
 * аттрибутов-файлов
 */
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

/* Инициализиуем наш участок sysfs */
void mod_sysfs_init(void){
	int ret;
	kobj = kobject_create_and_add("kernel_stack", kernel_kobj);
	ret = sysfs_create_group(kobj, &attr_group);
}

/* Освобождаем ресурсы sysfs */
void mod_sysfs_close(void){
	sysfs_remove_group(kobj, &attr_group);
	kobject_put(kobj);
}

