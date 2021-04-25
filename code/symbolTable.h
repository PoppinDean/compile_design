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
    type tp;                  // 数组类型
    vector<bound> *boundrays; // 数组各维上下界
};

class STRUCTINFO // 类：结构信息
{
    map<string, type> *records;

public:
    type *isrecord(string name); // 判断是否属于该结构
};

class FUNC // 类：函数
{
    string returnType;            // 返回值类型
    map<string, parameter> *list; // 参数列表

public:
    parameter *isParameter(string name); // 判断该标识符是否是函数参数
    int paraNum();                      // 返回list的元素数量
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

    SYMBOLTABLE();                                             // 符号表构造函数（无参数）
    SYMBOLTABLE(SYMBOLTABLE *lastLevel, void *additionalInfo); // 符号表构造函数
    void insert(TABLEITEM item);                               // 符号表增添表项函数
    void del(string name);                                     // 符号表删除表项函数
    TABLEITEM *find(string name);                              // 符号表查找表项函数：按给定的名字查表
    TABLEITEM *findInALL(string name);                         // 符号表查找表项函数（全局范围内寻找）
    SYMBOLTABLE *locate(TABLEITEM item);                       // 符号表定位操作函数
    SYMBOLTABLE *relocate();                                   // 符号表重定位操作函数
};

/**
 * 判断该某一类型是否属于该结构，若是返回该类型指针，否则返回NULL
 * @par name 类型名字
 * @return 返回一个类型指针
 */
type *STRUCTINFO::isrecord(string name)
{
    std::map<string, type>::iterator iter = records->find(name);
    if (iter != records->end()) // 如果查找到返回类型指针
    {
        return &(iter->second);
    }
    else //否则返回NULL
        return NULL;
}

/**
 * 判断该标识符是否是函数参数，若是返回指向该参数信息的指针，否则返回NULL
 * @par name 标识符名字
 * @return 返回一个参数信息指针
 */
parameter *FUNC::isParameter(string name)
{
    std::map<string, parameter>::iterator iter = list->find(name);
    if (iter != list->end()) // 如果查找到返回参数指针
    {
        return &(iter->second);
    }
    else //否则返回NULL
        return NULL;
}

/**
 * 返回list中元素数量
 * @return int型
 */
int FUNC::paraNum()
{
    return list->size();
}

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
 * 符号表构造函数(无参数)
 */
SYMBOLTABLE::SYMBOLTABLE()
{
    this->lastLevel = NULL;
    this->additionalInfo = NULL;
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
 * 符号表查找表项函数：按给定的名字查表。若找到返回表项指针，否则返回NULL
 * @par name 给定查找的名字
 * @return 返回一个表项指针
 */
TABLEITEM *SYMBOLTABLE::find(string name)
{
    std::map<string, TABLEITEM>::iterator iter = items.find(name);
    if (iter != items.end()) // 若找到返回表项指针
    {
        return &(iter->second);
    }
    else // 否则返回NULL
        return NULL;
}

/**
 * 符号表查找表项函数：按给定的名字查表(在全局范围内寻找，注意与find区分)若找到返回表项指针，否则返回NULL
 * @par name 给定查找的名字名字
 * @return 返回一个表项指针
 */
TABLEITEM *SYMBOLTABLE::findInALL(string name)
{
    TABLEITEM *item = find(name);
    if (item != NULL)
        return item;
    else if (lastLevel == NULL) // 若无父表，即当前为主表
        return NULL;
    else // 类似递归查询：对父表进行查询
        return lastLevel->findInALL(name);
}

/**
 * 符号表定位操作函数
 * @par item 需要创建子符号表的表项
 * @return 返回一个指向子符号表的指针
 */
SYMBOLTABLE *SYMBOLTABLE::locate(TABLEITEM item)
{
    return new SYMBOLTABLE(this, item.tp.aditionalInfo);
}

/**
 * 符号表重定位操作函数
 * @return 返回指向父符号表的指针
 */
SYMBOLTABLE *SYMBOLTABLE::relocate()
{
    return lastLevel;
}
