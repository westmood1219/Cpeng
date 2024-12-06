/*********************************************************************************************************
* 模块名称: Main.c
* 摘    要: 主文件，包含初始化函数和main函数
* 当前版本: 1.0.0
* 作    者: Leyutek(COPYRIGHT 2018 - 2021 Leyutek. All rights reserved.)
* 完成日期: 2022年2月1日
* 内    容: 
* 注    意: 
**********************************************************************************************************
* 取代版本: 
* 作    者: 
* 完成日期: 
* 修改内容: 
* 修改文件: 
*********************************************************************************************************/
/*********************************************************************************************************
*                                              包含头文件
*********************************************************************************************************/
#include <reg52.h>

/*********************************************************************************************************
*                                              宏定义
*********************************************************************************************************/
sbit LED1 = P2^4; //定义LED1

/*********************************************************************************************************
*                                              枚举结构体定义
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                              内部函数声明
*********************************************************************************************************/
static void InitInterrupt(void);
static void InitTimer0(void);

/*********************************************************************************************************
*                                              内部函数实现
*********************************************************************************************************/
/*********************************************************************************************************
* 函数名称: InitInterrupt
* 函数功能: 配置中断
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2022年2月1日
* 注    意: 
*********************************************************************************************************/
static void InitInterrupt()
{
  ET0 = 1;   //打开 定时器0 中断允许
  EA  = 1;   //打开 总中断允许
}

/*********************************************************************************************************
* 函数名称: InitTimer0
* 函数功能: 配置定时器0
* 输入参数: nms-延迟时间（毫秒）
* 输出参数: void
* 返 回 值: void
* 创建日期: 2022年2月1日
* 注    意: 
*********************************************************************************************************/
static void InitTimer0()
{
  TMOD = 0x01;  //设置 定时器0 工作模式1（16位定时器）
  TH0  = 0xFC;  //设置 定时器0 计数初值高8位
  TL0  = 0x18;  //设置 定时器0 计数初值低8位，定时1ms后溢出
  TR0  = 1;     //打开 定时器0  
}

/*********************************************************************************************************
* 函数名称: main
* 函数功能: 主函数
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2022年2月1日
* 注    意: 
*********************************************************************************************************/
void main()
{ 
  InitInterrupt();  //配置中断
  InitTimer0();     //配置定时器0
  while (1)
  {

  }
}

/*********************************************************************************************************
* 函数名称: Timer0_Handler
* 函数功能: 定时器/计数器0中断服务函数
* 输入参数: void
* 输出参数: void
* 返 回 值: void
* 创建日期: 2022年2月1日
* 注    意: 
*********************************************************************************************************/
void Timer0_Handler() interrupt 1
{
  static unsigned int s_iCounter;  //定义静态变量s_iCounter作为计数变量
  TH0 = 0XFC;                      //重新设置 定时器0 计数初值高8位 
  TL0 = 0X18;                      //重新设置 定时器0 计数初值低8位，定时1ms后溢出
  
  s_iCounter++;                    //每次进入一次中断，计数变量加1
  if(s_iCounter >= 1000)           //当计数变量达到1000时，即1000ms
  {
    s_iCounter = 0;                //计数变量清零
    LED1 = ~LED1;                  //翻转LED1开关状态
  }
}
