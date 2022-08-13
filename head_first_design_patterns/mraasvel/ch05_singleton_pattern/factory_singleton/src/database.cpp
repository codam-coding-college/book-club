#include "database.hpp"
#include "factory_service.hpp"
#include <memory>

CleverPointer<IService> DatabaseService::clone(FactoryService&) {
	return CleverPointer<IService>(this);
}

void DatabaseService::add(FactoryService& factory) {
	factory.add_service("database", std::unique_ptr<DatabaseService>(new DatabaseService {}));
}

CleverPointer<DatabaseService> DatabaseService::build(FactoryService& factory) {
	auto generic = factory.build("database");
	return generic.convert<DatabaseService>();
}
