/**
* Name: Jose de Jesus Rodriguez Rivas
* Lab: lab1_2
* Date: 02/06/19
**/
#include "processor.h"

MESSAGE messageCache[CACHE_SIZE];
int numMessages = 0;
int msgTypeCount[4];
int messageBatches = 0;
int messagesProcessed = 0;

void addMessageToCache(char *inputLine) {
    // TODO See the description of the Task 10 done
    if(numMessages == CACHE_SIZE) { // we have reached mach cache size
        messageDispatcher(); // Process messages
        numMessages = 0; // Reset cache, messages will be written over
    }
    int type = 0;
    sscanf(inputLine, "%d", &type); // determine the type of message
    MESSAGE *message = &messageCache[numMessages]; // Create a reference to the current message
    switch (type) {
        case MSG_TYPE_1:
            messageCache[numMessages].content.string = malloc(strlen(inputLine)); // Make space for the string
            sscanf(inputLine, "%d %s", &message->type, message->content.string); // Read data into string
            break;
        case MSG_TYPE_2:
            // Read type and int into message
            sscanf(inputLine, "%d %d %d %d %d %d",
                   &message->type,
                   &message->content.integers[0],
                   &message->content.integers[1],
                   &message->content.integers[2],
                   &message->content.integers[3],
                   &message->content.integers[4]);
            break;
        case MSG_TYPE_3:
            // Read type and doubles into message
            sscanf(inputLine, "%d %lf %lf %lf %lf",
                   &message->type,
                   &message->content.doubles[0],
                   &message->content.doubles[1],
                   &message->content.doubles[2],
                   &message->content.doubles[3]);
            break;
        case MSG_TYPE_4:
            // Read strings into message
            sscanf(inputLine, "%d %s %s %s %s %s",
                   &message->type,
                   message->content.words[0],
                   message->content.words[1],
                   message->content.words[2],
                   message->content.words[3],
                   message->content.words[4]);
            break;
    }
    msgTypeCount[type - 1]++;
    numMessages++;
}

void messageDispatcher(void) {
    // TODO See the description of the Task 10
    messageBatches++;
    for (int i = 0; i < numMessages; i++) {
        processMessage(&messageCache[i]);
    }
}

void processMessage(MESSAGE *message) {
    // TODO See the description of the Task 10
    printf("TYPE %d: ", message->type);
    messagesProcessed++;
    switch (message->type) {
        case MSG_TYPE_1:
            // Print the string
            printf("%s", message->content.string);
            // Free the string
            free(message->content.string);
            break;
        case MSG_TYPE_2:
            // Print each int
            printf("%d,%d,%d,%d,%d",
                   message->content.integers[0],
                   message->content.integers[1],
                   message->content.integers[2],
                   message->content.integers[3],
                   message->content.integers[4]
            );
            break;
        case MSG_TYPE_3:
            // Print each string
            printf("%lf/%lf/%lf/%lf",
                   message->content.doubles[0],
                   message->content.doubles[1],
                   message->content.doubles[2],
                   message->content.doubles[3]
            );
            break;
        case MSG_TYPE_4:
            printf("%s %s %s %s %s",
                   message->content.words[0],
                   message->content.words[1],
                   message->content.words[2],
                   message->content.words[3],
                   message->content.words[4]
            );
            break;
    }
    printf("\n");
}

void printStatistics(void) {
    // TODO See the description of the Task 10
    printf("Number of message batches: %d\n", messageBatches);
    puts("Messages processed:");
    printf("Total: %d\n", messagesProcessed);
    for(int i = 0; i < 4; i++) {
        printf("Type %d: %d\n", (i + 1), msgTypeCount[i]);
    }
}
