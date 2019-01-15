//项目：串(定长顺序储存结构)
//创建时间：2018/11/21 21:00
//完成时间：2018/11/22 22:41
//最后一次修改时间：
//修改次数：
//修改原因：
//
//
//作者：CenJieTeng
//QQ: 2271369683
#pragma once
#ifndef SSTRING_H
#define SSTRING_H
#include <string.h>
#define MAXSIZE 20

class SString
{
public:
	SString();
	~SString();

public:
	void StrAssign(const char *c_str); 
	void StrCopy(const SString &T);
	bool StrEmpty() const;
	int StrCompare(const SString &T) const;
	int StrLenght() const;
	void ClearString();
	void Concat(const SString &s1, const SString &s2);
	void SubString(SString *T, int pos, int len);
	int Index(const SString &T, int pos);
	bool StrInsert(const SString &T, int pos);
	bool StrDelete(int pos, int len);
	void Replace(const SString &oldStr, const SString &newStr);


private:
	char data[MAXSIZE + 1];
};

#endif // !SSTRING_H
