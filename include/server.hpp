#include <string>
#include <unistd.h>
#include "clientRequest.hpp"
#include "location.hpp"
#include "config.hpp"



class Server
{
  private:
    int _serverSocket;
    std::string _endpoint;
    location_t* _locationList;
    const Config& _config;

    void    _sigintHandle(int signum);
    int _createServerSocket(int port);
    bool _checkLocation(const ClientRequest& clientRequest);

  public:
    Server();
    Server(int port, const std::string& endpoint, const Config& config);
    Server(const Config& config);
    Server(const Server& server);
    ~Server();
    Server &operator=(const Server& server);
    void start(void);
};
