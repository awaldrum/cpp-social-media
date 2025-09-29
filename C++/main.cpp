#include "User.h"
#include <iostream>

int main() {
    std::cout << "\n=== Creating users ===\n";
    User* user1 = new User("Alice", "alice@example.com");
    User* user2 = new User("Bob", "bob@example.com");
    User* user3 = new User("Charlie", "charlie@example.com");
    User* user4 = new User("David", "david@example.com");
    User* user5 = new User("Eve", "eve@example.com");

    std::cout << "\n=== Making friend connections ===\n";
    User::makeFriends(user1, user2);  // Alice - Bob
    User::makeFriends(user1, user3);  // Alice - Charlie
    User::makeFriends(user2, user4);  // Bob - David
    User::makeFriends(user3, user4);  // Charlie - David
    User::makeFriends(user4, user5);  // David - Eve

    std::cout << "\n=== Testing printFriends ===\n";
    std::cout << "Alice's friends: ";
    user1->printFriends();
    std::cout << "Bob's friends: ";
    user2->printFriends();
    std::cout << "David's friends: ";
    user4->printFriends();

    std::cout << "\n=== Testing mutual_friends ===\n";
    std::cout << "Mutual friends between Bob and Charlie: ";
    User** mutuals1 = user2->mutual_friends(user3);
    user2->print_mutual_friends(mutuals1);

    std::cout << "Mutual friends between Alice and David: ";
    User** mutuals2 = user1->mutual_friends(user4);
    user1->print_mutual_friends(mutuals2);

    std::cout << "\n=== Testing user information changes ===\n";
    std::cout << "Changing Bob's name and email...\n";
    user2->change_user_name("Robert");
    user2->change_user_email("robert@example.com");
    
    std::cout << "\nBob's updated information:\n";
    std::cout << "Name: " << user2->getName() << "\n";
    std::cout << "Email: " << user2->getEmail() << "\n";

    std::cout << "\n=== Testing posts and likes ===\n";
    Post* post1 = user1->new_post("Hello, this is my first post!");
    Post* post2 = user2->new_post("Hi everyone, Bob here!");
    Post* post3 = user4->new_post("David's thoughts on the weather...");
    Post* post4 = user5->new_post("Eve's secret post!");
    
    post1->addLike(user2);  // Bob likes Alice's post
    post1->addLike(user4);  // David likes Alice's post
    post2->addLike(user1);  // Alice likes Bob's post
    
    std::cout << "\n=== Displaying Alice's feed ===\n";
    std::cout << "(Should see posts from Bob but not Eve)\n";
    user1->display_feed();
    
    std::cout << "\n=== Displaying Eve's feed ===\n";
    std::cout << "(Should see posts from David but not Alice)\n";
    user5->display_feed();
    
    std::cout << "\n=== Testing user search ===\n";
    std::cout << "Searching for user 'Robert' by name...\n";
    User* foundUser1 = User::search_user_by_name("Robert");
    if (foundUser1) {
        std::cout << "Found user: " << foundUser1->getName() << " (" << foundUser1->getEmail() << ")\n";
    } else {
        std::cout << "User not found by name!\n";
    }

    std::cout << "\nSearching for user by email 'eve@example.com'...\n";
    User* foundUser2 = User::search_user_by_email("eve@example.com");
    if (foundUser2) {
        std::cout << "Found user: " << foundUser2->getName() << " (" << foundUser2->getEmail() << ")\n";
    } else {
        std::cout << "User not found by email!\n";
    }

    std::cout << "\nTrying to search for a non-existent user...\n";
    User* notFound = User::search_user_by_name("Frank");
    if (notFound) {
        std::cout << "Unexpectedly found a user!\n";
    } else {
        std::cout << "Correctly reported that user doesn't exist\n";
    }

    std::cout << "\n=== Testing chat system ===\n";
    // Test messaging between friends
    std::cout << "Testing chat between Alice and Robert (friends):\n";
    user1->sendMessage(user2, "Hi Robert! How are you?");
    user2->sendMessage(user1, "Hey Alice! I'm good, thanks!");
    user1->sendMessage(user2, "Glad to hear that!");
    
    // Display the chat from both sides
    std::cout << "\nViewing chat from Alice's side:\n";
    user1->displayChat(user2);
    std::cout << "\nViewing chat from Robert's side:\n";
    user2->displayChat(user1);
    
    // Test messaging between non-friends
    std::cout << "\nTesting chat between Alice and Eve (not friends):\n";
    user1->sendMessage(user5, "Hi Eve!");  // Should fail
    
    std::cout << "\n=== Testing delete_user ===\n";
    std::cout << "Deleting Charlie...\n";
    user3->delete_user();
    
    std::cout << "Alice's friends after Charlie's deletion: ";
    user1->printFriends();
    std::cout << "David's friends after Charlie's deletion: ";
    user4->printFriends();
}

