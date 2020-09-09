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


#include <ct_api.h>
#include <stdlib.h>
#include <string.h>
#include <ct_queue.h>
#include <ct_message.h>
#include <ct_buffer.h>
#include <ct_param_list.h>
#include <ct_net_api.h>
#include <jansson.h>
#include <ct_common.h>

struct ct_api_s {
	ct_queue_t *unread_messages;
	char *token;
	ssize_t last_update_id;
};

/**
 * @brief ct_api_request - запрос серверу telegram
 * @param ct_api
 * @param method - метод
 * @param params - параметры (будут очищены в процессе выполнения)
 * @return
 */
static json_t *ct_api_request(const ct_api_t *ct_api, const char *method, ct_param_list_t *params);

ct_api_t *ct_api_create()
{
	ct_api_t *ct_api = (ct_api_t *) malloc(sizeof (ct_api_t));

	if (ct_api) {
		ct_api->unread_messages = ct_queue_create();
		ct_queue_set_free_function(ct_api->unread_messages, (free_function_t) ct_message_free);
		ct_api->token = strdup("");
		ct_api->last_update_id = 0;
	}

	return ct_api;
}


void ct_api_free(ct_api_t *ct_api)
{
	ct_queue_free(ct_api->unread_messages);
	free(ct_api->token);
	free(ct_api);
}

void ct_api_set_token(ct_api_t *ct_api, const char *token)
{
	free(ct_api->token);
	ct_api->token = strdup(token);
}

bool ct_api_update(ct_api_t *ct_api)
{
	ct_param_list_t *ct_param_list = ct_param_list_create();
	ct_param_list_add_integer(ct_param_list, "offset", ct_api->last_update_id);

	json_t *result = ct_api_request(ct_api, "getUpdates", ct_param_list);

	if (!result) {
		ct_log_error("telegramm_api_request() error!");
		return false;
	}


	size_t size = json_array_size(result);

	if (size) {
		json_t *last_updates = json_array_get(result, size - 1);
		ssize_t last_update_id = (ssize_t) json_integer_value(json_object_get(last_updates, "update_id"));
		ct_api->last_update_id = last_update_id + 1;
	}


	size_t index;
	json_t *value;

	json_array_foreach(result, index, value) {
		json_t *j_message = json_object_get(value, "message");
		json_t *j_text = json_object_get(j_message, "text");
		json_t *j_photo = json_object_get(j_message, "photo");

		if (j_photo) {
			ct_log_info("Receive Photo");
		}

		if (j_text) {
			ct_log_info("Receive Text");
			json_t *j_chat = json_object_get(j_message, "chat");
			json_t *j_date = json_object_get(j_message, "date");
			json_t *j_mess_id = json_object_get(j_message, "message_id");
			json_t *j_chat_id = json_object_get(j_chat, "id");

			if (!j_chat_id || !j_date || !j_mess_id || !j_text) {
				continue;
			}

			ct_message_t *ct_message = ct_message_create();
			ct_message_set_date(ct_message, (time_t) json_integer_value(j_date));
			ct_message_set_text(ct_message, json_string_value(j_text));
			ct_message_set_chat_id(ct_message, json_integer_value(j_chat_id));
			ct_message_set_message_id(ct_message, json_integer_value(j_mess_id));
			ct_queue_push(ct_api->unread_messages, ct_message);
		}
	}
	json_decref(result);
	return true;
}

ct_message_t *ct_api_recv_message(ct_api_t *ct_api)
{
	return ct_queue_pull(ct_api->unread_messages);
}

static json_t *ct_api_request(const ct_api_t *ct_api, const char *method, ct_param_list_t *params)
{
	char request[256];
	sprintf(request, "https://api.telegram.org/bot%s/%s", ct_api->token, method);

	json_t *j_answer = ct_post(request, params);

	json_t *out = NULL;
	const json_t *j_ok = json_object_get(j_answer, "ok");

	if (json_is_true(j_ok)) {
		json_t *j_result = json_object_get(j_answer, "result");

		if (j_result) {
			out = json_deep_copy(j_result);
		}
	}

	json_decref(j_answer);
	return out;
}

bool ct_api_send_text(ct_api_t *ct_api, ssize_t chat_id, const char *text)
{
	ct_param_list_t *ct_param_list = ct_param_list_create();
	ct_param_list_add_integer(ct_param_list, "chat_id", chat_id);
	ct_param_list_add_string(ct_param_list, "text", text);

	json_t *result = ct_api_request(ct_api, "sendMessage", ct_param_list);

	if (!result) {
		ct_log_error("telegramm_api_request() error!");
		return false;
	}

	json_decref(result);
	return true;
}

ct_buffer_t *ct_api_get_file(ct_api_t *ct_api, const char *file_id)
{
	ct_param_list_t *ct_param_list = ct_param_list_create();
	ct_param_list_add_string(ct_param_list, "file_id", file_id);

	json_t *result = ct_api_request(ct_api, "getFile", ct_param_list);

	if (!result) {
		ct_log_error("telegramm_api_request() error!");
		return NULL;
	}

	size_t file_size = (size_t) json_integer_value(json_object_get(result, "file_size"));
	char *file_path = NULL;
	const char *_file_path = json_string_value(json_object_get(result, "file_path"));

	if (_file_path) {
		file_path = strdup(_file_path);
	}

	json_decref(result);

	ct_log_info("file: size: %d bytes; path: %s", file_size, file_path);

	char req[1024];
	snprintf(req, sizeof(req), "https://api.telegram.org/file/bot%s/%s", ct_api->token, file_path);

	return ct_load_file(req);
}

bool ct_api_send_photo(ct_api_t *ct_api, ssize_t chat_id, ct_buffer_t *content)
{
	ct_param_list_t *ct_param_list = ct_param_list_create();
	ct_param_list_add_integer(ct_param_list, "chat_id", chat_id);
	ct_param_list_add_image(ct_param_list, "photo", content);

	json_t *result = ct_api_request(ct_api, "sendPhoto", ct_param_list);

	if (!result) {
		ct_log_error("ct_api_send_photo() error!");
		return false;
	}

	json_decref(result);
	return true;
}
