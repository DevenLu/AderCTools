



#include "PropTable.h"





//////////////////////////////////////
// ��¼��׮��Ϣ��Ŀ��ȫ�ֱ���
//int g_propNodeCount = 0;
/////////////////////////////////////

// ������׮��Ϣ��, ���ҳ�ʼ��
PropTable CreatePropTable(void)
{
    PropTable  propTable = NULL;

    if((propTable = (PropTableNode *)malloc(sizeof(PropTableNode))) != NULL)
    {
        propTable->m_prop.m_offset = 0;
        propTable->m_prop.m_kind = -1;
        propTable->m_next = NULL;
    }
    ////////////////////////////////////////////////////////////
    // g_propNodeCount = 0;            // ��ǰ��׮��Ϣ������ĿΪ��
    ////////////////////////////////////////////////////////////
    // InsertPropData(propTable, )
    return propTable;
}

// ����ƫ��offset�ں������ҵ��ʵ���λ��
PropTableNode *FindPropInsertPos(PropTable propTable, int offset)
{
    PropTableNode   *headPropNode = propTable;
    PropTableNode   *lastPropNode = headPropNode;           // ��һ�����
    PropTableNode   *currPropNode = headPropNode->m_next;   // ��ǰ���

    while(currPropNode != NULL)
    {
        // ����ƫ�ƴ�С�����˳�򽫲�׮��Ϣ�������׮��Ϣ����
        // ����ҵ���ǰ��׮��Ϣ������ƫ�ƴ��ڵ�ǰҪ����ƫ�Ƶ��Ǹ����currPropNode
        // �ý���ǰһ��λ��currPropNode����Ҫ�����λ��
        // ʹ�� ">" ���Ա�֤ƫ����ͬʱ�� �Ȳ���Ľ����ǰ�� �����Ľ���ں�...
        if(currPropNode->m_prop.m_offset > offset)
        {
            break;
        }

        lastPropNode = currPropNode;
        currPropNode = currPropNode->m_next;
    }


    return lastPropNode;
}

// ����׮�����Լ��ض����к���Ϣ�����׮��Ϣ��
void InsertPropDataWithLine(PropTable propTable, long offset, PropStrKind kind, int line)
{
#ifdef PROP_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // PROP_DEBUG_DEFINE
    PropTableNode   *headPropNode = (PropTableNode *)propTable;             // ͷָ�봮
    PropTableNode   *posPropNode = FindPropInsertPos(propTable, offset);    // ������λ�ô���
    PropTableNode   *newPropNode = NULL;                                    // �����봮

    if((newPropNode = (PropTableNode *)malloc(sizeof(PropTableNode))) != NULL)
    {
//        printf("���ٵĵ�ַ%p\n", newPropNode);
//        printf("%p    ******** %p\n", propNode, newPropNode);

        #ifdef PROP_SHOWS_DEFINE
        printf("��[%d, %d]�����׮��Ϣ����\n", offset, kind);
        #endif // PROP_SHOWS_DEFINE

        newPropNode->m_prop.m_offset = offset;
        newPropNode->m_prop.m_kind = kind;
        newPropNode->m_prop.m_line = line;

        newPropNode->m_next = posPropNode->m_next;
        posPropNode->m_next = newPropNode;

        //////////////////////////////////////////////
        // ��¼��ǰ��׮��Ϣ������ݽ����Ŀ
        // g_propNodeCount++;
        headPropNode->m_prop.m_offset++;
        //////////////////////////////////////////////
    }
    else
    {
        FILE_FUNC_LINE( );
        fprintf(stderr, "NO MEMORY\n");
    }
}

// ��"��Ҫ��offsetƫ�ƣ� ����kind��ʽ�Ĳ�׮��"�Ĳ�׮������Ϣ������ַ���
void InsertPropData(PropTable propTable, long offset, PropStrKind kind)
{
#ifdef PROP_DEBUG_DEFINE
FILE_FUNC_LINE( );
#endif // PROP_DEBUG_DEFINE
    PropTableNode   *headPropNode = (PropTableNode *)propTable;             // ͷָ�봮
    PropTableNode   *posPropNode = FindPropInsertPos(propTable, offset);    // ������λ�ô���
    PropTableNode   *newPropNode = NULL;                                    // �����봮

    if((newPropNode = (PropTableNode *)malloc(sizeof(PropTableNode))) != NULL)
    {
//        printf("���ٵĵ�ַ%p\n", newPropNode);
//        printf("%p    ******** %p\n", propNode, newPropNode);

        #ifdef PROP_SHOWS_DEFINE
        printf("��[%d, %d]�����׮��Ϣ����\n", offset, kind);
        #endif // PROP_SHOWS_DEFINE

        newPropNode->m_prop.m_offset = offset;
        newPropNode->m_prop.m_kind = kind;

        newPropNode->m_next = posPropNode->m_next;
        posPropNode->m_next = newPropNode;

        //////////////////////////////////////////////
        // ��¼��ǰ��׮��Ϣ������ݽ����Ŀ
        // g_propNodeCount++;
        headPropNode->m_prop.m_offset++;
        //////////////////////////////////////////////
    }
    else
    {
        FILE_FUNC_LINE( );
        fprintf(stderr, "NO MEMORY\n");
    }
}


// ɾ����׮��Ϣ��ĵ�һ�����ݽ��
void DeleteFirstPropData(PropTable propTable)
{
    PropTableNode *headPropNode = propTable;

    if(EmptyPropTable(propTable) != true)           // ֻҪ��ǰ��׮��Ϣ���ǿձ�
    // if(headPropNode->m_next != NULL)
    // if(headPropNode->m_prop.m_offset != 0)
    {
        PropTableNode *firstPropNode = headPropNode->m_next;
        headPropNode->m_next = firstPropNode->m_next;
        free(firstPropNode);

        /////////////////////////////////////////
        headPropNode->m_prop.m_offset--;/////////
        /////////////////////////////////////////
    }
    else            // �ղ�׮��Ϣ���޷�ɾ����һ�����ݽ��
    {
        fprintf(stderr, "��ǰ��׮��Ϣ��Ϊ��");
    }
}

// ��ʾ��ǰ��׮��������
void ShowPropTableNode(PropTableNode *propNode)
{
    printf("[%d, %d]\n", propNode->m_prop.m_offset, propNode->m_prop.m_kind);
}


// ��ʾ��ǰ��׮��Ϣ��
void ShowPropTable(PropTable propTable)
{
    #ifdef PROP_HELPS_DEFINE
    printf("*************************************************\n");
    printf("**               ��ʾ��׮��Ϣ��                **\n");
    printf("*************************************************\n");
    PAUSE( );
    #endif
    PropTableNode *pNode = (PropTableNode *)propTable;

    while(pNode != NULL)
    {
        ShowPropTableNode(pNode);
        pNode = pNode->m_next;
    }
    PAUSE( );
}




// ���ٵ�ǰ��׮��Ϣ��
void DestroyPropTable(PropTable propTable)
{
    PropTableNode *headPropNode = (PropTableNode *)propTable;

    while(EmptyPropTable(propTable) != true)           // ֻҪ��ǰ��׮��Ϣ���ǿձ�
    {
        DeleteFirstPropData(propTable);
    }

    free(headPropNode);
}


void WritePropDefStr(PropTableNode *propNode, CToolsFILE destFp, const char *srcFname)
{

    // ����������ÿ�޸�һ�����Ҫȥ�ļ�PropTable.h���޸�PropStrKind������
    const char *propDefStrArray[] =
    {
        START_DEFINE_PROP_STR,            // ��ʼ��Ϣ�괮
        INCLUDE_DEFINE_PROP_STR,          // �������ļ������꣬������ļ���ͷ
        LINE_DEFINE_PROP_STR,             // �����Ĳ�׮���֧�ֺ꣬������ļ���ͷ
        FILE_OPEN_DEFINE_PROP_STR,        // ���ļ����׮���������main������ʼ��λ��
        PROP_CLOSE_DEFINE_PROP_STR,       // �ر��ļ����׮��, ���������������֮ǰ
        PROP_BASE_PROP_STR,               // ������Ĳ�׮��Ϣ��" LINE(stream) "
        PROP_COMMA_PROP_STR,              // ��","�Ĳ�׮��Ϣ��" LINE(stream), "
        PROP_SEMICOLON_PROP_STR,          // ��"��"�Ĳ�׮��Ϣ��" LINE(stream); "
        PROP_LBRACE_SEPARATOR_STR,        // " { "
        PROP_RBRACE_SEPARATOR_STR,        // " } "
    };

    // ������д���ļ���
    #ifdef CTOOLS_FILE_OPEN_BINARY
    fwrite(propDefStrArray[propNode->m_prop.m_kind], sizeof(propDefStrArray[propNode->m_prop.m_kind]), 1, destFp);
    #endif // CTOOLS_FILE_OPEN_BINARY
    #ifdef CTOOLS_FILE_OPEN_TEXT
    fprintf(destFp, "%s", propDefStrArray[propNode->m_prop.m_kind]);
    #endif // CTOOLS_FILE_OPEN_TEXT
/*
    if(propNode->m_prop.m_kind == FILE_OPEN_DEFINE_PROP_KIND)
   //|| propNode->m_prop.m_kind == FILE_CLOSE_DEFINE_PROP_KIND)
    {
        WritePropLineStr(destFp, srcFname, propNode->m_prop.m_line);              // �����кų�ʼ������
    }
    */
}

// ����PropTable����Ϣ��Դ�ļ�srcFname������д��destFname�ļ�
void WriteProp(PropTable propTable, const char *destFname, const char *srcFname)
{


    // ��׮��Ϣ������
    PropTableNode *headPropNode = (PropTableNode *)propTable;
    PropTableNode *currPropNode = headPropNode->m_next;

    // �������׼��
    #ifdef CTOOLS_FILE_OPEN_TEXT
    // ���ı���ʽ���ļ�
    CToolsFILE     destFp = CToolsOpen(destFname, WRITE_ONLY_TEXT);
    CToolsFILE     srcFp = CToolsOpen(srcFname,  READ_ONLY_TEXT);
    #endif // CTOOLS_FILE_OPEN_TEXT

    #ifdef CTOOLS_FILE_OPEN_BINARY
    // �Զ����Ʒ�ʽ���ļ�
    CToolsFILE     destFp = CToolsOpen(destFname, WRITE_ONLY_BINARY);
    CToolsFILE     srcFp = CToolsOpen(srcFname,  READ_ONLY_BINARY);
    #endif // CTOOLS_FILE_OPEN_BINARY


    long           startOffset = -1;
    long           endOffset = -1;
    int             count = 0;

    // ��ʼ��Ŀ���ļ���д���׮��Ϣ
    InitProp(destFp, srcFname);
    startOffset = 0;                // �����׮�ļ�����ʼλ�ÿ�ʼд��
    while(currPropNode != NULL)
    {
        #ifdef PROP_SHOWS_DEFINE
        printf("��ǰ�����׮��Ϣ�����ݵ�Ԫ:");
        ShowPropTableNode(currPropNode);
        PAUSE( );
        #endif // PROP_SHOWS_DEFINE

        endOffset = currPropNode->m_prop.m_offset;

        count = endOffset - startOffset;
        // ��srcFpָ��Դ�ļ��е�ǰλ�ÿ�ʼ��count���ַ�д��destFpָ���Ŀ���ļ�
        PropWriteCountSrcToDest(destFp, srcFp, count);

//        #ifdef PROP_DEBUG_DEFINE
//        printf("%s\n", propDefStrArray[currPropNode->m_prop.m_kind]);
//        #endif // PROP_DEBUG_DEFINE

        //fprintf(destFp, "%s", propDefStrArray[currPropNode->m_prop.m_kind]);
        WritePropDefStr(currPropNode, destFp, srcFname);
        currPropNode = currPropNode->m_next;
        startOffset = endOffset;
    }
    PropWriteAllSrcToDest(destFp, srcFp);       // ��Դ�ļ���������д��Ŀ���ļ�

    CToolsCloseAll(destFp, srcFp, NULL);            // �ر������ļ���Ϣ
}

