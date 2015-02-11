/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : main.c                                                         *
*   Description: CTools                                                         *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/




#include "LiteralTable.h"


/// Literal�ĺ�����������
#ifdef PUBLIC_and_PRIVATE
#
#
// ����token��Hash���еĲ���λ��
PRIVATE int LiteralHashCode(char *token);
#
#
#endif




// ����token��Hash���еĲ���λ��
int LiteralHashCode(char *token)
{
   for(int i = 0; token[i] != '\0'; i++)
   {

   }
   return 0;
}

// ����ʾtoken��ӽ�����ű�
Literal* InsertLiteralToken(char *token, LiteralTable literalTable)
{
    /// ���崮�Ĺ�ϣ������Ϣ, �Լ����ű�ָ����
    int code;                                   // ���浱ǰ���Ĺ�ϣ����
    Literal *pNode = NULL, *newNode = NULL;  // ����ָ����Ϣ

    /// ǰ�ڼ��Ĳ���
    if(LiteralHashCode(token) == CON_ERROR)     // ֻҪ��ʶ�����Ϸ�
    {
        return NULL;                        // ֱ�ӷ���
    }
    else if((pNode = FindLiteralToken(token, literalTable)) != NULL)   // ��ǰ��ʶ�����Ѿ��ڷ��ű���
    {
        return pNode;                        // ��ǰ���Ѿ���Ŀǰ����, �����ٲ���, ֱ�ӷ���ָ��ǰ���ĵ�ַ
    }
    //assert(token != NULL && strlen(token) > 0 && SymbolHashCode(token) == ID_ERROR);          // ��������Ϊ��

    /// ����ʶ�����뵽���ű�
    code = LiteralHashCode(token);     // ���㵱ǰ�����Ĺ�ϣ��

    /// ����ǰ��ʶ�������ϣ����
    if(literalTable[code]->m_offset/*ͷ����offset��ʶ��ǰ������������*/ == 0)        // �����ǰ��ϣ��û������
    {   // �ȳ�ʼ��ͷ�����, �ڽ����ݲ���
        // pNodeָ��ͷָ��
        /*Identifier* */pNode = literalTable[code];
        /*Identifier* */newNode = NULL;

        // ��ʼ��ͷ�����Ϣ
        pNode = (Literal *)malloc(sizeof(Literal));       // Ϊͷ��㿪�ٿռ�
        pNode->m_data = NULL;                                      // ͷ�������ƴ�Ϊ�մ�
        pNode->m_offset = 0;                            // ��ǰƫ�Ƶ�ַΪδ֪��
        pNode->m_kind = CONST;                                   // ��ǰ��ʶ��������δ֪
        //pNode->m_expand = NULL;                                   // ��ǰ��ʶ������չ��������ΪNULL
        pNode->m_next = NULL;                                     // ��һ��ָ����Ϊ��

        // ����Ҫ������Ϣ���½��
        newNode = (Literal*)malloc(sizeof(Literal));         // Ϊ�����ݿ��ٿռ�
        // �½���������ʼ��
        newNode->m_data = (char *)malloc(strlen(token) + sizeof(char));  // Ϊ���Ƶ����ݿ��ٿռ�
        strcpy(newNode->m_data, token);                              // Ϊ��ʶ�����Ƹ�ֵ
        newNode->m_offset = UNKNOWVALUE;                            // ��ǰƫ�Ƶ�ַΪδ֪��
        newNode->m_kind = UNKNOW;                                   // ��ǰ��ʶ��������δ֪
        //newNode->m_expand = NULL;                                   // ��ǰ��ʶ������չ��������ΪNULL
        newNode->m_next = NULL;                                     // ��һ��ָ����Ϊ��
        // ����������Ϣ
        pNode->m_next = newNode;                                    // ����ǰ��ĩβָ���µ�ĩβ

        // ��ǰ������������Ŀ��1
        literalTable[code]->m_offset++;   // ͷ����offset��ʶ��ǰ������������

        return pNode;// return newNode;                 // ���ص�ǰ������ĵ�ַ��Ϣ
    }
    else      // �����ǰ��ϣ���Ѿ���������
    {   // ֱ�ӽ����Ų���
        //Literal[code].m_name = malloc(strlen(token) + 1);       // Ϊ���������ƿ��ٱ�Ҫ�Ŀռ�
        /*Identifier* */pNode = literalTable[code]->m_next;                 // ָ��ͷ������һ��λ��Ҳ���ǵ�һ�����
        /*Identifier* */newNode = NULL;

        // �����ҵ���ǰ������ĩβ
        while(pNode != NULL)        // ѭ���ߵ������ĩβ
        {
            pNode = pNode->m_next;          //ֻҪ���������ĩβ������һ�������
        }

        // ���ٿռ�
        newNode = (Literal*)malloc(sizeof(Literal));         // Ϊ�����ݿ��ٿռ�
        // �������ʼ��
        newNode->m_data = (char *)malloc(strlen(token) + sizeof(char));  // Ϊ���Ƶ����ݿ��ٿռ�
        strcpy(newNode->m_data, token);                              // Ϊ��ʶ�����Ƹ�ֵ
        newNode->m_offset = UNKNOWVALUE;                            // ��ǰƫ�Ƶ�ַΪδ֪��
        newNode->m_kind = UNKNOW;                                   // ��ǰ��ʶ��������δ֪
        //newNode->m_expand = NULL;                                   // ��ǰ��ʶ������չ��������ΪNULL
        newNode->m_next = NULL;                                     // ��һ��ָ����Ϊ��
        // ����������Ϣ
        pNode->m_next = newNode;                                    // ����ǰ��ĩβָ���µ�ĩβ

        // ��ǰ������������Ŀ��1
        literalTable[code]->m_offset++;   // ͷ����offset��ʶ��ǰ������������

        return pNode;// return newNode;                 // ���ص�ǰ������ĵ�ַ��Ϣ
    }

    return pNode;
}


// ��ѯtoken�Ƿ��ڷ��ű���
Literal* FindLiteralToken(char *token, LiteralTable literalTable)
{
    int code = code = LiteralHashCode(token);     // ���㵱ǰ�����Ĺ�ϣ��

    Literal *pNode = literalTable[code]->m_next;       // ָ���һ�������Ϣ

    while(pNode != NULL)
    {
        if(strcmp(literalTable[code]->m_data, token) == 0)       // �����ǰ����Ŀǰ���
        {
            break;
        }
        pNode = pNode->m_next;          // ֻ����һ��ָ��λ��
    }

    return pNode;           // ���ص�ǰ����ַ
}









