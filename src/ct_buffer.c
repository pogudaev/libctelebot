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


#include <ct_buffer.h>

#include <string.h>

struct ct_buffer_s{
    void *data;
    size_t size;
};

ct_buffer_t *ct_buffer_create()
{
    ct_buffer_t *buffer = (ct_buffer_t *) malloc(sizeof (ct_buffer_t));

    if (buffer) {
        buffer->data = malloc(1);
        buffer->size = 0;
        ((char *)(buffer->data))[0] = 0;
    }

    return buffer;
}

void ct_buffer_free(ct_buffer_t *buffer)
{
    if (buffer) {
        free(buffer->data);
        free(buffer);
    }
}

void ct_buffer_set(ct_buffer_t *buffer, const void *data, size_t size)
{
    buffer->data = realloc(buffer->data, size + 1); //небезопасно
    memcpy(buffer->data, data, size);
    buffer->size = size;
    ((char *)(buffer->data))[buffer->size] = 0;
}

void ct_buffer_add(ct_buffer_t *buffer, const void *data, size_t size)
{
    if (size == 0) return;

    buffer->data = realloc(buffer->data, buffer->size + size + 1); //небезопасно
    memcpy(((char *)(buffer->data)) + buffer->size, data, size);
    buffer->size += size;
    ((char *)(buffer->data))[buffer->size] = 0;
}

void ct_buffer_get(const ct_buffer_t *buffer, void **data, size_t *size)
{
    (*data) = malloc(buffer->size + 1);
    memcpy(*data, buffer->data, buffer->size + 1);
    *size = buffer->size;
}

void ct_buffer_set_string(ct_buffer_t *buffer, const char *string)
{
    ct_buffer_set(buffer, string, strlen(string) + 1);
}

const void *ct_buffer_get_data(const ct_buffer_t *buffer)
{
    return (const void *) buffer->data;
}

size_t ct_buffer_get_size(const ct_buffer_t *buffer)
{
    return buffer->size;
}
