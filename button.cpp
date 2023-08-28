#include "button.hpp"

Button::Button(int posX, int posY) {
	x_ = posX;
	y_ = posY;
	connect(this, &QPushButton::pressed, this, &Button::handleButtonPressed);
}

void Button::handleButtonPressed() {
	emit pressedWithPosition(x_, y_); 
}