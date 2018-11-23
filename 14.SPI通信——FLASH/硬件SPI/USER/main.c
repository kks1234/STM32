#include "spi_flash.h"
#include "usart.h"
u32 flash_id;

u8 readbuf[4096];
u8 writebuf[4096];
u32 i;


int main()
{
	uart_init(115200);
	spi_init();
	
	printf("spi≤‚ ‘≥Ã–Ú\r\n");
	
	flash_id=flash_read_id();
	
	printf("ID : %X\r\n",flash_id);
	
	printf("Sector Erase\r\n");
	
	for(i=0;i<4096;i++)
		writebuf[i] = i;
	
	flash_sector_erase(0);
	
	flash_write_buf(0,writebuf,4096);  
	flash_read_buf(0,readbuf,4096);
	
	for(i=0;i<4096;i++)
	{
		printf("0X%X  ",readbuf[i]);
		if(i%10 == 0)
			printf("\r\n");
	}
	
	while(1)
	{	
	}	
}





