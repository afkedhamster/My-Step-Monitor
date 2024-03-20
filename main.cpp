#include <wiringPi.h>
#include "Self_defined_classes.h"
#include <iostream>

Screen::Screen() {
	// Initialization
	std::cout << "Screen initialized" << std::endl;
}

void Screen::displayText(const std::string& text) {
	// Display the text
	std::cout << "Displaying text: " << text << std::endl;
}

void Screen::bmp_read(int address) {
	// read BMP file
	readbmp();//伪函数
}

void Screen::display_bmp(int bmp) {
	displaybmp();//伪函数
}

PostureMonitor::PostureMonitor(Screen& screen) : screen(screen) {}

void PostureMonitor::handlePostureChange(Buzzer& buzzer) {
	bool postureChanged = true;
	if (postureChanged) {
		screen.displayText("Posture change");
		buzzer.alarm();
	}
}

int main(void)
{
	class Screen led();
	class Buzzer Buz();
	class PostureMonitor Pos_change_sender();
	class PostureChange Pos_change_detector();
}