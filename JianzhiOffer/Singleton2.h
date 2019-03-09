#ifndef SINGLETON2_H
#define SINGLETON2_H

/*利用一个局部静态变量达到延迟实例化、线程安全的单例模式*/

#include <iostream>

class Singleton2 {
	Singleton2() { std::cout << "create" << std::endl; }
	Singleton2(const Singleton2&) {}
	Singleton2& operator=(const Singleton2&){}
	~Singleton2() { std::cout << "Destroy" << std::endl; }
	
public:
	static Singleton2* getInstance();
};
#endif
