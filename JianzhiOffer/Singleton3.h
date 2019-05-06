//饿汉模式

#ifndef SINGLETON3_H
#define SINGLETON3_H

#include <iostream>
using namespace std;

class Singleton3 {
	Singleton3() { cout << "create" << endl; }
	Singleton3(const Singleton3& s){}
	Singleton3& operator=(const Singleton3 &s){}
	~Singleton3();
	static Singleton3* instance;
public:
	static Singleton3* getInstance();
};

#endif  // SINGLETON3_H

//注意点
//1.饿汉模式：类加载进来就实例化
//2.因为类加载时就初始化，不会有线程安全问题
//3.虽然静态变量在程序结束时由程序自动销毁，但是instance指向的内存要在析构函数中手动delete
