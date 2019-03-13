#ifndef CMYSTRING_H
#define CMYSTRING_H

class CMyString {
public:
	CMyString& operator=(const CMyString& str) {  
		if (&str != this) {
			CMyString tmp(str);  //copy and swap
			int ptemp = tmp.m_pData;
			tmp.m_pData = m_pData;
			m_pData = ptemp;
		}
		return *this;
	}
private:
	char* m_pData;
};
#endif

// 注意点
// 1.返回类型要声明为该类型的引用:避免一次拷贝；
//	 实现连续赋值（如果返回的是值类型，要对return后面的对象进行一次拷贝得到一个临时对象，而临时对象是右值，不能放在=左边，所以指向a=b后不能继续执行=c
// 2.参数类型声明为const引用
// 3.避免自我赋值：效率；如果类的数据成员中含有指针，自我赋值是灾难性的（例如将指针p_赋值给指针p，那么要先将p所指向的内存释放掉，然后再进行复制）。
// 4.释放自身已有内存：因为创建了临时对象tmp，在出if结构时会自动调用析构函数，释放内存
// 5.深复制：创建临时对象tmp时复创建了指针，也创建了一块新的内存
// 6.异常安全：如果在创建临时对象tmp时申请内存抛出异常，那么此时实例还保持了原来的状态，符合异常安全