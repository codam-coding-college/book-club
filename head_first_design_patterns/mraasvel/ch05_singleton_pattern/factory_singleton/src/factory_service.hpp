#pragma once

#include "iservice.hpp"
#include <unordered_map>
#include <memory>

class FactoryService {
private:
	FactoryService();

public:
	~FactoryService();

	CleverPointer<IService> build(std::string type);
	void add_service(std::string type, std::unique_ptr<IService> instance);
	static FactoryService& get();

private:
	std::unordered_map<std::string, std::unique_ptr<IService>> services;
};
