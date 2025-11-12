#pragma once 
#include "Node.h"
#include "File.h"
#include <string>

struct ScoreEntry {
    int score;
    std::string playerName;
    
    ScoreEntry(int s = 0, const std::string& name = "") : score(s), playerName(name) {}
};

class HighScoresHandler {
private:
    XmlFile scoreFile;
    Node<ScoreEntry>* head;
    Node<ScoreEntry>* tail;
    int scoreCount;
    static const int MAX_SCORES = 10;
    
    void insertSorted(const ScoreEntry& entry);
    void removeLowestScore();
    void clearList();
public:
    HighScoresHandler();
    ~HighScoresHandler();
    void initialize(int level);
    void loadHighScores(int level);
    void addNewScore(int score, const std::string& playerName);
    void saveHighScores(int level);
    int getHighScore() const;
    int getScoreAt(int position) const;
    std::string getPlayerNameAt(int position) const;
    int getScoreCount() const;
};