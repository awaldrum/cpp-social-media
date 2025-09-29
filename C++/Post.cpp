#include "Post.h"
#include <iostream>
#include <cstdlib>

static int globalRecencyCounter = 0;

Post::Post(User* author, const std::string& postContent) {
    user = author;
    postID = rand() % MAX_ID;
    content = postContent.substr(0, MAX_POST_CHARS);
    next = nullptr;
    likeCount = 0;
    userLikes = nullptr;
    recencyNum = ++globalRecencyCounter;
}

Post::~Post() {
    if (userLikes) {
        free(userLikes);
    }
}

void Post::addLike(User* user) {
    // Check if user already liked the post
    if (userLikes) {
        for (int i = 0; i < likeCount; i++) {
            if (userLikes[i] == user) {
                std::cout << "User has already liked this post.\n";
                return;
            }
        }
    }

    // First like
    if (likeCount == 0) {
        userLikes = (User**)malloc(sizeof(User*));
    } else {
        // Reallocate array to make space for new like
        User** newLikes = (User**)realloc(userLikes, sizeof(User*) * (likeCount + 1));
        if (newLikes == nullptr) {
            std::cout << "Failed to allocate memory for new like.\n";
            return;
        }
        userLikes = newLikes;
    }

    userLikes[likeCount++] = user;
    std::cout << user->getName() << " liked the post.\n";
}

void Post::displayPost() const {
    std::cout << "Post by " << user->getName() << ":\n";
    std::cout << content << "\n";
    std::cout << "Likes: " << likeCount << "\n";
    if (likeCount > 0) {
        std::cout << "Liked by: ";
        for (int i = 0; i < likeCount; i++) {
            std::cout << userLikes[i]->getName();
            if (i < likeCount - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }
    std::cout << "-------------------\n";
}