/**
 * written by Dean
 * 编译原理课程设计
 * 符号表的管理
 */
#pragma once

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <map>
#include <set>

#ifdef __cplusplus
extern "C"
{
#endif

    using namespace std;

    struct type // 结构：类型
    {
        string typ;          // 类型
        string value;        // 存储该量的值
        void *aditionalInfo; // 额外信息 为数组时则存储数组信息，为结构类型时存储结构体信息，为函数时存储子符号表
    };

    struct parameter // 结构：参数
    {
        string name;   // 参数名称
        string typ;    // 参数类型
        int valueType; // 为0传值调用，为1引用调用
    };

    struct bound // 结构：数组上下界
    {
        int upperBound; // 上界
        int lowerBound; // 下界
    };

    struct Array // 结构：数组
    {
        type tp;                 // 数组类型
        vector<bound> boundrays; // 数组各维上下界
    };

    struct record_item
    {
        string name;         //名称
        string type;         //类型
        int declarativeLine; //声明行数
        set<int> UseLine;    //使用行数
    };

    class STRUCTINFO // 类：结构信息
    {
    public:
        vector<record_item> records;

        bool isrecord(string name); // 判断是否属于该结构
    };

    class FUNC // 类：函数
    {
    public:
        string returnType;                   // 返回值类型
        vector<parameter> list;         // 参数列表
        vector<string> order;                // 参数type顺序
        parameter *isParameter(string name); // 判断该标识符是否是函数参数
        int paraNum();                       // 返回list的元素数量
    };

    class TABLEITEM //类：符号表表项，代表每个标识符的信息
    {
    public:
        string name;            // 名字
        type tp;                // 类型
        int isConst;            // 是否为常量
        int declarativeLine;    // 声明行
        vector<int> *usedLines; // 引用行
        int dimension;          // 数组维数（或参数个数）

        TABLEITEM();
        TABLEITEM(string name, type tp, int declarativeLine, int dimension, vector<int> *usedLines); // 表项构造函数
    };

    class SYMBOLTABLE // 类：符号表
    {
    public:
        map<string, TABLEITEM> items; // 符号表表项
        SYMBOLTABLE *lastLevel;       // 上一级符号表
        void *additionalInfo;         // 额外信息，若为函数符号表，则函数有返回类型及参数
        SYMBOLTABLE();                                            // 符号表构造函数（无参数）
        SYMBOLTABLE(SYMBOLTABLE *lastLevel, void *additionalInfo); // 符号表构造函数
        void insert(TABLEITEM item);                               // 符号表增添表项函数
        void del(string name);                                     // 符号表删除表项函数
        TABLEITEM *find(string name);                              // 符号表查找表项函数：按给定的名字查表
        TABLEITEM *findInALL(string name);                         // 符号表查找表项函数（全局范围内寻找）
        SYMBOLTABLE *locate(TABLEITEM item);                       // 符号表定位操作函数
        SYMBOLTABLE *relocate();                                   // 符号表重定位操作函数
    };

#ifdef __cplusplus
}

#endif
