#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

/*表达式求值的顺序一部分是由运算符的优先级决定的，另一部分是由结合性决定的。
同时，有些表达式的操作数在求值过程中可能需要转换为另一种类型。*/

//int main()
//{
//    //优先级
//    int a = 2 + 6 / 3;//2 + (6 / 3) = 4
//    //结合性
//    int b = 2 + 6 % 3;//(2 + 6) % 3 = 2
//    //结合性概念：表达式中具有相同优先级的运算符的结合性是从左到右的
//    return 0;
//}

//隐式类型转换(以整形转换为例)
// 定义:在表达式中，如果参与运算的两个操作数类型不一致，那么系统会自动将低类型转换为高类型，然后进行运算。
//int main()
//{
//    int a = 5;
//    int b = 126;
//    char c = a + b;
//    //计算过程：5：00000000 00000000 00000000 00000101
//    //126：       00000000 00000000 00000000 01111110
//    //相加：      00000000 00000000 00000000 10000011//注意输出的是源码所以要转化如下↓
//    // 补码到源码：10000000 00000000 00000000 01111101
//    //截断：       10000011（首位为1，高位补零，因而为负数）
//    //printf("%c\n", c);//输出为？，因为-125 不在标准 ASCII 打印字符的范围内
//    printf("%d\n", c);//输出为-125
//    return 0;
//}
/*//负数的整形提升char cl =-1;
变量c1的二进制位（补码）中只有8个比特位：1111111
因为char为有符号的char
所以整形提升的时候，高位补充符号位，即为1提升之后的结果是：
111111111111111111111111111111
//正数的整形提升char c2 1;
变量c2的二进制位（补码）中只有8个比特位：00000001
因为char为有符号的char
所以整形提升的时候，高位补充符号位，即为0提升之后的结果是：
00000000000000000000000000000001
无符号数整形提升，高位补零。*/

////例子1：
//int main()
//{
//    char a = 0xb6;//10110110
//    short b = 0xb600;//1011011000000000
//    int c = 0xb6000000;//10110110000000000000000000000000
//
//    if (a == 0xb6)//可以看作一个表达式，a被提升为int类型
//        printf("a");
//    if (b == 0xb600)
//        printf("b");
//    if (c == 0xb6000000)
//        printf("c");
//    return 0;
//}
//例子二：
//int main()
//{
//    char c = 1;
//    printf("%u\n", sizeof(c));//1
//    printf("%u\n", sizeof(+c));//4
//    printf("%u\n", sizeof(-c));//4
//    //只要在表达式里面，char类型会被提升为int类型
//    return 0;
//}

//操作符的优先级
//相邻优先级的操作符，结合性是从左到右
// eg1:
//int fun()
//{
//    static int count = 1; 
//    return ++count;
//}
//int main()
//{
//    int answer;
//    answer = fun() - fun() * fun();//会不知道先调用哪一个函数,在不同编译器里面结果不同
//    printf("%d\n", answer);//输出多少？
//    return 0;
//}
//eg2:
//int main()
//{
//    int a = 1;
//    int b = (++a)+(++a)+(++a);//vs2022是先把所有(++a)都运行一遍再执行加和,linus是运行前两个++a就加,然后再++a再加和
//    printf("%d\n", b);//输出多少？
//    return 0;
//}