#ifndef __METER_H
#define __METER_H

#include "stm32f10x_conf.h"

/*
���ݸ�ʽ 
O ������
C �⼤��
D ���
S �鿴״̬
*/

#define METER_RATE 19200    //������

void Meter_init(void);
void Meter_run(void);
void Meter_stop(void);
void Meter_status(void);

#endif


