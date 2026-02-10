#include <linux/list.h>

/**
 * struct stack - структура стека 
 *
 * @elements:      Указатель на голову связанного списка
 * @size:          Текущее количество элементов стека
 */
struct stack {
	struct list_head elements;
	int size;
};

/**
 * stack_entry - структура элемента стека 
 * @list:         Узел связанного списка
 * @data:         Данные (целое число)
 */
struct stack_entry {
	struct list_head list;
	int data;
};

/**
 * stack_init() - инициализация стека
 */
void stack_init(void);

/*
 * stack_push() - добавляет элемент на вершину стека
 *
 * @int:           добавляемый элемент
 *
 * Return: int (0 - успех, 1 - ошибка)
 */
int stack_push(int value);

/*
 *
 */
int stack_pop(void);
