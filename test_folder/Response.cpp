#include <iostream>
#include "Response.h"
#include "IPC.h"

void Response::start(Buzzer *bobj, LCD *lobj, enum POS_CHANGE *posChange)
{
    buzzer = bobj;
    lcd = lobj;
    thread = std::thread(&Response::trigger_buzz_lcd, this, std::ref(*posChange));
}

void Response::Read()
{
    IPC ipc_C("/tmp", 'C');

    while (true) 
    {
        Message message_C;
        if (!ipc_C.receive(message_C)) 
        {
            std::cerr << "Failed to receive message from B." << std::endl;
            continue;
        }
        // Pos_Change
        float posChange = value.message_C.DataResult;

        trigger_buzz_lcd(posChange);
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
                case 0: // FALL
                    buzzer->Beep(5000, 20000);
                    lcd->print("Emergency!!! Fall detected!!!");
                    break;
                case 4: // RISE
                    buzzer->Beep(3000, 1500);
                    lcd->print("Rise detected!");
                    break;
                case 5: // SIT2LAY
                    buzzer->Beep(2000, 1000);
                    lcd->print("Sit to lay detected!");
                    break;
                case 6: // STAND2SIT
                    buzzer->Beep(2000, 1000);
                    lcd->print("Stand to sit detected!");
                    break;
                case 7: // STAND2LAY
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
