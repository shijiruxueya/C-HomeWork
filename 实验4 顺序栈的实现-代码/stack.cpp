#include <iostream>
#include <cstdlib>
using namespace std;

/* 顺序栈的数据结构 */
typedef int DataType;
struct Stack
{
    int top;            // 栈顶指针，指向栈顶元素的下标
    int maxsize;        // 顺序栈的最大空间
    DataType* elements; // 存放顺序栈的栈元素
};

// 函数声明
Stack* InitStack(int size);
bool IsEmpty(Stack* s);
bool IsFull(Stack* s);
bool Push(Stack* s, DataType x);
bool Pop(Stack* s, DataType* e);
bool GetTop(Stack* s, DataType* e);
void Convert(int number, int base);
void DestroyStack(Stack* s);

/*函数功能：初始化一个空的顺序栈
 *函数形参：顺序栈的最大空间 int size
 *函数返回值：成功返回顺序栈指针，失败返回 nullptr
 */
Stack* InitStack(int size)
{
    if (size <= 0)                                   // 容量不合法
        return nullptr;
    Stack* s = (Stack*)malloc(sizeof(Stack));        // 申请栈结构体
    if (s)
    {
        s->elements = (DataType*)malloc(sizeof(DataType) * size); // 申请元素区
        if (s->elements)
        {
            s->maxsize = size;
            s->top = -1;                             // top = -1 表示空栈
            return s;
        }
        free(s);                                     // 元素区申请失败，释放栈
    }
    return nullptr;
}

/*函数功能：判断顺序栈是否为空
 *函数形参：顺序栈指针 Stack* s
 *函数返回值：空返回 true，否则 false
 */
bool IsEmpty(Stack* s)
{
    return s == nullptr || s->top == -1;             // 栈顶指针为 -1 即空栈
}

/*函数功能：判断顺序栈是否已满
 *函数形参：顺序栈指针 Stack* s
 *函数返回值：满返回 true，否则 false
 */
bool IsFull(Stack* s)
{
    return s == nullptr || s->top == s->maxsize - 1;  // 栈顶到达最大下标即满
}

/*函数功能：入栈，把元素 x 压入栈顶
 *函数形参：顺序栈指针 Stack* s，入栈元素 DataType x
 *函数返回值：成功 true，栈满失败 false
 */
bool Push(Stack* s, DataType x)
{
    if (IsFull(s))                                   // 栈满，不能入栈
        return false;
    s->top++;                                        // 栈顶指针先加 1
    s->elements[s->top] = x;                         // 再存入新元素
    return true;
}

/*函数功能：出栈，删除栈顶元素并用 e 带回其值
 *函数形参：顺序栈指针 Stack* s，元素指针 DataType* e
 *函数返回值：成功 true，栈空失败 false
 */
bool Pop(Stack* s, DataType* e)
{
    if (IsEmpty(s))                                  // 栈空，不能出栈
        return false;
    *e = s->elements[s->top];                        // 先取出栈顶元素
    s->top--;                                        // 栈顶指针再减 1
    return true;
}

/*函数功能：获取栈顶元素值（不删除栈顶元素）
 *函数形参：顺序栈指针 Stack* s，元素指针 DataType* e
 *函数返回值：成功 true，栈空失败 false
 */
bool GetTop(Stack* s, DataType* e)
{
    if (IsEmpty(s))                                  // 栈空，无栈顶元素
        return false;
    *e = s->elements[s->top];                        // 只读取，不移动栈顶指针
    return true;
}

/*函数功能：把十进制整数 number 转换成 base 进制并输出（2 <= base <= 9）
 *函数形参：待转换的十进制整数 int number，目标进制 int base
 *函数返回值：无，void 类型
 */
void Convert(int number, int base)
{
    if (base < 2 || base > 9)                        // 进制范围检查
    {
        cout << "进制 base 应在 2~9 之间！" << endl;
        return;
    }
    Stack* s = InitStack(64);                        // 转换用的工作栈
    if (s == nullptr)
    {
        cout << "栈初始化失败！" << endl;
        return;
    }

    int sign = number;                               // 记录原数（含符号）
    if (number < 0)
        number = -number;                            // 先按正数处理

    if (number == 0)                                 // 0 是特殊情况，直接入栈
        Push(s, 0);

    while (number > 0)                               // 反复“除 base 取余”并入栈
    {
        Push(s, number % base);                      // 当前最低位入栈
        number = number / base;                      // 去掉已处理的低位
    }

    cout << "十进制 " << sign << " 转换成 " << base << " 进制：";
    if (sign < 0)
        cout << "-";                                 // 负号在最高位之前
    DataType e = 0;
    while (!IsEmpty(s))                              // 依次出栈即高位到低位
    {
        Pop(s, &e);
        cout << e;
    }
    cout << endl;

    DestroyStack(s);
}

/*函数功能：销毁顺序栈，释放存储空间
 *函数形参：顺序栈指针 Stack* s
 *函数返回值：无，void 类型
 */
void DestroyStack(Stack* s)
{
    if (s)
    {
        free(s->elements);
        free(s);
    }
}

/* 测试主函数：先完成一组入栈/出栈操作，再由键盘输入完成数制转换 */
int main()
{
    Stack* s = InitStack(5);                         // 建立容量为 5 的顺序栈
    if (s == nullptr)
    {
        cout << "顺序栈初始化失败！" << endl;
        return 0;
    }
    cout << "初始化后：是否为空=" << (IsEmpty(s) ? "是" : "否")
         << "，是否已满=" << (IsFull(s) ? "是" : "否") << endl;

    cout << "请输入入栈序列（以 -1 结束）：";
    int x = 0;
    while (cin >> x && x != -1)                      // 依次入栈
    {
        if (Push(s, x))
            cout << "入栈 " << x << " 成功，top=" << s->top << endl;
        else
            cout << "栈已满，" << x << " 入栈失败" << endl;
    }

    DataType e = 0;
    if (GetTop(s, &e))                               // 读取栈顶元素
        cout << "当前栈顶元素：" << e << endl;
    else
        cout << "栈空，取栈顶元素失败" << endl;

    cout << "依次出栈：";
    while (Pop(s, &e))                               // 全部出栈
        cout << e << " ";
    cout << endl;
    cout << "全部出栈后是否为空：" << (IsEmpty(s) ? "是" : "否") << endl;
    if (!Pop(s, &e))                                 // 空栈出栈测试
        cout << "栈已空，出栈失败" << endl;
    DestroyStack(s);

    cout << "请输入十进制整数 number 和目标进制 base：";
    int number = 0, base = 0;
    if (cin >> number >> base)                       // 数制转换
        Convert(number, base);

    return 0;
}
