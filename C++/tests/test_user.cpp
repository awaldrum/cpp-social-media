#include <cassert>
#include "User.h"

void testCreateUser() {
    User user("Alice", "alice@example.com");
    assert(user.getName() == "Alice");
    assert(user.getEmail() == "alice@example.com");
}

void testMakeFriends() {
    User user1("Alice", "alice@example.com");
    User user2("Bob", "bob@example.com");
    User::makeFriends(&user1, &user2);
    assert(user1.isFriend(&user2));
    assert(user2.isFriend(&user1));
}

void testPrintFriends() {
    User user1("Alice", "alice@example.com");
    User user2("Bob", "bob@example.com");
    User::makeFriends(&user1, &user2);
    user1.printFriends(); // Check output manually
}

void testDeleteUser() {
    User* user = new User("Charlie", "charlie@example.com");
    user->delete_user();
    assert(user->isDeleted() == true);
    delete user; // Clean up
}

int main() {
    testCreateUser();
    testMakeFriends();
    testPrintFriends();
    testDeleteUser();
    return 0;
}