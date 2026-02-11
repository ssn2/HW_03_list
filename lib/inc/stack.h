#include <linux/list.h>

#define STACK_OK          0      /* Операция успешна */
#define STACK_EMPTY      -1      /* Стек пуст */
#define STACK_NOMEM      -2      /* Нет памяти */
#define STACK_INVALID    -3      /* Неверный параметр */



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

/**
 * stack_push() - добавляет элемент на вершину стека
 *
 * @int:           добавляемый элемент
 *
 * Return: int (0 - успех, 1 - ошибка)
 */
int stack_push(int value);

/**
 *
 */
int stack_pop(void);

/**
 * Удаляет элемент из вершины стека и возвращает его 
 *
 * Return:  * int, значение или код ошибки
 */
int stack_peek(void);

/**
 * Проверяет пустоту стека. 
 *
 * Return: int, 0 - пустой, 1 - нет
 */
int stack_is_empty(void);

/**
 * Возвращает текущее количество элементов
 */
int stack_size(void);

/**
 * Очищает стек
 */
void stack_clear(void);

