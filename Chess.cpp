#include "Chess.h"
#include <QTimer>
#include <QTime>

QString beigeBackground = "Background-color: rgb(238,238,210)";
QString GreenBackground = "Background-color: rgb(118,150,86)";
QString SelectedBackground = "Background-color: rgb(186,202,68)";


namespace vue
{
	Chess::Chess(QWidget* parent)
		: QMainWindow(parent)
	{
		ui.setupUi(this);

		QMenuBar* menuBar = new QMenuBar(this);
		setMenuBar(menuBar);

		createChecker();
		//game = new controleur::Game("Alternate");
		draw();

	}

	Chess::~Chess()
	{}

	void Chess::createChecker() {
		board = new QGridLayout();
		board->setSpacing(0);

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++) {

				buttonArr[i][j] = new Button(i, j);
				buttonArr[i][j]->setFixedSize(85, 85);
				board->addWidget(buttonArr[i][j], i, j);

				QObject::connect(buttonArr[i][j], &QPushButton::clicked, this, &Chess::bouttonAppuye);
			}
		}
		centralWidget()->setLayout(board);
	}


	void Chess::bouttonAppuye()
	{
		Button* button = qobject_cast<Button*>(QObject::sender());
		int x = button->getX();
		int y = button->getY();
		Position position{ x, y };

		if (isGameStarted) {
			bool isInvalidMove = game->handlePressedButton(position);

			if (isInvalidMove && game->getSelectedPiece() != nullptr && position != game->getSelectedPiece()->trouverPositon()) {
				QString redBackground = "Background-color: rgb(255, 0, 0)";
				button->setStyleSheet(redBackground);
				QTimer::singleShot(2000, this, [this, button] {
					draw();
					});
			}
			else {
				draw();
			}
		}
		else if (position == Position{ 4, 4 }) {
			game = new controleur::Game("Alternate");
			isGameStarted = true;
			buttonArr[4][3]->setText("");
			buttonArr[4][4]->setText("");
			draw();
		}
		else if (position == Position{ 4, 3 }) {
			game = new controleur::Game("Standard");
			isGameStarted = true;
			buttonArr[4][3]->setText("");
			buttonArr[4][4]->setText("");
			draw();
		}
	}



	void Chess::draw() {

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++) {

				if (((i + j) % 2) == 0)
					buttonArr[i][j]->setStyleSheet(GreenBackground);
				else
					buttonArr[i][j]->setStyleSheet(beigeBackground);

				if (isGameStarted && game->getPieceFormPlateau(i, j) != nullptr)
				{
					buttonArr[i][j]->setIcon(game->getPieceFormPlateau(i, j)->icon);
					buttonArr[i][j]->setIconSize(QSize(75, 75));
				}
				else buttonArr[i][j]->setIcon(QIcon());
			}
		}
		if (!isGameStarted) {
			buttonArr[4][3]->setText("Standard");
			buttonArr[4][4]->setText("Alternate");
		}
		if (isGameStarted) drawValidMove();
	}

	void Chess::drawValidMove() {
		for (Position validMove : game->validMoves) {
			buttonArr[validMove.x][validMove.y]->setStyleSheet(SelectedBackground);
		}
	}

}