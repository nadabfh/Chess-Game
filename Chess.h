#pragma once

#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QSignalMapper>
#include <QObject>
#include <Qdebug>


#include "ui_Chess.h"
#include "button.hpp"
#include "Piece.hpp"
#include "Game.hpp"

namespace vue
{
    class Chess : public QMainWindow
    {
        Q_OBJECT

    public:
        std::shared_ptr<Piece> selectedPiece = nullptr;

        Chess(QWidget* parent = nullptr);
        ~Chess();
        void draw();
        void drawValidMove();

    private slots:
        void bouttonAppuye();
    private:
        Ui::ChessClass ui;
        controleur::Game* game = nullptr;
        bool isGameStarted = false;
        QGridLayout* board;
        QPushButton* buttonArr[8][8];

        void createChecker();
    };
}