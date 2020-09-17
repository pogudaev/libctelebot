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

#include <ct_common.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LOG_LENGTH 1024

static log_print_function_t _log_print_function = NULL;

void ct_log_print(int priority, const char *file, long line, const char *__restrict format, ...)
{
	if (!_log_print_function) {
		return;
	}

	const char *f = strrchr(file, '/');

	if (f) {
		f++;
	} else {
		f = file;
	}

	char log_buffer[MAX_LOG_LENGTH];
	snprintf(log_buffer, MAX_LOG_LENGTH, "[%s:%ld] ", f, line);

	size_t fill = strlen(log_buffer);

	char *mess = log_buffer + fill;

	va_list(args);
	va_start(args, format);
	vsnprintf(mess, MAX_LOG_LENGTH - fill - 1, format, args);
	strcat(mess, "\n");
	(*_log_print_function)(priority, "%s", log_buffer);
}

void ct_set_log_print_function(log_print_function_t log_print_function)
{
	_log_print_function = log_print_function;
}
