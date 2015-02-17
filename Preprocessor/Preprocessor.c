/**
*********************************************************************************
*   CopyRight  : 2013-2014, HerBinUnversity, GatieMe                            *
*   File Name  : Preprocessor.c                                                         *
*   Description: CTools                                                         *
*   Author     : Gatie_Me                                                       *
*   Version    : Copyright 2013-2014                                            *
*   Data_Time  : 2013-3-10 21:29:24                                             *
*   Content    : CTools-Lexical                                                 *
*********************************************************************************
**/








#include "Preprocessor.h"               // Ԥ�������ӿ�
#include "Errors.h"                     // ����λ��Ϣ
#include "Buffer.h"

/// Preprocessor��������
#ifdef PUBLIC_and_PRIVATE
#
#
/// ȷ��Ԥ�����ļ�������
PRIVATE bool                                // ����Ԥ�����Ƿ�ɹ�
SetProFileName(
               char *sourFile);             // ������Դ�ļ����ƻ���·��
#
#
/// ��#define�궨��ָ����д���
PRIVATE bool                                // ���ض�#defineԤ�����Ƿ�ɹ�
ProDefine(DouBuffer *douBuffer,             // ˫��������Ϣ
          char *str,                        // �������ļ��ж�ȡ�������ַ�����Ϣ
          CToolsFILE ifp);                  // �������ļ�
#
#
/// ��#line�궨��ָ����д���
PRIVATE bool                                // ����#lineԤ���봦���Ƿ�ɹ�
ProLine(DouBuffer *douBuffer,               // ������������Ϣ
        char *str);                          // ��������ַ���
#
#
#endif          // PUBLIC_and_PRIVATE

/// Ԥ������
/*
˼·��
    ���ȴ�ԭ�ļ��ж�ȡһ����Ϣ, �жϵ�ǰ��Ϣ
    ��������͵�ע�;�����
    �����#Ԥ����ָ��Ϳ�ʼ����
    ͬʱ�ݹ������Ϣ
    ���Դ�ļ����к���Ϣ
*/

/// ȷ��Ԥ�����ļ�������
bool SetProFileName(char *sourFile)             // ������Դ�ļ����ƻ���·��
{
    return false;
}


bool Processor(char *destFile, char *sourFile)
{
    char        str[BUFFER_SIZE];              // ���ڴ洢���ļ��ж�ȡ�����ַ�����Ϣ

    // ׼������������ļ�
    /// �������һ�����⣺���������ļ�ʧ�ܷ��ص���ifpȴ�򿪲�û�йر�
    CToolsFILE  ifp = CToolsFineOpen(sourFile, READ_ONLY_BINARY, NULL/*��ǰ���ļ��б�Ϊ��*/);        // ��Դ�ļ�
    CToolsFILE  ofp = CToolsFineOpen(destFile,WRITE_ONLY_BINARY, ifp, NULL/*��ǰ���ļ��б�Ϊifp, NULL*/);        // Ŀ���ļ�

    /// �ʷ��кŵļ�¼��Ϣ
    ///Coord *coord = InitCoord(sourFile);                 // �ļ��кż�¼��Ϣ

    /// ˫������������Ϣ
    DouBuffer *douBuffer = InitBuffer(sourFile);                   // ˫��������Ϣ

    if(CToolsGets(str, BUFFER_SIZE, ifp) != NULL)        // ���д�ԭ�ļ��ж�ȡ��Ϣ
    {
        if(str[0] == '#')           // ��#��ͷ��ΪԤ��������
        {
            if(strncmp(str, "include", 7) == 0)             //
            {

            }
            else if(strncmp(str, "define", 6) == 0)         // �궨��Ԥ����ָ��
            {

            }
            else if(strncmp(str, "undef", 5) == 0)          // ȡ�������ָ��
            {

            }
            else if(strncmp(str, "if", 2) == 0)             // ��������ָ��#if, #ifdef, #ifndef, #if define,
            {

            }
            else if(strncmp(str, "el", 2) == 0)             // ��������ָ��
            {

            }
            else if(strncmp(str, "error", 5) == 0)         // ����Ԥ����ָ��
            {

            }
            else if(strncmp(str, "line", 4) == 0)           // �кű���ָ��
            {

            }
            else if(strncmp(str, "pragma", 6) == 0)         // �������ָ��
            {

            }
            else
            {
                ///*/////////////////////////////////////////////////////////
                ///                 �ļ����д�����Ϣ
                ///*/////////////////////////////////////////////////////////
            }
        }
        else                // Դ�ļ��в���#��ͷ�ľ���Դ������Ϣ
        {
            WriteStrInBuffer(douBuffer, str);               // ֱ�ӽ�Դ����д�뻺������
        }
    }

    if(douBuffer->m_coord != NULL)
    {
        free(douBuffer->m_coord);
    }

    return true;
}



/// ��#define�궨��ָ����д���
// char *str    ���ļ��ж�ȡ����str�ַ�����Ϣ
//
bool ProDefine(DouBuffer *douBuffer, char *str, CToolsFILE ifp)
{
    return true;
}


/// ��#ifdef�궨��ָ����д���
// char *str    ���ļ��ж�ȡ����str�ַ�����Ϣ
//
bool ProIfdef(DouBuffer *douBuffer, char *str, CToolsFILE ifp)
{
    #ifdef CTOOLS_DEBUG_DEFINE
    assert(strncmp(str, "ifdef", 5) == 0);          // ��������Ϸ�
    #endif     // CTOOLS_DEBUG_DEFINE


    return true;
}


/// ��#line�궨��ָ����д���
bool ProLine(DouBuffer *douBuffer, char *str)                          // ��������ַ���
{
    return true;
}
