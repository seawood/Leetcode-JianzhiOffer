#include "Singleton2.h"

Singleton2* Singleton2::getInstance() {
	static Singleton2 instance; 
	return &instance;
}