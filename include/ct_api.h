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

ct_api_t *ct_api_create(void);
void ct_api_free(ct_api_t *ct_api);

void ct_api_set_token(ct_api_t *ct_api, const char *token);

bool ct_api_update(ct_api_t *ct_api);

bool ct_api_send_text(ct_api_t *ct_api, ssize_t chat_id, const char *text);

ct_buffer_t *ct_api_get_file(ct_api_t *ct_api, const char *file_id);
bool ct_api_send_photo(ct_api_t *ct_api, ssize_t chat_id, ct_buffer_t *content);

ct_message_t *ct_api_recv_message(ct_api_t *ct_api);

#endif // CT_API_H
