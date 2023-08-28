#include "Chess.h"
#include <assert.h>

#if __has_include("gtest/gtest.h")
#include "gtest/gtest.h"
#endif
#ifdef TEST

using namespace vue;
using namespace controleur;
using namespace modele;

TEST(GameTest, GameInitializationTest) {
    Game game;
    ASSERT_EQ(game.getPieceFormPlateau(7, 3)->getType(), PieceType::ROI);
    ASSERT_EQ(game.getPieceFormPlateau(0, 3)->getType(), PieceType::ROI);
    ASSERT_EQ(game.getPieceFormPlateau(7, 4)->getType(), PieceType::REINE);
    ASSERT_EQ(game.getPieceFormPlateau(0, 4)->getType(), PieceType::REINE);
    ASSERT_EQ(game.getPieceFormPlateau(7, 0)->getType(), PieceType::TOUR);
    ASSERT_EQ(game.getPieceFormPlateau(7, 7)->getType(), PieceType::TOUR);
    ASSERT_EQ(game.getPieceFormPlateau(0, 0)->getType(), PieceType::TOUR);
    ASSERT_EQ(game.getPieceFormPlateau(0, 7)->getType(), PieceType::TOUR);
};


TEST(PieceTest, RoiTest) {
    Roi roi(0, 0, Couleur::BLANC);
    ASSERT_EQ(roi.getCouleur(), Couleur::BLANC);
    ASSERT_EQ(roi.getType(), PieceType::ROI);
}

TEST(PieceTest, ReineTest) {
    Reine reine(0, 0, Couleur::BLANC);
    ASSERT_EQ(reine.getCouleur(), Couleur::BLANC);
    ASSERT_EQ(reine.getType(), PieceType::REINE);
}

TEST(PieceTest, TourTest) {
    Tour tour(0, 0, Couleur::BLANC);
    ASSERT_EQ(tour.getCouleur(), Couleur::BLANC);
    ASSERT_EQ(tour.getType(), PieceType::TOUR);
}

TEST(PieceTest, PiecePositionTest) {
    Roi roi(0, 0, Couleur::BLANC);
    Position pos = roi.trouverPositon();
    ASSERT_EQ(pos.x, 0);
    ASSERT_EQ(pos.y, 0);

    roi.setPosition(Position(1, 1));
    pos = roi.trouverPositon();
    ASSERT_EQ(pos.x, 1);
    ASSERT_EQ(pos.y, 1);
}

TEST(PlateauTest, PlateauInitializationTest) {
    Plateau plateau;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            ASSERT_EQ(plateau(i, j), nullptr);
        }
    }
}

TEST(PlateauTest, PlateauAssignmentTest) {
    Plateau plateau;
    std::shared_ptr<Piece> roi = std::make_shared<Roi>(Roi(0, 0, Couleur::BLANC));
    plateau(0, 0, roi);
    ASSERT_EQ(plateau(0, 0), roi);
}

TEST(RoiTest, RoiMovementTest) {
    Plateau plateau;
    std::shared_ptr<Piece> roi = std::make_shared<Roi>(Roi(0, 0, Couleur::BLANC));
    plateau(0, 0, roi);

    ASSERT_TRUE(roi->isMovementLegal(plateau, Position(1, 0)));
    ASSERT_TRUE(roi->isMovementLegal(plateau, Position(1, 1)));
    ASSERT_FALSE(roi->isMovementLegal(plateau, Position(2, 0)));
    ASSERT_FALSE(roi->isMovementLegal(plateau, Position(2, 2)));
}

TEST(ReineTest, ReineMovementTest) {
    Plateau plateau;
    std::shared_ptr<Piece> reine = std::make_shared<Reine>(Reine(0, 0, Couleur::BLANC));
    plateau(0, 0, reine);

    ASSERT_TRUE(reine->isMovementLegal(plateau, Position(7, 7)));
    ASSERT_TRUE(reine->isMovementLegal(plateau, Position(0, 7)));
    ASSERT_FALSE(reine->isMovementLegal(plateau, Position(2, 5)));
    ASSERT_FALSE(reine->isMovementLegal(plateau, Position(1, 6)));
}

TEST(TourTest, TourMovementTest) {
    Plateau plateau;
    std::shared_ptr<Piece> tour = std::make_shared<Tour>(Tour(0, 0, Couleur::BLANC));
    plateau(0, 0, tour);

    ASSERT_TRUE(tour->isMovementLegal(plateau, Position(0, 7)));
    ASSERT_TRUE(tour->isMovementLegal(plateau, Position(7, 0)));
    ASSERT_FALSE(tour->isMovementLegal(plateau, Position(7, 7)));
    ASSERT_FALSE(tour->isMovementLegal(plateau, Position(1, 1)));
}

TEST(GameTest, CheckTest) {
    Plateau plateau;
    std::shared_ptr<Piece> roiBlanc = std::make_shared<Roi>(Roi(7, 3, Couleur::BLANC));
    std::shared_ptr<Piece> roiNoir = std::make_shared<Roi>(Roi(7, 7, Couleur::NOIR));
    std::shared_ptr<Piece> tour = std::make_shared<Tour>(Tour(0, 7, Couleur::BLANC));
    plateau(7, 3, roiBlanc);
    plateau(7, 7, roiNoir);
    plateau(0, 7, tour);

    Game game;
    ASSERT_FALSE(game.verificationEchec(Couleur::BLANC));
    ASSERT_TRUE(game.verificationEchec(Couleur::NOIR));
}

#endif
