

#ifndef CTOOLS_H_INCLUDED
#define CTOOLS_H_INCLUDED




/// �����ļ���Ϣ
#include "..\Config\Config.h"                // ���ù���


/// ȫ�ֽӿ�
#include "..\Tools\Errors.h"               // ������ӿ�
#include "..\Tools\Files.h"                 // �ļ�����ӿ�

/// ������Ϣ
#include "..\Tools\Buffer.h"               // ˫������

/// �ʷ�������
//#include "..\Lexical\BinaryTuple.h"         // �ʷ���Ԫ��ӿ�
#include "..\Lexical\Lexical.h"             // �ʷ����������س���

/// �﷨������
#include "..\Parser\Parser.h"               // �﷨�������س���

/// ���ű���Ϣ
#include "..\Table\SymbolTable.h"

/// ��׮����Ϣ
#include "..\Prop\Prop.h"

/// �궨�庯���Ķ��巽ʽ��Ϣ
#ifndef PUBLIC_and_PRIVATE
#define PUBLIC_and_PRIVATE
#
#define PUBLIC  extern          // �������Ա�������
#define PRIVATE static      // ����ֻ�ܱ����ļ��ĺ�������
#
#endif





#endif // CTOOLS_H_INCLUDED
