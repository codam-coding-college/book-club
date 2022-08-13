#include <iostream>
#include <string>
#include <mutex>

using std::string;

class Configuration {
private:
	static constexpr char config_file[] = "/etc/program_name/default.conf";

	Configuration() {
		// maybe parse initial state from a configuration file
		std::cout << "Constructing Configuration" << std::endl;
	}

public:
/* Creation */

	static Configuration* build() {
		if (config == nullptr) {
			std::lock_guard<std::mutex> guard { build_mutex };
			if (config == nullptr) {
				config = new Configuration {};
			}
		}
		return config;
	}

	void f() const {}
	void g() {} // if there are any non-const functions then the singleton won't be thread-safe depending on the context

private:
	static Configuration* config;
	static std::mutex build_mutex;
};

Configuration* Configuration::config = nullptr;
std::mutex Configuration::build_mutex;

void f() {
	auto config = Configuration::build();
	// user updates settings
}

int main() {
	auto config = Configuration::build();

	f();
	// user might have updated settings and we still have access to it
	return 0;
}
