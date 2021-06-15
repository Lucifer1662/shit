#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>


namespace Shit { 
	
	class Command {
		std::string action;
		std::vector<std::string> params;
		std::unordered_map<std::string, void (Command::*)()> commands = initCommands();


		std::unordered_map<std::string, void (Command::*)()> initCommands();

	public:
		Command(std::string action, std::vector<std::string> params) :action(action), params(params) { }
		Command(std::string action, const char** params, const int nparams) :action(action), params(params, params+nparams) {}

	
		
	
		void execute();

		void init();

		void add();

		void checkout() {

		}

		void clone();
		void commit();
		void branch() {

			

		}

		void host();


		void push();

		void pull();
	};
}