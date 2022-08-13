#pragma once

class Light {
	public:
		Light();
		void on();
		void off();

	private:
		bool is_on;
};
