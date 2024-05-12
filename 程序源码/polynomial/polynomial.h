#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <string>
#include <cstring>
#include <math.h>
#include <QString>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <conio.h>
#include <process.h>
#include <fstream>

#define MAX 100
using namespace std;

template<typename T>
struct polynomial {
    T Coefficient;
    int index;
    polynomial* next;
};

class calculator {
public:
    calculator();
    //检查输入格式是否符合规范
    //bool check(QString strr);

    //获取每项系数
    double GetCoefficient(char *str);

    //每项输入进入多项式链表中
    template<typename T>
    void push(polynomial<T> *head, T Coefficient, int index);

    //最核心的函数：将输入字符转化为链式的数据结构
    QString GetPolynomialList(QString a, int choose);

    //合并同类型
    template<typename T>
    void CombineSort(polynomial<T> *head);

    //删除指定系数和指数的项
    template<typename T>
    void del(polynomial<T> *DLList1, double Coefficient, int index);

    //升幂排序
    template<typename T>
    void sort(polynomial<T> *DLList1);

    //反转链表
    template<typename T>
    void Inverselist(polynomial<T> *DLList1);

    //将链表末端置空
    template<typename T>
    void Q(polynomial<T> *Ac);

    //定积分函数
    template<typename T>
    double numericalIntegration(polynomial<T> *poly, int down, int up);

    //选择运算方式
    template<typename T>
    QString Algorithm(int mode);

    //格式化输出运算结果
    template<typename T>
    QString Print(polynomial<T> *abc);

    int down=2;
    int up=4;

private:
    polynomial<double>* Aa;
    polynomial<double>* Bb;
    polynomial<double>* Cc;
};


#endif // POLYNOMIAL_H
