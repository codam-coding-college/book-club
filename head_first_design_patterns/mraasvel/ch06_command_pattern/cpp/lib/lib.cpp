#include "cmd.hpp"
#include "remote.hpp"
#include "commands/light_command.hpp"

using command_type = std::unique_ptr<ICommand>;

int run() {
	RemoteControl remote;
	Light light;
	remote.set_device(0,
		command_type { new LightOn { light } },
		command_type { new LightOff { light } });
	return 0;
}
