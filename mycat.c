#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main()
{
    printf("> hello to mycat program <3\n");
    printf("> ====================== <\n");
    printf("> Type ./mycat filename -> show file content\n");
    printf("> Type ./mycat filename file2name etc. -> show files content\n");
    printf("> Type ./mycat <filename> file2name -> copy content from 1 to 2\n");
    printf("> Type ./mycat -> take keyboard input and print it to stdn\n");
    printf("> ====================== <\n\n");

    // printf("hello to mycat program <3");
    // printf("hello to mycat program <3");
    // printf("hello to mycat program <3");
    // printf("hello to mycat program <3");

    char STNDcommand[8] = "./mycat ";

    char input[1024];
    char ch;    

    int i = 0;
    ch = getchar();
    while (ch != '\n')
    {
        input[i] = ch;
        i++;
        ch = getchar();
    }
    input[i] = '\0';

    for (int i = 0; i < 8; i++)
    {
        if (input[i] != STNDcommand[i])
        {
            printf("Command syntax is wrong pls try again :( \n");
            exit(1);
        }
    }

    char file[1024];
    strncpy(file, input + 8, strlen(input));

    if (strlen(file) == 0)
    {
        while(1)
        {
            char infinitIN[1024];
            scanf("%s", infinitIN);
            printf("%s\n", infinitIN);
        }
    }

    printf("\n%s:\n", file);
    for (int i = 0; i < strlen(file)+1; i++)
        printf("%c", '-');
    printf("\n");

    int j = 1;

    for (int i = 0; i < strlen(file); i++)
    {
        if (file[i] == ' ')
        {
            j++;
            continue;
        }
    }

    char files[j][40];
    j = 0;
    int k = -1;

    for (int i = 0; i < strlen(file); i++)
    {
        if (file[i] == ' ')
        {
            files[j][k+1] = '\0';
            k = -1;
            j++;
        }
        else
        {
            k++;
            files[j][k] = file[i];
        }
    }
    files[j][k + 1] = '\0';

    for (int i = 0; i < j+1; i++)
    {
        char buff[1024];
        for (int i = 0; i < 1024; i++) { buff[i] = '\0'; }

        if (files[i][0] == '<' && files[i][strlen(files[i])-1] == '>')
        {
            char fileFrom[40];
            strncpy(fileFrom, files[i] + 1, strlen(files[i]) - 2);
            fileFrom[strlen(files[i])-2] = '\0';

            int writefrom = open(fileFrom, O_RDWR);
            int dataTOwrite = read(writefrom, buff, 1024);

            int writeTO = open(files[i+1], O_WRONLY);
            write(writeTO, buff, strlen(buff));
            exit(1);
        }

        int openID = open(files[i], O_RDWR);
        int readID = read(openID, buff, 1024);

        if (openID == -1)
        {
            perror("Program");
        }
        else
        {
            if (readID == -1)
            {
                perror("An error occurred while trying to read the file, ");
            }
            else
            {
                printf("%s", buff);

                int closeID = close(openID);

                if (closeID == -1)
                {
                    perror("\nProgram\n");
                    exit(1);
                }
                for (int i = 0; i < 1024; i++) { buff[i] = '\0'; }
            }
        }
    }
    printf("\n");

    return 0;
}