// functions.h
#include <time.h>
#include <inttypes.h>
#include <stdint.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define MAX_NAME 49 //Max string length + NULL
#define MAX_EMAIL 49 //Max string length + NULL
#define MAX_ID 2147483647 //Max num for int-type variable
#define MAX_ID 2147483647 //Max num for int-type variable
#define MAX_USERS 10000 //Max Users for platform
#define MAX_MESSAGE_CHARS 256 //Maximum characters to send to another user
#define MAX_MESSAGE_CHATS 50 //Maximum amount of chats between users
#define MAX_POST_CHARS 256 //Maximum characters per post
#define MAX_LIKES 2147483647 //Maximum likes (integer type)
#define MAX_FEED 20 //Maximum posts in a users feed

typedef struct User{
    int userID;
    char name[MAX_NAME + 1];   //Allocate fixed sized array allows for the maximum length + 1 extra for Null terminator
    char email[MAX_EMAIL + 1]; //Allocate fixed sized array allows for the maximum length + 1 extra for Null terminator
    struct User** friends; //Array of pointers for each user, Always make sure NULL terminated
    int Fcount; //Keep track of number of friends per user
    struct Chat** userChats; //Store chats you have with users, allocate memory as you increase chats, Always NULL terminated
    int chatCount; //To keep track of the chats between users
    struct Post* postsHead;
    struct Post* postsTail;
    int postCount;
} User;

typedef struct Hash{
    User* table[MAX_USERS]; //Create buckets
}Hash;

//Declare the hash table global, so it can be accessed from functions.c
extern Hash UserHashTable;

typedef struct Post{
    User* user;
    int postID;
    char content[MAX_POST_CHARS + 1];
    struct Post* next;
    int likeCount;
    User** userlikes; //A list of likes from users
    int recencyNum; //Global variable is assigned to this to give every post a number to determine its recency
} Post;

typedef struct Message{
    int messageID;
    User* sender;
    User* receiver;
    char content[MAX_MESSAGE_CHARS + 1];
    struct Message* next;
} Message;

typedef struct Chat{
    User* user1; //One of the users in the chat
    User* user2; //Other user in the chat
    Message* head; //Pointer to the start of the messages linked list
    Message* tail; //Pointer to the end of the messages linked list
    int messageCount; //To keep track of number of messages between 2 users
}Chat;

void add_friend(User* user1, User* user2); // users user1 and user2 are now friends
void add_like(Post* post, User* user); // user is the individual who liked the post
Chat* addMessageToChat(Message* message, Chat* chat); //Helper function to add the message to the linked list in Chat struct
int comparePostPosition(Post* post1, Post* post2); //Helper function that returns 1 if post 1 is older, -1 if post 2 is older or the same
Chat* createChat(User* user1, User* user2);
void change_user_email(User* user, char* new_email);
void change_user_name(User* user, char* new_name);
Message* create_message(User* sender, User* receiver, const char* content); // int message_id is auto-generated to be unique
User* create_user(const char* name, const char* email); // int user_id is auto-generated to be unique
void display_feed(User* user1);
void delete_friend(User* user1, User* user2); // users user1 and user2 are no longer friends
void delete_user(User* user); // user is deleted
void display_chat(User* user1, User* user2); // print messages in FIFO
Chat* getChat(User* user1, User* user2); //Helper function to return the chat between 2 users
Post** getFeedPosts(User* user, int* totalPosts); //Helper function to return all posts for a user and their friends
User** getFriends(User* user); //Return a copy of users friends
int hashKey(int userID); //create a hash key
User** mutual_friends(User* user1, User* user2); // returns an array of pointers to the mutual friends
Post* new_post(User* user, const char* content); // post id is auto-generated to be unique
void print_friends(User* user); // prints user's friends in ascending order
void print_message(Message* message);
void print_mutual_friends(User** friends); // prints mutual friends' usernames in ascending order
void print_user_list(User** users); //Helper code, Print users in the list in ascending order
void print_users(); // prints all usernames in ascending order
User* search_user_by_name(const char* name);
User* search_user_by_email(const char* email);
int sender_receiver_friends(User* sender, User* receiver); //Helper function to determine if the sender and receiver are friends
void sortPosts(Post** posts, int totPosts, User* user);
void testingParser(int arg1, char *arg2);
#endif
