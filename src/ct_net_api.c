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


#include <ct_net_api.h>

#include <curl/curl.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ct_common.h>

static size_t write_data_cb(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	ct_buffer_t *data = (ct_buffer_t *)(userp);
	ct_buffer_add(data, contents, realsize);
	return realsize;
}

ct_buffer_t *ct_load_file_with_auth(const char *req, const char *login, const char *password)
{
	ct_buffer_t *answer = ct_buffer_create();

	curl_global_init(CURL_GLOBAL_ALL);
	CURLcode res;
	CURL *curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, req);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) answer);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //Возможно небезопасно!!
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		if (login) {
			curl_easy_setopt(curl, CURLOPT_USERNAME, login);
		}
		if (password) {
			curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
		}

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			ct_log_error("curl_easy_perform() failed: %s %d", curl_easy_strerror(res), res);
		}

		curl_easy_cleanup(curl);
	}

	curl_global_cleanup();

	return answer;
}

ct_buffer_t *ct_load_file(const char *req)
{
	return ct_load_file_with_auth(req, NULL, NULL);
}

typedef struct {
	struct curl_httppost *post;
	struct curl_httppost *last;
} foreach_args_t;

static void foreach_func(const char *param_name, const ct_buffer_t *param_data, ct_type_t ct_type, void *user_args)
{
	foreach_args_t *foreach_args = user_args;

	switch (ct_type) {
		case ct_type_default:
			curl_formadd(&foreach_args->post, &foreach_args->last,
			             CURLFORM_PTRNAME, param_name,
			             CURLFORM_PTRCONTENTS, ct_buffer_get_data(param_data),
			             CURLFORM_END);
			break;

		case ct_type_image_jpeg:
			ct_log_info("ct_type_image_jpeg %zu", ct_buffer_get_size(param_data));
			curl_formadd(&foreach_args->post, &foreach_args->last,
			             CURLFORM_PTRNAME, param_name,
			             CURLFORM_BUFFER, "image/jpeg",
			             CURLFORM_BUFFERPTR, ct_buffer_get_data(param_data),
			             CURLFORM_BUFFERLENGTH, ct_buffer_get_size(param_data),
			             CURLFORM_END);
			break;
	}
}

json_t *ct_post(const char *req, ct_param_list_t *params)
{
	ct_buffer_t *answer = ct_buffer_create();

	const char *header = "Content-Type: multipart/form-data";
	struct curl_slist *headerlist = NULL;
	headerlist = curl_slist_append(headerlist, header);

	foreach_args_t foreach_args;
	foreach_args.last = NULL;
	foreach_args.post = NULL;

	curl_global_init(CURL_GLOBAL_ALL);
	CURLcode res;
	CURL *curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
		curl_easy_setopt(curl, CURLOPT_URL, req);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data_cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) answer);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //Возможно небезопасно!!

		ct_param_list_foreach(params, foreach_func, &foreach_args);
		curl_easy_setopt(curl, CURLOPT_HTTPPOST, foreach_args.post);

		res = curl_easy_perform(curl);

		ct_param_list_free(params);

		if (res != CURLE_OK) {
			ct_log_error("curl_easy_perform() failed: %s %d", curl_easy_strerror(res), res);
		}

		long status_code = 0;
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);

		if (status_code < 200 || status_code > 299) {
			ct_log_error("request receive error %ld: %s", status_code, ct_buffer_get_data(answer));
		}

		curl_easy_cleanup(curl);
		curl_formfree(foreach_args.post);
		curl_slist_free_all (headerlist);
	}

	curl_global_cleanup();

	json_error_t error;
	json_t *result = json_loadb(ct_buffer_get_data(answer), ct_buffer_get_size(answer), JSON_DECODE_ANY, &error);
	ct_buffer_free(answer);

	if (result == NULL){
		ct_log_error("json_loadb error: '%s'", error.text);
	}

	return result;
}
