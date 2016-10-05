#include "engine.h"
#include <iostream>
#include "engine_config.h"

namespace engine {

	void Engine::Initialize()	{
		std::cout << "Initializing Engine." << std::endl;
		std::cout << "Version: " 
			<< ENGINE_VERSION_MAJOR << "."
			<< ENGINE_VERSION_MINOR << "."
			<< ENGINE_VERSION_PATCH << "."
			<< ENGINE_VERSION_TWEAK
			<< std::endl;
	}

	void Engine::Start() {

	}

	void Engine::Stop() {

	}

	void Engine::Terminate() {
		std::cout << "Terminating Engine." << std::endl;
	}
}