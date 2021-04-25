#include "Type_Check.h"
#include "symbolTable.h"
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

vector<string> Split(string s, char c)
{
    vector<string> answer;
    string temp = "";
    for (char t : s)
    {
        if (t == c)
        {
            answer.push_back(temp);
            temp = "";
        }
        temp += t;
    }
    if (temp != "")
        answer.push_back(temp);
    return answer;
}

bool Type_Check(string a, string b, SYMBOLTABLE &table) //判断为type的两个变量是否结构等价
{
    type *type1 = &(table.find(a)->tp), *type2 = &(table.find(b)->tp);
    while (type1->typ == type2->typ && "array" == type1->typ)
    {
        Array *arr1 = (Array *)(type1->aditionalInfo), *arr2 = (Array *)(type2->aditionalInfo);
        type1 = &(arr1->tp);
        type2 = &(arr2->tp);
    }
    if (type1->typ == type2->typ)
        return true;
    return false;
}

string Assign_Check(string a, string b) //判断赋值符号两边类型是否相同或者满足C语言隐式转换的条件，若满足则返回表达式类型，否则返回error
{
    if (a == b && a != "record") //当a和b都是为基本类型时(非record)
        return a;
    else if (a == b && a == "record") //当a和b均为record时返回record_check，需要程序进一步判断
        return "record_check";
    else if ((a == "integer" && b == "real") || (a == "real" && b == "integer") || (a == "char" && b == "integer"))
        return a;
    else if ((a == "integr" || a == "real") && b == "char")
        return a;
    else
        return "error";
}

bool Relop_Check(string a, string b) //判断relop两边的类型a和b是否相同或者满足C语言隐式转换的条件
{
    if (a == b || ((a == "integer" || a == "char" || a == "real") && (b == "integer" || b == "char" || b == "real")))
        return true;
    else
        return false;
}

string Binary_Check(string a, string b) //判断二元符号addop和mulop两边类型是否相同或者满足C语言隐式转换的条件，若满足则返回表达式类型，否则返回error
{
    if (a == b)
        return a;
    else if ((a == "real" || a == "integer") && (b == "real" || b == "integer"))
        return "real";
    else if ((a == "real" || a == "char") && (b == "real" || b == "char"))
        return "real";
    else if ((a == "integer" || a == "char") && (b == "integer" || b == "char"))
        return "integer";
    else
        return "error";
}

string Change_Para(FUNC &fun, string code) //根据参数列表Para的信息修改以逗号分隔的表达式code，在传引用调用的地方加上&
{
    string ans = "", t = "";
    int Length = code.length();
    for (int i = 0; i < Length; i++)
    {
        if (code[i] == ',')
        {
            if (!fun.isParameter(t))
                return "error";
            if (!fun.isParameter(t)->valueType) //传引用调用
                t = "&(" + t + ")";
            ans += t + ",";
            t = "";
        }
        else
            t += code[i];
    }
    if (t != "")
    {
        if (!fun.isParameter(t))
            return "error";
        if (!fun.isParameter(t)->valueType) //传引用调用
            t = "&(" + t + ")";
        ans += t + ",";
    }
    return ans;
}

bool Para_Check(FUNC &fun, string types, string code) //types以空格分隔,检查参数列表与types是否能够匹配
{
    vector<string> ty = Split(types, ' '), name = Split(code, ',');
    if (fun.paraNum() != ty.size())
        return false;

    for (int i = 0; i < ty.size(); i++)
    {
        if (fun.isParameter(name[i])->typ != ty[i])
            return false;
    }
    return true;
}