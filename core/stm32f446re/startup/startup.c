#include "startup.h"

void Default_Handler(void) {
  while (1)
    ;
}

void Default_Handler_Loop(void) {
  // do nothing
}

void *memcpy(void *dest, const void *src, uint16_t n)
{
    for (uint16_t i = 0; i < n; i++)
    {
        ((char*)dest)[i] = ((char*)src)[i];
    }
}

void  *memset(void *b, int c, int len)
{
  int           i;
  unsigned char *p = b;
  i = 0;
  while(len > 0)
    {
      *p = c;
      p++;
      len--;
    }
  return(b);
}

/*
    1)  copy .data section to sram
    2)  init the .bss section to 0x0 sram
    3)  call init function of init library (if used)
    4)  call main()
*/
void Reset_Handler(void) {
  uint32_t size = 0;

  size = (uint32_t)&_edata - (uint32_t)&_sdata;
  uint8_t *pDst = (uint8_t *)&_sdata;
  uint8_t *pSrc = (uint8_t *)&_la_data;
  for (uint32_t i = 0; i < size; i++) {
    *pDst++ = *pSrc++;
  }

  size = (uint32_t)&_ebss - (uint32_t)&_sbss;
  pDst = (uint8_t *)&_sbss;
  for (uint32_t i = 0; i < size; i++) {
    *pDst++ = 0;
  }

  _text_size = (uint32_t)&_etext - (uint32_t)&_stext;
  _data_size = (uint32_t)&_edata - (uint32_t)&_sdata;
  _bss_size = (uint32_t)&_ebss - (uint32_t)&_sbss;

  main();
}