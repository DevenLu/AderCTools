/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : SyntaxTree.c                                                   *
*   Description: CTools-SyntacicParser                                          *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/


///-//////////////////////////////////////////////////////////////////////////////////////-///
/// ���ļ�ϵAderCTools�������﷨�����������ӿ�ʵ���ļ�                                          ///
/// ���ʱ��2013-7-21   15:16                                                               ///
/// ���룺GatieMe                                                                           ///
/// �汾0.3.3���                                                                           ///
///-//////////////////////////////////////////////////////////////////////////////////////-///



#include "Syntax.h"               // �﷨�������Ϣ


/*
*   �������ڹ�Լ�����н����﷨����˼·�ǣ� ��������߲㽨��һ���ܸ�
*   �ڹ�Լ�Ĺ����У�
*
*
*
*/


/** ��ʼ���µ��﷨����Ϣ*************************************************************************
*   Function	 :  CreateSyntaxTree
*   Param		 :
*   Return		 :  �����½������﷨�����ڵ���Ϣ,�������ָ��
*   Description:  �ú������﷨�����ĳ�ʼ���׶Σ������﷨�������ĳ�ʼ������
*   Calls		 :  NULL
*   CalledBy   :
*   Version    :	0.4.0
*   Warning    :
**********************************************************************************************/
SyntaxTree CreateSyntaxTree( )
{
    SyntaxTreeNode* root;               // ��ǰ�﷨���Ľ����Ϣ

    if((root = (SyntaxTreeNode *)malloc(sizeof(SyntaxTreeNode))) != NULL)            // Ϊ���ڵ㿪�ٿռ�
    {
        printf("�﷨��ͷ���%p\n", root);
        PAUSE( );
        root->m_syntax.m_kind = SYNTAX_TERR_STARTER;                              // �﷨���ĸ�Ϊ��ʼ�ķ�����
        root->m_syntax.m_data.m_syntaxKind = SYN_STARTER;                              // �ķ���ʼ���ű�ʾΪSYN_START

        /// ������ָ����ֵ
        // ˫�׵ĸ�ֵ
        root->m_parent = NULL;                  // ��û��˫�׽��
        // ���Һ��Ӳ��Եĸ�ֵ
        root->m_finalChild = NULL;
        root->m_leftBrother = NULL;
        // �����Ӳ��Եĸ�ֵ
        root->m_firstChild = NULL;
        root->m_rightBrother = NULL;

        root->m_next = NULL;
    }
    else
    {
        fprintf(stderr, "��ʼ���﷨��ʱ��  ���ٸ��ڵ�ʧ��\n");
    }

    return root;
}

/** �����﷨��������Ϣ***************************************************************************
*   Function	 :  DeleteSyntaxTreeNode
*   Param		 :  root[SYNTAXTREE]�����ٵ��﷨������������Ϣ.
*   Return		 :  ���ٳɹ�����TRUE,����ʧ�ܷ���FALSE
*   Description:  �ú������﷨�����ĳ�ʼ���׶Σ������﷨�������ĳ�ʼ������
*   Calls		 :  NULL
*   CalledBy   :
*   Version    :	0.4.2
*   Warning    :
**********************************************************************************************/
void DeleteSyntaxTreeNode(SyntaxTreeNode *node)
{
    if(node == (SyntaxTreeNode *)node->m_parent->m_firstChild)        // (node->m_leftBrother == NULL)��ǰ����Ǹ��ڵ�ĵ�һ������-=>
    {
        node->m_parent->m_firstChild = node->m_rightBrother;

        node->m_rightBrother->m_leftBrother = NULL/*node->leftBrother = NULL*/;
        //node->m_leftBrother->m_leftBrother = node->m_rightBrother;
    }
    else if(node == node->m_parent->m_finalChild)        // (node->m_rightBrother == NULL)��ǰ����Ǹ��ڵ�����һ������-=>
    {
        node->m_parent->m_finalChild = node->m_leftBrother;

        node->m_leftBrother->m_leftBrother = NULL/*node->m_rightBrother = NULL*/;
        //node->m_rightBrother->leftBrother = node->m_leftBrother;
    }
    else //if(node->m_rightBrother != NULL)
    {
        node->m_rightBrother->m_leftBrother = node->m_leftBrother;
        node->m_leftBrother->m_leftBrother = node->m_rightBrother;
    }

    free(node);             // ɾ�����Ŀռ�
}


/** �����﷨��������Ϣ***************************************************************************
*   Function	 :  DestroySyntaxTree
*   Param		 :  root[SYNTAXTREE]�����ٵ��﷨������������Ϣ.
*   Return		 :  ���ٳɹ�����TRUE,����ʧ�ܷ���FALSE
*   Description:  �ú������﷨�����ĳ�ʼ���׶Σ������﷨�������ĳ�ʼ������
*   Calls		 :  NULL
*   CalledBy   :
*   Version    :	0.4.2
*   Warning    :
**********************************************************************************************/
void DestroySyntaxTree(SyntaxTree root)
{
    /// �����ں������
    if(root != NULL)
    {
        /// ��������﷨��
        if(root->m_firstChild != NULL)          // �ݹ�������һ������
        {
            DestroySyntaxTree(root->m_firstChild);
        }
        else if(root->m_rightBrother != NULL)
        {
            DestroySyntaxTree(root->m_rightBrother);        // ɾ����һ�������Ժ�ݹ�������ұߵ��ֵ�
        }

        DeleteSyntaxTreeNode(root);                                     // ɾ����ǰλ�ã�Ҳ���ǵ�һ�����ӵ���Ϣ
    }
}






/** ��ӵ�id������ʽ���ŵ��﷨��*****************************************************************
*   Function	 :  InsertTree
*   Param		 :  root[SyntaxTREE*] ��ǰ��������﷨�����ڵ�
*                 stack[SyntaxSTACK*]��ǰ�﷨ջ��Ϣ���洢�˵�ǰ����Ĵʷ����ķ�������Ϣ
*                 id[INT]           ��ǰ��Լ�Ĳ���ʽ�ı��, ���Բ��ҵ��ķ��Ĳ���ʽ���Ҳ�����Ϣ
*   Return		 :  �����﷨�����ĸ��ڵ���Ϣ, ָ������������ָ��
*   Description:  �ú������﷨�������й��µ�ʱ�����, ��ԭ�﷨���в���һ���﷨����
*              :  ���﷨�������е���Ϣ����Grammar.c�е�id���ķ�����ʽ�Ĵ洢�ṹ,
*                 ����һ�ŷ��ϵ�ǰ��ԼҪ����﷨����
*   Calls		 :  NULL
*   CalledBy   :
*   Version    :	0.3.8
*   Warning    :
**********************************************************************************************/
SyntaxTree InsertSyntaxTree(SyntaxStack *stack, int id)
{
#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
assert(stack != NULL                            // �﷨����ջջ����㲻Ϊ��
    && EmptySyntaxStack(stack) != true);         // �﷨����ջ��Ϊ��
#endif // PARSER_DEBUG_DEFINE

#ifdef PARSER_SHOWS_DEFINE
if( stack == NULL)
{
    fprintf(stderr, "��ǰ�﷨���������߷���ջδ��ʼ��, ���ΪNULL\n");
    PAUSE( );
    exit(-1);
}

if(EmptySyntaxStack(stack) == true)
{
    fprintf(stderr, "��ǰ����ջΪ��, �޷������﷨��������");
    PAUSE( );
    exit(-1);
}
#endif // PARSER_SHOWS_DEFINE

/*
*   ���㽨����Ҫ��Լ��ʱ�򣬲���ʽ���Ҳ���λ�ڷ���ջ�Ķ���
*   ����ֻ��Ҫ�ڷ���ջ�н����﷨����֮��ĸ����ֵܽ�����ϰ�����ڣ�
*
*/
    // ��ȡ����ʽ����Ϣ
    int                      length = RightGrammarLength(id);               // ��ѯ������ǰ�ķ�����ʽ�ĳ���

    //printf("%dͷָ���ַ%p\n", __LINE__, root);

    #ifdef PARSER_SHOWS_DEFINE
    printf("��ǰ��Լ��Ϣ:\n");
    printf("����ʽ���:%d", id);
    printf("����ʽ�Ҳ�����:%d\n", length);
    #endif // PARSER_SHOWS_DEFINE

    // ��ȡ�ͽ����﷨��������Ϣ
    // SyntaxStackNode*         syntaxStackNode = NULL;
    SyntaxTreeNode*/* Syntax */ parentSyntaxNode = NULL;
    SyntaxTreeNode*/* Syntax */ currSyntaxNode = NULL;    // = TopSyntax(stack);             // ȡ��ջ�����﷨��Ϣ
    SyntaxTreeNode*/* Syntax */ lastSyntaxNode = NULL;    // = NULL;
    SyntaxTreeNode*/* Syntax */ nextSyntaxNode = NULL;


    // ���ȹ�Լʱ, �������﷨���������ķ�����ʽ���󲿵��ķ���ϢΪ�������ڵ��
    if((parentSyntaxNode = (SyntaxTreeNode *)malloc(sizeof(SyntaxTreeNode))) == NULL)                // �����������ڵ����Ϣ
    {
        fprintf(stderr, "malloc ERROR\n");
        exit(-1);
    }
    //printf("******************parentSyntaxNode = %p******************\n", parentSyntaxNode);
    parentSyntaxNode->m_syntax.m_kind = SYNTAX_TERR_VARIBALE;                                    // ����ʽ�����ķ�����
    parentSyntaxNode->m_syntax.m_data.m_syntaxKind = LeftGrammarData(id);                                 // ����ʽ�󲿵��ķ�ֵ

    // ��ʱ�޷���ȡ��ǰ�﷨���޽����ֵ���Ϣ��
    parentSyntaxNode->m_rightBrother = NULL;
    parentSyntaxNode->m_leftBrother = NULL;


    // �������ڵ��뺢�ӵ���ϵ
    parentSyntaxNode->m_finalChild = GetSyntax(stack, 0);//TopSyntax(stack);            // �������������Һ�����ջ��
    parentSyntaxNode->m_firstChild = GetSyntax(stack, length - 1);                       //
    parentSyntaxNode->m_syntax.m_startCoord = parentSyntaxNode->m_firstChild->m_syntax.m_startCoord;
    parentSyntaxNode->m_syntax.m_endCoord = parentSyntaxNode->m_finalChild->m_syntax .m_endCoord;

    //parentSyntaxNode->m_syntax.m_coord =
    // ��ǰ�����ջ�е���ϰ��ʱ�޷�ȷ��
    parentSyntaxNode->m_next = NULL;

    /// �����﷨����Ҷ�ӽ��ĸ�ֵ
    for(int step = 0; step < length; step++)
    {
        currSyntaxNode = GetSyntax(stack, step);                    // ȡ����ǰ�﷨�ڵ�

        if(step == 0)                                               // ��һ���﷨�ڵ���Ϊ�����������Һ��ӽڵ㣬����һ�����Ϊ��
        {
            lastSyntaxNode = NULL;
        }
        else                                                        // ����ȡ������һ�﷨�ڵ����Ϣ
        {
            lastSyntaxNode = GetSyntax(stack, step - 1);
        }

        if(step == length - 1)                                      // ���һ���﷨�ڵ���Ϊ�����������ӣ�����һ�����Ϊ��
        {
            nextSyntaxNode = NULL;
        }
        else                                                        // ����ȡ������һ���﷨�ڵ�
        {
            nextSyntaxNode = GetSyntax(stack, step + 1);
        }

        currSyntaxNode->m_parent = parentSyntaxNode;                    // ��ǰ����˫�׽��Ϊ�½���˫�׽��
        currSyntaxNode->m_leftBrother = nextSyntaxNode;                 // ��ǰ��������Ϊ����һ�����
        currSyntaxNode->m_rightBrother = lastSyntaxNode;                // ��ǰ�����Һ���Ϊ����һ�����

        if(currSyntaxNode->m_syntax.m_kind == SYNTAX_TERR_TERINAL)             // �����ǰ���Ϊ�ս����, �亢�ӽ��ΪNULL
        {
            currSyntaxNode->m_firstChild = NULL;
            currSyntaxNode->m_finalChild = NULL;
        }

        #ifdef PARSER_DEBUG_DEFINE
        printf("curr = %p, left = %p, right = %p\n", currSyntaxNode, nextSyntaxNode, lastSyntaxNode);
        ShowSyntaxTreeNode(currSyntaxNode);
        printf("\n");
        ShowSyntaxTreeNode(nextSyntaxNode);
        printf("\n");
        ShowSyntaxTreeNode(lastSyntaxNode);
        printf("\n");
        #endif // PARSER_DEBUG_DEFINE

    }
    //printf("******************parentSyntaxNode = %p******************\n", parentSyntaxNode);
    return parentSyntaxNode;                // ���ز����﷨�����ĸ��׽��
}




// ��ȡ��rootΪ�����﷨���ĸ߶�
int GetSyntaxTreeHeight(SyntaxTree root)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        int leftHeight, rightHeight;
        leftHeight = GetSyntaxTreeHeight(root->m_firstChild);
        rightHeight = GetSyntaxTreeHeight(root->m_rightBrother);

        return 1 + (leftHeight > rightHeight) ? leftHeight : rightHeight;
    }
}


// ��ȡ��rootΪ�����﷨���Ľ�����
int GetSyntaxTreeNodeCount(SyntaxTree root)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + GetSyntaxTreeNodeCount(root->m_firstChild) + GetSyntaxTreeNodeCount(root->m_rightBrother);
    }
}


// ��ʾ��ǰ�﷨��Ϣ��ֵ
void ShowSyntaxTreeNode(SyntaxTreeNode  *pNode)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    if(pNode != NULL)
    {
        printf("{%03d : ", pNode->m_syntax.m_kind);

        if(pNode->m_syntax.m_kind == SYNTAX_TERR_VARIBALE
           || pNode->m_syntax.m_kind == SYNTAX_TERR_STARTER)           // ��ǰ������﷨������Ҳ���Ƿ��ս����
        {
            printf("[%03d, %03d]", pNode->m_syntax.m_kind, pNode->m_syntax.m_data.m_syntaxKind);      // ����﷨�����ı��
        }
        else if(pNode->m_syntax.m_kind == SYNTAX_TERR_TERINAL)       // ��ǰ������ս����
        {
            ShowTupleData(pNode->m_syntax.m_data.m_tupleNode);
        }
        printf("}");
    }
    #ifdef PARSER_DEBUG_DEFINE
    else
    {
        printf("��ǰ�﷨�����Ϊ��\n");
    }
    #endif // PARSER_DEBUG_DEFINE

}


// ���������rootΪ�����﷨��
void PreOrderSytaxTree(SyntaxTree root)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    SyntaxTreeNode *pNode = root;
    if(pNode != NULL)
    {
        ShowSyntaxTreeNode(pNode);                      // ��ʾ��ǰ�������Ϣ
        printf("\n");
        PreOrderSytaxTree((SyntaxTree)pNode->m_firstChild);       // �ݹ鵱ǰ������
        //printf("�������\n");
        PreOrderSytaxTree((SyntaxTree)pNode->m_rightBrother);    // �ݹ鵱ǰ�������ֵ�
        //printf("�ֵ����\n");
    }
}

// ���������rootΪ�����﷨��
void InOrderSyntaxTree(SyntaxTree root)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    SyntaxTreeNode *pNode = root;
    //printf("root = %p\n", root);
    //PAUSE( );
    if(pNode != NULL)
    {
        InOrderSyntaxTree((SyntaxTree)pNode->m_firstChild);       // �ݹ鵱ǰ������

        ShowSyntaxTreeNode(pNode);                      // ��ʾ��ǰ�������Ϣ
        printf("\n");
        InOrderSyntaxTree((SyntaxTree)pNode->m_rightBrother);    // �ݹ鵱ǰ�������ֵ�
    }
}



// ���������rootΪ�����﷨��
void PostOrderSyntaxTree(SyntaxTree root)
{
#ifdef PARSER_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // PARSER_DEBUG_DEFINE
    SyntaxTreeNode *pNode = root;

    if(pNode != NULL)
    {
        PostOrderSyntaxTree((SyntaxTree)pNode->m_firstChild);       // �ݹ鵱ǰ������
        PostOrderSyntaxTree((SyntaxTree)pNode->m_rightBrother);    // �ݹ鵱ǰ�������ֵ�
        ShowSyntaxTreeNode(pNode);                      // ��ʾ��ǰ�������Ϣ
        printf("\n");
    }
}
/// ����������﷨����done����
void InOrderDoneSyntaxTree(SyntaxTree root, void (*Done)(void *))                  // ϣ����ȡ�Ĳ���
{
    SyntaxTreeNode *pNode = root;

    if(pNode != NULL)
    {
        PostOrderSyntaxTree((SyntaxTree)pNode->m_firstChild);       // �ݹ鵱ǰ������
        (*Done)((void *)pNode);                      // ��ʾ��ǰ�������Ϣ
        printf("\n");
        PostOrderSyntaxTree((SyntaxTree)pNode->m_rightBrother);    // �ݹ鵱ǰ�������ֵ�
    }
}


// ����״��ʾ�﷨��-=> ��α����﷨��
void ShowSyntaxTree(Syntax root)
{
    SyntaxTreeNode *node = NULL;
    SyntaxQueue    *queue = CreateSyntaxQueue( );

    if(root != NULL)            // �����Ϊ�ǿ�, �򽫸����
    {
        InSyntaxQueue(queue, root);
    }

    while(EmptySyntaxQueue(queue) != true)
    {
        node = OutSyntaxQueue(queue);
        /*if(SYN_ENDL)
        {
            printf("\n");
        }*/
        ShowSyntaxTreeNode(node);                   // ��ʾ��ǰ�﷨��������Ϣ

        // ���ν������к������
        if(node->m_firstChild != NULL)
        {
            node = node->m_firstChild;
            InSyntaxQueue(queue, node);             // �Ƚ���һ���������

            while(node->m_rightBrother != NULL)     // ���ν���һ�����ӵ����ֵܼ������������
            {
                node = node->m_rightBrother;
                InSyntaxQueue(queue, node);
            }
            //InSyntaxQueue(queue, SYN_ENDL);
        }

    }
}





// ����parentRootΪ�����﷨�������ҵ���һ�����ս����Ҷ�ӽڵ�
SyntaxTreeNode* FindFirstChildTreeNode(SyntaxTree parentRoot)
{
    SyntaxTreeNode *treeNode = NULL;

    /// �������ҵ��﷨�����е�һ��Ҷ�ӽ��
    treeNode = parentRoot;
    while(treeNode->m_firstChild != NULL)          // �ҵ���һ���ս�����
    {
        treeNode = treeNode->m_firstChild;
    }

    // Ȼ���ҵ��������ƵĴʷ����
    if(treeNode == NULL)
    {
        #ifdef PROP_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // PROP_DEBUG_DEFINE
        fprintf(stderr, "���﷨�����е�һ��Ҷ�ӽڵ㲻���ս����\n");
        return NULL;
    }
    else if(treeNode->m_syntax.m_kind == SYNTAX_TERR_TERINAL)        // �﷨�����ĵ�һ��Ҷ�ӽ����뵫���ս����
    {
        return treeNode;
    }

    return treeNode;
}


// ����parentRootΪ�����﷨�������ҵ���һ�����ս����Ҷ�ӽڵ�
TupleNode* FindFirstChildTupleNode(SyntaxTree parentRoot)
{
    SyntaxTreeNode *treeNode = NULL;
    if((treeNode = FindFirstChildTreeNode(parentRoot)) != NULL)
    {
        return treeNode->m_syntax.m_data.m_tupleNode;
    }
    else
    {
        return NULL;
    }
//
//    SyntaxTreeNode *treeNode = NULL;
//
//    /// �������ҵ��﷨�����е�һ��Ҷ�ӽ��
//    treeNode = parentRoot;
//    while(treeNode->m_firstChild != NULL)          // �ҵ���һ���ս�����
//    {
//        treeNode = treeNode->m_firstChild;
//    }
//
//    // Ȼ���ҵ��������ƵĴʷ����
//    if(treeNode == NULL)
//    {
//        #ifdef PROP_DEBUG_DEFINE
//        FILE_FUNC_LINE( );
//        #endif // PROP_DEBUG_DEFINE
//        fprintf(stderr, "���﷨�����е�һ��Ҷ�ӽڵ㲻���ս����\n");
//        return NULL;
//    }
//    if(treeNode->m_syntax.m_kind == SYNTAX_TERR_TERINAL)        // �﷨�����ĵ�һ��Ҷ�ӽ����뵫���ս����
//    {
//        return treeNode->m_syntax.m_data.m_tupleNode;
//    }

}

// ����parentRootΪ�����﷨�������ҵ��ս��treinal��λ��
TupleNode* FindFirstSyntaxTreeTreinal(SyntaxTree parentRoot, TokenKind treinal)
{
    TupleNode      *headTupleNode = NULL;
    TupleNode      *tupleNode = NULL;

    /// �������ҵ��﷨�����е�һ��Ҷ�ӽ��d�Ĵʷ�ָ����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // FILE_FUNC_LINE( );
    // Ȼ���ҵ��������ƵĴʷ����
    if(headTupleNode == NULL)
    {
        #ifdef PROP_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // PROP_DEBUG_DEFINE
        fprintf(stderr, "���﷨�����е�һ��Ҷ�ӽڵ㲻���ս����\n");
        return NULL;
    }
    else        // �﷨�����ĵ�һ��Ҷ�ӽ����뵫���ս����
    {
        tupleNode = FindFirstTupleTreinal(headTupleNode, treinal);
        return tupleNode;
    }
}


// ����parentRootΪ�����﷨�������ҵ����һ�����ս����Ҷ�ӽڵ�
SyntaxTreeNode* FindFinalChildTreeNode(SyntaxTree parentRoot)
{
    SyntaxTreeNode *treeNode = NULL;

    /// �������ҵ��﷨���������һ��Ҷ�ӽ��
    treeNode = (SyntaxTreeNode *)parentRoot;
    while(treeNode->m_finalChild != NULL)          // �ҵ���һ���ս�����
    {
        treeNode = treeNode->m_finalChild;
    }

    // Ȼ���ҵ��������ƵĴʷ����
    if(treeNode == NULL)
    {
        #ifdef PROP_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // PROP_DEBUG_DEFINE
        fprintf(stderr, "���﷨���������һ��Ҷ�ӽڵ㲻���ս����\n");
        return NULL;
    }
    else if(treeNode->m_syntax.m_kind == SYNTAX_TERR_TERINAL)        // �﷨�����ĵ�һ��Ҷ�ӽ����뵫���ս����
    {
        return treeNode;
    }

    return treeNode;
}

// ����parentRootΪ�����﷨�������ҵ���һ�����ս����Ҷ�ӽڵ�
TupleNode* FindFinalChildTupleNode(SyntaxTree parentRoot)
{
    SyntaxTreeNode *treeNode = NULL;
    if((treeNode = FindFinalChildTreeNode(parentRoot)) != NULL)
    {
        return treeNode->m_syntax.m_data.m_tupleNode;
    }
    else
    {
        return NULL;
    }
}
