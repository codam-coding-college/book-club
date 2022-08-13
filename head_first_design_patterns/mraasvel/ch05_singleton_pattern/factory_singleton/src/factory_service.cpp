#include "factory_service.hpp"
#include <iostream>

FactoryService::FactoryService() {}

FactoryService::~FactoryService() {}

void FactoryService::add_service(std::string type, std::unique_ptr<IService> instance) {
	// unique pointer can only be moved since there is only one pointer allowed
	services[type] = std::move(instance);
}

// if it returns a singleton then it shouldn't be deleted, meaning this should be wrapped in some sort of memory management class
// similar to unique_ptr but with an owned/not_owned attribute
CleverPointer<IService> FactoryService::build(std::string type) {
	auto service = services.find(type);
	if (service == services.end()) {
		std::cout << "didn't find service" << std::endl;
	}
	return service->second->clone(*this);
}

FactoryService& FactoryService::get() {
	static FactoryService factory;
	return factory;
}
