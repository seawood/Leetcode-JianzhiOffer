#ifndef SINGLETON1_H
#define SINGLETON1_H
/*懒汉式：第一次调用getInstance时生成实例
利用双重检查和加锁机制来确保线程安全
注意在析构函数中实现内存释放*/

#include <iostream>
#include <mutex>

class Singleton1 {
	Singleton1();
	Singleton1(const Singleton1&){}
	Singleton1& operator=(const Singleton1&){}
	~Singleton1();
	static Singleton1* instance;
	static std::mutex mu;

public:
	static Singleton1* getInstance();
};
#endif
