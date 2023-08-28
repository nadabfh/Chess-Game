#include  "Roi.hpp"
int Roi::instances_ = 0;


Roi::Roi(int x, int y, Couleur couleur) : Piece(PieceType::ROI, couleur, x, y) {
    instances_++;
    if (instances_ > 2) {
        throw std::runtime_error("Cannot create more than 2 Roi instances.");
    }
    if (couleur == Couleur::BLANC)
        icon.addFile(":/image/wKing.png", QSize(70, 70));
    else if (couleur == Couleur::NOIR)
        icon.addFile(":/image/bKing.png", QSize(70, 70));
    std::cout << "Roi construit" << std::endl;
}

bool Roi::isMovementLegal(modele::Plateau& plateau, Position nextPosition) const
{
    int dx = abs(nextPosition.x - position_.x);
    int dy = abs(nextPosition.y - position_.y);

    if (((dx == 1 && dy == 0) || (dx == 0 && dy == 1) || (dx == 1 && dy == 1))){
        if (nextPosition != trouverPositon())
        {
            std::shared_ptr<Piece> targetPiece = plateau(nextPosition.x, nextPosition.y);
            if (!targetPiece || targetPiece->getCouleur() == getCouleurAdverse()) {
                return true;
            }
        }
    }
    return false;
}


