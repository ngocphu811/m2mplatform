#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdint.h>
#include <stdbool.h>

/* Small functions in header file for efficient inlining. */


/* Rounding integer division for positive numbers
 * a/b + 0.5 = (a + b/2) / b                       */
static inline unsigned int round_div(unsigned int a, unsigned int b)
{
	return (a + b/2) / b;
}

/* Ceiling integer division for positive numbers
 * ceil(a/b) = (a + b - 1) / b                       */
static inline unsigned int ceil_div(unsigned int a, unsigned int b)
{
        return (a + b - 1) / b;
}

/* Compile-time assert */
#define ct_assert(e) ((void)sizeof(char[1 - 2*!(e)]))

/* Prevent compiler from optimizing away a memory access.
 * Used to reset flags for USART/SPI by reading status register. */
#define always_read(x) asm(""::"r"(x))

/* Ordinary MAX() and MIN() macros */
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define ABS(x) ((x) >= 0 ? (x) : (-x))

/* Bit-banding access to single bits. */
#define BITBAND_ACCESS(variable, bitnumber) \
    *(uint32_t*)(((uint32_t)&variable & 0xF0000000) \
            + 0x2000000 \
            + (((uint32_t)&variable & 0x000FFFFF) << 5) \
            + (bitnumber << 2))

#define set_bit(variable, bitmask) \
    BITBAND_ACCESS(variable, __builtin_ctz(bitmask)) = 1

#define clear_bit(variable, bitmask) \
    BITBAND_ACCESS(variable, __builtin_ctz(bitmask)) = 0


#endif