#include "../include/Cgi.hpp"

std::string getExtension(std::string const &htmlPath) {
  size_t pos = htmlPath.find_last_of(".");
  size_t arg = htmlPath.find("?");
  if (pos ==
      std::string::npos) // si no encuentra punto devuelve string vaciobuildOk
    return "";
  if (arg != std::string::npos)
    return htmlPath.substr(pos, arg - pos);
  return htmlPath.substr(pos);
}

bool isCGI(std::string const &htmlPath, const Config &config) {
  std::string extension = getExtension(htmlPath);
  if (!config.getIsCgi())
    return false;
  if (extension != config.getCgiExt())
    return false;
  return (extension == ".py" || extension == ".php" || extension == ".sh" ||
          extension == ".pl" || extension == ".cgi" || extension == ".bin");
}

std::string determineInterpreter(std::string const &htmlPath) {
  std::string extension = getExtension(htmlPath);
  if (extension == ".py")
    return "/usr/bin/python3";
  else if (extension == ".php")
    return "/usr/bin/php";
  else if (extension == ".pl")
    return "/usr/bin/perl";
  else if (extension == ".sh")
    return "/bin/bash";
  else
    return ""; // para los .cgi
}

std::string extractMethod(std::string petition) {
  size_t pos = petition.find(" ");
  return petition.substr(0, pos);
}

std::string extractQuery(std::string petition) {
  size_t posQuestion = petition.find("?");
  if (posQuestion == std::string::npos)
    return ""; // si no hay query no se devuelve parametro
  size_t posHTTP = petition.find(" HTTP");
  if (posHTTP == std::string::npos)
    return petition.substr(posQuestion + 1); // por si no acaba en " HTTP"
  else
    return petition.substr(posQuestion + 1, posHTTP - posQuestion - 1);
}

char **vectorToArray(std::vector<std::string> envVars) {
  std::vector<std::string>::size_type size = envVars.size();
  char **env = new char *[size + 1];

  for (std::vector<std::string>::size_type i = 0; i < size; i++) {
    std::vector<std::string>::size_type len = envVars[i].length();
    env[i] = new char[len + 1];
    std::strcpy(env[i], envVars[i].c_str());
  }
  env[size] = NULL;
  return env;
}
