#include "WorkingDirectory.h"
#include <filesystem>
#include <iostream>
#include "Path.h"


template<typename Func>
void RemovalThatDontMatch(std::string current_directory, Func shouldIgnore) {
	for (const auto& entry : std::filesystem::directory_iterator(current_directory)) {
		std::cout << entry.path() << std::endl;
		if (!shouldIgnore(entry)) {
			if (entry.is_directory()) {
				RemovalThatDontMatch(entry.path().string(), shouldIgnore);
			}
			std::filesystem::remove(entry.path());
		}

	}
}

auto shitIgnore = [](const std::filesystem::directory_entry& f) {
	return f.path().string().find(".shit") != std::string::npos;
};

void WorkingDirectory::PlaceSnapshotIn(const Snapshot& snapshot)
{

	RemovalThatDontMatch(Shit::Path::workingDirectory, shitIgnore);

	for (auto& [obj, path] : snapshot.objects) {
		auto directory = std::filesystem::path(Shit::Path::workingDirectory + path).remove_filename();
		std::filesystem::create_directories(directory);
		std::filesystem::copy_file(obj.getPath(), Shit::Path::workingDirectory + path);
	}
}


template<typename Func>
void getFilesRecurse(std::vector<std::pair<File::Key, std::string>>& files, std::string current_directory,
	Func shouldIgnore) {
	for (const auto& entry : std::filesystem::directory_iterator(current_directory)) {
		if (!shouldIgnore(entry)) {
			if (entry.is_directory()) {
				getFilesRecurse(files, entry.path().string(), shouldIgnore);
			}
			else if (entry.is_regular_file()) {
				auto path = entry.path().string();
				path = path.substr(Shit::Path::workingDirectory.length());
				files.push_back(std::make_pair(File::getKeyFromFile(path), path));
			}
		}
	}
}

std::vector<std::pair<File::Key, std::string>> WorkingDirectory::getFiles()
{
	std::vector<std::pair<File::Key, std::string>> files;

	getFilesRecurse(files, Shit::Path::workingDirectory, shitIgnore);

	return files;
}
