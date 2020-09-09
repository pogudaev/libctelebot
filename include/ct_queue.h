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

#ifndef CT_QUEUE_H
#define CT_QUEUE_H

struct ct_queue_s;
typedef struct ct_queue_s ct_queue_t;
typedef void (*free_function_t)(void *);

ct_queue_t *ct_queue_create(void);
void ct_queue_free(ct_queue_t *ct_queue);
void ct_queue_set_free_function(ct_queue_t *ct_queue, free_function_t free_function);

void ct_queue_push(ct_queue_t *ct_queue, void *object);
void *ct_queue_pull(ct_queue_t *ct_queue);

void ct_queue_erase(ct_queue_t *ct_queue);





#endif // CT_QUEUE_H
