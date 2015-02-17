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



#include "Syntax.h"




/// ������ʼ��ջ��Ϣ
SyntaxStack* CreateSyntaxStack( )
{
    SyntaxStack *stack = malloc(sizeof(SyntaxStack));           // ����ջ��ַ�ռ�

    stack->m_top = NULL;            // ����ջ��ָ��
    stack->m_count = 0;

    return stack;
}


/// ����Stackջ��Ϣ
void DestroySyntaxStack(SyntaxStack *stack) // �����ٵ�ջ��Ϣ
{
    #ifdef PARSER_SHOWS_DEFINE
    printf("��ǰջ��Ԫ����Ŀ%d\n", stack->m_count);
    #endif

    while(stack->m_count > 0)
    {
        PopSyntax(stack);     // ����
    }

    free(stack);        // ��յ�ַ��Ϣ
}

/// ��pNode��ָ��Ĵʷ���Ϣ���ѹ�����ջ��
bool PushTupleInSyntaxStack(SyntaxStack *stack, TupleNode *tupleNode)
{
    if(EmptySyntaxStack(stack) == true)
    {
        CreateSyntaxStack(stack);
    }
    SyntaxStackNode *newNode = NULL;

    if((newNode = (SyntaxStackNode *)malloc(sizeof(SyntaxStackNode))) != NULL)
    {//��������������������
        // ���������ֵ
        newNode->m_syntax.m_kind = SYNTAX_TERR_TERINAL;     // ָ��ʷ���Ϣ�Ľ�㶼���ս����
        newNode->m_syntax.m_data.m_tupleNode = tupleNode;        // �½���������
        newNode->m_syntax.m_startCoord = tupleNode->m_tuple.m_coord;
        newNode->m_syntax.m_endCoord = tupleNode->m_tuple.m_coord;

        // �﷨�����ָ�����ʼ��
        newNode->m_parent = NULL;
        newNode->m_finalChild = NULL;
        newNode->m_leftBrother = NULL;
        newNode->m_firstChild = NULL;
        newNode->m_rightBrother = NULL;

        // ����ջ�Ľ����ϵ
        newNode->m_next = stack->m_top;     // ��ջ��Ԫ����Ϊ�½������ĺ��
        stack->m_top = newNode;             // �½����Ľ����Ϊ��ջ��
        // ����ջ��Ԫ�ظ���
        stack->m_count++;                   // ջԪ�ظ�����1

        //ShowSyntaxTreeNode(newNode->m_syntax);

        #ifdef PARSER_SHOWS_DEFINE
        printf("���ս��%dѹ�����ջ��, ��ַ%p  %p\n", newNode->m_syntax.m_data.m_tupleNode->m_tuple.m_kind, newNode, stack->m_top);
        printf("��ǰ����ջ��Ԫ����Ŀ%d\n", stack->m_count);
        #endif
        return true;
    }
    else      // ���ٿռ�ʧ��
    {
        fprintf(stderr, "�ڴ治��, ����ջ�ռ�ʧ��\n");
        return false;
    }

    return false;
}
/// ��kind ���������ķ���������ѹ�����ջ��
bool PushGrammarInSyntaxStack(SyntaxStack *stack, SyntaxKind syntax)    // �﷨������Ϣ
{
    if(EmptySyntaxStack(stack) == true)
    {
        CreateSyntaxStack(stack);
    }

    SyntaxStackNode *newNode = NULL;
    if((newNode = (SyntaxStackNode *)malloc(sizeof(SyntaxStackNode))) != NULL)
    {//��������������������
        // ջ�Ľ��������ֵ
        newNode->m_syntax.m_kind = SYNTAX_TERR_VARIBALE;     // ָ��ʷ���Ϣ�Ľ�㶼���﷨����
        newNode->m_syntax.m_data.m_syntaxKind = syntax;        // �½���������
        // �﷨�����ָ�����ʼ��
        newNode->m_parent = NULL;
        newNode->m_finalChild = NULL;
        newNode->m_leftBrother = NULL;
        newNode->m_firstChild = NULL;
        newNode->m_rightBrother = NULL;

        // ����ջ�Ľ����ϵ
        newNode->m_next = stack->m_top;     // ��ջ��Ԫ����Ϊ�½������ĺ��
        stack->m_top = newNode;             // �½����Ľ����Ϊ��ջ��

        // ����ջ��Ԫ�ظ���
        stack->m_count++;                   // ջԪ�ظ�����1

        //ShowSyntaxTreeNode(newNode->m_syntax);

        #ifdef PARSER_SHOWS_DEFINE
        printf("���ķ���%dѹ�����ջ��, ��ַ%p\n", (int)syntax, newNode);
        printf("��ǰ����ջ��Ԫ����Ŀ%d\n", stack->m_count);
        #endif
        return true;
    }
    else      // ���ٿռ�ʧ��
    {
        fprintf(stderr, "�ڴ治��, ����ջ�ռ�ʧ��\n");
        return false;
    }

    return false;
}





bool PushSynTreeNodeInSynStack(SyntaxStack *stack, SyntaxTreeNode *syntaxNode)
{
    if(EmptySyntaxStack(stack) == true)
    {
        CreateSyntaxStack(stack);
    }

    SyntaxStackNode *newNode = NULL;
    if(syntaxNode != NULL)
    {//��������������������
        // ջ�Ľ��������ֵ
        newNode = syntaxNode;

        // ����ջ�Ľ����ϵ
        newNode->m_next = stack->m_top;     // ��ջ��Ԫ����Ϊ�½������ĺ��
        stack->m_top = newNode;             // �½����Ľ����Ϊ��ջ��

        // ����ջ��Ԫ�ظ���
        stack->m_count++;                   // ջԪ�ظ�����1
        //ShowSyntaxTreeNode(newNode->m_syntax);
        #ifdef PARSER_SHOWS_DEFINE
        if(syntaxNode->m_syntax.m_kind == SYNTAX_TERR_VARIBALE)
        {
        printf("���ķ���%dѹ�����ջ��, ��ַ%p\n", newNode->m_syntax.m_data.m_syntaxKind, newNode);
        }
        else
        {
            printf("���ս��%dѹ�����ջ��, ��ַ%p  %p\n", newNode->m_syntax.m_data.m_tupleNode->m_tuple.m_kind, newNode, stack->m_top);
        }
        printf("��ǰ����ջ��Ԫ����Ŀ%d\n", stack->m_count);
        #endif
        return true;
    }
    else      // ���ٿռ�ʧ��
    {
        fprintf(stderr, "�ڴ治��, ����ջ�ռ�ʧ��\n");
        return false;
    }

    return false;
}

/// ��Ԫ��Syntaxѹ��ջ��
bool PushSyntax(SyntaxStack *stack, Syntax syntax)
{

    return PushSynTreeNodeInSynStack(stack, syntax);
}



/// ��ջ�����ݵ���
bool PopSyntax(SyntaxStack *stack)
{

    //Syntax Syntax = (Syntax)NULL;      //
    if(EmptySyntaxStack(stack) != true)        // ���ܶԿ�ջ���е�������
    {
        #ifdef PARSER_SHOWS_DEFINE
        if(stack->m_top->m_syntax.m_kind == SYNTAX_TERR_TERINAL)
        {
            printf("���ս��%d��������ջ��, ��ַ%p\n", stack->m_top->m_syntax.m_data.m_tupleNode->m_tuple.m_kind, stack->m_top);
        }
        else
        {
            printf("���ķ���%d��������ջ��, ��ַ%p\n", stack->m_top->m_syntax.m_data.m_syntaxKind, stack->m_top);
        }
        printf("��ǰ����ջ��Ԫ����Ŀ%d\n", stack->m_count - 1);
        #endif

        SyntaxStackNode *oldTop;
        oldTop = stack->m_top;       // ����ԭ��ջ��
        //Syntax = oldTop->m_syntax;       // ���潫Ҫ����������
        stack->m_top = oldTop->m_next;   // ����㵯��
        //free(oldTop);                // ɾ����ջ���Ŀռ�
        stack->m_count--;           // ջ��Ԫ�ظ�������1
    }
    else
    {
        fprintf(stderr,"%d, ��ǰ����ջΪ��, ����ִ�е�������\n", __LINE__);
        ///////////////////////////////////////////////////////////////////////////////
        //Syntax = (Syntax)EOF;/////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////
        return false;
    }
    return true;
}

/// ��ջ�����ݵ���
void PopedSyntax(SyntaxStack *stack, int count)
{
    #ifdef PARSER_SHOWS_DEFINE
    printf("���ӷ���ջ�е���%d������\n", count);
    #endif

    while(count--)          // ѭ������count������
    {
        PopSyntax(stack);         // ����ջ������
    }
}


/// ����ջ��Ԫ�ص���һ��Ԫ�ص���Ϣ
Syntax NextSyntax(SyntaxStack *stack)
{
    return stack->m_top->m_next;
}


/// ��ȡջ��ջ��step��Ԫ�ص�������Ϣ
Syntax GetSyntax(SyntaxStack *stack, int step)           // ����ջ��Ԫ�ص���һ��Ԫ�ص���Ϣ
{
    if(step < 0 || step >= stack->m_count)
    {
        return (Syntax)NULL;
    }
    // �ҵ���ջ������Ϊstep���﷨�ڵ���Ϣ
    int i = 0;
    SyntaxStackNode* syntaxStackNode = stack->m_top;

    while(i < step)
    {
        syntaxStackNode = syntaxStackNode->m_next;
        i++;
    }

    return (Syntax)syntaxStackNode;           // ���ص�ǰռջ�е�������
}

/// pandaun��ǰջ�ǲ��ǿ�ջ
bool EmptySyntaxStack(SyntaxStack *stack)   // ջ��Ϣ
{
    return (stack->m_count == 0 && stack->m_top == NULL);
}

/// ����ջ����������Ϣ
Syntax TopSyntax(SyntaxStack *stack)  // ����ջ��ջ������
{
    return (Syntax)(stack->m_top);      // ����ջ��������
}


void ShowSyntaxStack(SyntaxStack *stack)
{
    printf("**********************************\n");
    printf("**\tSyntaxStack  %04d\t**\n", stack->m_count);

    SyntaxStackNode *pNode = stack->m_top;

    for(int i = 0; pNode != NULL; i++)
    {
        printf("**\t");
        ShowSyntaxTreeNode(pNode);
        pNode = pNode->m_next;
        printf("\t**\n");
    }

    printf("**********************************\n\n");
}
