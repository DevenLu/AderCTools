/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////
// action185��������[����ת
//////////////////////////

// ʶ��i++
//action 59  identifier ԭ����114, ����Ϊ185 ���ȼ���ԭ����97
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��һ�¼���״̬��������(1��117)
114			-=>223
144			-=>96
169
180
304
22


state : 114		Size : 3
primary-expression --> identifier   �� 		�� %=   &=   (   *   *=   +=   -=   /=   ;   <<=   =   >>=   ^=   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile   |=   }    ��
typedef-name --> identifier   �� 		�� %=   &=   (   *   *=   +=   -=   /=   ;   <<=   =   >>=   ^=   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile   |=   }    ��
labeled-statement --> identifier   �� :  statement  		�� %=   &=   (   *   *=   +=   -=   /=   ;   <<=   =   >>=   ^=   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile   |=   }    ��


state : 144		Size : 2
identifier-list --> identifier   �� 		�� (   )   *   ,   [   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile    ��
typedef-name --> identifier   �� 		�� (   )   *   ,   [   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile    ��


state : 169		Size : 2
primary-expression --> identifier   �� 		�� %=   &=   (   )   *   *=   +=   -=   /=   <<=   =   >>=   [   ^=   _Bool   _Complex   _Imaginary   bool   char   const   double   enum   float   identifier   int   long   restrict   short   signed   struct   union   unsigned   void   volatile   |=    ��
typedef-name --> identifier   �� 		�� %=   &=   (   )   *   *=   +=   -=   /=   <<=   =   >>=   [   ^=   _Bool   _Complex   _Imaginary   bool   char   const   double   enum   float   identifier   int   long   restrict   short   signed   struct   union   unsigned   void   volatile   |=    ��


state : 180		Size : 3
typedef-name --> identifier   �� 		�� %=   &=   (   *   *=   +=   -=   /=   ;   <<=   =   >>=   ^=   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile   |=   }    ��
primary-expression --> identifier   �� 		�� %=   &=   (   *   *=   +=   -=   /=   ;   <<=   =   >>=   ^=   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile   |=   }    ��
labeled-statement --> identifier   �� :  statement  		�� %=   &=   (   *   *=   +=   -=   /=   ;   <<=   =   >>=   ^=   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile   |=   }    ��

state : 304		Size : 2
typedef-name --> identifier   �� 		�� %=   &=   (   )   *   *=   +=   -=   /=   <<=   =   >>=   [   ^=   _Bool   _Complex   _Imaginary   bool   char   const   double   enum   float   identifier   int   long   restrict   short   signed   struct   union   unsigned   void   volatile   |=    ��
primary-expression --> identifier   �� 		�� %=   &=   (   )   *   *=   +=   -=   /=   <<=   =   >>=   [   ^=   _Bool   _Complex   _Imaginary   bool   char   const   double   enum   float   identifier   int   long   restrict   short   signed   struct   union   unsigned   void   volatile   |=    ��


state : 22		Size : 2
direct-declarator --> identifier   �� 		�� (   )   *   ,   ;   [   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile   {    ��
typedef-name --> identifier   �� 		�� (   )   *   ,   ;   [   _Bool   _Complex   _Imaginary   auto   bool   char   const   double   enum   extern   float   identifier   inline   int   long   register   restrict   short   signed   static   struct   typedef   union   unsigned   void   volatile   {    ��



//////////////////////////////////////////
// action169�������˶�+�� -����ת223
	{    ADD_OPERATE,                REDUCTION,      PRIMARY_EXPRESSION, 223,    },
    {    SUB_OPERATE,                REDUCTION,      PRIMARY_EXPRESSION, 223,    },
// ʶ��(a + b)
//action	85	identifier ԭ����169, ����Ϊ150 ���ȼ���ԭ����68	

//////////////////////////////////////////

/////////////////////////////////////////
103	for		0	112
103	goto		0	113
103	identifier		0	180  -=> 114
103	if		0	115
//////////////////////////////////////////

////////////////////////////////////////////////
387	for		0	112
387	goto		0	113
387	identifier		0	185
387	if		0	115
//////////////////////////////////////////////////








60	)		0	141
60	_Bool		0	3
60	_Complex		0	4
60	_Imaginary		0	5
60	auto		0	6
60	bool		0	7
60	char		0	8
60	const		0	9
60	double		0	14
60	enum		0	15
60	extern		0	17
60	float		0	19
60	identifier		0	144 -=> 22

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// һ�¼���״̬�ж�identifier�Ĵ����Ǵ����
32	// �Ѿ��޸�-=>ʶ�𲻴�����ֵ�ĺ�������
38	// ʶ��������ʽ��
37
161 // ʶ��ṹ��
160
21	// inline main(){ }


// �޸���action32[] 
// ʶ������������ֵ�Ķ���ʽ��
32	identifier		0	58
///////////////////////////////////////////////////////
32	(		1	declaration-specifiers	13
32	)		1	declaration-specifiers	13
32	*		1	declaration-specifiers	13
32	,		1	declaration-specifiers	13
32	;		1	declaration-specifiers	13
32	[		1	declaration-specifiers	13
32	_Bool		0	3
32	_Complex		0	4
32	_Imaginary		0	5
32	auto		0	6
32	bool		0	7
32	char		0	8
32	const		0	9
32	double		0	14
32	enum		0	15
32	extern		0	17
32	float		0	19
32	identifier		0	58///////////////////


// ʶ��������ʽ��
38	[		1	declaration-specifiers	15
38	_Bool		0	3
38	_Complex		0	4
38	_Imaginary		0	5
38	auto		0	6
38	bool		0	7
38	char		0	8
38	const		0	9
38	double		0	14
38	enum		0	15
38	extern		0	17
38	float		0	19
38	identifier		0	58////////////////

// ʶ��ṹ��
161	(		1	specifier-qualifier-list	58
161	)		1	specifier-qualifier-list	58
161	*		1	specifier-qualifier-list	58
161	:		1	specifier-qualifier-list	58
161	[		1	specifier-qualifier-list	58
161	_Bool		0	3
161	_Complex		0	4
161	_Imaginary		0	5
161	bool		0	7
161	char		0	8
161	const		0	9
161	double		0	14
161	enum		0	15
161	float		0	19
161	identifier		0	58/////////////////////













