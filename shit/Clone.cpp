#include "Clone.h"
#include "Client/Client.h"

void Clone::operator()(std::string url)
{
	getFiles(url, "", "master");
}
