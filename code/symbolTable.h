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

using namespace std;

/**自定义**/

enum types // 各类型所对应类型号
{
    CONST,    // 0为常量
    INTEGER,  // 1为integer型变量
    REAL,     // 2为real型变量
    BOOLEAN,  // 3为BOOLEAN型变量
    CHAR,     // 4为CHAR型变量
    FUNCTION, // 5为函数
    ARRAY,    // 6为数组
    STRUCT,   // 7为结构

};

struct type // 结构：类型
{
    types typeNum;       // 类型号
    string value;        // 存储该量的值
    void *aditionalInfo; // 额外信息 为数组时则存储数组信息，为结构类型时存储结构体信息，为函数时存储子符号表
};

struct parameter // 结构：参数
{
    string name;   // 参数名称
    types type;    // 参数类型
    int valueType; // 为0传值调用，为1引用调用
};

struct func // 结构：函数
{
    types returnType;        // 返回值类型
    vector<parameter> *list; // 参数列表
};

struct bound // 结构：数组上下界
{
    int upperBound; // 上界
    int lowerBound; // 下界
};

struct array // 结构：数组
{
    vector<bound> boundrays; // 数组各维上下界
};

struct structInfo // 结构：结构信息
{
    vector<type> records;
};

class TABLEITEM //类：符号表表项，代表每个标识符的信息
{
public:
    string name;            // 名字
    type tp;                // 类型
    int declarativeLine;    // 声明行
    vector<int> *usedLines; // 引用行
    int dimension;          // 数组维数（或参数个数）

    TABLEITEM(string name, type tp, int declarativeLine, int dimension, vector<int> *usedLines); // 表项构造函数
};

class SYMBOLTABLE // 类：符号表
{
public:
    map<string, TABLEITEM> items; // 符号表表项
    SYMBOLTABLE *lastLevel;       // 上一级符号表
    void *additionalInfo;         // 额外信息，若为函数符号表，则函数有返回类型及参数

    SYMBOLTABLE(SYMBOLTABLE *lastLevel, void *additionalInfo); // 符号表构造函数
    void insert(TABLEITEM item);                               // 符号表增添表项函数
    void del(string name);                                     // 符号表删除表项函数
    TABLEITEM *find(string name);                              // 符号表查找表项函数：按给定的名字查表
    SYMBOLTABLE *locate(TABLEITEM item);                       // 符号表定位操作函数
    SYMBOLTABLE *relocate();                                   // 符号表重定位操作函数
};

/**
 * TABLEITEM表项构造函数
 * @par name 名字  @par tp 类型  @par declarativeLine 声明行  @par dimension 维数  @par usedLines 引用行
 */
TABLEITEM::TABLEITEM(string name, type tp, int declarativeLine, int dimension, vector<int> *usedLines)
{
    this->name = name;
    this->tp = tp;
    this->declarativeLine = declarativeLine;
    this->dimension = dimension;
    this->usedLines = usedLines;
}

/**
 * 符号表构造函数
 * @par lastLevel 上级符号表指针  @par additionalInfo 额外信息指针
 */
SYMBOLTABLE::SYMBOLTABLE(SYMBOLTABLE *lastLevel, void *additionalInfo)
{
    this->lastLevel = lastLevel;
    this->additionalInfo = additionalInfo;
}

/**
 * 符号表增添表项函数
 * @par item 新的表项内容
 */
void SYMBOLTABLE::insert(TABLEITEM item)
{
    items.insert(pair<string, TABLEITEM>(item.name, item));
}

/**
 * 符号表删除表项函数
 * @par name 要删除的表项名
 */
void SYMBOLTABLE::del(string name)
{
    items.erase(name);
}

/**
 * 符号表查找表项函数：按给定的名字查表
 * @par name 名字
 * @return 返回一个表项指针
 */
TABLEITEM *SYMBOLTABLE::find(string name)
{
    std::map<string, TABLEITEM>::iterator iter = items.find(name);
    if (iter != items.end())
    {
        return &iter->second;
    }
    else
        return NULL;
}

/**
 * 符号表定位操作函数
 */
SYMBOLTABLE *SYMBOLTABLE::locate(TABLEITEM item)
{
    return new SYMBOLTABLE(this, item.tp.aditionalInfo);
}

/**
 * 符号表重定位操作函数
 */
SYMBOLTABLE *SYMBOLTABLE::relocate()
{
    return lastLevel;
}
