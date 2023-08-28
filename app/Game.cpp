#include "Game.hpp"

controleur::Game::Game() {

    if (true) placeStandardPosition();

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            plateau_(i, j, trouverPiece(Position{ i,j }));
        }
    }
}

controleur::Game::Game(std::string startingPosition) {

    if (startingPosition == "Standard") placeStandardPosition();
    else if (startingPosition == "Alternate") placeAlternatePosition();

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            plateau_(i, j, trouverPiece(Position{ i,j }));
        }
    }
}

void controleur::Game::capturerPiece(std::shared_ptr<Piece>& piece) {
    if (piece != nullptr)
    {
        piecesCapturees_.push_back(piece);

        auto it = std::find(pieces_.begin(), pieces_.end(), piece);
        pieces_.erase(it);
    }
}
bool controleur::Game::verificationEchec(Couleur couleur) {

    Position roiAdversePosition = Position(0, 0);
    std::shared_ptr<Piece> roi;
    for (const auto& piece : pieces_) { //on essaye de trouver la position du roi
        if (getCouleurAdverse(couleur) == piece->getCouleur() && piece->getType() == PieceType::ROI) {
            roiAdversePosition = piece->trouverPositon();
            roi = piece;
            break;
        }
    }
    std::vector<Position> kingValidMoves = roi->getValidMoves(plateau_);
    std::vector<Position> pieceValidMoves;
    for (const auto& piece : pieces_) { //on essaye de verifier si une des pièces adverses peut legalement se 
        //deplacer sur la position du roi position. Si c'est le cas donc il ya échec
        pieceValidMoves = piece->getValidMoves(plateau_);
        auto new_end = std::remove_if(kingValidMoves.begin(), kingValidMoves.end(), [&pieceValidMoves](const Position& x) {
            return std::find(pieceValidMoves.begin(), pieceValidMoves.end(), x) != pieceValidMoves.end();
            });

        // Erase the removed elements
        kingValidMoves.erase(new_end, kingValidMoves.end());
        if (piece->getCouleur() != couleur) {
            if (piece->isMovementLegal(plateau_, roiAdversePosition)) {
                if (kingValidMoves.empty()) checkmate = true;
                return true;
            }
        }
    }
    return false;
}
bool controleur::Game::handlePressedButton(Position clicked) {
    if (checkmate) { return false; }
    bool isInvalidMove = false;

    if (selectedPiece) {
        if (selectedPiece->isMovementLegal(plateau_, clicked)) {
            bougerPiece(selectedPiece, clicked);
            selectedPiece = nullptr;
        }
        else if (plateau_(clicked.x, clicked.y) == selectedPiece) {
            selectedPiece = nullptr;
        }
        else {
            isInvalidMove = true;
        }
    }
    else if (isSquarePopulated(clicked) == true) {
        if (plateau_(clicked.x, clicked.y)->getCouleur() == tourDeJeu) {
            selectedPiece = plateau_(clicked.x, clicked.y);
            isInvalidMove = false;
        }
        else {
            isInvalidMove = true;
        }
    }
    updateValidMoves();
    return isInvalidMove;
}


bool controleur::Game::isSquarePopulated(Position position) {

    if (plateau_(position.x, position.y) == nullptr) return false;

    else return true;
}

void controleur::Game::bougerPiece(std::shared_ptr<Piece>& piece, Position nextPosition) {
    plateau_(piece->trouverPositon().x, piece->trouverPositon().y, nullptr);
    plateau_(nextPosition.x, nextPosition.y, piece);
    piece->setPosition(nextPosition);
    updateTurn();
}

std::shared_ptr<Piece> controleur::Game::trouverPiece(Position position) {

    for (auto&& piece : pieces_)
    {
        if (piece->trouverPositon().x == position.x && piece->trouverPositon().y == position.y)
        {
            return piece;
        }
    }
    return nullptr;
}

void controleur::Game::updateValidMoves() {
    validMoves.clear();
    if (selectedPiece == nullptr) return;
    validMoves = selectedPiece->getValidMoves(plateau_);
}
void controleur::Game::updateTurn() {
    if (verificationEchec(tourDeJeu)) std::cout << "ECHEC " << int(getCouleurAdverse(tourDeJeu)) << std::endl;
    if (checkmate) { std::cout << "CHECKMATE" << std::endl; }
    tourDeJeu = getCouleurAdverse(tourDeJeu);
    std::cout << int(tourDeJeu) << std::endl;
}

void controleur::Game::placeStandardPosition() {
    try {
        pieces_.push_back(std::make_shared<Roi>(Roi(7, 3, Couleur::BLANC)));
        pieces_.push_back(std::make_shared<Roi>(Roi(0, 3, Couleur::NOIR)));
    }
    catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    //reine
    pieces_.push_back(std::make_shared<Reine>(Reine(7, 4, Couleur::BLANC)));
    pieces_.push_back(std::make_shared<Reine>(Reine(0, 4, Couleur::NOIR)));
    //tour
    pieces_.push_back(std::make_shared<Tour>(Tour(7, 0, Couleur::BLANC)));
    pieces_.push_back(std::make_shared<Tour>(Tour(7, 7, Couleur::BLANC)));
    pieces_.push_back(std::make_shared<Tour>(Tour(0, 0, Couleur::NOIR)));
    pieces_.push_back(std::make_shared<Tour>(Tour(0, 7, Couleur::NOIR)));
}


void controleur::Game::placeAlternatePosition() {
    pieces_.push_back(std::make_shared<Roi>(Roi(4, 0, Couleur::BLANC)));
    pieces_.push_back(std::make_shared<Roi>(Roi(4, 4, Couleur::NOIR)));

    //reine
    pieces_.push_back(std::make_shared<Reine>(Reine(4, 1, Couleur::BLANC)));
    pieces_.push_back(std::make_shared<Reine>(Reine(4, 5, Couleur::NOIR)));
    //tour
    pieces_.push_back(std::make_shared<Tour>(Tour(4, 2, Couleur::BLANC)));
    pieces_.push_back(std::make_shared<Tour>(Tour(4, 3, Couleur::BLANC)));
    pieces_.push_back(std::make_shared<Tour>(Tour(4, 6, Couleur::NOIR)));
    pieces_.push_back(std::make_shared<Tour>(Tour(4, 7, Couleur::NOIR)));
}