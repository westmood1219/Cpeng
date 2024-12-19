#include "Com_Util.h"
#include <REG52.H>

sbit LED1 = P2 ^ 4;
sbit KEY1 = P3 ^ 2;
sbit KEY2 = P3 ^ 3;
sbit SegmentG1 = P2^3;
sbit SegmentG2 = P2^2;
sbit SegmentG3 = P2^1;
sbit SegmentG4 = P2^0;

static u16 s_iDuty = 100;//初始状态灯不亮

const unsigned char arrNumber[] = {0x03, 0x9f, 0x25, 0x0d, 0x99, 0x49, 0x41, 0x1f, 0x01, 0x09};


static void InitInterrupt()
{
    ET0 = 1;
    EA  = 1;

    EX0 = 1;
    IT0 = 1;//下降沿
    EX1 = 1;
    IT1 = 1;//下降沿

    IP = 0x05;//外部中断为高优先级
}

static void InitTimer0()
{
    TMOD = 0x02;
    TH0  = 0X9C;
    TL0  = 0X9C;
    TR0  = 1;
}

static void DelayNms(int nms)
{
    unsigned int i,j;
    for(i = 0; i < nms; i++)
        for(j = 0; j < 123; j++);
}

void main()
{
    u8 thousands, hundreds, tens, ones;
    InitInterrupt();
    InitTimer0();
    while(1)
    {
        thousands = s_iDuty / 1000;
        hundreds = (s_iDuty / 100) % 10;
        tens = (s_iDuty / 10) % 10;
        ones = s_iDuty % 10;
        
        // 显示千位
        P0 = arrNumber[thousands];
        SegmentG1 = 0;
        DelayNms(1);
        SegmentG1 = 1;
        // 显示百位
        P0 = arrNumber[hundreds];
        SegmentG2 = 0;
        DelayNms(1);
        SegmentG2 = 1;
        
        // 显示十位
        P0 = arrNumber[tens];
        SegmentG3 = 0;
        DelayNms(1);
        SegmentG3 = 1;
        
        // 显示个位
        P0 = arrNumber[ones];
        SegmentG4 = 0;
        DelayNms(1);
        SegmentG4 = 1;
    }
}

void External0_Handler() interrupt 0
{
    while (KEY1 == 0);
    s_iDuty += 10;//每次亮度暗10%
}

void External1_Handler() interrupt 2
{
    while (KEY2 == 0);
    s_iDuty -= 10;
}

void Timer0_Handler() interrupt 1
{
    static u16 s_iCnt = 0;
    s_iCnt++;
    if (s_iCnt >= 100)
    {
        s_iCnt = 0;
    }

    if (s_iCnt <= s_iDuty)
    {
        LED1 = 1;
    }
    else
    {
        LED1 = 0;
    }
}