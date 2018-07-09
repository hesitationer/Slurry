#include "Laser.h"


void Laser_init()
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//ʹ��ʱ��

    //GPIOF9,F10��ʼ������
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

    GPIO_ResetBits(GPIOB, GPIO_Pin_5);//�ر�
}

void Laser_off()
{
	GPIO_SetBits(GPIOB, GPIO_Pin_5);    
}

void Laser_on()
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
}

void Laser_tog()
{
    if(GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_5))
    {
      	GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    }else
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_5);
    }
}
