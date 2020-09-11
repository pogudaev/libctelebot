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

#ifndef CT_API_H
#define CT_API_H

#include <stdbool.h>
#include "ct_message.h"
#include "ct_buffer.h"

struct ct_api_s;
typedef struct ct_api_s ct_api_t;

/**
 * @brief ct_api_create создает объект ct_api_t
 * @return указатель на объект ct_api_t, или NULL в случае ошибки
 * @note объект ct_api_t создается в куче. Требуется очистка памяти функцией ct_api_free
 */
ct_api_t *ct_api_create(void);

/**
 * @brief ct_api_free очищает память выделенную под объект ct_api_t
 * @param ct_api указатель на объект ct_api_t для которого требуется очистка памяти
 */
void ct_api_free(ct_api_t *ct_api);

/**
 * @brief ct_api_set_token устанавливает токен бота
 * @param ct_api указатель на объект ct_api_t
 * @param token указатель на строку с токеном
 * @note token следует получить у @BotFather
 */
void ct_api_set_token(ct_api_t *ct_api, const char *token);

/**
 * @brief ct_api_update проверяет новые входящие сообщения и загружает их. Для получения загруженного сообщения надо использовать ct_api_recv_message
 * @param ct_api указатель на объект ct_api_t
 * @return true - успех, false - ошибка
 */
bool ct_api_update(ct_api_t *ct_api);

/**
 * @brief ct_api_send_text посылает текстовое сообщение в указанный чат
 * @param ct_api указатель на объект ct_api_t
 * @param chat_id идентификатор чата
 * @param text отправляемый текст
 * @return true - успех, false - ошибка
 */
bool ct_api_send_text(ct_api_t *ct_api, ssize_t chat_id, const char *text);

/**
 * @brief ct_api_get_file загружает файл по указанному идентификатору
 * @param ct_api указатель на объект ct_api_t
 * @param file_id идентификатор файла
 * @return указатель на буффер с файлом
 * @note буффер ct_buffer_t создается в куче. Требуется очистка памяти функцией ct_buffer_free
 */
ct_buffer_t *ct_api_get_file(ct_api_t *ct_api, const char *file_id);

/**
 * @brief ct_api_send_photo посылает сообщение с картинкой
 * @param ct_api указатель на объект ct_api_t
 * @param chat_id идентификатор чата
 * @param content указатель на буффер с передаваемыми данными
 * @note буфер должен быть создан в куче, он переходит во владение этой функции и не требует очистки
 * @note в буфере должно находиться валидное содержимое JPEG-файла, другие форматы пока не поддерживаются
 * @return true - успех, false - ошибка
 */
bool ct_api_send_photo(ct_api_t *ct_api, ssize_t chat_id, ct_buffer_t *content);

/**
 * @brief ct_api_recv_message возвращает загруженное принятое сообщение
 * @param ct_api указатель на объект ct_api_t
 * @return указатель на сообщение типа ct_message_t
 * @note сообщение ct_message_t создается в куче. Требуется очистка памяти функцией ct_message_free
 */
ct_message_t *ct_api_recv_message(ct_api_t *ct_api);

#endif // CT_API_H
