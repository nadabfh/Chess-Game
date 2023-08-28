#ifndef ROI_HPP
#define ROI_HPP
#include "Piece.hpp"



class Roi : public Piece
{
public : 

	Roi(int x, int y, Couleur couleur);

	bool isMovementLegal(modele::Plateau& plateau, Position nextPosition) const override;
	std::string trouverNom() override
	{
		return name_;
	}
	bool cheminDegage(modele::Plateau& plateau, Position nextPosition) const override
	{
		return true;
	}
	~Roi() override {
		std::cout << "Roi detruit" << std::endl;
		--instances_;
	}
private:
	static int instances_;

	std::string name_ = "R";
};


#endif// ROI_HPP