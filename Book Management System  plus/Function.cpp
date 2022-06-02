#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Function.h"

char w_e_r = '\0';
char StartTime[66] = { 0 };
char OutTime[66] = { 0 };
int readTxtAlready = 0;
Book* AllBookDate;
Book* BookDate;
User* UserDate;
Administrator* AdministratorDate;

void HeadmenuFunction()
{
    char start[20] = { '\0' };
    AllBookDate = (Book*)malloc(sizeof(Book));
    if (AllBookDate == NULL)
    {
        printf("内存分配不成功！\n");
        printf("请联系管理员\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
    else
    {
        strcpy_s(AllBookDate->name, start);
        strcpy_s(AllBookDate->author, start);
        strcpy_s(AllBookDate->press, start);
        AllBookDate->next = NULL;
    }
    BookDate = (Book*)malloc(sizeof(Book));
    if (BookDate == NULL)
    {
        printf("内存分配不成功！\n");
        printf("请联系管理员\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
    else
    {
        strcpy_s(BookDate->author, start);
        strcpy_s(BookDate->name, start);
        strcpy_s(BookDate->press, start);
        BookDate->next = NULL;
    }
    UserDate = (User*)malloc(sizeof(User));
    if (UserDate == NULL)
    {
        printf("内存分配不成功！\n");
        printf("请联系管理员\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
    else
    {
        strcpy_s(UserDate->name, start);
        strcpy_s(UserDate->password, start);
        strcpy_s(UserDate->phone, start);
        UserDate->returnnumber = 0;
        UserDate->next = NULL;
    }
    AdministratorDate = (Administrator*)malloc(sizeof(Administrator));
    if (AdministratorDate == NULL)
    {
        printf("内存分配不成功！\n");
        printf("请联系管理员\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
    else
    {
        strcpy_s(AdministratorDate->name, start);
        strcpy_s(AdministratorDate->password, start);
        AdministratorDate->next = NULL;
    }
    TimePrintf(StartTime);
    while (1)
    {
        switch (HeadMenu())
        {
        case 0:
            goto out;
            break;
        case 1:
            UsermenuFunction();
            break;
        case 2:
            RegisterUser();
            break;
        case 3:
            SearchBookFunction();
            break;
        case 4:
            AdministratorFunciton();
            break;
        case 5:
            ReadToTextLoad();
            printf("请按任意键继续...");
            w_e_r = getchar();
            break;
        case 6:
            LibraryTextLoad();
            printf("请按任意键继续...");
            w_e_r = getchar();
            break;
        }
        system("cls");
    }
out:
    system("cls");
    TimePrintf(OutTime);
    OutSystem();
}

void UsermenuFunction()
{
    User* Active;
    Active = (User*)malloc(sizeof(User));
    if (UserDate->next == NULL)
    {
        printf("查找失败!不存在用户信息!\n");
        printf("请先完成注册\n");
        RegisterUser();
    }
    Active = UserLoad();
    if (Active != UserDate)
    {
        while (1)
        {
            switch (UserMenu())
            {
            case 0:
                goto out;
                break;
            case 1:
                BorrowBook(Active->name);
                if (!AgainOnce())
                {
                    goto out;
                }
                break;
            case 2:
                ReturnBook(Active->name);
                if (!AgainOnce())
                {
                    goto out;
                }
                break;
            case 3:
                ReviseuserPassword(Active);
                if (!AgainOnce())
                {
                    goto out;
                }
                break;
            }
            system("cls");
        }
    }
out:
    printf("您已退出福州大学至诚学院图书管理系统用户端\n");
    printf("请按任意键继续...");
    w_e_r = getchar();
    system("cls");
}

User* UserLoad()
{
    User* search;
    search = (User*)malloc(sizeof(User));
    char process[30];
    int flag = 0;
    search = UserDate;
    printf("请输入账号:");
    gets_s(process, 30);
    while (search->next != NULL)
    {
        search = search->next;
        if (!strcmp(search->name, process))
        {
            flag = 1;
        }
    }
    if (flag == 1)
    {
        printf("请输入密码:");
        gets_s(process, 30);
        if (!strcmp(search->password, process))
        {
            printf("登录成功\n");
            return search;
            printf("请按任意键继续...");
            w_e_r = getchar();
            system("cls");
        }
        else
        {
            printf("密码错误\n");
        }
    }
    else
    {
        printf("没有此用户\n");
    }
    printf("登录失败\n");
    return UserDate;
}

void DeleteUser()
{
    User* search;
    search = (User*)malloc(sizeof(User));
    search = UserDate;
    if (search->next == NULL)
    {
        printf("删除失败！不存在用户信息！\n");
    }
    else
    {
        printf("-------------------------------------------------------------\n");
        int Iterator = 1;
        while (search->next != NULL)
        {
            search = search->next;
            printf("%d  %-20s%-20s\n", Iterator, search->name, search->password);
            Iterator++;
        }
        printf("-------------------------------------------------------------\n");
        search = UserDate;
        char process[30];
        while (1)
        {
            printf("请输入要删除的用户名：");
            gets_s(process, 30);
            while (search->next != NULL)
            {
                search = search->next;
                if (!strcmp(search->name, process))
                {
                    if (search->returnnumber != 0)
                    {
                        printf("此用户还有未归还的图书,无法删除\n");
                        printf("此用户的联系方式为:%s\n", search->phone);
                    }
                    else
                    {
                        User* p;
                        p = (User*)malloc(sizeof(User));
                        p = UserDate;
                        while (p->next != search)
                        {
                            p = p->next;
                        }
                        p->next = search->next;
                        printf("删除成功\n");
                    }
                    return;
                }
            }
            printf("没有此用户,请重新输入\n");
        }
    }
    printf("请按任意键继续...");
    w_e_r = getchar();
}

void PrintUser()
{
    if (UserDate->next == NULL)
    {
        printf("没有用户数据\n");
    }
    else
    {
        User* search;
        search = (User*)malloc(sizeof(User));
        search = UserDate;
        int Iterator = 1;
        printf("----------------------------------用户名单-------------------------------\n");
        while (search->next != NULL)
        {
            search = search->next;
            printf("%d  %-20s%-20s    已借阅%d本书\n", Iterator, search->name, search->password,search->returnnumber);
            Iterator++;
        }
        printf("-------------------------------------------------------------------------\n");
    }
}

void RegisterUser()
{
    User* node, * search;
    int flag = 1;
    node = (User*)malloc(sizeof(User));
    if (node == NULL)
    {
        printf("内存分配不成功！\n");
        printf("请联系管理员\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
    else
    {
        search = (User*)malloc(sizeof(User));
        if (search == NULL)
        {
            printf("内存分配不成功！\n");
            printf("请联系管理员\n");
            printf("请按任意键继续...");
            w_e_r = getchar();
        }
        else
        {
            printf("请输入用户名:");
            gets_s(search->name, 20);
            node = UserDate;
            while (node->next != NULL)
            {
                node = node->next;
                if (!strcmp(node->name, search->name))
                {
                    flag = 0;
                }
            }
            node = UserDate;
            while (node->next != NULL)
            {
                node = node->next;
            }
            if (!flag)
            {
                printf("该用户已存在,注册失败\n");
                printf("请按任意键继续...");
                w_e_r = getchar();
            }
            else
            {
                printf("请输入密码:");
                gets_s(search->password, 20);
                printf("请输入联系方式:");
                gets_s(search->phone, 30);
                search->returnmenu = (Book*)malloc(sizeof(Book));
                if (search->returnmenu == NULL)
                {
                    printf("内存分配不成功！\n");
                    printf("请联系管理员\n");
                    printf("请按任意键继续...");
                    w_e_r = getchar();
                }
                else
                {
                    search->returnmenu = (Book*)malloc(sizeof(Book));
                    if (search->returnmenu == NULL)
                    {
                        printf("内存分配不成功！\n");
                        printf("请联系管理员\n");
                        printf("请按任意键继续...");
                        w_e_r = getchar();
                    }
                    else
                    {
                        search->returnmenu->next = NULL;
                    }
                    search->returnnumber = 0;
                    search->next = NULL;
                    node->next = search;
                    printf("注册成功\n");
                    printf("请按任意键继续...");
                    w_e_r = getchar();
                }
            }
        }
    }
}

void Input_Book()
{
    Book* node, * search;
    int flag = 1;
    node = (Book*)malloc(sizeof(Book));
    search = (Book*)malloc(sizeof(Book));
    if (search == NULL)
    {
        printf("内存分配不成功！\n");
        printf("请联系管理员\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
    else
    {
        printf("请输入书名:");
        gets_s(search->name, 20);
        node = AllBookDate;
        while (node->next != NULL)
        {
            node = node->next;
            if (!strcmp(node->name, search->name))
            {
                flag = 0;
            }
        }
        if (!flag)
        {
            printf("该图书已存在,录入失败\n");
        }
        else
        {
            printf("请输入作者:");
            gets_s(search->author, 20);
            printf("请输入出版社名:");
            gets_s(search->press, 50);
            search->next = NULL;
            node = AllBookDate;
            while (node->next != NULL)
            {
                node = node->next;
            }
            node->next = search;
            Book* p;
            p = (Book*)malloc(sizeof(Book));
            if (p == NULL)
            {
                printf("内存分配不成功！\n");
                printf("请联系管理员\n");
                printf("请按任意键继续...");
                w_e_r = getchar();
            }
            else
            {
                strcpy_s(p->author, search->author);
                strcpy_s(p->name, search->name);
                strcpy_s(p->press, search->press);
                p->next = NULL;
                node = BookDate;
                while (node->next != NULL)
                {
                    node = node->next;
                }
                node->next = p;
                printf("录入成功\n");
            }
        }
    }
}

void BookSearchAll()
{
    if (AllBookDate->next == NULL)
    {
        printf("此书库无图书\n");
    }
    else
    {
        int flag;
        Book* search, * p;
        search = AllBookDate;
        printf("*= =====================================书库数据==================================== =*\n");
        while (search->next != NULL)
        {
            flag = 0;
            search = search->next;
            p = BookDate;
            while (p->next != NULL)
            {
                p = p->next;
                if (!strcmp(p->name, search->name))
                {
                    flag = 1;
                    break;
                }
            }
            if (flag == 1)
            {
                printf("|| %-30s %-20s %-20s  可借阅  ||\n", search->name, search->author, search->press);
            }
            else
            {
                printf("|| %-30s %-20s %-20s  已借阅  ||\n", search->name, search->author, search->press);
            }
        }
        printf("*= ================================================================================= =*\n");
    }
    printf("请按任意键继续...");
    w_e_r = getchar();
}

void DelBooksFunction()
{
    if (AllBookDate->next == NULL)
    {
        printf("删除失败！不存在图书信息！\n");
    }
    else
    {
        char process[30];
        int flag = 0;
        Book* search;
        search = (Book*)malloc(sizeof(Book));
        search = AllBookDate;
        while (search->next != NULL)
        {
            search = search->next;
            printf("%-30s %-20s %-20s\n", search->name, search->author, search->press);
        }
        printf("请输入要删除的书名：");
        gets_s(process, 30);
        search = AllBookDate;
        while (search->next != NULL)
        {
            search = search->next;
            if (!strcmp(search->name, process))
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("没有这本图书,无法删除\n");
        }
        else
        {
            char botton[30];
            int key;
            while (1)
            {
                printf("确认删除吗(是'1',否'0'): ");
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
            if (key)
            {
                Book* p;
                p = (Book*)malloc(sizeof(Book));
                p = AllBookDate;
                while (p->next->next == search)
                {
                    p = p->next;
                }
                p->next = search->next;
                p = BookDate;
                while (p->next == search)
                {
                    p = p->next;
                }
                p->next = search->next;
                printf("删除图书信息成功！\n");
            }
        }
    }
}

void OutSystem()
{
    WriteToText();
    printf("请按任意键继续...");
    w_e_r = getchar();
    system("cls");
    printf("本次使用的数据如下:\n");
    if (AllBookDate->next == NULL && UserDate->next == NULL && AdministratorDate->next == NULL)
    {
        printf("空\n");
    }
    else
    {
        Book* searchBook;
        User* searchUser;
        Administrator* searchAdministrator;
        searchBook = (Book*)malloc(sizeof(Book));
        searchUser = (User*)malloc(sizeof(User));
        searchAdministrator = (Administrator*)malloc(sizeof(Administrator));
        searchBook = AllBookDate;
        searchUser = UserDate;
        searchAdministrator = AdministratorDate;
        printf("                             <<图书数据>>\n");
        if (AllBookDate->next == NULL)
        {
            printf("空\n");
        }
        else
        {
            printf("*= =================================================================== =*\n");
            while (searchBook->next != NULL)
            {
                searchBook = searchBook->next;
                printf("%-30s %-20s %-20s\n", searchBook->name, searchBook->author, searchBook->press);
            }
            printf("*= =================================================================== =*\n");
        }
        printf("                             <<用户数据>>\n");
        if (UserDate->next == NULL)
        {
            printf("空\n");
        }
        else
        {
            printf("*= =================================================================== =*\n");
            while (searchUser->next != NULL)
            {
                searchUser = searchUser->next;
                printf("%-20s%-20s%-30s\n", searchUser->name, searchUser->password, searchUser->phone);
            }
            printf("*= =================================================================== =*\n");
        }
        printf("                             <<管理员数据>>\n");
        if (searchAdministrator->next == NULL)
        {
            printf("空\n");
        }
        else
        {
            printf("*= =================================================================== =*\n");
            while (searchAdministrator->next != NULL)
            {
                searchAdministrator = searchAdministrator->next;
                printf("%-20s%-20s\n", searchAdministrator->name, searchAdministrator->password);
            }
            printf("*= =================================================================== =*\n");
        }
    }
    printf("<<此次福州大学至诚学院图书管理系统运行时间>>\n");
    printf("开始时间:%s\n",StartTime);
    printf("结束时间:%s\n",OutTime);
    printf("请按任意键继续...");
    w_e_r = getchar();
}

int AdministratorLoad()
{
    Administrator* node, process = { '\0' };
    node = (Administrator*)malloc(sizeof(Administrator));
    printf("请输入管理员账号:");
    gets_s(process.name, 20);
    printf("请输入管理员密码:");
    gets_s(process.password, 20);
    node = AdministratorDate;
    while (node->next != NULL)
    {
        node = node->next;
        if ((!strcmp(node->name, process.name)) && (!strcmp(node->password, process.password)))
        {
            printf("登录成功\n");
            printf("请按任意键继续...");
            w_e_r = getchar();
            system("cls");
            return 1;
        }
    }
    printf("账号密码错误,登录失败\n");
    return 0;
}

int RegisterAdministrator11()
{
    if (LoadFirstAdministrator())
    {
        Administrator* node, * search;
        int flag = 1;
        node = (Administrator*)malloc(sizeof(Administrator));
        search = (Administrator*)malloc(sizeof(Administrator));
        if (search == NULL)
        {
            printf("内存分配不成功！\n");
            printf("请联系管理员\n");
            printf("请按任意键继续...");
            w_e_r = getchar();
        }
        else
        {
            printf("请输入用户名:");
            gets_s(search->name, 20);
            node = AdministratorDate;
            while (node->next != NULL)
            {
                node = node->next;
                if (!strcmp(node->name, search->name))
                {
                    flag = 0;
                }
            }
            node = AdministratorDate;
            while (node->next != NULL)
            {
                node = node->next;
            }
            if (!flag)
            {
                printf("该用户已存在,注册失败\n");
                printf("请按任意键继续...");
                w_e_r = getchar();
                return 0;
            }
            else
            {
                printf("请输入密码:");
                gets_s(search->password, 20);
                search->next = NULL;
                node->next = search;
                printf("注册成功\n");
                printf("请按任意键继续...");
                w_e_r = getchar();
                return 1;
            }
        }
    }
    else
    {
        printf("注册失败\n");
    }
    return 0;
}

void AdministratorFunciton()
{
    int flag = 1;
    switch (AdministratorLoadChose())
    {
    case 1:
        if (AdministratorDate->next == NULL)
        {
            printf("查找失败!不存在管理员信息!\n");
            printf("请先完成注册\n");
            flag = RegisterAdministrator11();
        }
        if (flag)
        {
            if (AdministratorLoad())
            {
                while (1)
                {
                    switch (AdministratorMenu())
                    {
                    case 0:
                        goto out;
                        break;
                    case 1:
                        Input_Book();
                        if (!AgainOnce())
                        {
                            goto out;
                        }
                        break;
                    case 2:
                        SearchBookFunction();
                        if (!AgainOnce())
                        {
                            goto out;
                        }
                        break;
                    case 3:
                        DelBooksFunction();
                        if (!AgainOnce())
                        {
                            goto out;
                        }
                        break;
                    case 4:
                        RegisterUser();
                        if (!AgainOnce())
                        {
                            goto out;
                        }
                        break;
                    case 5:
                        PrintUser();
                        if (!AgainOnce())
                        {
                            goto out;
                        }
                        break;
                    case 6:
                        DeleteUser();
                        if (!AgainOnce())
                        {
                            goto out;
                        }
                        break;
                    case 7:
                        UserBorrowingDataQuery();
                        if (!AgainOnce())
                        {
                            goto out;
                        }
                        break;
                    }
                    system("cls");
                }
            }
            else
            {
                goto out;
            }
        }
        printf("请按任意键继续...");
        w_e_r = getchar();
        break;
    case 2:
        RegisterAdministrator11();
        break;
    case 3:
        PrintfAdministrator();
        break;
    case 4:
        ReviseuserPasswordAdministrator();
        break;
    case 5:
        Initialization();
        break;
    out:
        printf("您已成功退出福州大学至诚学院图书管理系统管理员端\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
        system("cls");
    }
}
void BorrowBook(char key[20])
{
    User* search;
    search = UserDate;
    while (search->next != NULL)
    {
        search = search->next;
        if (!strcmp(search->name, key))
        {
            break;
        }
    }
    if (BookDate->next == NULL)
    {
        printf("没有书本\n");
    }
    else
    {
        if (search->returnnumber == 6)
        {
            printf("您已借阅6本书,请归还后再进行借阅\n");
        }
        else
        {
            int frequency, number = 1;
            frequency = BorrowBookFrequency();
            while (number <= frequency)
            {
                if (BorrowBookFunction11(key))
                {
                    printf("第%d本借书完成\n", number);
                    search->returnnumber++;
                    number++;
                }
                else
                {
                    printf("第%d本借书失败\n", number);
                    number++;
                }
            }
            printf("全部借书完成\n");
        }
        Book* p;
        p = BookDate;
        printf("-----------------------------书库数据-----------------------------------\n");
        while (p->next != NULL)
        {
            p = p->next;
            printf("%-30s %-20s %-20s\n", p->name, p->author, p->press);
        }
        printf("------------------------------------------------------------------------\n");
    }
}

void ReturnBook(char key[20])
{
    User* Active;
    Active = UserDate;
    while (Active->next != NULL)
    {
        Active = Active->next;
        if (!strcmp(Active->name, key))
        {
            break;
        }
    }
    if (Active->returnnumber == 0)
    {
        printf("此用户还未借书,不需要归还\n");
    }
    else
    {
        int frequency, number = 1;
        frequency = ReturnBookFrequency();
        while (number <= frequency)
        {
            if (ReturnBookFunction11(Active->name))
            {
                printf("第%d本还书完成\n", number);
                Active->returnnumber--;
                number++;
            }
            else
            {
                printf("第%d本还书失败\n", number);
                number++;
            }
        }
        printf("全部还书完成\n");
    }
}

int BorrowBookFunction11(char key[20])
{
    User* Active;
    Active = UserDate;
    while (Active->next != NULL)
    {
        Active = Active->next;
        if (!strcmp(Active->name, key))
        {
            break;
        }
    }
    char process[30];
    Book* search;
    search = (Book*)malloc(sizeof(Book));
    search = BookDate;
    printf("-------------------可借阅书库目录-------------------------\n");
    while (search->next != NULL)
    {
        search = search->next;
        printf("%-30s %-20s %-20s\n", search->name, search->author, search->press);
    }
    printf("----------------------------------------------------------\n");
    printf("请输入需要借阅的书名:");
    gets_s(process, 30);
    int flag = 0;
    search = BookDate;
    while (search->next != NULL)
    {
        search = search->next;
        if (!strcmp(search->name, process))
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        Book* p;
        p = BookDate;
        while (p->next != search)
        {
            p = p->next;
        }
        p->next = search->next;
        search->next = NULL;
        Book* end;
        end = Active->returnmenu;
        while (end->next != NULL)
        {
            end = end->next;
        }
        end->next = search;
        return 1;
    }
    else
    {
        return 0;
    }
}

int ReturnBookFunction11(char key[20])
{
    User* Active;
    Active = UserDate;
    while (Active->next != NULL)
    {
        Active = Active->next;
        if (!strcmp(Active->name, key))
        {
            break;
        }
    }
    char process[30];
    Book* search;
    search = (Book*)malloc(sizeof(Book));
    search = Active->returnmenu;
    printf("-------------------借阅记录-------------------------\n");
    while (search->next != NULL)
    {
        search = search->next;
        printf("%-30s %-20s %-20s\n", search->name, search->author, search->press);
    }
    printf("----------------------------------------------------\n");
    printf("请输入需要归还的书名:");
    gets_s(process, 30);
    int flag = 0;
    search = Active->returnmenu;
    while (search != NULL)
    {
        if (!strcmp(search->name, process))
        {
            flag = 1;
            break;
        }
        search = search->next;
    }
    if (flag)
    {
        Book* p;
        p = BookDate;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = search;
        p = Active->returnmenu;
        if (p->next == NULL)
        {
            Active->returnmenu = search;
        }
        else
        {
            while (p->next != search)
            {
                p = p->next;
            }
            p->next = search->next;
        }
        return 1;
    }
    else
    {
        printf("您未借阅这本图书,请重新输入\n");
    }
    return 0;
}

void LibraryText()
{
    if (readTxtAlready==1)
    {
        printf("您已成功导入数据，无法再次导入\n");
    }
    else
    {
        int success = 0;
        FILE* UserDataText;
        errno_t err;
        if ((err = fopen_s(&UserDataText, "UserDataText.txt", "r")) != 0)
        {
            printf("打开用户文件失败！\n");
        }
        else
        {
            if (UserDataText != NULL)
            {
                int UserDataNumber;
                fscanf_s(UserDataText, "%d\n", &UserDataNumber);
                User* node, * search;
                search = (User*)malloc(sizeof(User));
                search = UserDate;
                while (search->next != NULL)
                {
                    search = search->next;
                }
                for (int i = 0; i < UserDataNumber; i++)
                {
                    node = (User*)malloc(sizeof(User));
                    fscanf_s(UserDataText, "%20s %20s %30s\n", &node->name, 20, &node->password, 20, &node->phone, 30);
                    node->returnnumber = 0;
                    node->returnmenu = (Book*)malloc(sizeof(Book));
                    if (node->returnmenu == NULL)
                    {
                        printf("内存分配不成功！\n");
                        printf("请联系管理员\n");
                        printf("请按任意键继续...");
                        w_e_r = getchar();
                    }
                    else
                    {
                        node->returnmenu->next = NULL;
                    }
                    search->next = node;
                    search = node;
                }
                search->next = NULL;
                fclose(UserDataText);
                success++;
                printf("已成功导入用户文件\n");
            }
            else
            {
                printf("打开用户文件失败！\n");
            }
        }
        FILE* BookDateText;
        if ((err = fopen_s(&BookDateText, "BookDataText.txt", "r")) != 0)
        {
            printf("打开图书文件失败！\n");
        }
        else
        {
            if (BookDateText != NULL)
            {
                int BookDataNumber;
                fscanf_s(BookDateText, "%d\n", &BookDataNumber);
                Book* node, * search, * p, * p_s;
                search = (Book*)malloc(sizeof(Book));
                p_s = (Book*)malloc(sizeof(Book));
                search = AllBookDate;
                p_s = BookDate;
                while (search->next != NULL)
                {
                    search = search->next;
                }
                while (p_s->next != NULL)
                {
                    p_s = p_s->next;
                }
                for (int i = 0; i < BookDataNumber; i++)
                {
                    node = (Book*)malloc(sizeof(Book));
                    p = (Book*)malloc(sizeof(Book));
                    fscanf_s(BookDateText, "%30s %20s %50s\n", &node->name, 30, &node->author, 20, &node->press, 50);
                    strcpy_s(p->author, node->author);
                    strcpy_s(p->name, node->name);
                    strcpy_s(p->press, node->press);
                    p->next = NULL;
                    node->next = NULL;
                    search->next = node;
                    p_s->next = p;
                    search = node;
                    p_s = p;
                }
                fclose(BookDateText);
                success++;
                printf("已成功导入图书文件\n");
            }
            else
            {
                printf("打开图书文件失败！\n");
            }
        }
        FILE* AdministratorDateText;
        if ((err = fopen_s(&AdministratorDateText, "AdministratorDataText.txt", "r")) != 0)
        {
            printf("打开管理员文件失败！\n");
        }
        else
        {
            if (AdministratorDateText != NULL)
            {
                int AdministratorDataNumber;
                fscanf_s(AdministratorDateText, "%d\n", &AdministratorDataNumber);
                Administrator* node, * search;
                search = (Administrator*)malloc(sizeof(Administrator));
                search = AdministratorDate;
                while (search->next != NULL)
                {
                    search = search->next;
                }
                for (int i = 0; i < AdministratorDataNumber; i++)
                {
                    node = (Administrator*)malloc(sizeof(Administrator));
                    if (node == NULL)
                    {
                        printf("内存分配不成功！\n");
                        printf("请联系管理员\n");
                        printf("请按任意键继续...");
                        w_e_r = getchar();
                    }
                    else
                    {
                        fscanf_s(AdministratorDateText, "%20s %30s\n", &node->name, 20, &node->password, 30);
                        search->next = node;
                        search = node;
                    }
                }
                search->next = NULL;
                fclose(AdministratorDateText);
                success++;
                printf("已成功导入管理员文件\n");
            }
            else
            {
                printf("打开管理员文件失败！\n");
            }
        }
        if (success == 3)
        {
            printf("已成功导入测试数据\n");
            printf("请按任意键继续...");
            w_e_r = getchar();
            system("cls");
            TextPrintf();
        }
        readTxtAlready = 1;
    }
}

void ReadToText()
{
    if (readTxtAlready == 1)
    {
        printf("您已成功导入数据，无法再次导入\n");
    }
    else
    {
        int success = 0;
        errno_t err;
        FILE* UserDataText;
        if ((err = fopen_s(&UserDataText, "UserData.txt", "r")) != 0)
        {
            printf("打开用户文件失败！\n");
        }
        else
        {
            if (UserDataText != NULL)
            {
                int UserDataNumber;
                fscanf_s(UserDataText, "%d\n", &UserDataNumber);
                User* node, * search;
                search = (User*)malloc(sizeof(User));
                search = UserDate;
                while (search->next != NULL)
                {
                    search = search->next;
                }
                for (int i = 0; i < UserDataNumber; i++)
                {
                    node = (User*)malloc(sizeof(User));
                    fscanf_s(UserDataText, "%20s %20s %30s\n", &node->name, 20, &node->password, 20, &node->phone, 30);
                    node->returnnumber = 0;
                    node->returnmenu = (Book*)malloc(sizeof(Book));
                    if (node->returnmenu == NULL)
                    {
                        printf("内存分配不成功！\n");
                        printf("请联系管理员\n");
                        printf("请按任意键继续...");
                        w_e_r = getchar();
                    }
                    else
                    {
                        node->returnmenu->next = NULL;
                    }
                    search->next = node;
                    search = node;
                    BorrowBookTextR(search);
                }
                search->next = NULL;
                fclose(UserDataText);
                success++;
                printf("已成功导入用户文件\n");
            }
            else
            {
                printf("打开用户文件失败！\n");
            }
        }
        FILE* BookDateText;
        if ((err = fopen_s(&BookDateText, "BookData.txt", "r")) != 0)
        {
            printf("打开动态图书文件失败！\n");
        }
        else
        {
            if (BookDateText != NULL)
            {
                int BookDataNumber;
                fscanf_s(BookDateText, "%d\n", &BookDataNumber);
                Book* p, * p_s;
                p_s = (Book*)malloc(sizeof(Book));
                p_s = BookDate;
                while (p_s->next != NULL)
                {
                    p_s = p_s->next;
                }
                for (int i = 0; i < BookDataNumber; i++)
                {
                    p = (Book*)malloc(sizeof(Book));
                    if (p == NULL)
                    {
                        printf("内存分配不成功！\n");
                        printf("请联系管理员\n");
                        printf("请按任意键继续...");
                        w_e_r = getchar();
                    }
                    else
                    {
                        fscanf_s(BookDateText, "%30s %20s %50s\n", &p->name, 30, &p->author, 20, &p->press, 50);
                        p->next = NULL;
                        p_s->next = p;
                        p_s = p;
                    }
                }
                fclose(BookDateText);
                success++;
                printf("已成功导入动态图书文件\n");
            }
            else
            {
                printf("打开动态图书文件失败！\n");
            }
        }
        FILE* AllBookDateText;
        if ((err = fopen_s(&AllBookDateText, "AllBookData.txt", "r")) != 0)
        {
            printf("打开动态图书文件失败！\n");
        }
        else
        {
            if (AllBookDateText != NULL)
            {
                int ALLBookDataNumber;
                fscanf_s(AllBookDateText, "%d\n", &ALLBookDataNumber);
                Book* node, * search;
                search = (Book*)malloc(sizeof(Book));
                search = AllBookDate;
                while (search->next != NULL)
                {
                    search = search->next;
                }
                for (int i = 0; i < ALLBookDataNumber; i++)
                {
                    node = (Book*)malloc(sizeof(Book));
                    if (node == NULL)
                    {
                        printf("内存分配不成功！\n");
                        printf("请联系管理员\n");
                        printf("请按任意键继续...");
                        w_e_r = getchar();
                    }
                    else
                    {
                        fscanf_s(AllBookDateText, "%30s %20s %50s\n", &node->name, 30, &node->author, 20, &node->press, 50);
                        node->next = NULL;
                        search->next = node;
                        search = node;
                    }
                }
                fclose(AllBookDateText);
                success++;
                printf("已成功导入图书文件\n");
            }
            else
            {
                printf("打开图书文件失败！\n");
            }
        }
        FILE* AdministratorDateText;
        if ((err = fopen_s(&AdministratorDateText, "AdministratorData.txt", "r")) != 0)
        {
            printf("打开管理员文件失败！\n");
        }
        else
        {
            if (AdministratorDateText != NULL)
            {
                int AdministratorDataNumber;
                fscanf_s(AdministratorDateText, "%d\n", &AdministratorDataNumber);
                Administrator* node, * search;
                search = (Administrator*)malloc(sizeof(Administrator));
                search = AdministratorDate;
                while (search->next != NULL)
                {
                    search = search->next;
                }
                for (int i = 0; i < AdministratorDataNumber; i++)
                {
                    node = (Administrator*)malloc(sizeof(Administrator));
                    if (node == NULL)
                    {
                        printf("内存分配不成功！\n");
                        printf("请联系管理员\n");
                        printf("请按任意键继续...");
                        w_e_r = getchar();
                    }
                    else
                    {
                        fscanf_s(AdministratorDateText, "%20s %30s\n", &node->name, 20, &node->password, 30);
                        search->next = node;
                        search = node;
                    }
                }
                search->next = NULL;
                fclose(AdministratorDateText);
                success++;
                printf("已成功导入管理员文件\n");
            }
            else
            {
                printf("打开管理员文件失败！\n");
            }
        }
        if (success == 4)
        {
            printf("已成功导入数据库\n");
            readTxtAlready = 1;
        }
        else if(success == 0)
        {
            printf("数据库没有数据，请先录入数据或导入测试数据\n");
        }
        else
        {
            printf("系统错误，请重新进入\n");
            printf("请按任意键继续...");
            w_e_r = getchar();
            system("exit");
        }
    }
}

void WriteToText()
{
    printf("正在保存数据\n");
    int success = 0;
    errno_t err;
    FILE* UserDataText;
    if ((err = fopen_s(&UserDataText, "UserData.txt", "w")) != 0)
    {
        printf("打开用户文件失败！\n");
    }
    else
    {
        if (UserDataText != NULL)
        {
            int UserDataNumber = 0;
            User* search;
            search = (User*)malloc(sizeof(User));
            search = UserDate;
            while (search->next != NULL)
            {
                search = search->next;
                UserDataNumber++;
            }
            fprintf(UserDataText, "%d\n", UserDataNumber);
            search = UserDate;
            while (search->next != NULL)
            {
                search = search->next;
                fprintf(UserDataText, "%20s %30s %30s\n", search->name, search->password, search->phone);
                BorrowBookTextW(search);
            }
            success++;
            fclose(UserDataText);
            printf("用户数据保存成功\n");
        }
        else
        {
            printf("打开用户文件失败！\n");
        }
    }
    FILE* BookDataText;
    if ((err = fopen_s(&BookDataText, "BookData.txt", "w")) != 0)
    {
        printf("打开动态图书文件失败！\n");
    }
    else
    {
        if (BookDataText != NULL)
        {
            int BookDataNumber = 0;
            Book* search;
            search = (Book*)malloc(sizeof(Book));
            search = BookDate;
            while (search->next != NULL)
            {
                search = search->next;
                BookDataNumber++;
            }
            fprintf(BookDataText, "%d\n", BookDataNumber);
            search = BookDate;
            while (search->next != NULL)
            {
                search = search->next;
                fprintf(BookDataText, "%30s %20s %50s\n", search->name, search->author, search->press);
            }
            fclose(BookDataText);
            success++;
            printf("动态图书数据保存成功\n");
        }
        else
        {
            printf("打开动态图书文件失败！\n");
        }
    }
    FILE* AllBookDataText;
    if ((err = fopen_s(&AllBookDataText, "AllBookData.txt", "w")) != 0)
    {
        printf("打开图书文件失败！\n");
    }
    else
    {
        if (AllBookDataText != NULL)
        {
            int BookDataNumber = 0;
            Book* AllSearch;
            AllSearch = (Book*)malloc(sizeof(Book));
            AllSearch = AllBookDate;
            while (AllSearch->next != NULL)
            {
                AllSearch = AllSearch->next;
                BookDataNumber++;
            }
            fprintf(AllBookDataText, "%d\n", BookDataNumber);
            AllSearch = AllBookDate;
            while (AllSearch->next != NULL)
            {
                AllSearch = AllSearch->next;
                fprintf(AllBookDataText, "%30s %20s %50s\n", AllSearch->name, AllSearch->author, AllSearch->press);
            }
            success++;
            printf("图书数据保存成功\n");
            fclose(AllBookDataText);
        }
        else
        {
            printf("打开图书文件失败！\n");
        }
    }
    FILE* AdministratorDataText;
    if ((err = fopen_s(&AdministratorDataText, "AdministratorData.txt", "w")) != 0)
    {
        printf("打开管理员文件失败！\n");
    }
    else
    {
        if (AdministratorDataText != NULL)
        {
            int AdministratorDataNumber = 0;
            Administrator* search;
            search = (Administrator*)malloc(sizeof(Administrator));
            search = AdministratorDate;
            while (search->next != NULL)
            {
                search = search->next;
                AdministratorDataNumber++;
            }
            fprintf(AdministratorDataText, "%d\n", AdministratorDataNumber);
            search = AdministratorDate;
            while (search->next != NULL)
            {
                search = search->next;
                fprintf(AdministratorDataText, "%20s %30s\n", search->name, search->password);
            }
            success++;
            printf("管理员数据保存成功\n");
            fclose(AdministratorDataText);
        }
        else
        {
            printf("打开管理员文件失败！\n");
        }
    }
    if (success == 4)
    {
        printf("数据已经成功保存至数据库\n");
    }
}

void Initialization()
{
    if (LoadFirstAdministrator())
    {
        AdministratorDate->next = NULL;
        BookDate->next = NULL;
        UserDate->next = NULL;
        AllBookDate->next = NULL;
        AdministratorDate->next = NULL;
        readTxtAlready = 0;
        system("del BookData.txt");
        system("del UserData.txt");
        system("del AdministratorData.txt");
        printf("格式化数据完成\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
    else
    {
        printf("第一管理员登录失败，无法格式化数据库\n");
    }
}

void PrintfAdministrator()
{
    if (AdministratorDate->next == NULL)
    {
        printf("无管理员数据\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
    else
    {
        if (LoadFirstAdministrator())
        {
            Administrator* search;
            search = AdministratorDate;
            printf("---------------------------管理员数据----------------------------\n");
            while (search->next != NULL)
            {
                search = search->next;
                printf("%-20s %-20s\n", search->name, search->password);
            }
            printf("-----------------------------------------------------------------\n");
            printf("请按任意键继续...");
            w_e_r = getchar();
        }
        else
        {
            printf("无法进行管理员查询\n");
            printf("请按任意键继续...");
            w_e_r = getchar();
        }
    }
}

void ReviseuserPasswordAdministrator()
{
    if (LoadFirstAdministrator())
    {
        Administrator* search;
        search = AdministratorDate;
        printf("---------------------------管理员数据----------------------------\n");
        while (search->next != NULL)
        {
            search = search->next;
            printf("%-20s %-20s\n", search->name, search->password);
        }
        char change[20];
        int flag = 0;
        printf("请输入需要修改密码的管理员用户名：\n");
        gets_s(change, 20);
        search = AdministratorDate;
        while (search->next != NULL)
        {
            search = search->next;
            if (!strcmp(search->name, change))
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            printf("查无此人\n");
            printf("无法进行管理员密码修改\n");
            printf("请按任意键继续...");
            w_e_r = getchar();
        }
        else
        {
            printf("请输入新密码:\n");
            gets_s(change, 20);
            char process[20];
            printf("请确认密码:\n");
            gets_s(process, 20);
            if (!strcmp(process, change))
            {
                strcpy_s(search->password, change);
                printf("重置密码成功\n");
            }
            else
            {
                printf("两次密码不一致，无法重置密码\n");
            }
            printf("请按任意键继续...");
            w_e_r = getchar();
        }
    }
    else
    {
        printf("无法进行管理员密码修改\n");
        printf("请按任意键继续...");
        w_e_r = getchar();
    }
}

void BookSearchAuthor()
{
    if (AllBookDate->next == NULL)
    {
        printf("此书库无图书\n");
    }
    else
    {
        int flag = 0;
        char key[20];
        printf("请输入作者名：");
        gets_s(key, 20);
        Book *search;
        search = AllBookDate;
        printf("*= =====================================书库数据==================================== =*\n");
        while (search->next!=NULL)
        {
            search = search->next;
            if (!strcmp(search->author, key))
            {
                flag = 1;
                if (SearchThisBook(search))
                {
                    printf("|| %-30s %-20s %-20s  可借阅  ||\n", search->name, search->author, search->press);
                }
                else
                {
                    printf("|| %-30s %-20s %-20s  已借阅  ||\n", search->name, search->author, search->press);
                }
            }
        }
        if (flag==0)
        {
            printf("|| 本图书馆没有该作者的作品                                                          ||\n");
        }
        printf("*= ================================================================================= =*\n");
    }
    printf("请按任意键继续...");
    w_e_r = getchar();
}

void  BookSearchName()
{
    if (AllBookDate->next == NULL)
    {
        printf("此书库无图书\n");
    }
    else
    {
        int flag = 0;
        char key[30];
        printf("请输入书名：");
        gets_s(key, 30);
        Book* search;
        search = AllBookDate;
        printf("*= =====================================书库数据==================================== =*\n");
        while (search->next != NULL)
        {
            search = search->next;
            if (!strcmp(search->name, key))
            {
                flag = 1;
                if (SearchThisBook(search))
                {
                    printf("|| %-30s %-20s %-20s  可借阅  ||\n", search->name, search->author, search->press);
                }
                else
                {
                    printf("|| %-30s %-20s %-20s  已借阅  ||\n", search->name, search->author, search->press);
                }
            }
        }
        if (flag == 0)
        {
            printf("|| 本图书馆没有该图书                                                                ||\n");
        }
        printf("*= ================================================================================= =*\n");
    }
    printf("请按任意键继续...");
    w_e_r = getchar();
}

int SearchThisBook(Book* lock)
{
    Book *search;
    search = BookDate;
    while (search->next!=NULL)
    {
        search = search->next;
        if (!strcmp(search->name,lock->name))
        {
            return 1;
        }
    }
    return 0;
}

void UserBorrowingDataQuery()
{
    char lock[20];
    User *search;
    printf("请输入需要查询的用户名：");
    gets_s(lock, 20);
    search = UserDate;
    int flag = 0;
    while (search->next!=NULL)
    {
        search = search->next;
        if (!strcmp(search->name,lock))
        {
            flag = 1;
            break;
        }
    }
    if (flag == 1)
    {
        if (search->returnnumber != 0)
        {
            Book* p;
            p = search->returnmenu;
            printf("*= =====================================借阅数据==================================== =*\n");
            while (p->next != NULL)
            {
                p = p->next;
                printf("|| %-30s %-20s %-20s          ||\n", p->name, p->author, p->press);
            }
            printf("*= ================================================================================= =*\n");
        }
        else
        {
            printf("此用户未借书\n");
        }
    }
    else
    {
        printf("没有此用户\n");
    }
}

void BorrowBookTextW(User *lock)
{
    errno_t err;
    FILE* BookDataText;
    if ((err = fopen_s(&BookDataText, lock->name, "w")) != 0)
    {
        printf("%s数据保存失败！\n",lock->name);
    }
    else
    {
        if (BookDataText != NULL)
        {
            Book* search;
            fprintf(BookDataText, "%d\n", lock->returnnumber);
            search = lock->returnmenu;
            while (search->next != NULL)
            {
                search = search->next;
                fprintf(BookDataText, "%30s %20s %50s\n", search->name, search->author, search->press);
            }
            fclose(BookDataText);
            printf("%s数据保存成功！\n", lock->name);
        }
        else
        {
            printf("%s数据保存失败！\n", lock->name);
        }
    }
}

void BorrowBookTextR(User* lock)
{
    errno_t err;
    FILE* BookDateText;
    if ((err = fopen_s(&BookDateText, lock->name, "r")) != 0)
    {
        printf("%s数据读取失败！\n", lock->name);
    }
    else
    {
        if (BookDateText != NULL)
        {
            fscanf_s(BookDateText, "%d\n", &lock->returnnumber);
            Book* p, * p_s;
            p_s = (Book*)malloc(sizeof(Book));
            p_s = lock->returnmenu;
            while (p_s->next != NULL)
            {
                p_s = p_s->next;
            }
            for (int i = 0; i < lock->returnnumber; i++)
            {
                p = (Book*)malloc(sizeof(Book));
                if (p == NULL)
                {
                    printf("内存分配不成功！\n");
                    printf("请联系管理员\n");
                    printf("请按任意键继续...");
                    w_e_r = getchar();
                }
                else
                {
                    fscanf_s(BookDateText, "%30s %20s %50s\n", &p->name, 30, &p->author, 20, &p->press, 50);
                    p->next = NULL;
                    p_s->next = p;
                    p_s = p;
                }
            }
            fclose(BookDateText);
            printf("%s数据读取成功！\n", lock->name);
        }
        else
        {
            printf("%s数据读取失败！\n", lock->name);
        }
    }
}

void TextPrintf()
{
    printf("测试数据如下：\n");
    printf("图书数据\n");
    BookSearchAll();
    system("cls");
    printf("测试数据如下：\n");
    printf("用户数据\n");
    PrintUser();
    printf("请按任意键继续...");
    w_e_r = getchar();
    system("cls");
    printf("测试数据如下：\n");
    printf("管理员数据\n");
    Administrator* search;
    search = AdministratorDate;
    printf("---------------------------管理员数据----------------------------\n");
    while (search->next != NULL)
    {
        search = search->next;
        printf("%-20s %-20s\n", search->name, search->password);
    }
    printf("-----------------------------------------------------------------\n");
}