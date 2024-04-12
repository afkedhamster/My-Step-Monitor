#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


// Message Queue
int getOrCreateMessageQueue(const char* filepath, int proj_id) 
{
    // Key
    key_t key = ftok(filepath, proj_id);
    if (key == -1) 
    {
        return -1; // Error
    }
    // Create Queue
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) 
    {
        return -1; // Error
    }

    return msgid;
}
