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


#include <ct_param_list.h>
#include <string.h>
#include <ct_buffer.h>
#include <ct_common.h>

struct ct_param_list_elem_s;
typedef struct ct_param_list_elem_s ct_param_list_elem_t;

struct ct_param_list_elem_s {
	char *param_name;
	ct_buffer_t *param_data;
	ct_type_t ct_type;
	ct_param_list_elem_t *next;
};

struct ct_param_list_s {
	ct_param_list_elem_t *head;
};

static void ct_param_list_add(ct_param_list_t *ct_param_list, char *param_name, ct_buffer_t *param_data, ct_type_t ct_type);

ct_param_list_t *ct_param_list_create()
{
	ct_param_list_t *ct_param_list = (ct_param_list_t *) calloc(sizeof(ct_param_list_t), 1);
	return ct_param_list;
}

void ct_param_list_free(ct_param_list_t *ct_param_list)
{
	ct_param_list_erase(ct_param_list);
	free(ct_param_list);
}

void ct_param_list_erase(ct_param_list_t *ct_param_list)
{
	if (ct_param_list->head) {
		ct_param_list_elem_t *item = ct_param_list->head;

		while (item) {
			free(item->param_name);
			ct_buffer_free(item->param_data);
			ct_param_list_elem_t *del_item = item;
			item = item->next;
			free(del_item);
		}
	}
}

void ct_param_list_foreach(const ct_param_list_t *ct_param_list, ct_param_list_foreach_function_t ct_param_list_foreach_function, void *user_args)
{
	if (ct_param_list_foreach_function == NULL) {
		return;
	}

	ct_param_list_elem_t *item = ct_param_list->head;

	while (item) {
		ct_param_list_foreach_function(item->param_name, item->param_data, item->ct_type, user_args);
		item = item->next;
	}
}

static void ct_param_list_add(ct_param_list_t *ct_param_list, char *param_name, ct_buffer_t *param_data, ct_type_t ct_type)
{
	if (ct_param_list->head == NULL) {
		ct_param_list_elem_t *item = (ct_param_list_elem_t *) malloc(sizeof (ct_param_list_elem_t));
		item->next = NULL;
		item->param_data = param_data;
		item->param_name = param_name;
		item->ct_type = ct_type;
		ct_param_list->head = item;
		return;
	}

	ct_param_list_elem_t *elem = ct_param_list->head;

	while (elem) {
		if (elem->next == NULL) {
			ct_param_list_elem_t *item = (ct_param_list_elem_t *) malloc(sizeof (ct_param_list_elem_t));
			item->next = NULL;
			item->param_data = param_data;
			item->param_name = param_name;
			item->ct_type = ct_type;
			elem->next = item;
			return;
		}

		elem = elem->next;
	}
}

void ct_param_list_add_string(ct_param_list_t *ct_param_list, const char *param_name, const char *param_value)
{
	if (param_name == NULL || param_value == NULL) {
		ct_log_warning("Bad param_name or param_value. Skip");
		return;
	}

	ct_buffer_t *ct_buffer = ct_buffer_create();
	ct_buffer_set_string(ct_buffer, param_value);
	ct_param_list_add(ct_param_list, strdup(param_name), ct_buffer, ct_type_default);
}

void ct_param_list_add_integer(ct_param_list_t *ct_param_list, const char *param_name, ssize_t param_value)
{
	if (param_name == NULL) {
		ct_log_warning("Bad param_name. Skip");
		return;
	}

	ct_buffer_t *ct_buffer = ct_buffer_create();
	char tmp[32];
	snprintf(tmp, sizeof (tmp), "%zd", param_value);
	ct_buffer_set_string(ct_buffer, tmp);
	ct_param_list_add(ct_param_list, strdup(param_name), ct_buffer, ct_type_default);
}

void ct_param_list_add_boolean(ct_param_list_t *ct_param_list, const char *param_name, bool param_value)
{
	if (param_name == NULL) {
		ct_log_warning("Bad param_name. Skip");
		return;
	}

	ct_buffer_t *ct_buffer = ct_buffer_create();

	if (param_value) {
		ct_buffer_set_string(ct_buffer, "true");
	} else {
		ct_buffer_set_string(ct_buffer, "false");
	}

	ct_param_list_add(ct_param_list, strdup(param_name), ct_buffer, ct_type_default);
}

void ct_param_list_add_image(ct_param_list_t *ct_param_list, const char *param_name, const ct_buffer_t *param_data)
{
	if (param_name == NULL || param_data == NULL) {
		ct_log_warning("Bad param_name or param_data. Skip");
		return;
	}

	ct_buffer_t *ct_buffer = ct_buffer_create();
	ct_buffer_set(ct_buffer, ct_buffer_get_data(param_data), ct_buffer_get_size(param_data));
	ct_param_list_add(ct_param_list, strdup(param_name), ct_buffer, ct_type_image_jpeg);
}
