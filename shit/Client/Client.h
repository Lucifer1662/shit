#include <string>

std::string getContent(std::string remotePath, std::string path);
void get(std::string remotePath, std::string key);
void put(std::string remotePath, std::string path);
void getFiles(std::string remotePath, std::string snapshot, std::string branch);