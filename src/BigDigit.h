#ifndef __BIG_DIGIT_H
#define __BIG_DIGIT_H

#ifdef _WIN32
typedef __int64 LONGINT;
#else
typedef long long LONGINT;
#endif

#define PREC_DEPTH 18	

class CFloat
{
public:
	CFloat();
	CFloat(const CFloat &f);
	CFloat(int v);
	CFloat(long v);
	CFloat(LONGINT v);
	CFloat(double v);
	CFloat(const char *s);

	void clear();
	int sign() const;
	static CFloat power();
	char *toString(char *buf) const;

	CFloat& abs();
	CFloat& trunc();
	CFloat& tail();

	CFloat& operator= (const CFloat &f);
	CFloat& operator= (int v);
	CFloat& operator= (long v);
	CFloat& operator= (LONGINT v);
	CFloat& operator= (double v);
	CFloat& operator= (const char *s);

	CFloat operator+ (const CFloat &f) const;
	void operator+= (const CFloat &f);

	CFloat operator- () const;
	CFloat operator- (const CFloat &f) const;
	void operator-= (const CFloat &f);

	CFloat operator* (const CFloat &f) const;
	void operator*= (const CFloat &f);
	CFloat& Multiply(const CFloat &f);

	CFloat operator/ (const CFloat &f) const;
	void operator/= (const CFloat &f);
	CFloat& Divide(const CFloat &f);

	CFloat operator% (const CFloat &f) const;

	int compare(const CFloat &f) const;
	bool operator> (const CFloat &f) const;
	bool operator>= (const CFloat &f) const;
	bool operator< (const CFloat &f) const;
	bool operator<= (const CFloat &f) const;
	bool operator== (const CFloat &f) const;
	bool operator!= (const CFloat &f) const;

	LONGINT m_integer;	
	LONGINT m_fraction;	
private:
	void assign(const CFloat &f);
	void assign(LONGINT v);
	void assign(double v);
	void assign(const char *s);
	void multiply(const CFloat &f, bool carry);
	void divide(const CFloat &f, bool carry);

	int m_sign;			
};

#endif
