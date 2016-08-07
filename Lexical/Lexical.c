/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : Lexical.c                                                      *
*   Description: CTools                                                         *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3NOT_FIND0 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/


#include "Lexical.h"    //  #include "..\Lexical\Lexical.h"



// ������TokenKind�е��ⲿ����
extern const char keyword[MAX_KEYWORD_COUNT][MAX_KEYWORD_SIZE];         // ���еĹؼ��ֱ���
extern const char procom[MAX_PROCOM_COUNT][MAX_PROCOM_SIZE];           // Ԥ����ָ���
extern const char operate[MAX_OPERATE_COUNT];             // �����������
extern const char allOperator[MAX_OPERATE_COUNT][MAX_OPERATE_SIZE];      // ���������
extern const char separator[MAX_SEPARAROR_COUNT];         // �ֽ������



#ifdef PUBLIC_and_PRIVATE
#
#
/// ������������
//// ���ص�ǰ�ؼ�����Ϣ���ֱ���
//PRIVATE int KeyCode(char *token);
#
#
/// ��token��¼���дʷ�����, ����Ϣ����douTupleԪ��, ������ΪdouBuffer, ���ű���symbolTable
PRIVATE TupleNode*              // ����ָ�����Ĵʷ���Ϣ��ָ��
Scanner(
        TupleNode *oldNode,             // ԭ���ʷ���Ϣ���ĩβ
        DouBuffer *douBuffer);           // ��������Ϣ
#define scanner Scanner
#
#
/// �Դ������ļ��еķֽ����Ϣ���д���
PRIVATE TupleNode*
LexSeparator(
             TupleNode *pNode,
             DouBuffer *douBuffer);
#
#
/// �Դ������ļ��е��������Ϣ���д���
PRIVATE TupleNode*
LexOperator(
            TupleNode *pNode,
            DouBuffer *douBuffer);
#define dis_pro_operator DisProOperator
#
#
PRIVATE TupleNode*
LexCharacter(
             TupleNode *pNode,         // �ʷ���Ϣ��β���
             DouBuffer *douBuffer);     // ˫��������Ϣ
#
#
/// ����������ĺ�����
PRIVATE TupleNode *
LexString(
          TupleNode *pNode,         // �ʷ���Ϣ��β���
          DouBuffer *douBuffer);     // ˫��������Ϣ
#
#
PRIVATE TupleNode*
LexIncludeFile(TupleNode *pNode,
               DouBuffer *douBuffer);
#
#
/// ��������Ϣ
PRIVATE TupleNode*
LexConstant(TupleNode *pNode,                   // ָ��ʷ���Ԫ���������һ���ʷ�����ָ��
            DouBuffer *douBuffer);               // ˫��������Ϣ
#
#
/// ����������ļ��е�Ԥ������Ϣ
PRIVATE Coord*                        // �����޸ĺ���﷨��Ϣ
LexLinePro(
          DouBuffer *douBuffer);    // ˫��������Ϣ
#
#
/// ����������ļ��е�Ԥ������Ϣ
PRIVATE TupleNode*                        // ���ز���Ĵʷ����
LexProCom(
          TupleNode *pNode,         // �ʷ���Ԫ����Ϣ
          DouBuffer *douBuffer);    // ˫��������Ϣ
#
#
/// ��������ַ�
PRIVATE bool        // ����ļ���������TRUE�� ���򷵻�FALSE
LexCntrl(
        DouBuffer *douBuffer);
#
#
// ����Ԥ����ָ����Ϣ
PRIVATE void
SkipProcom(
           DouBuffer *douBuffer);
#endif          // PUBLIC_and_PRIVATE



/// ������ڵ�Ԥ����ָ����Ϣ[#line  #program]
/**	������ڵ�Ԥ����ָ����Ϣ[#line]***********************************************************
***	Function	:	IsPoint
***	Param		:	douBuffer[DOUBUFFER*] ��������ļ���������Ϣ
***               ifp      [CTOOLSFILE] ָ��������ļ����ļ�ָ��
                  coord    [COORD*]     ��ʾ�ļ���Ϣ�ı�ʶ
***	Return		:	Coord*  ��#line��Ҫ���¶�λCoord����Ϣ�������޸ĺ��coord��ʶ
***	Description:	������ڵ�Ԥ����ָ����Ϣ[#line]
***	Calls		:   NULL
***	Called By	:	�ļ����������#��ͷ��Ԥ����ָ��, �����Ƚ���LexProCom�������д���, ����Ϣ��ʶ����
                  �����ȡ������Ԥ����ָ����#line, ����ô˺�����Դ�ļ��кű�ʶ�������¶�λ
***	Version		:	0.4.2����������¶���
***	Warning		:	��pragmaָ��Ĵ���δ���ж���
********************************************************************************************/
Coord* LexLinePro(DouBuffer *douBuffer)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
assert(*(douBuffer->m_forward) == '#');     // Ԥ����ָ����#��ʼ
#endif // LEICAL_DEBUG_DEFINR

    char *token = NULL;

    //DisBufSpace(douBuffer);     // ����Ԥ�������������Ը��������հ��ַ�
    /// ���ȶ�ȡ����Ҫ���к���Ϣ
    do
    {
        AddBufForward(douBuffer);             // �ҵ��кŵ���Ϣ
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
    }while(IsDigit(*(douBuffer->m_forward)) == true);       // �ҵ����һ���������ֵ��ַ�
    token = CopyBufToken(douBuffer);           // ���к������ֵķ�ʽȡ����

    // �������������кű�ʶ�հ�������Ϣ��ʶ��
    douBuffer->m_coord->m_fileLine = atoi(token) - 1;
    free(token);

    #ifdef  LEXICAL_DEBUG_DEFINE
    printf("��ȡ�������к���ϢLINE = %d\n", douBuffer->m_coord->m_fileLine);
    #endif  // LEXICAL_DEBUG_DEFINE

    /// �����ȡ��ָ��ָʾ�����ļ�
    do      // ָ������ַ�����"��ʼ
    {
        AddBufForward(douBuffer);      // ��������ǰָ������
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
    }while(*(douBuffer->m_forward-1) != '\"');
    CheckLexemeToForward(douBuffer);        // ��λ��ʼָ�뵽��ǰѭ���ҵ�λ��
    ////CheckBegOffsetToEndOffset(coord);

    do          // ��λ���ļ����ֵĽ���λ��Ҳ���ǡ���λ��
    {
        AddBufForward(douBuffer);
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
    }while(*(douBuffer->m_forward) != '\"');

    if((token = CopyBufToken(douBuffer)) != NULL)  // ȡ��ָʾ�����ļ���
    {
        douBuffer->m_coord->m_fileName = token;          // ���ļ��б�ʾ���ļ���ָ����ָ����ȡ�������ļ����ַ���

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("���Ĵʷ���Ϣ���ļ���Ϊ��%s\n", douBuffer->m_coord->m_fileName);
        printf("���Ĵʷ���Ϣ���ļ���Ϊ��%d\n", douBuffer->m_coord->m_fileLine);
        #endif      // LEXICAL_DEBUG_DEFINE
    }

    /// ������Ԥ��������ĺ���������Ϣ
    do
    {
        AddBufForward(douBuffer);
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
    }while(*(douBuffer->m_forward) != '\r' && *(douBuffer->m_forward) != '\n');

    CheckLexemeToForward(douBuffer);
    //CheckBegOffsetToEndOffset(coord);

    return douBuffer->m_coord;           // ���ص�ǰ���ļ��б�ʶ
}





TupleNode* LexProCom(TupleNode *pNode, DouBuffer *douBuffer)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
assert(*(douBuffer->m_forward) == '#');     // Ԥ����ָ����#��ʼ
#endif // LEICAL_DEBUG_DEFINR

    char *token = NULL;
    int  keyCode = NOT_FIND;
    // �����ҵ�#����ָ����ź����һ���ǿհ׷���
    //DisBufSpace(douBuffer);           // ����Ԥ����ָ�������Ը�������Ŀհ��ַ�
    #ifdef LEXICAL_DEBUG_DEFINE
    printf("��ǰ�ַ�%c, ƫ��%d %d\n", *(douBuffer->m_forward), douBuffer->m_coord->m_fileBegOffset, douBuffer->m_coord->m_fileEndOffset);
    #endif  // LEXICAL_DEBUG_DEFINE
    do
    {
        AddBufForward(douBuffer);      // �ҵ���ǰ�������Ϣ��ĩβ
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ǰ�ַ�%c, ƫ��%d %d\n", *(douBuffer->m_forward), douBuffer->m_coord->m_fileBegOffset, douBuffer->m_coord->m_fileEndOffset);
        #endif  // LEXICAL_DEBUG_DEFINE
    }while(IsLetterOrDigit(*(douBuffer->m_forward)) == true);

    if((token = CopyBufToken(douBuffer)) != NULL)     // ȡ���м���ַ���
    {
        if((keyCode = IsProCom(token)) != NOT_FIND)
        {
            if(strcmp(token, "line") == 0)
            {
                free(token);
                douBuffer->m_coord = LexLinePro(douBuffer);
            }
            else if (strcmp(token, "include") == 0)
            {
                free(token);
                //DisBufSpace(douBuffer);
                //LexIncludeFile(pNode, douBuffer, ifp, coord);
            }
            else
            {
            //    pNode = newNode;
                CheckLexemeToForward(douBuffer);
                //CheckBegOffsetToEndOffset(coord);
                free(token);
            }
        }
        else
        {
        #ifdef    CTOOLS_LEX_ERRO_DEFINE
        ///////////////////////////////////////////////////////////////////////////////////////////////
        /**/Error(coord, "the %s can't distinguish as Operator", token);// �޷���ʶ����������////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
        #endif // CTOOLS_LEX_ERRO_DEFINE
        }
    }


    DisBufProcom(douBuffer);
    CheckLexemeToForward(douBuffer);
    //CheckBegOffsetToEndOffset(coord);
    //DisBufSpace(douBuffer);

    #ifdef LEXICAL_DEBUG_DEFINE
    printf("Ԥ�����ǰ�ַ�%c\n", *(douBuffer->m_forward));
    printf("Ԥ�����ǰ�ַ�%c\n", *(douBuffer->m_forward));
    #endif // LEXICAL_DEBUG_DEFINE

    return pNode;
}





/// ��������ַ�
bool LexCntrl(DouBuffer *douBuffer)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // LEXICAL_DEBUG_DEFINE

    // ����ָ������ո񡢻��з����Ʊ������
    if(iscntrl(*(douBuffer->m_forward)) != 0
    && *(douBuffer->m_forward) != '\t'
    && *(douBuffer->m_forward) != '\n')
    {
        //printf("��ǰΪ�ո�-����-�����Ʊ��, ���߲��ɴ�ӡ\n");
        #ifdef LEXICAL_DEBUG_DEFINE
        printf("ƫ��%d\n", douBuffer->m_coord->m_fileBegOffset);
        #endif // LEXICAL_DEBUG_DEFINE

        DisBufControl(douBuffer);
        //while(iscntrl(*(douBuffer->m_forward)) != 0); // �����ָ������ո񡢻��з����Ʊ������

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ǰ���ַ���%c = %d", *(douBuffer->m_forward), *(douBuffer->m_forward));
        #endif

        CheckLexemeToForward(douBuffer);
        //CheckBegOffsetToEndOffset(coord);
        ///-////////////////////////////////////////////////////////////////////////////
        ///-AddBufForward(douBuffer->m_forward, ifp);  �����м�����������ǳ���ֵ�����
        ///-////////////////////////////////////////////////////////////////////////////
    }

    if(*(douBuffer->m_forward) == (char)CToolsIsEOF)
    {
        if(feof(douBuffer->m_fp) == 0)         // ��������ļ�����
        {
            PutBuffer(douBuffer);       // ������һ��������д����Ϣ
            return false;
        }
        else        // ����˵�����ļ�����, ��ֹ�ʷ�����
        {
            #ifdef LEXICAL_HELPS_DEFINE         // ���ð����� -=> ��ʾ�ļ��Ѿ�����
            FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
            printf("\t\t**********************************************\n");
            printf("\t\t******The File is End...................******\n");
            printf("\t\t**********************************************\n");
            PAUSE( );
            #endif      // LEXICAL_HELPS_DEFINE

            return true;
        }
    }

    return false;
}

/*
��C�У��ַ���������û��ʲô���ʵ�����
char���Կ�����1���ֽڵ�������
short���Կ���2���ֽڵĿ��ַ���
int���Կ���4���ֽڵĿ��ַ���
���ԣ�'a'��ʾһ���ַ�'a'��'ab'���ʾһ��2���ֽڵ��������߿��ַ���
'abcd'���ʾһ��4���ֽڵ���������ַ�������ֻ֧��1�ֽڡ�2�ֽڡ�4�ֽڡ�
char c='a'; //��Ȼû����
char c='ab'; //�൱������ char c=0x6162����Ϊ'a'�ַ���ʾ0x61��'b'�ַ���ʾ0x62������Ϊ'ab'��2���ֽڣ����Ը���charʱ��������ضϵľ��档
char c='abc'; //�൱������char c=0x00616263��Ҳ������档
char c='abcd'; //�൱������char c=0x61626364��Ҳ������档
char c='abcde'; //������������ֽڳ���4����������
*/
TupleNode* LexCharacter(TupleNode *pNode, DouBuffer *douBuffer)              // �ʷ���Ŀ
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
assert(*(douBuffer->m_forward) == '\'');         // ��ǰ�ַ��������ǵ�����
#endif  // LEXICAL_DEBUG_DEFINE

    char *token = NULL;                     // ���ڴ洢����Ϣ
    TupleNode *newNode = NULL;              // ���ڴ洢�ַ�����Ϣ

    /// ����ǰָ��ָ��'��ĩβ
    do          /// ѭ���������е��ַ�����Ϣ
    {
        if(*(douBuffer->m_forward) == '\n' || *(douBuffer->m_forward) == '\r' || *(douBuffer->m_forward) == EOF)       // �����˻���ȴ��Ȼû���ҵ�"
        {   // ˵��Դ�ļ��д���
            /// stdERR��������һ������, ���Դ����ֻ��һ�������ſ��ܻ���ִ���
            ///Error(crood, "");
            break;
        }

        AddBufForward(douBuffer);             // ѭ�������������""֮���ַ���Ϣ
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1

    }while(*(douBuffer->m_forward) != '\'');    // �����ַ�ͣ���ں����"λ��

    if(*(douBuffer->m_forward) == '\'')
    {
        AddBufForward(douBuffer);
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1

        /// ���ַ����������ӽ���ʷ���Ԫ��
        if((token = CopyBufToken(douBuffer)) != NULL)      // ��ȡ����֮����ַ������
        {
            #ifdef CTOOLS_LEX_WARN_DEFINE
            if(strlen(token) > INT_SIZE)           // ���ȴ������������γ��Ƚ���ʾ����ضϾ���
            {
                Warning(coord, "overflow in implicit constant conversion\n");
            }
            if(strlen(token) > 1)           // �ַ��ĳ��ȴ���1�����ַ��������ȹ����ľ���
            {
                Warning(coord, "character constant too long for its type\n");
            }
            #endif

            // ��Ҫ����Ϣ�����Ԫ����[��Ϊ:�ַ��������]
            if((newNode = InsertTupleLiteral(pNode, token, douBuffer->m_coord, CHAR_CONST)) != NULL)
            {
                pNode = newNode;

                #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
                printf("\n�ַ�\n");

                SHOW_FILE_NAME(pNode->m_tuple.m_coord.m_fileName);
                printf("Line = %d  ", pNode->m_tuple.m_coord.m_fileLine);
                printf("Begi = %d ", pNode->m_tuple.m_coord.m_fileBegOffset);
                printf("Endl = %d ", pNode->m_tuple.m_coord.m_fileEndOffset);
                printf("[%d, %s]\n", CONST, token);
                #endif      // LEXICAL_SHOWS_DEFINE
            }
            else
            {   /// ��������ߵ����˵�����������
                printf("���ַ��������%s����ʷ���Ԫ���ʱ�����\n", token);
            }
        }
        else
        {
            /// ��������ߵ����˵�����������
            printf("���ֽ��%c����ʷ���Ԫ���ʱ�����\n", *(douBuffer->m_forward));
        }
    }
    else                    // δ�ҵ��ַ�'���Ľ�β
    {
    #ifdef CTOOLS_LEX_ERRO_DEFINE
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /**/Error(coord, "missing terminating \' Character...");//�ַ����������δƥ��////////////////////////
    /**/douBuffer->m_forward = douBuffer->m_lexeme;///////////���˵���ʼ�ַ��������ʼ��λ��////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    #endif // CTOOLS_LEX_DRR_DEFINE
    }

    //CheckLexemeToForward(douBuffer);
    ////CheckBegOffsetToEndOffset(coord);
    douBuffer->m_forward--;
    douBuffer->m_coord->m_fileEndOffset--;
    //SubBufForward(douBuffer);
    return pNode;               // ���شʷ���Ԫ��ĵ�ַ
}


/// ����������ĺ�����
TupleNode * LexString(TupleNode *pNode, DouBuffer *douBuffer)          // �ļ�ָ����Ϣ
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
assert(*(douBuffer->m_forward) == '\"');
#endif // DEBUG_DEFINE

    char *token = NULL;                   // ���ڴ洢����Ϣ
    TupleNode *newNode = NULL;              // ���ڴ洢�ַ�����Ϣ

    do          /// ѭ���������е��ַ�����Ϣ
    {
        if(*(douBuffer->m_forward) == '\n' || *(douBuffer->m_forward) == '\r' || *(douBuffer->m_forward) == (char)EOF)     // �����˻���ȴ��Ȼû���ҵ�"
        {   // ˵��Դ�ļ��д���
            /// stdERR��������һ������, ���Դ����ֻ��һ�������ſ��ܻ���ִ���
            ///Error(crood, "");
            break;
        }

        AddBufForward(douBuffer);             // ѭ�������������""֮���ַ���Ϣ
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1

    }while(*(douBuffer->m_forward) != '\"' || *(douBuffer->m_forward - 1) == '\\');    // �����ַ�ͣ���ں����"λ��


    if(*(douBuffer->m_forward) == '\"')      // ֻ�е�ǰ�ַ���", ȡ�������ַ��������ַ��������
    {
        AddBufForward(douBuffer);
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
        /// ���ַ����������ӽ���ʷ���Ԫ��
        if((token = CopyBufToken(douBuffer)) != NULL)      // ��ȡ""֮����ַ��������
        {   // ��Ҫ����Ϣ�����Ԫ����[��Ϊ:�ַ��������]
            if((newNode = InsertTupleLiteral(pNode, token, douBuffer->m_coord, STRING_CONST)) != NULL)
            {
                pNode = newNode;

                #ifdef LEXICAL_SHOWS_DEFINE      // ���ð����� -=> ��ʾ���ִʷ���Ϣ������
                printf("\n�ַ���\n");

                SHOW_FILE_NAME(pNode->m_tuple.m_coord.m_fileName);
                printf("Line = %d  ", pNode->m_tuple.m_coord.m_fileLine);
                printf("Begi = %d ", pNode->m_tuple.m_coord.m_fileBegOffset);
                printf("Endl = %d ", pNode->m_tuple.m_coord.m_fileEndOffset);
                printf("[%d, %s]\n", CONST, token);
                #endif      // LEXICAL_SHOWS_DEFINE
            }
            else
            {   /// ��������ߵ����˵�����������
                printf("���ַ��������%s����ʷ���Ԫ���ʱ�����\n", token);
            }
        }
        else
        {
            /// ��������ߵ����˵�����������
            printf("���ֽ��%c����ʷ���Ԫ���ʱ�����\n", *(douBuffer->m_forward));
        }
    }
    else                    // δ�ҵ��ַ�'���Ľ�β
    {
    #ifdef CTOOLS_LEX_ERRO_DEFINE
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /**/Error(douBuffer->m_coord, "missing terminating \" String...");//�ַ��������""δ���/////////////////////////
    /**/douBuffer->m_forward = douBuffer->m_lexeme;////////���˵���ʼ�ַ��������ʼ��λ��///////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    #endif //CTOOLS_LEX_DRR_DEFINE
    }

    //CheckLexemeToForward(douBuffer);
    ////CheckBegOffsetToEndOffset(coord);

    douBuffer->m_forward--;
    douBuffer->m_coord->m_fileEndOffset--;

    return pNode;               // ���شʷ���Ԫ��ĵ�ַ
}



/**	LexIncludeFile***************************************************************************
*   \brief  the function can display the file name in "include<filename>"
*   \param  pNode       the node point to the tuple of the lexical
*   \param  doubuffer   the buffer which you read file in
*   \param  ifp         the file pointer point to the file you want to compiler
*   \param  coord       the global coord of the current char you display
*   \return return the node which point to the tuple if you find
********************************************************************************************/
TupleNode* LexIncludeFile(TupleNode *pNode, DouBuffer *douBuffer)              // �ʷ���Ŀ
{
    #ifdef LEXICAL_DEBUG_DEFINE
    assert(*(douBuffer->m_forward) == '<');         // ��ǰ�ַ��������ǵ�����
    #endif  // LEXICAL_DEBUG_DEFINE

    int keyCode = IsAllOperate("<");        // ����'�ı�����Ϣ
    char *token = NULL;                     // ���ڴ洢����Ϣ
    TupleNode *newNode = NULL;              // ���ڴ洢�ַ�����Ϣ

    /// ��Ҫ����Ϣ�����Ԫ����[��Ϊ:�ֽ��], �����ض�Ϊ'
    if((newNode = InsertTupleKey(pNode, OPERATE, keyCode, douBuffer->m_coord)) != NULL)
    {
        pNode = newNode;

        AddBufForward(douBuffer);
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1

        CheckLexemeToForward(douBuffer);
        //CheckBegOffsetToEndOffset(coord);
        ///*count += 1;

        #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
        printf("\n�����\n");

        SHOW_FILE_NAME(pNode->m_tuple.m_coord.m_fileName);
        printf("Line = %d  ", pNode->m_tuple.m_coord.m_fileLine);
        printf("Begi = %d ", pNode->m_tuple.m_coord.m_fileBegOffset);
        printf("Endl = %d ", pNode->m_tuple.m_coord.m_fileEndOffset);
        printf("[%d, %s]\n", OPERATE, allOperator[keyCode]);        // ��"�������
        #endif         // LEXICAL_SHOWS_DEFINE
    }
    else
    {
        /// ��������ߵ����˵�����������
        printf("���ֽ��%c����ʷ���Ԫ���ʱ�����\n", *(douBuffer->m_forward));
    }

    /// ����ǰָ��ָ��'��ĩβ
    do          /// ѭ���������е��ַ�����Ϣ
    {
        if(*(douBuffer->m_forward) == '\n' || *(douBuffer->m_forward) == '\r' || *(douBuffer->m_forward) == EOF)       // �����˻���ȴ��Ȼû���ҵ�"
        {   // ˵��Դ�ļ��д���
            /// stdERR��������һ������, ���Դ����ֻ��һ�������ſ��ܻ���ִ���
            ///Error(crood, "");
            break;
        }
        AddBufForward(douBuffer);             // ѭ�������������""֮���ַ���Ϣ
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1

    }while(*(douBuffer->m_forward) != '>');    // �����ַ�ͣ���ں����"λ��

    if(*(douBuffer->m_forward) == '>')      // ֻ�е�ǰ�ַ��ǡ�, ȡ�������ַ��������ַ������
    {
        /// ���ַ����������ӽ���ʷ���Ԫ��
        if((token = CopyBufToken(douBuffer)) != NULL)      // ��ȡ����֮����ַ������
        {
            #ifdef CTOOLS_LEX_WARN_DEFINE
            if(strlen(token) > INT_SIZE)           // ���ȴ������������γ��Ƚ���ʾ����ضϾ���
            {
                Warning(coord, "overflow in implicit constant conversion\n");
            }
            if(strlen(token) > 1)           // �ַ��ĳ��ȴ���1�����ַ��������ȹ����ľ���
            {
                Warning(coord, "character constant too long for its type\n");
            }
            #endif

            // ��Ҫ����Ϣ�����Ԫ����[��Ϊ:�ַ��������]
            if((newNode = InsertTupleLiteral(pNode, token, douBuffer->m_coord, STRING_CONST)) != NULL)
            {
                pNode = newNode;
                ///*count += 1;

                #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
                printf("\n�ַ���\n");


                SHOW_FILE_NAME(pNode->m_tuple.m_coord.m_fileName);
                printf("Line = %d  ", pNode->m_tuple.m_coord.m_fileLine);
                printf("Begi = %d ", pNode->m_tuple.m_coord.m_fileBegOffset);
                printf("Endl = %d ", pNode->m_tuple.m_coord.m_fileEndOffset);
                printf("[%d, %s]\n", CONST, token);
                #endif      // LEXICAL_SHOWS_DEFINE
            }
            else
            {   /// ��������ߵ����˵�����������
                printf("���ַ��������%s����ʷ���Ԫ���ʱ�����\n", token);
            }
        }

        // ��Ҫ����Ϣ�����Ԫ����[��Ϊ:�ֽ��], �����ض�Ϊ"
        keyCode = IsAllOperate(">");        // ����'�ı�����Ϣ
        if((newNode = InsertTupleKey(pNode, OPERATE, keyCode, douBuffer->m_coord)) != NULL)
        {
            pNode = newNode;
            CheckLexemeToForward(douBuffer);

            AddBufLexeme(douBuffer);
            ///*count += 1;

            #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
            printf("\n�ֽ��\n");
            ShowTupleNode(pNode);
            #endif      // LEXICAL_SHOWS_DEFINE
        }
        else
        {
            /// ��������ߵ����˵�����������
            printf("���ֽ��%c����ʷ���Ԫ���ʱ�����\n", *(douBuffer->m_forward));
        }
    }
    else                    // δ�ҵ��ַ�'���Ľ�β
    {
    #ifdef CTOOLS_LEX_ERRO_DEFINE
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /**/Error(coord, "missing terminating \' Character...");//�ַ����������δƥ��////////////////////////
    /**/douBuffer->m_forward = douBuffer->m_lexeme;///////////���˵���ʼ�ַ��������ʼ��λ��////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    #endif // CTOOLS_LEX_DRR_DEFINE
    }


    return pNode;               // ���شʷ���Ԫ��ĵ�ַ
}


/// ��token��¼���дʷ�����, ����Ϣ����douTupleԪ��β��pNode, ������ΪdouBuffer, ���ű���symbolTable
TupleNode* Scanner(TupleNode *pNode, DouBuffer *douBuffer)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // LEXICAL_DEBUG_DEFINE
    char *token = NULL;
    int keyCode = NOT_FIND;

    // �����ǰλ�õ���Ϣ����Ϸ��ı�������Ҫ��, ˵����ǰ��ʶ�����߹ؼ��ֻ�û�н���
    if(IsLetterOrDigit(*(douBuffer->m_forward)) == true)
    {
        #ifdef LEXICAL_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // LEXICAL_DEBUG_DEFINE

        printf("��ǰ�ַ���Ȼ������Ϊһ������Ҫ��ı�ʶ��, �������г�ǰ����\n");
        return NULL;            // ��ǰ��ʶ����Ȼû�н���, Ӧ����ǰ����
    }

    if((token = CopyBufToken(douBuffer)) == NULL)      // ���Ƚ��������еĴ�ȡ����
    {
        #ifdef LEXICAL_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        #endif // LEXICAL_DEBUG_DEFINE

        return NULL;
    }

    #ifdef LEXICAL_DEBUG_DEFINE
    FILE_FUNC_LINE( );
    printf("��ǰȡ�����Ĵ���Ϣ��%s\n", token);
    ShowCoord(douBuffer->m_coord);
    printf("\n");
    #ifdef CTOOLS_STEPS_DEFINE
    PAUSE( );
    #endif      //  CTOOLS_STEPS_DEFINE
    #endif // LEXICAL_DEBUG_DEFINE
    TupleNode *newNode = NULL;     // �½���Ԫ����

    if((keyCode = IsKeyword(token)) != NOT_FIND)   /// �ǹؼ���
    {
        // ������Ԫ�����Ϣ
        if((newNode = InsertTupleKey(pNode, KEYWORD, keyCode, douBuffer->m_coord)) != NULL) // ��token�������ؼ��ֲ���Tuple
        {
            pNode = newNode;

            // �����ǰ����Ϣ
            #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
            printf("\n�ؼ���\n");
            ShowTupleNode(pNode);
            #endif      // LEXICAL_SHOWS_DEFINE
        }
        else        /// ��������ߵ�����˵�����������
        {
            printf("ERROR:���򽫹ؼ���%s���뵽�ʷ����ʱ�����\n", token);
            PAUSE( );
        }
    }
//    else if((keyCode = IsProCom(token)) != NOT_FIND)   /// �ǹؼ���
//    {
//        // ������Ԫ�����Ϣ
//        if((newNode = InsertTupleKey(pNode, PROCOM, keyCode, douBuffer->m_coord)) != NULL) // ��token�������ؼ��ֲ���Tuple
//        {
//            pNode = newNode;
//
//            // �����ǰ����Ϣ
//            #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
//            printf("\nԤ����\n");
//            ShowTupleNode(pNode);
//            #endif      // LEXICAL_SHOWS_DEFINE
//        }
//        else        /// ��������ߵ�����˵�����������
//        {
//            printf("ERROR:���򽫹ؼ���%s���뵽�ʷ����ʱ�����\n", token);
//            PAUSE( );
//        }
//    }
    else            /// token�ȷǹؼ��֣��ַǳ��������ж�Ϊ��ʶ�������token���ÿ�
    {
        // ������Ԫ�����Ϣ
        if((newNode = InsertTupleId(pNode, token, douBuffer->m_coord)) != NULL) // ��token��������ʶ������Tuple��sysmbolTable
        {
            pNode = newNode;

            #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
            printf("\n��ʶ��\n");
            ShowTupleNode(pNode);
            #endif      // LEXICAL_SHOWS_DEFINE
        }
        else
        {
            printf("ERROR:���򽫱�ʶ��%s���뵽���ű��ʱ�����\n", token);
            PAUSE( );
            /// ��������ߵ�����˵�����������
        }
    }

    CheckLexemeToForward(douBuffer);

    return pNode;           // ���ص�ǰ��Ԫ��ĵ�ĩβ���
}



/// ����ֽ���ĺ�����
/**	����������ļ��еķֽ�����ŵ���Ϣ*****************************************************
***	Function	:	IsPoint
***	Param		:	pNode    [TUPLENODE*] �ʷ���Ԫ������βָ��
***               douBuffer[DOUBUFFER*] ��������ļ���������Ϣ
***               ifp      [CTOOLSFILE] ָ��������ļ����ļ�ָ��
***               coord    [COORD*]     ��ʾ�ļ���Ϣ�ı�ʶ
***	Return		:	Coord*  ��#line��Ҫ���¶�λCoord����Ϣ�������޸ĺ��coord��ʶ
***	Description:	Ԥ�����ļ��в�������ע����Ϣ, ���ע����Ϣ�������ж�
***	Calls		:   NULL
***	Called By	:	����ԭ�ļ�ʱ�� ��������ֽ��, �Ƚ��ֽ������ڴʷ���Ԫ��������
                  �ڵ��ô˺������к�����Ϣ��ʶ���Ĵ��� ��ΪԴ�ļ��зֽ��������ܳ��ֱ�ʶ������Ϣ
***	Version	:	0.4.2
***	Warning	:	Դ�ļ��д���#Ԥ����ָ��, ��Ԥ�����ļ��в�����
***************************************************************************************/
TupleNode* LexSeparator(TupleNode *pNode, DouBuffer *douBuffer)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // LEXICAL_DEBUG_DEFINE
    int         keyCode = NOT_FIND;
    TupleNode   *newNode = NULL;

    //if(*(douBuffer->m_forward) == ' ' || *(douBuffer->m_forward) == '\t')          // �����ǰ�ַ��ǿո�
    if(IsSpace(*douBuffer->m_forward) == true)
    {
        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ǰΪSPACE�ַ�\n");
        #endif      // LEXICAL_DEBUG_DEFINE
        //printf("=======%d", *(douBuffer->m_forward));
        /// �����һ���ַ����ǿո񡢻��С��Ʊ�������߲��ɴ�ӡ�ַ�
        DisBufSpace(douBuffer);

        CheckLexemeToForward(douBuffer);

        douBuffer->m_forward--;
        douBuffer->m_coord->m_fileEndOffset--;
    }
    else if(*(douBuffer->m_forward) == '\"')                   // ��ǰ�ַ���˫����, �����������һ���ַ�������
    {
        if((newNode = LexString(pNode, douBuffer)) != NULL)       // �����м��ַ���
        {
            pNode = newNode;
            CheckLexemeToForward(douBuffer);

            AddBufLexeme(douBuffer);           // �ڲ����˷���֮��, ����ʼָ���ƶ�����һλ
        }
    }
    else if(*(douBuffer->m_forward) == '\'')         // ��ǰ�ַ��ǵ�����', ���ܳ�����һ���ַ�����
    {
        if((newNode = LexCharacter(pNode, douBuffer)) != NULL);
        {
            pNode = newNode;
            CheckLexemeToForward(douBuffer);
            //CheckBegOffsetToEndOffset(coord);
//            douBuffer->m_lexeme++;          // �ڲ����˷���֮��, ����ʼָ���ƶ�����һλ
//            coord->m_fileBegOffset++;
            AddBufLexeme(douBuffer);                // �ڲ����˷���֮��, ����ʼָ���ƶ�����һλ
        }
    }
    else if(*(douBuffer->m_forward) == '#')
    {
        LexProCom(pNode, douBuffer);
        CheckLexemeToForward(douBuffer);

        AddBufLexeme(douBuffer);                // �ڲ����˷���֮��, ����ʼָ���ƶ�����һλ

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ǰ�ַ�%c, ƫ��%d %d\n", *(douBuffer->m_forward), douBuffer->m_coord->m_fileBegOffset, douBuffer->m_coord->m_fileEndOffset);
        #endif  // LEXICAL_DEBUG_DEFINE
    }
    else if((keyCode = IsSeparator(*(douBuffer->m_forward))) != NOT_FIND)  // ��ǰ�ַ��Ƿֽ��
    {
        // ��Ҫ����Ϣ�����Ԫ����[��Ϊ:�ֽ��]
        if((newNode = InsertTupleKey(pNode, SEPARATOR, keyCode, douBuffer->m_coord)) != NULL)
        {
            pNode = newNode;
            CheckLexemeToForward(douBuffer);

            AddBufLexeme(douBuffer);                // �ڲ����˷���֮��, ����ʼָ���ƶ�����һλ

            #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
            printf("\n�ֽ��\n");
            ShowTupleNode(pNode);
            #endif      // LEXICAL_SHOWS_DEFINE


        }
        else
        {
            /// ��������ߵ����˵�����������
            printf("���ֽ��%c����ʷ���Ԫ���ʱ�����\n", *(douBuffer->m_forward));
        }
    }

    return pNode;
}




/// ����������ŵĺ�����
/**	����Ԥ�����ļ��е��������***********************************************************
***	Function	:	IsPoint
***	Param		:	pNode    [TUPLENODE*] �ʷ���Ԫ������βָ��
***               douBuffer[DOUBUFFER*] ��������ļ���������Ϣ
***               ifp      [CTOOLSFILE] ָ��������ļ����ļ�ָ��
***               coord    [COORD*]     ��ʾ�ļ���Ϣ�ı�ʶ
***	Return		:	Coord*  ��#line��Ҫ���¶�λCoord����Ϣ�������޸ĺ��coord��ʶ
***	Description:	Ԥ�����ļ��в�������ע����Ϣ, ���ע����Ϣ�������ж�
***	Calls		:   NULL
***	Called By	:	����ԭ�ļ�ʱ�� ��������������, �Ƚ����������ڴʷ���Ԫ��������
                  �ڵ��ô˺������к�����Ϣ��ʶ���Ĵ��� ��ΪԴ�ļ��������������ܳ��ֱ�ʶ������Ϣ
***	Version		:	0.4.2�˺����η���, Դ�ļ���Ԥ�����ļ�����ͬ���Ĵ���ʽ
***	Warning		:	Դ�ļ��д���ע����Ϣ, ��Ԥ�����ļ����Ѿ���Ԥ����׶ν�ע����Ϣ�޳�
***************************************************************************************/
TupleNode* LexOperator(TupleNode *pNode, DouBuffer *douBuffer)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // LEXICAL_DEBUG_DEFINE
    char        *token = NULL;
    int         keyCode = NOT_FIND;
    TupleNode   *newNode = NULL;


    // ��ע����Ϣ�����ų�
    if(*(douBuffer->m_forward) == '/' && *(douBuffer->m_forward + 1) == '/') // �ж��Ƿ�Ϊ����ע��//
    {   // �ų�//��ע��

        DisBufCurrLine(douBuffer);
        CheckLexemeToForward(douBuffer);

        AddBufLexeme(douBuffer);                // �ڲ����˷���֮��, ����ʼָ���ƶ�����һλ

    }
    else if(*(douBuffer->m_forward) == '/' && *(douBuffer->m_forward + sizeof(char)) == '*')  // �ж��Ƿ�Ϊ����ע��//
    {   // �ų�/**/��ע��
        DisBufCommentLine(douBuffer);
        CheckLexemeToForward(douBuffer);

        AddBufLexeme(douBuffer);
    }
    else if(IsOperate(*(douBuffer->m_forward) != NOT_FIND))            // �����������
    {
        char *oldLexeme = douBuffer->m_lexeme;
        char *oldForward = douBuffer->m_forward;

        // ���������������ܳ��ֵ������+��˫�����++�� �������>>=
        do
        {
            AddBufForward(douBuffer);
            //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
        }while(IsOperate(*(douBuffer->m_forward)) != NOT_FIND);     // ֻҪ������Ȼ���������++

        if((token = CopyBufToken(douBuffer)) != NULL)            // �ҳ��ַ���
        {
            if((keyCode = IsAllOperate(token)) != NOT_FIND)
            {
                /// ����������������������Ԫ����
                if((newNode = InsertTupleKey(pNode, OPERATE, keyCode, douBuffer->m_coord)) != NULL)
                {
                    pNode = newNode;

                    #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
                    printf("\n�����\n");
                    ShowTupleNode(pNode);
                    #endif      // LEXICAL_SHOWS_DEFINE
                }
            }
            else
            {
                printf("�޷���ʶ����������\n", token);
                free(token);
                #ifdef    CTOOLS_LEX_ERRO_DEFINE
                ///////////////////////////////////////////////////////////////////////////////////////////////
                /**/Error(coord, "the %s can't distinguish as Operator", token);// �޷���ʶ����������////////
                ///////////////////////////////////////////////////////////////////////////////////////////////
                #endif // CTOOLS_LEX_ERRO_DEFINE
            }
        }

        CheckLexemeToForward(douBuffer);

        douBuffer->m_forward--;      // �������ǰ����һλ
        douBuffer->m_coord->m_fileEndOffset--;
    }
    return pNode;
}





/// �Գ�����Ϣ���д���
TupleNode* LexConstant(TupleNode *pNode, DouBuffer *douBuffer)
{
    #ifdef LEXICAL_DEBUG_DEFINE
    assert(IsDigit(*douBuffer->m_forward) == true);
    #endif // LEICAL_DEBUG

    char        *token = NULL;
    TokenKind    kind = TOKEN_NULL;
    TupleNode   *newNode = NULL;

    CheckLexemeToForward(douBuffer);            // �����ƶ����ַ�����ͷ
    //CheckBegOffsetToEndOffset(coord);

    do              // Ѱ�ҵ�����
    {
        #ifdef LEXICAL_DEBUG_DEFINE
        printf("%c", *(douBuffer->m_forward));
        #endif // LEXICAL_DEBUG_DEFINE

        AddBufForward(douBuffer);             // �ƶ��ַ���
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
    }while(IsHexDigit(*(douBuffer->m_forward)) == true
        || *(douBuffer->m_forward) == '.'
        || *(douBuffer->m_forward) == 'x' || *(douBuffer->m_forward) == 'X');

    #ifdef LEXICAL_DEBUG_DEFINE
    printf("�ƶ���������ĩβ%c", *(douBuffer->m_forward));
    #endif // LEICAL_DEBUG

    if((token = CopyBufToken(douBuffer)) != NULL)          // ȡ��������Ϣ
    {   //FILE_FUNC_LINE( );
        if((kind = IsConstant(token)) != TOKEN_NULL)                   // ���ȡ�����ĳ�����Ϣ��һ���Ϸ��ĳ�����Ϣ
        {//FILE_FUNC_LINE( );
            if((newNode = InsertTupleLiteral(pNode, token, douBuffer->m_coord, kind)) != NULL)        // ����������Ϣ��ӽ�ȥ
            {//FILE_FUNC_LINE( );
                pNode = newNode;


                #ifdef LEXICAL_SHOWS_DEFINE               //  ������ʾ�� -=> ������ֵĴʷ���Ϣ
                printf("\n������\n");
                ShowTupleNode(pNode);
                #endif      // LEXICAL_SHOWS_DEFINE
            }
        }
        else
        {
            free(token);           // ������ǳ�������, �ͽ�ָ������
        }
        // ��ָ�����ú�,�Թ��´ο�ʼ�����µĴʷ���Ϣ
        CheckLexemeToForward(douBuffer);

        douBuffer->m_forward--;
        douBuffer->m_coord->m_fileEndOffset--;
    }

    return pNode;               // ���شʷ���Ԫ�������β����
}


BinaryTuple BufferLexical(const char *sourFile)
{
    int         count = 0;              // �˷���������

    /// ˫��������Ϣ
    DouBuffer   *douBuffer = InitBuffer(sourFile);


    /// ������Ϣ�Ĵ�����
    CompResult  *compResult = InitCompResult( );     // ������-=> ����������Ŀ, ������Ŀ, ��ֹλ��

    /// �ʷ���Ԫ�����Ϣ
    BinaryTuple douTuple = InitTuple(sourFile);            // ��ʼ����Ԫ����
    TupleNode   *pNode = (TupleNode *)douTuple, *newNode = NULL; // ���ָ��




    /// �����ʷ���������
    for(PutBuffer(douBuffer); /*feof(ifp) == 0*/; AddBufForward(douBuffer))     // ѭ���������������ַ�, ֻҪû�е��ﻺ����ĩβ
    {
        if(LexCntrl(douBuffer) == true)       // ��������ַ���Ϣ
        {
            break;
        }
        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ǰ�����ַ�%c=%d, ƫ��%d %d\n", *(douBuffer->m_forward), *(douBuffer->m_forward), douBuffer->m_coord->m_fileBegOffset, douBuffer->m_coord->m_fileEndOffset);
        #ifdef CTOOLS_STEPS_DEFINE
        PAUSE( );
        #endif      // CTOOLS_STEPS_DEFINE
        #endif

        if(IsSeparator(*(douBuffer->m_forward)) != NOT_FIND)	/// ==========�ֽ���ŵĴ������==========
        {
            if((newNode = Scanner(pNode, douBuffer)) != NULL)       /// �ȶԶԶ�ȡ����Ϣ���дδʷ�ɨ��
            {
                pNode = newNode;        // ��pNodeָ���µ�����β��
                count++;
            }

            if((newNode = LexSeparator(pNode, douBuffer)) != NULL)    /// �ٶԷ��ֵĵ�ǰ�ֽ���Ž��дʷ�����
            {
                pNode = newNode;
                count++;
            }
        }
        else if(IsOperate(*(douBuffer->m_forward)) != NOT_FIND)  /// ==========������Ĵ������==========
        {
            if((newNode = Scanner(pNode, douBuffer)) != NULL)       /// �ȶԶԶ�ȡ����Ϣ���дδʷ�ɨ��
            {
                pNode = newNode;        // ��pNodeָ���µ�ĩβ
                count++;
            }

            if((newNode = LexOperator(pNode, douBuffer)) != NULL)          /// �ٶԷ��ֵĵ�ǰ������Ž��дʷ�����
            {
                pNode = newNode;
                count++;       // �ļ��ؼ���ʶ++
            }
        }
        else if(IsDigit(*douBuffer->m_forward) == true && IsLetter(*(douBuffer->m_forward - sizeof(char))) != true)     /// ==========���ֵĵ�������[�������������ֳ���]==========
        {
            if((newNode = LexConstant(pNode, douBuffer)) != NULL)
            {
                pNode = newNode;
                count++;
            }
        }
        else if(isprint(*(douBuffer->m_forward)) == 0)     /// ����������޷�ʶ��ı������
        {
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /**/Error(douBuffer->m_coord, "the %d can't distinguish as C Language infomation", *(douBuffer->m_forward));////////////////
        /**/compResult->m_erroCount++;/////////////////////////////////////////////////////////////////////������Ŀ����1
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }


    }     // end of FOR(IsBufferEnd(douBuffer) != true)

    /// ������Ԫ��
    #ifdef LEXICAL_HELPS_DEFINE         // C���ð����� -=> ��ʾ�ʷ��������, ��ʾ���ֵĴʷ���Ϣ��Ŀ
    FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
    printf("\n\t******************************************************************\n");
    printf("\t****      We have find %d Lexeical in the file you give...  ****\n", count);
    printf("\t******************************************************************\n");
    PAUSE( );
    #endif  // LEXICAL_HELPS_DEFINE

    if((newNode = InsertEndToken(pNode)) != NULL)
    {
        pNode = newNode;
    }


    FinitBuffer(douBuffer);     // ��������β��Ϣ
    /////////////////////////////////////////////////////
    //FinitBuffer(coord);         // �ļ�λ��ָ�����β������
    /////////////////////////////////////////////////////
    douTuple->m_tuple.m_coord.m_fileLine = count;  // tͷ����λ�ñ�ʶ��Ϣ���к������ڱ�ʶ�ʷ���Ŀ

    //CToolsClose(ifp);

    if(compResult->m_erroCount != 0)
    {
        //printf("��ΪԴ�����г��ִ���, �ڴʷ�������ֱ�ӽ��ļ��ر�\n");
        DestroyTuple(douTuple);
        douTuple = NULL;
    }
    return douTuple;
}



// ��Դ�ļ����дʷ�����
// ���Դ�ļ���.c����.hΪ��׺��, ��Ĭ�ϵ���Դ�ļ����дʷ�����
// ����ļ���.iΪ��׺,����Ĭ�ϵ���Ԥ�����ļ����б���
void MainOfLexical( )   // ������Դ�ļ�
{
    #ifdef SYS_WINDOWS_DEF
    system("title �ʷ�������");
    system("color 00");
    #endif      // SYS_WINDOWS_DEF

    char sourFile[FILE_NAME_SIZE];        // Դ�ļ���
    BinaryTuple douTuple = NULL;               // ��Ԫ����Ϣ


    while(printf("Please enter your sourFile's-url:"), scanf("%s", sourFile) != EOF)
    {

        douTuple = BufferLexical(sourFile);      // ֱ�Ӵ���Դ�ļ�
        #ifdef LEXICAL_SHOWS_DEFINE
        VisitTuple(douTuple);            // ������Ԫ����Ϣ, ���Ҷ�Ԫ����ȷ��
        #endif

        DestroyTuple(douTuple);                // ��ն�Ԫ��ռ�Ϊϵͳ��ʡ�ڴ�ռ�
    }

    #ifdef LEXICAL_HELPS_DEFINE
    VERSION( );
    #endif          // LEXICAL_HELPS_DEFINE


    #ifdef LEXICAL_DEBUG_DEFINE
    PAUSE( );
    #endif

}


// ��Դ�ļ����дʷ�����
void TestOfLexical( )    // ������Դ�ļ�
{
    #ifdef SYS_WINDOWS_DEF
    system("title �ʷ�������");
    system("color 00");
    #endif      // SYS_WINDOWS_DEF

    clock_t start, finish;
    start = clock( );

    BinaryTuple douTuple;               // ��Ԫ����Ϣ

    douTuple = BufferLexical("TEST/test0.c");      // ֱ�Ӵ���Դ�ļ�

    #ifdef LEXICAL_SHOWS_DEFINE
    VisitTuple(douTuple);            // ������Ԫ����Ϣ, ���Ҷ�Ԫ����ȷ��
    #endif
    DestroyTuple(douTuple);                // ��ն�Ԫ��ռ�Ϊϵͳ��ʡ�ڴ�ռ�

    #ifdef LEXICAL_HELPS_DEFINE
    VERSION( );
    #endif          // LEXICAL_HELPS_DEFINE

    #ifdef LEXICAL_DEBUG_DEFINE
    PAUSE( );
    #endif

    finish = clock( );
    printf("LEXICAL TIME : %lf seconds\n", (double)(finish - start)/(double)CLOCKS_PER_SEC);

}



