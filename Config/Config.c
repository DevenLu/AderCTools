


#include "Config.h"     //  #include "..\Config\Config.h"

int CToolsPrintf(const char* format, ...)
{
	va_list	argPtr;
	int		count;

	va_start(argPtr, format);				// ��ȡ�ɱ�����б�ĵ�ַ
	count = vprintf(format, argPtr);		// ����Ϣ���������豸
	va_end(argPtr);							// �ɱ�����Ľ���

	return count;
}




///CTOOLSȫ�ֵ��Ժ궨��////////////////////////////////////////////
// CTools���Ժ���Ϣ////////////////////////////////
#ifdef CTOOLS_DEBUG_DEFINE
    #define CToolsDebugPrintf(arg)  CToolsPrintf arg
    #define ShowFileFunctionLine( )    FILE_FUNC_LINE( )
#else
    #define CToolsDebugPrintf
    #define ShowFileFunctionLine( )
#endif
//////////////////////////////////////////////////
#
#
// CTools��Ϣ�����////////////////////////////////
#ifdef CTOOLS_SHOWS_DEFINE
    #define CToolsShowsPintf(arg)    CToolsPrintf arg
#else
    #define CToolsShowsPintf(arg)
#endif
//////////////////////////////////////////////////
#
#
//////////////////////////////////////////////////
#ifdef CTOOLS_HELPS_DEFINE
    #define CToolsHelpsPrintf(arg)  CToolsPrintf arg
#else
    #define CToolsHelpsPrintf(arg)
#endif
//////////////////////////////////////////////////
///-/////////////////////////////////////////////////////////////
#
#
///-�ʷ�LEXȫ�ֵ�����Ϣ����////////////////////////////////////////
// LEXICAL���Ժ���Ϣ////////////////////////////////
#ifdef LEXICAL_DEBUG_DEFINE
    #define LexicalDebugPrintf(arg)  CToolsPrintf arg
#else
    #define LexicalDebugPrintf
#endif
//////////////////////////////////////////////////
#
#
// LEXICAL��Ϣ�����////////////////////////////////
#ifdef LEXICAL_SHOWS_DEFINE
    #define LexicalShowsPintf(arg)    CToolsPrintf arg
#else
    #define LexicalShowsPintf(arg)
#endif
//////////////////////////////////////////////////
#
#
// LEXICAL���������////////////////////////////////
#ifdef LEXICAL_HELPS_DEFINE
    #define LexicalHelpsPrintf(arg)  CToolsPrintf arg
#else
    #define LexicalHelpsPrintf(arg)
#endif
//////////////////////////////////////////////////
///-/////////////////////////////////////////////////////////////
#
#
///-�﷨PARSERȫ�ֵ�����Ϣ����////////////////////////////////////////
// PARSER���Ժ���Ϣ////////////////////////////////
#ifdef PARSER_DEBUG_DEFINE
    #define ParserDebugPrintf(arg)  CToolsPrintf arg
#else
    #define ParserDebugPrintf
#endif
//////////////////////////////////////////////////
#
#
// PARSER��Ϣ�����////////////////////////////////
#ifdef PARSER_SHOWS_DEFINE
    #define ParserShowsPintf(arg)    CToolsPrintf arg
#else
    #define ParserShowsPintf(arg)
#endif
//////////////////////////////////////////////////
#
#
// PARSER���������////////////////////////////////
#ifdef PARSER_HELPS_DEFINE
    #define ParserHelpsPrintf(arg)  CToolsPrintf arg
#else
    #define ParserHelpsPrintf(arg)
#endif
//////////////////////////////////////////////////
///-////////////////////////////////////////////////////////////
