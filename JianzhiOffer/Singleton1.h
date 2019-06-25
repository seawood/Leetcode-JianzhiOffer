//懒汉式1
#ifndef SINGLETON1_H
#define SINGLETON1_H

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

//注意点
//1.构造函数和赋值运算符被声明为private，防止被外部调用实例化
//2.在析构函数中释放内存
//3.线程安全：加锁和双重检查（第一次检查是为了效率，只有在instance为nullptr时才尝试获取锁；
//第二次检查是因为在第一次检查到获取锁期间，实例有可能已经被别的线程创建了，因此要再检查一次）
//4.懒汉式：在第一次调用getInstance时生成实例