#include <iostream>

using namespace std;

const long long N = 2e8;

int main(void) {
    for (long long i = 0; i < N; ++i) {
        if (i % (N / 100) == 0) {
            cout << "\r[";
            for (int j = 0; j < 25; ++j) {
                if (i <= j * (N / 25)) {
                    cout << " ";
                } else {
                    cout << "#";
                }
            }
            cout << "] ";
            cout << (i / (N / 100)) << "% completed." << flush;
        }
    }
    cout << "\r[";
    for (int i = 0; i < 25; ++i) {
        cout << "#";
    }
    cout << "] 100% completed." << endl;
}
