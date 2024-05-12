#include "widget.h"
#include "ui_widget.h"
#include"polynomial.h"
#include <QString>
calculator::calculator() {
    Aa = new polynomial<double>;
    Bb = new polynomial<double>;
    Cc = new polynomial<double>;
}

//找到链表尾部并置空
template<typename T>
void calculator::Q(polynomial<T> *Ac)
{
    polynomial<T> *p,*q;
    p=Ac;
    while (p->next!=nullptr)
    {
        q=p->next;
        p->next=q->next;
        free(q);
    }
    Ac->next=nullptr;
}

//获取每项前面的系数
QString calculator::GetPolynomialList(QString strr , int choose)
{
    if(choose == 1)
    {
        Aa->next = nullptr;
        int i=0;
        double Coefficient;
        int index = 0;
        char str[MAX];

        string strA = string(strr.toLocal8Bit());
        strcpy(str, strA.c_str());

        while(*(str+i))
        {
            Coefficient=GetCoefficient(str+i);
            if(*(str+i)!='x')
                i++;
            while((*(str+i)>='0'&&*(str+i)<='9')||(*(str+i)=='.'))
                i++;
            if(*(str+i)=='+'||*(str+i)=='-'||*(str+i)=='\0')
                index=0;
            else
            {
                if(*(str+i)=='x')
                {
                    i++;
                    if(*(str+i)=='+'||*(str+i)=='-'||*(str+i)=='\0')
                        index=1;
                    else
                        if(*(str+i)=='^')
                        {
                            i++;
                            index=(int)GetCoefficient(str+i);
                            while((*(str+i)>='0'&&*(str+i)<='9')||(*(str+i)=='.'))
                                i++;
                        }
                }
            }
            push(Aa,Coefficient,index);
            CombineSort(Aa);
        }
        return Print(Aa);
    }
    else
    {
        Bb->next = nullptr;
        int i=0;
        double Coefficient;
        int index = 0;
        char str[MAX];

        string strA = string(strr.toLocal8Bit());
        strcpy(str, strA.c_str());

        //if(!check(str)) return strr;
        Coefficient=GetCoefficient(str+i);
        while(*(str+i))
        {
            Coefficient=GetCoefficient(str+i);
            if(*(str+i)!='x')
                i++;
            while((*(str+i)>='0'&&*(str+i)<='9')||(*(str+i)=='.'))
                i++;
            if(*(str+i)=='+'||*(str+i)=='-'||*(str+i)=='\0')
                index=0;
            else
            {
                if(*(str+i)=='x')
                {
                    i++;
                    if(*(str+i)=='+'||*(str+i)=='-'||*(str+i)=='\0')
                        index=1;
                    else
                        if(*(str+i)=='^')
                        {
                            i++;
                            index=(int)GetCoefficient(str+i);
                            while((*(str+i)>='0'&&*(str+i)<='9')||(*(str+i)=='.'))
                                i++;
                        }
                }
            }
            push(Bb,Coefficient,index);
            CombineSort(Bb);
        }
    return Print(Bb);
    }
}

//按照格式输出多项式链
template<typename T>
QString calculator::Print(polynomial<T> *abc) {
    polynomial<T> *p;
    p = abc;
    QString s = "";
    //安全性检查
    if (p->next == nullptr)
        return s;
    if (p->next->Coefficient == 0) {
        s += "0";
        return s;
    } else {//拼接每项的系数和指数
        while (p->next) {
            p = p->next;
            if (p->Coefficient == 0)
                continue;

            if (p->Coefficient == 1 || p->Coefficient == -1) {
                if (p->index == 0) {
                    s += QString::number(p->Coefficient);
                    continue;
                }
                if (p->Coefficient == -1 && p->index != 0)
                    s += "-";
            } else
                s += QString::number(p->Coefficient);
            if (p->index > 0) {
                s += "x";
                if (p->index > 1)
                    s += "^" + QString::number(p->index);
            }
            if (p->next != nullptr) {
                if (p->next->Coefficient > 0)
                    s += "+";
            }
        }
        return s;
    }
}

//合并指数相同的数据，根据指数排序
template<typename T>
void calculator::CombineSort(polynomial<T> *head)
{
    polynomial<T> *p,*q;
    p=head;

    while(p->next)
    {
        q=p->next;
        while(q->next!= nullptr)
        {
            if(p->next->index == q->next->index)
            {
                p->next->Coefficient = q->next->Coefficient+p->next->Coefficient;
                del(head,q->next->Coefficient,q->next->index);

            }
            else
                q=q->next;
        }
        p=p->next;
    }
    //进行升幂排序
    sort(head);
    //转置，实现降幂
    Inverselist(head);
}

//将系数指数存储在链表中
//void calculator::push(polynomial<T> *head, T Coefficient, int index)
template<typename T>
void calculator::push(polynomial<T> *head,T Coefficient,int index)
{
    polynomial<T> *L = nullptr;
    polynomial<T> *p = nullptr;
    L = head;
    while (L->next != nullptr)
        L = L->next;
    p = new polynomial<T>;
    p->Coefficient = Coefficient;
    p->index=index;
    p->next = nullptr;
    L->next = p;
}

//返回系数
double calculator::GetCoefficient(char *str)
{
    double s=0.0;
    double d=10.0;
    bool falg=false;
    while(*str==' ')
    {
        str++;
    }
    if(*str=='-')//记录数字正负
    {
        falg=true;
        str++;
        if(*str=='x')
            return -1.0;
    }
    else
        if((*str=='+'&&*(str+1)=='x')||(*str=='x'))
        {
            return 1.0;
        }
    if(*str=='+'&&(*(str+1)>='0'&&*(str+1)<='9'))str++;
    if(!(*str>='0'&&*str<='9'))//如果一开始非数字则退出，返回
        return s;
    while(*str>='0'&&*str<='9'&&*str!='.')//计算小数点前整数部分
    {
        s=s*10.0+*str-'0';
        str++;
    }
    if(*str=='.')//以后为小数部分
        str++;
    while(*str>='0'&&*str<='9')//计算小数部分
    {
        s=s+(*str-'0')/d;
        d*=10.0;
        str++;
    }
    return s*(falg?-1.0:1.0);
}


template<typename T>
void calculator::sort(polynomial<T>  *DLList1) // 直接插入排序
{
    polynomial<T>  *p,*q,*r;
    polynomial<T>  heah; // 创建头结点
    p=&heah;
    heah.next=nullptr;
    p=DLList1;
    DLList1->index=0; // 设置头结点的指数和系数为0
    DLList1->Coefficient=0;
    if(p->next==nullptr||p->next->next==nullptr) // 如果链表为空或只有一个元素，则直接返回
        return;
    for(p=p->next->next;p!=nullptr;p=p->next) // 遍历
    {
        DLList1->index=p->index; // 保存
        DLList1->Coefficient=p->Coefficient;
        q=DLList1;
        while(q->next!=p)q=q->next;
        while(DLList1->index<q->index) // 如果当前节点的指数小于前一个节点的指数
        {
            q->next->index=q->index;
            q->next->Coefficient=q->Coefficient;
            r=q; // 保存
            q=DLList1;
            while(q->next!=r)q=q->next;
        }
        q->next->index=DLList1->index;
        q->next->Coefficient=DLList1->Coefficient;
    }
}

//删除特点结点
template<typename T>
void calculator::del(polynomial<T>  *DLList1,double Coefficient,int index)
{
    polynomial<T>  *p,*q;
    p=DLList1;
    while(p->next)
    {
        if(p->next->index==index && p->next->Coefficient == Coefficient)
            break;
        p=p->next;
    }
    if(p->next&&p->next->index == index && p->next->Coefficient == Coefficient)
    {
        q=p->next;
        if(q->next)
        {
            p->next=q->next;//p->next存在
        }
        else
        {
            p->next=nullptr;//q->next是nullptr
        }
        free(q);
    }
}

//反转链表
template<typename T>
void calculator::Inverselist(polynomial<T>  *DLList1)//逆置
{
    polynomial<T>  *p,*q,*heah;
    heah=DLList1;
    if(heah->next==nullptr||heah->next->next==nullptr)return;
    p=heah->next->next;		//p指向第二个元素
    heah->next->next=nullptr;
    while(p!=nullptr)
    {
        q=p->next;	//q指向下一个元素
        p->next=heah->next; 	//把p插入第一个元素前
        heah->next=p;
        p=q;
    }
}

//选择运算方法
template<typename T>
QString calculator::Algorithm(int mode){
    polynomial<T> *a=Aa;
    polynomial<T> *b=Bb;
    polynomial<T> *c=Cc;
    QString str;
    Q(Cc);
    if(mode==1)//+
    {
        while(a->next){push(c,a->next->Coefficient,a->next->index);a=a->next;}
        while(b->next){push(c,b->next->Coefficient,b->next->index);b=b->next;}
        CombineSort(c);
        str= Print(c);
    }
    else if(mode==2)//-
    {
        while(a->next){push(c,a->next->Coefficient,a->next->index);a=a->next;}
        while(b->next){push(c,-(b->next->Coefficient),b->next->index);b=b->next;}
        CombineSort(c);
        str= Print(c);
    }

    else if (mode == 3) { // *
        polynomial<T> *p = a->next;
        polynomial<T> *q = b->next;
        while (p) {
            while (q) {
                push(c, p->Coefficient * q->Coefficient, p->index + q->index);
                q = q->next;
            }
            p = p->next;
            q = b->next;
        }
        CombineSort(c);
        str = Print(c);
    }
    else if (mode == 4) { // 定积分运算
        T integral_result = numericalIntegration(a, down, up);
        str = QString::number(integral_result);
    }
    return str;
}

template<typename T>
double calculator::numericalIntegration(polynomial<T> *poly, int down, int up) {
    polynomial<T> *p = poly->next;
    T result = 0;
    // 设置步长
    const T step = 0.00001;

    while (p) {
        T term_integral = 0;
        for (T x = down; x < up; x += step) {
            term_integral += step * (p->Coefficient * pow(x, p->index) + p->Coefficient * pow(x + step, p->index)) / 2;
        }
        result += term_integral;
        p = p->next;
    }
    return result;
}

//窗口代码
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("多项式计算");
    QIcon icon1("E:\\桌面\\CS\\面向对象\\大作业\\x.png");
    ui->label1->setPixmap(icon1.pixmap(QSize(51, 51))); // 设置图标大小
    QIcon icon2("E:\\桌面\\CS\\面向对象\\大作业\\y.png");
    ui->label2->setPixmap(icon2.pixmap(QSize(51, 51)));
    QIcon icon3("E:\\桌面\\CS\\面向对象\\大作业\\up.png");
    ui->label3->setPixmap(icon3.pixmap(QSize(51, 51)));
    QIcon icon4("E:\\桌面\\CS\\面向对象\\大作业\\down.png");
    ui->label4->setPixmap(icon4.pixmap(QSize(51, 51)));
    QIcon icon5("E:\\桌面\\CS\\面向对象\\大作业\\plu.png");
    ui->plus->setIcon(icon5);
    ui->plus->setIconSize(QSize(100, 100));
    QIcon icon6("E:\\桌面\\CS\\面向对象\\大作业\\min.png");
    ui->minus->setIcon(icon6);
    ui->minus->setIconSize(QSize(100, 100));
    QIcon icon7("E:\\桌面\\CS\\面向对象\\大作业\\mul.png");
    ui->multiply->setIcon(icon7);
    ui->multiply->setIconSize(QSize(100, 100));
    QIcon icon8("E:\\桌面\\CS\\面向对象\\大作业\\cal.png");
    ui->calculus->setIcon(icon8);
    ui->calculus->setIconSize(QSize(100, 100));
    QIcon icon9("E:\\桌面\\CS\\面向对象\\大作业\\output.png");
    ui->label5->setPixmap(icon9.pixmap(QSize(51, 51)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_plus_clicked()
{
    ui->LineX->setText(c.GetPolynomialList(ui->LineX->text(),1));
    ui->LineY->setText(c.GetPolynomialList(ui->LineY->text(),2));
    // 获取算法结果并转换为QString
    QString result = c.Algorithm<double>(1);
    // 设置结果文本到 Lineoutput
    ui->Lineoutput->setText(result);
}

void Widget::on_minus_clicked()
{
    ui->LineX->setText(c.GetPolynomialList(ui->LineX->text(),1));
    ui->LineY->setText(c.GetPolynomialList(ui->LineY->text(),2));
    QString result = c.Algorithm<double>(2);
    ui->Lineoutput->setText(result);
}

void Widget::on_multiply_clicked()
{
    ui->LineX->setText(c.GetPolynomialList(ui->LineX->text(),1));
    ui->LineY->setText(c.GetPolynomialList(ui->LineY->text(),2));
    QString result = c.Algorithm<double>(3);
    ui->Lineoutput->setText(result);
}

void Widget::on_calculus_clicked()
{
    ui->LineX->setText(c.GetPolynomialList(ui->LineX->text(),4));
    strup=ui->Lineup->text();
    c.up=strup.toInt();
    strdown=ui->Linedown->text();
    c.down=strdown.toInt();
    QString result = c.Algorithm<double>(4);
    ui->Lineoutput->setText(result);
}
