#include "Singleton3.h"

Singleton3* Singleton3::instance = new Singleton3();
Singleton3::~Singleton3() {
	delete instance;
}
Singleton3* Singleton3::getInstance() {
	return instance;
}