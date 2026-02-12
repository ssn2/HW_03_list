/*
 * stack.c
 * Реализация функиций работы со стеком
 */

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/string.h>
#include <linux/slab.h>
#include "inc/stack.h"

/* Собственно сам стек */
struct stack mystack;

void stack_init()
{
	pr_info("Начинаем инициализацию стека\n");
	INIT_LIST_HEAD(&mystack.elements);
	mystack.size=0;
	pr_info("И закончили\n");
}

int stack_push(int value)
{
	struct stack_entry *item;

	item = kmalloc(sizeof(struct stack_entry), GFP_KERNEL);
	if (!item) {
		pr_err("Ошибка выделения памяти для элемента стека\n");
		return STACK_NOMEM;
	}

	item->data = value;
	INIT_LIST_HEAD(&item->list);
	list_add(&item->list, &mystack.elements);
	mystack.size++;
	pr_info("Добавлен элемент: %d. Размер стека: %d\n",
            value, mystack.size);
	return STACK_OK;
}

int stack_pop(void)
{
	struct stack_entry *item;
	int _value;

	if (list_empty(&mystack.elements)){
		pr_err("Ошибка - стек пуст\n");
		return STACK_EMPTY;
	}

	item = list_first_entry(&mystack.elements, struct stack_entry, list);
	_value = item->data;
	list_del(&item->list);
	kfree(item);
	mystack.size--;
	pr_info("Вынут элемент: %d. Размер стека: %d\n", _value, mystack.size);

	return _value;
}

int stack_peek()
{
	struct stack_entry *item;
	if (list_empty(&mystack.elements)){
		pr_err("Ошибка - стек пуст\n");
		return STACK_EMPTY;
	}

	item = list_first_entry(&mystack.elements, struct stack_entry, list);
	pr_info("На вершине стека: %d\n", item->data);
	return item->data;
}

int stack_is_empty()
{
	return mystack.size == 0;
}

int stack_size()
{
	return mystack.size;
}

void stack_clear(void)
{
	struct stack_entry *item, *tmp;

	list_for_each_entry_safe(item, tmp, &mystack.elements, list) {
		list_del(&item->list);
		kfree(item);
	}

	mystack.size = 0;
	pr_info("Cтек очищен\n");
}

