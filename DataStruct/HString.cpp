#include "HString.h"

HString::HString() : data(nullptr), length(0)
{
}

HString::~HString()
{
	if (data) free(data);
}

void HString::StrAssign(const char *c_str)
{
	int len = static_cast<int>(strlen(c_str));

	if (len)
	{
		if (data) free(data);
		data = (char *)malloc(len * sizeof(char));

		for (int i = 0; i < len; i++)
		{
			data[i] = c_str[i];
		}
		length = len;
	}
}

void HString::StrCopy(const HString &T)
{
	if (T.data)
	{
		int len = T.StrLenght();

		if (data) free(data);
		data = (char *)malloc(len * sizeof(char));

		for (int i = 0; i < len; i++)
		{
			data[i] = T.data[i];
		}
		length = len;
	}
}

bool HString::StrEmpty() const
{
	return (data == nullptr);
}

int HString::StrCompare(const HString &T) const
{
	int result;
	int m_len = StrLenght(), len = T.StrLenght();
	int minLen = m_len < len ? m_len : len;

	int i;
	for (i = 0; i < minLen; i++)
	{
		if (data[i] != T.data[i])
			break;
	}

	//前一段相同,比长度
	if (i == minLen)
	{
		if (m_len == len)
			result = 0;
		else if (m_len > len)
			result = 1;
		else
			result = -1;
	}
	else if (data[i] > T.data[i])
		result = 1;
	else
		result = -1;
	
	return result;
}

int HString::StrLenght() const
{
	return length;
}

void HString::ClearString()
{
	if (data) free(data);
	data = nullptr;
	length = 0;
}

void HString::Concat(const HString &s1, const HString &s2)
{
	//if (s1.StrEmpty() || s2.StrEmpty())
	//	return;

	int len1 = s1.StrLenght();
	int len2 = s2.StrLenght();

	ClearString();
	data = (char *)malloc((len1 + len2) * sizeof(char));

	for (int i = 0; i < len1; i++)
		data[i] = s1.data[i];

	for (int j = 0; j < len2; j++)
		data[len1 + j] = s2.data[j];

	length = len1 + len2;
}


void HString::SubString(HString *T, int pos, int len)
{
	if (pos <1 || pos > length)
		return;

	if ((pos - 1) + len > length)
	{
		len = length - (pos - 1);
	}
	
	T->ClearString();
	T->data = (char *)malloc(len * sizeof(char));
	for (int i = 0; i < len; i++)
	{
		T->data[i] = data[pos - 1 + i];
	}

	T->length = len;
}


int HString::Index(const HString &T, int pos)
{
	auto len = T.StrLenght();
	
	if (pos < 1 || pos > length 
		|| len + (pos-1) > length)
		return -1;
	
	HString temp;
	while (len + (pos - 1) <= length)
	{
		SubString(&temp, pos, len);
	
		if (T.StrCompare(temp) == 0)
			return pos;
	
		pos++;
	}
	
	return -1;
}

bool HString::StrInsert(const HString &T, int pos)
{
	if (pos <1 || pos > length + 1)
		return false;

	if (T.data)
	{
		int len = T.length;
		if (data) data = (char *)realloc(data, (length + len) * sizeof(char));
		else data = (char *)malloc(len * sizeof(char));

		for (int i = length - 1; i >= pos - 1; i--)
		{
			data[i + len] = data[i];
		}

		for (int j = 0; j < len; j++)
		{
			data[(pos - 1) + j] = T.data[j];
		}
		length += len;

		return true;
	}

	return false;
}

bool HString::StrDelete(int pos, int len)
{
	if (pos < 1 || pos > length)
		return false;
	
	if ((pos - 1) + len > length)
	{
		len = length - (pos - 1);
	}
	
	//移动元素
	for (int i = (pos - 1) + len; i < length; i++)
	{
		data[i - len] = data[i];
	}
	length = length - len;
	
	return true;
}

void HString::Replace(const HString &oldStr, const HString &newStr)
{
	auto oldStr_len = oldStr.length;
	auto newStr_len = newStr.length;
	
	HString temp;
	temp.StrCopy(*this);

	int pos = 1;
	pos = Index(oldStr, pos);
	while (pos != -1)
	{
		if (!StrDelete(pos, oldStr_len) || !StrInsert(newStr, pos))
		{
			StrCopy(temp);
			return;
		}
	
		pos += newStr_len;
		pos = Index(oldStr, pos);
	}
}
