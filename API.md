# API接口文档

## 符号表接口

|函数名| <div style="width:260px">参数</div> |<div style="width:190px">返回值</div> |作用|
|------|-----|-----|----|
|STRUCTINFO::isrecord|string name 类型名字 |type * <br/>返回一个类型指针|判断该某一类型是否属于该结构，若是返回该类型指针，否则返回NULL|
|FUNC::isParameter|string name 标识符名字 |parameter * <br/>返回一个类型指针|判断该标识符是否是函数参数，若是返回指向该参数信息的指针，否则返回NULL|
|FUNC::paraNum|无|int <br/>返回list的元素数量|返回list中元素数量|
|TABLEITEM::TABLEITEM|无|无|TABLEITEM表项无参构造函数|
|TABLEITEM::TABLEITEM|string name 标识符名字<br/>type tp 类型 <br/>int declarativeLine 声明行 <br/>int dimension 维数 <br/> vector<int> *usedLines 引用行|无|TABLEITEM表项构造函数|
|SYMBOLTABLE::SYMBOLTABLE|无|无|符号表无参构造函数|
|SYMBOLTABLE::SYMBOLTABLE|SYMBOLTABLE *lastLevel 上级符号表指针<br/>void *additionalInfo 额外信息指针|无|符号表构造函数|
|SYMBOLTABLE::insert|TABLEITEM item 新的表项内容|无|TABLEITEM表项构造函数|
|SYMBOLTABLE::del|string name 要删除的表项名|无|符号表删除表项函数|
|SYMBOLTABLE::find|string name 给定查找的名字|TABLEITEM * <br/>返回一个表项内容|符号表删除表项函数|
|SYMBOLTABLE::findInALL|string name 给定查找的名字|TABLEITEM * <br/>返回一个表项内容|符号表查找表项函数：按给定的名字查表(在全局范围内寻找，注意与find区分)若找到返回表项指针，否则返回NULL|
|SYMBOLTABLE::locate|TABLEITEM item 需要创建子符号表的表项|SYMBOLTABLE *<br/>返回一个指向子符号表的指针|符号表定位操作函数|
|SYMBOLTABLE::relocate|无|SYMBOLTABLE *<br/>返回指向父符号表的指针|符号表重定位操作函数|








