#include "Rating.h"
#include <string>
using std::string;

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
