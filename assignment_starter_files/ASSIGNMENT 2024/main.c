#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "Debug.h"

#define MAX_LINE_LENGTH 1024
#define MAX_ARGUMENTS 10

// Function to call the appropriate function based on the function name
void callFunction(char *funcName, char **args, int argCount) {

    if (strcmp(funcName, "testingParser") == 0) {
        if (argCount >= 2) {
            testingParser(atoi(args[0]), args[1]);
        } else {
            printf("Invalid arguments for function: %s\n", funcName);
        }
    }

        // UNCOMMENT ME AFTER YOU HAVE WRITTEN MY FUNCTION
    else if (strcmp(funcName, "create_user") == 0) {
        if (argCount >= 2) {
            create_user(args[0], args[1]);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "print_users") == 0) {
        if (argCount >= 0) {
            print_users();
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "search_user_by_name") == 0) {
        if (argCount >= 1) {
            search_user_by_name(args[0]);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "search_user_by_email") == 0) {
        if (argCount >= 1) {
            search_user_by_email(args[0]);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "delete_user") == 0) {
        if (argCount >= 1) {
            delete_user(search_user_by_name(args[0]));
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "change_user_name") == 0) {
        if (argCount >= 2) {
            change_user_name(search_user_by_name(args[0]), args[1]);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "change_user_email") == 0) {
        if (argCount >= 2) {
            change_user_email(search_user_by_name(args[0]), args[1]);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "add_friend") == 0) {
        if (argCount >= 2) {
            add_friend(search_user_by_name(args[0]), search_user_by_name(args[1]));
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "delete_friend") == 0) {
        if (argCount >= 2) {
            delete_friend(search_user_by_name(args[0]), search_user_by_name(args[1]));
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "print_mutual_friends") == 0) {
        if (argCount >= 2) {
            print_mutual_friends(mutual_friends(search_user_by_name(args[0]), search_user_by_name(args[1])));
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "print_friends") == 0) {
        if (argCount >= 1) {
            User *tempUser = search_user_by_name(args[0]);
            print_friends(tempUser);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "create_message") == 0) {
        if (argCount >= 3) {
            create_message(search_user_by_name(args[0]), search_user_by_name(args[1]), args[2]);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "display_chat") == 0) {
        if (argCount >= 2) {
            display_chat(search_user_by_name(args[0]), search_user_by_name(args[1]));
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "new_post") == 0) {
        if (argCount >= 2) {
            new_post(search_user_by_name(args[0]), args[1]);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    } else if (strcmp(funcName, "display_feed") == 0) {
        if (argCount >= 1) {
            display_feed(search_user_by_name(args[0]));
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    }

        // TESTS EDGE CASES FOR USER MANAGEMENT
    else if (strcmp(funcName, "test_users") == 0) {
        if (argCount >= 0) {
            User *tmpUser;
            //does create user handle NULL user name or email
            printf("Does Create User Handle NULL inputs? ");
            tmpUser = create_user(NULL, NULL);
            if (tmpUser == NULL) { printf("YES\n"); }

            //does create user handle parameters too long?
            printf("Does Create User Handle Name too long? ");
            tmpUser = create_user("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwx", "test@test.com");
            if (tmpUser == NULL) { printf("YES\n"); }

            printf("Does Create User Handle Email too long? ");
            tmpUser = create_user("MyName", "abcdefghijklmnopqrstuvwxyzabcdefghijklmno@test.com");
            if (tmpUser == NULL) { printf("YES\n"); }

            //does create user handle duplicate names?
            printf("Does Create User Handle Duplicate Name input? ");
            tmpUser = create_user("TestName1", "TestEmail1@test.com");
            tmpUser = create_user("TestName1", "TestEmail2@test.com");
            if (tmpUser == NULL) { printf("YES\n"); }
            printf("Does Create User Handle Duplicate Email input? ");
            tmpUser = create_user("TestName2", "TestEmail1@test.com");
            if (tmpUser == NULL) { printf("YES\n"); }

            // search a user
            printf("Does search User work? ");
            tmpUser = create_user("UserToDelete", "UserToDelete@test.com");
            tmpUser = search_user_by_name("UserToDelete");
            if (tmpUser != NULL) { printf("YES\n"); }

            printf("Does delete User work? ");
            delete_user(tmpUser);
            printf("YES\n");

            //printf("Does delete User work for NULL input? ");
            //delete_user(NULL);
            //printf("YES\n");

            printf("Does search User work if not found? ");
            tmpUser = search_user_by_name("UserToDelete");
            if (tmpUser == NULL) { printf("YES\n"); }

            //printf("Does search User work if NULL input? ");
            //tmpUser = search_user_by_name(NULL);
            //if(tmpUser == NULL) { printf("YES\n");}

            // MORE TEST FUNCTIONS
            printf("Does changing a name and email work");
            tmpUser = create_user("UserToChg2", "UserToChg2@test.com");
            tmpUser = create_user("UserToChg1", "UserToChg1@test.com");

            change_user_name(tmpUser, "UserToChg1_NewName");
            printf("YES\n");
            change_user_email(tmpUser, "UserToChg1_NewName@test.com");
            printf("YES\n");

            printf("Does changing a name and email work");
            tmpUser = create_user("UserToChg1", "UserToChg1@test.com");
            change_user_name(tmpUser, "UserToChg1_NewName");
            printf("YES\n");
            change_user_email(tmpUser, "UserToChg1_NewName@test.com");
            printf("YES\n");


            printf("Does changing a name with NULL work - not crash?");
            change_user_name(tmpUser, NULL);
            printf("YES\n");
            printf("Does changing an email with NULL work - not crash?");
            change_user_email(tmpUser, NULL);
            printf("YES\n");

            printf("Does changing a name to an existing name fail?");
            change_user_name(tmpUser, "UserToChg2");

            printf("Does changing an email to an existing email fail?");
            change_user_name(tmpUser, "UserToChg2@test.com");

        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    }
        // TESTS EDGE CASES FOR USER MANAGEMENT
    else if (strcmp(funcName, "test_max_users") == 0) {
        if (argCount >= 0) {
            User *tmpUser;
            //only run this on it's own.
            //does it max out and fail at 10,001 users
            printf("does it max out and fail at 10,001 users? ");
            char name[49] = "";
            char email[49] = "";
            char num[5];
            char newname[49];
            char newemail[49];
            for (int i = 1; i <= MAX_USERS; i++) {
                itoa(i, num, 10);
                //printf("Num: %s\n", num);
                strcpy(newname, "TestName");
                strcpy(newemail, "TestEmail");
                strcat(newname, num);
                strcat(newemail, num);
                strcat(newemail, "@test.com");
                printf("new USer name: %s, new email: %s\n", newname, newemail);
                tmpUser = create_user(newname, newemail);
            }
            strcpy(newname, "TestName");
            strcpy(newemail, "TestEmail");
            strcat(newname, "10001");
            strcat(newemail, "10001");
            strcat(newemail, "@test.com");
            tmpUser = create_user(newname, newemail);
            if (tmpUser == NULL) {
                printf("YES\n");
            } else {
                printf("NO\n");
            }


        } else {
            printf("Invalid arguments for %s\n", funcName);
        }

    }
        // TESTS EDGE CASES FOR FRIEND MANAGEMENT
    else if (strcmp(funcName, "test_friends") == 0) {
        if (argCount >= 0) {
            User *tmpUser1 = create_user("Friends_User1", "Friends_User1@test.com");
            User *tmpUser2 = create_user("Friends_User2", "Friends_User2@test.com");
            User *tmpUser3 = create_user("Friends_User3", "Friends_User3@test.com");
            User *tmpUser4 = create_user("Friends_User4", "Friends_User4@test.com");
            User *tmpUser5 = create_user("Friends_User5", "Friends_User5@test.com");


            add_friend(tmpUser1, tmpUser2);
            add_friend(tmpUser1, tmpUser3);
            add_friend(tmpUser1, tmpUser4);
            add_friend(tmpUser1, tmpUser5);

            add_friend(tmpUser2, tmpUser1);
            add_friend(tmpUser2, tmpUser3);
            add_friend(tmpUser2, tmpUser4);
            add_friend(tmpUser2, tmpUser5);

            printf("Does printing mutual friends work");
            print_mutual_friends(mutual_friends(tmpUser1, tmpUser2));
            printf("YES\n");

            printf("Does deleting friends remove them from both users friend lists?");
            delete_friend(tmpUser1, tmpUser3);
            print_friends(tmpUser3);
            print_friends(tmpUser1);

            printf("YES\n");

            printf("Does deleting a user that is a friend work?");
            delete_user(tmpUser3);
            printf("YES\n");

//            printf("Does deleting a user twice work?");
//            delete_user(tmpUser3);
//            printf("YES\n");

            printf("Does printing mutual friends work after a mutual friend is deleted?");
            print_mutual_friends(mutual_friends(tmpUser1, tmpUser2));
            printf("YES\n");

            printf("Does printing friends of a user who had a friend deleted work?");
            print_friends(tmpUser1);
            printf("YES\n");
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    }
        // TESTS EDGE CASES FOR MESSAGE MANAGEMENT
    else if (strcmp(funcName, "test_messages") == 0) {
        if (argCount >= 0) {

            Message *tmpMsg;
            User *tmpUser1 = create_user("User1", "User1@test.com");
            User *tmpUser2 = create_user("User2", "User2@test.com");
            User *tmpUser3 = create_user("User3", "User3@test.com");


            add_friend(tmpUser1, tmpUser2);
            add_friend(tmpUser1, tmpUser3);
            add_friend(tmpUser2, tmpUser1);
            add_friend(tmpUser2, tmpUser3);

            printf("Does creating a message with null user inputs fail properly? ");
            tmpMsg = create_message(NULL, NULL, "Message1");
            if (tmpMsg == NULL) {
                printf("YES\n");
            }

            printf("Does creating a message with null content fail properly? ");
            tmpMsg = create_message(tmpUser1, tmpUser2, NULL);
            if (tmpMsg == NULL) {
                printf("YES\n");
            }

            printf("Does creating a message with more than 256chars fail properly? ");
            tmpMsg = create_message(tmpUser1, tmpUser2,
                                    "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
            if (tmpMsg == NULL) { printf("YES\n"); }


            char name[49];
            char email[49];
            char num[5];
            char newname[49];
            char newemail[49];
            char newmsg[300];
            for (int i = 1; i <= 49; i = i + 2) {
                itoa(i, num, 10);
                strcpy(newmsg, "Message");
                strcat(newmsg, num);
                tmpMsg = create_message(tmpUser1, tmpUser2, newmsg);
                itoa(i + 1, num, 10);
                strcpy(newmsg, "Message");
                strcat(newmsg, num);
                tmpMsg = create_message(tmpUser2, tmpUser1, newmsg);

            }

            display_chat(tmpUser1, tmpUser2);

            printf("does the chat storage max out at 50?");
            tmpMsg = create_message(tmpUser1, tmpUser2, "Message51");
            tmpMsg = create_message(tmpUser2, tmpUser1, "Message52");
            display_chat(tmpUser1, tmpUser2);

            printf("does deleting a user in a chat work?");
            delete_user(tmpUser2);
            printf("YES\n");

            printf("can I print a chat with a deleted user?");
            display_chat(tmpUser1, tmpUser2);

            printf("can I send another chat from or to a deleted user?");
            tmpMsg = create_message(tmpUser1, tmpUser2, "Message53");
            tmpMsg = create_message(tmpUser2, tmpUser1, "Message54");
            display_chat(tmpUser1, tmpUser2);
        } else {
            printf("Invalid arguments for %s\n", funcName);
        }
    }
    else {
        printf("Unknown function: %s\n", funcName);
    }
}


int main() {
    FILE *file = fopen("C:\\ELEC 278 Labs\\ELEC 278 Assignment 1\\assignment_starter_files\\ASSIGNMENT 2024\\test_cases.csv", "r");
    if (file == NULL) {
        perror("Unable to open file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token;
        char *funcName = NULL;
        char *args[MAX_ARGUMENTS];
        int argCount = 0;

        token = strtok(line, ",\n");
        while (token != NULL) {
            if (funcName == NULL) {
                funcName = token;
            } else {
                args[argCount++] = token;
            }
            token = strtok(NULL, ",\n");
        }

        if (funcName != NULL) {
            callFunction(funcName, args, argCount);
        }
    }

    fclose(file);
    return 0;
}
