#include <iostream>
#include <vector>

class GameOfLife {
    static const int I_[];
    static const int J_[];
    std::vector<std::vector<bool>> grid_;
    size_t m_;
    size_t n_;

   public:
    GameOfLife(size_t m, size_t n)
        : grid_(std::vector<std::vector<bool>>(m, std::vector<bool>(n))),
          m_(m),
          n_(n) {}

    void set(size_t i, size_t j, bool live) { grid_[i][j] = live; }

    void next() {
        std::vector<std::vector<bool>> grid(m_, std::vector<bool>(n_));
        for (size_t i = 0; i != m_; ++i) {
            for (size_t j = 0; j != n_; ++j) {
                unsigned c = 0;
                for (unsigned k = 0; k != 8; ++k) {
                    size_t ii = i + I_[k];
                    size_t jj = j + J_[k];
                    if (0 <= ii && ii < m_ && 0 <= jj && jj < n_ &&
                        grid_[ii][jj]) {
                        ++c;
                    }
                }
                if (grid_[i][j]) {
                    if (c == 2 || c == 3) {
                        grid[i][j] = true;
                    }
                } else {
                    if (c == 3) {
                        grid[i][j] = true;
                    }
                }
            }
        }
        grid_.swap(grid);
    }

    void start(size_t count) {
        for (size_t i = 0; i != count; ++i) {
            next();
        }
    }

    void simulate(size_t count) {
        for (size_t i = 0; i != count; ++i) {
            print();
            std::cout << std::endl;
            next();
        }
        print();
        std::cout << std::endl;
    }

    void print() {
        for (size_t i = 0; i != m_; ++i) {
            for (size_t j = 0; j != n_; ++j) {
                std::cout << (grid_[i][j] ? "0" : ".");
            }
            std::cout << std::endl;
        }
    }
};

const int GameOfLife::I_[]{1, 1, 0, -1, -1, -1, 0, 1};
const int GameOfLife::J_[]{0, 1, 1, 1, 0, -1, -1, -1};

int main() {
    GameOfLife gol(20, 20);
    gol.set(1, 2, true);
    gol.set(2, 3, true);
    gol.set(3, 1, true);
    gol.set(3, 2, true);
    gol.set(3, 3, true);
    gol.simulate(5);
}
