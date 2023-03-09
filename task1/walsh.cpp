#include <bits/stdc++.h>
using namespace std;

class Position {
    long long int x;
    long long int y;

 public:
    Position(long long int _x, long long int _y)
        : x(_x)
        , y(_y) {}

    long long int getX() {
        return x;
    }

    long long int getY() {
        return y;
    }
};

class Task1 {
 public:
    void solve() {
        read_input();
        print_output();
    }

 private:
    long long int n;
    int k;
    vector<Position> positions;

    /**
     * Function reading and processing the provided input
    **/
    void read_input() {
        ifstream fin("./walsh.in");
        fin >> n >> k;

        long long int x, y;

        // read positions array
        for (int i = 0; i < k; i++) {
            fin >> x >> y;
            positions.push_back(Position(x, y));
        }

        fin.close();
    }

    /**
     * Function performing a Z traversal on a matrix in order to get position value
     * @param n square size
     * @param x line position
     * @param y column position
    **/
    int Z_traversal(long long int n, long long int x, long long int y) {
        if (n == 1) {
            return 0;
        } else {
            // divide by 2
            n >>= 1;
            if (x <= n && y <= n) {
                // first square (left corner, up)
                return Z_traversal(n, x, y);
            } else if (x <= n && y > n) {
                // second square (right corner, up)
                return Z_traversal(n, x, y - n);
            } else if (x > n && y <= n) {
                // third square (left corner, down)
                return Z_traversal(n, x - n, y);
            } else {
                // fourth square (right corner, down)
                return 1 + Z_traversal(n, x - n, y - n);
            }
        }
    }

    /**
     * Function returning the calculated Walsh matrix value for given positions
    **/
    int get_value(long long int n, long long int x, long long int y) {
        // result based on how many times square 4 was accessed
        return (Z_traversal(n, x, y) % 2);
    }

    /**
     * Function displaying the value of each position in the n * n matrix
    **/
    void print_output() {
        ofstream fout("./walsh.out");

        for (Position position : positions) {
            fout << get_value(n, position.getX(), position.getY()) << '\n';
        }

        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task1();
    if (!task) {
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
