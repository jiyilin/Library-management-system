#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Book
{
    char name[30];     //书名
    char author[20];   //作者
    char press[50];    //出版社名
    struct Book* next; //下一本书
} Book;

typedef struct User
{
    char name[20];     //用户名
    char password[20]; //用户密码
    char phone[30];    //联系方式
    int returnnumber;  //可还书数量
    Book* returnmenu;  //可还书数据头
    struct User* next; //下一个节点
} User;

typedef struct Administrator
{
    char name[20];              //管理员id
    char password[20];          //管理员密码
    struct Administrator* next; //下一个节点
} Administrator;

void Input_Book();                      //注册书本
void BorrowBook(char key[20]);          //借书函数
void ReturnBook(char key[20]);          //还书函数
void BookSearchAll();                   //书本显示
void DelBooksFunction();                //书本删除
int BorrowBookFrequency();              //借书次数
int ReturnBookFrequency();              //还书次数
int BorrowBookFunction11(char key[20]); //借书实现
int ReturnBookFunction11(char key[20]); //还书实现
int SearchBookMenu();                   //查书目录
void SearchBookFunction();              //查书总函数
void BookSearchAuthor();                //按作者查书
void  BookSearchName();                 //按书名查书
int SearchThisBook(Book *lock);         //查找BookData是否有数据(成功1 ； 失败0)；

int UserMenu();                        //用户目录
void RegisterUser();                   //注册用户
void UsermenuFunction();               //用户目录调用函数实体
User* UserLoad();                      //用户登陆函数(成功1 ； 失败0)
void DeleteUser();                     //删除用户
void ReviseuserPassword(User* Active); //修改密码
void PrintUser();                      //用户输出
void UserBorrowingDataQuery();         //用户借阅数据查询 
void BorrowBookTextW(User* lock);      //用户借书数据保存
void BorrowBookTextR(User* lock);      //用户借书数据写入程序

int AdministratorMenu();                //管理员目录
int AdministratorLoadChose();           //管理员登录选择
int RegisterAdministrator11();          //管理员注册
void AdministratorFunciton();           //管理员目录调用函数实体
int AdministratorLoad();                //管理员登陆
int LoadFirstAdministrator();           //登录第一管理员(成功1 ； 失败0)
void PrintfAdministrator();             //管理员输出
void ReviseuserPasswordAdministrator(); //管理员修改密码

int HeadMenu();               //头目录
void HeadmenuFunction();      //头目录调用函数实体
void ReadToText();            //文件读取
void WriteToText();           //文件输出
int AgainOnce();              //是否继续(1:继续; 0:退出)
void TimePrintf(char clock[]); //输出时间
void Initialization();        //初始化数据
void LibraryText();           //导入测试数据
void OutSystem();             //退出系统
void ReadToTextLoad();        //文件读取权限验证
void LibraryTextLoad();       //测试文件读取权限验证
void logo();                  //logo
void TextPrintf();            //显示测试数据