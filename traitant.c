#include <traitant.h>

void init_traitant_IT(uint32_t num_IT, void (*traitant)(void)) {
  uint32_t *ptr = (uint32_t*) ADDR_IT;
  ptr += num_IT*2;
  *ptr = KERNEL_CS<<16 | (0xffff & (uint32_t) traitant);
  ptr ++;
  *ptr = (0xffff0000 & (uint32_t) traitant) | 0x8e00;
}
