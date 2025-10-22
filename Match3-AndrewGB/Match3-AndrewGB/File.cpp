#include "File.h"

File::File() {
	fileName = "";
}

void File::openIn() {
    try {
        inFile = std::ifstream(fileName);
        if (!inFile.is_open()) {
            throw - 1;
        }
    }
    catch (int e) {
        if (e == -1) {
            std::cerr << "No se pudo abrir el archivo para leer.\n"
                << "Programa Terminado\n";
            exit(e);
        }
    }
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

