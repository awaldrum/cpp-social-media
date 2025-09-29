#include "Message.h"
#include "User.h"
#include "Chat.h"
#include <iostream>
#include <cstdlib>

Message::Message(User* from, User* to, const std::string& msg) {
    messageID = rand() % MAX_ID;
    sender = from;
    receiver = to;
    content = msg.substr(0, MAX_MESSAGE_CHARS);
    next = nullptr;
}

Message::~Message() {
    // No need to delete sender/receiver as they are managed elsewhere
}

void Message::displayMessage() const {
    std::cout << sender->getName() << " -> " << receiver->getName() << ": " << content << std::endl;
}