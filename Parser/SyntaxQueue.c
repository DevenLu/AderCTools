#include "Syntax.h"


// ��ʼ����ǰ�﷨����
SyntaxQueue* CreateSyntaxQueue( )
{
    SyntaxQueue *queue = NULL;

    if((queue = malloc(sizeof(SyntaxQueue))) == NULL)
    {
        fprintf(stderr, "malloc ERROR\n");
    }

    queue->m_front = NULL;
    queue->m_rear = NULL;
    queue->m_count = 0;

    return queue;
}


// �жϵ�ǰ�﷨�����Ƿ�Ϊ��
bool EmptySyntaxQueue(SyntaxQueue *queue)
{
    return (queue->m_count == 0);
}
//#define EmptySyntaxQueue(queue)     ((queue)->m_count == 0)

// ���﷨����ѹ���﷨����
void InSyntaxQueue(SyntaxQueue *queue, SyntaxTreeNode *node)
{
    if(EmptySyntaxQueue(queue) == true)
    {
        queue->m_front = node;
        queue->m_rear = node;
        node->m_next = NULL;
    }
    else
    {
        queue->m_rear->m_next = node;
        queue->m_rear = node;
        node->m_next = NULL;
    }
    queue->m_count++;
}


// ���﷨���ݵ����﷨����
SyntaxTreeNode* OutSyntaxQueue(SyntaxQueue *queue)
{
    SyntaxTreeNode *node = NULL;

    if(EmptySyntaxQueue(queue) == true)
    {
        fprintf(stderr, "��ǰ�﷨����Ϊ��, �޷�����ͷ���ݵ���\n");
    }
    else
    {
        node = queue->m_front;
        queue->m_front = node->m_next;
        queue->m_count--;
    }
    return node;
}
