/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : Parser.h                                                       *
*   Description: CTools-SyntacicParser                                          *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/








#include "Parser.h"    //  #include "..\Parser\Parser.h"





/// �Դʷ���Ԫ����������﷨����
SyntaxTree ParseTuple(BinaryTuple douTuple)       // �ʷ���Ԫ����Ϣ
{
//#ifdef LEXICAL_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // LEXICAL_DEBUG_DEFINE

    // ����Ĵʷ�����ģ��
    TupleNode       *tupleNode = (TupleNode *)douTuple;       // ָ��ʷ���Ԫ���ͷ���

    // �﷨����ջ
    StateStack      *stateStack = CreateStateStack( );         // ״̬ջ -=> ���ÿһ����״̬�ź�
    SyntaxStack     *syntaxStack = CreateSyntaxStack( );         // ����ջ -=> ����Ѿ�ʶ��������﷨����

    // �﷨��ģ��
    SyntaxTreeNode  *parentNode = NULL;

    // �﷨������
    ActionNode      *actionpNode = NULL;        // ACTON״̬ת�ƽ��
    GoToNode        *gotopNode   = NULL;          // OTO״̬ת�ƽ��

    // ��Լʱ��׮����
    #ifdef PROP_REDUCTION_DEFINE                // ��ʼ����Ϣ -=�� �ڹ�Լͬʱ���еĲ�׮
    PropTable        propTable = CreatePropTable( );                  // ������׮��Ϣ��
    const char *destPropFname = PROP_FILE_NAME;                       // ��׮Ŀ���ļ�
    const char *srcPropFname = douTuple->m_tuple.m_coord.m_fileName;  // ����׮Դ�ļ�
    #endif // PROP_REDUCTION_DEFINE

    #ifdef PARSER_HELPS_DEFINE
    printf("*************************************************\n");
    printf("**  The File we Display is %10s   **\n", douTuple->m_tuple.m_data.m_fileName);       // ͷ����ָ����ָʾ���ļ���
    printf("**  The File we Display is %10s   **\n", douTuple->m_tuple.m_coord.m_fileName);       // ͷ����ָ����ָʾ���ļ���
    printf("*************************************************\n");
    PAUSE( );
    #endif



    // ջ��Ϣ���г�ʼ��
    ///PushGrammarInSyntaxStack(SyntaxStack, SYN_ANA_TREE_NULL);             // ��#ѹ��ջ��
    PushState(stateStack, (State)(0));                // ����ʼ״̬ѹ��ջ��

    for(tupleNode = tupleNode->m_next;          // ָ���һ���ʷ���Ϣ
        tupleNode != NULL; )                // ֻҪ�ʷ�ָ�벻Ϊ��
    {

//        if(IsProComTupleNode(tupleNode) == true)            // ��ǰ�����Ԥ����ָ��
//        {
//            tupleNode = SkipProComTupleNode(tupleNode);              // ����Ԥ����ָ��
//        }
        #ifdef PARSER_SHOWS_DEFINE
        printf("\n\n��ǰ����Ĵʷ���Ϣ:");
        ShowTupleNode(tupleNode);                // ��ʾ��ǰ����ʷ���Ϣ
        #endif         // CTOOLS_SHOWS_DEINFE

        #ifdef PARSER_DEBUG_DEFINE
        printf("��ʼ����ACTION[%d, %d]\n", TopState(stateStack), tupleNode->m_tuple.m_kind);
        #endif // PARSER_DEBUG_DEFINE


        if((actionpNode = ACTION(TopState(stateStack), tupleNode)) != NULL)                  // �жϵ�ǰ����״̬
        {
            #ifdef PARSER_SHOWS_DEFINE
            printf("ACTION[%d, %d] = action:%d, state:%d\n", TopState(stateStack), tupleNode->m_tuple.m_kind, (int)actionpNode->m_action, actionpNode->m_actState);
            #endif     // PARSER_HELPS_DEFINE
        }
        else
        {
            #ifdef PARSER_SHOWS_DEFINE
            printf("ACTION[%d, %d] = NULL\n", TopState(stateStack), tupleNode->m_tuple.m_kind, (int)actionpNode->m_action, actionpNode->m_actState);
            #endif     // PARSER_SHOWS_DEFINE
            fprintf(stderr, "��actionTable�Ҳ�����Ӧ����Ϣ, ����������ȷ�ԣ�����ActionTable����ȷ��\n");
            PAUSE( );
        }

        if(actionpNode->m_action == MOVING)     // ���������Ϣ״̬Ϊ�ƽ�-=>�����ǰACTION(״̬, �������) = S[i]
        {
            /// �ƽ� -=> ѹ��״̬�ͷ���
            #ifdef PARSER_SHOWS_DEFINE
            printf("���ڿ�ʼ�ƽ�....\n");
            #endif // PARSER_SHOWS_DEFINE

            PushTupleInSyntaxStack(syntaxStack, tupleNode);                // �ƽ�������� -=> ��������Ϣѹ�����ջ
            PushState(stateStack, actionpNode->m_actState);      // �ƽ�״̬ -=> ��״̬��Ϣѹ��״̬ջ


            tupleNode = tupleNode->m_next;                            // ����������һ���ʷ���Ϣ
        }
        else if(actionpNode->m_action == REDUCTION)   // ���������Ϣ״̬Ϊ��Լ-=>�����ǰACTION(״̬, �������) = R[i]
        {
            /// ��Լ -=>

            #ifdef PARSER_DEBUG_DEFINE
            ShowStateStack(stateStack);
            ShowSyntaxStack(syntaxStack);
            #endif // PARSER_DEBUG_DEFINE


            #ifdef PARSER_SHOWS_DEFINE          // ������Ϣ-=>������յڼ�������ʽ��Լ
            printf("���ڿ�ʼ��Լ....\n");
            printf("���յ�%d������ʽ��ʼ��Լ\n", actionpNode->m_actState);                          // ���յڸ�actInfo.m_state���ķ���ʼ��Լ
            #endif      // PARSER_SHOWS_DEFINE

            // ���Ƚ���Լ����ʽ���Ҳ���������ջ
            parentNode = InsertSyntaxTree(syntaxStack, actionpNode->m_actState);           // ���յ�actionpNode->m_actState������ʽ�����﷨����

            #ifdef PROP_REDUCTION_DEFINE
//            if(actionpNode->m_actState <= 219)
//            {
//                printf("��ǰ����ʽ���%d\n", actionpNode->m_actState);
//                PAUSE( );
//            }
            // ���յ�actionpNode->m_actState������ʽ����ʽ���﷨��������׮��Ϣ�����׮��Ϣ��
            PropRed(propTable, parentNode, actionpNode->m_actState);
            #endif // PROP_REDUCTION_DEFINE

            PopedSyntax(syntaxStack, (int)RightGrammarLength(actionpNode->m_actState));
            PopedState(stateStack, (int)RightGrammarLength(actionpNode->m_actState));

            // Ȼ���ٽ���Լ����ʽ����ѹ�����ջ
            //PushGrammarInSyntaxStack(SyntaxStack, (SyntaxKind)LeftGrammarData(actionpNode->m_actState));      // �����ķ�����ѹ��
            PushSynTreeNodeInSynStack(syntaxStack, parentNode);

            #ifdef PARSER_DEBUG_DEFINE
            printf("��ʼ����GOTO[%d, %d]\n", TopState(stateStack), LeftGrammarData(actionpNode->m_actState));
            #endif // PARSER_DEBUG_DEFINE

            // ��Լ����Ҫת��һ���µ�״̬���¿�ʼ, ����gotoTable��ѯ�����״̬, ���µ�״̬ѹ��״̬ջ��
            if((gotopNode = GOTO((int)TopState(stateStack), (SyntaxKind)LeftGrammarData(actionpNode->m_actState))) != NULL)           // ��Լ����Ҫת��һ���µ�״̬���¿���
            {
                #ifdef PARSER_SHOWS_DEFINE
                printf("GOTO[%d, %d] = goto%d\n", TopState(stateStack), LeftGrammarData(actionpNode->m_actState), gotopNode->m_gotoState);
                #endif      // PARSER_SHOWS_DEFINE
                PushState(stateStack, gotopNode->m_gotoState);                                    // ����״̬ѹ��״̬ջ��
            }
            else
            {
                #ifdef PARSER_SHOWS_DEFINE
                printf("GOTO[%d, %d] = NULL\n", TopState(stateStack), LeftGrammarData(actionpNode->m_actState));
                #endif // PARSER_SHOWS_DEFINE
                fprintf(stderr, "��gotoTable�Ҳ�����Ӧ����Ϣ, ����������ȷ�ԣ�����GoToTable����ȷ��\n");
                PAUSE( );
            }
        }
        else if(actionpNode->m_action == ACCEPT)               // ����������ķ���Ϣ
        {
            // ��ǰ�ַ�����ԼΪ��������
            printf("\nAccpet the Grammar\n");
            #ifdef PARSER_SHOWS_DEFINE
            printf("**********************************\n");
            printf("**\tACCEPT This Grammer\t**\n");
            printf("**********************************\n");
            #endif // PARSER_SHOWS_DEFINE

            DestroyStateStack(stateStack);                       // ����״̬ջ
            DestroySyntaxStack(syntaxStack);                       // ���ٷ���ջ
            break;
        }
        else if(actionpNode == NULL)
        {
            printf("\nThe Grammer you give is Wrong\n");
            DestroyStateStack(stateStack);                       // ����״̬ջ
            DestroySyntaxStack(syntaxStack);                       // ���ٷ���ջ
            break;
        }

//        #ifdef PARSER_DEBUG_DEFINE
//        PAUSE( );
//        #endif   // PARSER_DEBUG_DEFINE
    }

    #ifdef PROP_REDUCTION_DEFINE                // ��ʼ����Ϣ -=�� �ڹ�Լͬʱ���еĲ�׮
    #ifdef PROP_SHOWS_DEFINE
    ShowPropTable(propTable);       // ��ʾ��׮��Ϣ��
    #endif // PROP_REDUCTION_DEFINE
    #endif // PROP_SHOWS_DEFINE

    #ifdef PROP_REDUCTION_DEFINE
    WriteProp(propTable, destPropFname, srcPropFname);
    #endif // PROP_REDUCTION_DEFINE

//    printf("�������﷨��ͷ���%p\n", root);
//    PAUSE( );

    return (SyntaxTreeNode *)parentNode;
}


/// �Դʷ�������Ԫ������﷨������ͬʱ�ڹ�Լʱ���в�׮������׮��Ϣд��destFname��
SyntaxTree ParseTuplePropRed(BinaryTuple douTuple, const char *destFname)       // �ʷ���Ԫ����Ϣ
{
//#ifdef LEXICAL_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // LEXICAL_DEBUG_DEFINE

    // ����Ĵʷ�����ģ��
    TupleNode       *tupleNode = (TupleNode *)douTuple;       // ָ��ʷ���Ԫ���ͷ���

    // �﷨����ջ
    StateStack      *stateStack = CreateStateStack( );         // ״̬ջ -=> ���ÿһ����״̬�ź�
    SyntaxStack     *syntaxStack = CreateSyntaxStack( );         // ����ջ -=> ����Ѿ�ʶ��������﷨����

    // �﷨��ģ��
    SyntaxTreeNode  *parentNode = NULL;

    // �﷨������
    ActionNode      *actionpNode = NULL;        // ACTON״̬ת�ƽ��
    GoToNode        *gotopNode   = NULL;          // OTO״̬ת�ƽ��

    // ��Լʱ��׮����
    //#ifdef PROP_REDUCTION_DEFINE                // ��ʼ����Ϣ -=�� �ڹ�Լͬʱ���еĲ�׮
    PropTable        propTable = CreatePropTable( );                  // ������׮��Ϣ��
    const char       *destPropFname = destFname;                       // ��׮Ŀ���ļ�
    const char       *srcPropFname = douTuple->m_tuple.m_coord.m_fileName;  // ����׮Դ�ļ�
    //#endif // PROP_REDUCTION_DEFINE

    #ifdef PARSER_HELPS_DEFINE
    printf("*************************************************\n");
    printf("**  The File we Display is %10s   **\n", douTuple->m_tuple.m_data.m_fileName);       // ͷ����ָ����ָʾ���ļ���
    printf("**  The File we Display is %10s   **\n", douTuple->m_tuple.m_coord.m_fileName);       // ͷ����ָ����ָʾ���ļ���
    printf("*************************************************\n");
    PAUSE( );
    #endif



    // ջ��Ϣ���г�ʼ��
    ///PushGrammarInSyntaxStack(SyntaxStack, SYN_ANA_TREE_NULL);             // ��#ѹ��ջ��
    PushState(stateStack, (State)(0));                // ����ʼ״̬ѹ��ջ��

    for(tupleNode = tupleNode->m_next;          // ָ���һ���ʷ���Ϣ
        tupleNode != NULL; )                // ֻҪ�ʷ�ָ�벻Ϊ��
    {
//        if(IsProComTupleNode(tupleNode) == true)            // ��ǰ�����Ԥ����ָ��
//        {
//            tupleNode = SkipProComTupleNode(tupleNode);              // ����Ԥ����ָ��
//        }

        #ifdef PARSER_SHOWS_DEFINE
        printf("\n\n��ǰ����Ĵʷ���Ϣ:");
        ShowTupleNode(tupleNode);                // ��ʾ��ǰ����ʷ���Ϣ
        #endif         // PARSER_SHOWS_DEFINE

        #ifdef PARSER_DEBUG_DEFINE
        printf("��ʼ����ACTION[%d, %d]\n", TopState(stateStack), tupleNode->m_tuple.m_kind);
        #endif // PARSER_DEBUG_DEFINE
//        int top = TopState(stateStack);
//        if(top == 114 || top == 144 || top == 169 || top == 180 || top == 304 || top == 22 || top == 59)
//        {
//            FILE_FUNC_LINE( );
//            PAUSE( );
//        }

        if((actionpNode = ACTION(TopState(stateStack), tupleNode)) != NULL)                  // �жϵ�ǰ����״̬
        {
            #ifdef PARSER_SHOWS_DEFINE
            printf("ACTION[%d, %d] = action:%d, state:%d\n", TopState(stateStack), tupleNode->m_tuple.m_kind, (int)actionpNode->m_action, actionpNode->m_actState);
            #endif     // PARSER_HELPS_DEFINE
        }
        else
        {
            #ifdef PARSER_SHOWS_DEFINE
            printf("ACTION[%d, %d] = NULL\n", TopState(stateStack), tupleNode->m_tuple.m_kind, (int)actionpNode->m_action, actionpNode->m_actState);
            #endif     // PARSER_SHOWS_DEFINE

            ShowCoord(&(tupleNode->m_tuple.m_coord));
            printf("\n");
            printf("ACTION[%d, %d]\n", TopState(stateStack), tupleNode->m_tuple.m_kind);
            fprintf(stderr, "��actionTable�Ҳ�����Ӧ����Ϣ, ����������ȷ�ԣ�����ActionTable����ȷ��\n");
            PAUSE( );
        }

        if(actionpNode->m_action == MOVING)     // ���������Ϣ״̬Ϊ�ƽ�-=>�����ǰACTION(״̬, �������) = S[i]
        {
            /// �ƽ� -=> ѹ��״̬�ͷ���
            #ifdef PARSER_SHOWS_DEFINE
            printf("���ڿ�ʼ�ƽ�....\n");
            #endif // PARSER_SHOWS_DEFINE

            PushTupleInSyntaxStack(syntaxStack, tupleNode);                // �ƽ�������� -=> ��������Ϣѹ�����ջ
            PushState(stateStack, actionpNode->m_actState);      // �ƽ�״̬ -=> ��״̬��Ϣѹ��״̬ջ


            tupleNode = tupleNode->m_next;                            // ����������һ���ʷ���Ϣ
        }
        else if(actionpNode->m_action == REDUCTION)   // ���������Ϣ״̬Ϊ��Լ-=>�����ǰACTION(״̬, �������) = R[i]
        {
            /// ��Լ -=>

            #ifdef PARSER_DEBUG_DEFINE
            ShowStateStack(stateStack);
            ShowSyntaxStack(syntaxStack);
            #endif // PARSER_DEBUG_DEFINE


            #ifdef PARSER_SHOWS_DEFINE          // ������Ϣ-=>������յڼ�������ʽ��Լ
            printf("���ڿ�ʼ��Լ....\n");
            printf("���յ�%d������ʽ��ʼ��Լ\n", actionpNode->m_actState);                          // ���յڸ�actInfo.m_state���ķ���ʼ��Լ
            #endif      // PARSER_SHOWS_DEFINE

            // ���Ƚ���Լ����ʽ���Ҳ���������ջ
            parentNode = InsertSyntaxTree(syntaxStack, actionpNode->m_actState);           // ���յ�actionpNode->m_actState������ʽ�����﷨����

            //#ifdef PROP_REDUCTION_DEFINE
//            if(actionpNode->m_actState == 223)
//            {
//                printf("��ǰ����ʽ���%d\n", actionpNode->m_actState);
//                PAUSE( );
//            }
            // ���յ�actionpNode->m_actState������ʽ����ʽ���﷨��������׮��Ϣ�����׮��Ϣ��
            PropRed(propTable, parentNode, actionpNode->m_actState);
            //#endif // PROP_REDUCTION_DEFINE

            PopedSyntax(syntaxStack, (int)RightGrammarLength(actionpNode->m_actState));
            PopedState(stateStack, (int)RightGrammarLength(actionpNode->m_actState));

            // Ȼ���ٽ���Լ����ʽ����ѹ�����ջ
            //PushGrammarInSyntaxStack(SyntaxStack, (SyntaxKind)LeftGrammarData(actionpNode->m_actState));      // �����ķ�����ѹ��
            PushSynTreeNodeInSynStack(syntaxStack, parentNode);

            #ifdef PARSER_DEBUG_DEFINE
            printf("��ʼ����GOTO[%d, %d]\n", TopState(stateStack), LeftGrammarData(actionpNode->m_actState));
            #endif // PARSER_DEBUG_DEFINE

            // ��Լ����Ҫת��һ���µ�״̬���¿�ʼ, ����gotoTable��ѯ�����״̬, ���µ�״̬ѹ��״̬ջ��
            if((gotopNode = GOTO((int)TopState(stateStack), (SyntaxKind)LeftGrammarData(actionpNode->m_actState))) != NULL)           // ��Լ����Ҫת��һ���µ�״̬���¿���
            {
                #ifdef PARSER_SHOWS_DEFINE
                printf("GOTO[%d, %d] = goto%d\n", TopState(stateStack), LeftGrammarData(actionpNode->m_actState), gotopNode->m_gotoState);
                #endif      // PARSER_SHOWS_DEFINE
                PushState(stateStack, gotopNode->m_gotoState);                                    // ����״̬ѹ��״̬ջ��
            }
            else
            {
                #ifdef PARSER_SHOWS_DEFINE
                printf("GOTO[%d, %d] = NULL\n", TopState(stateStack), LeftGrammarData(actionpNode->m_actState));
                #endif // PARSER_SHOWS_DEFINE

                ShowCoord(&(tupleNode->m_tuple.m_coord));
                printf("\n");
                printf("��ʼ����GOTO[%d, %d]\n", TopState(stateStack), LeftGrammarData(actionpNode->m_actState));
                fprintf(stderr, "��gotoTable�Ҳ�����Ӧ����Ϣ, ����������ȷ�ԣ�����GoToTable����ȷ��\n");
                PAUSE( );
            }
        }
        else if(actionpNode->m_action == ACCEPT)               // ����������ķ���Ϣ
        {
            // ��ǰ�ַ�����ԼΪ��������
            #ifdef PARSER_SHOWS_DEFINE
            printf("**********************************\n");
            printf("**\tACCEPT This Grammer\t**\n");
            printf("**********************************\n");
            #endif // PARSER_SHOWS_DEFINE
            printf("*****Accept the Grammar*****\n");

            DestroyStateStack(stateStack);                       // ����״̬ջ
            DestroySyntaxStack(syntaxStack);                       // ���ٷ���ջ
            break;
        }
        else if(actionpNode == NULL)
        {
            printf("\nThe Grammer you give is Wrong\n");
            //DestroyStack(stateStack);                       // ����״̬ջ
            //DestroyStack(SyntaxStack);                       // ���ٷ���ջ
            break;
        }

        /// STEP BY STEP
//        #ifdef PARSER_DEBUG_DEFINE
//        PAUSE( );
//        #endif   // PARSER_DEBUG_DEFINE
    }

    #ifdef PROP_SHOWS_DEFINE
    ShowPropTable(propTable);       // ��ʾ��׮��Ϣ��
    #endif // PROP_SHOWS_DEFINE


    //#ifdef PROP_REDUCTION_DEFINE
    WriteProp(propTable, destPropFname, srcPropFname);          // ����׮��Ϣд���׮Ŀ���ļ�
    DestroyPropTable(propTable);                                // ���ٲ�׮��Ϣ��
    //#endif // PROP_REDUCTION_DEFINE

    return (SyntaxTreeNode *)parentNode;
}

/// ���ļ�fileName�����﷨����
SyntaxTree ParseFile(const char *sourFile)          // Դ�ļ�����
{
    SyntaxTree     syntaxRoot;
    #ifdef PARSER_HELPS_DEFINE
    printf("**********************************************************\n");
    printf("**  The file you want to syntax is \"%10s\"  **\n", sourFile);
    printf("**********************************************************\n");
    #endif // PARSER_HELPS_DEFINE

    BinaryTuple douTuple = NULL;               // ��Ԫ����Ϣ

    douTuple = BufferLexical(sourFile);      // ֱ�Ӵ���Դ�ļ�


    #ifdef PARSER_SHOWS_DEFINE
    VisitTuple(douTuple);            // ������Ԫ����Ϣ, ���Ҷ�Ԫ����ȷ��
    #endif // PARSER_SHOWS_DEFINE

    syntaxRoot = ParseTuple(douTuple);

    if(syntaxRoot != NULL)
    {
        #ifdef PARSER_SHOWS_DEFINE
        printf("�﷨�����%d\n", GetSyntaxTreeHeight(syntaxRoot));
        printf("�﷨�����%d\n", GetSyntaxTreeNodeCount(syntaxRoot));
        PAUSE( );
        #endif // PARSER_SHOWS_DEFINE



        //printf("������ʾ�﷨��\n");
        //ShowSyntaxTree(syntaxRoot);

        #ifdef PARSER_DEBUG_DEFINE
        printf("��������﷨��\n");
        PreOrderSytaxTree(syntaxRoot);
        PAUSE( );

        printf("��������﷨��\n");
        InOrderSyntaxTree(syntaxRoot);
        PAUSE( );

        printf("��������﷨��\n");
        PostOrderSyntaxTree(syntaxRoot);
        PAUSE( );
        #endif // PARSER_DEBUG_DEFINE

    }

    #ifdef PARSER_HELPS_DEFINE
    VERSION( );
    #endif          // LEXICAL_HELPS_DEFINE

    DestroyTuple(douTuple);                // ��ն�Ԫ��ռ�Ϊϵͳ��ʡ�ڴ�ռ�

    return syntaxRoot;                  // �Դʷ���Ԫ������﷨����
}


/// ���ļ�fileName�����﷨����, ͬʱ���в�׮����
SyntaxTree ParseFilePropRed(const char *destFname, const char *sourFname)          // Դ�ļ�����
{
     SyntaxTree     syntaxRoot;
    #ifdef PARSER_HELPS_DEFINE
    printf("**********************************************************\n");
    printf("**  The file you want to syntax is \"%10s\"  **\n", sourFname);
    printf("**********************************************************\n");
    #endif // PARSER_HELPS_DEFINE

    BinaryTuple douTuple = NULL;               // ��Ԫ����Ϣ

    /// ��Դ�ļ�sourFname�ʷ�����
    douTuple = BufferLexical(sourFname);      // ֱ�Ӵ���Դ�ļ�

    #ifdef PARSER_SHOWS_DEFINE
    VisitTuple(douTuple);            // ������Ԫ����Ϣ, ���Ҷ�Ԫ����ȷ��
    #endif // PARSER_SHOWS_DEFINE

    /// ��Դ�ļ������﷨������������׮��Ϣд��destFname
    syntaxRoot = ParseTuplePropRed(douTuple, destFname);


    #ifdef PARSER_HELPS_DEFINE
    VERSION( );
    #endif          // LEXICAL_HELPS_DEFINE

    DestroyTuple(douTuple);                // ��ն�Ԫ��ռ�Ϊϵͳ��ʡ�ڴ�ռ�

    return syntaxRoot;                  // �Դʷ���Ԫ������﷨����
}


/// �﷨��������������
bool TestOfParse( )
{
    return ParseFile("TEST/test0.c");
}





/// 0.6.0����
/// �﷨����ʱ����Ҫ��Ԥ����ָ������
/// ��������Ԥ�����������
TupleNode* SkipProComTupleNode(TupleNode *tupleNode)
{
    assert(tupleNode->m_tuple.m_kind == POUND_SEPARATOR             // Ԥ����ָ����'#'��ͷ
        && tupleNode->m_next->m_tuple.m_data.m_keyCode == PROCOM);   // '#'����һ��ָ��ΪԤ��������

    int line = tupleNode->m_tuple.m_coord.m_fileLine;

    while( 1 )
    {
        //ShowTupleData(tupleNode);
        tupleNode = tupleNode->m_next;

        if(tupleNode->m_tuple.m_coord.m_fileLine != line)           // ����ָ��������Ϊ��λ��
        {
            if(tupleNode->m_last->m_tuple.m_kind == BACKSLASH_SEPARATOR)       // '\'���з��ſ�����Ϊ��Ԥ����ռ�ö���
            {
                line = tupleNode->m_tuple.m_coord.m_fileLine;
            }
            else            // ������һ���µ��У�����һ��û�����У���˵��Ԥ����ָ��Ľ���
            {
                break;
            }
        }
    }

    return tupleNode;
}
