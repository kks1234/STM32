#include "stm32f10x.h"
#include "dma.h"
#include "usart.h"


extern u8 buff[SIZEBUFF];

u8 bu[] = "DMA´®¿Ú·¢ËÍ²âÊÔ\r\n";

int main()
{
	u32 i;
	for(i=0 ; i<SIZEBUFF ; i++)
	{
		buff[i] = bu[i%(sizeof(bu))];
	}
	uart_init(115200);
	dma_init();
	dma_goon();
	while(1);
}





