#ifndef C___USER_H
#define C___USER_H
#include <string>
#include "functions.h"
#include "Post.h"
#include "Chat.h"
#include "Message.h"

#define MAX_NAME 49 //Max string length + NULL
#define MAX_EMAIL 49 //Max string length + NULL
#define MAX_ID 2147483647


class User {
private:
    // Class based static variables
    static User* usersTable[MAX_USERS];
    
    // Object based variables
    int userID;
    std::string name;
    std::string email;
    User** friends; //Array of pointers for each user, Always make sure NULL terminated
    int Fcount; //Keep track of number of friends per user
    struct Chat** userChats; //Store chats you have with users, allocate memory as you increase chats, Always NULL terminated
    int chatCount; //To keep track of the chats between users
    struct Post* postsHead;
    struct Post* postsTail;
    int postCount;

    void init();
    Chat* getChat(User* user1); //Helper function to return the chat between 2 users
    void addFriend(User* newFriend);



public:
    // Static methods
    static User* search_user_by_name(const std::string& name);
    static User* search_user_by_email(const std::string& email);
    
    // Chat methods
    Chat* createChat(User* otherUser);
    void sendMessage(User* receiver, const std::string& content);
    void displayChat(User* otherUser);
    bool isFriendsWith(User* otherUser) const;
    
    // Constructors
    User(); //Default constructor
    User(const std::string& newName, const std::string& newEmail);
    void setName(const std::string& newName);
    void setEmail(const std::string& newEmail);
    std::string getName();
    std::string getEmail();
    int getUserID() const;
    void printUser();
    void printFriends();
    void change_user_email(const std::string& new_email);
    void change_user_name(const std::string& new_name);
    //User* create_user(const char* name, const char* email); // int user_id is auto-generated to be unique
    Post* new_post(const std::string& content);
    void display_feed();
    void delete_friend(User* friendToRemove);
    void delete_user();
    void display_chat(User* user);
    //Post** getFeedPosts(User* user, int* totalPosts); //Helper function to return all posts for a user and their friends
    User** getFriends(); //Return a copy of users friends
    User** mutual_friends(User* otherUser); // returns an array of pointers to the mutual friends
    void print_mutual_friends(User** friends); // prints mutual friends' usernames in ascending order
    void print_user_list(User** users);
    static void makeFriends(User* user1, User* user2);
};

// Global user count
extern int globalUserCount;



#endif //C___USER_H
