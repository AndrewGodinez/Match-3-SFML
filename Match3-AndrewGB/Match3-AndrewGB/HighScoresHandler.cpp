#include "HighScoresHandler.h"


HighScoresHandler::HighScoresHandler() {
    head = nullptr;
    tail = nullptr;
    scoreCount = 0;
}

HighScoresHandler::~HighScoresHandler() {
    clearList();
}

void HighScoresHandler::clearList() {
    Node<ScoreEntry>* current = head;
    while (current != nullptr) {
        Node<ScoreEntry>* next = current->getNext();
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    scoreCount = 0;
}

void HighScoresHandler::initialize(int level) {
    std::string filename = "highscores_level_" + std::to_string(level) + ".xml";
    scoreFile.setFileName(filename);
    if (!scoreFile.openIn()) {
        scoreFile.createFileWithRoot("highscores");
    }
}

void HighScoresHandler::loadHighScores(int level) {
    clearList();
    initialize(level);
    int entryCount = scoreFile.countTags("entry");
    for (int i = 0; i < entryCount; i++) {
        std::string scoreStr = scoreFile.getTagAt("score", i);
        std::string playerName = scoreFile.getTagAt("name", i);
        
        if (!scoreStr.empty()) {
            int score = std::stoi(scoreStr);
            ScoreEntry entry(score, playerName);
            insertSorted(entry);
        }
    }
}

void HighScoresHandler::insertSorted(const ScoreEntry& entry) {
    Node<ScoreEntry>* newNode = new Node<ScoreEntry>(entry);
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        scoreCount = 1;
        return;
    }
    if (entry.score >= head->getData().score) {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
        scoreCount++;
        return;
    }
    if (entry.score <= tail->getData().score) {
        if (scoreCount < MAX_SCORES) {
            tail->setNext(newNode);
            newNode->setPrev(tail);
            tail = newNode;
            scoreCount++;
        }
        else {
            delete newNode;
        }
        return;
    }
    Node<ScoreEntry>* current = head;
    while (current != nullptr && current->getData().score > entry.score) {
        current = current->getNext();
    }
    Node<ScoreEntry>* prev = current->getPrev();
    newNode->setNext(current);
    newNode->setPrev(prev);
    if (prev != nullptr) {
        prev->setNext(newNode);
    }
    current->setPrev(newNode);
    scoreCount++;
    if (scoreCount > MAX_SCORES) {
        removeLowestScore();
    }
}

void HighScoresHandler::removeLowestScore() {
    if (tail == nullptr || scoreCount == 0) return;
    Node<ScoreEntry>* toDelete = tail;
    if (tail->getPrev() != nullptr) {
        tail = tail->getPrev();
        tail->setNext(nullptr);
    } else {
        // Solo había un nodo
        head = nullptr;
        tail = nullptr;
    }
    delete toDelete;
    scoreCount--;
}

void HighScoresHandler::addNewScore(int score, const std::string& playerName) {
    ScoreEntry entry(score, playerName);
    if (scoreCount < MAX_SCORES) {
        insertSorted(entry);
        return;
    }
    if (tail != nullptr && score > tail->getData().score) {
        insertSorted(entry);
    }
}

void HighScoresHandler::saveHighScores(int level) {
    initialize(level);
    scoreFile.clearAllTags();
    Node<ScoreEntry>* current = head;
    while (current != nullptr) {
        ScoreEntry entry = current->getData();
        scoreFile.addEntry("entry", "score", std::to_string(entry.score), "name", entry.playerName);
        current = current->getNext();
    }
}

int HighScoresHandler::getHighScore() const {
    if (head != nullptr) {
        return head->getData().score;
    }
    return 0;
}

int HighScoresHandler::getScoreAt(int position) const {
    if (position < 0 || position >= scoreCount) {
        return 0;
    }
    
    Node<ScoreEntry>* current = head;
    for (int i = 0; i < position && current != nullptr; i++) {
        current = current->getNext();
    }
    
    return (current != nullptr) ? current->getData().score : 0;
}

std::string HighScoresHandler::getPlayerNameAt(int position) const {
    if (position < 0 || position >= scoreCount) {
        return "";
    }
    
    Node<ScoreEntry>* current = head;
    for (int i = 0; i < position && current != nullptr; i++) {
        current = current->getNext();
    }
    
    return (current != nullptr) ? current->getData().playerName : "";
}

int HighScoresHandler::getScoreCount() const {
    return scoreCount;
}
