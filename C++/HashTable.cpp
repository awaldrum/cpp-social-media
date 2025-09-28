#include "HashTable.h"

User* UserHashTable::table[MAX_USERS] = {nullptr};

// Insert a user into the hash table
void UserHashTable::insertUser(User* newUser) {
    int index = newUser->getUserID() % MAX_USERS; // Hash function (simple modulus)

    // Linear probing in case of collisions
    while (table[index] != nullptr) {
        // Handle collision (this example does linear probing, but you could implement other strategies)
        index = (index + 1) % MAX_USERS;
    }

    table[index] = newUser;  // Insert the user into the table
}

// Delete a user from the hash table
void UserHashTable::deleteUser(User* user) {
    int index = user->getUserID() % MAX_USERS;  // Hash function (simple modulus)

    // Linear probing to find the user
    while (table[index] != nullptr) {
        if (table[index]->getUserID() == user->getUserID()) {
            table[index] = nullptr;  // Remove the user
            return;
        }
        index = (index + 1) % MAX_USERS;  // Continue probing
    }

    std::cout << "User not found in the hash table." << std::endl;
}
