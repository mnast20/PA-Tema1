#include <bits/stdc++.h>
using namespace std;

#define MOD ((long long)1e9 + 7)

class Task {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, m;
    long long unique_letters;
    string str;
    string substring;

    /**
     * Function reading and processing the provided input
    **/
    void read_input() {
        ifstream fin("./crypto.in");

        fin >> n >> m;
        fin >> str;
        fin >> substring;

        unique_letters = get_unique_letters(substring);

        fin.close();
    }

    /**
     * Function calculating the number of unique letters in the substring
     * @param s substring
     * @return number of unique letters
    **/
    long long get_unique_letters(string &s) {
        string s2;

        // create string made up of unique letters
        for (long unsigned int i = 0; i < s.length(); i++) {
            if (s2.find(s[i]) == string::npos) {
                s2.push_back(s[i]);
            }
        }
        return s2.length();
    }

    /**
     * Function calculating the number of strings by using a dynamic
     * programming algorithm
     * @param str1
     * @param str2
     * @param unique_letters number of unique letters in second string
    **/
    long long get_nr_substrings(string &str1, string &str2,
                                            long long unique_letters) {
        int n = str.length();
        int m = str2.length();

        vector<vector<long long>> dp(n + 1,
                                            vector<long long>(m + 1));

        for (int i = 0; i <= m; ++i) {
            dp[0][i] = 0;
        }

        dp[0][0] = 1;

        long long generated_strings = 1;

        // fill the matrix
        for (int i = 1; i <= n; i++) {
            if (str[i - 1] == '?') {
                // the number f generated strings is multiplied by
                // the number of unique letters
                generated_strings = ((generated_strings % MOD) *
                                            (unique_letters % MOD)) % MOD;
            }

            dp[i][0] = generated_strings;

            for (int j = 1; j <= m; ++j) {
                if (str[i - 1] == '?') {
                    // case where '?' is replaced by second string's letters

                    // consider every possible case, meaning there is a match
                    // and (unique letters - 1) unmatches
                    dp[i][j] =
                        ((dp[i - 1][j - 1] % MOD) +
                            (((unique_letters % MOD) * (dp[i - 1][j] % MOD))
                            % MOD)) % MOD;
                } else if (str[i - 1] == str2[j - 1]) {
                    // case where string1 and string2 letters match
                    // consider first string's previous letter (dp[i - 1][j])
                    // and both strings' previous letter (dp[i - 1][j - 1])
                    dp[i][j] = ((dp[i - 1][j] % MOD) +
                                        (dp[i - 1][j - 1] % MOD)) % MOD;
                } else {
                    // case where string and string2 letters don't match
                    // use solution from previous line/step
                    // consider only first string's previous letter
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        // the number of strings
        return dp[n][m];
    }

    long long get_result() {
        return get_nr_substrings(str, substring, unique_letters);
    }

    /**
     * Function displaying the calculated number of substrings
     * @param result number of substrings
    **/
    void print_output(long long result) {
        ofstream fout("./crypto.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task();
    if (!task) {
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
