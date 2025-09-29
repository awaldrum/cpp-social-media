#include "Chat.h"
#include "User.h"
#include "Message.h"
#include <iostream>

Chat::Chat(User* first, User* second) {
    user1 = first;
    user2 = second;
    head = nullptr;
    tail = nullptr;
    messageCount = 0;
}

Chat::~Chat() {
    Message* current = head;
    while (current != nullptr) {
        Message* next = current->getNext();
        delete current;
        current = next;
    }
}

void Chat::addMessage(Message* msg) {
    if (messageCount >= MAX_MESSAGE_CHATS) {
        std::cout << "Chat limit reached!" << std::endl;
        return;
    }
    
    if (head == nullptr) {
        head = tail = msg;
    } else {
        tail->next = msg;
        tail = msg;
    }
    messageCount++;
}

void Chat::displayChat() const {
    std::cout << "=== Chat between " << user1->getName() 
              << " and " << user2->getName() << " ===" << std::endl;
    
    if (messageCount == 0) {
        std::cout << "No messages yet." << std::endl;
        return;
    }
    
    Message* current = head;
    while (current != nullptr) {
        current->displayMessage();
        current = current->getNext();
    }
}

bool Chat::involvesUser(User* user) const {
    return (user == user1 || user == user2);
}