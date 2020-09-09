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

#include <stdlib.h>
#include <jansson.h>

struct ct_buffer_s;
typedef struct ct_buffer_s ct_buffer_t;

ct_buffer_t *ct_buffer_create(void);
void ct_buffer_free(ct_buffer_t *buffer);

void ct_buffer_set(ct_buffer_t *buffer, const void *data, size_t size);
void ct_buffer_add(ct_buffer_t *buffer, const void *data, size_t size);
void ct_buffer_get(const ct_buffer_t *buffer, void **data, size_t *size);

const void *ct_buffer_get_data(const ct_buffer_t *buffer);
size_t ct_buffer_get_size(const ct_buffer_t *buffer);

#define ct_buffer_get_string(b) (const char *)(ct_buffer_get_data(buff));
void ct_buffer_set_string(ct_buffer_t *buffer, const char *string);


#endif // CT_BUFFER_H
