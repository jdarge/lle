#pragma once

#ifndef LLE_SBRK_H
#define LLE_SBRK_H

#include "def.h"

void *brk(void *end_data_segment);

void *sbrk(intptr_t increment);

#endif
