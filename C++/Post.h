#ifndef C___POST_H
#define C___POST_H

#include "User.h"
#include <string>

#define MAX_POST_CHARS 256
#define MAX_LIKES 2147483647
#define MAX_FEED 20

class Post {
private:
    User* user;
    int postID;
    std::string content;
    Post* next;
    int likeCount;
    User** userLikes;  // Array of users who liked the post
    int recencyNum;    // Global number to determine post recency

public:
    Post(User* author, const std::string& postContent);
    ~Post();
    
    void addLike(User* user);
    void displayPost() const;
    int getLikeCount() const { return likeCount; }
    int getRecencyNum() const { return recencyNum; }
    User* getAuthor() const { return user; }
    std::string getContent() const { return content; }
    
    friend class User;  // Allow User class to access private members
};

#endif // C___POST_H