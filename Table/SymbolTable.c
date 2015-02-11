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




#include "SymbolTable.h"

#define ID_ERROR -1


/// SymBolTable�ĺ�����������
#ifdef PUBLIC_and_PRIVATE
#
#
// ����token��Hash���еĲ���λ��
PRIVATE int SymbolHashCode(char *token);
#
#
#endif




// ����token��Hash���еĲ���λ��
int SymbolHashCode(char *token)
{
    //assert(token != NULL && strlen(token) > 0);          // ��������Ϊ��
    if(token[0] == '_')         // ��_�»��߿�ͷ�ı�����ʶ
    {
        return 0;
    }
    else if(isalpha(token[0]) != 0)     // ����ĸ��ͷ��
    {
        return tolower(token[0]) - 'a';       // ������ĸ�����
    }
    else
    {
        return ID_ERROR;      // ���ش��󲻺Ϸ��ı�ʶ����
    }
}

// ����ʾtoken��ӽ�����ű�
Identifier* InsertSymbolToken(char *token, SymbolTable symbolTable)
{
    /// ���崮�Ĺ�ϣ������Ϣ, �Լ����ű�ָ����
    int code;                                   // ���浱ǰ���Ĺ�ϣ����
    Identifier *pNode = NULL, *newNode = NULL;  // ����ָ����Ϣ
    printf("%s %d %p\n", __func__, __LINE__, symbolTable);
    /// ǰ�ڼ��Ĳ���
    if(SymbolHashCode(token) == ID_ERROR)     // ֻҪ��ʶ�����Ϸ�
    {
        return NULL;                        // ֱ�ӷ���
    }
    else if((pNode = FindSymbolToken(token, symbolTable)) != NULL)   // ��ǰ��ʶ�����Ѿ��ڷ��ű���
    {
        return pNode;                        // ��ǰ���Ѿ���Ŀǰ����, �����ٲ���, ֱ�ӷ���ָ��ǰ���ĵ�ַ
    }
    //assert(token != NULL && strlen(token) > 0 && SymbolHashCode(token) == ID_ERROR);          // ��������Ϊ��

    printf("%d", __LINE__);system("pause");

    /// ����ǰ��ʶ��������ű�Ĺ�ϣ����
    code = SymbolHashCode(token);     // ���㵱ǰ�����Ĺ�ϣ��

    // �����ҵ���ǰ������ĩβ
    pNode = symbolTable[code]->m_next;                 // ָ��ͷ������һ��λ��Ҳ���ǵ�һ�����

    while(pNode != NULL)        // ѭ���ߵ������ĩβ
    {
        pNode = pNode->m_next;          //ֻҪ���������ĩβ������һ�������
    }

    // ���ٿռ�
    newNode = (Identifier *)malloc(sizeof(Identifier));         // Ϊ�����ݿ��ٿռ�
    // �������ʼ��
    newNode->m_name = (char *)malloc(sizeof(token));  // Ϊ���Ƶ����ݿ��ٿռ�
    strcpy(newNode->m_name, token);                              // Ϊ��ʶ�����Ƹ�ֵ

    newNode->m_offset = UNKNOWVALUE;                            // ��ǰƫ�Ƶ�ַΪδ֪��
    newNode->m_kind = UNKNOW;                                   // ��ǰ��ʶ��������δ֪
    newNode->m_expand = NULL;                                   // ��ǰ��ʶ������չ��������ΪNULL
    newNode->m_next = NULL;                                     // ��һ��ָ����Ϊ��
    // ����������Ϣ
    pNode->m_next = newNode;                                    // ����ǰ��ĩβָ���µ�ĩβ
    // ��ǰ������������Ŀ��1
    symbolTable[code]->m_offset++;   // ͷ����offset��ʶ��ǰ������������

    return pNode;// return newNode;                 // ���ص�ǰ������ĵ�ַ��Ϣ

}


// ��ѯtoken�Ƿ��ڷ��ű���
Identifier* FindSymbolToken(char *token, SymbolTable symbolTable)
{
    int code = code = SymbolHashCode(token);     // ���㵱ǰ�����Ĺ�ϣ��
    printf("%s %d %p\n", __func__, __LINE__, symbolTable);
    printf("%s %d %p\n", __func__, __LINE__, *(symbolTable + code));
    printf("%s %d %p\n", __func__, __LINE__, symbolTable[code]);
    Identifier *pNode = symbolTable[code];       // ָ���һ�������Ϣ
    printf("%s %d %p\n", __func__, __LINE__, symbolTable);
    //symbolTable[code]->m_offset;
    printf("1111");
    printf("%s %d %d\n", __func__, __LINE__, symbolTable[code]->m_offset);
    printf("1111");
    if(pNode->m_offset == 0)     // �����ǰ��ϣ���л�û������
    {
        printf("%d", __LINE__);system("pause");
        return NULL;
    }
    printf("%d", __LINE__);system("pause");

    for(pNode = pNode->m_next; pNode != NULL; pNode = pNode->m_next)
    {
        if(strcmp(symbolTable[code]->m_name, token) == 0)       // �����ǰ����Ŀǰ���
        {
            break;
        }
    }

    return pNode;           // ���ص�ǰ����ַ
}



// ��ʼ����ϣ����Ϣ
SymbolTable InitSymbolTalbe(SymbolTable __attribute__((unused)) symbolTable)
{   /// ������һ������, ԭ��Ϊ����symbolTableûʹ�ù�
    symbolTable = (Identifier **)malloc(sizeof(Identifier *) * BUCKETS);        /*typedef Identifier **SymbolTable;       // ���ű���Ϣ*/
    printf("%d %p\n", __LINE__, symbolTable);
    Identifier* pNode = NULL;

    for(int code = 0; code < BUCKETS; code++)          // ��ʼ��ÿ��ͷ���
    {
        // ָ��ͷ���
        pNode = symbolTable[code];
        pNode = *(symbolTable + code);            // ������

        //printf("%d %p", __LINE__, pNode);
        // ��ʼ��ͷ�����Ϣ
        pNode = (Identifier *)malloc(sizeof(Identifier));       // Ϊͷ��㿪�ٿռ�
        pNode->m_name = NULL;                                      // ͷ�������ƴ�Ϊ�մ�
        pNode->m_offset = 0;                            // ��ǰƫ�Ƶ�ַΪδ֪��
        pNode->m_kind = UNKNOW;                                   // ��ǰ��ʶ��������δ֪
        pNode->m_expand = NULL;                                   // ��ǰ��ʶ������չ��������ΪNULL
        pNode->m_next = NULL;                                     // ��һ��ָ����Ϊ��
        printf("%d %p %d\n", __LINE__, pNode, pNode->m_offset);
    }

    return symbolTable;
}

// ��ʾ���ű�ÿ����ϣ�����������Ϣ
void ShowSymbolList(Identifier *idenList)
{
    //getchar( );
    printf("��%d�������Ϣ\n", idenList->m_offset);

    Identifier *pNode = idenList->m_next;       // ָ���һ�������Ϣ

    while(pNode != NULL)
    {
        printf("{%d, %s}\n", pNode->m_kind, pNode->m_name);
        pNode = pNode->m_next;          // ֻ����һ��ָ��λ��
    }
}


// ��ʾ���ű����Ϣ
void VisitSymbolTable(SymbolTable symbolTable)
{
    for(int code = 0; code < BUCKETS; code++)       // ���ÿ��Ԫ�ص���Ϣ
    {
        printf("\n\nHASHCODECODE -=> %d\n", code);
        ShowSymbolList(symbolTable[code]);                // ���ÿ����ϣ���������Ϣ
        //printf("%s %d %p %p\n", __func__, __LINE__, symbolTable[code], *(symbolTable + code));
    }
}


void ShowSymbolPoint(SymbolTable __attribute__((unused)) symbolTable)
{
    for(int code = 0; code < BUCKETS; code++)       // ���ÿ��Ԫ�ص���Ϣ
    {
        printf("%s %d %p %p\n", __func__, __LINE__, symbolTable[code], *(symbolTable + code));
    }
}
// **p = *a[]
// (*p)[4] = a[][4]

/**
185 00662ae8
202 00662b60 0
202 00662b80 0
202 00662ba0 0
202 00662bc0 0
202 00662be0 0
202 00662c00 0
202 00662c20 0
202 00662c40 0
202 00662c60 0
202 00662c80 0
202 00662ca0 0
202 00662cc0 0
202 00662ce0 0
202 00662d00 0
202 00662d20 0
202 00662d40 0
202 00662d60 0
202 00666aa0 0
202 009ad850 0
202 009ad870 0
202 009ad890 0
202 009ad8b0 0
202 009ad8d0 0
202 009ad8f0 0
202 009ad910 0
202 009ad930 0
202 009ad950 0
**/
