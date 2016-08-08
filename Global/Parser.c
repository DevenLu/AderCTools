/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : Parser.c                                                         *
*   Description: CTools                                                         *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/





#include "CTools.h"    //  #include "..\Global\CTools.h"




int main(int argc, char **argv/*char *argv[]*/)
{
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

    #if defined(SYS_WINDOWS_DEF)
    system("title �﷨������");
    system("color 00");
    #endif      // SYS_WINDOWS_DEF



    SyntaxTree     syntaxRoot;
    printf("**********************************************************\n");
    printf("**  The file you want to syntax is \"%10s\"  **\n", sourceFile);
    printf("**********************************************************\n");


    douTuple = BufferLexical(sourceFile);      // ֱ�Ӵ���Դ�ļ�


    #ifdef PARSER_SHOWS_DEFINE
    VisitTuple(douTuple);            // ������Ԫ����Ϣ, ���Ҷ�Ԫ����ȷ��
    #endif // PARSER_SHOWS_DEFINE

    syntaxRoot = ParseTuple(douTuple);

    if(syntaxRoot != NULL)
    {
        printf("Syntax Tree Height      : %d\n", GetSyntaxTreeHeight(syntaxRoot));
        printf("Syntax Tree Node Count  : %d\n", GetSyntaxTreeNodeCount(syntaxRoot));


        //printf("������ʾ�﷨��\n");
        //ShowSyntaxTree(syntaxRoot);

        printf("Pre-Order Syntax Tree\n");
        PreOrderSytaxTree(syntaxRoot);
        //PAUSE( );
        /*
        printf("In-Order Syntax Tree\n");
        InOrderSyntaxTree(syntaxRoot);
        PAUSE( );

        printf("Post-Order Syntax Tree\n");
        PostOrderSyntaxTree(syntaxRoot);
        PAUSE( );
        */
    }
    DestroyTuple(douTuple);                // ��ն�Ԫ��ռ�Ϊϵͳ��ʡ�ڴ�ռ�

    VERSION( );


    return syntaxRoot;                  // �Դʷ���Ԫ������﷨����
}


