#include "Singleton1.h"
#include "Singleton2.h"
int m1() {
	Singleton1* s11 = Singleton1::getInstance();
	Singleton1* s12 = Singleton1::getInstance();
	Singleton2* s21 = Singleton2::getInstance();
	Singleton2* s22 = Singleton2::getInstance();
	return 0;
}