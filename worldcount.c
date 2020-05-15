#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    int char_count = 0, world_count = 0; //字符的数量，单词的数量
    FILE *fp;                            //文件指针
    char buf[1024];                      //缓冲，存放每一行所有的字符
    char c;
    if (argc < 3)
    {
        printf("参数不足，请输入控制参数及文件名\n");
        exit(1);
    }

    if ((fp = fopen(argv[2], "r")) == NULL)
    {
        printf("文件打开失败!\n");
        exit(1);
    }

    if (strcmp(argv[1], "-c") == 0) //统计字符数
    {
        while ((c = fgetc(fp)) != EOF)
            char_count++;
        fclose(fp);
        printf("字符数：%d\n", char_count);
        return 0;
    }

    // 统计单词数
    else if ((strcmp(argv[1], "-w")) == 0)
    {
        // 读取一行放入buf
        int len = 0;
        while (fgets(buf, 1024, fp) != NULL)
        {
            if (buf[0] == '\n')
                continue;
            int flag = 1;      //上一个字符是否为空格或者逗号，1--是，0--否
            len = strlen(buf); //实际长度
            for (int i = 0; i < len; i++)
            {
                c = buf[i];
                if (c == ' ' || c == ',')
                {
                    // 上一个不是空格，但是当前是空格
                    
                    if (flag == 0)
                    {
                        world_count++;
                    }
                    flag = 1;
                    //printf("%d\n",flag);
                }
                else if (c != '\n' && c != '\r' )
                {
                    flag = 0;
                }

                // 边界控制
                if (i == len - 1 && flag == 0)
                    world_count++;
            }
        }
        fclose(fp);
        printf("单词数:%d\n", world_count);
        return 0;
    }
}