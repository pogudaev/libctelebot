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

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

struct ct_message_s;
typedef struct ct_message_s ct_message_t;

ct_message_t *ct_message_create(void);
void ct_message_free(ct_message_t *ct_message);

void ct_message_set_message_id(ct_message_t *ct_message, ssize_t message_id);
void ct_message_set_date(ct_message_t *ct_message, time_t date);
void ct_message_set_chat_id(ct_message_t *ct_message, ssize_t chat_id);
void ct_message_set_text(ct_message_t *ct_message, const char *text);

ssize_t ct_message_get_message_id(const ct_message_t *ct_message);
time_t ct_message_get_date(const ct_message_t *ct_message);
ssize_t ct_message_get_chat_id(const ct_message_t *ct_message);
const char *ct_message_get_text(const ct_message_t *ct_message);

#endif // CT_MESSAGE_H
