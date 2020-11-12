//项目：串(堆分序储存结构)
//创建时间：2018/11/24 22:12
//完成时间：2018/11/25 15:30
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef HSTRING_H
#define HSTRING_H
#include <iostream>
#include <string>

class HString
{
public:
	HString();
	~HString();

public:
	void StrAssign(const char *c_str); 
	void StrCopy(const HString &T);
	bool StrEmpty() const;
	int StrCompare(const HString &T) const;
	int StrLenght() const;
	void ClearString();
	void Concat(const HString &s1, const HString &s2);
	void SubString(HString *T, int pos, int len);
	int Index(const HString &T, int pos);
	bool StrInsert(const HString &T, int pos);
	bool StrDelete(int pos, int len);
	void Replace(const HString &oldStr, const HString &newStr);

private:
	char *data;
	int length;
};

#endif // !HSTRING_H
