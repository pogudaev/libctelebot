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

#ifndef CT_PARAM_LIST_H
#define CT_PARAM_LIST_H

#include <ct_buffer.h>
#include <stdbool.h>

typedef enum {
    ct_type_default,
    ct_type_image_jpeg
} ct_type_t;

struct ct_param_list_s;
typedef struct ct_param_list_s ct_param_list_t;
typedef void (*ct_param_list_foreach_function_t)(const char *param_name, const ct_buffer_t *param_data, ct_type_t ct_type, void *user_args);


ct_param_list_t *ct_param_list_create(void);
void ct_param_list_free(ct_param_list_t *ct_param_list);
void ct_param_list_erase(ct_param_list_t *ct_param_list);

void ct_param_list_add_string(ct_param_list_t *ct_param_list, const char *param_name, const char *param_value);
void ct_param_list_add_integer(ct_param_list_t *ct_param_list, const char *param_name, ssize_t param_value);
void ct_param_list_add_boolean(ct_param_list_t *ct_param_list, const char *param_name, bool param_value);
void ct_param_list_add_image(ct_param_list_t *ct_param_list, const char *param_name, const ct_buffer_t *param_data);


void ct_param_list_foreach(const ct_param_list_t *ct_param_list, ct_param_list_foreach_function_t ct_param_list_foreach_function, void *user_args);

#endif // CT_PARAM_LIST_H
