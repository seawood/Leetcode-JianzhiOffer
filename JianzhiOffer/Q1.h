#ifndef CMYSTRING_H
#define CMYSTRING_H

class CMyString {
public:
	CMyString& operator=(const CMyString& str) {
		if (&str != this) {
			CMyString tmp(str);
			int ptemp = tmp.m_pData;
			tmp.m_pData = m_pData;
			m_pData = ptemp;
		}
		return *this;
	}
private:
	int m_pData;
};
#endif
