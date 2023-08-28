#pragma once

#include "Piece.hpp"


class Tour : public Piece
{
public:

	Tour(int x, int y, Couleur couleur);
	std::string trouverNom() override
	{
		return name_;
	}

	bool isMovementLegal(modele::Plateau& plateau, Position nextPosition) const override;
	bool cheminDegage(modele::Plateau& plateau, Position nextPosition) const override;
	~Tour() override = default;
private:
	std::string name_ = "T";
};
