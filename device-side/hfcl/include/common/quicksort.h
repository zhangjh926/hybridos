/*
** HFCL - HybridOS Foundation Class Library
**
** Copyright (C) 2018 Beijing FMSoft Technologies Co., Ltd.
**
** This file is part of HFCL.
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef HFCL_COMMON_QUICKSORT_H_
#define HFCL_COMMON_QUICKSORT_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef int (*Compare)(const void *, const void *);

void quickSort(void* base, unsigned num, unsigned width, Compare comp);

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif  // HFCL_COMMON_QUICKSORT_H_

