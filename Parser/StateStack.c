/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : Buffer.h                                                       *
*   Description: CTools-SyntacicParser                                          *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/



#include "..\Parser\StateStack.h"



/// ������ʼ��ջ��Ϣ
StateStack* CreateStateStack( )
{
    StateStack *stack = malloc(sizeof(StateStack));           // ����ջ��ַ�ռ�

    stack->m_top = NULL;            // ����ջ��ָ��
    stack->m_count = 0;

    return stack;
}


/// ����Stackջ��Ϣ
void DestroyStateStack(StateStack *stack) // �����ٵ�ջ��Ϣ
{
    #ifdef PARSER_SHOWS_DEFINE
    printf("��ǰջ��Ԫ����Ŀ%d\n", stack->m_count);
    #endif

    while(stack->m_count > 0)
    {
        PopState(stack);     // ����
    }

    free(stack);        // ��յ�ַ��Ϣ
}

/// pandaun��ǰջ�ǲ��ǿ�ջ
bool EmptyStateSatck(StateStack *stack)   // ջ��Ϣ
{
    return (stack->m_count == 0 && stack->m_top == NULL);
}


/// ��Ԫ��elemѹ��ջ��
bool PushState(StateStack *stack, State state)
{

    if(EmptyStateSatck(stack) == true)
    {
        CreateStateStack(stack);
    }

    StateNode *newNode = NULL;
    if((newNode = (StateNode *)malloc(sizeof(StateNode))) != NULL)     // �����¿ռ�
    {//��������������������
        // ����ջ�Ľ����ϵ
        newNode->m_state = state;     // �½���������
        newNode->m_next = stack->m_top;     // ��ջ��Ԫ����Ϊ�½������ĺ��
        stack->m_top = newNode;             // �½����Ľ����Ϊ��ջ��
        // ����ջ��Ԫ�ظ���
        stack->m_count++;                   // ջԪ�ظ�����1

        #ifdef PARSER_SHOWS_DEFINE
        printf("��״̬%dѹ��ջ��, ��ַ%p\n", state, newNode);
        printf("��ǰ״̬ջ��Ԫ����Ŀ%d\n", stack->m_count);
        #endif      // PARSER_SHOWS_DEFINE

        return true;
    }
    else      // ���ٿռ�ʧ��
    {
        fprintf(stderr, "�ڴ治��, ����ջ�ռ�ʧ��\n");
        return false;
    }

    return false;
}


/// ��ջ�����ݵ���
State PopState(StateStack *stack)
{
    StateNode *oldTop;
    State elem;      //

    if(EmptyStateSatck(stack) != true)        // ���ܶԿ�ջ���е�������
    {
        oldTop = stack->m_top;       // ����ԭ��ջ��
        elem = oldTop->m_state;       // ���潫Ҫ����������
        stack->m_top = oldTop->m_next;   // ����㵯��
        free(oldTop);                // ɾ����ջ���Ŀռ�
        stack->m_count--;           // ջ��Ԫ�ظ�������1

        #ifdef PARSER_SHOWS_DEFINE
        printf("��%d����ջ��, ��ַ%p\n", elem, oldTop);
        printf("��ǰ״̬ջ��Ԫ����Ŀ%d\n", stack->m_count);
        #endif  // PARSER_SHOWS_DEFINE
    }
    else
    {
        fprintf(stderr,"%d, ��ǰ״̬ջΪ��, ����ִ�е�������\n", __LINE__);
        elem = (State)EOF;
    }
    return elem;
}

/// ��ջ�����ݵ���
void PopedState(StateStack *stack, int count)
{
    #ifdef PARSER_SHOWS_DEFINE
    printf("����״̬ջ�е���%d������\n", count);
    #endif  // PARSER_SHOWS_DEFINE
    while(count--)          // ѭ������count������
    {
        PopState(stack);         // ����ջ������
    }
}


/// ����ջ��Ԫ�ص���һ��Ԫ�ص���Ϣ
State NextState(StateStack *stack)
{
    if(stack->m_count <= 1)
    {
        return (State)EOF;
    }
    else
    {
        return (State)stack->m_top->m_next->m_state;           // ����ջ����һ��λ�õ�������Ϣ
    }

    return (State)EOF;               //
}



/// ����ջ����������Ϣ
State TopState(StateStack *stack)  // ����ջ��ջ������
{
    return (State)(stack->m_top->m_state);      // ����ջ��������
}



/// ��ʾ��ǰ״̬ջ�е�������Ϣ
void ShowStateStack(StateStack *stack)
{
    printf("******************************\n");
    printf("**\tStateStack  %02d\t**\n", stack->m_count);
    StateNode *pNode = stack->m_top;
    for(int i = 0; pNode != NULL; i++)
    {
        printf("**%02d -=> (%03d, %p)**\n", i, pNode->m_state, pNode);
        pNode = pNode->m_next;
    }
    printf("******************************\n\n");
}

