#pragma once

#include "symbolTable.h"
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

vector<string> Split(string s, char c); //将字符串以字符‘c’分割为数组

bool Type_Check(string a, string b, SYMBOLTABLE &table); //判断为record的两个变量是否结构等价

string Assign_Check(string a, string b); //判断赋值符号两边类型是否相同或者满足C语言隐式转换的条件，若满足则返回表达式类型，否则返回error

bool Relop_Check(string a, string b); //判断relop两边的类型a和b是否相同或者满足C语言隐式转换的条件

string Binary_Check(string a, string b); //判断二元符号addop和mulop两边类型是否相同或者满足C语言隐式转换的条件，若满足则返回表达式类型，否则返回error

string Change_Para(FUNC &fun, string code); //根据参数列表Para的信息修改以逗号分隔的表达式code，在传引用调用的地方加上&

bool Para_Check(FUNC &fun, string types, string code); //types以空格分隔,检查参数列表与types是否能够匹配
