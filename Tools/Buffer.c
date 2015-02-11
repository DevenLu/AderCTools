/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : BinaryTuple.h                                                  *
*   Description: CTools                                                         *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/


#include "Buffer.h"

///**
//˵��:
//��  ÿ���������Ĵ�СΪ -=> BUFFER_SIZE + sizeof(char) = 4097
//    �򻺳������±�Ϊ[0..BUFFER_SIZE - 1], ��[BUFFER_SIZE]���洢EOF
//
//��  ÿ���������ָ��֮����ַ���Ӧ��ȡ������������[m_lexeme, m_forward);
//
//
//�� ����ǰָ��ָ����һ���µĻ�����ʱ����ʼָ����Ȼָ��ǰһ���ɵĻ�����
//    ����ʹ��m_using��������Ȼָ�ɵĻ�����, ֻ����ִ����Check��ʹ�û�������ָ���µĻ�����
//
//��   ������ǰָ��Ϳ�ʼָ���ڲ���ͬһ����������ʱ�򣬸��ݢۣ�ʹ�õ���Ȼ�ǾɵĻ�����
//    ������ǰָ��һ�������������Ļ�������
//    ���ֻ��Ҫ����ǰָ���ڲ��ڵ�ǰʹ�õĻ������ڼ���
//**/

/**
˵��:0.6.9�Ի����������������޸�
    ԭʼ�汾��ʵ���У���Ҫ��Check��AddbufLexeme�ĺ����ж��޸Ļ�����ʹ�ñ�ʶ
    ���ڵİ汾�� ֻҪ��PutBuffer��ʹ�ñ�ʶm_using����ǰm_forward���Ѿ�ָ�����µĻ�����

    ����ֻ��һ���ط�����ʵ��m_using���޸ģ�����ʹ��������ʵ�ֶԳ���Ա͸��

��  ÿ���������Ĵ�СΪ -=> BUFFER_SIZE + sizeof(char) = 4097
    �򻺳������±�Ϊ[0..BUFFER_SIZE - 1], ��[BUFFER_SIZE]���洢EOF

��  ÿ���������ָ��֮����ַ���Ӧ��ȡ������������[m_lexeme, m_forward);
    ǰ�պ�

�� ����ǰָ��ָ����һ���µĻ�����ʱ����ʼָ����Ȼָ��ǰһ���ɵĻ�����
    ����ʹ��m_using�������Ѿ�ָ�����µĻ�����,

��   ������ǰָ��Ϳ�ʼָ���ڲ���ͬһ����������ʱ�򣬸��ݢۣ�ʹ�õ��Ѿ����µĻ�����
    ���������ǰָ��һ�������������Ļ�����(ʹ�û�����)������ʼָ�������Ȼ��ǰһ���ɵĻ�������
    ���ֻ��Ҫ����ʼָ���ڲ��ڵ�ǰʹ�õĻ������ڼ���
**/


/// ���ַ���str���뵽��������
/*[ʵ�ַ���]
    ���ݵ���ǰ��ǰָ���λ��, ���ַ�����Ϣstr�����ļ�
    ������ɺ�, ������ʼָ�����ǰָ���ָ��ǰ�����ַ����󻺳�����λ��
    ����ֵ���������������޸��˻�������λ��, ���ط���ֵfalse, ���򷵻�true
*/
bool WriteStrInBuffer(DouBuffer *douBuffer, char *str)
{
    assert(douBuffer->m_lexeme  == douBuffer->m_forward);       // ����Ҫ��ʼָ�����ǰָ�붼ָ����ʼλ��

    char *pStr = str;                   // ��ָ��ָ��ǰ�ַ������׵�ַ

    // ֻҪ�ַ���û�н���ͬʱ��ǰ������û�н����ͽ������ַ����е��������뻺����
    while(*pStr != '\0' && douBuffer->m_forward < BufferEnd(douBuffer, THIS))                // ѭ�������ַ���
    {
        *(douBuffer->m_forward) = *pStr;        // ���ַ������뻺��������ǰָ����
        (douBuffer->m_forward)++;                 // ��ǰָ��ָ����һ��λ��
        pStr++;                 // �ַ���ָ����һ��λ��
    }

    if(douBuffer->m_forward == BufferEnd(douBuffer, THIS)/*&& pStr != '\0'*/)        // ��������������˵����ַ�����û����ȫ���ȥ
    {   // ��ʣ����ַ������Ļ�������
        /// ���Ƚ����建�����е�����д������ļ���
        douBuffer->m_forward = BufferBegin(douBuffer, OTHER);           // �л�������һ���������Ŀ�ʼλ��
        while(*pStr != '\0')            // ����һ�����ַ�����ʣ��û�����뻺�������ַ������ȥ
        {
            *(douBuffer->m_forward) = *pStr;        // ���ַ������뻺��������ǰָ����
            (douBuffer->m_forward)++;                 // ��ǰָ��ָ����һ��λ��
            pStr++;                 // �ַ���ָ����һ��λ��
        }

        douBuffer->m_using *= -1;       // ����ʹ�û�����
        douBuffer->m_lexeme = douBuffer->m_forward;      // ��ǰָ��Ϳ�ʼָ�붼ָ�򻺳���

        return false;              // ����޸��˻�������ʹ�����-=>����false
    }
    return true;                   //û���޸Ļ�������ʹ���������true
}


/// ���������е���Ϣ�����ļ���
int WriteBufferToFile(DouBuffer *douBuffer, CToolsFILE ofp, int choice)
{
    #ifdef CTOOLS__DEBUG_DEFINE
    assert(ofp != NULL);
    #endif
    if(douBuffer->m_fp == NULL)             // �������ļ�ָ��Ϊ�ղ�������
    {
        return 0;
    }

    switch(choice)          // ���ݽ�Ҫ�������Ϣ���д���
    {
    case LEFT:              // �����Ҫ��������󲿻�����
        WriteLeftBufferToFile(douBuffer, ofp);      // ���󲿻���������Ϣд������ļ�

        break;
    case RIGHT:             // �����Ҫ��������Ҳ�������
        WriteRightBufferToFile(douBuffer, ofp);     // ���Ҳ�����������Ϣд������ļ�
        break;
    case ALL:               // �����Ҫ�����ȫ���Ļ�����
        WriteLeftBufferToFile(douBuffer, ofp);      // �Ƚ��󲿻�����������д���ļ�
        WriteRightBufferToFile(douBuffer, ofp);     // �Ƚ��Ҳ�������������д���ļ�
        break;
    }

    return 0;
}

/// ���������е���Ϣ�����ļ���
int WriteLeftBufferToFile(DouBuffer *douBuffer, CToolsFILE ofp)
{
    #ifdef CTOOLS_DEBUG_DEFINE
    assert(douBuffer != NULL && douBuffer->m_leftBuffer != NULL && douBuffer->m_fp != NULL);
    #endif      //  CTOOLS_DEBUG_DEFINE

    // ���󲿻�����ָ�뿪ʼ��BUFFER_SZIE���ֽڵ�����д��ofp�ļ���
    #ifdef CTOOLS_FILE_OPEN_BINARY
    fwrite(douBuffer->m_leftBuffer, BUFFER_SIZE, 1, douBuffer->m_fp);
    #endif // CTOOLS_FILE_OPEN_BINARY
    #ifdef CTOOLS_FILE_OPEN_TEXT
    //fputs(douBuffer->m_leftBuffer, BUFFER_SIZE, douBuffer->m_fp);

    #endif // CTOOLS_FILE_OPEN_TEXT

    return 0;
}

/// ���������е���Ϣ�����ļ���
int WriteRightBufferToFile(DouBuffer *douBuffer, CToolsFILE ofp)
{
    #ifdef CTOOLS_DEBUG_DEFINE
    assert(douBuffer != NULL && douBuffer->m_rightBuffer != NULL && douBuffer->m_fp != NULL);
    #endif      //  CTOOLS_DEBUG_DEFINE

    // ���Ҳ�������ָ�뿪ʼ��BUFFER_SZIE���ֽڵ�����д��ofp�ļ���
    #ifdef CTOOLS_FILE_OPEN_BINARY
    fwrite(douBuffer->m_rightBuffer, BUFFER_SIZE, 1, ofp);
    #endif // CTOOLS_FILE_OPEN_BINARY
    #ifdef CTOOLS_FILE_OPEN_TEXT
    fgets(douBuffer->m_rightBuffer, BUFFER_SIZE, douBuffer->m_fp);
    #endif // CTOOLS_FILE_OPEN_TEXT
    return 0;
}


/// ��������Դ�ļ�m_fp�ļ�����Ϣ���ַ�Ϊ��λ���뻺����
int PutBuffer(DouBuffer *douBuffer)
{
    if(feof(douBuffer->m_fp) != 0)           // ���ȼ���Ƿ������ļ�ĩβ
    {
        return CToolsIsEOF;       // #define -1
    }

    int i = 0;
    int ch;

    switch((int)douBuffer->m_using)
    {
        case LEFT  :        // �����ǰ���ڴ����������󲿷�
            while((i < (int)BUFFER_SIZE) && ((ch = CToolsGetc(douBuffer->m_fp)) != EOF))          // �����������Ҳ��ֻ�����
            {
                douBuffer->m_rightBuffer[i++] = ch;
                //printf("%d\n", douBuffer->m_rightBuffer[i-1]);
            }
            douBuffer->m_rightBuffer[i] = (char)EOF;      // ������ĩβ�����ļ�������־EOF

            douBuffer->m_forward = douBuffer->m_rightBuffer;      // ��ǰָ���ʼ��ָ�򻺳�����ͷ

            douBuffer->m_using = RIGHT;
            #ifdef CTOOLS_HELPS_DEFINE       // ���ð�����Ϣ��-=>��ʾ�����Ѿ�д���һ�����
            FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
            printf("\n\t\t***********************************************\n");
            printf("\t\t**Data are already write in the RightBuffer..**\n");
            printf("\t\t***********************************************\n");
            PAUSE( );
            #endif      // CTOOLS_HELPS_DEFINE

            break;

        case NOT_USE:                       // �ոճ�ʼ�����
            douBuffer->m_lexeme =  douBuffer->m_forward = douBuffer->m_leftBuffer;      // ����ָ��ָ���󲿻�������ʼλ��
            //douBuffer->m_using = LEFT;                // ��ʼ��ʹ���󲿻�����
            /*break;*/
        case RIGHT :        // �����ǰ���ڴ����������Ҳ���, �������ֱ�ӽ�����д���󻺳���
            while(i < (int)BUFFER_SIZE && ((ch = CToolsGetc(douBuffer->m_fp)) != EOF))          // �����������Ҳ��ֻ�����
            {
                douBuffer->m_leftBuffer[i++] = ch;
                //printf("%d\n", douBuffer->m_leftBuffer[i-1]);
            }
            douBuffer->m_leftBuffer[i] = (char)EOF;      // ������ĩβ�����ļ�������־EOF

            douBuffer->m_forward = douBuffer->m_leftBuffer;          // ��ǰָ���ʼ��ָ�򻺳�����ͷ

            douBuffer->m_using = LEFT;
            #ifdef CTOOLS_HELPS_DEFINE               // ���ð�����Ϣ��-=>��ʾ�����Ѿ�д���󻺳���
            FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
            printf("\n\t\t***********************************************\n");
            printf("\t\t**Data are already write in the LeftBuffer...**\n");
            printf("\t\t***********************************************\n");
            PAUSE( );
            #endif        // CTOOLS_HELPS_DEFINE

            break;
        default :
            #ifdef CTOOLS_HELPS_DEFINE
            FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
            printf("\n\t\t***********************************************\n");
            printf("\t\t**     Error When Date Put in PutBuffer...   **\n");
            printf("\t\t***********************************************\n");
            PAUSE( );
            #endif      // CTOOLS_HELPS_DEFINE
            break;
    }

    //PAUSE( );
    if(feof(douBuffer->m_fp) != 0)
    {
        return CToolsToEOF;       // #define 1
    }
    else
    {
        return CToolsNotEOF;    // #define 0
    }
}

/* ����˫�������ļ�
DouBuffer* CreateBuffer()
{
    DouBuffer *douBuffer = (DouBuffer *)malloc(sizeof(DouBuffer));          // ���ƻ������Ľṹ�洢��Ϣ

    // ���ȳ�ʼ����������������Ϣ
    douBuffer->m_leftBuffer = (char *)malloc(BUFFER_SIZE + sizeof(char));     // �����󻺳����Ŀռ�
    douBuffer->m_rightBuffer = (char *)malloc(BUFFER_SIZE + sizeof(char));    // �����һ������Ŀռ�

    // ��ʼ�����󲿻�����д����Ϣ
    douBuffer->m_using = NOT_USE;     // ��ʼ��������ΪRIGHT, ����������ʹ��������������д��

    return douBuffer;
}
*/

// ��ʼ������������Ϣ
DouBuffer* InitBuffer(const char *fileName)
{
    DouBuffer *douBuffer = (DouBuffer *)malloc(sizeof(DouBuffer));          // ���ƻ������Ľṹ�洢��Ϣ
    // ���ȳ�ʼ����������������Ϣ
    douBuffer->m_leftBuffer = (char *)malloc(BUFFER_SIZE + sizeof(char));     // �����󻺳����Ŀռ�
    douBuffer->m_rightBuffer = (char *)malloc(BUFFER_SIZE + sizeof(char));    // �����һ������Ŀռ�

    douBuffer->m_using = NOT_USE;               // ��ǰ�������ճ�ʼ��, ��δ��ʹ��λ��

    /// ��Դ�ļ�
    #ifdef CTOOLS_FILE_OPEN_TEXT
    douBuffer->m_fp = CToolsOpen(fileName, READ_ONLY_TEXT);
    #endif // CTOOLS_FILE_OPEN_TEXT
    // �����������ǲ��ܹ����...
    #ifdef CTOOLS_FILE_OPEN_BINARY
    douBuffer->m_fp = CToolsOpen(fileName, READ_ONLY_BINARY);
    #endif // CTOOLS_FILE_OPEN_BINARY

    douBuffer->m_lexeme = NULL;
    douBuffer->m_forward = NULL;

    douBuffer->m_coord = InitCoord(fileName);       // ����Դ�ļ���Ϣ��ʼ��ƫ����Ϣ

    #ifdef CTOOLS_HELPS_DEFINE         // ���ð����� -=> ��ʾ�������Ѿ���ʼ��
    FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
    printf("\n\t*****************************************************************\n");
    printf("\t**The Double Buffer has been init for you to read infomation...**\n");
    printf("\t*****************************************************************\n");
    PAUSE( );
    #endif          // CTOOLS_HELPS_DEFINE

    return douBuffer;
}




// ��������β����
void FinitBuffer(DouBuffer *douBuffer)
{
    // �����󲿻�����
    if(douBuffer->m_leftBuffer != NULL)
    {
        free(douBuffer->m_leftBuffer);
    }

    // �����Ҳ�������
    if(douBuffer->m_rightBuffer != NULL)
    {
        free(douBuffer->m_rightBuffer);
    }

    // �ر��ļ�
    CToolsClose(douBuffer->m_fp);

    // ����λ����Ϣ��ʶ
    if(douBuffer->m_coord != NULL)
    {
        free(douBuffer->m_coord);
    }

    // ���ٻ������ṹ
    if(douBuffer != NULL)           // ����Ϊ������ָ�뿪�ٵĿռ�
    {
        free(douBuffer);
    }



    #ifdef CTOOLS_HELPS_DEFINE         // ���ð����� -=> ��ʾ�������Ѿ������β
    FILE_FUNC_LINE( );      // ��ʾ�ļ���-������-�к�
    printf("\n\t*****************************************************************\n");
    printf("\t**       Dis End...The Double Buffer has been destroy...       **\n");
    printf("\t*****************************************************************\n");
    PAUSE( );
    #endif          // CTOOLS_HELPS_DEFINE
}

// ���㻺��������ָ��֮���ַ����ĳ���
int TokenLength(DouBuffer *douBuffer)
{
    if(IsInSameBuffer(douBuffer) == true)   // �������ָ����һ��������
    {
        #ifdef CTOOLS_DEBUG_DEFINE
        printf("����ָ����ͬһ��������\n");
        #endif // CTOOLS_DEBUG_DEFINE

        return (douBuffer->m_forward - douBuffer->m_lexeme);    // ����
    }
    else        // ��ʱ����ָ��ͬһ��������
    {
        #ifdef CTOOLS_DEBUG_DEFINE
        printf("����ָ�벻��ͬһ������\n");
        FILE_FUNC_LINE( );
        printf("����ʹ��%d������\n", douBuffer->m_using);
        printf("��ʼָ��%p\n", douBuffer->m_lexeme);
        printf("��ǰָ��%p\n", douBuffer->m_forward);
        printf("�󻺳�����ʼ[%p, %p]\n", douBuffer->m_leftBuffer, douBuffer->m_leftBuffer + BUFFER_SIZE);
        printf("�һ�������ʼ[%p, %p]\n", douBuffer->m_rightBuffer, douBuffer->m_rightBuffer + BUFFER_SIZE);
        #ifdef CTOOLS_STEP_DEFINE
        PAUSE( );
        #endif
        #endif // CTOOLS_DEBUG_DEFINE


        return ((douBuffer->m_forward - BufferBegin(douBuffer, THIS))/*��ǰָ�������ڻ�������ʼ�Ĳ�ֵ*/ + (BufferEnd(douBuffer, OTHER) - douBuffer->m_lexeme));
    }
}



// ����ʼ�ַ�����ǰָ��֮����ַ�������
char* CopyBufToken(DouBuffer *douBuffer)
{
#ifdef CTOOLS_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // CTOOLS_DEBUG_DEFINE
    #ifdef CTOOLS_DEBUG_DEFINE
    printf("%p %p %d\n", douBuffer->m_lexeme, douBuffer->m_forward, TokenLength(douBuffer));
    #endif // CTOOLS_DEBUG_DEFINE

    if(TokenLength(douBuffer) < 1)               // ������С��1, ˵���м�û�д�������ȡ-=>����
    {
        if(TokenLength(douBuffer) < 0)
        {
            FILE_FUNC_LINE( );
            printf("����ʹ��%d������\n", douBuffer->m_using);
            printf("��ʼָ��%p\n", douBuffer->m_lexeme);
            printf("��ǰָ��%p\n", douBuffer->m_forward);
            printf("�󻺳�����ʼ[%p, %p]\n", douBuffer->m_leftBuffer, douBuffer->m_leftBuffer + BUFFER_SIZE);
            printf("�һ�������ʼ[%p, %p]\n", douBuffer->m_rightBuffer, douBuffer->m_rightBuffer + BUFFER_SIZE);
            printf("ǰ��Ĵ�����%p - %p = %d\n", BufferEnd(douBuffer, OTHER), douBuffer->m_lexeme, (BufferEnd(douBuffer, OTHER) - douBuffer->m_lexeme));
            printf("����Ĵ�����%p - %p = %d\n", douBuffer->m_forward, BufferBegin(douBuffer, THIS), (douBuffer->m_forward - BufferBegin(douBuffer, THIS)));
            printf("������������ʱ��ʱ����\n");

            PAUSE( );

        }
        return NULL;
    }

    char    *token = (char *)malloc(TokenLength(douBuffer) + 1);
    char    *pbuf = douBuffer->m_lexeme, *pstr = token;

    if(IsInSameBuffer(douBuffer) == true)          // �������ָ����ͬһ��������
    {//FILE_FUNC_LINE( );
        //printf("����ָ����ͬһ��������\n");
        while(pbuf < (douBuffer->m_forward))     // ����ÿ���ַ���
        {
            //printf("%p %p\n", pbuf, douBuffer->m_forward);
            *(pstr++) = *(pbuf++);
            //printf("%p %p\n", pbuf, douBuffer->m_forward);
        }
        *pstr = '\0';
    }
    else
    {
        while(pbuf < BufferEnd(douBuffer, OTHER))            // ����ȡ����ǰָ���еĴ�
        {
            *pstr++ = *pbuf++;
        }

        // ��ȡ������һ������������Ϣ
        pbuf = BufferBegin(douBuffer, THIS);
        while(pbuf < douBuffer->m_forward)
        {
            *pstr++ = *pbuf++;
        }
        *pstr = '\0';
    }
//    else if(douBuffer->m_using == LEFT)      // ��Ȼ��ʹ���󻺳���, ������ǰָ��
//    {//FILE_FUNC_LINE( );
//         //printf("��ʼָ�����󻺳���, ��ǰָ�����һ�����\n");
//         while(pbuf < LeftBufferEnd(douBuffer))     //  �Ƚ����ڻ������е���Ϣ����
//         {
//             *pstr++ = *pbuf++;
//         }
//         pbuf = douBuffer->m_rightBuffer;     // ����ֵָ�붨λ�ڻ�������ʼλ��
//         while(pbuf < douBuffer->m_forward)          // �������ڻ������еĻ����
//         {
//             *pstr++ = *pbuf++;
//         }
//         *pstr = '\0';
//    }
//    else if(douBuffer->m_using == RIGHT)
//    {//FILE_FUNC_LINE( );
//         //printf("��ʼָ�����һ�����, ��ǰָ�����󻺳���\n");
//         while(pbuf < RightBufferEnd(douBuffer))
//         {
//             *pstr++ = *pbuf++;
//         }
//         pbuf = douBuffer->m_leftBuffer;
//         while(pbuf < douBuffer->m_forward)
//         {
//             *pstr++ = *pbuf++;
//         }
//         *pstr = '\0';
//    }

    #ifdef CTOOLS_DEBUG_DEFINE
    printf("��ȡ�������ַ���Ϊ��%s\n", token);
    #endif // CTOOLS_DEBUG_DEFINE

    return token;       // ���ش�ָ��
}


// ����ʼָ��ָ����һλ��, ͬʱ����λ�ñ�ƫ����Ŀ�ʼƫ��
void AddBufLexeme(DouBuffer *douBuffer)
{
    douBuffer->m_lexeme++;
    AddCoordBegOffset(douBuffer->m_coord);

    if(IsLexmeAtBufEnd(douBuffer) == true)           // �����ʼָ��ָ���˻�������ĩβ
    {
        if(IsInSameBuffer(douBuffer) == true)
        {
            douBuffer->m_lexeme = BufferBegin(douBuffer, OTHER);
        }
        else
        {
            douBuffer->m_lexeme = BufferBegin(douBuffer, THIS);
        }
    }
    // return
}

// ����ǰָ��ָ����һ��λ��, ͬʱ����λ��ָ��Ľ���ƫ��
int AddBufForward(DouBuffer *douBuffer)
{

    douBuffer->m_forward++;                 // ����ǰָ����ǰ��һ����λ
    AddCoordEndOffset(douBuffer->m_coord);  // ÿ����ǰָ���1, ����Ҫ��λ��ָ��ƫ�ƽ�1

    if(IsBufferEnd(douBuffer) == true)
    {
        //printf("%d, �ļ�ĩβ���ط���ֵ%d\n", __LINE__, feof(douBuffer->m_fp));PAUSE( );
        //PAUSE( );
        return PutBuffer(douBuffer);
    }

    return CToolsNotEOF;
}


// ����ʼָ��ָ����һλ��, ͬʱ����λ�ñ�ƫ����Ŀ�ʼƫ��
void SubBufLexeme(DouBuffer *douBuffer)
{
    if(douBuffer->m_lexeme == BufferBegin(douBuffer, 0))        // �����ʼָ���ڵ�ǰ�������Ŀ�ʼ
    {
        douBuffer->m_lexeme = BufferEnd(douBuffer, 1);
    }
    else
    {
        douBuffer->m_lexeme--;
    }

    SubCoordBegOffset(douBuffer->m_coord);
}

// ����ǰָ��ָ����һ��λ��, ͬʱ����λ��ָ��Ľ���ƫ��
void SubBufForward(DouBuffer *douBuffer)
{
    if(douBuffer->m_forward == BufferBegin(douBuffer, 0))        // �����ʼָ���ڵ�ǰ�������Ŀ�ʼ
    {
        douBuffer->m_forward = BufferEnd(douBuffer, 1);
    }
    else
    {
        douBuffer->m_lexeme--;
    }

    SubCoordEndOffset(douBuffer->m_coord);

}






// ��鿪ʼָ���ǲ���λ�ڻ�����ĩβ
bool IsLexmeAtBufEnd(DouBuffer *douBuffer)
{
    switch((int)douBuffer->m_using)
    {
        case LEFT  :        // �����ǰ���ڴ����������󲿷�
            return (douBuffer->m_lexeme == (douBuffer->m_leftBuffer + BUFFER_SIZE)
                    || *(douBuffer->m_lexeme) == (char)EOF );     // ������ǰָ���Ƿ񵽴ﻺ����ĩβ
            //break;
        case RIGHT :        // �����ǰ���ڴ���Ļ������Ҳ���
            return (douBuffer->m_lexeme == (douBuffer->m_rightBuffer + BUFFER_SIZE)    // ������ǰָ���Ƿ񵽴ﻺ����ĩβ
                    || *(douBuffer->m_lexeme) == (char)EOF);
        default:
            return false;
    }
    return false;
}


bool IsBufferEnd(DouBuffer *douBuffer)
{
    switch((int)douBuffer->m_using)
    {
        case LEFT  :        // �����ǰ���ڴ����������󲿷�
            return (douBuffer->m_forward == (douBuffer->m_leftBuffer + BUFFER_SIZE)
                    || *(douBuffer->m_forward) == (char)EOF );     // ������ǰָ���Ƿ񵽴ﻺ����ĩβ
            //break;
        case RIGHT :        // �����ǰ���ڴ���Ļ������Ҳ���
            return (douBuffer->m_forward == (douBuffer->m_rightBuffer + BUFFER_SIZE)    // ������ǰָ���Ƿ񵽴ﻺ����ĩβ
                    || *(douBuffer->m_forward) == (char)EOF);
        default:
            return false;
    }
    return false;
}


// ��ȡ��ǰ���ַ���Ϣ
char NowData(DouBuffer *douBuffer)
{
    return *(douBuffer->m_forward);
}

// ��ȡ��һ���ַ�����Ϣ
char NextData(DouBuffer *douBuffer)
{
    return *(douBuffer->m_forward + 1);
}



// �жϵ�ǰ����ָ���Ƿ���ͬһ���������ڲ�
bool IsInSameBuffer(DouBuffer *douBuffer)
{
    switch((int)douBuffer->m_using)
    {
    case LEFT :
        return  (douBuffer->m_lexeme >= douBuffer->m_leftBuffer
             && douBuffer->m_lexeme <= douBuffer->m_leftBuffer + BUFFER_SIZE);
    case RIGHT:
        return  (douBuffer->m_lexeme >= douBuffer->m_rightBuffer
             && douBuffer->m_lexeme <= douBuffer->m_rightBuffer + BUFFER_SIZE);
    default :
        ///Error();
        break;
    }
    return false;
}


// ���ص�ǰ�󲿻�������ĩβ
char*  LeftBufferEnd(DouBuffer *douBuffer)
{
    return (douBuffer->m_leftBuffer + BUFFER_SIZE);
}

// ���ص�ǰ�Ҳ���������ĩβ
char* RightBufferEnd(DouBuffer *douBuffer)
{
    return (douBuffer->m_rightBuffer + BUFFER_SIZE);
}

// ���ص�ǰ������ĩβ
char* BufferEnd(DouBuffer *douBuffer, int choice)
{   // LEFT = -1, RIGHT = 1
    // ���� , ��ʾ��ǰʹ�õĻ�������ĩβ
    // ���� -1, ��ʾ��ǰδʹ�û�������ĩβ
    // unsing + choice
    // 0  0 �󻺳���ĩβ0 / 2 = 0
    // 0  1 �һ�����ĩβ1 / 2 = 1
    // 1  0 �һ�����ĩβ1 / 2 = 1
    // 1  1 �󻺳���ĩβ2 / 2 = 0
    #ifdef CTOOLS_DEBUG_DEFINE
    printf("���㻺�����Ľ���\n");
    printf("����ʹ��%d������\n", douBuffer->m_using);
    #endif // CTOOLS_DEBUG_DEFINE

    switch(((int)douBuffer->m_using + choice) % 2)
    {
        case LEFT :
            #ifdef CTOOLS_DEBUG_DEFINE
            printf("�����󻺳�������%p\n", douBuffer->m_leftBuffer + BUFFER_SIZE);
            #endif // CTOOLS_DEBUG_DEFINE
            return (char *)(douBuffer->m_leftBuffer + BUFFER_SIZE);     // LeftBufferEnd(douBuffer);
            //break;

        case RIGHT:
            #ifdef CTOOLS_DEBUG_DEFINE
            printf("�����һ���������%p\n", douBuffer->m_rightBuffer + BUFFER_SIZE);
            #endif // CTOOLS_DEBUG_DEFINE
            return (char *)(douBuffer->m_rightBuffer + BUFFER_SIZE);    // RightBufferEnd(douBuffer);
            //break;
        default:
            return (char *)NULL;
            break;
    }
    return NULL;
}


/// �������Ŀ�ʼλ��
char* BufferBegin(DouBuffer *douBuffer, int choice)
{   // LEFT = 0, RIGHT = 1
    // ���� 0, ��ʾ��ǰʹ�õĻ������Ŀ�ʼ
    // ���� 1, ��ʾ��ǰδʹ�û������Ŀ�ʼ
    // unsing + choice
    //0 0 �󻺳�����ʼ0 % 2 = 0
    //0 1 �һ�������ʼ1 % 2 = 1
    //1 0 �һ�������ʼ1 % 2 = 1
    //1 1 �󻺳�����ʼ2 % 2 = 0
    #ifdef CTOOLS_DEBUG_DEFINE
    printf("���㻺�����Ŀ�ʼ\n");
    printf("����ʹ��%d������\n", douBuffer->m_using);
    #endif // CTOOLS_DEBUG_DEFINE
    switch(((int)douBuffer->m_using + choice) % 2)
    {
        case LEFT :         // 0
            #ifdef CTOOLS_DEBUG_DEFINE
            printf("�����󻺳�����ʼ%p\n", douBuffer->m_leftBuffer);
            #endif // CTOOLS_DEBUG_DEFINE
            return (char *)(douBuffer->m_leftBuffer);
            //break;
        case RIGHT:         // 1
            #ifdef CTOOLS_DEBUG_DEFINE
            printf("�����һ�������ʼ%p\n", douBuffer->m_rightBuffer);
            #endif // CTOOLS_DEBUG_DEFINE

            return (char *)(douBuffer->m_rightBuffer);
            //break;
        default:
            return (char *)NULL;
    }

    return NULL;
}

/// ����ʼָ���������ǰָ���λ��
void CheckLexemeToForward(DouBuffer *douBuffer)
{

//    if(IsInSameBuffer(douBuffer) != true)      // �����ǰ����ָ�벻��ͬһ����
//    {
//        printf("����ǰʹ��%d������\n", douBuffer->m_using);
//        // LEFT 0, RIGHT 1
//        int using = douBuffer->m_using;
//        douBuffer->m_using  = (using == 1) ? 0 : 1;           // ����ʹ������
//        //#ifdef CTOOLS_DEBUG_DEFINE
//        printf("����ʹ������Ϊ%d\n", douBuffer->m_using);
//        //#ifdef CTOOLS_STEPS_DEFINE
//        PAUSE( );
//        //#endif      // CTOOLS_STEPS_DEFINE
//        //#endif      // CTOOLS_DEBUG_DEFINE
//        printf("����ǰ����ʼָ��%p����ǰָ��%p\n", douBuffer->m_lexeme, douBuffer->m_forward);
//    }

    douBuffer->m_lexeme = douBuffer->m_forward;
    CheckBegOffsetToEndOffset(douBuffer->m_coord);

    #ifdef CTOOLS_DEBUG_DEFINE
    printf("�����󣬿�ʼָ��%p����ǰָ��%p\n", douBuffer->m_lexeme, douBuffer->m_forward);
    printf("����ָ�븴λ\n");
    #endif
}



bool IsBufSpace(DouBuffer *douBuffer)
{
    return (*(douBuffer->m_forward) == ' '
        || *(douBuffer->m_forward) == '\t'
        || *(douBuffer->m_forward) == '\r'
        || *(douBuffer->m_forward) == '\n');
}

/// ����Ԥ���봦��ʱ,�����հ��ַ�����Ϣ-=>�ո��Ʊ����
void DisBufSpace(DouBuffer *douBuffer)
{
#ifdef CTOOLS_DEBUG_DEFINE
FILE_FUNC_LINE( );
assert(IsBufSpace(douBuffer) == true);
#endif // CTOOLS_DEBUG_DEFINE

    while(IsBufSpace(douBuffer) == true)     // ����Ԥ����ָ�������Ը�������Ŀհ��ַ�
    {
        if(*(douBuffer->m_forward) == '\n')
        {
            douBuffer->m_coord->m_fileLine++;       // �ļ���������1

            #ifdef LEXICAL_DEBUG_DEFINE
            FILE_FUNC_LINE( );
            printf("����һ�к�LINE = %d\n", douBuffer->m_coord->m_fileLine);
            #ifdef CTOOLS_STEPS_DEFINE
            PAUSE( );
            #endif      // CTOOLS_STEPS_DEFINE
            #endif
        }
        AddBufForward(douBuffer);      // ��������ǰָ������

        #ifdef CTOOLS_DEBUG_EFINE
        printf("�����˿հ��ַ�\n");
        #endif // CTOOLS_DEBUG_EFINE


    }
    CheckLexemeToForward(douBuffer);        // ��λ��ʼָ�뵽��ǰѭ���ҵ�λ��
}




/// ��������ַ�
void DisBufControl(DouBuffer *douBuffer)
{
#ifdef CTOOLS_DEBUG_DEFINE
FILE_FUNC_LINE( );
assert(iscntrl(*(douBuffer->m_forward)) != 0);
#endif // CTOOLS_DEBUG_DEFINE
    // ����ָ������ո񡢻��з����Ʊ������

    /// �����һ���ַ����ǿո񡢻��С��Ʊ�������߲��ɴ�ӡ�ַ�
    while(iscntrl(*(douBuffer->m_forward)) != 0)
    {
        if(*(douBuffer->m_forward) == '\n')
        {
            douBuffer->m_coord->m_fileLine++;       // �ļ���������1

            #ifdef LEXICAL_DEBUG_DEFINE
            FILE_FUNC_LINE( );
            printf("����һ�к�LINE = %d\n", douBuffer->m_coord->m_fileLine);
            #ifdef CTOOLS_STEPS_DEFINE
            PAUSE( );
            #endif      // CTOOLS_STEPS_DEFINE
            #endif      // LEXICAL_DEBUG_DEFINE
        }
        AddBufForward(douBuffer);
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1


        #ifdef LEXICAL_DEBUG_DEFINE
        printf("���������ַ�%c = %d\n", *(douBuffer->m_forward), *(douBuffer->m_forward));
        #endif  // LEXICAL_DEBUG_DEFINE
    }
}


void DisBufCurrLine(DouBuffer *douBuffer)
{
#ifdef CTOOLS_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // CTOOLS_DEBUG_DEFINE
    while (*(douBuffer->m_forward) != '\n')  //ֱ����һ�н���Ϊֹ
    {
        AddBufForward(douBuffer);
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
    }

    if(*(douBuffer->m_forward) == '\n')
    {
        #ifdef LEXICAL_DEBUG_DEFINE
        FILE_FUNC_LINE( );
        printf("������һ��\n");
        #ifdef CTOOLS_STEPS_DEFINE
        PAUSE( );
        #endif      // CTOOLS_STEPS_DEFINE
        #endif // LEXICAL_DEBUG_DEFINE
        douBuffer->m_coord->m_fileLine++;                // ������һ��
    }
}



void DisBufCommentLine(DouBuffer *douBuffer)
{
#ifdef CTOOLS_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // CTOOLS_DEBUG_DEFINE
    while (!(*(douBuffer->m_forward - 1) == '*' && *(douBuffer->m_forward) == '/') )   //ֱ������*/Ϊֹ
    {
        if(*(douBuffer->m_forward) == '\n')     // ���˸��еĽ�����Ҫ���ļ����кŽ�1
        {
            #ifdef LEXICAL_DEBUG_DEFINE
            FILE_FUNC_LINE( );
            printf("������һ��\n");
            #ifdef CTOOLS_STEPS_DEFINE
            PAUSE( );
            #endif  //CTOOLS_STEPS_DEFINE
            #endif // LEXICAL_DEBUG_DEFINE
            douBuffer->m_coord->m_fileLine++;                // ������һ��
        }
            // DisCommentLine(douBuffer);
        AddBufForward(douBuffer);
    }
}



// ����Ԥ����ָ����Ϣ
void DisBufProcom(DouBuffer *douBuffer)
{
#ifdef LEXICAL_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif
    /// ������Ԥ��������ĺ���������Ϣ
    while( 1 )
    {

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("��ǰ�ַ�%c, ƫ��%d %d\n", *(douBuffer->m_forward), douBuffer->m_coord->m_fileBegOffset, douBuffer->m_coord->m_fileEndOffset);
        #endif  // LEXICAL_DEBUG_DEFINE

        #ifdef LEXICAL_DEBUG_DEFINE
        printf("%c", *(douBuffer->m_forward));
        #endif // LEXICAL_DEBUG_DEFINE

        if(*(douBuffer->m_forward) == '\n')
        {
            douBuffer->m_coord->m_fileLine++;

            #ifdef LEXICAL_DEBUG_DEFINE
            FILE_FUNC_LINE( );
            printf("������һ��\n");
            #ifdef CTOOLS_STEPS_DEFINE
            PAUSE( );
            #endif  //CTOOLS_STEPS_DEFINE
            #endif // LEXICAL_DEBUG_DEFINE

            if(*(douBuffer->m_forward - 1) == '\\')      // Ԥ����ָ��ʹ�������з�
            {
                //continue;
            }
            else if(*(douBuffer->m_forward + 1) == '#')
            {
               // continue;
            }
            else
            {
                #ifdef LEXICAL_DEBUG_DEFINE
                printf("��ǰ�ַ�%c, ƫ��%d %d\n", *(douBuffer->m_forward), douBuffer->m_coord->m_fileBegOffset, douBuffer->m_coord->m_fileEndOffset);
                #endif  // LEXICAL_DEBUG_DEFINE
                break;
            }
        }
        AddBufForward(douBuffer);
        //AddCoordEndOffert(coord);           // ÿ��ǰ���ƽ��ַ�, ƫ�ƾ�����1
    }

    #ifdef LEXICAL_DEBUG_DEFINE
    printf("��ǰ�ַ�%c, ƫ��%d %d\n", *(douBuffer->m_forward), douBuffer->m_coord->m_fileBegOffset, douBuffer->m_coord->m_fileEndOffset);
    #endif  // LEXICAL_DEBUG_DEFINE
}
