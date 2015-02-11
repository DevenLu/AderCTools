#include "PropRed.h"




// �洢ÿ������ʽ��Լ��������ָ�������
void (*PropRedFuncPointArray[233])(PropTable, SyntaxTree) =
{
   PropReduction0,     PropReduction1,     PropReduction2,     PropReduction3,     PropReduction4,
   PropReduction5,     PropReduction6,     PropReduction7,     PropReduction8,     PropReduction9,
  PropReduction10,    PropReduction11,    PropReduction12,    PropReduction13,    PropReduction14,
  PropReduction15,    PropReduction16,    PropReduction17,    PropReduction18,    PropReduction19,
  PropReduction20,    PropReduction21,    PropReduction22,    PropReduction23,    PropReduction24,
  PropReduction25,    PropReduction26,    PropReduction27,    PropReduction28,    PropReduction29,
  PropReduction30,    PropReduction31,    PropReduction32,    PropReduction33,    PropReduction34,
  PropReduction35,    PropReduction36,    PropReduction37,    PropReduction38,    PropReduction39,
  PropReduction40,    PropReduction41,    PropReduction42,    PropReduction43,    PropReduction44,
  PropReduction45,    PropReduction46,    PropReduction47,    PropReduction48,    PropReduction49,
  PropReduction50,    PropReduction51,    PropReduction52,    PropReduction53,    PropReduction54,
  PropReduction55,    PropReduction56,    PropReduction57,    PropReduction58,    PropReduction59,
  PropReduction60,    PropReduction61,    PropReduction62,    PropReduction63,    PropReduction64,
  PropReduction65,    PropReduction66,    PropReduction67,    PropReduction68,    PropReduction69,
  PropReduction70,    PropReduction71,    PropReduction72,    PropReduction73,    PropReduction74,
  PropReduction75,    PropReduction76,    PropReduction77,    PropReduction78,    PropReduction79,
  PropReduction80,    PropReduction81,    PropReduction82,    PropReduction83,    PropReduction84,
  PropReduction85,    PropReduction86,    PropReduction87,    PropReduction88,    PropReduction89,
  PropReduction90,    PropReduction91,    PropReduction92,    PropReduction93,    PropReduction94,
  PropReduction95,    PropReduction96,    PropReduction97,    PropReduction98,    PropReduction99,
 PropReduction100,   PropReduction101,   PropReduction102,   PropReduction103,   PropReduction104,
 PropReduction105,   PropReduction106,   PropReduction107,   PropReduction108,   PropReduction109,
 PropReduction110,   PropReduction111,   PropReduction112,   PropReduction113,   PropReduction114,
 PropReduction115,   PropReduction116,   PropReduction117,   PropReduction118,   PropReduction119,
 PropReduction120,   PropReduction121,   PropReduction122,   PropReduction123,   PropReduction124,
 PropReduction125,   PropReduction126,   PropReduction127,   PropReduction128,   PropReduction129,
 PropReduction130,   PropReduction131,   PropReduction132,   PropReduction133,   PropReduction134,
 PropReduction135,   PropReduction136,   PropReduction137,   PropReduction138,   PropReduction139,
 PropReduction140,   PropReduction141,   PropReduction142,   PropReduction143,   PropReduction144,
 PropReduction145,   PropReduction146,   PropReduction147,   PropReduction148,   PropReduction149,
 PropReduction150,   PropReduction151,   PropReduction152,   PropReduction153,   PropReduction154,
 PropReduction155,   PropReduction156,   PropReduction157,   PropReduction158,   PropReduction159,
 PropReduction160,   PropReduction161,   PropReduction162,   PropReduction163,   PropReduction164,
 PropReduction165,   PropReduction166,   PropReduction167,   PropReduction168,   PropReduction169,
 PropReduction170,   PropReduction171,   PropReduction172,   PropReduction173,   PropReduction174,
 PropReduction175,   PropReduction176,   PropReduction177,   PropReduction178,   PropReduction179,
 PropReduction180,   PropReduction181,   PropReduction182,   PropReduction183,   PropReduction184,
 PropReduction185,   PropReduction186,   PropReduction187,   PropReduction188,   PropReduction189,
 PropReduction190,   PropReduction191,   PropReduction192,   PropReduction193,   PropReduction194,
 PropReduction195,   PropReduction196,   PropReduction197,   PropReduction198,   PropReduction199,
 PropReduction200,   PropReduction201,   PropReduction202,   PropReduction203,   PropReduction204,
 PropReduction205,   PropReduction206,   PropReduction207,   PropReduction208,   PropReduction209,
 PropReduction210,   PropReduction211,   PropReduction212,   PropReduction213,   PropReduction214,
 PropReduction215,   PropReduction216,   PropReduction217,   PropReduction218,   PropReduction219,
 PropReduction220,   PropReduction221,   PropReduction222,   PropReduction223,   PropReduction224,
 PropReduction225,   PropReduction226,   PropReduction227,   PropReduction228,   PropReduction229,
 PropReduction230,   PropReduction231,   PropReduction232,
};


// ��ʼ����׮��Ϣ
void InitProp(CToolsFILE destFp, const char *srcFname)
{
    // ����������ļ�, ������ļ�����Ӳ�׮Ԥ����ͷ
    //CToolsFILE  destFp = CToolsOpen(destFname, "w");     // ������ļ�
    //CToolsFILE  srcFp = CToolsOpen(srcFname, "r");
    #ifdef PROP_DEBUG_DEFINE
    printf("%s\n", START_DEFINE_PROP_STR);
    PAUSE( );
    #endif // PROP_DEBUG_DEFINE

    fprintf(destFp, "%s\n", START_DEFINE_PROP_STR);
    //fprintf(destFp, "%s\n", INCLUDE_DEFINE_PROP_STR);          // ����ʼ����Ϣ������ļ���
    //fprintf(destFp, "%s\n", LINE_DEFINE_PROP_STR);             // ���в�׮��Ķ�����Ϣ��������ļ���
    //fprintf(destFp, "%s\n", GLOBAL_FILE_POINT_PROP_STR);             // ���в�׮��Ķ�����Ϣ��������ļ���

    WritePropLineStr(destFp, srcFname, 1);              // �����кų�ʼ������
    //WritePropStr(fp, "fp");

}

////
//PropTableNode* FinitProp(const char *destFname, const char *srcFname)
//{
//    fclose( );
//}

// ���﷨����parentRoot���յ�id������ʽ����ʽ���в�׮
void PropRed(PropTable propTable, SyntaxTree parentRoot, int id)
{
    // FILE_FUNC_LINE( );
    (*PropRedFuncPointArray[id])(propTable, parentRoot);

}


// ���յ�0������ʽ��Լʱ�Ĳ�׮����
void PropReduction0(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE

}



// ���յ�1������ʽ��Լʱ�Ĳ�׮����
void PropReduction1(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE


}



// ���յ�2������ʽ��Լʱ�Ĳ�׮����
void PropReduction2(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE

}



// ���յ�3������ʽ��Լʱ�Ĳ�׮����
void PropReduction3(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE

}



// ���յ�4������ʽ��Լʱ�Ĳ�׮����
void PropReduction4(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE

}



// ���յ�5������ʽ��Լʱ�Ĳ�׮����
void PropReduction5(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE

}



// ���յ�6������ʽ��Լʱ�Ĳ�׮����
void PropReduction6(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE

}



// ���յ�7������ʽ��Լʱ�Ĳ�׮����
// function-definition -=> declaration-specfiers declarator declaration compound-statement
// ��������ʽ
// eg
// int main( )
// {
//
// }
// int main( )
// {
//
// }
// ִ�ж���, �����жϵ�ǰ���������ǲ���main,
// ˼·   ���������ں��������ں�����ʼ��λ��, ��Ӳ�׮�ļ�����Ϣ�꣬������ִ����������
//       ��Ӳ�׮
void PropReduction7(PropTable propTable, SyntaxTree parentRoot)
{
#ifdef PROP_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // PROP_DEBUG_DEFINE

    if(IsMainFunc(parentRoot) == true)          // �����ǰ��������ʽ����main����
    {                                       // ��Ҫ��"{"�����λ�ò����׮�ļ����������Ŵ���
        #ifdef PROP_SHOWS_DEFINE
        printf("��ǰ������main����ں���\n");
        #endif // PROP_SHOWS_DEFINE


        // �����ҵ�"{"��λ��
        TupleNode   *tupleNode = NULL;
        if((tupleNode = FindFirstSyntaxTreeTreinal(parentRoot, LBRACE_SEPARATOR)) != NULL)
        {   // ��"{"�ĺ������һ����׮�ļ�������������

            #ifdef PROP_SHOWS_DEFINE
            printf("��main����{�ĺ�������׮�ļ���������\n");
            #endif // PROP_SHOWS_DEFINE

            int offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
            int line = tupleNode->m_tuple.m_coord.m_fileLine;
            // ����ļ�����������׮��Ϣ��,  ���¶�λ�к�
            //InsertPropDataWithLine(propTable, offset, FILE_OPEN_DEFINE_PROP_KIND, line + 1);
            InsertPropData(propTable, offset, FILE_OPEN_DEFINE_PROP_KIND);

            // ������������֮ǰ�����ļ��ر�������
            tupleNode = NULL;
            if((tupleNode = FindFuncRegPos(parentRoot)) != NULL)
            {
                #ifdef PROP_DEBUG_DEFINE
                ShowTupleData(tupleNode);
                PAUSE( );
                #endif // PROP_DEBUG_DEFINE

                offset = tupleNode->m_tuple.m_coord.m_fileBegOffset;
                //line = tupleNode->m_tuple.m_coord.m_fileLine;
                InsertPropData(propTable, offset, FILE_CLOSE_DEFINE_PROP_KIND);
            }
        }
        else
        {
            FILE_FUNC_LINE( );
            fprintf(stderr, "δ�ں�������ʽ���ҵ�\"{\"��λ��\n");
            PAUSE( );
        }
    }

}



// ���յ�8������ʽ��Լʱ�Ĳ�׮����
void PropReduction8(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE

}



// ���յ�9������ʽ��Լʱ�Ĳ�׮����
void PropReduction9(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE

}



// ���յ�10������ʽ��Լʱ�Ĳ�׮����
// declaration -=> declaration-specifiers init-declaration-list ;
// ��������ʽ��ʱ���������в�׮�� ����Ǻ�������ȫ�ֱ������壬 ��׮����޷�ִ��
void PropReduction10(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PROP_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PROP_DEBUG_DEFINE
    //PropWritePropLineInEnd(dest, src, parentRoot);
    //
    // ����int a = 10;
    // ��׮int a = 10;Line(__prop__);
    //
    // ��ĩβ���һ�������Ĳ�׮���
//    int offset = parentRoot->m_syntax.m_endCoord.m_fileEndOffset;
//
//    InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
}




// ���յ�11������ʽ��Լʱ�Ĳ�׮����
void PropReduction11(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�12������ʽ��Լʱ�Ĳ�׮����
void PropReduction12(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�13������ʽ��Լʱ�Ĳ�׮����
void PropReduction13(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�14������ʽ��Լʱ�Ĳ�׮����
void PropReduction14(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�15������ʽ��Լʱ�Ĳ�׮����
void PropReduction15(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�16������ʽ��Լʱ�Ĳ�׮����
void PropReduction16(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�17������ʽ��Լʱ�Ĳ�׮����
void PropReduction17(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�18������ʽ��Լʱ�Ĳ�׮����
void PropReduction18(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�19������ʽ��Լʱ�Ĳ�׮����
void PropReduction19(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�20������ʽ��Լʱ�Ĳ�׮����
void PropReduction20(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�21������ʽ��Լʱ�Ĳ�׮����
void PropReduction21(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�22������ʽ��Լʱ�Ĳ�׮����
void PropReduction22(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�23������ʽ��Լʱ�Ĳ�׮����
void PropReduction23(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�24������ʽ��Լʱ�Ĳ�׮����
void PropReduction24(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�25������ʽ��Լʱ�Ĳ�׮����
void PropReduction25(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�26������ʽ��Լʱ�Ĳ�׮����
void PropReduction26(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�27������ʽ��Լʱ�Ĳ�׮����
void PropReduction27(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�28������ʽ��Լʱ�Ĳ�׮����
void PropReduction28(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�29������ʽ��Լʱ�Ĳ�׮����
void PropReduction29(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�30������ʽ��Լʱ�Ĳ�׮����
void PropReduction30(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�31������ʽ��Լʱ�Ĳ�׮����
void PropReduction31(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�32������ʽ��Լʱ�Ĳ�׮����
void PropReduction32(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�33������ʽ��Լʱ�Ĳ�׮����
void PropReduction33(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�34������ʽ��Լʱ�Ĳ�׮����
void PropReduction34(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�35������ʽ��Լʱ�Ĳ�׮����
void PropReduction35(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�36������ʽ��Լʱ�Ĳ�׮����
void PropReduction36(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�37������ʽ��Լʱ�Ĳ�׮����
void PropReduction37(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�38������ʽ��Լʱ�Ĳ�׮����
void PropReduction38(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�39������ʽ��Լʱ�Ĳ�׮����
void PropReduction39(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�40������ʽ��Լʱ�Ĳ�׮����
void PropReduction40(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�41������ʽ��Լʱ�Ĳ�׮����
void PropReduction41(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�42������ʽ��Լʱ�Ĳ�׮����
void PropReduction42(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�43������ʽ��Լʱ�Ĳ�׮����
void PropReduction43(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�44������ʽ��Լʱ�Ĳ�׮����
void PropReduction44(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�45������ʽ��Լʱ�Ĳ�׮����
void PropReduction45(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�46������ʽ��Լʱ�Ĳ�׮����
void PropReduction46(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�47������ʽ��Լʱ�Ĳ�׮����
void PropReduction47(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�48������ʽ��Լʱ�Ĳ�׮����
void PropReduction48(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�49������ʽ��Լʱ�Ĳ�׮����
void PropReduction49(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�50������ʽ��Լʱ�Ĳ�׮����
void PropReduction50(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�51������ʽ��Լʱ�Ĳ�׮����
void PropReduction51(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�52������ʽ��Լʱ�Ĳ�׮����
void PropReduction52(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�53������ʽ��Լʱ�Ĳ�׮����
void PropReduction53(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�54������ʽ��Լʱ�Ĳ�׮����
void PropReduction54(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�55������ʽ��Լʱ�Ĳ�׮����
void PropReduction55(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�56������ʽ��Լʱ�Ĳ�׮����
void PropReduction56(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�57������ʽ��Լʱ�Ĳ�׮����
void PropReduction57(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�58������ʽ��Լʱ�Ĳ�׮����
void PropReduction58(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�59������ʽ��Լʱ�Ĳ�׮����
void PropReduction59(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�60������ʽ��Լʱ�Ĳ�׮����
void PropReduction60(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�61������ʽ��Լʱ�Ĳ�׮����
void PropReduction61(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�62������ʽ��Լʱ�Ĳ�׮����
void PropReduction62(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�63������ʽ��Լʱ�Ĳ�׮����
void PropReduction63(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�64������ʽ��Լʱ�Ĳ�׮����
void PropReduction64(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�65������ʽ��Լʱ�Ĳ�׮����
void PropReduction65(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�66������ʽ��Լʱ�Ĳ�׮����
void PropReduction66(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�67������ʽ��Լʱ�Ĳ�׮����
void PropReduction67(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�68������ʽ��Լʱ�Ĳ�׮����
void PropReduction68(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�69������ʽ��Լʱ�Ĳ�׮����
void PropReduction69(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�70������ʽ��Լʱ�Ĳ�׮����
void PropReduction70(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�71������ʽ��Լʱ�Ĳ�׮����
void PropReduction71(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�72������ʽ��Լʱ�Ĳ�׮����
void PropReduction72(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�73������ʽ��Լʱ�Ĳ�׮����
void PropReduction73(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�74������ʽ��Լʱ�Ĳ�׮����
void PropReduction74(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�75������ʽ��Լʱ�Ĳ�׮����
void PropReduction75(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�76������ʽ��Լʱ�Ĳ�׮����
void PropReduction76(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�77������ʽ��Լʱ�Ĳ�׮����
void PropReduction77(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�78������ʽ��Լʱ�Ĳ�׮����
void PropReduction78(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�79������ʽ��Լʱ�Ĳ�׮����
void PropReduction79(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�80������ʽ��Լʱ�Ĳ�׮����
void PropReduction80(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�81������ʽ��Լʱ�Ĳ�׮����
void PropReduction81(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�82������ʽ��Լʱ�Ĳ�׮����
void PropReduction82(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�83������ʽ��Լʱ�Ĳ�׮����
void PropReduction83(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�84������ʽ��Լʱ�Ĳ�׮����
void PropReduction84(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�85������ʽ��Լʱ�Ĳ�׮����
void PropReduction85(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�86������ʽ��Լʱ�Ĳ�׮����
void PropReduction86(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�87������ʽ��Լʱ�Ĳ�׮����
void PropReduction87(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�88������ʽ��Լʱ�Ĳ�׮����
void PropReduction88(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�89������ʽ��Լʱ�Ĳ�׮����
void PropReduction89(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�90������ʽ��Լʱ�Ĳ�׮����
void PropReduction90(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�91������ʽ��Լʱ�Ĳ�׮����
void PropReduction91(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�92������ʽ��Լʱ�Ĳ�׮����
void PropReduction92(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�93������ʽ��Լʱ�Ĳ�׮����
void PropReduction93(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�94������ʽ��Լʱ�Ĳ�׮����
void PropReduction94(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�95������ʽ��Լʱ�Ĳ�׮����
void PropReduction95(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�96������ʽ��Լʱ�Ĳ�׮����
void PropReduction96(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�97������ʽ��Լʱ�Ĳ�׮����
void PropReduction97(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�98������ʽ��Լʱ�Ĳ�׮����
void PropReduction98(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�99������ʽ��Լʱ�Ĳ�׮����
void PropReduction99(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�100������ʽ��Լʱ�Ĳ�׮����
void PropReduction100(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�101������ʽ��Լʱ�Ĳ�׮����
void PropReduction101(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�102������ʽ��Լʱ�Ĳ�׮����
void PropReduction102(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�103������ʽ��Լʱ�Ĳ�׮����
void PropReduction103(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�104������ʽ��Լʱ�Ĳ�׮����
void PropReduction104(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�105������ʽ��Լʱ�Ĳ�׮����
void PropReduction105(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�106������ʽ��Լʱ�Ĳ�׮����
void PropReduction106(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�107������ʽ��Լʱ�Ĳ�׮����
// statement -=> labeledstatement
void PropReduction107(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�108������ʽ��Լʱ�Ĳ�׮����
// statement -=> expression-statement
void PropReduction108(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�109������ʽ��Լʱ�Ĳ�׮����
// statement -=> compound-statement
void PropReduction109(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�110������ʽ��Լʱ�Ĳ�׮����
// statement -=> seletion-statement
void PropReduction110(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�111������ʽ��Լʱ�Ĳ�׮����
// statement -=> iteration-statement
void PropReduction111(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�112������ʽ��Լʱ�Ĳ�׮����
// statement -=> jump-statement
void PropReduction112(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�113������ʽ��Լʱ�Ĳ�׮����
// labeled-statement -=> idenfitier : statement
void PropReduction113(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�114������ʽ��Լʱ�Ĳ�׮����
// label-statement -=> case constant-expression : statement
void PropReduction114(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�115������ʽ��Լʱ�Ĳ�׮����
// labeled-atatement -=> defautt : statement;
void PropReduction115(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}




// ���յ�116������ʽ��Լʱ�Ĳ�׮����
void PropReduction116(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�117������ʽ��Լʱ�Ĳ�׮����
void PropReduction117(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�118������ʽ��Լʱ�Ĳ�׮����
void PropReduction118(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�119������ʽ��Լʱ�Ĳ�׮����
void PropReduction119(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�120������ʽ��Լʱ�Ĳ�׮����
void PropReduction120(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�121������ʽ��Լʱ�Ĳ�׮����
void PropReduction121(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�122������ʽ��Լʱ�Ĳ�׮����
void PropReduction122(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�123������ʽ��Լʱ�Ĳ�׮����
void PropReduction123(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�124������ʽ��Լʱ�Ĳ�׮����
void PropReduction124(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�125������ʽ��Լʱ�Ĳ�׮����
void PropReduction125(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�126������ʽ��Լʱ�Ĳ�׮����
void PropReduction126(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}

// ���յ�127������ʽ��Լʱ�Ĳ�׮����
// expression-statement -=> ;
void PropReduction127(PropTable propTable, SyntaxTree parentRoot)
{
#ifdef PARSER_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // PARSER_DEBUG_DEFINE
    TupleNode       *tupleNode = NULL;
    int         offset = -1;

    // �������﷨�������ҵ����һ���ս��
    if((tupleNode = FindFirstChildTupleNode(parentRoot)) != NULL)
    {
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
    }
}



// ���յ�128������ʽ��Լʱ�Ĳ�׮����
// expression-statement -=> expression ;
void PropReduction128(PropTable propTable, SyntaxTree parentRoot)
{
#ifdef PARSER_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // PARSER_DEBUG_DEFINE
   //  TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode = NULL;
    int         offset = -1;

    // �������﷨�������ҵ����һ���ս��
    if((tupleNode = FindFirstChildTupleNode(parentRoot)) != NULL)
    {
        offset = tupleNode->m_tuple.m_coord.m_fileBegOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }
    /*
    if((tupleNode = FindFinalChildTupleNode(parentRoot)) != NULL)
    {
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
    }*/
}




// ���յ�129������ʽ��Լʱ�Ĳ�׮����
void PropReduction129(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�130������ʽ��Լʱ�Ĳ�׮����
void PropReduction130(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�131������ʽ��Լʱ�Ĳ�׮����
void PropReduction131(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�132������ʽ��Լʱ�Ĳ�׮����
void PropReduction132(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�133������ʽ��Լʱ�Ĳ�׮����
void PropReduction133(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�134������ʽ��Լʱ�Ĳ�׮����
void PropReduction134(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�135������ʽ��Լʱ�Ĳ�׮����
// selection-statement -=> if( expression ) statement
// EG   if(left == right) printf("124");
// AS   if(LINE(stream), left == right) printf("124");
void PropReduction135(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode = NULL;
    int         offset = -1;

    // ���Ȳ��ҵ��﷨���е�һ���ʷ��ڵ��ս����Ϣ
    if((headTupleNode = FindFirstChildTupleNode(parentRoot)) != NULL)
    {
        // ���ҵ���һ��"("��λ��
        if((tupleNode = FindFirstTupleTreinal(headTupleNode, LPAREN_OPERATE)) != NULL)
        {
            // ��"("��λ�������һ����","�ŵĲ�׮��Ϣ��
            offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
            InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
        }
        else
        {
            FILE_FUNC_LINE( );
            fprintf(stderr, "��IF���ṹ���Ҳ���\"(\"���ŵ�λ��\n");
        }
    }
    else
    {
        FILE_FUNC_LINE( );
        fprintf(stderr, "��ǰIF����﷨�������Ҳ����ս�����\n");
    }


}



// ���յ�136������ʽ��Լʱ�Ĳ�׮����
// selection-statement -=> if( expression ) statement else statement
// if(left == right) printf("125YES"); else printf("125NO");
void PropReduction136(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode = NULL;
    PropTableNode   *newPropNode = NULL;
    int         offset = -1;

    // ���Ȳ��ҵ��﷨���е�һ���ʷ��ڵ��ս����Ϣ
    if((headTupleNode = FindFirstChildTupleNode(parentRoot)) != NULL)
    {
        // ���ҵ���һ��"("��λ��
        if((tupleNode = FindFirstTupleTreinal(headTupleNode, LPAREN_OPERATE)) != NULL)
        {
            // ��"("��λ�������һ����","�ŵĲ�׮��Ϣ��
            offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
            InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
        }
    }


}



// ���յ�137������ʽ��Լʱ�Ĳ�׮����
// selection-statement -=> switch( expression ) statement
// switch(choice)
void PropReduction137(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode = NULL;
    PropTableNode   *newPropNode = NULL;
    int         offset = -1;

    // ���Ȳ��ҵ��﷨���е�һ���ʷ��ڵ��ս����Ϣ
    if((headTupleNode = FindFirstChildTupleNode(parentRoot)) != NULL)
    {
        // ���ҵ���һ��"("��λ��
        if((tupleNode = FindFirstTupleTreinal(headTupleNode, LPAREN_OPERATE)) != NULL)
        {
            // ��"("��λ�������һ����","�ŵĲ�׮��Ϣ��
            offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
            InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
        }
    }


}



// ���յ�138������ʽ��Լʱ�Ĳ�׮����
// iteration-statement -=> while( expression ) statement ;
// EG while(i < 10) i++;
// AS while(LINE(stream), i < 10) i++;
void PropReduction138(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

    TupleNode     *tupleNode = NULL;

    // �ҵ�"("LPAREN_OPERATE�ؼ��ֵ�λ��
    if((tupleNode = FindFirstSyntaxTreeTreinal(parentRoot, LPAREN_OPERATE)) != NULL)
    {
        // ��(������ĺ����������LINE(stream),
        long offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }


}



// ���յ�139������ʽ��Լʱ�Ĳ�׮����
// iteration-statement -=> do statement while ( expression ) ;
// EG do i++ while(i < 10);
// AS do i++ while(LINE(STREAM), i < 10);
void PropReduction139(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

    TupleNode     *tupleNode = NULL;
    TupleNode     *terinalNode = NULL;
    // �ҵ�"("LPAREN_OPERATE�ؼ��ֵ�λ��
    // ���ǲ���ֱ����FindFirstSyntaxTreeTreinal(parentRoot, LPAREN_OPERATE)
    // ��Ϊѭ����statement�п��ܴ���"("�������
    // �����ȷ�ķ���Ӧ����
    //      ���ҵ�while�ؼ���, Ȼ���ڴʷ���Ԫ��������˳��while�ؼ���������,
    //      �ҵ��ĵ�һ��"("��������Ҫ�ҵ����Ǹ�"("����
    if((tupleNode = FindFirstSyntaxTreeTreinal(parentRoot, WHILE_KEYWORD)) != NULL)      // ���ҵ�while�ؼ���
    {
        if((terinalNode = FindFirstTupleTreinal(tupleNode, LPAREN_OPERATE)) != NULL)
        {
            // ��(������ĺ����������LINE(stream),
            long offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
            InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
        }

    }


}



// ���յ�140������ʽ��Լʱ�Ĳ�׮����
// iteration-statement -=> for( ; ; ) statement
// EG for( ; ; ) i++;
// AS for( LINE(stream) ;  ; LINE(stream)) i++;
void PropReduction140(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode  = NULL;
    PropTableNode   *newPropNode = NULL;
    int              offset = -1;


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // �ҵ���1��"("��λ��,
    if((tupleNode = FindTupleTreinal(headTupleNode, LPAREN_OPERATE, 1)) != NULL)
    {
        // �ڴ�λ�ò���һ����","�Ĳ�׮���ݴ�
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
    }

    // �ҵ���2��";"��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, SEMICOLON_SEPARATOR, 2)) != NULL)
    {
        // �ڵ�2��";"�������һ����׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
    }
}



// ���յ�141������ʽ��Լʱ�Ĳ�׮����
// iteration-statement -=> for( ; ;  expression ) statement
// eg for( ; ; i++) printf("130");
// AS for( LINE(strean); ; LINE(stream), i++) printf("130");
void PropReduction141(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode  = NULL;
    PropTableNode   *newPropNode = NULL;
    int              offset = -1;


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // �ҵ���1��"("��λ��,
    if((tupleNode = FindTupleTreinal(headTupleNode, LPAREN_OPERATE, 1)) != NULL)
    {
        // �ڴ�λ�ò���һ����","�Ĳ�׮���ݴ�
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
    }

    // �ҵ���2��";"��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, SEMICOLON_SEPARATOR, 2)) != NULL)
    {   //////////////////////////////////
        // �ڵ�1��";"ǰ������","�ŵĲ�׮��Ϣ��
        //offset = tupleNode->m_tuple.m_coord.m_fileBegOffset;
        //InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
        //////////////////////////////////
        // �ڵ�2��";"�������һ����׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }


}



// ���յ�142������ʽ��Լʱ�Ĳ�׮����
// iteration-statement -=> for ( ; expression ; ) statement
// EG for( ; i < 10; ) i++;
// AS for( LINE(stream) ; i < 10; LINE(stream)) i++;
void PropReduction142(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode  = NULL;
    PropTableNode   *newPropNode = NULL;
    int              offset = -1;


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // �ҵ���1��"("��λ��,
    if((tupleNode = FindTupleTreinal(headTupleNode, LPAREN_OPERATE, 1)) != NULL)
    {
        // �ڴ�λ�ò���һ����","�Ĳ�׮���ݴ�
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }

    // �ҵ���2��";"��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, SEMICOLON_SEPARATOR, 2)) != NULL)
    {
        // �ڵ�2��";"�������һ����׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
    }


}



// ���յ�143������ʽ��Լʱ�Ĳ�׮����
// iteration-statement -=> for( ; expression ; expression ) statement
// EG for( ; i < 10; i++) printf("132");
// AS for( LINE(stream); i < 10; LINE(stream), i++) printf("132");
void PropReduction143(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode  = NULL;
    PropTableNode   *newPropNode = NULL;
    int              offset = -1;


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // �ҵ���1��"("��λ��,
    if((tupleNode = FindTupleTreinal(headTupleNode, LPAREN_OPERATE, 1)) != NULL)
    {
        // �ڴ�λ�ò���һ����","�Ĳ�׮���ݴ�
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
    }

    // �ҵ���2��";"��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, SEMICOLON_SEPARATOR, 2)) != NULL)
    {
        // �ڵ�2��";"�������һ����׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }

}



// ���յ�144������ʽ��Լʱ�Ĳ�׮����
// iteration-statemnt -=> for( expression ; ; ) statement
// EG for( i = 0 ; ;) printf("133");
// AS for( LINE(stream), i = 0 ; ; LINE(stream) ) printf("133");
void PropReduction144(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode  = NULL;
    PropTableNode   *newPropNode = NULL;
    int              offset = -1;


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // �ҵ���1��"("��λ��,
    if((tupleNode = FindTupleTreinal(headTupleNode, LPAREN_OPERATE, 1)) != NULL)
    {
        // �ڴ�λ�ò���һ����","�Ĳ�׮���ݴ�
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }

    // �ҵ���2��";"��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, SEMICOLON_SEPARATOR, 2)) != NULL)
    {   //////////////////////////////////
        // �ڵ�1��";"ǰ������","�ŵĲ�׮��Ϣ��
        //offset = tupleNode->m_tuple.m_coord.m_fileBegOffset;
        //InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
        //////////////////////////////////
        // �ڵ�2��";"�������һ����׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
    }


}



// ���յ�145������ʽ��Լʱ�Ĳ�׮����
// iteration-statement -=> for( expression ; ; expression) printf("134");
// EG   for(i = 0 ; ; i++) printf("134");
// AS   for(LINE(stream), i = 0 ; ; LINE(stream), i++) printf("134");
void PropReduction145(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode  = NULL;
    PropTableNode   *newPropNode = NULL;
    int              offset = -1;


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // �ҵ���1��"("��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, LPAREN_OPERATE, 1)) != NULL)
    {
        // �ڵ�1��"("��������","�ŵĲ�׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);

        tupleNode = NULL;       // ���滹Ҫ���²����µ�tupleNode��Ϊ��ֹ����, ��ָ���ÿ�
    }

    // �ҵ���2��";"��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, SEMICOLON_SEPARATOR, 2)) != NULL)
    {
        // �ڵ�2��";"��������","�ŵĲ�׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }


}



// ���յ�146������ʽ��Լʱ�Ĳ�׮����
// iteration-statement -=> for( expression ; expression ; ) printf("135");
// EG for(i = 0 ; i < 10 ; ) printf("135");
// AS for(LINE(stream), i = 0; i < 10; LINE(stream) ) printf("135");
void PropReduction146(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode      *headTupleNode = NULL;
    TupleNode       *tupleNode  = NULL;
    PropTableNode   *newPropNode = NULL;
    int              offset = -1;


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // �ҵ���1��"("��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, LPAREN_OPERATE, 1)) != NULL)
    {
        // �ڵ�1��"("��������","�ŵĲ�׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);

        tupleNode = NULL;       // ���滹Ҫ���²����µ�tupleNode��Ϊ��ֹ����, ��ָ���ÿ�
    }

    // �ҵ���2��";"��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, SEMICOLON_SEPARATOR, 2)) != NULL)
    {
        // �ڵ�2��";"�������һ��������׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_BASE_PROP_KIND);
    }


}



// ���յ�147������ʽ��Լʱ�Ĳ�׮����
// iteraition-statement -=> for( expression ; expression ; expression ) statement
// EG   for(i = 0; i < 10; i++) printf("136");
// AS   for(LINE(stream), i = 10 ; i < 10; LINE(stream), i++) printf("136");
void PropReduction147(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
    TupleNode       *headTupleNode = NULL;
    TupleNode       *tupleNode  = NULL;
    PropTableNode   *newPropNode = NULL;
    int              offset = -1;


    // ���﷨�������ҵ���һ���ս�����
    headTupleNode = FindFirstChildTupleNode(parentRoot);

    // �ҵ���1��"("��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, LPAREN_OPERATE, 1)) != NULL)
    {
        // �ڵ�1��";"ǰ������","�ŵĲ�׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }

    // �ҵ���2��";"��λ��, �ڴ�λ�ò���һ�������Ĳ�׮���ݴ�
    if((tupleNode = FindTupleTreinal(headTupleNode, SEMICOLON_SEPARATOR, 2)) != NULL)
    {
        // �ڵ�2��";"�������һ����׮��Ϣ��
        offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
    }


}



// ���յ�148������ʽ��Լʱ�Ĳ�׮����
// jump-statement -=> goto identifier ;
// EG goto label
// AS  LINE(stream); goto label
void PropReduction148(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

//    TupleNode     *tupleNode = NULL;
//
//    // �ҵ�goto�ؼ��ֵ�λ��
//    if((tupleNode = FindFirstSyntaxTreeTreinal(parentRoot, GOTO_KEYWORD)) != NULL)
//    {
//        // ��goto�ؼ��ֵ�ǰ���������
//        long offset = tupleNode->m_tuple.m_coord.m_fileBegOffset;
//        InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
//    }
    long offset = -1;
    SyntaxTreeNode *treeNode = parentRoot;

    // ����ʼλ�����һ��" { LINE(strewam);"
    offset = treeNode->m_syntax.m_startCoord.m_fileBegOffset;
    InsertPropData(propTable, offset, PROP_LBRACE_SEPARATOR_KIND);
    InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
    // ����ʼλ�����һ��" } "
    offset = treeNode->m_syntax.m_endCoord.m_fileEndOffset;
    InsertPropData(propTable, offset, PROP_RBRACE_SEPARATOR_KIND);
}



// ���յ�149������ʽ��Լʱ�Ĳ�׮����
// jump-statement -=> continue ;
// EG continue ;
// AS LINE(stream); continue;
// AS
void PropReduction149(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

//    TupleNode     *tupleNode = NULL;
//
//    // �ҵ�continue�ؼ��ֵ�λ��
//    if((tupleNode = FindFirstSyntaxTreeTreinal(parentRoot, CONTINUE_KEYWORD)) != NULL)
//    {
//        // ��continue�ؼ��ֵ�ǰ���������
//        long offset = tupleNode->m_tuple.m_coord.m_fileBegOffset;
//        InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
//
//    }
    long offset = -1;
    SyntaxTreeNode *treeNode = parentRoot;

    // ����ʼλ�����һ��" { LINE(strewam);"
    offset = treeNode->m_syntax.m_startCoord.m_fileBegOffset;
    InsertPropData(propTable, offset, PROP_LBRACE_SEPARATOR_KIND);
    InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
    // ����ʼλ�����һ��" } "
    offset = treeNode->m_syntax.m_endCoord.m_fileEndOffset;
    InsertPropData(propTable, offset, PROP_RBRACE_SEPARATOR_KIND);
}



// ���յ�150������ʽ��Լʱ�Ĳ�׮����
// jump-statement -=> break;
void PropReduction150(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

    TupleNode     *tupleNode = NULL;

//    // �ҵ�break�ؼ��ֵ�λ��
//    if((tupleNode = FindFirstSyntaxTreeTreinal(parentRoot, BREAK_KEYWORD)) != NULL)
//    {
//        // ��break�ؼ��ֵ�ǰ���������
//        long offset = tupleNode->m_tuple.m_coord.m_fileBegOffset;
//        InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
//    }
    long offset = -1;
    SyntaxTreeNode *treeNode = parentRoot;

    // ����ʼλ�����һ��" { LINE(strewam);"
    offset = treeNode->m_syntax.m_startCoord.m_fileBegOffset;
    InsertPropData(propTable, offset, PROP_LBRACE_SEPARATOR_KIND);
    InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
    // ����ʼλ�����һ��" } "
    offset = treeNode->m_syntax.m_endCoord.m_fileEndOffset;
    InsertPropData(propTable, offset, PROP_RBRACE_SEPARATOR_KIND);
}



// ���յ�151������ʽ��Լʱ�Ĳ�׮����
// jump-statement -=> return;
// EG return ;
// AS LINE(stream); return ;
void PropReduction151(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

//    TupleNode     *tupleNode = NULL;
//
//    // �ҵ�return�ؼ��ֵ�λ��
//    if((tupleNode = FindFirstSyntaxTreeTreinal(parentRoot, RETURN_KEYWORD)) != NULL)
//    {
//        // ��return�ؼ��ֵ�ǰ���������
//        long offset = tupleNode->m_tuple.m_coord.m_fileBegOffset;
//        InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
//    }
    long offset = -1;
    SyntaxTreeNode *treeNode = parentRoot;

    // ����ʼλ�����һ��" { LINE(strewam);"
    offset = treeNode->m_syntax.m_startCoord.m_fileBegOffset;
    InsertPropData(propTable, offset, PROP_LBRACE_SEPARATOR_KIND);
    InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
    // ����ʼλ�����һ��" } "
    offset = treeNode->m_syntax.m_endCoord.m_fileEndOffset;
    InsertPropData(propTable, offset, PROP_RBRACE_SEPARATOR_KIND);

}



// ���յ�152������ʽ��Լʱ�Ĳ�׮����
// jump-statement -=> return expression ;
// ���ط���һ��expression;������ֵ
// EG   return NULL;
// AS   return Line(stream), NULL;
void PropReduction152(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

//
//    TupleNode     *tupleNode = NULL;
//
//    // �ҵ�return�־��λ��
//    if((tupleNode = FindFirstSyntaxTreeTreinal(parentRoot, RETURN_KEYWORD)) != NULL)
//    {
//        long offset = tupleNode->m_tuple.m_coord.m_fileEndOffset;
//        InsertPropData(propTable, offset, PROP_COMMA_PROP_KIND);
//    }
    long offset = -1;
    SyntaxTreeNode *treeNode = parentRoot;

    // ����ʼλ�����һ��" { LINE(strewam);"
    offset = treeNode->m_syntax.m_startCoord.m_fileBegOffset;
    InsertPropData(propTable, offset, PROP_LBRACE_SEPARATOR_KIND);
    InsertPropData(propTable, offset, PROP_SEMICOLON_PROP_KIND);
    // ����ʼλ�����һ��" } "
    offset = treeNode->m_syntax.m_endCoord.m_fileEndOffset;
    InsertPropData(propTable, offset, PROP_RBRACE_SEPARATOR_KIND);
}






// ���յ�153������ʽ��Լʱ�Ĳ�׮����
void PropReduction153(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�154������ʽ��Լʱ�Ĳ�׮����
void PropReduction154(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�155������ʽ��Լʱ�Ĳ�׮����
void PropReduction155(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�156������ʽ��Լʱ�Ĳ�׮����
void PropReduction156(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�157������ʽ��Լʱ�Ĳ�׮����
void PropReduction157(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�158������ʽ��Լʱ�Ĳ�׮����
void PropReduction158(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�159������ʽ��Լʱ�Ĳ�׮����
void PropReduction159(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�160������ʽ��Լʱ�Ĳ�׮����
void PropReduction160(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�161������ʽ��Լʱ�Ĳ�׮����
void PropReduction161(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�162������ʽ��Լʱ�Ĳ�׮����
void PropReduction162(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�163������ʽ��Լʱ�Ĳ�׮����
void PropReduction163(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�164������ʽ��Լʱ�Ĳ�׮����
void PropReduction164(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�165������ʽ��Լʱ�Ĳ�׮����
void PropReduction165(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�166������ʽ��Լʱ�Ĳ�׮����
void PropReduction166(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�167������ʽ��Լʱ�Ĳ�׮����
void PropReduction167(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�168������ʽ��Լʱ�Ĳ�׮����
void PropReduction168(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�169������ʽ��Լʱ�Ĳ�׮����
void PropReduction169(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�170������ʽ��Լʱ�Ĳ�׮����
void PropReduction170(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�171������ʽ��Լʱ�Ĳ�׮����
void PropReduction171(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�172������ʽ��Լʱ�Ĳ�׮����
void PropReduction172(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�173������ʽ��Լʱ�Ĳ�׮����
void PropReduction173(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�174������ʽ��Լʱ�Ĳ�׮����
void PropReduction174(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�175������ʽ��Լʱ�Ĳ�׮����
void PropReduction175(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�176������ʽ��Լʱ�Ĳ�׮����
void PropReduction176(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�177������ʽ��Լʱ�Ĳ�׮����
void PropReduction177(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�178������ʽ��Լʱ�Ĳ�׮����
void PropReduction178(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�179������ʽ��Լʱ�Ĳ�׮����
void PropReduction179(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�180������ʽ��Լʱ�Ĳ�׮����
void PropReduction180(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�181������ʽ��Լʱ�Ĳ�׮����
void PropReduction181(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�182������ʽ��Լʱ�Ĳ�׮����
void PropReduction182(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�183������ʽ��Լʱ�Ĳ�׮����
void PropReduction183(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�184������ʽ��Լʱ�Ĳ�׮����
void PropReduction184(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�185������ʽ��Լʱ�Ĳ�׮����
void PropReduction185(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�186������ʽ��Լʱ�Ĳ�׮����
void PropReduction186(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�187������ʽ��Լʱ�Ĳ�׮����
void PropReduction187(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�188������ʽ��Լʱ�Ĳ�׮����
void PropReduction188(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�189������ʽ��Լʱ�Ĳ�׮����
void PropReduction189(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�190������ʽ��Լʱ�Ĳ�׮����
void PropReduction190(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�191������ʽ��Լʱ�Ĳ�׮����
void PropReduction191(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�192������ʽ��Լʱ�Ĳ�׮����
void PropReduction192(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�193������ʽ��Լʱ�Ĳ�׮����
void PropReduction193(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�194������ʽ��Լʱ�Ĳ�׮����
void PropReduction194(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�195������ʽ��Լʱ�Ĳ�׮����
void PropReduction195(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�196������ʽ��Լʱ�Ĳ�׮����
void PropReduction196(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�197������ʽ��Լʱ�Ĳ�׮����
void PropReduction197(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�198������ʽ��Լʱ�Ĳ�׮����
void PropReduction198(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�199������ʽ��Լʱ�Ĳ�׮����
void PropReduction199(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�200������ʽ��Լʱ�Ĳ�׮����
void PropReduction200(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�201������ʽ��Լʱ�Ĳ�׮����
void PropReduction201(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�202������ʽ��Լʱ�Ĳ�׮����
void PropReduction202(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�203������ʽ��Լʱ�Ĳ�׮����
void PropReduction203(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�204������ʽ��Լʱ�Ĳ�׮����
void PropReduction204(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�205������ʽ��Լʱ�Ĳ�׮����
void PropReduction205(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�206������ʽ��Լʱ�Ĳ�׮����
void PropReduction206(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�207������ʽ��Լʱ�Ĳ�׮����
void PropReduction207(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�208������ʽ��Լʱ�Ĳ�׮����
void PropReduction208(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�209������ʽ��Լʱ�Ĳ�׮����
void PropReduction209(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�210������ʽ��Լʱ�Ĳ�׮����
void PropReduction210(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�211������ʽ��Լʱ�Ĳ�׮����
void PropReduction211(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�212������ʽ��Լʱ�Ĳ�׮����
void PropReduction212(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�213������ʽ��Լʱ�Ĳ�׮����
void PropReduction213(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�214������ʽ��Լʱ�Ĳ�׮����
void PropReduction214(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�215������ʽ��Լʱ�Ĳ�׮����
void PropReduction215(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�216������ʽ��Լʱ�Ĳ�׮����
void PropReduction216(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�217������ʽ��Լʱ�Ĳ�׮����
void PropReduction217(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�218������ʽ��Լʱ�Ĳ�׮����
void PropReduction218(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}



// ���յ�219������ʽ��Լʱ�Ĳ�׮����
void PropReduction219(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE

}

// ���յ�220������ʽ��Լʱ�Ĳ�׮����
void PropReduction220(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�221������ʽ��Լʱ�Ĳ�׮����
void PropReduction221(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�222������ʽ��Լʱ�Ĳ�׮����
void PropReduction222(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�223������ʽ��Լʱ�Ĳ�׮����
void PropReduction223(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�224������ʽ��Լʱ�Ĳ�׮����
void PropReduction224(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�225������ʽ��Լʱ�Ĳ�׮����
void PropReduction225(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�226������ʽ��Լʱ�Ĳ�׮����
void PropReduction226(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�227������ʽ��Լʱ�Ĳ�׮����
void PropReduction227(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�228������ʽ��Լʱ�Ĳ�׮����
void PropReduction228(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�229������ʽ��Լʱ�Ĳ�׮����
void PropReduction229(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�230������ʽ��Լʱ�Ĳ�׮����
void PropReduction230(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�231������ʽ��Լʱ�Ĳ�׮����
void PropReduction231(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}



// ���յ�232������ʽ��Լʱ�Ĳ�׮����
void PropReduction232(PropTable propTable, SyntaxTree parentRoot)
{
//#ifdef PARSER_DEBUG_DEFINE
//FILE_FUNC_LINE( );
//#endif // PARSER_DEBUG_DEFINE
//    return NULL;
}

