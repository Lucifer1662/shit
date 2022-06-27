#include "Commands.h"
#include "Shit.h"
#include "glob/glob.h"
#include "Snapshot.h"
#include "Commit.h"
#include "Server/RemoteServer.h"
#include "Push.h"
#include "Host.h"
#include "Init.h"
#include "Clone.h"



std::unordered_map<std::string, void (Command::*)()> Command::initCommands() {
	std::unordered_map<std::string, void (Command::*)()> commands;
	commands[std::string("add")] = &Command::add;
	commands[std::string("checkout")] = &Command::checkout;
	commands[std::string("clone")] = &Command::clone;
	commands[std::string("commit")] = &Command::commit;
	commands[std::string("branch")] = &Command::branch;
	commands[std::string("host")] = &Command::host;
	commands[std::string("push")] = &Command::push;
	commands[std::string("pull")] = &Command::push;
	commands[std::string("init")] = &Command::init;
	return commands;
}

void Command::execute() {
	auto commandIt = commands.find(action);
	if (commandIt != commands.end()) {
		auto funcP = commandIt->second;
		(this->*funcP)();
	}
}

void Command::init()
{
	auto shit = Shit();
	Init(shit)();

}


void Command::add() {
	
	Shit shit = Shit();
	std::vector<std::string> paths;
	for (auto& param : params) {
		auto path = shit.workingDirectory + param;


		glob::Glob globber(path);
		while (globber){
			auto path = globber.GetFileName();
			paths.push_back(path);
			std::cout << path << std::endl;
			globber.Next();
		};
	}


	stage(paths);
}

void Command::clone() {
	auto c = Clone();
	c("http://127.0.0.1:34568");
}

void Command::commit() {

	std::string message;

	for (size_t i = 0; i < params.size(); i++)
	{
		if (params[i] == "-m") {
			if (i + 1 < params.size())
				message = params[i + 1];
		}
	}

	std::cout << "Starting Commit" << std::endl;

	
	Shit shit = Shit();
	auto head = Snapshot::getHeadKey(shit);
	std::string previous;
	if (head)
		previous = *head;

	

	Commit commit(shit, previous, std::string(message));
	auto snapshot = commit();
	auto branch = Branch::currentBranch(shit);
	if (branch) {
		branch->setSnapshot(snapshot.getKey());
	}
}

void Command::host()
{
	Shit shit = Shit();
	Host host = Host(shit);
	host();
}

void Command::push()
{
	Push push("http://127.0.0.1:34568");
	push();
}

void Command::pull()
{
}
