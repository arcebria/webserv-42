#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <list>
#include <iostream>
#include "../include/Server.hpp"
#include "../include/Config.hpp"
#include "../include/PollManager.hpp"
#include <poll.h>
#include <cstdlib>
#include <list>

int main(int argc, char **argv)
{
	if (argc > 2) {
		std::cerr << GREEN << "Error: Only accepted 1 file or none argument for default config" << RESET << std::endl;
		std::exit(1);
	}
	std::list<Config> configList = (argc == 2) ? takeConfig(argv[1]) : takeConfig("configs/default.conf");
    if (configList.empty())
    	return 1;
    std::list<Server> serverList;
    for (std::list<Config>::iterator config = configList.begin(); config != configList.end(); ++config) {
        serverList.push_back(Server(*config));
    }
    PollManager pollManager(serverList);
    pollManager.start();
    return 0;
}
