/*
 * types.h
 *
 *  Created on: Sep 8, 2016
 *      Author: Jay Chung
 */

#ifndef TYPES_H_
#define TYPES_H_

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>

#define icscm_bitfield	uint16_t

#define int8  	uint8_t
#define int16 	unsigned short
#define int32	unsigned int
#define int64	unsigned long long

#define int8s	char
#define int16s	short
#define int32s	int
#define int64s	long long

#define icscm_uint8		uint8_t
#define icscm_uint16	int16
#define icscm_uint32	int32
#define icscm_uint64	int64

#define icscm_int8		int8s
#define icscm_int16		int16s
#define icscm_int32		int32s
#define icscm_int64		int64s

#define icscm_float32	float
#define icscm_float64	long double

#ifndef bool
#define bool	int16
#endif

#define POINTERS_ARE_32BITS

#endif /* TYPES_H_ */
