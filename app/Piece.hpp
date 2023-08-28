#ifndef PIECE_HPP
#define PIECE_HPP

#pragma once
#include <string>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <ostream>
#include <QIcon>
#include <QMessageBox>

#include "Plateau.hpp"

enum class Couleur {
	BLANC,
	NOIR
};
enum class PieceType {
	ROI,
	TOUR,
	REINE
};

struct Position
{
	int x, y;
	Position(int i, int j) : x(i), y(j)
	{};
	friend bool operator==(const Position& lhs, const Position& rhs)
	{
		return (lhs.x == rhs.x) && (lhs.y == rhs.y);
	}

	friend bool operator!=(const Position& lhs, const Position& rhs)
	{
		return !(lhs == rhs);
	}
};

class Piece {
public:
	//Piece() = default;
	Piece(PieceType type, Couleur couleur, int x, int y) : typePiece_(type), couleur_(couleur), position_(Position(x, y)) {
	};
	PieceType getType() const
	{
		return typePiece_;
	}
	Position trouverPositon() const
	{
		return position_;
	}
	void setPosition(Position pos)
	{
		position_ = pos;
	}
	Couleur getCouleur() const
	{
		return couleur_;
	}
	Couleur getCouleurAdverse() const {
		return (couleur_ == Couleur::BLANC) ? Couleur::NOIR : Couleur::BLANC;
	}

	std::vector<Position> getValidMoves(modele::Plateau& plateau) {
		std::vector<Position> validMoves;
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				Position position = { i,j };
				if (isMovementLegal(plateau, position))
					validMoves.push_back(position);
			}
		}
		return validMoves;
	}

	virtual bool isMovementLegal(modele::Plateau& plateau, Position nextPosition) const = 0;
	virtual bool cheminDegage(modele::Plateau& plateau, Position nextPosition) const = 0;
	virtual std::string trouverNom() = 0;
	virtual ~Piece() = default;

	QIcon icon;

protected:
	Position position_;
	std::string name_;
	Couleur couleur_;
	PieceType typePiece_;
};

#endif// PIECE_HPP
