/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : BinaryTuple.c                                                  *
*   Description: CTools                                                         *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/




#include "BinaryTuple.h"


#ifndef DEBUG
#define DEBUG
#endif


/// Literal�ĺ�����������
#ifdef PUBLIC_and_PRIVATE
#
#
// ���ÿ����Ԫ��Node������Ϣ
PRIVATE void
FreeNode(TupleNode *pNode);                 // ����ǰ�ʷ�������Ϣɾ��
#define free_node   FreeNode
#
#
/// ����Ԫ������Ϣ����ifp��ָ���ļ���
PRIVATE CToolsFILE
WriteNode(
          TupleNode *pNode,             // �ʷ���Ԫ����
          CToolsFILE fp);               // �ļ�ָ��
#
#
/// ����Ԫ������Ϣ��ifp��ָ���ļ��ж�ȡ����
PRIVATE TupleNode*                      // ���ؽ���ָ��
ReadNode(
         CToolsFILE fp);               // �ļ�ָ��
#
#
/// ���ٶ�Ԫ����Ϣ
void
FinitTuple(
           BinaryTuple douTuple);           // ��Ԫ����β����
#define finit_tuple FinitTuple
#
#
#endif


// ������TokenKind�е��ⲿ����
extern const char keyword[MAX_KEYWORD_COUNT][MAX_KEYWORD_SIZE];         // ���еĹؼ��ֱ���
extern const char procom[MAX_PROCOM_COUNT][MAX_PROCOM_SIZE];           // Ԥ����ָ���
extern const char operate[MAX_OPERATE_COUNT];             // �����������
extern const char allOperator[MAX_OPERATE_COUNT][MAX_OPERATE_SIZE];      // ���������
extern const char separator[MAX_SEPARAROR_COUNT];         // �ֽ������



/// ��ʼ����Ԫ����Ϣ
BinaryTuple InitTuple(const char* sourFile)
{
    BinaryTuple douTuple = (TupleNode *)malloc(sizeof(TupleNode));       // Ϊͷ��㿪�ٿռ�

    // Ϊ�洢�ļ������ٱ�Ҫ�Ŀռ�
    char *fileName = (char *)malloc(strlen(sourFile) + sizeof(1));
    strcpy(fileName, sourFile);       // �ļ���д��[]

    // �ʷ�Ԫ�鸳ֵ
    douTuple->m_tuple.m_kind = HEAD;     // ͷ��ŵ���HEAD��ʶ

    douTuple->m_tuple.m_data.m_fileName = fileName;         // �ļ���ָ��ָ��ǰ���ļ���
    // ��Ϣλ�ñ�ʶ��ֵ
    douTuple->m_tuple.m_coord.m_fileName = fileName;                // �ʷ�λ�ñ�ʶ�ļ���ͬ��ָ���ļ���
    douTuple->m_tuple.m_coord.m_fileLine = -1;                      // ��ʼ���ļ�����Ϊ0

    douTuple->m_next = NULL;
    douTuple->m_last = NULL;

    return douTuple;
}

/// ���ٶ�Ԫ����Ϣ
void FinitTuple(BinaryTuple douTuple)
{
    TupleNode *pNode = douTuple;

    // ����ͷ���ռ�
    if(pNode != NULL)
    {
        if(pNode->m_tuple.m_data.m_fileName != NULL)          // ����Ϊ�洢�ļ������ٵĿռ�
        {
            free(pNode->m_tuple.m_data.m_fileName);
        }
        free(pNode);           // ����ͷ���
    }
}


/// ��һ���﷨��Ϣ[�ؼ���, �����, �ֽ��]���뵽��Ԫ����
TupleNode* InsertTupleKey(TupleNode *pNode, TokenKind kind, int keyCode, Coord *coord)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // LEXICAL_DEBUG_DEFINE

    TupleNode *newNode = NULL;

    if((newNode = (TupleNode* )malloc(sizeof(TupleNode))) != NULL)         // ��Ҫ������½��
    {
        //printf("keyCode = %d\n", keyCode);
        // ���½�㸳ֵ
        newNode->m_tuple.m_kind = (enum TokenKind)((int)kind + keyCode);      // ��ǰ������[�����OPERATOR, �ֽ����SEPARATOE, ]
        newNode->m_tuple.m_data.m_keyCode = (int)kind/**KEYWORD | PROCOM | SEPARATOR | OPERATE**/;        // ���㵱ǰ�ַ������ֱ���

//      newNode->m_tuple.m_coord.m_fileName = coord->m_fileName;    // �õ�ǰ�ʷ�λ�õ��ļ�ָ���ַָ���ļ����Ĵ洢��ַ
//      newNode->m_tuple.m_coord.m_fileLine = coord->m_fileLine;    // �ļ����кŸ�ֵ
//      newNode->m_tuple.m_coord.m_fileBegOffset = coord->m_fileBegOffset;      // �ʷ���Ϣ��ʼλ�õ�ƫ����
//      newNode->m_tuple.m_coord.m_fileEndOffset = coord->m_fileEndOffset;      // �ʷ���Ϣ����λ�õ�ƫ����

        newNode->m_tuple.m_coord = *coord;
        if(kind == SEPARATOR)                               // [�ؼ��֣����������ʶ�����ֽ����������ֻ�зֽ�������ǵ�����]
        {
            newNode->m_tuple.m_coord.m_fileEndOffset++;      // �ʷ���Ϣ����λ�õ�ƫ������1ָ����һλ��
        }

        // ָ��������˫��ѭ������Ľ���
        newNode->m_next = pNode->m_next/* = NULL*/;
        newNode->m_last = pNode;
        if(pNode->m_next != NULL)
        {
            pNode->m_next->m_last = newNode;
        }
        pNode->m_next = (TupleNode *)newNode;

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ӵ���Ϣ��[%d, %d]", kind, newNode->m_tuple.m_kind);
        printf("��¼�������к�LINE = %d\n", newNode->m_tuple.m_coord.m_fileLine);
        #endif
    }
    else
    {
        FILE_FUNC_LINE( );
        fprintf(stderr, "���ٴʷ���Ԫ����ʧ��\n");
    }

    return newNode;
}

/// ��һ��������Ϣ���뵽��Ԫ����
TupleNode* InsertTupleLiteral(TupleNode *pNode, char *token, Coord *coord, TokenKind kind)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // LEXICAL_DEBUG_DEFINE
    // ������Ԫ�����Ϣ
    TupleNode *newNode = NULL;

    if((newNode= (TupleNode* )malloc(sizeof(TupleNode))) != NULL)
    {
        // ȷ����ǰ������Ϣ������
        if(kind == CONST)
        {
            newNode->m_tuple.m_kind = CONST;           // ��ǰ��ϢΪ����
        }
        else
        {
            newNode->m_tuple.m_kind = kind;
        }

        newNode->m_tuple.m_data.m_constNum = token;         // ֱ���ó���ָ����ָ���ַ����ĵ�ַ

//      newNode->m_tuple.m_coord.m_fileName = coord->m_fileName;    // �õ�ǰ�ʷ�λ�õ��ļ�ָ���ַָ���ļ����Ĵ洢��ַ
//      newNode->m_tuple.m_coord.m_fileLine = coord->m_fileLine;    // �ļ����кŸ�ֵ
//      newNode->m_tuple.m_coord.m_fileBegOffset = coord->m_fileBegOffset;      // �ʷ���Ϣ��ʼλ�õ�ƫ����
//      newNode->m_tuple.m_coord.m_fileEndOffset = coord->m_fileEndOffset;      // �ʷ���Ϣ����λ�õ�ƫ����
        newNode->m_tuple.m_coord = *coord;

        // ָ��������˫��ѭ������Ľ���
        newNode->m_next = pNode->m_next/* = NULL*/;
        newNode->m_last = pNode;
        if(pNode->m_next != NULL)
        {
            pNode->m_next->m_last = newNode;
        }
        pNode->m_next = (TupleNode *)newNode;
        //pNode = newNode;                // ��pNode����ָ��β���

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ӵ���Ϣ��[%d, %d]", kind, newNode->m_tuple.m_kind);
        printf("��¼�������к�LINE = %d\n", newNode->m_tuple.m_coord.m_fileLine);
        #endif
    }
    else
    {
        FILE_FUNC_LINE( );
        fprintf(stderr, "���ٴʷ���Ԫ����ʧ��\n");
    }

    return newNode;
}

/// ��һ����ʶ�����뵽��Ԫ����
TupleNode* InsertTupleId(TupleNode *pNode, char *token, Coord *coord)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // LEXICAL_DEBUG_DEFINE
    // ������Ԫ�����Ϣ
    TupleNode *newNode = NULL;

    if((newNode = (TupleNode* )malloc(sizeof(TupleNode))) != NULL)
    {

        // ��ǰָ����ֵ
        newNode->m_tuple.m_kind = IDENTIFIER;           // ��ǰ��ϢΪ��ʶ
        newNode->m_tuple.m_data.m_identifier = token;           // ֱ����ָ����ָ���ַ����ĵ�ַ

//      newNode->m_tuple.m_coord.m_fileName = coord->m_fileName;    // �õ�ǰ�ʷ�λ�õ��ļ�ָ���ַָ���ļ����Ĵ洢��ַ
//      newNode->m_tuple.m_coord.m_fileLine = coord->m_fileLine;    // �ļ����кŸ�ֵ
//      newNode->m_tuple.m_coord.m_fileBegOffset = coord->m_fileBegOffset;      // �ʷ���Ϣ��ʼλ�õ�ƫ����
//      newNode->m_tuple.m_coord.m_fileEndOffset = coord->m_fileEndOffset;      // �ʷ���Ϣ����λ�õ�ƫ����
        newNode->m_tuple.m_coord = *coord;


        // ָ��������˫��ѭ������Ľ���
        newNode->m_next = pNode->m_next/* = NULL*/;
        newNode->m_last = pNode;
        if(pNode->m_next != NULL)
        {
            pNode->m_next->m_last = newNode;
        }
        pNode->m_next = (TupleNode *)newNode;
        //pNode = newNode;                // ��pNode����ָ��β���

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ӵ���Ϣ��[%d, %s]", IDENTIFIER, newNode->m_tuple.m_data.m_identifier);
        printf("��¼�������к�LINE = %d\n", newNode->m_tuple.m_coord.m_fileLine);
        #endif
    }
    else
    {
        FILE_FUNC_LINE( );
        fprintf(stderr, "���ٴʷ���Ԫ����ʧ��\n");
    }
    return newNode;
}


// ���ÿ����Ԫ��Node������Ϣ
void ShowTupleNode(TupleNode *pNode)
{

//    SHOW_FILE_NAME(pNode->m_tuple.m_coord.m_fileName);
//    printf("Line = %d  ", pNode->m_tuple.m_coord.m_fileLine);
//    printf("Begi = %d ", pNode->m_tuple.m_coord.m_fileBegOffset);
//    printf("Endl = %d ", pNode->m_tuple.m_coord.m_fileEndOffset);

    ShowCoord(&(pNode->m_tuple.m_coord));
    ShowTupleData(pNode);
    printf("\n");

}


/// �����ʷ���Ԫ����
void VisitTuple(BinaryTuple douTuple)
{
    #ifdef LEXICAL_HELPS_DEFINE      // ���ð���������ʷ���Ϣ����Ŀ
    FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
    printf("\t\t**********************************************\n");
    printf("\t\t*   The Lexical the sourFile has%04d words   *\n", douTuple->m_tuple.m_coord.m_fileLine);
    printf("\t\t**********************************************\n");
    PAUSE( );
    #endif // CTOOLS_HELP_DEFINE
    if(douTuple == NULL)
    {
        return ;
    }

    TupleNode *pNode = (TupleNode *)douTuple->m_next;

    while(pNode != NULL)
    {
        ShowTupleNode(pNode);
        pNode = (TupleNode *)pNode->m_next;      // ָ����һ��ָ����
    }
}





// ���ÿ����Ԫ��Node������Ϣ
void FreeNode(TupleNode *pNode)
{
    if(pNode->m_next == NULL                            // ���һ���ʷ���Ϣ��ʱ����Ҫ��λ����Ϣ���ļ���������
    || pNode->m_tuple.m_coord.m_fileName != pNode->m_next->m_tuple.m_coord.m_fileName)  // ��һ���ʷ�λ����Ϣ���ļ����뵱ǰ�ʷ��������ļ�����ͬʱ
    {
        #ifdef LEXICAL_DEBUG_DEFINE
        printf("�����˴ʷ�λ����Ϣ���ļ���ָ����\n");
        #endif // LEXICAL_DEBUG_DEFINE
        //free(pNode->m_tuple.m_coord.m_fileName);
    }
        /// 0.3.4֮�����������Ҫ���¶���
    switch((int)pNode->m_tuple.m_kind)          // ���ݵ�ǰ�˷����ı���
    {
		case TOKEN_NULL              :
		case UNKNOW                  :
		case TOKEN_END               :
		case ARRAY                   :
		case FUNCTION                :
		case PARAMETERS              :
        case POINT                   :
		{
			break;
		}

		case HEAD                    :
		{
            free(pNode->m_tuple.m_data.m_fileName);
            // free(pNode->m_tuple.m_coord.m_fileName);     // ����ָ����ʹ�õ���ͬ���ڴ�ռ�
            break;
		}

		case IDENTIFIER              :                  // ��ʶ����
		{
            free(pNode->m_tuple.m_data.m_identifier);
            break;
		}

		case STRING_CONST           :
        {
            free(pNode->m_tuple.m_data.m_constNum);
            break;
        }
        default                    :
        {
            break;
        }
    }
    free(pNode);                // �����ݵĽ����Ϣɾ��
}


/// ����ʷ���Ԫ����Ϣ
bool DestroyTuple(BinaryTuple douTuple)
{
    #ifdef LEXICAL_HELPS_DEFINE      // ���ð���������ʷ���Ϣ����Ŀ
    FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
    printf("\t\t**********************************************\n");
    printf("\t\t*   The Lexical the sourFile has%04d words   *\n", douTuple->m_tuple.m_kind); // ͷ��������Ϣ�Ǵʷ�������Ŀ
    printf("\t\t**********************************************\n");
    printf("Starting Destroy BinaryTuple......\b\b");
    PAUSE( );
    #endif  // CTOOLS_HELP_DEFINE

    #ifdef LEXICAL_SHOWS_DEFINE
    int count = 0;
    #endif
    if(douTuple == NULL)
    {
        ///printf("Դ�ļ��п��ܳ��ִ���,�ʷ���Ԫ���Ѿ�������, �����ٴ�����\n");
        return false;
    }

    TupleNode *pNode = (TupleNode *)douTuple->m_next, *nextNode = NULL;

    while(pNode != NULL)
    {
        #ifdef LEXICAL_SHOWS_DEFINE
        printf("delete the %d tuple node  -=>  ", ++count);
        ShowTupleData(pNode);
        #endif

        nextNode = (TupleNode *)pNode->m_next;           // ������һ��������Ϣ
        FreeNode(pNode);                        // ɾ�����
        pNode = nextNode;                   // ָ����һ�����

    }

    FinitTuple(douTuple);       // �Դʷ���Ԫ�������β
    douTuple = NULL;

    return true;
}


/// ����Ԫ������Ϣ����ifp��ָ���ļ���
CToolsFILE WriteNode(TupleNode *pNode, CToolsFILE fp)               // �ļ�ָ��
{
    if(pNode == NULL || fp == NULL)     // �������Ϸ�
    {
        return NULL;
    }

    CToolsWrite(&(pNode->m_tuple.m_kind), sizeof(pNode->m_tuple.m_kind), 1, fp);        // ���ֱ���д���ļ���
    CToolsWrite(&(pNode->m_tuple.m_data), sizeof(pNode->m_tuple.m_data), 1, fp);            // д���ļ���Ϣ


    return fp;              // �����ļ�ָ�����Ϣ
}


/// ����Ԫ������Ϣ��ifp��ָ���ļ��ж�ȡ����
TupleNode *ReadNode(CToolsFILE fp)               // �ļ�ָ��
{
    if(fp == NULL)     // �������Ϸ�
    {
        return NULL;
    }

    TupleNode *pNode = (TupleNode *)malloc(sizeof(TupleNode));          // Ϊ��ǰ��Ϣ���ٿռ�

    CToolsRead(&(pNode->m_tuple.m_kind), sizeof(pNode->m_tuple.m_kind), 1, fp);        // ���ֱ���д���ļ���
    CToolsRead(&(pNode->m_tuple.m_data), sizeof(pNode->m_tuple.m_data), 1, fp);            // д���ļ���Ϣ


    return pNode;              // ���شʷ�������Ϣ
}


/// ���ʷ���Ԫ����Ϣ���ȥ�ƶ����ļ���
void WriteTupleFile(BinaryTuple douTuple, char *fname)           // ������Ĵʷ��ļ�
{
    if((int)douTuple->m_tuple.m_kind == 0)              // ͷ�����ֱ�����m_kind��ʾ����Ԫ����Ŀ
    {
        printf("��ǰ�ʷ���Ϣ��Ԫ��Ϊ��, �޷�����Ϣд���ļ���\n");
        //return NULL;
    }

    CToolsFILE ofp = CToolsOpen(fname, WRITE_ONLY_BINARY);       // ��һ������ļ�

    // д��ʷ���Ԫ���ļ�ͷ��Ϣ
    fwrite(TUPLE_MAGIC_NUM, sizeof(TUPLE_MAGIC_NUM), 1, ofp);      // �ʷ���Ԫ���ļ���ǰ10���ֽ�Ϊħ��"ctools.tup"

    TupleNode *pNode = NULL;            // ��ͷ��㿪ʼ
    for(pNode = (TupleNode*)douTuple;                // ��ͷ��㿪ʼ
        pNode != NULL && WriteNode(pNode, ofp) != NULL;    // ֻҪ��ǰ��㲻Ϊ��, �ͽ������Ϣ����ofp��ָ����ļ���
        pNode = pNode->m_next);                    // ֻҪ��ǰ��㲻Ϊ��


    #ifdef LEXICAL_HELPS_DEFINE          // ���ð�����-=>��ʾ�ʷ���Ϣ�Ѿ�д���ļ�
    FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
    printf("\t\t************************************************\n");
    printf("\t\t*  write the tuple infomation in file already  *\n");
    printf("\t\t************************************************\n");
    PAUSE( );
    #endif // LEXICAL_HELP_DEFINE
    CToolsClose(ofp);               // �ر��ļ�ָ��

    //return ofp;             // �����ļ���ָ��
}


/// ��ָ���ļ��ж�ȡ�ʷ���Ԫ����Ϣ
BinaryTuple ReadTupleFile(char *fname)           // ������Ĵʷ��ļ�
{
    CToolsFILE ifp = CToolsOpen(fname, READ_ONLY_BINARY);       // ��һ������ļ�

    // д��ʷ���Ԫ���ļ�ͷ��Ϣ
    fseek(ifp, sizeof(TUPLE_MAGIC_NUM), SEEK_SET);                  // ������ʼ��10���ֽڵ�ħ��

    ReadNode(ifp);
    CToolsClose(ifp);               // �ر��ļ�ָ��
    return NULL;                     // ���شʷ���Ԫ��
}



BinaryTuple InsertEndToken(TupleNode *pNode)
{
    TupleNode *newNode = (TupleNode* )malloc(sizeof(TupleNode));

    // ��ǰָ����ֵ
    newNode->m_tuple.m_kind = TOKEN_END;           // ��ǰ��ϢΪ��ʶ
    newNode->m_tuple.m_data.m_keyCode = TOKEN_END;           // ֱ����ָ����ָ���ַ����ĵ�ַ

    newNode->m_tuple.m_coord.m_fileName = "";    // �õ�ǰ�ʷ�λ�õ��ļ�ָ���ַָ���ļ����Ĵ洢��ַ
    newNode->m_tuple.m_coord.m_fileLine = CToolsIsEOF;    // �ļ����кŸ�ֵ
    newNode->m_tuple.m_coord.m_fileBegOffset = CToolsIsEOF;      // �ʷ���Ϣ��ʼλ�õ�ƫ����
    newNode->m_tuple.m_coord.m_fileEndOffset = CToolsIsEOF;      // �ʷ���Ϣ����λ�õ�ƫ����

    newNode->m_next = NULL;              // �½���ָ�����ÿ�

    // �����½��������������ϵ
    pNode->m_next = (TupleNode *)newNode;        // ����ǰβ����ָ����ָ��ս����Ľ��, Ҳ����˵����newNode��β���
    pNode = newNode;                // ��pNode����ָ��β���

    return pNode;
}

//  �жϵ�ǰ�ڵ��ǲ���END�ʷ��ڵ�
bool IsEndToken(TupleNode *pNode)
{
    return (pNode->m_tuple.m_kind == TOKEN_END
         || pNode->m_tuple.m_data.m_keyCode == TOKEN_END);           // ֱ����ָ����ָ���ַ����ĵ�ַ
}

// ���ÿ����Ԫ��Node������Ϣ
void ShowTupleData(TupleNode *pNode)
{
 /// 0.3.4֮�����������Ҫ���¶���
    switch((int)pNode->m_tuple.m_kind)          // ���ݵ�ǰ�˷����ı���
    {
        case TOKEN_END               :                  // ��ʶ����
		{
            //printf("[%d, %d]", TOKEN_END, pNode->m_tuple.m_data.m_keyCode);
            printf("[END, END]", TOKEN_END, pNode->m_tuple.m_data.m_keyCode);
			break;
		}
		case TOKEN_NULL              :
		case UNKNOW                  :
		case ARRAY                   :
		case FUNCTION                :
		case PARAMETERS              :
        case POINT                   :
		{
			break;
		}

		case HEAD                    :
		{
		    printf("COUNT = %d", pNode->m_tuple.m_coord.m_fileLine);
		    printf("COUNT = %d", pNode->m_tuple.m_data.m_keyCode);
			break;
		}

		case IDENTIFIER              :                  // ��ʶ����
		{
            printf("[%d, %s]", IDENTIFIER, pNode->m_tuple.m_data.m_identifier);
			break;
		}

		case KEYWORD                 :                  /// �ؼ�����Ϣ
		case AUTO_KEYWORD            :
        case BOOL_KEYWORD            :
		case BREAK_KEYWORD           :
		case CASE_KEYWORD            :
		case CHAR_KEYWORD            :
		case CONST_KEYWORD           :
		case CONTINUE_KEYWORD        :
		case DEFAULT_KEYWORD         :
		case DO_KEYWORD              :
		case DOUBLE_KEYWORD          :
		case ELSE_KEYWORD            :
		case ENUM_KEYWORD            :
		case EXTERN_KEYWORD          :
		case FLOAT_KEYWORD           :
		case FOR_KEYWORD             :
		case GOTO_KEYWORD            :
		case IF_KEYWORD              :
		case INLINE_KEYWORD          :
		case INT_KEYWORD             :
		case LONG_KEYWORD            :
		case REGISTER_KEYWORD        :
		case RETURN_KEYWORD          :
		case SHORT_KEYWORD           :
		case SIGNED_KEYWORD          :
		case SIZEOF_OPERATE          :
		case STATIC_KEYWORD          :
		case STRUCT_KEYWORD          :
		case SWITCH_KEYWORD          :
		case TYPEDEF_KEYWORD         :
		case UNION_KEYWORD           :
		case UNSIGNED_KEYWORD        :
		case VOID_KEYWORD            :
		case VOLATILE_KEYWORD        :
		case WHILE_KEYWORD           :
        case _BOOL_KEYWORD           :
        case _COMPLEX_KEYWORD        :
        case _IMAGINARY_KEYWORD      :
        {
            int pos = pNode->m_tuple.m_kind - pNode->m_tuple.m_data.m_keyCode;
            printf("[%d, %s]", KEYWORD, keyword[pos]);
            printf("[%d, %d]", pNode->m_tuple.m_data.m_keyCode, pNode->m_tuple.m_kind);
            break;
        }

		case OPERATE                 :                  /// �������
		case COMMA_OPERATE           :                  // ,
		case ASSIGN_OPERATE          :                  // =
		case ADD_ASSIGN_OPERATE      :                  // +=
		case SUB_ASSIGN_OPERATE      :                  // -=
		case MUL_ASSIGN_OPERATE      :                  // *=
		case DIV_ASSIGN_OPERATE      :                  // /=
		case MOD_ASSIGN_OPERATE      :                  // %=
		case BITOR_ASSIGN_OPERATE    :                  // |=
		case BITXOR_ASSIGN_OPERATE   :                  // ^=
		case BITAND_ASSIGN_OPERATE   :                  // &=
		case RSHIFT_ASSIGN_OPERATE   :                  // >>=
		case LSHIFT_ASSIGN_OPERATE   :                  // <<=
		case QUESTION_OPERATE        :                  // ?
		case COLON_OPERATE           :                  // :
		case OR_OPERATE              :                  // ||
		case AND_OPERATE             :                  // &&
		case BITOR_OPERATE           :                  // |
		case BITXOR_OPERATE          :                  // ^
		case BITAND_OPERATE          :                  // &
		case EQUAL_OPERATE           :                  // ==
		case UNEQUAL_OPERATE         :                  // !=
		case GREATER_OPERATE         :                  // >
		case GREATER_EQUAL_OPERATE   :                  // >=
		case LESS_OPERATE            :                  // <
		case LESS_EQUAL_OPERATE      :                  // <=
		case RSHIFT_OPERATE          :                  // >>
		case LSHIFT_OPERATE          :                  // <<
		case ADD_OPERATE             :                  // +
		case SUB_OPERATE             :                  // -
		case MUL_OPERATE             :                  // *
		case DIV_OPERATE             :                  // /
		case MOD_OPERATE             :                  // %
		case NOT_OPERATE             :                  // !
		case COMP_OPERATE            :                  // ~
		case INC_OPERATE             :                  // ++
		case DEC_OPERATE             :                  // --
//		case RPAREN_OPERATE          :                  // )
//		case LPAREN_OPERATE          :                  // (
//        case RBRACKET_OPERATE        :                  // ]
//		case LBRACKET_OPERATE        :                  // [
		case DOT_OPERATE             :                  // .
        case POINT_TO_OPERATE        :                  // ->
		case ELLIPSE_OPERATE         :                  // ...
		{
            int pos = pNode->m_tuple.m_kind - pNode->m_tuple.m_data.m_keyCode;
            printf("[%d, %s]", OPERATE, allOperator[pos]);
            printf("[%d, %d]", pNode->m_tuple.m_data.m_keyCode, pNode->m_tuple.m_kind);
			break;
		}

		case SEPARATOR               :
        case SPACE_SEPARATOR         :
		case LBRACE_SEPARATOR        :
		case RBRACE_SEPARATOR        :
		case SEMICOLON_SEPARATOR     :
		case POUND_SEPARATOR         :
        case SINGLE_QUOTE_SEPARATOR  :
        case DOUBLE_QUOTE_SEPARATOR  :
		case NEWLINE_SEPARATOR       :
//		case ELLIPSE_SEPARATOR       :
        case RPAREN_OPERATE          :                  // )
		case LPAREN_OPERATE          :                  // (
        case RBRACKET_OPERATE        :                  // ]
		case LBRACKET_OPERATE        :                  // [
		{
            int pos = pNode->m_tuple.m_kind - pNode->m_tuple.m_data.m_keyCode;
            printf("[%d, %c]", SEPARATOR, separator[pos]);
            printf("[%d, %d]", pNode->m_tuple.m_data.m_keyCode, pNode->m_tuple.m_kind);
            break;
		}

		case CONST                   :
		case INT_CONST               :
		case UINT_CONST              :
		case LONG_CONST              :
		case ULONG_CONST             :
		case LLONG_CONST             :
		case ULLONG_CONST            :
		case FLOAT_CONST             :
		case DOUBLE_CONST            :
		case LDOUBLE_CONST           :
		case CHAR_CONST              :
		case WCHAR_CONST             :
		case STRING_CONST            :
        {
            printf("[%d, %s]", pNode->m_tuple.m_kind, pNode->m_tuple.m_data.m_constNum);
            break;
        }
		case ENUM_CONST              :
		{
			break;
		}
    }
}


// ����pNodeΪ��ʼ�Ĵʷ���Ԫ�������У���������ҵ�����Ϊ�ս��treinal�Ľ��
TupleNode* FindFirstTupleTreinal(TupleNode *pNode, TokenKind terinal)
{
    TupleNode *tupleNode = pNode;

    while(tupleNode != NULL)     // �������Ƶ�������IDENTIFIER
    {
        if(tupleNode->m_tuple.m_kind == terinal
       || tupleNode->m_tuple.m_data.m_keyCode == terinal)
        {
            break;
        }
        tupleNode = tupleNode->m_next;
    }

    if(tupleNode == NULL)
    {
        #ifdef PROP_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // PROP_DEBUG_DEFINE
        fprintf(stderr, "�ڴʷ���Ԫ�����Ҳ����ս��%d\n", terinal);
        return NULL;
    }
    else if(tupleNode->m_tuple.m_kind == terinal
       || tupleNode->m_tuple.m_data.m_keyCode == terinal)
    {

        return tupleNode;
    }

    return tupleNode;
}



// ����pNodeΪ��ʼ�Ĵʷ���Ԫ�������У� ������ҵ��ҵ���count������Ϊ�ս��terinal�Ľ��
TupleNode* FindTupleTreinal(TupleNode *pNode, TokenKind terinal, int count)
{
    int         num = 0;
    TupleNode *tupleNode = pNode;

    while(tupleNode != NULL)     // find in the tuple nodes...
    {
        if(tupleNode->m_tuple.m_kind == terinal
       || tupleNode->m_tuple.m_data.m_keyCode == terinal)
        {
            num++;
            if(num == count)            // break this "WHILE", when you have find count "TERINALS"
            {
                break;
            }
        }
        tupleNode = tupleNode->m_next;
        //num++;
    }

    //
    if(tupleNode == NULL)
    {
        #ifdef PROP_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // PROP_DEBUG_DEFINE
        fprintf(stderr, "�ڴʷ���Ԫ�����Ҳ����ս��%d\n", terinal);
        return NULL;
    }
    else if((tupleNode->m_tuple.m_kind == terinal
        || tupleNode->m_tuple.m_data.m_keyCode == terinal)
    && num == count)
    {
        //ShowTupleData(tupleNode);
        return tupleNode;
    }
    return tupleNode;
}


// ��pNode��β�Ĵʷ���Ԫ�鴮�У�������ҵ���һ��������terinal�Ĵʷ���Ԫ����
TupleNode* ReFindFirstTupleTreinal(TupleNode *pNode, TokenKind terinal)
{
    TupleNode *tupleNode = pNode;

    while(tupleNode != NULL)     // �������Ƶ�������IDENTIFIER
    {
        if(tupleNode->m_tuple.m_kind == terinal
       || tupleNode->m_tuple.m_data.m_keyCode == terinal)
        {
            break;
        }
        tupleNode = tupleNode->m_last;
    }

    if(tupleNode == NULL)
    {
        #ifdef PROP_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // PROP_DEBUG_DEFINE
        fprintf(stderr, "�ڴʷ���Ԫ�����Ҳ����ս��%d\n", terinal);
        return NULL;
    }
    else if(tupleNode->m_tuple.m_kind == terinal
       || tupleNode->m_tuple.m_data.m_keyCode == terinal)
    {
        return tupleNode;
    }

    return tupleNode;
}


// ����pNode��β�Ĵʷ���Ԫ��������, �ҵ���count��������terinal�Ĵʷ���Ԫ��
TupleNode* ReFindTupleTreinal(TupleNode *pNode, TokenKind terinal, int count)
{
    int         num = 0;
    TupleNode *tupleNode = pNode;

    while(tupleNode != NULL)     // find in the tuple nodes...
    {
        if(tupleNode->m_tuple.m_kind == terinal
       || tupleNode->m_tuple.m_data.m_keyCode == terinal)
        {
            num++;
            if(num == count)            // break this "WHILE", when you have find count "TERINALS"
            {
                break;
            }
        }
        tupleNode = tupleNode->m_last;
        //num++;
    }

    //
    if(tupleNode == NULL)
    {
        #ifdef PROP_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // PROP_DEBUG_DEFINE
        fprintf(stderr, "�ڴʷ���Ԫ�����Ҳ����ս��%d\n", terinal);
        return NULL;
    }
    else if((tupleNode->m_tuple.m_kind == terinal
        || tupleNode->m_tuple.m_data.m_keyCode == terinal)
    && num == count)
    {
        //ShowTupleData(tupleNode);
        return tupleNode;
    }

    return tupleNode;
}


// �жϵ�ǰ����ǲ���Ԥ����ָ��
bool IsProComTupleNode(TupleNode *tupleNode)
{
    ShowTupleData(tupleNode);
    return (tupleNode->m_tuple.m_kind == POUND_SEPARATOR             // Ԥ����ָ����'#'��ͷ
         && tupleNode->m_next->m_tuple.m_data.m_keyCode == PROCOM);  // '#'������Ԥ����ָ��
}


