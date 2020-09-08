#pragma once


#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <fstream>
#include <iostream>  
#include <sstream>  
#include <experimental/filesystem>  

using namespace std;
namespace fs = std::experimental::filesystem;

class CString
{
public:

	// Fetches the files in the directory
	static std::vector<std::string> RetrieveFiles(const std::string& directory);

	// Fetches the files which are of the type requested
	static std::vector<std::string> RetrieveFilesOfType(const std::string& directory, const std::string& fileType);

	// Format ex: "%.2f", Args ex: deltaTime
	template<typename ... Args>
	static std::string FormatString(const std::string& format, Args ... args);
	
	// Splits the string by the delimiter
	static std::vector<std::string> Split(const std::string& input, char delimiter);

	// Returns the file-type, for ex. ".png" or ".obj"
	static std::string FileType(const std::string& filePath);

	// Concats the path of the object
	static std::string ExcludeFileFromPath(const std::string& filePath);

	// Retrieves the filename of an object 
	static std::string GetFileFromFullPath(const std::string& filePath);


	
};

inline std::vector<std::string> CString::RetrieveFilesOfType(const std::string& directory, const std::string& fileType)
{
	std::vector<std::string> files;

	for (const auto& entry : fs::directory_iterator(directory))
	{
		std::string path = entry.path().generic_string();
		std::string type = FileType(path);
		std::string file = GetFileFromFullPath(path);

		if (type == fileType)
			files.push_back(file);
	}

	return files;
}

inline std::vector<std::string> CString::RetrieveFiles(const std::string& directory)
{
	std::vector<std::string> files;

	for (const auto& entry : fs::directory_iterator(directory))
	{
		std::string path = entry.path().generic_string();
		std::string file = GetFileFromFullPath(path);
		files.push_back(file);
	}

	return files;
}

template <typename ... Args>
std::string CString::FormatString(const std::string& format, Args... args)
{
	const size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; 

	const std::unique_ptr<char[]> buffer(new char[size]);

	// ty C++11
	snprintf(buffer.get(), size, format.c_str(), args ...);

	// skip the '\0' 
	return std::string(buffer.get(), buffer.get() + size - 1); 
}

inline std::vector<std::string> CString::Split(const std::string& input, const char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(input);

	while (getline(tokenStream, token, delimiter))
		tokens.push_back(token);

	return tokens;
}

inline std::string CString::FileType(const std::string& filePath)
{
	return filePath.substr(filePath.size() - 4, 4);
}

inline std::string CString::ExcludeFileFromPath(const std::string& filePath)
{
	return filePath.substr(0, filePath.find_last_of('/')) + "/";
}

inline std::string CString::GetFileFromFullPath(const std::string& filePath)
{
	const size_t i = filePath.rfind('/', filePath.length());

	std::string trimmed = filePath.substr(i + 1, filePath.length() - i);

	return trimmed;
}