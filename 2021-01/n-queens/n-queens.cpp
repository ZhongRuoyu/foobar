#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class NQueens {
   public:
    static vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> solutions;
        vector<int> queens(n, -1);
        solve(solutions, queens, n);
        return solutions;
    }

   private:
    static void solve(vector<vector<string>> &solutions, vector<int> &queens, int n, int row = 0, int columns = 0, int diagonals1 = 0, int diagonals2 = 0) {
        if (row == n) {
            solutions.emplace_back(generateBoard(queens, n));
        } else {
            int availablePositions = ((1 << n) - 1) & (~(columns | diagonals1 | diagonals2));
            while (availablePositions) {
                int columnPosition = availablePositions & (-availablePositions);  // get lowest set bit
                availablePositions &= (availablePositions - 1);                   // clear lowest set bit
                queens[row] = getLowestSetBitPosition(columnPosition);            // get current position
                solve(solutions, queens, n, row + 1, columns | columnPosition, (diagonals1 | columnPosition) >> 1, (diagonals2 | columnPosition) << 1);
                queens[row] = -1;
            }
        }
    }

    static vector<string> generateBoard(vector<int> &queens, int n) {
        vector<string> board;
        for (int i = 0; i < n; ++i) {
            board.emplace_back(string(n, '.'));
            board[i][queens[i]] = 'Q';
        }
        return board;
    }

    static constexpr int getLowestSetBitPosition(int n) {
        int position = 0;
        while (n >>= 1) ++position;
        return position;
    }
};

int main(int argc, char **argv) {
    int n = 8;

    if (argc > 1) {
        if (argc > 2) {
            cerr << "Provide one argument only." << endl;
            cerr << "Usage: n-queens [n]" << endl;
            cerr << "Default: n = 8" << endl;
            return 1;
        }
        stringstream arg;
        arg = stringstream(argv[1]);
        arg >> n;
        if (arg.fail()) {
            cerr << "Error reading input." << endl;
            cerr << "Usage: n-queens [n]" << endl;
            cerr << "Default: n = 8" << endl;
            return 1;
        }
        if (n <= 0) {
            cerr << "Provide a positive integer." << endl;
            cerr << "Usage: n-queens [n]" << endl;
            cerr << "Default: n = 8" << endl;
            return 1;
        }
    }

    auto begin = chrono::high_resolution_clock::now();
    vector<vector<string>> solutions{NQueens::solveNQueens(n)};
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1e6;

    for (auto &solution : solutions) {
        for (auto &row : solution) {
            cout << row << endl;
        }
        cout << endl;
    }

    cout << n << " queens: "
         << solutions.size() << " solution(s) found in " << duration << "s." << endl;

    return 0;
}
