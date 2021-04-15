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
#include <set>
using namespace std;

/**自定义**/

enum types // 各类型所对应类型号
{
    CONST,    // 0为常量
    VARIABLE, // 1为变量
    FUNCTION, // 2为函数
    ARRAY,    // 3为数组
    STRUCT    // 4为结构
};

struct type // 结构：类型
{
    int typeNum;         // 类型号
    string value;        // 存储该量的值
    void *aditionalInfo; // 额外信息 为数组时则存储数组信息，为结构类型时存储结构体信息，为函数时存储子符号表
};

class TABLEITEM //类：符号表表项，代表每个标识符的信息
{
private:
    string name;         // 名字
    type tp;             // 类型
    int declarationLine; // 声明行
    set<int> usedLines;  // 引用行
    int dimension;       // 数组维数（或参数个数）

public:
    TABLEITEM();
};