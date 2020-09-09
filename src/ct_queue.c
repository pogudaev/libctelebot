/*
Copyright (c) 2020 Alexander Pogudaev
This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.
Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:
1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
    Alexander Pogudaev
    pogudaev@yandex.ru
*/

#include <ct_queue.h>
#include <stdlib.h>

struct ct_queue_elem_s;

typedef struct ct_queue_elem_s ct_queue_elem_t;

struct ct_queue_elem_s {
	void *object;
	ct_queue_elem_t *prev;
	ct_queue_elem_t *next;
};

struct ct_queue_s {
	free_function_t free_function;
	ct_queue_elem_t *head;
	ct_queue_elem_t *tail;
};

ct_queue_t *ct_queue_create(void)
{
	ct_queue_t *ct_queue = calloc(sizeof (ct_queue_t), 1);
	return ct_queue;
}

void ct_queue_free(ct_queue_t *ct_queue)
{
	ct_queue_erase(ct_queue);
	free(ct_queue);
}

void ct_queue_push(ct_queue_t *ct_queue, void *object)
{
	ct_queue_elem_t *ct_queue_elem = calloc(sizeof (ct_queue_elem_t), 1);

	if (!ct_queue_elem) {
		return;
	}

	ct_queue_elem->object = object;

	if (ct_queue->head == NULL) { //пока нет элементов
		ct_queue->head = ct_queue_elem;
		ct_queue->tail = ct_queue_elem;
	} else {
		ct_queue->tail->next = ct_queue_elem;
		ct_queue_elem->prev = ct_queue->tail;
		ct_queue->tail = ct_queue_elem;
	}
}

void *ct_queue_pull(ct_queue_t *ct_queue)
{
	if (ct_queue->head == NULL) {
		return NULL;    //нет элементов
	}

	ct_queue_elem_t *ct_queue_elem = ct_queue->head;

	if (ct_queue->head == ct_queue->tail) { //1 элемент
		ct_queue->head = NULL;
		ct_queue->tail = NULL;
	} else { // > 1 элемента
		ct_queue->head = ct_queue->head->next;
		ct_queue->head->prev = NULL;
	}

	void *ret = ct_queue_elem->object;
	free(ct_queue_elem);
	return ret;
}

void ct_queue_erase(ct_queue_t *ct_queue)
{
	if (!ct_queue->free_function) {
		return;
	}

	ct_queue_elem_t *elem = ct_queue->head;

	while (elem) {
		ct_queue->free_function(elem->object);
		ct_queue_elem_t *del_elem = elem;
		elem = elem->next;
		free(del_elem);
	}
}

void ct_queue_set_free_function(ct_queue_t *ct_queue, free_function_t free_function)
{
	ct_queue->free_function = free_function;
}
