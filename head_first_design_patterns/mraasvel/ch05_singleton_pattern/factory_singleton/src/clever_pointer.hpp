#pragma once

#include <memory>
#include <iostream>

/*
class stores either unique pointer or regular pointer based on ownership status
*/

template <typename T>
class CleverPointer {
public:
	using owned_type = std::unique_ptr<T>;
	using borrowed_type = T*;

	CleverPointer()
	: owned(nullptr), borrowed(nullptr) {}

	template <typename U>
	CleverPointer(std::unique_ptr<U> owned)
	: owned(std::move(owned)), borrowed(nullptr) {}

	template <typename U>
	CleverPointer(U* borrowed)
	: owned(nullptr), borrowed(borrowed) {}

	T& operator*() const {
		if (owned != nullptr) {
			return *owned;
		} else {
			return *borrowed;
		}
	}

	T* operator->() const {
		if (owned != nullptr) {
			return &(*owned);
		} else {
			return &(*borrowed);
		}
	}

	// Todo: conversion SFINAE for clear error message
	// move pointers into returned pointer
	template <typename U>
	CleverPointer<U> convert() {
		CleverPointer<U> p ((U*)nullptr);
		if (owned != nullptr) {
			p = CleverPointer<U>(
				std::unique_ptr<U> (static_cast<U*>(owned.release()))
			);
		} else {
			p = CleverPointer<U>(static_cast<U*>(borrowed));
		}
		owned = nullptr;
		borrowed = nullptr;
		return p;
	}

private:
	owned_type owned;
	borrowed_type borrowed;
};
