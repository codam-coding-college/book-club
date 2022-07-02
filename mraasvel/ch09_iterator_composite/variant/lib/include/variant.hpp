#pragma once

#include "option.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

namespace variant {

// gross

/*
std::variant is a better solution obviously
*/
class Json {
	public:
		enum JsonType {
			Number,
			Boolean,
			String,
			Array,
			Object,
			Null
		};

	private:
		union JsonData {
			JsonData(int n);
			JsonData(bool b);
			JsonData(const std::string& s);
			JsonData(const std::vector<Json*>& array);
			JsonData(const std::unordered_map<std::string, Json*>& object);
			~JsonData();

			JsonData& operator=(const JsonData&) = delete;
			JsonData& operator=(JsonData&&) = delete;
			JsonData(JsonData&&) = delete;
			JsonData(const JsonData&) = delete;

			int n;
			bool b;
			std::string str;
			std::vector<Json*> array;
			std::unordered_map<std::string, Json*> object;
		};

	public:
		using PointerType = Json*;
		using ArrayType = std::vector<PointerType>;
		using ObjectType = std::unordered_map<std::string, PointerType>;

	public:
		Json();
		Json(int n);
		Json(bool b);
		Json(const std::string& s);
		Json(const ArrayType& array);
		Json(const ObjectType& object);
		~Json();

		Json& operator=(const Json&) = delete;
		Json& operator=(Json&&) = delete;
		Json(Json&&) = delete;
		Json(const Json&) = delete;

		JsonType get_type() const;
		int get_num() const;
		bool get_bool() const;
		const std::string& get_string() const;
		const ArrayType& get_array() const;
		const ObjectType& get_object() const;
	
	private:
		void destroy_int();
		void destroy_bool();
		void destroy_string();
		void destroy_array();
		void destroy_object();

	private:
		Option<JsonData> data;
		JsonType type;
};

}
