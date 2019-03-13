//懒汉式2
#ifndef SINGLETON2_H
#define SINGLETON2_H

#include <iostream>
using namespace std;

class Singleton2 {
	Singleton2() { std::cout << "create" << std::endl; }
	Singleton2(const Singleton2&) {}
	Singleton2& operator=(const Singleton2&){}
	~Singleton2() { std::cout << "Destroy" << std::endl; }
	
public:
	static Singleton2* getInstance();
};

#endif  // SINGLETON2_H

//注意点
//1.因为局部静态变量只会被初始化一次，所以是线程安全的，不需要加锁（但我看到有的代码是加锁的？）
//2.getInstance返回指针而不是引用？
