/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : Errors.c                                                      *
*   Description: CTools                                              *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/




#include "Errors.h"
#include "CTools.h"    //  #include "..\Global\CTools.h"






int ErrorCount;         // �����ȫ�ֱ�������������Ŀ
int WarningCount;       // �����ȫ�ֱ������뾯�����Ŀ


Coord* InitCoord(const char *sourFile)            // ��ʼ����λ��Ϣ
{
    Coord *coord = malloc(sizeof(Coord));           // ��ʼ��λ��Ϣ�Ŀռ�

    char *str = malloc(strlen(sourFile) + sizeof(char));
    strcpy(str, sourFile);
    coord->m_fileName = str;            // �ļ���
    coord->m_fileLine = 1;              // �кų�ʼ��Ϊ0
    coord->m_fileBegOffset = 0;         // ��ʼƫ����Ϣ��ʼ��Ϊ0
    coord->m_fileEndOffset = 0;         // ����ƫ����Ϣ��ʼ��Ϊ0
    return coord;
}


/// ����Coordλ�ñ�ʶ�Ĵʷ�������ƫ��
void AddCoordEndOffset(Coord *coord)
{
    coord->m_fileEndOffset += sizeof(char);
}


/// ����Coordλ�ñ�ʶ�Ĵʷ���ʼƫ��
void AddCoordBegOffset(Coord *coord)
{
    coord->m_fileBegOffset += sizeof(char);
}

/// ����Coordλ�ñ�ʶ�Ĵʷ���ʼƫ��
void SubCoordBegOffset(Coord *coord)
{
    coord->m_fileBegOffset -= sizeof(char);
}

/// ����Coordλ�ñ�ʶ�Ĵʷ�������ƫ��
void SubCoordEndOffset(Coord *coord)
{
    coord->m_fileEndOffset -= sizeof(char);
}


// ��ʾ��ǰλ��ƫ����Ϣ
void ShowCoord(Coord *coord)
{
    SHOW_FILE_NAME(coord->m_fileName);
    printf("Line = %d  ", coord->m_fileLine);
    printf("Begi = %d ", coord->m_fileBegOffset);
    printf("Endl = %d ", coord->m_fileEndOffset);
}



/// ���ʷ���ʼλ��ƫ�ƶ��뵽����λ�ñ�ʶ
void CheckBegOffsetToEndOffset(Coord *coord)
{
    coord->m_fileBegOffset = coord->m_fileEndOffset;
}

// �ļ�λ�ñ�ʶ����β��־
void FinitCoord(Coord *coord)
{
    if(coord != NULL)
    {
        free(coord);            // ���ļ�λ�ñ�ʶ��ָ��ѿռ����
    }
}



CompResult* InitCompResult( )                          // ��ʼ��������
{
    CompResult *compResult = malloc(sizeof(CompResult));

    compResult->m_erroCount = 0;        // ��ʼ���޴���
    compResult->m_warnCount = 0;        // ��ʼ���޾���
    compResult->m_stop = NO_ERR;        // ��ʼ����ֹ��ϢΪ�޴��󷵻�

    return compResult;          // ���ر�������
}

/// ����ʵ�ֲ���
void Error(Coord *coord, const char *format, ...)
{
	va_list ap;

	ErrorCount++;
	if (coord)
	{
		fprintf(stderr, "[%s, %4d]\t", coord->m_fileName, coord->m_fileLine);
	}
	fprintf(stderr, "error:");
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	fprintf(stderr, "\n");
	va_end(ap);
}

void Fatal(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	fprintf(stderr, "\n");
	va_end(ap);

	exit(-1);
}

void Warning(Coord *coord, const char *format, ...)
{
	va_list ap;

	WarningCount++;
	if (coord)
	{
		fprintf(stderr, "[%s,%4d]:\t", coord->m_fileName, coord->m_fileLine);
	}

	fprintf(stderr, "warning:");
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	fprintf(stderr, "\n");
	va_end(ap);

	return;
}




