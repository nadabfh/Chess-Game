#include <QPushButton>
#include <Qdebug>

class Button : public QPushButton {
	Q_OBJECT

public:
	Button() = default;
	~Button() override = default;

	Button(int posX, int posY);
	int getX() { return x_; }
	int getY() { return y_; }

signals:
	void pressedWithPosition(int x, int y); 

private slots:
	void handleButtonPressed();

private:

	int x_;
	int y_;
};