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

#ifndef CT_NET_API_H
#define CT_NET_API_H

#include "ct_buffer.h"
#include <jansson.h>
#include "ct_param_list.h"

/**
 * @brief ct_post - отправляет POST запрос на сервер
 * @param req - reqest line
 * @param params - список параметров для POST запроса (будет очищен после вызова)
 * @return ответ в виде json (требуется последующая очистка), NULL - если ошибка.
 */

json_t *ct_post(const char *req, ct_param_list_t *params);

ct_buffer_t *ct_load_file(const char *req);

#endif // CT_NET_API_H
