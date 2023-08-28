#pragma once
#include "Piece.hpp"

class Reine : public Piece
{
public:
	Reine(int x, int y, Couleur couleur);
	bool isMovementLegal(modele::Plateau& plateau, Position nextPosition) const override;
	std::string trouverNom() override
	{
		return name_;
	}
	bool cheminDegage(modele::Plateau& plateau, Position nextPosition) const override;
	~Reine() override = default;
private:
	std::string name_ = "Q";
};
