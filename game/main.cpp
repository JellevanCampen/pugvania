#include <iostream>
#include "game/pugvania_config.h"

int main()
{
	std::cout << "Pugvania V"
		<< PUGVANIA_VERSION_MAJOR << "."
		<< PUGVANIA_VERSION_MINOR << "."
		<< PUGVANIA_VERSION_PATCH << "."
		<< PUGVANIA_VERSION_TWEAK
		<< std::endl;

	std::cin;

	return 0;
}