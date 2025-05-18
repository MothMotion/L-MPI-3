#pragma once
#ifndef VEC_OPER_H
#define VEC_OPER_H

#include "config.h"

#include <stdint.h>
#include <stddef.h>

void Summ(arr_t* arr1, arr_t* arr2, arr_t* arr_out, const uint32_t size);
void Diff(arr_t* arr1, arr_t* arr2, arr_t* arr_out, const uint32_t size);
void Mult(arr_t* arr1, arr_t* arr2, arr_t* arr_out, const uint32_t size);
void Div(arr_t* arr1, arr_t* arr2, arr_t* arr_out, const uint32_t size);

#endif // !VEC_OPER_H
