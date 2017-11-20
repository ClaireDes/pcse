#include <segment.h>
#include <inttypes.h>
#include <stdio.h>

#define ADDR_IT 0x1000

extern void init_traitant_IT(uint32_t num_IT, void (*traitant)(void));
