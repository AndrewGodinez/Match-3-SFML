#include "File.h"

File::File() {
	fileName = "";
}

bool File::openIn() {
    try {
        inFile = std::ifstream(fileName);
        if (!inFile.is_open()) {
            throw - 1;
        }
    }
    catch (int e) {
        if (e == -1) {
            std::cerr << "ERROR: Failed to open file for reading: " << fileName << "\n";
            return false;
        }
    }
    return true;
}

void File::openOut() {
    try {
        outFile = std::ofstream(fileName, std::ios::app);
        if (!outFile.is_open()) {
            throw - 1;
        }
    }
    catch (int e) {
        if (e == -1) {
            std::cerr << "ERROR: Failed to open file for writing: " << fileName << "\n"
                << "Program terminated.\n";
            exit(e);
        }
    }
}

void File::setFileName(std::string name) {
    this->fileName = name;
}

XmlFile::XmlFile() {
}

std::string XmlFile::getTag(const std::string& tag) {
    std::string line;
    std::string route;
    std::string openTag = "<" + tag + ">";
    std::string closeTag = "</" + tag + ">";
    bool found = false;
    while (std::getline(inFile, line) && found != true) {
        if (line.find(openTag) != std::string::npos) {
            std::size_t start = line.find(openTag) + openTag.size();
            std::size_t end = line.find(closeTag);
            route = line.substr(start, end - start);
            found = true;
        }
    }
    try {
        if (route.empty()) {
            throw -1;
        }
    }
    catch (int e) {
        if (e == -1) {
            std::cerr << "No se encontro la ruta del tag: " << tag << "\n";
            exit(e);
        }
    }
    inFile.close();
    return route;
}

std::string XmlFile::getTagAt(const std::string& tag, int index) {
    openIn();
    std::string line;
    std::string result;
    std::string openTag = "<" + tag + ">";
    std::string closeTag = "</" + tag + ">";
    int currentIndex = 0;
    
    while (std::getline(inFile, line)) {
        if (line.find(openTag) != std::string::npos) {
            if (currentIndex == index) {
                std::size_t start = line.find(openTag) + openTag.size();
                std::size_t end = line.find(closeTag);
                result = line.substr(start, end - start);
                break;
            }
            currentIndex++;
        }
    }
    inFile.close();
    return result;
}

void XmlFile::createFileWithRoot(const std::string& rootTag) {
    outFile.open(fileName);
    if (!outFile.is_open()) {
        std::cerr << "ERROR: Failed to create XML file: " << fileName << "\n";
        exit(-1);
    }
    outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    outFile << "<" << rootTag << ">\n";
    outFile << "</" << rootTag << ">\n";
    outFile.close();
}

void XmlFile::addTag(const std::string& tag, const std::string& content) {
    openIn();
    std::string line;
    std::string tempFileName = "temp.xml";
    std::ofstream tempFile(tempFileName);
    if (!tempFile.is_open()) {
        std::cerr << "No se pudo crear el archivo temporal.\n";
        exit(-1);
    }
    std::string closeRootTag;
    while (std::getline(inFile, line)) {
        if (line.find("</") != std::string::npos) {
            closeRootTag = line;
            tempFile << "    <" << tag << ">" << content << "</" << tag << ">\n";
        }
        tempFile << line << "\n";
    }
    inFile.close();
    tempFile.close();
    std::remove(fileName.c_str());
    std::rename(tempFileName.c_str(), fileName.c_str());
}

void XmlFile::addEntry(const std::string& entryTag, const std::string& tag1, const std::string& content1, const std::string& tag2, const std::string& content2) {
    openIn();
    std::string line;
    std::string tempFileName = "temp.xml";
    std::ofstream tempFile(tempFileName);
    if (!tempFile.is_open()) {
        std::cerr << "No se pudo crear el archivo temporal.\n";
        exit(-1);
    }
    bool entryAdded = false;
    while (std::getline(inFile, line)) {
        if (!entryAdded && line.find("</") != std::string::npos && line.find("    ") == std::string::npos) {
            tempFile << "    <" << entryTag << ">\n";
            tempFile << "        <" << tag1 << ">" << content1 << "</" << tag1 << ">\n";
            tempFile << "        <" << tag2 << ">" << content2 << "</" << tag2 << ">\n";
            tempFile << "    </" << entryTag << ">\n";
            entryAdded = true;
        }
        tempFile << line << "\n";
    }
    inFile.close();
    tempFile.close();
    std::remove(fileName.c_str());
    std::rename(tempFileName.c_str(), fileName.c_str());
}

void XmlFile::replaceTag(const std::string& tag, const std::string& newContent) {
    openIn();
    std::string line;
    std::string tempFileName = "temp.xml";
    std::ofstream tempFile(tempFileName);
    if (!tempFile.is_open()) {
        std::cerr << "No se pudo crear el archivo temporal.\n";
        exit(-1);
    }
    std::string openTag = "<" + tag + ">";
    std::string closeTag = "</" + tag + ">";
    while (std::getline(inFile, line)) {
        if (line.find(openTag) != std::string::npos && line.find(closeTag) != std::string::npos) {
            tempFile << "    " << openTag << newContent << closeTag << "\n";
        } else {
            tempFile << line << "\n";
        }
    }
    inFile.close();
    tempFile.close();
    std::remove(fileName.c_str());
    std::rename(tempFileName.c_str(), fileName.c_str());
}

int XmlFile::countTags(const std::string& tag) {
    openIn();
    std::string line;
    int count = 0;
    std::string openTag = "<" + tag + ">";
    while (std::getline(inFile, line)) {
        if (line.find(openTag) != std::string::npos) {
            count++;
        }
    }
    inFile.close();
    return count;
}

void XmlFile::removeTag(const std::string& tag) {
    openIn();
    std::string line;
    std::string tempFileName = "temp.xml";
    std::ofstream tempFile(tempFileName);
    if (!tempFile.is_open()) {
        std::cerr << "No se pudo crear el archivo temporal.\n";
        exit(-1);
    }
    std::string openTag = "<" + tag + ">";
    std::string closeTag = "</" + tag + ">";
    while (std::getline(inFile, line)) {
        if (line.find(openTag) == std::string::npos || line.find(closeTag) == std::string::npos) {
            tempFile << line << "\n";
        }
    }
    inFile.close();
    tempFile.close();
    std::remove(fileName.c_str());
    std::rename(tempFileName.c_str(), fileName.c_str());
}

void XmlFile::clearAllTags() {
    openIn();
    std::string line;
    std::string tempFileName = "temp.xml";
    std::ofstream tempFile(tempFileName);
    if (!tempFile.is_open()) {
        std::cerr << "No se pudo crear el archivo temporal.\n";
        exit(-1);
    }
    std::string rootTag;
    std::string rootClosingTag;
    while (std::getline(inFile, line)) {
        if (line.find("<?xml") != std::string::npos) {
            tempFile << line << "\n";
        } 
        else if (line.find("<") != std::string::npos && line.find("</") == std::string::npos && 
                 line.find("    ") == std::string::npos && rootTag.empty()) {
            rootTag = line;
            tempFile << line << "\n";
        } 
        else if (line.find("</") != std::string::npos && line.find("    ") == std::string::npos && rootClosingTag.empty()) {
            rootClosingTag = line;
        }
    }
    if (!rootClosingTag.empty()) {
        tempFile << rootClosingTag << "\n";
    }
    inFile.close();
    tempFile.close();
    std::remove(fileName.c_str());
    std::rename(tempFileName.c_str(), fileName.c_str());
}


CsvFile::CsvFile() {
}

std::string CsvFile::getLine(int id) {
    if (!inFile.is_open()) {
        openIn();
    }
    inFile.clear();
    inFile.seekg(0, std::ios::beg);

    std::string line;
    std::string aux;
    std::string result;
    int currentLine = 0;
    bool found = false;
    while (std::getline(inFile, line) && !found) {
        if (currentLine == id) {
            aux = line;
            found = true;
        }
        currentLine++;
    }
    try {
        if (!found) {
            throw -1;
        }
    }
    catch (int e) {
        if (e == -1) {
            std::cerr << "No se encontro la linea: " << id << " en el archivo CSV\n";
            exit(e);
        }
    }
    for (int i = 0; i < (int)aux.size(); i++) {
        if (aux[i] != ',' && aux[i] != '\n' && aux[i] != '\r') {
            result += aux[i];
        }
    }
    return result;
}

TxtFile::TxtFile() {
    fileName = "";
}

void TxtFile::replaceContent(std::string newContent) {
    outFile = std::ofstream(fileName);
    try {
        if (!outFile.is_open()) {
            throw - 1;
        }
    }
    catch (int e) {
        if(e==-1) {
            std::cerr << "No se pudo abrir el archivo para escribir.\n"
                << "Programa Terminado\n";
            exit(e);
		}
    }
	outFile << newContent;
	outFile.close();

}

void TxtFile::addLine(std::string line) {
    openOut();
    try {
        outFile << line << "\n";
        outFile.close();
    }
    catch (int e) {
        if (e == -1) {
            std::cerr << "No se pudo abrir el archivo para escribir.\n"
                << "Programa Terminado\n";
            exit(e);
        }
    }
}

bool TxtFile::isTextOnFile(std::string text) {
	std::string line;
    while (std::getline(inFile, line)) {
        if (line == text) {
            inFile.close();
            return true;
        }
	}
	return false;
}

std::string TxtFile::getFirstLine() {
    std::string line;
    std::getline(inFile, line);
    return line;
}


