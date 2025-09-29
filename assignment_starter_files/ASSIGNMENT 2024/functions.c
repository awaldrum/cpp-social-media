#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// WRITE FUNCTIONS BELOW
//Define a global post ID that assigns lower values to older messages, so it's easier to sort by recency in display feed
int globalPostNum;
//Global number of users
int globalUserCount = 0;

void add_friend(User* user1, User* user2){
    //If one of the users is NULL, return
    if ((user1 == NULL) || (user2 == NULL)){
        printf("Invalid users, cannot add friend.\n");
        return;
    }

    //Check if user 1 and user 2 are friends already
    for (int i = 0; i < user1->Fcount; i++){
        if(user1->friends[i]->userID == user2->userID) {
            printf("Already friends\n");
            return;
        }
    }
    //Add user2 to user1
    //If user has no friends yet, allocate memory for first friend and for NULL terminator (+2)
    if (user1->Fcount == 0){
        user1->friends = malloc(sizeof(User*) * (user1->Fcount + 2));
        if (user1->friends == NULL){
            printf("USER 1: New friend allocation Failed.\n");
            return;
        }
    }
    else {
        //Reallocate memory
        //Dynamically add memory based on how many friends the user has
        user1->friends = realloc(user1->friends,sizeof(User *) * (user1->Fcount + 2)); //Allocate 1 extra space for NULL
        if (user1->friends == NULL) {
            printf("USER 1: Adding Memory for another friend failed.\n");
            return;
        }
    }
    //Increment amount of friends
    user1->Fcount++;
    //Add user2 to user1's friends
    user1->friends[user1->Fcount - 1] = user2;
    user1->friends[user1->Fcount] = NULL; //Ensure the end of the friend array is null

    //add user1 to user2
    //If user has no friends yet, allocate memory for first friend and for NULL terminator
    if (user2->Fcount == 0){
        user2->friends = malloc(sizeof(User*) * (user2->Fcount + 2));
        if (user2->friends == NULL){
            printf("USER 2: New friend allocation Failed.\n");
            return;
        }
    }
    else {
        //Reallocate memory
        //Dynamically add memory based on how many friends the user has
        user2->friends = realloc(user2->friends,
                                 sizeof(User *) * (user2->Fcount + 2)); //Allocate 1 extra space for NULL
        if (user2->friends == NULL) {
            printf("USER 2: Adding Memory for another friend failed.\n");
            return;
        }
    }
    //Increment amount of friends
    user2->Fcount++;

    //Add user1 to user2's friends
    user2->friends[user2->Fcount - 1] = user1;
    user2->friends[user2->Fcount] = NULL; //Ensure the end of the friend array is null
}

void add_like(Post* post, User* user){
    //Determine if the user has already like the post
    for (int i = 0; i < post->likeCount; i++){
        if (post->userlikes[i] == user) {
            printf("User has already liked the post.\n");
            return;
        }
    }

    //Ensure the post doesn't have more likes than the max
    if (post->likeCount >= MAX_LIKES){
        printf("Post already has the maximum likes.\n");
        return;
    }


    //Allocate 1 new space in the array for the new user like
    if (post->likeCount == 0){
        post->userlikes = malloc(sizeof(User*) * (post->likeCount + 1)); //Allocate for 1 spot in user chat list
        if (post->userlikes == NULL){
            printf("New like chat allocation Failed.\n");
            return;
        }
    }
    else {
        //Reallocate memory
        //Dynamically add memory based on how many likes the user has
        post->userlikes = realloc(post->userlikes,sizeof(User*) * (post->likeCount + 1));// +1 more for an extra chat
        if (post->userlikes == NULL) {
            printf("Adding Memory for another like failed.\n");
            return;
        }
    }
    //Add that like to the list of likes and increment counter

    post->userlikes[post->likeCount] = user;
    post->likeCount++;
}

Chat* addMessageToChat(Message* message, Chat* chat){
    //Determine if this is the first message in the chat
    if (chat->head == NULL){
        chat->head = message;
        chat->tail = message;
    }
    else{
        //If not first message, add to end of linked list
        chat->tail->next = message; //Current tail's next is now the added message
        chat->tail = message; //Set tail to the new message
    }
    //For both cases, the next entity in list is NULL
    message->next = NULL;
    chat->messageCount++; //Increment chat count to keep track of total number of chats

    //If more than 50 messages, pop oldest message (head of list)
    //Point the head to the second message in list
    if (chat->messageCount == (MAX_MESSAGE_CHATS + 1)){
        Message* oldHead = chat->head; //Temp pointer to allow for freeing the old head
        chat->head = chat->head->next;
        free(oldHead); //Remove head (oldest message)
        chat->messageCount--;
    }
}

int comparePostPosition(Post* post1, Post* post2){
    if (post1->recencyNum < post2->recencyNum){
        return 1; //Post1 is older
    }
    else{
        return -1; //Post 2 is older
    }
}

Chat* createChat(User* user1, User* user2){
    //Allocate memory for a new chat
    Chat* chat = (Chat*)malloc(sizeof(Chat));
    if (chat == NULL){
        printf("User 1 New chat allocation failed.\n");
        return NULL;
    }

    //Initialize chat between 2 users
    chat->user1 = user1;
    chat->user2 = user2;
    chat->head = NULL; //Since no messages have been set yet
    chat->tail = NULL;
    chat->messageCount = 0;

   //Allocate 1 new space in the array for the new user chat
    if (user1->chatCount == 0){
        user1->userChats = malloc(sizeof(Chat*) * (user1->chatCount + 1)); //Allocate for 1 spot in user chat list
        if (user1->userChats == NULL){
            printf("USER 1: New user chat allocation Failed.\n");
            return NULL;
        }
    }
    else {
        //Reallocate memory
        //Dynamically add memory based on how many friends the user has
        user1->userChats = realloc(user1->userChats,sizeof(Chat*) * (user1->chatCount + 1));// +1 more for an extra chat
        if (user1->userChats == NULL) {
            printf("USER 1: Adding Memory for another user chat failed.\n");
            return NULL;
        }
    }

    //Allocate 1 new space in the array for the new user chat
    if (user2->chatCount == 0){
        user2->userChats = malloc(sizeof(Chat*) * (user2->chatCount + 1));
        if (user2->userChats == NULL){
            printf("USER 2: New user chat allocation Failed.\n");
            return NULL;
        }
    }
    else {
        //Reallocate memory
        //Dynamically add memory based on how many friends the user has
        user2->userChats = realloc(user2->userChats,sizeof(Chat*) * (user2->chatCount + 1)); // +1 more for an extra chat
        if (user2->userChats == NULL) {
            printf("USER 2: Adding Memory for another user chat failed.\n");
            return NULL;
        }
    }

    //Add chat to each users list of chats
    user1->userChats[user1->chatCount] = chat;
    user2->userChats[user2->chatCount] = chat;

    //Increment chat counts
    user1->chatCount++;
    user2->chatCount++;
    return chat;
}

User* create_user(const char* name, const char* email) {
    //Check if 10,000 users are already created
    if (globalUserCount >= MAX_USERS){
        printf("Too many users.\n");
        return NULL;
    }

    //Check if name or email is null
    if ((name == NULL) || (email == NULL)){
        printf("Create user failed, name or email is NULL");
        return NULL;
    }

    //Ensure name isn't too long
    if (strlen(name) > MAX_NAME){
        printf("Name is too long.\n");
        return NULL;
    }

    //Ensure email isn't too long
    if (strlen(email) > MAX_EMAIL){
        printf("Email is too long.\n");
        return NULL;
    }

    User *NewUser = (User *) malloc(sizeof(User)); //Allocate memory for NewUser
    if (NewUser == NULL) {
        printf("New User allocation failed.\n");
        return NULL;
    }
    int TempUserID;
    int Unique = 0;
    while (!Unique) {
        TempUserID = rand() % MAX_ID; //Generate Random ID that maxes out at MAX_ID (10000 users)
        Unique = 1; //Assume TempID is unique
        for (int i = 0; i < MAX_USERS; i++) { //Check if any previously created users already have that ID
            if (UserHashTable.table[i] != NULL && UserHashTable.table[i]->userID == TempUserID) {
                Unique = 0; //Means ID has been previously used. So redo.
                break;
            }
        }
    }
    NewUser->userID = TempUserID;
    strncpy(NewUser->name, name, MAX_NAME); //Move unique name into the new user
    strncpy(NewUser->email, email, MAX_EMAIL);  //Move unique email into the new user

    //Insert new user into table
    int hIndex = hashKey(NewUser->userID); //Find the index of the user
    while (UserHashTable.table[hIndex] != NULL) {
        hIndex = (hIndex + 1) % MAX_USERS; //Check if the following index is taken, if so, loop again till an empty spot is found
    }
    UserHashTable.table[hIndex] = NewUser; //Assign the index with that was previously NULL to the User

    //Brand-new user that has no friends yet, Set Fcount = 0
    NewUser->Fcount = 0;

    //Set chatCount to 0
    NewUser->chatCount = 0;

    //Set postCount to 0
    NewUser->postCount = 0;

    //Head/tail of the post linked list to null
    NewUser->postsHead = NULL;
    NewUser->postsTail = NULL;

    //Increment userCount
    globalUserCount++;

    return NewUser;
}

void display_feed(User* user1){
    int totPostsNum = 0;
   //Create function to gather all posts from user and their friends and store in temp array
   Post** totPosts = getFeedPosts(user1, &totPostsNum);

   //Sort posts in correct order using sortPosts function
    sortPosts(totPosts, totPostsNum, user1);

    //Allow a max of 20 posts on a users feed
    if (totPostsNum > MAX_FEED){
        for (int i = MAX_FEED; i < totPostsNum; i++){
            free(totPosts[i]);
        }
        totPosts = realloc(totPosts, (sizeof(Post*)) * MAX_FEED);
        totPostsNum = MAX_FEED; //Set total posts to 20
    }

   for (int i = 0; i < totPostsNum; i++) {
      printf("[%s:]%s", totPosts[i]->user->name, totPosts[i]->content);

      //Coma after every post except the last one in the feed
       if (i < (totPostsNum - 1)){
           printf(",");
       }
   }
}

void change_user_email(User* user, char* new_email){
    //Check if user and email is NULL
    if ((user == NULL) || (new_email == NULL)){
        printf("Invalid user or email, cannot change email.\n");
        return;
    }

    //Ensure email isn't too long
    if (strlen(new_email) > MAX_EMAIL){
        printf("Email is too long.\n");
        return;
    }

    int taken = 0;
    //Ensuring the new email isn't already taken
    for (int i = 0; i < MAX_USERS; i++) {
        if (UserHashTable.table[i] != NULL && strcmp(UserHashTable.table[i]->email, new_email) == 0) {
            taken = 1; //Set email to taken
            printf("Email is already taken.\n");
            return;
        }
    }
    //Find and update the users email if unique
    if (!taken){
        strncpy(user->email,new_email,MAX_EMAIL); //Make sure  email doesnt exceed max value
    }
}

void change_user_name(User* user, char* new_name) {
    //Check if user is NULL
    if ((user == NULL) || (new_name == NULL)){
        printf("Invalid user or name, cannot change name.\n");
        return;
    }

    //Ensure name isn't too long
    if (strlen(new_name) > MAX_NAME){
        printf("Name is too long.\n");
        return;
    }

    int taken = 0;
    //Compare to all users already in the hash table
    for (int i = 0; i < MAX_USERS; i++) {
        if (UserHashTable.table[i] != NULL && strcmp(UserHashTable.table[i]->name, new_name) == 0) {
            taken = 1; //Set name to taken
            printf("Name is already taken.\n");
            break;
        }
    }
    //If the name is unique, update the users name
    if (!taken){
        strncpy(user->name,new_name,MAX_NAME); //Make sure name doesnt exceed max value
    }
}

Message* create_message(User* sender, User* receiver, const char* content) {
    //Check for NULL in sender, receiver, content
    if ((sender == NULL) || (receiver == NULL) || (content == NULL)){
        printf("Sender, receiver, or content is NULL.\n");
        return NULL;
    }

    //Determine if users are friends
    if (sender_receiver_friends(sender, receiver) == 0) {
        printf("Users are not friends, so you cannot send a message\n");
        return NULL;
    }

    //Create a message
    Message* message = (Message*)malloc(sizeof(Message));
    if (message == NULL){
        printf("New message memory allocation failed.\n");
        return NULL;
    }
    //Create a unique message ID
    message->messageID = rand() % MAX_ID;
    //Identify sender and receiver
    message->sender = sender;
    message->receiver = receiver;
    message->next = NULL; //Initialize next point to NULL
    //Copying content into message array
    strncpy(message->content, content, MAX_MESSAGE_CHARS);
    //Create a chat and add to each users chat list if one doesn't exist already
    Chat* chat = getChat(sender, receiver); //Helper function
    if (chat == NULL){
       chat = createChat(sender, receiver); //Helper function
        if (chat == NULL){
            printf("New chat allocation failed.");
            return NULL;
        }
    }
    //Add message to Chat struct
    addMessageToChat(message, chat);

    return message;
}

void delete_friend(User* userA, User* userB){
    //If one of the users is NULL, return
    if ((userA == NULL) || (userB == NULL)){
        printf("Invalid users, cannot delete friend.\n");
        return;
    }
    User* user1 = userA;
    User* user2 = userB;

    //Find user2 in user1's friend list
    for (int i = 0; i < user1->Fcount; i++){
        //Use strcmp to compare the names
        if(user1->friends[i]->userID == user2->userID) {
            //Shift all users after the friend that wants to be deleted 1 spot the left to delete user2
            int j;
            for (j = i; j < user1->Fcount - 1; j++) {
                user1->friends[j] = user1->friends[j + 1];
            }
            user1->friends[j] = NULL; //Ensure null terminated
            //Decrease the friend count
            user1->Fcount--;

            //No more friends
            if (user1->Fcount == 0) {
                free(user1->friends);
            }
            else {
                //Shrink the size of the array
                user1->friends = realloc(user1->friends, sizeof(User*) * (user1->Fcount + 1));
                if (user1->friends == NULL) {
                    printf("Shrinking array to fill in removed friend's allocation failed.\n");
                    return;
                }
            }
        }
    }

    user1 = userB;
    user2 = userA;

    //Find user2 in user1's friend list
    for (int i = 0; i < user1->Fcount; i++){
        //Use strcmp to compare the names
        if(user1->friends[i]->userID == user2->userID) {
            //Shift all users after the friend that wants to be deleted 1 spot the left to delete user2
            int j;
            for (j = i; j < user1->Fcount - 1; j++) {
                user1->friends[j] = user1->friends[j + 1];
            }
            user1->friends[j] = NULL; //Ensure null terminated
            //Decrease the friend count
            user1->Fcount--;

            //No more friends
            if (user1->Fcount == 0) {
                free(user1->friends);
            }
            else {
                //Shrink the size of the array
                user1->friends = realloc(user1->friends, sizeof(User*) * (user1->Fcount + 1));
                if (user1->friends == NULL) {
                    printf("Shrinking array to fill in removed friend's allocation failed.\n");
                    return;
                }
            }
        }
    }
}

void delete_user(User* user) {
    //If the users is NULL, return
    if (user == NULL){
        printf("Invalid user, cannot delete the user.\n");
        return;
    }

    //Pass in copy of friends array
    User** friendsCopy = getFriends(user);
    //Delete this user from all friend lists
    int i = 0;
    while (friendsCopy[i] != NULL) {
        delete_friend(friendsCopy[i], user);
        i++;
    }
    
    //Find user in the hash table
    for (int i = 0; i < MAX_USERS; i++) {
        //Make sure index isn't NULL and find the user to delete
        if(UserHashTable.table[i] != NULL && UserHashTable.table[i]->userID == user->userID){
            //Free memory before setting that index to NULL
            free(UserHashTable.table[i]);
            UserHashTable.table[i] = NULL;
            //decrease user count
            globalUserCount--;
            return;
        }
    }
    //User was never found in the hash table
    printf("User not found.\n");
}

void display_chat(User* user1, User* user2){
    //Get the chats between user1 and user2
    Chat* chat = getChat(user1, user2);

    //Check if chats exist
    if (chat == NULL){
        printf("No chats exist.\n");
        return;
    }

    Message* messageToPrint = chat->head;
    for (int i = 0; i < chat->messageCount; i++){
            print_message(messageToPrint);
            messageToPrint = messageToPrint->next;
            //Printing coma separator unless it is the last one
            if (i < (chat->messageCount - 1)){
                printf(",");
            }
    }
    printf("\n"); //Newline at the end of the last message in the chat
}
//Helper function to return the chat between 2 users
Chat* getChat(User* userA, User* userB){
    //Check if the chat between the 2 users exist
    for (int i = 0; i < userA->chatCount; i++) {
        //Iterate through user1's chats and find a chat with user2 in it
        //UserA could be either in User 1 or User 2 in the chat structure
        if ((userA->userChats[i]->user1 == userB) || (userA->userChats[i]->user2 == userB)){
            return userA->userChats[i];
        }
    }
    return NULL; //No chat found
}

Post** getFeedPosts(User* user, int* totPostsCount){
    //Determine how many posts between user and their friends
    int friendPosts = 0;
    for (int i = 0; i < user->Fcount; i++){
        friendPosts += user->friends[i]->postCount;
    }
    *totPostsCount = user->postCount + friendPosts; //Store the total amount of posts

    //Allocate enough memory for an array for all users posts + their friends posts
    Post** totPosts = malloc(sizeof(Post*) * (*totPostsCount));
    if (totPosts == NULL){
        printf("User + friends posts list allocation failed.\n");
        return NULL;
    }

    //Add user's post to array by traversing linked list
    Post* currentPost = user->postsHead; //create pointer to start at the head of the list
    int count = 0; //Keep track of index in while loop
    while (currentPost != NULL){
        totPosts[count++] = currentPost; //Place elements in the list
        currentPost = currentPost->next; //Set current pointer to the next pointer in list
    }

    //Add friend posts to list
    for (int i = 0; i < user->Fcount; i++){
       //Determine the current friend
        Post* friendCurrent = user->friends[i]->postsHead; //create pointer to start at the head of the friend list
        while (friendCurrent != NULL){
            totPosts[count++] = friendCurrent; //Place elements in the list
            friendCurrent = friendCurrent->next; //Set current pointer to the next pointer in list
        }
    }

    return totPosts;
}

User** getFriends(User* user) {
    //Initialize copy
    User **friendsCopy;

    //Add memory for amount of friends
    friendsCopy = malloc(sizeof(User *) * (user->Fcount + 1)); //Incorporate 1 space for null
    if (friendsCopy == NULL) {
        printf("New copy of friend list allocation Failed.\n");
        return NULL;
    }

    //To add to the list of friends
    int i;
    for (i = 0; i < user->Fcount; i++) {
        friendsCopy[i] = user->friends[i];
    }
    friendsCopy[i] = NULL;

    return friendsCopy;
}

//Create hash key function
//Will return a unique index for each user
int hashKey(int userID){
    return userID % MAX_USERS;
}

User** mutual_friends(User* user1, User* user2) {
    //Pointer to mutual friend list
    User** mutuals;
    int mutualCount = 0;

    //print_user_list(user1->friends);
    //print_user_list(user2->friends);
    for (int i = 0; i < user1->Fcount; i++) { //Loop 1 iterates through user 1s friends
        for (int j = 0; j < user2->Fcount; j++) { //Loop 2 compares each friend of user 1 to user 2s friends
            if (strcmp(user1->friends[i]->name, user2->friends[j]->name) == 0) {
                //Found a match, add to mutual friend list
                if (mutualCount == 0) {
                    mutuals = malloc(sizeof(User *) * (mutualCount + 2));
                    if (mutuals == NULL) {
                        printf("New mutual friend allocation Failed.\n");
                        return NULL;
                    }
                } else {
                    //Reallocate memory
                    //Dynamically add memory based on how many friends the user has
                    mutuals = realloc(mutuals, sizeof(User *) * (mutualCount + 2));
                    if (mutuals == NULL) {
                        printf("New mutual friend reallocation Failed.\n");
                        return NULL;
                    }
                }
                mutuals[mutualCount] = user1->friends[i];
                mutualCount++;
                break;
            }
        }
    }
    mutuals[mutualCount] = NULL;
    //No mutual friends were found between user1 and user2
    if (mutualCount == 0){
        printf("No mutual friends were found between %s and %s.\n", user1->name, user2->name);
        return NULL;
    }
    return mutuals;
}

Post* new_post(User* user, const char* content){

    //Create a post
    Post* post = (Post*)malloc(sizeof(Post));
    if (post == NULL){
        printf("New post memory allocation failed.\n");
        return NULL;
    }
    //Create a unique Post ID
    post->postID = rand() % MAX_ID;

    //Initialize user
    post->user = user;


    //Copying content into message array
    strncpy(post->content, content, MAX_POST_CHARS);

    //Initiate like count to 0
    post->likeCount = 0;

    //Initialize User likes on a post to null
    post->userlikes = NULL;

    //Determine if this is the first message in the chat
    if (user->postsHead == NULL){
        user->postsHead = post;
        user->postsTail = post;
    }
    else{
        //If not first message, add to end of linked list
        user->postsTail->next = post; //Current tail's next is now the added message
        user->postsTail = post; //Set tail to the new message
    }
    //For both cases, the next entity in list is NULL
    post->next = NULL;
    user->postCount++; //Increment chat count to keep track of total number of chats

    //Set the global variable to the next number in line
    post->recencyNum = globalPostNum++;

    return post;
}

void print_friends(User* user) {
    //Make sure there are friends to print
    if (user->Fcount <= 0) {
        printf("No friends in friend list.\n");
        return;
    }
    print_user_list(user->friends);
}

void print_message(Message* message){
    printf("[%s]:%s", message->sender->name, message->content);
}

void print_mutual_friends(User** friends) {
    //Call the generic print users function, and pass it list of friends given
    print_user_list(friends);
}

void print_user_list(User** users){
    int userCount = 0;

    //Copy all valid entries into the array
    int i = 0;
    while (users[i] != NULL) {
        if (users[i] != NULL) {
            i++;
            userCount++;
        }
    }

    User **tempFriends = malloc(sizeof(User*) * userCount);
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
            if (strcmp(tempFriends[j]->name, tempFriends[j + 1]->name) > 0) {
                temp = tempFriends[j];
                tempFriends[j] = tempFriends[j + 1];
                tempFriends[j + 1] = temp;
            }
        }
    }
    //Print out the ascending names list
    for (int i = 0; i < userCount; i++) {
        if (i < userCount - 1) { //Print all names but the last with a coma
            printf("%s,", tempFriends[i]->name);
        } else {
            printf("%s", tempFriends[i]->name); //Print last name without a coma
        }
    }
    printf("\n");
    free(tempFriends);
}

void print_users() {
    //Find how many users are in the hash table
    int userCount = 0;
    for (int i = 0; i < MAX_USERS; i++) {
        if (UserHashTable.table[i] != NULL) {
            userCount++;
        }
    }
    //Create an array for valid users in the hash table
    User **tempUsers = malloc(sizeof(User*) * userCount);
    int index = 0;

    //Copy all valid entries into the array
    for (int i = 0; i < MAX_USERS; i++) {
        if (UserHashTable.table[i] != NULL) {
            tempUsers[index++] = UserHashTable.table[i];
        }
    }

    //Bubble sort users names within the hash table
    User *temp = NULL;
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            //Checks if element at i is greater than the next element. If so, swap
            if (strcmp(tempUsers[j]->name, tempUsers[j + 1]->name) > 0) {
                temp = tempUsers[j];
                tempUsers[j] = tempUsers[j + 1];
                tempUsers[j + 1] = temp;
            }
        }
    }
    //Print out the ascending names list
    for (int i = 0; i < userCount; i++) {
        if (i < userCount - 1) { //Print all names but the last with a coma
            printf("%s,", tempUsers[i]->name);
        } else {
            printf("%s", tempUsers[i]->name); //Print last name without a coma
        }
    }
    printf("\n");
    free(tempUsers);
}

User* search_user_by_name(const char* name){
    //Compare the name of user that want to be searched to each non-empty index of the hash table
    for (int i = 0; i < MAX_USERS; i++){
        if (UserHashTable.table[i] != NULL && strcmp(UserHashTable.table[i]->name, name) == 0){
            return UserHashTable.table[i]; //Return the pointer when found
        }
    }
    //If no match found, return NULL
    printf("User's name not found.\n");
    return NULL;
}

User* search_user_by_email(const char* email) {
    //Compare the email of user that want to be searched to each non-empty index of the hash table
    for (int i = 0; i < MAX_USERS; i++) {
        if (UserHashTable.table[i] != NULL && strcmp(UserHashTable.table[i]->email, email) == 0) {
            User* matchedUser = UserHashTable.table[i];
            return matchedUser; //Return the pointer when found
        }
    }
    //If no match found, return NULL
    printf("User's email not found.\n");
    return NULL;
}

//Helper function to determine if sender and receiver are friends
int sender_receiver_friends(User* sender, User* receiver) {
    for (int i = 0; i < sender->Fcount; i++) {
        if (sender->friends[i]->userID == receiver->userID) { //If they are friends, continue with program
            return 1;
        }
    }
    return 0; //Not friends
}

void sortPosts(Post** posts, int totPosts, User* user){
    //Bubble sort for likes and recency
    Post* temp = NULL; //use to swap entities later in bubble sort

    for (int i = 0; i < totPosts - 1; i++){
        for (int j = 0; j < totPosts - i - 1; j++){
            //First determine which post has more likes
            if (posts[j]->likeCount < posts[j + 1]->likeCount){
                //Rearrange likes in decreasing order
                temp = posts[j];
                posts[j] = posts[j + 1];
                posts[j + 1] = temp;
            }
            //If the likes are the same, we need to compare the position using comparePostPosition function
            else if (posts[j]->likeCount == posts[j + 1]->likeCount){
                int compare = comparePostPosition(posts[j], posts[j + 1]);
                if (compare < 0){ //If posts[j + 1] is newer than posts[j], swap
                    temp = posts[j];
                    posts[j] = posts[j + 1];
                    posts[j + 1] = temp;
                }
            }
        }
    }
}

Hash UserHashTable;
void testingParser(int arg1, char *arg2){
    printf("The parser was called with arguments: %d and %s\n", arg1, arg2);
}