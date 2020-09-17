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

#ifndef CT_COMMON_H
#define CT_COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <syslog.h>

typedef void (*log_print_function_t)(int, const char *, ...);

/**
 * @brief ct_set_log_print_function устанавливает функцию для логирования
 * @param log_print_function - callback вызываемый для записи логов
 */
void ct_set_log_print_function(log_print_function_t log_print_function);

/**
 * @brief ct_log_print печать в лог
 * @param priority приоритет
 * @param file файл
 * @param line строка в файле
 * @param format форматная строка с последущими аргументами
 * @note не рекомендуется к прямому использованию. Правильнее будет использовать макросы ct_log_debug, ct_log_info и т.д.
 */
void ct_log_print(int priority, const char *file, long line, const char *__restrict format, ...);

#define ct_log_debug(...)      ct_log_print(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define ct_log_info(...)      ct_log_print(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define ct_log_notice(...)      ct_log_print(LOG_NOTICE, __FILE__, __LINE__, __VA_ARGS__)
#define ct_log_warning(...)      ct_log_print(LOG_WARNING, __FILE__, __LINE__, __VA_ARGS__)
#define ct_log_error(...)      ct_log_print(LOG_ERR, __FILE__, __LINE__, __VA_ARGS__)
#define ct_log_crit(...)      ct_log_print(LOG_CRIT, __FILE__, __LINE__, __VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // CT_COMMON_H

