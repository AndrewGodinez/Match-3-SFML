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
	bool openIn();
	void openOut();
	void setFileName(std::string name);
};

class XmlFile : public File {
public:
	XmlFile();
	void createFileWithRoot(const std::string& rootTag);
	std::string getTag(const std::string& tag);
	std::string getTagAt(const std::string& tag, int index);
	void addTag(const std::string& tag, const std::string& content);
	void addEntry(const std::string& entryTag, const std::string& tag1, const std::string& content1, const std::string& tag2, const std::string& content2);
	void replaceTag(const std::string& tag, const std::string& newContent);
	int countTags(const std::string& tag);
	void removeTag(const std::string& tag);
	void clearAllTags();
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
	bool isTextOnFile(std::string text);
	std::string getFirstLine();
};