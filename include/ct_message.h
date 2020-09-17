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

#ifndef CT_MESSAGE_H
#define CT_MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

struct ct_message_s;
typedef struct ct_message_s ct_message_t;

typedef enum {
	ct_message_type_unknown,
	ct_message_type_text,
	ct_message_type_photo
} ct_message_type_t;

/**
 * @brief ct_message_create создает объект ct_message_t
 * @return указатель на объект ct_message_t, или NULL в случае ошибки
 * @note объект создается в куче и требует последующей очистки функцией ct_message_free
 */
ct_message_t *ct_message_create(void);

/**
 * @brief ct_message_free освобождает память выделенную для объекта ct_message_t
 * @param ct_message указатель на объект ct_message_t для которого требуется освобождение памяти
 */
void ct_message_free(ct_message_t *ct_message);

/**
 * @brief ct_message_set_message_id устанавливает идентификатор сообщения для ct_message_t
 * @param ct_message указатель на объект ct_message_t
 * @param message_id идентификатор сообщения
 */
void ct_message_set_message_id(ct_message_t *ct_message, ssize_t message_id);

/**
 * @brief ct_message_set_date устанавливает дату и время для ct_message_t
 * @param ct_message указатель на объект ct_message_t
 * @param date дату и время в формате unixtime
 */
void ct_message_set_date(ct_message_t *ct_message, time_t date);

/**
 * @brief ct_message_set_chat_id устанавливает идентификатор чата для ct_message_t
 * @param ct_message указатель на объект ct_message_t
 * @param chat_id идентификатор чата
 */
void ct_message_set_chat_id(ct_message_t *ct_message, ssize_t chat_id);

/**
 * @brief ct_message_set_text устанавливает текст сообщения для ct_message_t
 * @param ct_message указатель на объект ct_message_t
 * @param text текст
 */
void ct_message_set_text(ct_message_t *ct_message, const char *text);

/**
 * @brief ct_message_set_file_id устанавливает идентификатор передаваемого файла
 * @param ct_message указатель на объект ct_message_t
 * @param file_id текстовый идентификатор
 */
void ct_message_set_file_id(ct_message_t *ct_message, const char *file_id);

/**
 * @brief ct_message_set_caption устанавливает описание передаваемого файла
 * @param ct_message указатель на объект ct_message_t
 * @param caption описание
 */
void ct_message_set_caption(ct_message_t *ct_message, const char *caption);

/**
 * @brief ct_message_set_message_type устанавливает тип сообщения по содержимому
 * @param ct_message указатель на объект ct_message_t
 * @param message_type тип сообщения
 */
void ct_message_set_message_type(ct_message_t *ct_message, ct_message_type_t message_type);

/**
 * @brief ct_message_get_message_id получает идентификатор сообщения
 * @param ct_message указатель на объект ct_message_t
 * @return идентификатор сообщения
 */
ssize_t ct_message_get_message_id(const ct_message_t *ct_message);

/**
 * @brief ct_message_get_date получает даты и время сообщения в формате unixtime
 * @param ct_message указатель на объект ct_message_t
 * @return дата и время сообщения
 */
time_t ct_message_get_date(const ct_message_t *ct_message);

/**
 * @brief ct_message_get_chat_id получает идентификатор чата
 * @param ct_message указатель на объект ct_message_t
 * @return идентификатор чата
 */
ssize_t ct_message_get_chat_id(const ct_message_t *ct_message);

/**
 * @brief ct_message_get_text получает текст сообщения
 * @param ct_message указатель на объект ct_message_t
 * @return указатель на текст сообщения
 */
const char *ct_message_get_text(const ct_message_t *ct_message);

/**
 * @brief ct_message_get_caption получает описание файла
 * @param ct_message указатель на объект ct_message_t
 * @return указатель на текст с описанием файла
 */
const char *ct_message_get_caption(const ct_message_t *ct_message);

/**
 * @brief ct_message_get_file_id получает идентификатор файла
 * @param ct_message указатель на объект ct_message_t
 * @return указатель на текст с идентификатором файла
 */
const char *ct_message_get_file_id(const ct_message_t *ct_message);

/**
 * @brief ct_message_get_message_type получает тип сообщения
 * @param ct_message указатель на объект ct_message_t
 * @return тип сообщения
 */
ct_message_type_t ct_message_get_message_type(const ct_message_t *ct_message);

#ifdef __cplusplus
}
#endif

#endif // CT_MESSAGE_H
