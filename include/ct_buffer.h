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

#ifndef CT_BUFFER_H
#define CT_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <jansson.h>

struct ct_buffer_s;
typedef struct ct_buffer_s ct_buffer_t;

/**
 * @brief ct_buffer_create создает буфер ct_buffer_t
 * @return указатель на объект ct_buffer_t, или NULL в случае ошибки
 * @note объект ct_buffer_t создается в куче. Требуется очистка памяти функцией ct_buffer_free
 */
ct_buffer_t *ct_buffer_create(void);

/**
 * @brief ct_buffer_free очищает память выделенную под объект ct_buffer_t
 * @param buffer указатель на объект ct_buffer_t для которого требуется очистка памяти
 */
void ct_buffer_free(ct_buffer_t *buffer);

/**
 * @brief ct_buffer_set устанавливает содержимое буфера. Прежние данные удаляются.
 * @param buffer указатель на объект ct_buffer_t
 * @param data указатель на область памяти из которой будут скопированы данные в буфер
 * @param size размер данных которые будут скопированны в буффер
 */
void ct_buffer_set(ct_buffer_t *buffer, const void *data, size_t size);

/**
 * @brief ct_buffer_add добавляет новые данные к тем что уже есть в буффере.
 * @param buffer указатель на объект ct_buffer_t
 * @param data указатель на область памяти из которой будут скопированы данные в буфер
 * @param size размер данных которые будут добавлены в буффер
 */
void ct_buffer_add(ct_buffer_t *buffer, const void *data, size_t size);

/**
 * @brief ct_buffer_get получает данные из буфера копированием в новую область памяти
 * @param buffer указатель на объект ct_buffer_t
 * @param data двойной указатель на новую область памяти куда будут записаны данные.
 * @param size указатель на переменную куда будет записано сколько байт было скопировано
 * @note для data выделяется память в куче, после использования ее необходимо освободить функцией free
 */
void ct_buffer_get(const ct_buffer_t *buffer, void **data, size_t *size);

/**
 * @brief ct_buffer_get_data возвращает указатель на данные в буфере
 * @param buffer указатель на объект ct_buffer_t
 * @return указатель на данные в буфере
 * @note если буффер пуст будет возвращен валидный указатель
 */
const void *ct_buffer_get_data(const ct_buffer_t *buffer);

/**
 * @brief ct_buffer_get_size возвращает текущий размер буфера
 * @param buffer указатель на объект ct_buffer_t
 * @return размер
 */
size_t ct_buffer_get_size(const ct_buffer_t *buffer);

/**
 * @brief ct_buffer_set_string устанавливает содержимое буфера из строки
 * @param buffer указатель на объект ct_buffer_t
 * @param string строка
 */
void ct_buffer_set_string(ct_buffer_t *buffer, const char *string);

/**
 * @brief ct_buffer_get_data возвращает указатель на строку в буфере
 * @param buffer указатель на объект ct_buffer_t
 * @return указатель на строку в буфере
 * @note если буффер пуст будет возвращен указатель на пустую строку
 */
#define ct_buffer_get_string(b) (const char *)(ct_buffer_get_data(buff));

#ifdef __cplusplus
}
#endif

#endif // CT_BUFFER_H
