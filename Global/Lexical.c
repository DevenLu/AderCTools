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





#include "CTools.h"    //  #include "..\Global\CTools.h"



/*
*
*   BUG:    ��Լ֮��Ӧ�ý�����ʽ������Ϣ��ջ, �����ٴι�Լʱ��������
*   BUG:    ������Ϣ�������������, ��Ҫ�����ݽ����жϽ���ͬ���͵ĳ������зֱ���
*   D:\SoftwareEngineer\[A]AderStep\AderCTools[0.5.3]\Prop\Prop.c
*
*/



int main(int argc, char **argv/*char *argv[]*/)
{
    //MainOfLexical( );
    char sourceFile[FILE_NAME_SIZE];        // Դ�ļ���
    BinaryTuple douTuple = NULL;               // ��Ԫ����Ϣ

    if(argc > 2)
    {
        printf("usage : %s [ source.c] \n", argv[1]);
    }
    else if(argc == 2)
    {
        strcpy(sourceFile, argv[1]);
    }
    else/* if(argc == 1)*/
    {
        printf("please input the fiel you want to lexical : ");
        scanf("%s", sourceFile);
    }

    #ifdef SYS_WINDOWS_DEF
    system("title �ʷ�������");
    system("color 00");
    #endif      // SYS_WINDOWS_DEF



    douTuple = BufferLexical(sourceFile);      // ֱ�Ӵ���Դ�ļ�
    VisitTuple(douTuple);                    // ������Ԫ����Ϣ, ���Ҷ�Ԫ����ȷ��


    return EXIT_SUCCESS;
}

