#include  "Tour.hpp"


Tour::Tour(int x, int y, Couleur couleur) : Piece(PieceType::TOUR, couleur, x, y){
    if (couleur == Couleur::BLANC)
        icon.addFile(":/image/wRook.png", QSize(70, 70));
    else if (couleur == Couleur::NOIR)
        icon.addFile(":/image/bRook.png", QSize(70, 70));
}

bool Tour::isMovementLegal(modele::Plateau& plateau, Position nextPosition) const {
    int dx = abs(nextPosition.x - position_.x);
    int dy = abs(nextPosition.y - position_.y);

    if ((dx == 0 || dy == 0)) {
        if (cheminDegage(plateau, nextPosition) && nextPosition != trouverPositon()) {
            std::shared_ptr<Piece> targetPiece = plateau(nextPosition.x,nextPosition.y);
            if (targetPiece == nullptr || targetPiece->getCouleur() == getCouleurAdverse()) {
                return true;
            }
        }
    }
    return false;
}


bool Tour::cheminDegage(modele::Plateau& plateau, Position nextPosition) const { 
    int dx = abs(nextPosition.x - position_.x);
    int dy = abs(nextPosition.y - position_.y);

    bool horizontalMove = dy == 0;
    int direction;
    if (horizontalMove) {
        if ((nextPosition.x - position_.x) > 0) {
            direction = 1;
        }
        else {
            direction = -1;
        }
    }
    else {
        if ((nextPosition.y - position_.y) > 0) {
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
        Position intermediatePosition = Position(0,0);
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

    return true;
}
