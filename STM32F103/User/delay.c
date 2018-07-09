#include "stm32f10x.h"
#include "delay.h"

static volatile u32 us_count;

void Delay_init(void)
{
    SysTick_Config(SystemCoreClock / 1000000);
// 	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); 
	us_count = 0;
}								    

 
 
//systick�жϷ�����,ʹ��OSʱ�õ�
void SysTick_Handler(void)
{
    if(us_count)
    {
        us_count --;
    }
}

void Delay_us(u32 us)
{
    SysTick->VAL=0x00; 
    us_count = us;
    while(us_count)
        __NOP();
    /*
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 				//ʱ�����	  		 
	SysTick->VAL=0x00;        				//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ; //��ʼ���� 	 
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk; //�رռ�����
	SysTick->VAL =0X00;       				//��ռ����� 
    */
}


void Delay_ms(u32 ms)
{	 	 
    while(ms--)
    {
        Delay_us(1000);
    }
} 
