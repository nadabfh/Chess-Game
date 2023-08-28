#include  "Reine.hpp"

Reine::Reine(int x, int y, Couleur couleur) : Piece(PieceType::REINE, couleur, x, y) {
    if (couleur == Couleur::BLANC) 
        icon.addFile(":/image/wQueen.png", QSize(70, 70));
    else if (couleur == Couleur::NOIR)
        icon.addFile(":/image/bQueen.png", QSize(70, 70));
}


bool Reine::isMovementLegal(modele::Plateau& plateau, Position nextPosition) const
{
    int dx = abs(nextPosition.x - position_.x);
    int dy = abs(nextPosition.y - position_.y);

    if (dx == dy || dx == 0 || dy == 0) {
        if (cheminDegage(plateau, nextPosition) && nextPosition != trouverPositon()) {
            std::shared_ptr<Piece> targetPiece = plateau(nextPosition.x,nextPosition.y);
            if (!targetPiece || targetPiece->getCouleur() == getCouleurAdverse()) {
                return true;
            }
        }
    }
    return false;
}

bool Reine::cheminDegage(modele::Plateau& plateau, Position nextPosition) const 
{
    int dx = abs(nextPosition.x - position_.x);
    int dy = abs(nextPosition.y - position_.y);

    if (dx == dy) {
        int xDirection;
        if ((nextPosition.x - position_.x) > 0) {
            xDirection = 1;
        }
        else {
            xDirection = -1;
        }

        int yDirection;
        if ((nextPosition.y - position_.y) > 0) {
            yDirection = 1;
        }
        else {
            yDirection = -1;
        }

        for (int i = 1; i < dx; ++i) {
            Position intermediatePosition(position_.x + i * xDirection, position_.y + i * yDirection); 
            if (plateau(intermediatePosition.x,intermediatePosition.y) != nullptr) {
                return false;
            }
        }
    }
    else {
        bool horizontalMove = dy == 0;
        int direction;
        if (horizontalMove) {
            if (nextPosition.x - position_.x > 0) {
                direction = 1;
            }
            else {
                direction = -1;
            }
        }
        else {
            if (nextPosition.y - position_.y > 0) {
                direction = 1;
            }
            else {
                direction = -1;
            }
        }
        int range;
        if (horizontalMove) {
            range = dx;
        }
        else {
            range = dy;
        }

        for (int i = 1; i < range; ++i) {
            Position intermediatePosition = Position(0, 0);

            if (horizontalMove) {
                intermediatePosition.x = position_.x + i * direction;
                intermediatePosition.y = position_.y;
            }
            else {
                intermediatePosition.x = position_.x;
                intermediatePosition.y = position_.y + i * direction;
            }
            if (plateau(intermediatePosition.x,intermediatePosition.y) != nullptr) {
                return false;
            }
        }
    }
    return true;
}
