/**************
*
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe
*   File Name  : Parser.h
*   Description: CTools-SyntacicParser
*   Version    : Copyright 2013-2014
*   Data_Time  : 2013-11-5  18:38:23
*   Content    : CTools-Lexical
*
*   This file is the CodeProp...
***************/




#include "Prop.h"

//extern const char keyword[MAX_KEYWORD][20];
//extern const char procom[MAX_PROCOM][10];
//extern const char operate[MAX_OPERATE];
//extern const char allOperator[MAX_OPERATE][4];
//extern const char separator[MAX_SEPARAROR];



// ���ļ�������ض����ļ��е���Ϣ
//void WritePropLineStr(CToolsFILE fp, const char *fileName, int fileLine)
//{
//    fprintf(fp, "#line %d \"%s\"\n", fileLine, fileName);
//}

// ���ļ�������ļ���׮��Ϣ
//void WritePropStr(CToolsFILE fp, const char *streamName)
//{
//    fprintf(fp, "line(%s);", streamName);
//}

// ��Դ�ļ�src��ƫ��start��end������д��dest�ļ���
void PropWriteSrcToDest(CToolsFILE dest, CToolsFILE src, int start, int end)
{
    int ch;
    fseek(src, start, SEEK_SET);            // ���ļ���λ���ļ�ƫ��start��λ��

    //printf("��\"");
    for(int pos = start; pos < end; pos++)
    {
        //if((ch = fgetc(src)) != 0)
        if(fscanf(src, "%c", &ch) == 1)
        {
            if(ch == '\r')
            {
                //printf("\\r");
                continue;
            }
            else if(ch == '\n')
            {
                //pos++;
                //printf("������һ�����з���%d", pos);
                //printf("\\n");
            }
            fprintf(dest, "%c", ch);
            //printf("ƫ��%d%c\n", pos, ch);
            //printf("%c", ch);
        }
    }

    fprintf(src, " ");
    //printf("\"д��dest��׮Ŀ���ļ���\n");
}


// ��Դ�ļ��дӵ�ǰλ�ÿ�ʼ��ĩβ�������ַ�д��Ŀ���ļ���
void PropWriteAllSrcToDest(CToolsFILE destFp, CToolsFILE srcFp)
{
    int ch;

    #ifdef PROP_DEBUG_DEFINE
    printf("����Դ�ļ�ƫ��%d����ʼ���е�����д���ļ�\n", ftell(srcFp));
    //printf("%d", ftell(srcFp), )
    #endif // PROP_DEBUG_DEFINE
    while(feof(srcFp) == 0)
    {
        if(fscanf(srcFp, "%c", &ch) ==  1)
        {

            #ifdef PROP_DEBUG_DEFINE
            printf("��ȡ�������ַ�%c\n", ch);
            #endif // PROP_DEBUG_DEFINE

            fprintf(destFp, "%c", ch);
        }
    }
}


// ��srcFp�ļ�ָ���е�count���ַ�д��destFpָ����ļ���
void PropWriteCountSrcToDest(CToolsFILE destFp, CToolsFILE srcFp, int count)
{
    int ch;
    int num = 0;
    #ifdef PROP_DEBUG_DEFINE
    printf("����Դ�ļ�ƫ��%d����ʼд��%d������\n", ftell(srcFp), count);
    //printf("%d", ftell(srcFp), )
    #endif // PROP_DEBUG_DEFINE

    while(num < count)
    {
        if(fscanf(srcFp, "%c", &ch) ==  1)
        {
            #ifdef PROP_DEBUG_DEFINE
            printf("��ȡ�������ַ�%c\n", ch);
            #endif // PROP_DEBUG_DEFINE

            fprintf(destFp, "%c", ch);
            num++;
        }
        else
        {
            if(feof(srcFp) != 0)
            {
                break;
            }
            //FILE_FUNC_LINE( );
            fprintf(stderr, "��ȡ����ʧ��");
        }
    }
    //FILE_FUNC_LINE( );
}

// ֱ����Դ�ļ�һ�������ս��������Ӳ�׮������
void PropWritePropLineInEnd(CToolsFILE dest, CToolsFILE src, SyntaxTree parentRoot)
{

    long start   =   parentRoot->m_syntax.m_startCoord.m_fileBegOffset;
    long end     =   parentRoot->m_syntax.m_endCoord.m_fileEndOffset;

    PropWriteSrcToDest(dest, src, start, end);          // ������д���ļ���
    WritePropStr(dest, "__propFP__");                     // �����׮��Ϣ
    //printf("��Line(__prop__);��׮��Ϣд���Ŀ���ļ�\n");

}


// �жϵ�ǰ�﷨��������ʾ�ĺ���������Ϣ�ǲ�����main�������
// ʵ��    �����ҵ��﷨�����д��뺯�����Ƶı�ʶ����Ϣ��λ��, �鿴�������ǲ���main
//         ������ʵ��˼·ʵ���ҵ����λ��,
//         һ�ַ�ʽ�Ǳ����﷨����,
//         ��һ�ַ�ʽ�������ҵ��﷨�����ĵ�һ���ս��, ����ս���űض����Ǵʷ����еĵ�һ�����
//         ����Լ�Ĺ����У��﷨�����м����ս���űض���������, ���
//         ���﷨�������ҵ���һ���ս������Ϣ, Ȼ��������ڵ�Ϊ�׽��, ���������ʷ����
//         �ҵ��ʷ������е�һ����ʶ�����ض����Ǻ������Ƶı�ʶ����Ϣ
bool IsMainFunc(SyntaxTree parentRoot)
{
    TupleNode      *headTupleNode = NULL;
    TupleNode      *tupleNode = NULL;

    /// �������ҵ��﷨�����е�һ��Ҷ�ӽ��
    if((headTupleNode = FindFirstChildTupleNode(parentRoot)) != NULL)
    {
        if((tupleNode = FindFirstTupleTreinal(headTupleNode, IDENTIFIER)) != NULL)
        {
            if(strcmp(tupleNode->m_tuple.m_data.m_identifier, "main") == 0)
            {
                return true;
            }
            else
            {
                #ifdef PROP_SHOWS_DEFINE
                printf("��ǰ��������main������\n");
                #endif // PROP_SHOWS_DEFINE

                return false;
            }
        }
        else
        {
            FILE_FUNC_LINE( );
            fprintf(stderr, "�ҵ��ʷ���Ԫ���ĩβ��Ȼδ�ҵ���ʶ��\n");
            return false;
        }
    }
    else
    {
        FILE_FUNC_LINE( );
        fprintf(stderr, "�޷����ҵ��﷨���ĵ�һ���ս�����������\n");

        return false;
    }
}


// �ڽ��в�׮��ʱ��, ������main����֮ǰ������һ���ļ��򿪲�׮������FILE_OPEN_DEFINE_PROP_STR
// ��Ϊ��Ҫ��������������ʱ���ļ��ر�
TupleNode* FindFuncRegPos(SyntaxTree parentRoot)
{
#ifdef PROP_DEBUG_DEFINE
FILE_FUNC_LINE( );
assert(IsMainFunc(parentRoot) == true);
#endif // PROP_DEBUG_DEFINE

    TupleNode   *finalTupleNode = NULL;
    TupleNode   *posTupleNode = NULL;

    // �����ҵ���������ʽ�ӵĽ���λ��
    if((finalTupleNode = FindFinalChildTupleNode(parentRoot)) != NULL)
    {
        // ��������ʽ�Ľ���λ��Ӧ����һ��"}"�ս���ʷ���Ԫ����
        if(finalTupleNode->m_tuple.m_kind == RBRACE_SEPARATOR)
        {
            // ������������ʽ���ҵ���ǰreturn ���͹ؼ��ֵ�λ��
            if((posTupleNode = ReFindFirstTupleTreinal(finalTupleNode, RETURN_KEYWORD)) != NULL)
            {   // �ҵ���return�ؼ���, �򷵻عؼ�λ��, ��Ϊ��Ҫ��return֮ǰ����ļ��ر���������
                return posTupleNode;
            }
            else
            {   // δ�ҵ�retunr�ؼ��� ��ֱ����"}"֮ǰ����������, ����"}"֮ǰ�����ļ��ر�����
                ///////////////////////////////////////////////////////////////////////////////////////
                // ˵��������δ����WARING
                ///////////////////////////////////////////////////////////////////////////////////////
                return finalTupleNode;
            }
        }
        else
        {
            FILE_FUNC_LINE( );
            fprintf(stderr, "�˺�������ʽ�д���, ���һ���ս���Ų���\"}\"");
            return NULL;
        }
    }
}



void PropWriteFileOpenDefineStr(CToolsFILE destFp, const char *srcFname, int srcLine)
{
    fprintf(destFp, "%s", FILE_OPEN_DEFINE_PROP_STR);        // ���ļ�����Ϣ��д���ļ���
    WritePropLineStr(destFp, srcFname, srcLine);        // ���ض����к���Ϣд���ļ���
}





//// ���ʷ���Ԫ�������ӵ�Ŀ���ļ���
//void PropWriteTupleNode(CToolsFILE destfp, TupleNode* pNode)
//{
//    switch((int)pNode->m_tuple.m_kind)          // ���ݵ�ǰ�˷����ı���
//    {
//        case TOKEN_END               :                  // ��ʶ����
//		{
//            printf("[%d, %d]", TOKEN_END, pNode->m_tuple.m_data.m_keyCode);
//			break;
//		}
//		case TOKEN_NULL              :
//		case UNKNOW                  :
//		case ARRAY                   :
//		case FUNCTION                :
//		case PARAMETERS              :
//        case POINT                   :
//		{
//			break;
//		}
//
//		case HEAD                    :
//		{
//		    printf("COUNT = %d", pNode->m_tuple.m_coord.m_fileLine);
//		    printf("COUNT = %d", pNode->m_tuple.m_data.m_keyCode);
//			break;
//		}
//
//		case IDENTIFIER              :                  // ��ʶ����
//		{
//            fprintf(destfp, "%s", pNode->m_tuple.m_data.m_identifier);
//			break;
//		}
//
//		case KEYWORD                 :                  /// �ؼ�����Ϣ
//		case AUTO_KEYWORD            :
//		case BREAK_KEYWORD           :
//		case CASE_KEYWORD            :
//		case CHAR_KEYWORD            :
//		case CONST_KEYWORD           :
//		case CONTINUE_KEYWORD        :
//		case DEFAULT_KEYWORD         :
//		case DO_KEYWORD              :
//		case DOUBLE_KEYWORD          :
//		case ELSE_KEYWORD            :
//		case ENUM_KEYWORD            :
//		case EXTERN_KEYWORD          :
//		case FLOAT_KEYWORD           :
//		case FOR_KEYWORD             :
//		case GOTO_KEYWORD            :
//		case IF_KEYWORD              :
//		case INT_KEYWORD             :
//		case LONG_KEYWORD            :
//		case REGISTER_KEYWORD        :
//		case RETURN_KEYWORD          :
//		case SHORT_KEYWORD           :
//		case SIGNED_KEYWORD          :
//		case SIZEOF_OPERATE          :
//		case STATIC_KEYWORD          :
//		case STRUCT_KEYWORD          :
//		case SWITCH_KEYWORD          :
//		case TYPEDEF_KEYWORD         :
//		case UNION_KEYWORD           :
//		case UNSIGNED_KEYWORD        :
//		case VOID_KEYWORD            :
//		case VOLATILE_KEYWORD        :
//		case WHILE_KEYWORD           :
//        {
//            fprintf(destfp, "%s", keyword[pNode->m_tuple.m_kind - pNode->m_tuple.m_data.m_keyCode]);
//            break;
//        }
//
//		case OPERATE                 :                  /// �������
//		case COMMA_OPERATE           :                  // ,
//		case ASSIGN_OPERATE          :                  // =
//		case ADD_ASSIGN_OPERATE      :                  // +=
//		case SUB_ASSIGN_OPERATE      :                  // -=
//		case MUL_ASSIGN_OPERATE      :                  // *=
//		case DIV_ASSIGN_OPERATE      :                  // /=
//		case MOD_ASSIGN_OPERATE      :                  // %=
//		case BITOR_ASSIGN_OPERATE    :                  // |=
//		case BITXOR_ASSIGN_OPERATE   :                  // ^=
//		case BITAND_ASSIGN_OPERATE   :                  // &=
//		case RSHIFT_ASSIGN_OPERATE   :                  // >>=
//		case LSHIFT_ASSIGN_OPERATE   :                  // <<=
//		case QUESTION_OPERATE        :                  // ?
//		case COLON_OPERATE           :                  // :
//		case OR_OPERATE              :                  // ||
//		case AND_OPERATE             :                  // &&
//		case BITOR_OPERATE           :                  // |
//		case BITXOR_OPERATE          :                  // ^
//		case BITAND_OPERATE          :                  // &
//		case EQUAL_OPERATE           :                  // ==
//		case UNEQUAL_OPERATE         :                  // !=
//		case GREATER_OPERATE         :                  // >
//		case GREATER_EQUAL_OPERATE   :                  // >=
//		case LESS_OPERATE            :                  // <
//		case LESS_EQUAL_OPERATE      :                  // <=
//		case RSHIFT_OPERATE          :                  // >>
//		case LSHIFT_OPERATE          :                  // <<
//		case ADD_OPERATE             :                  // +
//		case SUB_OPERATE             :                  // -
//		case MUL_OPERATE             :                  // *
//		case DIV_OPERATE             :                  // /
//		case MOD_OPERATE             :                  // %
//		case NOT_OPERATE             :                  // !
//		case COMP_OPERATE            :                  // ~
//		case INC_OPERATE             :                  // ++
//		case DEC_OPERATE             :                  // --
//		//case RPAREN_OPERATE          :                  // )
//		//case LPAREN_OPERATE          :                  // (
//        //case RBRACKET_OPERATE        :                  // ]
//		//case LBRACKET_OPERATE        :                  // [
//		case DOT_OPERATE             :                  // .
//        case POINT_TO_OPERATE        :                  // ->
//		case ELLIPSE_OPERATE         :                  // ...
//		{
//            fprintf("%s", allOperator[pNode->m_tuple.m_kind - pNode->m_tuple.m_data.m_keyCode]);
//			break;
//		}
//
//		case SEPARATOR               :
//        case SPACE_SEPARATOR         :
//		case LBRACE_SEPARATOR        :
//		case RBRACE_SEPARATOR        :
//		case SEMICOLON_SEPARATOR     :
//		case POUND_SEPARATOR         :
//        case SINGLE_QUOTE_SEPARATOR  :
//        case DOUBLE_QUOTE_SEPARATOR  :
//		case NEWLINE_SEPARATOR       :
//		//case ELLIPSE_SEPARATOR       :
//        case RPAREN_OPERATE          :                  // )
//		case LPAREN_OPERATE          :                  // (
//        case RBRACKET_OPERATE        :                  // ]
//		case LBRACKET_OPERATE        :                  // [
//		{
//            fprintf("[%d, %d]", separator[pNode->m_tuple.m_kind - pNode->m_tuple.m_data.m_keyCode]);
//            break;
//		}
//
//		case CONST                   :
//		case INT_CONST               :
//		case UINT_CONST              :
//		case LONG_CONST              :
//		case ULONG_CONST             :
//		case LLONG_CONST             :
//		case ULLONG_CONST            :
//		case FLOAT_CONST             :
//		case DOUBLE_CONST            :
//		case LDOUBLE_CONST           :
//		case CHAR_CONST              :
//		case WCHAR_CONST             :
//		case STRING_CONST            :
//        {
//            fprintf(destfp, "%s", pNode->m_tuple.m_data.m_constNum);
//            break;
//        }
//		case ENUM_CONST              :
//		{
//			break;
//		}
//    }
//}



// ��Դ�ļ�srcFname���в�׮�� ��׮�������destFname
void PropFile(const char *destFname, const char *srcFname)
{
    ParseFilePropRed(destFname, srcFname);
}



int MainOfProp(int argc, char **argv)
{
    // ����ȷ��ִ���˲�׮����
    //#ifndef PROP_REDUCTION_DEFINE
    //#error "ErrorPROP: can't find PROP_REDUCTION_DEFINE in elf...\n"
    //#endif // PROP_REDUCTION_DEFINE

    const char propDestFname[FILE_NAME_SIZE];
    const char propSrcFname[FILE_NAME_SIZE];


    // ȷ����������ļ�
    if(argc < 2)
    {
        printf("Please input the file name of the SOURCE FILE:\n");
        scanf("%s", propSrcFname);
        printf("Please input the file name of the DEST FILE:\n");
        scanf("%s", propDestFname);
    }
    else if(argc > 3)
    {
        printf("ErrorPROP: too many file...\n");
        exit(-1);
    }

    // ��ȡ��������ļ�
    strcpy(propSrcFname, argv[1]);           // ȡ�������ļ�
    if(argc == 2)
    {
        strcpy(propDestFname, PROP_FILE_NAME);
    }
    else if(argc == 3)
    {
        strcpy(propDestFname, argv[2]);
    }

    // �﷨������ͬʱ��Դ�ļ����в�׮����...
    PropFile(propDestFname, propSrcFname);

    return EXIT_SUCCESS;
}

//
//#ifdef PROP_REDUCTION_DEFINE
//// ��׮����������PROP_main
//int main(int argc, char **argv)
//{
//    // ����ȷ��ִ���˲�׮����
//    #ifndef PROP_REDUCTION_DEFINE
//    // printf("ErrorPROP: can't find PROP_REDUCTION_DEFINE in %s(elf)\n", argv[0]);
//    // exit(-1);
//    #error "ErrorPROP: can't find PROP_REDUCTION_DEFINE in elf...\n"
//    #endif // PROP_REDUCTION_DEFINE
//
//    const char *propDestFname = NULL;
//    const char *propSrcFname = NULL;
//
//
//
//    // ȷ����������ļ�
//    if(argc < 2)
//    {
//        printf("ErroePROP: no input file... \n");
//        exit(-2);
//    }
//    else if(argc > 3)
//    {
//        printf("ErrorPROP: too many file...\n");
//    }
//
//    // ��ȡ��������ļ�
//    propSrcFname = argv[1];           // ȡ�������ļ�
//    if(argc == 2)
//    {
//        propDestFname = PROP_FILE_NAME;
//    }
//    else if(argc == 3)
//    {
//        propDestFname = argv[2];
//    }
//
//    // �﷨������ͬʱ��Դ�ļ����в�׮����...
//    PropFile(propDestFname, propSrcFname);
//
//    return EXIT_SUCCESS;
//}
//#endif
