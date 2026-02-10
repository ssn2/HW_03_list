/*
 *
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ":" fmt

#include <linux/kernel.h>
#include <linux/module.h>

#include "inc/stack.h"

void stack_init()
{
}

int stack_push(int value)
{
	return value;
}

int stack_pop(void)
{
	return 0;
}
