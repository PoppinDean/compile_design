#include "symbolTable.h"
#include <vector>
#include <map>

using namespace std;
/**
 * 判断该某一类型是否属于该结构，若是返回该类型指针，否则返回NULL
 * @par name 类型名字
 * @return 返回一个类型指针
 */
bool STRUCTINFO::isrecord(string name)
{
    for (auto item : records)
    {
        if (item.name == name)
            return true;
    }
    return false;
}

/**
 * 判断该标识符是否是函数参数，若是返回指向该参数信息的指针，否则返回NULL
 * @par name 标识符名字
 * @return 返回一个参数信息指针
 */
parameter *FUNC::isParameter(string name)
{
    for(int i = 0; i<list.size();i++)
    {
        if(list[i].name == name)
         return &list[i];
    }
    //否则返回NULL
    return NULL;
}

/**
 * 返回list中元素数量
 * @return int型
 */
int FUNC::paraNum()
{

    return list.size();
}

/**
 * TABLEITEM表项构造函数
 * @par name 名字  @par tp 类型  @par declarativeLine 声明行  @par dimension 维数  @par usedLines 引用行
 */
TABLEITEM::TABLEITEM()
{
}

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