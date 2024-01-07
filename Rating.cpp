#include "Rating.h"
#include <string>
using std::string;

// Rating::Rating(std::vector<int>* scoresPtr, std::vector<std::string>* commentsPtr)
//     : scores(scoresPtr ? scoresPtr : new std::vector<int>), comments(commentsPtr ? commentsPtr : new std::vector<std::string>) {}

// // Destructor to free allocated memory
// Rating::~Rating() {
//     delete scores;
//     delete comments;
// }


// void Rating::addRating(int score, const std::string& comment) {
//     if (score > 10 || score < 0) {
//         throw std::invalid_argument("Invalid input! Score must be between 0 and 10");
//     } else {
//         scores->push_back(score);
//         comments->push_back(comment.empty() ? "" : comment);
//     }
// }
// void Rating::displayRating() {
//     std::cout << "Ratings:" << std::endl;
//     if (scores->empty() || comments->empty()) {
//         std::cout << "No ratings available." << std::endl;
//         return;
//     }

//     for (int i = 0; i < scores->size(); ++i) {
//         std::cout << "Score: " << (*scores)[i] << ", Comment: " << (*comments)[i] << std::endl;
//     }
// }

// float Rating::avgRating() const {
//     if (scores->empty()) {
//         return 0.0f; // Return 0 if there are no ratings
//     }

//     int totalScore = 0;
//     for (int score : *scores) {
//         totalScore += score;
//     }
//     float avgScore = static_cast<float>(totalScore) / scores->size();

//     return avgScore;
// }

Rating::Rating(float score_val, string comment_val)
: score(score_val), comment(comment_val) {};


float Rating::getScore() {
    return score;
}

string Rating::getComment() {
    return comment;
}


void Rating::insertRating(std::string& line, const std::string& ratingTag, const std::string& ratingString) {
    size_t pos = line.find(ratingTag);
    if (pos == std::string::npos) {
        // If the tag is not found, find the position to insert the new tag
        if (ratingTag == "[supporter|") {
            pos = line.find("[host|");
            if (pos == std::string::npos) pos = line.size(); // If host tag is not there, insert at end
        } else if (ratingTag == "[host|") {
            pos = line.size(); // Always insert host tag at the end
        }
    } else {
        pos = line.find("],[", pos) + 3; // Find the position right after the existing tag
    }
    line.insert(pos, ratingString + ",");
}
