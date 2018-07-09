#include "Led.h"
#include "Comm.h"
#include "Meter.h"
 
void Meter_timer_init(void);
void Meter_init(){
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��

    //GPIO�˿����� ʹ�ܴ���1��Ӧ���Ÿ���ӳ��
//    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIOA2����ΪUSART2
//   GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIOA3����ΪUSART2

    //USART2�˿����� �˴���������Ҫ��д
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD ;//��©���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA10
    

    //Usart2 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;   //����2�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 1;     //��ռ���ȼ�1
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ�� NVIC

    //USART2 ��ʼ��
    USART_InitStructure.USART_BaudRate = METER_RATE;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;   //��У��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure); //��ʼ������2
    USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���2
    USART_OverSampling8Cmd (USART2, DISABLE);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ж�

    Meter_timer_init();
}

void Meter_timer_init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  ///ʹ��TIM3ʱ��

    TIM_TimeBaseInitStructure.TIM_Period = 3000; 	//���Ͳ����źŵļ��
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200-1;  //��ʱ����Ƶ
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV2; 

    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//��ʼ��

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //��ʱ��11�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
    
    TIM_ClearFlag(TIM7, TIM_FLAG_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
    USART_SendData(USART2, 'D');
    LED_tog();
}

void USART2_IRQHandler(void) 
{

    if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET && 
        USART_GetFlagStatus(USART2, USART_FLAG_NE | USART_FLAG_FE |USART_FLAG_PE) == RESET)
    {
        u16 byte16 = USART_ReceiveData(USART2);   //(USART2->DR) ��������־λ
		u8 byte = *((u8*)&byte16);     //little endian
        Comm_send(byte);
    }else
    {
           u16 byte16 = USART_ReceiveData(USART2);   //(USART2->DR) ��������־λ
    }
}

void Meter_stop()
{
    USART_SendData(USART2, 'C');
    TIM_Cmd(TIM3,DISABLE);    
}

void Meter_run()
{
    USART_SendData(USART2, 'O');
    TIM_Cmd(TIM3,ENABLE);
}

void Meter_status()
{
    TIM_Cmd(TIM3,DISABLE);
    USART_SendData(USART2, 'S');
}
