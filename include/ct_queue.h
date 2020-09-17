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

#ifndef CT_QUEUE_H
#define CT_QUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

struct ct_queue_s;
typedef struct ct_queue_s ct_queue_t;
typedef void (*free_function_t)(void *);

/**
 * @brief ct_queue_create создает очередь, объект типа ct_queue_t
 * @return указатель на объект типа ct_queue_t
 * @note объект создается в куче и требует последущего освобождения памяти функцией ct_queue_free
 */
ct_queue_t *ct_queue_create(void);

/**
 * @brief ct_queue_free освобождает память выделенную для объекта ct_queue_t
 * @param ct_queue указатель на объект типа ct_queue_t
 * @note память освобождается также и для хранящихся внутри элементов
 */
void ct_queue_free(ct_queue_t *ct_queue);

/**
 * @brief ct_queue_set_free_function задает функцию, которая вызывается для освобождения памяти объектов в очереди
 * @param ct_queue указатель на объект типа ct_queue_t
 * @param free_function указатель на освобождающую память функцию
 */
void ct_queue_set_free_function(ct_queue_t *ct_queue, free_function_t free_function);

/**
 * @brief ct_queue_push помещает новый элемент в конец очереди
 * @param ct_queue указатель на объект типа ct_queue_t
 * @param object помещаемый объект, должен быть создан в куче, переходит во владение очереди
 */
void ct_queue_push(ct_queue_t *ct_queue, void *object);

/**
 * @brief ct_queue_pull получает элемент из начала очереди удаляя первый элемент очереди.
 * @param ct_queue указатель на объект типа ct_queue_t
 * @return указатель на полученный элемент, требует дальнейшей очистки памяти
 */
void *ct_queue_pull(ct_queue_t *ct_queue);

/**
 * @brief ct_queue_erase удаляет из очереди все объекты
 * @param ct_queue указатель на объект типа ct_queue_t
 */
void ct_queue_erase(ct_queue_t *ct_queue);

#ifdef __cplusplus
}
#endif

#endif // CT_QUEUE_H
