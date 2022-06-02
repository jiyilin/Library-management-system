#include <stdio.h>
#include "Function.h"
int main()
{
    HeadmenuFunction();
    printf("谢谢使用\n");
    system("cls");
    logo();
    return 0;
}

char w_e_r_t = '\0';
int HeadMenu()
{
    char botton[30];
    int key;
    while (1)
    {
        printf("*= ================================================  =*\n");
        printf("|| *******欢迎使用福州大学至诚学院图书管理系统****** ||\n");
        printf("||    1.登录                                         ||\n");
        printf("||    2.注册                                         ||\n");
        printf("||    3.查看书籍                                     ||\n");
        printf("||    4.管理员系统                                   ||\n");
        printf("||    5.数据库导入                                   ||\n");
        printf("||    6.导入测试数据                                 ||\n");
        printf("||    0.退出                                         ||\n");
        printf("|| *******---------~~~~~~~~~~~~~~~~~~--------******* ||\n");
        printf("*= ================================================  =*\n");
        printf("请输入您需要的功能按钮:");
    again:
        gets_s(botton, 30);
        if (strlen(botton) == 0)
        {
            goto again;
        }
        else if (strlen(botton) > 1)
        {
            printf("输入错误,请重新输入\n");
            printf("请按任意键继续...");
            w_e_r_t = getchar();
            system("cls");
        }
        else
        {
            if (botton[0] != '0' && botton[0] != '1' && botton[0] != '2' && botton[0] != '3' &&
                botton[0] != '4' && botton[0] != '5' && botton[0] != '6')
            {
                printf("输入错误,请重新输入\n");
                printf("请按任意键继续...");
                w_e_r_t = getchar();
                system("cls");
            }
            else
            {
                break;
            }
        }
    }
    key = botton[0] - '0';
    return key;
}

void TimePrintf(char key[])
{
    char w_e_r_t;
    char clock[66];
    time_t now = time(0);
    ctime_s(clock, sizeof clock, &now);
    printf("*= =============================================================  =*\n");
    printf("||                                                                ||\n");
    printf("||                       Thanks for using it                      ||\n");
    printf("||                                                                ||\n");
    printf("                 现在是北京时间：%s", clock);
    printf("||                                                                ||\n");
    printf("||                                                                ||\n");
    printf("||                                                                ||\n");
    printf("*= =============================================================  =*\n");
    printf("请按任意键继续...");
    w_e_r_t = getchar();
    system("cls");
    strncpy_s(key, 66, clock, 66);
}

int AgainOnce()
{
    char botton[30];
    int key;
    while (1)
    {
        printf("还需要继续吗?[yes(1) ; no(0)]\n");
    againOut:
        gets_s(botton, 30);
        if (strlen(botton) == 0)
        {
            goto againOut;
        }
        else if (strlen(botton) > 1)
        {
            printf("输入错误,请重新输入\n");
        }
        else
        {
            if (botton[0] != '0' && botton[0] != '1')
            {
                printf("输入错误,请重新输入\n");
            }
            else
            {
                break;
            }
        }
    }
    key = botton[0] - '0';
    return key;
}

int UserMenu()
{
    char botton[30];
    int key;
    while (1)
    {
        printf("*= ================================================  =*\n");
        printf("|| *******------------------------------------****** ||\n");
        printf("|| ****欢迎使用福州大学至诚学院图书管理系统用户端*** ||\n");
        printf("|| *  1.借书                                       * ||\n");
        printf("|| *  2.还书                                       * ||\n");
        printf("|| *  3.修改密码                                   * ||\n");
        printf("|| *  0.退出                                       * ||\n");
        printf("|| *******---------~~~~~~~~~~~~~~~~~~--------******* ||\n");
        printf("*= ================================================  =*\n");
        printf("请输入您需要的功能按钮:");
    again:
        gets_s(botton, 30);
        if (strlen(botton) == 0)
        {
            goto again;
        }
        else if (strlen(botton) > 1)
        {
            printf("输入错误,请重新输入\n");
            printf("请按任意键继续...");
            w_e_r_t = getchar();
            system("cls");
        }
        else
        {
            if (botton[0] != '1' && botton[0] != '2' && botton[0] != '3' && botton[0] != '0')
            {
                printf("输入错误,请重新输入\n");
                printf("请按任意键继续...");
                w_e_r_t = getchar();
                system("cls");
            }
            else
            {
                break;
            }
        }
    }
    key = botton[0] - '0';
    return key;
}

void ReviseuserPassword(User* Active)
{
    char newPassword[20], againPassword[20];
    while (1)
    {
        printf("请输入新密码:");
        gets_s(newPassword, 20);
        printf("请再次输入新密码:");
        gets_s(againPassword, 20);
        if (!strcmp(newPassword, againPassword))
        {
            if (strcmp(newPassword, Active->password))
            {
                strcpy_s(Active->password, newPassword);
                printf("重置密码成功\n");
                return;
            }
            else
            {
                printf("新密码不能与旧密码一致\n");
            }
        }
        else
        {
            printf("输入错误,两次密码不一致\n");
        }
        printf("修改密码失败,请重新输入\n");
    }
}

int AdministratorMenu()
{
    char botton[30];
    int key;
    while (1)
    {
        printf("*= ================================================  =*\n");
        printf("|| *******---------~~~~~~~~~~~~~~~~~~--------******* ||\n");
        printf("||  == **** * 欢迎进入图书管理系统管理端  *  **** == ||\n");
        printf("||  == 1.书本录入                                 == ||\n");
        printf("||  == 2.书本查询                                 == ||\n");
        printf("||  == 3.下架书本                                 == ||\n");
        printf("||  == 4.用户录入                                 == ||\n");
        printf("||  == 5.用户查询                                 == ||\n");
        printf("||  == 6.用户删除                                 == ||\n");
        printf("||  == 7.用户借阅数据查询                         == ||\n");
        printf("||  == 0.退出管理系统                             == ||\n");
        printf("|| *******---------~~~~~~~~~~~~~~~~~~--------******* ||\n");
        printf("*= ================================================  =*\n");
        printf("请输入您需要的功能按钮:");
    again:
        gets_s(botton, 30);
        if (strlen(botton) == 0)
        {
            goto again;
        }
        else if (strlen(botton) > 1)
        {
            printf("输入错误,请重新输入\n");
            printf("请按任意键继续...");
            w_e_r_t = getchar();
            system("cls");
        }
        else
        {
            if (botton[0] != '0' && botton[0] != '1' && botton[0] != '2' &&
                botton[0] != '3' && botton[0] != '4' && botton[0] != '5' &&
                botton[0] != '6' && botton[0] != '7')
            {
                printf("输入错误,请重新输入\n");
                printf("请按任意键继续...");
                w_e_r_t = getchar();
                system("cls");
            }
            else
            {
                break;
            }
        }
    }
    key = botton[0] - '0';
    return key;
}

int AdministratorLoadChose()
{
    char botton[30];
    int key;
    while (1)
    {
        printf("*= ================================================  =*\n");
        printf("*= 1.登录                                            =*\n");
        printf("*= 2.注册                                            =*\n");
        printf("*= 3.查询                                            =*\n");
        printf("*= 4.修改管理员密码                                  =*\n");
        printf("*= 5.格式化数据库                                    =*\n");
        printf("*= ================================================  =*\n");
        printf("请输入您需要的功能按钮:");
    again:
        gets_s(botton, 30);
        if (strlen(botton) == 0)
        {
            goto again;
        }
        else if (strlen(botton) > 1)
        {
            printf("输入错误,请重新输入\n");
            printf("请按任意键继续...");
            w_e_r_t = getchar();
            system("cls");
        }
        else
        {
            if (botton[0] != '1' && botton[0] != '2' && botton[0] != '3' && botton[0] != '4' && botton[0] != '5')
            {
                printf("输入错误,请重新输入\n");
                printf("请按任意键继续...");
                w_e_r_t = getchar();
                system("cls");
            }
            else
            {
                break;
            }
        }
    }
    key = botton[0] - '0';
    return key;
}

int BorrowBookFrequency()
{
    char botton[30];
    int key;
    while (1)
    {
        printf("请输入需要借阅的书本数量(最多借6本):");
    again:
        gets_s(botton, 30);
        if (strlen(botton) == 0)
        {
            goto again;
        }
        else if (strlen(botton) > 1)
        {
            printf("输入错误,请重新输入\n");
        }
        else
        {
            if (botton[0] < '0' || botton[0] > '6')
            {
                printf("输入错误,请重新输入\n");
            }
            else
            {
                break;
            }
        }
    }
    key = botton[0] - '0';
    return key;
}

int ReturnBookFrequency()
{
    char botton[30];
    int key;
    while (1)
    {
        printf("请输入需要归还的书本数量(最多借6本):");
    again:
        gets_s(botton, 30);
        if (strlen(botton) == 0)
        {
            goto again;
        }
        else if (strlen(botton) > 1)
        {
            printf("输入错误,请重新输入\n");
        }
        else
        {
            if (botton[0] < '0' || botton[0] > '6')
            {
                printf("输入错误,请重新输入\n");
            }
            else
            {
                break;
            }
        }
    }
    key = botton[0] - '0';
    return key;
}

void ReadToTextLoad()
{
    if (LoadFirstAdministrator())
    {
        ReadToText();
    }
    else
    {
        printf("数据导入失败\n");
    }
}

void LibraryTextLoad()
{
    if (LoadFirstAdministrator())
    {
        LibraryText();
    }
    else
    {
        printf("数据导入失败\n");
    }
}

int LoadFirstAdministrator()
{
    char id[] = { "福州大学至诚学院" };
    char password[] = { "123456" };
    char process[20];
    printf("请输入第一管理员账号:");
    gets_s(process, 20);
    if (!strcmp(id, process))
    {
        printf("请输入第一管理员密码:");
        gets_s(process, 20);
        if (!strcmp(password, process))
        {
            printf("第一管理员登陆成功\n");
            return 1;
        }
        else
        {
            printf("密码错误,无法登录第一管理员\n");
        }
    }
    else
    {
        printf("账号错误,无法登录第一管理员\n");
    }
    return 0;
}

int SearchBookMenu()
{
    char botton[30];
    int key;
    while (1)
    {
        printf("*= ================================================= =*\n");
        printf("|| ----------------请选择查询方式------------------- ||\n");
        printf("||    1.按书名查询                                   ||\n");
        printf("||    2.按作者查询                                   ||\n");
        printf("||    3.查看全部书籍                                 ||\n");
        printf("|| ------------------------------------------------- ||\n");
        printf("*= ================================================= =*\n");
        printf("请输入您需要的功能按钮:");
    again:
        gets_s(botton, 30);
        if (strlen(botton) == 0)
        {
            goto again;
        }
        else if (strlen(botton) > 1)
        {
            printf("输入错误,请重新输入\n");
            printf("请按任意键继续...");
            w_e_r_t = getchar();
            system("cls");
        }
        else
        {
            if (botton[0] != '1' && botton[0] != '2' && botton[0] != '3')
            {
                printf("输入错误,请重新输入\n");
                printf("请按任意键继续...");
                w_e_r_t = getchar();
                system("cls");
            }
            else
            {
                break;
            }
        }
    }
    key = botton[0] - '0';
    return key;
}

void SearchBookFunction()
{
    switch (SearchBookMenu())
    {
    case 1:
        BookSearchName();
        break;
    case 2:
        BookSearchAuthor();
        break;
    case 3:
        BookSearchAll();
        break;
    }
}

void logo()
{
    printf("*= ============================================================== =*\n");
    printf("||             __/\\__         _   _________     _                 ||\n");
    printf("||          __/      \\__     | | |_______  \\___| |                ||\n");
    printf("||        _/  ________  \\_   | |         | |_____|                ||\n");
    printf("||        \\_ /        \\ _/   | |_________| |______                ||\n");
    printf("||         _|__________|_    | |_________   ______|               ||\n");
    printf("||        |______        |   | |______   | | __                   ||\n");
    printf("||              /       /    | |____  |  \\ \\/ /                   ||\n");
    printf("||             /       /     | |    | |   \\ \\/                    ||\n");
    printf("||            /_____  /      | |    | |  / \\ \\                    ||\n");
    printf("||         __/_____  /____   | |    | |  | |\\ \\__                 ||\n");
    printf("||        |_______________|  | |    | |  | | \\_  |                ||\n");
    printf("||         _______________   | |    | |  | |   | |                ||\n");
    printf("||        |_______________|  |_|    |_|  |_|   |_|                ||\n");
    printf("*= ============================================================== =*\n");
    printf("请按任意键继续...");
    w_e_r_t = getchar();
    system("cls");
}