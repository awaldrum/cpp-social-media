#ifndef C___CHAT_H
#define C___CHAT_H

#include <string>

// Forward declarations
class User;
class Message;
#define MAX_MESSAGE_CHATS 50

class Chat {
private:
    User* user1;
    User* user2;
    Message* head;  // First message in chat
    Message* tail;  // Last message in chat
    int messageCount;

public:
    Chat(User* first, User* second);
    ~Chat();
    
    void addMessage(Message* msg);
    void displayChat() const;
    bool involvesUser(User* user) const;
    int getMessageCount() const { return messageCount; }
    
    friend class User;  // Allow User class to access private members
};

#endif // C___CHAT_H