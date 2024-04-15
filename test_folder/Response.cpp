#include <iostream>
#include "Response.h"
#include "IPC.h"
#include "Judgment.h"

Response::Response(){};

void Response::start(Buzzer *bobj, LCD *lobj, enum POS_CHANGE *posChange)
{
    buzzer = bobj;
    lcd = lobj;
    thread = std::thread(&Response::trigger_buzz_lcd, this, std::ref(*posChange));
}

void Response::stop()
{
    thread.join();
}

void Response::Read()
{
    IPC ipc_C("/tmp", 'C');

    while (true) 
    {
        Message message_C(1);
        if (!ipc_C.receive(message_C)) 
        {
            std::cerr << "Failed to receive message from B." << std::endl;
            continue;
        }
        // Pos_Change
        float posChange = message_C.DataResult[0];
        trigger_buzz_lcd(static_cast<enum POS_CHANGE>(posChange));
    }    
}

void Response::trigger_buzz_lcd(enum POS_CHANGE posChange)
{
    while (true)
    {
        if (buzzer != nullptr && lcd != nullptr)
        {
            switch (posChange)
            {
                case FALL:
                    buzzer->Beep(5000, 20000);
                    lcd->print("Emergency!!! Fall detected!!!");
                    break;
                case RISE:
                    buzzer->Beep(3000, 1500);
                    lcd->print("Rise detected!");
                    break;
                case SIT2LAY:
                    buzzer->Beep(2000, 1000);
                    lcd->print("Sit to lay detected!");
                    break;
                case STAND2SIT:
                    buzzer->Beep(2000, 1000);
                    lcd->print("Stand to sit detected!");
                    break;
                case STAND2LAY:
                    buzzer->Beep(2000, 1000);
                    lcd->print("Stand to lay detected!");
                    break;
                default:
                    break;
            }
        }
        else
        {
            break;
        }
        // Delay to avoid tight loops
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
    }
}
