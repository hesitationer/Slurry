#include "Led.h"
#include "Laser.h"
#include "Trigger.h"
#include "Comm.h"
 
	
u8 RX_BUF[COMM_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
volatile u8 debug_byte;
volatile u8 debug_step;
void cmd_protocol(void);

void Comm_init(){
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��

    //GPIO���Ÿ���ӳ��
 // GPIO_PinRemapConfig  (GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //GPIOA9����ΪUSART1
 // GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //GPIOA10����ΪUSART1

    //USART1�˿�����
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD ;//��©���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;//��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA10
    
    //USART1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   //����1�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 3;     //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//�����ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ�� NVIC

    //USART1 ��ʼ��
    USART_InitStructure.USART_BaudRate = COMM_RATE;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_9b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_Even;   //żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
    USART_OverSampling8Cmd (USART1, DISABLE);
    //USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ж�	
}


void USART1_IRQHandler(void) 
{
    u8 byte;
    static int step = 0;
    
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET && 
        USART_GetFlagStatus(USART1, USART_FLAG_NE | USART_FLAG_FE |USART_FLAG_PE) == RESET)
    {
        u16 byte16 = USART_ReceiveData(USART1);   //(USART1->DR) ��������־λ
		byte = *((u8*)&byte16);     //little endian
        debug_byte = byte;
        switch(step)
        {
            case 0:
                if(byte == COMM_HEAD_MAGIC)
                {
                    step = 1;
                }
            break;
            
            case 1:
                RX_BUF[0] = byte;
                step ++;
            break;
            
            case 2:
                RX_BUF[1] = byte;
                step ++;
            break;
            

            case 3:
                RX_BUF[2] = byte;
                    step++;
/*                if(byte == RX_BUF[1])
                {
                    RX_BUF[2] = byte;
                    step++;
                }else
                {
                    step = 0;
                }*/
            break;
            
            case 4:
               if(byte == RX_BUF[0])
                {
                    RX_BUF[3] = byte;
                    step++;
                }else
                {
                    step = 0;
                }
            break;            
             
            case 5:
               if(byte == (RX_BUF[0] ^ RX_BUF[1]))
                {
                    //Good Data Received
                    cmd_protocol();    
                }
                step = 0;
                break;
                
            default:
                if(byte == COMM_HEAD_MAGIC)
                {
                    step = 1;
                }else
                {
                    step = 0;
                }
        }    
        debug_step = step;
    }else
    {
           u16 byte16 = USART_ReceiveData(USART1);   //(USART1->DR) ��������־λ
    }
}

void Comm_send(u8 dat)
{
    USART_SendData(USART1, dat);
}
