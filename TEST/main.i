int main(void)
{

    char sourFile[MAX_STR_SIZE];

    while(printf("�����������Դ�ļ���:"), scanf("%s", sourFile) != (-1))
    {
        Lexical(sourFile);
    }

    return 0;
}
