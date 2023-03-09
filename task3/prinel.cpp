#include <bits/stdc++.h>
using namespace std;

class Task3 {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, op;
    vector<int> weights;
    vector<int> points;
    vector<int> targets;

    /**
     * Function reading and processing the provided input
    **/
    void read_input() {
        ifstream fin("./prinel.in");
        fin >> n >> op;

        int x, max = 0;

        // read target array
        for (int i = 0; i < n; ++i) {
            fin >> x;

            // get maximum number in array
            if (x > max) {
                max = x;
            }

            targets.push_back(x);
        }

        // maximum number of operations up to 1000 is 24
        // for op = 24 * 1000, then sum of points for targets is calculated
        if (op < 24000) {
            // calculate number of operations for every value up to max
            weights.resize(max + 1);
            get_min_op(max, weights);
        }

        // read points array
        for (int i = 0; i < n; ++i) {
            fin >> x;
            points.push_back(x);
        }

        fin.close();
    }

    /**
     * Function using Dynamic programming in order to calculate
     * number of operations for every number up to a given one
     * @param n maximum number in target array
     * @param dp array of operations for each number from 1 to n
    **/
    void get_min_op(int n, vector<int> &dp) {
        // Initilal state
        dp[1] = 0;
        int pow = 1;

        // Iterate for the remaining numbers
        for (int i = 2; i <= n; i++) {
            // check if number is current power of 2
            if (i == pow * 2) {
                // result basen on previous power of 2's number of operations
                dp[i] = dp[i / 2] + 1;
                // calculate next power of 2
                pow *= 2;
                continue;
            }

            dp[i] = INT_MAX;

            // number not power of 2
            for (int j = pow; j < i; j++) {
                // check if difference divisor
                if (i % (i - j) == 0) {
                    // get minimum number of operations
                    // compare previous element's operations with current one's
                    if (dp[j] + 1 < dp[i]) {
                        dp[i] = dp[j] + 1;
                    }
                }
            }
        }
    }

    /**
     * Function using Dynamic programming in order to get maximum points
     * using an alternate Backpack algorithm (0-1 Knapsack)
     * @param n array lengths
     * @param op target number of operations
     * @param t target array
     * @param p point array
     * @return maximum number of eared points
    **/
    long long int get_max_points(int n, int op, vector<int> &t,
                                vector<int> &p) {
        // maximum number of operations up to 1000 is 24
        if (op >= 24000) {
            // sum of target points will be calculated
            int sum = 0;
            for (int i = 0; i < n; ++i) {
                sum += p[i];
            }

            return sum;
        }

        vector<vector<long long int>> dp(n + 1,
                                            vector<long long int>(op + 1));

        // set first column as 0
        for (int i = 0; i <= op; ++i) {
            dp[0][i] = 0;
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= op; ++j) {
                // don't use object i
                // use solution from previous line/step
                dp[i][j] = dp[i - 1][j];

                // use object i
                // reserve maximum weights[t[i - 1]] units
                if (j - weights[t[i - 1]] >= 0) {
                    long long int sol_aux =
                                    dp[i - 1][j - weights[t[i - 1]]] + p[i - 1];

                    // get maximum value
                    if (sol_aux > dp[i][j]) {
                        dp[i][j] = sol_aux;
                    }
                }
            }
        }

        // total points
        return dp[n][op];
    }

    /**
     * Function returning the maximum value of points
     * @param n array lengths
     * @param op target number of operations
     * @param targets target array
     * @param points points array
     * @return maximum number of eared points
    **/
    long long int get_value(int n, int op, vector<int> targets,
                            vector<int> points) {
        return get_max_points(n, op, targets, points);
    }

    long long int get_result() { return get_value(n, op, targets, points); }

    /**
     * Function displaying the calculated maximum number of points
     * @param result maximum number of points
    **/
    void print_output(long long int result) {
        ofstream fout("./prinel.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task3();
    if (!task) {
        return -1;
    }

    task->solve();
    delete task;
    return 0;
}
