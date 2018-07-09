#include "stm32f10x_conf.h"
#include "Led.h"
#include "Comm.h"
#include "Watchdog.h"

#include "Key.h"

static void IO_init(void);

void Key_init()
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	IO_init(); //������Ӧ��IO�ڳ�ʼ��
 
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);//PE0 ���ӵ��ж���0
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);//PE1 ���ӵ��ж���1

    /* ����EXTI_Line4 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;//LINE0
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش��� 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE4
    EXTI_Init(&EXTI_InitStructure);//����

    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;//�ⲿ�ж�0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//������3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);//����

    /* ����EXTI_Line5 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);//����

    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�2
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;//�����ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);//����
}    

void IO_init()
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);//PIOEʱ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5 ; //KEY0 KEY1��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}


void EXTI4_IRQHandler(void)
{
    EXTI_ClearFlag(EXTI_Line4);
    LED_warning();
}

void EXTI9_5_IRQHandler(void)
{
    EXTI_ClearFlag(EXTI_Line5);
    //Reboot();
    Comm_send(0x20);
}



