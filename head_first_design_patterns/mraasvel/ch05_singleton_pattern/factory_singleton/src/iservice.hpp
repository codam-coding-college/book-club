#pragma once

#include "clever_pointer.hpp"

class FactoryService;

class IService {
public:
	virtual CleverPointer<IService> clone(FactoryService& factory) = 0;
	virtual ~IService() {};
};
