#pragma once
#include <iostream>
#include <fstream>
#include <string>

class File {
protected:
	std::ifstream inFile;
	std::ofstream outFile;
	std::string fileName;
public:
	File();
	void openIn();
	void openOut();
	void setFileName(std::string name);
};

class XmlFile : public File {
public:
	XmlFile();
	std::string getTag(const std::string& tag);
};

class CsvFile : public File {
public:
	CsvFile();
	std::string getLine(int id);
};

class TxtFile : public File {
public:
	TxtFile();
	void replaceContent(std::string newContent);
	void addLine(std::string line);
};