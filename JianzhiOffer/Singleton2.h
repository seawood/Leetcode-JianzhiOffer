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
//1.因为局部静态变量只会被初始化一次，所以是线程安全的，不需要加锁
//2.getInstance返回指针而不是引用:如果返回的是引用，执行Singleton2 s21 = Singleton2::getInstance()时要执行一次复制即调用Singleton2(const Singleton2&)，
//这不符合单例模式不可复制的特点而且这个复制构造函数被声明为private，不可访问。
//3.构造函数Singleton2()在静态变量static Singleton2 instance初始化时被调用，仅初始化一次。