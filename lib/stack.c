/*
 *
 *
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
	return 0;
}

int stack_peek()
{
	return 0;
}

int stack_is_empty()
{
	return 0;
}

int stack_size()
{
	return mystack.size;
}

void stack_clear()
{
	return;
}

