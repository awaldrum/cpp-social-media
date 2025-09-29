#ifndef C___MESSAGE_H
#define C___MESSAGE_H

#include <string>

// Forward declarations
class User;
class Chat;

#define MAX_MESSAGE_CHARS 256

class Message {
private:
    int messageID;
    User* sender;
    User* receiver;
    std::string content;
    Message* next;

public:
    Message(User* from, User* to, const std::string& msg);
    ~Message();
    
    // Getters
    User* getSender() const { return sender; }
    User* getReceiver() const { return receiver; }
    std::string getContent() const { return content; }
    Message* getNext() const { return next; }
    int getMessageID() const { return messageID; }
    
    // Display
    void displayMessage() const;
    
    friend class Chat;  // Allow Chat class to access private members
};

#endif // C___MESSAGE_H