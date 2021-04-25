#pragma once

#include "symbolTable.h"
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;


//bool RecordCheck(string a,string b); //判断为record的两个变量是否结构等价

//string AssignCheck(string a,string b); //判断赋值符号两边类型是否相同或者满足C语言隐式转换的条件，若满足则返回表达式类型，否则返回error

//bool RelopCheck(string a,string b); //判断relop两边的类型a和b是否相同或者满足C语言隐式转换的条件


//string BinaryCheck(string a, string b); //判断二元符号addop和mulop两边类型是否相同或者满足C语言隐式转换的条件，若满足则返回表达式类型，否则返回error

//string ChangeParameter(vector<Parameter*> Para, string code);//根据参数列表Para的信息修改以逗号分隔的表达式code，在传引用调用的地方加上&

//bool ParaCheck(vector<Parameter*> Para, string types); //types以空格分隔,检查参数列表与types是否能够匹配

