#include <iostream>
using namespace std;

typedef int DataType;      // 数据元素类型

/* 单链表结点定义 */
struct Node
{
    DataType data;         // 数据域：存放元素值
    Node* next;            // 指针域：指向下一个结点
};

/* 函数声明 */
Node* InitList();                  // 初始化带头结点的空链表
void  CreateList_Head(Node* head); // 头插法建立单链表
void  CreateList_Tail(Node* head); // 尾插法建立单链表
bool  IsEmpty(Node* head);         // 判断链表是否为空
int   Length(Node* head);          // 求链表长度
void  OutputList(Node* head);      // 输出链表内容
void  DestroyList(Node* head);     // 销毁链表，释放全部结点

/*函数功能：初始化一个带头结点的空单链表
 *函数形参：无
 *函数返回值：头结点指针，Node* 类型
 */
Node* InitList()
{
    Node* head = new Node;      // 申请头结点，其数据域不存放有效元素
    head->next = nullptr;       // 头结点指针域置空，表示空表
    return head;
}

/*函数功能：用头插法建立单链表（输入 -1 结束）
 *函数形参：带头结点的单链表 Node* head
 *函数返回值：无，void 类型
 */
void CreateList_Head(Node* head)
{
    if (head == nullptr)
        return;
    DataType x;
    cout << "请输入元素（输入 -1 结束）：";
    while (cin >> x && x != -1)
    {
        Node* s = new Node;     // 申请新结点
        s->data = x;            // 存入数据
        s->next = head->next;   // 新结点指向原来的首结点
        head->next = s;         // 头结点指向新结点，新结点成为首结点
    }
}

/*函数功能：用尾插法建立单链表（输入 -1 结束）
 *函数形参：带头结点的单链表 Node* head
 *函数返回值：无，void 类型
 */
void CreateList_Tail(Node* head)
{
    if (head == nullptr)
        return;
    Node* tail = head;          // tail 始终指向当前表尾结点
    DataType x;
    cout << "请输入元素（输入 -1 结束）：";
    while (cin >> x && x != -1)
    {
        Node* s = new Node;     // 申请新结点
        s->data = x;            // 存入数据
        s->next = nullptr;      // 新结点作为新的表尾
        tail->next = s;         // 原表尾的指针域指向新结点
        tail = s;               // 尾指针后移
    }
}

/*函数功能：判断链表是否为空
 *函数形参：带头结点的单链表 Node* head
 *函数返回值：空返回 true，否则返回 false
 */
bool IsEmpty(Node* head)
{
    if (head == nullptr)
        return true;
    return head->next == nullptr;
}

/*函数功能：求单链表的长度（不含头结点）
 *函数形参：带头结点的单链表 Node* head
 *函数返回值：链表中元素的个数，int 类型
 */
int Length(Node* head)
{
    int count = 0;
    if (head == nullptr)
        return 0;
    Node* p = head->next;       // 从首结点开始
    while (p != nullptr)
    {
        count++;                // 每访问一个结点，长度加 1
        p = p->next;
    }
    return count;
}

/*函数功能：输出单链表的内容
 *函数形参：带头结点的单链表 Node* head
 *函数返回值：无，void 类型
 */
void OutputList(Node* head)
{
    if (head == nullptr)
        return;
    Node* p = head->next;
    if (p == nullptr)           // 空表单独处理
    {
        cout << "空表" << endl;
        return;
    }
    while (p != nullptr)
    {
        cout << p->data;
        if (p->next != nullptr)
            cout << " ";
        p = p->next;
    }
    cout << endl;
}

/*函数功能：销毁单链表，释放包括头结点在内的所有结点
 *函数形参：带头结点的单链表 Node* head
 *函数返回值：无，void 类型
 */
void DestroyList(Node* head)
{
    Node* p = head;
    while (p != nullptr)
    {
        Node* q = p->next;      // 先保存后继结点
        delete p;               // 再释放当前结点
        p = q;
    }
}

int main()
{
    /*------------------- 头插法 -------------------*/
    cout << "===== 头插法建立单链表 =====" << endl;
    Node* head1 = InitList();
    cout << "初始化后：是否为空=" << (IsEmpty(head1) ? "是" : "否")
         << "，长度=" << Length(head1) << endl;
    CreateList_Head(head1);
    cout << "头插法得到的链表：";
    OutputList(head1);
    cout << "链表长度：" << Length(head1) << endl;
    cout << "链表是否为空：" << (IsEmpty(head1) ? "是" : "否") << endl;
    DestroyList(head1);

    /*------------------- 尾插法 -------------------*/
    cout << "===== 尾插法建立单链表 =====" << endl;
    Node* head2 = InitList();
    cout << "初始化后：是否为空=" << (IsEmpty(head2) ? "是" : "否")
         << "，长度=" << Length(head2) << endl;
    CreateList_Tail(head2);
    cout << "尾插法得到的链表：";
    OutputList(head2);
    cout << "链表长度：" << Length(head2) << endl;
    cout << "链表是否为空：" << (IsEmpty(head2) ? "是" : "否") << endl;
    DestroyList(head2);

    return 0;
}
