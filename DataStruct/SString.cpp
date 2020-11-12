#include "SString.h"

SString::SString()
{
	data[0] = '\0';
}

SString::~SString()
{
}

void SString::StrAssign(const char *cstr)
{
	int len = static_cast<int>(strlen(cstr));
	if (len > MAXSIZE)
		len = MAXSIZE;

	for (int i = 0; i < len; i++)
	{
		data[i] = cstr[i];
	}
	data[len] = '\0';
}

void SString::StrCopy(const SString &T)
{
	auto len = T.StrLenght();

	for (int i = 0; i < len; i++)
	{
		data[i] = T.data[i];
	}
	data[len] = '\0';
}

bool SString::StrEmpty() const
{
	return data[0] == '\0';
}

int SString::StrCompare(const SString &T) const
{
	int i = 0;
	while (data[i] != '\0' || T.data[i] != '\0')
	{
		if (data[i] - T.data[i] != 0)
			break;

		i++;
	}

	if (data[i] - T.data[i] < 0)
		i = -1;
	else if (data[i] - T.data[i] > 0)
		i = 1;
	else
		i = 0;

	return i;
}


int SString::StrLenght() const
{
	int i = 0;
	while (data[i] != '\0')
		++i;

	return i;
}
void SString::ClearString()
{
	data[0] = '\0';
}

void SString::Concat(const SString &s1, const SString &s2)
{
	auto len1 = s1.StrLenght();
	auto len2 = s2.StrLenght();

	if (MAXSIZE >= len1 + len2)
	{
		StrCopy(s1);

		for (int j = 0; j < len2; j++)
		{
			data[len1 + j] = s2.data[j];
		}

		data[len1 + len2] = '\0';
	}
	else if (MAXSIZE >= len1)
	{
		StrCopy(s1);

		for (int j = 0; j < MAXSIZE - len1; j++)
		{
			data[len1 + j] = s2.data[j];
		}

		data[MAXSIZE] = '\0';
	}
	else
	{
		//暂时不会出现这种情况
	}
}


void SString::SubString(SString *T, int pos, int len)
{
	auto m_len = StrLenght();

	if (pos < 1 || pos > m_len)
		return;

	if ((pos - 1) + len > m_len)
	{
		len = m_len - (pos - 1);
	}

	for (int i = 0; i < len; i++)
	{
		T->data[i] = data[pos - 1 + i];
	}

	T->data[len] = '\0';
}

int SString::Index(const SString& T, int pos)
{
	auto m_len = StrLenght();
	auto len = T.StrLenght();

	if (pos < 1 || pos > m_len 
		|| len + (pos-1) > m_len)
		return -1;

	SString temp;
	while (len + (pos - 1) <= m_len)
	{
		SubString(&temp, pos, len);

		if (T.StrCompare(temp) == 0)
			return pos;

		pos++;
	}

	return -1;
}

bool SString::StrInsert(const SString &T, int pos)
{
	auto len = T.StrLenght();
	auto m_len = StrLenght();

	if (pos < 1 || pos > m_len + 1
		||m_len + len > MAXSIZE)
		return false;

	//移动元素
	for (int i = m_len - 1; i >= (pos - 1); i--)
	{
		data[i + len] = data[i];
	}
	data[len + m_len] = '\0';

	//拷贝新串
	for (int i = 0; i < len; i++)
	{
		data[(pos - 1) + i] = T.data[i];
	}

	return true;
}

bool SString::StrDelete(int pos, int len)
{
	auto m_len = StrLenght();

	if (pos < 1 || pos > m_len)
		return false;

	if ((pos - 1) + len > m_len)
	{
		len = m_len - (pos - 1);
	}

	//移动元素
	for (int i = (pos - 1) + len; i < m_len; i++)
	{
		data[i - len] = data[i];
	}
	data[m_len - len] = '\0';

	return true;
}

void SString::Replace(const SString &oldStr, const SString &newStr)
{
	auto oldStr_len = oldStr.StrLenght();
	auto newStr_len = newStr.StrLenght();

	//如果新串长度大于旧串有一定风险(如空间不足)
	//保证如果出现错误，本串保持不变
	SString temp;
	if (newStr_len > oldStr_len)
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
