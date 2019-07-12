#ifndef UFDATATYPE_H
#define UFDATATYPE_H

#include "stdio.h"

typedef __int64		UF_INT8;

struct I64S
{
	char cs[32];
};
I64S print64(UF_INT8 a);
I64S print64(UF_INT8 a)
{
	I64S s;
	sprintf(s.cs, "%I64d", a);
	return s;
}
#define PRINT64(a) (print64(a).cs)

class CUFBaseStringType
{
};

template <int length, int precision> class CUFBigDecimalType : public CUFBaseStringType
{
public:
	///构造函数
	CUFBigDecimalType(void)
	{
		buffer[0] = '\0';
	}

	///复制构造子
	///@param	s	构造的源对象
	CUFBigDecimalType(const CUFBigDecimalType<length, precision>& s)
	{
		setValue(s.getValue());
	}

	///复制构造子
	///@param	p	构造的源对象
	CUFBigDecimalType(const char *p)
	{
		setValue(p);
	}

	CUFBigDecimalType(const int &v)
	{
		char tmp[100];
		sprintf(tmp, "%d", v);
		setValue(tmp);
	}
	CUFBigDecimalType(const UF_INT8 &v)
	{
		char tmp[100];
		sprintf(tmp, "%s", PRINT64(v));
		setValue(tmp);
	}
	CUFBigDecimalType(const double &f)
	{
		char tmp[512];
		sprintf(tmp, "%f", f);
		setValue(tmp);
	}
	CUFBigDecimalType(const CFloat &f)
	{
		char tmp[100];
		setValue(f.toString(tmp));
	}

	///等于操作符
	///@param	s	等于的值
	///@return	输入的值
	const CUFBigDecimalType & operator =(const CUFBigDecimalType<length, precision>& s)
	{
		setValue(s.getValue());
		return s;
	}
	const CFloat & operator =(const CFloat &f)
	{
		char tmp[100];
		setValue(f.toString(tmp));
		return f;
	}
	const double & operator =(const double &v)
	{
		char tmp[512];
		sprintf(tmp, "%f", v);
		setValue(tmp);
		return v;
	}

	///等于操作符，从字符串中获取
	///@param	p	等于的字符串
	///@return	输入的字符串
	const char * operator =(const char *p)
	{
		setValue(p);
		return p;
	}

	///等于操作符，从整数中获取
	///@param	v	等于的整数
	///@return	输入的整数
	const int operator =(const int v)
	{
		char tmp[100];
		sprintf(tmp, "%*d", length, v);
		setValue(tmp);
		return v;
	}

	const UF_INT8 operator =(const UF_INT8 v)
	{
		char tmp[100];
		sprintf(tmp, "%*s", length, PRINT64(v));
		setValue(tmp);
		return v;
	}

	const char * operator +=(const char *p)
	{
		if (strlen(p) + strlen(buffer) >= length)
		{
			return NULL;
		}
		strcat(buffer, p);
		buffer[length] = '\0';
		return p;
	}

	///清除字符串内容
	void clear(void)
	{
		buffer[0] = '\0';
	}

	///获取字符串的值
	///@return	字符串的值
	const char *getValue(void) const
	{
		return buffer;
	}

	///设置字符串的值
	///@param	s	要设置的字符串
	void setValue(const char *s)
	{
		if (s == NULL)
			buffer[0] = '\0';
		else
		{
			strncpy(buffer, s, length);
			buffer[length] = '\0';
		}
	}

	///在strBuf中得到本类型的字符串表示	
	///@param	strBuf	用于放置结果的字符串
	void getString(char *strBuf) const
	{
		if (strBuf != NULL)
		{
			memcpy(strBuf, buffer, length);
			strBuf[length] = '\0';
		}
	}

	///判断是否为空
	///@return	true表示为空，false表示不为空
	bool isNull(void) const
	{
		const char *p = buffer;
		while (*p)
		{
			if (*p != ' ')
			{
				return false;
			}
			p++;
		}
		return true;
	}

	///判断是否合法
	///@return	true表示合法，false表示不合法
	bool isValid(void) const
	{
		return true;
	}

	///转化为字符串
	///@return	得到的字符串
	operator const char *(void) const
	{
		return buffer;
	}

	///将右边的空格删除
	void trimRight(void)
	{
		char *p = buffer + strlen(buffer) - 1;
		while (p >= buffer)
		{
			if (*p != ' ')
			{
				break;
			}
			*p = '\0';
			p--;
		}
	}

	///判断是否小于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator < (const char *r) const
	{
		return strcmp(buffer, r) < 0;
	}

	///判断是否大于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator > (const char *r) const
	{
		return strcmp(buffer, r) > 0;
	}

	///判断是否小于等于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator <= (const char *r) const
	{
		return strcmp(buffer, r) <= 0;
	}

	///判断是否大于等于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator >= (const char *r) const
	{
		return strcmp(buffer, r) >= 0;
	}

	///判断是否等于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator == (const char *r) const
	{
		return strcmp(buffer, r) == 0;
	}

	///判断是否不等于某个字符串
	///@param	r	右边项
	///@return	true表示是，false表示否
	bool operator != (const char *r) const
	{
		return strcmp(buffer, r) != 0;
	}

	///产生hash值
	///@param	seed	种子
	///@return	得到的hash值
	unsigned int hash(unsigned int seed) const
	{
		unsigned long ret = seed;
		const char *str = buffer;

		if (*str == '\0')
		{
			return(ret);
		}
		long n = 0x100;
		while (*str)
		{
			unsigned long v = n | (*str);
			n += 0x100;
			int r = (int)((v >> 2) ^ v) & 0x0f;
			ret = (ret << r) | (ret >> (32 - r));
			ret &= 0xFFFFFFFFL;
			ret ^= v * v;
			str++;
		}
		return ((ret >> 16) ^ ret);
	}


protected:
	///存储字符串的值
	char buffer[length + 1];
};

#define DefineBigDecimalType(length,precision,newType)			\
	typedef CUFBigDecimalType<length,precision> C ## newType;	\
	typedef const CUFBigDecimalType<length,precision> CReadOnly ## newType;

#define DefineBigDecimalType(length,precision,newType)			\
	typedef CUFBigDecimalType<length,precision> C ## newType;	\
	typedef const CUFBigDecimalType<length,precision> CReadOnly ## newType;


DefineBigDecimalType(36,18,VolumeType)

#endif