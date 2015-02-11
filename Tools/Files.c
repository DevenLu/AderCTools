/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : Files.c                                                        *
*   Description: CTools                                                         *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/



#include "Files.h"


/// files����ʵ�ֲ���
CToolsFILE CToolsOpen(const char* fileName, const char *openWay)     // ���ļ�
{
    assert(fileName != NULL);       // �ļ�������Ϊ��

    CToolsFILE CToolsFILE_point;      // Դ�����ļ�

    if((CToolsFILE_point = fopen(fileName, openWay)) == NULL)      // ���ļ�
    {
        printf("can't open the source file...[%s]\n", fileName);
        exit(EXIT_FAILURE);
    }

    return CToolsFILE_point;
}


CToolsFILE CToolsFineOpen(const char* fileName, const char *openWay, CToolsFILE fp, ...)     // ���ļ�
{
    #ifdef CTOOLS_DEBUG_DEFINE
    assert(fileName != NULL);       // �ļ�������Ϊ��
    #endif // CTOOLS_DEBUG_DEFINE

    CToolsFILE CToolsFILE_point;      // Դ�����ļ�

    if((CToolsFILE_point = fopen(fileName, openWay)) == NULL)      // ���ļ�
    {
        printf("can't open the source file...[%s]\n", fileName);

        /// �ر��Ѿ��򿪵��ļ�
        if(fp != NULL)              // ֻҪ�����ļ����ǿյ�
        {
            va_list argPtr;

            int argCount = 0; // �ɱ������Ŀ
            CToolsFILE argValue = fp;
            va_start(argPtr, fp);    // �Թ̶������ĵ�ַΪ���ȷ����ε��ڴ���ʼ��ַ

            while(argValue != NULL)
            {
                fclose(argValue);       // �ر��ļ�

                printf("%p\n", argValue);
                argValue = va_arg(argPtr, CToolsFILE);  // ȡ����һ����ַ��������Ϣ
                printf("%p\n", argValue);
                ++argCount;     // ������Ŀ����1
            }
            #ifdef CTOOLS_DEBUG_DEFINE
            printf("�����ر����Ѿ��򿪵�%d�ļ�\n", argCount);
            #endif // CTOOLS_DEBUG_DEFINE

            exit(EXIT_FAILURE);
        }
    }

    return CToolsFILE_point;
}

int	CToolsCloseAll(CToolsFILE fpi,...)          // �ر��ļ�
{

    va_list argPtr;

    int argCount = 0; // �ɱ������Ŀ
    CToolsFILE argValue = fpi;


    va_start(argPtr, fpi);    // �Թ̶������ĵ�ַΪ���ȷ����ε��ڴ���ʼ��ַ
    //va_start(argPtr, argValue);

    while(argValue != NULL)
    {
        fclose(argValue);       // �ر��ļ�

        //printf("%p\n", argValue);
        argValue = va_arg(argPtr, CToolsFILE);  // ȡ����һ����ַ��������Ϣ
        ++argCount;     // ������Ŀ����1
    }

    // ����Ĵ���ȼ�������Ĵ���
    /*do
    {
    //    printf("%p\n", argValue);
        fclose(argValue);       // �ر��ļ�
        argValue = va_arg(argPtr, CToolsFILE);  // ȡ����һ����ַ��������Ϣ
        ++argCount;        // ��������1
    }while(argValue != NULL);*/
    return argCount;
}


void CToolsFree(void *point)
{
    if(point != NULL)
    {
        free(point);
    }
}




