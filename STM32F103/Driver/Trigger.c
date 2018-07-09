#include "Trigger.h"

void Trigger_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   //ʹ��ʱ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��

    GPIO_ResetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_8);    //��
}
    
void Trigger1_on(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_8);    //��   
}    

void Trigger1_off(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);    //��
}    

void Trigger2_on(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_6);    //��
}

void Trigger2_off(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);    //��
}

void Tribot_off(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_9);    //��
}

void Tribot_on(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_9);    //��
}
