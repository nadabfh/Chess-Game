#pragma once
class Piece;

namespace modele 
{
    class Plateau {
    public:
        Plateau() {
            std::cout << "construit plateau" << std::endl;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    plateau[i][j] = nullptr; 
                }
            }
        }
        std::shared_ptr<Piece>& operator()(int x, int y) {
            return plateau[x][y];
        }

        std::shared_ptr<Piece>& operator()(int x, int y, std::shared_ptr<Piece> piece) {
            return plateau[x][y] = piece;
        }

    private:
        std::shared_ptr<Piece> plateau[8][8];
    };
}