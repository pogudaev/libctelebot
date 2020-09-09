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


#include <ct_message.h>
#include <string.h>

struct ct_message_s{
    ssize_t message_id;
    time_t date;
    ssize_t chat_id;
    char *text; //0-4096
    //TODO - добавить обработку картинок и прочего.
};

ct_message_t *ct_message_create()
{
    ct_message_t *ct_message = (ct_message_t *) calloc(sizeof (ct_message_t), 1);
    if (ct_message) {
        ct_message->text = calloc(1, 1);
    }
    return ct_message;
}

void ct_message_free(ct_message_t *ct_message)
{
    if (ct_message->text) free(ct_message->text);
    free(ct_message);
}

void ct_message_set_message_id(ct_message_t *ct_message, ssize_t message_id)
{
    ct_message->message_id = message_id;
}

void ct_message_set_date(ct_message_t *ct_message, time_t date)
{
    ct_message->date = date;
}

void ct_message_set_chat_id(ct_message_t *ct_message, ssize_t chat_id)
{
    ct_message->chat_id = chat_id;
}

void ct_message_set_text(ct_message_t *ct_message, const char *text)
{
    free(ct_message->text);
    ct_message->text = strdup(text);
}

ssize_t ct_message_get_message_id(const ct_message_t *ct_message)
{
    return ct_message->message_id;
}

time_t ct_message_get_date(const ct_message_t *ct_message)
{
    return ct_message->date;
}

ssize_t ct_message_get_chat_id(const ct_message_t *ct_message)
{
    return ct_message->chat_id;
}

const char *ct_message_get_text(const ct_message_t *ct_message)
{
    return ct_message->text;
}

