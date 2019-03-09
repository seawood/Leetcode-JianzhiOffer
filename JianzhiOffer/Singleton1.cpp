#include "Singleton1.h"
using namespace std;

mutex Singleton1::mu;
Singleton1* Singleton1::instance = nullptr;

Singleton1::Singleton1() {
	cout << "Create" << endl;
}

Singleton1::~Singleton1() {
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
	cout << "Destroy" << endl;
}

Singleton1* Singleton1::getInstance() {
	if (instance == nullptr)
	{
		lock_guard<mutex> mlock(mu);
		if (instance == nullptr)
			instance = new Singleton1();
	}
	return instance;
}

