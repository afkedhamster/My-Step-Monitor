#include <iostream>
#include <condition_variable>
#include <mutex>
#include "Response.h"
#include "IPC.h"
#include "Judgment.h"

// Thread Mark
std::condition_variable cv_r_ready;
std::mutex mtx_r_ready;
bool r_ready = false;

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

    /*while (true) 
    {*/
        // Recevie C
        Message message_C(1);
        if (!ipc_C.receive(message_C)) 
        {
            std::cerr << "Failed to receive message from B." << std::endl;
            continue;
        }
        // Pos_Change
        float posChange = message_C.DataResult[0];
        trigger_buzz_lcd(static_cast<enum POS_CHANGE>(posChange));

        // Finish Thread
        {
            std::lock_guard<std::mutex> lock(mtx_r_ready);
            r_ready = true;
            cv_r_ready.notify_one();
        }
    //}    
}

// Wait Thread
void Response::wait_R_ready() 
{
    std::unique_lock<std::mutex> lock(mtx_r_ready);
    cv_r_ready.wait(lock, []{ return r_ready; });
    r_ready = false;
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
