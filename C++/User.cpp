#include "User.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <algorithm>
#include "functions.h"

int globalUserCount = 0;

User* User::usersTable[MAX_USERS] = {NULL};

User* User::search_user_by_name(const std::string& searchName) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (usersTable[i] != NULL && usersTable[i]->getName() == searchName) {
            return usersTable[i];
        }
    }
    return NULL;
}

User* User::search_user_by_email(const std::string& searchEmail) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (usersTable[i] != NULL && usersTable[i]->getEmail() == searchEmail) {
            return usersTable[i];
        }
    }
    return NULL;
}

void User::makeFriends(User* user1, User* user2) {
    user1->addFriend(user2);
    user2->addFriend(user1);
}


User::User(){
    this->init();
}

User::User(const std::string& newName, const std::string& newEmail){
    this->init();
    this->setName(newName);
    this->setEmail(newEmail);

    // Insert into the hash table
    User::usersTable[globalUserCount] = this;
    globalUserCount++;
}

void User::init(){
    this->userID = rand() % MAX_ID;
    this->Fcount = 0;
    this->friends = nullptr;
    this->userChats = nullptr;
    this->chatCount = 0;
    this->postsHead = nullptr;
    this->postsTail = nullptr;
    this->postCount = 0;
}

void User::setName(const std::string& newName){
    this->name = newName;
}

void User::setEmail(const std::string& newEmail){
    this->email = newEmail;
}

std::string User::getName(){
    return this->name;
}

std::string User::getEmail(){
    return this->email;
}

void User::change_user_name(const std::string& new_name) {
    if (new_name.length() > MAX_NAME) {
        std::cout << "Error: Name is too long (max " << MAX_NAME << " characters)\n";
        return;
    }
    this->setName(new_name);
    std::cout << "Username changed to: " << this->getName() << std::endl;
}

void User::change_user_email(const std::string& new_email) {
    if (new_email.length() > MAX_EMAIL) {
        std::cout << "Error: Email is too long (max " << MAX_EMAIL << " characters)\n";
        return;
    }
    this->setEmail(new_email);
    std::cout << "Email changed to: " << this->getEmail() << std::endl;
}

int User::getUserID() const {
    return userID;
}

void User::printUser(){
    std::cout << this->name << std::endl;;
}

void User::addFriend(User* newFriend) {
    //If new friend is NULL, return
    if (newFriend == NULL) {
        printf("Invalid user, cannot add friend.\n");
        return;
    }

    //Check if newFriend is already my friend
    for (int i = 0; i < this->Fcount; i++) {
        if (this->friends[i]->userID == newFriend->userID) {
            printf("Already friends\n");
            return;
        }
    }
    //Add newFriend to us
    //If we have no friends yet, allocate memory for first friend and for NULL terminator (+2)
    if (this->Fcount == 0) {
        this->friends = (User **) malloc(sizeof(User *) * (this->Fcount + 2));
        if (this->friends == NULL) {
            printf("USER 1: New friend allocation Failed.\n");
            return;
        }
    }
    else {
        //Reallocate memory
        //Dynamically add memory based on how many friends the user has
        this->friends = (User **) realloc(this->friends,
                                          sizeof(User *) * (this->Fcount + 2)); //Allocate 1 extra space for NULL
        if (this->friends == NULL) {
            printf("USER 1: Adding Memory for another friend failed.\n");
            return;
        }
    }

    //Increment amount of friends
    this->Fcount++;
    this->friends[this->Fcount - 1] = newFriend;
    this->friends[this->Fcount] = NULL; //Ensure the end of the friend array is null

}

void User::printFriends(){
    if (Fcount == 0 || friends == nullptr) {
        std::cout << name << " has no friends." << std::endl;
        return;
    }

    int userCount = 0;

    //Copy all valid entries into the array
    int i = 0;
    while (this->friends[i] != NULL) {
        if (this->friends[i] != NULL) {
            i++;
            userCount++;
        }
    }
    std::vector<User*> tempFriends(userCount);
    int index = 0;

    //Copy all valid entries into the array
    for (int i = 0; i < userCount; i++) {
        if (this->friends[i] != NULL) {
            tempFriends[index++] = this->friends[i];
        }
    }

    //Bubble sort users names within the hash table
    User *temp = NULL;
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            //Checks if element at i is greater than the next element. If so, swap
            if (tempFriends[j]->getName() > tempFriends[j + 1]->getName()) {
                temp = tempFriends[j];
                tempFriends[j] = tempFriends[j + 1];
                tempFriends[j + 1] = temp;
            }
        }
    }
    //Print out the ascending names list
    for (int i = 0; i < userCount; i++) {
        if (i < userCount - 1) { //Print all names but the last with a coma
            std::cout << tempFriends[i]->getName() << ",";
        } else {
            std::cout <<  tempFriends[i]->getName() << std::endl; //Print last name without a coma
        }
    }
}

void User::delete_friend(User* friendToRemove) {
    if (!friendToRemove) {
        std::cout << "Invalid friend pointer, cannot delete.\n";
        return;
    }

    // Find the friend in the array
    int index = -1;
    for (int i = 0; i < Fcount; i++) {
        if (friends[i] == friendToRemove) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return; // Friend not found, just return.
    }

    // Shift elements left
    for (int i = index; i <= Fcount - 1; i++) {
        friends[i] = friends[i + 1];
    }

    friends[Fcount - 1] = NULL;
    Fcount--;

    // Free memory if no friends are left
    if (Fcount == 0) {
        free(friends);
        friends = NULL;
    }

    // Call delete_friend on the other user, but ensure it hasn't already been deleted
    if (friendToRemove->Fcount > 0) {
        friendToRemove->delete_friend(this);
    }
}

User** User::mutual_friends(User* otherUser) {
    //Pointer to mutual friend list
    User** mutuals;
    int mutualCount = 0;

    for (int i = 0; i < this->Fcount; i++) { //Loop 1 iterates through user 1s friends
        for (int j = 0; j < otherUser->Fcount; j++) { //Loop 2 compares each friend of user 1 to user 2s friends
            if (this->friends[i] == otherUser->friends[j]) {
                //Found a match, add to mutual friend list
                if (mutualCount == 0) {
                    mutuals = (User**)malloc(sizeof(User *) * (mutualCount + 2));
                    if (mutuals == NULL) {
                        std::cout << "New mutual friend allocation Failed.\n";
                        return NULL;
                    }
                } else {
                    //Reallocate memory
                    //Dynamically add memory based on how many friends the user has
                    mutuals = (User**)realloc(mutuals, sizeof(User *) * (mutualCount + 2));
                    if (mutuals == NULL) {
                        std::cout << "New mutual friend reallocation Failed.\n";
                        return NULL;
                    }
                }
                mutuals[mutualCount] = this->friends[i];
                mutualCount++;
                break;
            }
        }
    }
    mutuals[mutualCount] = NULL;
    //No mutual friends were found between user1 and user2
    if (mutualCount == 0){
        std::cout << "No mutual friends were found between" << this->name << " and " << otherUser->name << ".\n";
        return NULL;
    }
    return mutuals;
}

void User::print_mutual_friends(User** friends) {
    print_user_list(friends);
}


void User::print_user_list(User** users){
    if (users == NULL) {
        std::cout << "No mutuals found";
        return;
    }

    int userCount = 0;

    //Copy all valid entries into the array
    int i = 0;
    while (users[i] != NULL) {
        if (users[i] != NULL) {
            i++;
            userCount++;
        }
    }

    std::vector<User*> tempFriends(userCount);
    int index = 0;

    //Copy all valid entries into the array
    for (int i = 0; i < userCount; i++) {
        if (users[i] != NULL) {
            tempFriends[index++] = users[i];
        }
    }

    //Bubble sort users names within the hash table
    User *temp = NULL;
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            //Checks if element at i is greater than the next element. If so, swap
            if (tempFriends[j]->name.compare(tempFriends[j + 1]->name) > 0) {
                temp = tempFriends[j];
                tempFriends[j] = tempFriends[j + 1];
                tempFriends[j + 1] = temp;
            }
        }
    }
    //Print out the ascending names list
    for (int i = 0; i < userCount; i++) {
        if (i < userCount - 1) { //Print all names but the last with a coma
            std::cout << tempFriends[i]->name << ",";
        } else {
            std::cout << tempFriends[i]->name; //Print last name without a coma
        }
    }
    std::cout << "\n";
}

void User::delete_user() {
    //If the users is NULL, return
    if (this == NULL){
        std::cout << "Invalid user, cannot delete the user.\n";
        return;
    }

    //Pass in copy of friends array
    User** friendsCopy = getFriends();
    //Delete this user from all friend lists
    int i = 0;
    while (friendsCopy[i] != NULL) {
        friendsCopy[i]->delete_friend(this);
        i++;
    }

    //Find user in the hash table
    for (int i = 0; i < MAX_USERS; i++) {
        //Make sure index isn't NULL and find the user to delete
        if(User::usersTable[i] != NULL && User::usersTable[i]->userID == this->userID){
            //Free memory before setting that index to NULL
            free(User::usersTable[i]);
            User::usersTable[i] = NULL;
            //decrease user count
            globalUserCount--;
            return;
        }
    }
    //User was never found in the hash table
    std::cout << "User not found.\n";
}

User** User::getFriends() {
    //Initialize copy
    User **friendsCopy;

    //Add memory for amount of friends
    friendsCopy = (User**)malloc(sizeof(User *) * (this->Fcount + 1)); //Incorporate 1 space for null
    if (friendsCopy == NULL) {
        std::cout << "New copy of friend list allocation Failed.\n";
        return NULL;
    }

    //To add to the list of friends
    int i;
    for (i = 0; i < this->Fcount; i++) {
        friendsCopy[i] = this->friends[i];
    }
    friendsCopy[i] = NULL;

    return friendsCopy;
}

bool User::isFriendsWith(User* otherUser) const {
    for (int i = 0; i < Fcount; i++) {
        if (friends[i] == otherUser) {
            return true;
        }
    }
    return false;
}

Chat* User::createChat(User* otherUser) {
    if (!isFriendsWith(otherUser)) {
        std::cout << "Cannot create chat: " << name << " and " 
                  << otherUser->getName() << " are not friends." << std::endl;
        return nullptr;
    }
    
    // Check if chat already exists
    for (int i = 0; i < chatCount; i++) {
        if (userChats[i]->involvesUser(otherUser)) {
            return userChats[i];
        }
    }
    
    // Create new chat
    Chat* newChat = new Chat(this, otherUser);
    
    // Add to both users' chat lists
    if (chatCount == 0) {
        userChats = new Chat*[1];
    } else {
        Chat** newChats = new Chat*[chatCount + 1];
        for (int i = 0; i < chatCount; i++) {
            newChats[i] = userChats[i];
        }
        delete[] userChats;
        userChats = newChats;
    }
    
    userChats[chatCount++] = newChat;
    return newChat;
}

void User::sendMessage(User* receiver, const std::string& content) {
    if (!isFriendsWith(receiver)) {
        std::cout << "Cannot send message: Users are not friends." << std::endl;
        return;
    }
    
    // Get or create chat
    Chat* chat = createChat(receiver);
    if (!chat) {
        return;
    }
    
    // Create and add message
    Message* msg = new Message(this, receiver, content);
    chat->addMessage(msg);
}

void User::displayChat(User* otherUser) {
    for (int i = 0; i < chatCount; i++) {
        if (userChats[i]->involvesUser(otherUser)) {
            userChats[i]->displayChat();
            return;
        }
    }
    std::cout << "No chat found between " << name << " and " 
              << otherUser->getName() << std::endl;
}

Post* User::new_post(const std::string& content) {
    Post* newPost = new Post(this, content);
    
    // If this is the first post
    if (postsHead == nullptr) {
        postsHead = postsTail = newPost;
    } else {
        // Add to end of list
        postsTail->next = newPost;
        postsTail = newPost;
    }
    
    postCount++;
    return newPost;
}

void User::display_feed() {
    std::cout << "=== " << name << "'s Feed ===\n";
    
    // First, collect all posts (user's posts and friends' posts)
    std::vector<Post*> allPosts;
    
    // Add user's own posts
    Post* current = postsHead;
    while (current != nullptr) {
        allPosts.push_back(current);
        current = current->next;
    }
    
    // Add friends' posts
    for (int i = 0; i < Fcount; i++) {
        current = friends[i]->postsHead;
        while (current != nullptr) {
            allPosts.push_back(current);
            current = current->next;
        }
    }
    
    // Sort posts by recency (most recent first)
    std::sort(allPosts.begin(), allPosts.end(), 
        [](Post* a, Post* b) { return a->getRecencyNum() > b->getRecencyNum(); });
    
    // Display most recent MAX_FEED posts
    int count = 0;
    for (Post* post : allPosts) {
        if (count++ >= MAX_FEED) break;
        post->displayPost();
    }
}