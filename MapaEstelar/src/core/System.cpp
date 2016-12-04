#include "System.h"

int System::updateAll() {
	int result = 1;

	for (std::list<Component*>::iterator i = components.begin(); i != components.end(); i++) {
		result &= ((Component*)(*i))->update();
	}

	return result;
}