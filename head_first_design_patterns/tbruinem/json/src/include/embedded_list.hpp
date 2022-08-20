#pragma once

namespace json {

struct EmbeddedList {
	EmbeddedList(void* holder) : holder(holder), next(nullptr), prev(nullptr) {}
	void*		holder;
	EmbeddedList* next;
	EmbeddedList* prev;

	EmbeddedList* Next() {
		return next;
	}
	EmbeddedList* Previous() {
		return prev;
	}
	void SetPrevious(EmbeddedList* element) {
		prev = element;
	}
	void AddBack(EmbeddedList* element) {
		if (next) {
			next->AddBack(element);
			return;
		}
		next = element;
		element->SetPrevious(this);
	}
};

} //namespace json
