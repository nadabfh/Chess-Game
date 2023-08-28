#pragma once
#include "Piece.hpp"
#include "Roi.hpp"
#include "Reine.hpp"
#include "Tour.hpp"
#include <QMenuBar>
#include <QMenu>
#include <QAction>

namespace controleur
{
	class Game
	{
	public:
		Game();
		Game(std::string startingPosition);
		std::shared_ptr<Piece> trouverPiece(Position position);
		Couleur getCouleurAdverse(Couleur couleur) {
			if (couleur == Couleur::BLANC)
				return Couleur::NOIR;
			return Couleur::BLANC;
		}
		std::shared_ptr<Piece> getSelectedPiece() const {
			return selectedPiece;
		}
		void capturerPiece(std::shared_ptr<Piece>& piece);
		void bougerPiece(std::shared_ptr<Piece>& piece, Position nextPosition);
		bool verificationEchec(Couleur couleur);
		bool handlePressedButton(Position position);
		std::shared_ptr<Piece>getPieceFormPlateau(int x, int y) { return plateau_(x, y); }
		std::vector<Position> validMoves;
		void updateValidMoves();
		void updateTurn();

	private:
		bool isSquarePopulated(Position positon);
		modele::Plateau plateau_;
		std::shared_ptr<Piece> selectedPiece = nullptr;
		Couleur tourDeJeu = Couleur::BLANC;
		bool checkmate = false;
		std::vector<std::shared_ptr<Piece>> pieces_;
		std::vector<std::shared_ptr<Piece>> piecesCapturees_;
		std::string startingPosition;
		void placeStandardPosition();
		void placeAlternatePosition();
		void verifyCheckmate() {}
	};
}