#pragma once

#ifndef SBRK_SBRK_H
#define SBRK_SBRK_H

#include "def.h"

void *my_brk(void *end_data_segment);

void *my_sbrk(intptr_t increment);

#endif //SBRK_SBRK_H
