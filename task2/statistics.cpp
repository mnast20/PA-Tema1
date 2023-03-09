#include <bits/stdc++.h>
using namespace std;

struct Word {
    int length;
    int alphabet_appearances[27] = {};
    int current_character = 0;  // used for iterating through the alphabet
};

class Task2 {
 public:
    void solve() {
        read_input();
        print_output(get_result());
    }

 private:
    int n, x, y;
    vector<Word> strings;

    /**
     * Function reading and processing the provided input
    **/
    void read_input() {
        ifstream fin("./statistics.in");
        fin >> n;

        string s;

        // read array of string
        for (int i = 0; i < n; ++i) {
            fin >> s;
            Word str;
            // put word length in structure
            str.length = s.length();
            // count number of letter occurences in each string
            count_appearances_string(str, s);
            strings.push_back(str);
        }

        fin.close();
    }

    /**
     * Function calculating the number of appearances for each letter
     * in a given string
     * @param str structure containing string's length and alphabet
     * frequency vector
     * @param str string
    **/
    void count_appearances_string(Word &str, string &s) {
        // increment number of occurences for every letter in string
        for (long unsigned int i = 0; i < s.length(); ++i) {
            str.alphabet_appearances[s[i] - 'a']++;
        }
    }

    /**
     * Function comparing two strings based on character's appearances
     * and string size
     * in a given string
     * @param s1 string structure
     * @param s2 string structure
     * @param pos position in alphabet
    **/
    static bool compare_strings(Word &s1, Word &s2) {
        int diff1 =
            2 * (s1.alphabet_appearances[s1.current_character]) - s1.length;
        int diff2 =
            2 * (s2.alphabet_appearances[s2.current_character]) - s2.length;

        return (diff1 > diff2);
    }

    /**
     * Function calculating the maximum number of concatenated words
     * @param n total number of words
     * @param strings array of words' structures
    **/
    int get_max_nr_words(int n, vector<Word> &strings) {
        int max_words = 0;

        // iterate through alphabet
        for (int i = 0; i <= 26; ++i) {
            // sort strings based on current letter

            if (i >= 1) {
                // increment the position in the alphabet
                // for every word structure
                for (int j = 0; j < n; j++) {
                    strings[j].current_character++;
                }
            }

            sort(strings.begin(), strings.end(), compare_strings);

            int nr_concatenated_words = 0;
            int char_appearances = 0;
            int concatenated_length = 0;

            // iterate through sorted array of strings
            for (Word &str : strings) {
                // calculate the number of current letter's appearances
                // in concatenated words
                char_appearances += str.alphabet_appearances[i];
                // calculate the length of concatenated words
                concatenated_length += str.length;

                // check if letter dominance condition is satisfied
                if (2 * char_appearances <= concatenated_length) {
                    break;
                }

                // increment the number of current concatenated words
                nr_concatenated_words++;
            }

            // check if max value
            if (nr_concatenated_words > max_words) {
                max_words = nr_concatenated_words;
            }
        }

        // no letter dominance
        if (max_words == 0) {
            return -1;
        }

        return max_words;
    }

    /**
     * Function returning the resulted maximum number of words
    **/
    int get_result() {
        return get_max_nr_words(n, strings);
    }

    /**
     * Function displaying the calculated maximum number of concatenated words
     * @param result maximum number of words
    **/
    void print_output(int result) {
        ofstream fout("./statistics.out");
        fout << result;
        fout.close();
    }
};

int main() {
    auto* task = new (nothrow) Task2();
    if (!task) {
        return -1;
    }
    task->solve();
    delete task;
    return 0;
}
