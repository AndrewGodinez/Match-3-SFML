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
            std::cerr << "No se pudo abrir el archivo para leer.\n";
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
            std::cerr << "No se pudo abrir el archivo para escribir.\n"
                << "Programa Terminado\n";
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
        if (line.find("<" + tag + ">") != std::string::npos) {
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


