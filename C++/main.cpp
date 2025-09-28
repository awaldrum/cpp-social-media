#include "User.h"



int main() {

    User* user1 = new User("Alice", "alice@example.com");
    User* user2 = new User("Bob", "bob@example.com");
    User* user3 = new User("Charlie", "charlie@example.com");


    User::makeFriends(user1, user2);
    User::makeFriends(user1, user3);

    user1->printFriends();
    user3->printFriends();
    user3->delete_user();

    user1->printFriends();
}

