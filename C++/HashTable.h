#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
#include "functions.h"
#include "User.h"

// Define a maximum number of users in the hash table
#define MAX_USERS 1000

// HashTable class definition
class UserHashTable {
public:
    static User* table[MAX_USERS];  // Array to store the users in the hash table

    // Method to insert a user into the hash table
    static void insertUser(User* newUser);

    // Method to delete a user from the hash table
    static void deleteUser(User* user);

    // Method to search for a user by userID
    static User* getUser(int userID);
};

#endif //HASHTABLE_H
