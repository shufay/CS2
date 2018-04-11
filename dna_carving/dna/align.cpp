//
//  align.cpp
//  dna_alignment
//
//  Created by Erika DeBenedictis on 1/27/13.
//  Copyright (c) 2014 California Institute of Technology. All rights reserved.
//
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// scoring values
#define GAP_SCORE -5
#define MISMATCH -1
#define MATCHING 2

/**
 * @brief Packages the score and instruction string the align function returns
 */
struct align_result {
    int score;      // score of this alignment
    string inst;    // instruction on how to align the inputs

    align_result(int s, string i) {
        this->score = s;
        this->inst = i;
    }
    align_result() {
        this->score = 0;
        this->inst = "";
    }
};

// memo_type will allow us to hash the string input to align
// with its output for memoization
typedef unordered_map<string, align_result> memo_type;

// Computes the score for strings s1 and t1. Returns an align_result
// with the computed score and instruction string.
align_result compute(string s1, string t1)
{
    align_result result;
    
    if (s1 == "" && t1 != "")
    {
        result.score += GAP_SCORE; 
        result.inst += "t";     
    }            

    else if (s1 != "" && t1 == "")
    {
        result.score += GAP_SCORE;
        result.inst += "s";
    }

    else if (s1 == t1)
    {
        result.score += MATCHING;
        result.inst += "|";
    }

    else
    {
        result.score += MISMATCH;
        result.inst += "*";
    }

    return result;
}

/**
 * @brief Function takes two strings, s and t, and produces an align_result
 * of the highest alignment score and its corresponding instruction str.
 */
align_result align(string s, string t, memo_type &memo) {
    // if this result is memoized, use recorded result
    string key = s + "," + t;
    if (memo.count(key) > 0){
      return memo[key];
    }

    align_result answer; // Initialize result.

    // Base case: if either s or t are empty, return align_result.
    if (s ==  "" || t == "")
    {
        if (s.size() > 0)
        {
            answer.score = -5 * s.size();

            for (unsigned int i = 0; i < s.size(); i++)
            {
                answer.inst += "s";    
            }   
        }

        else if (t.size() > 0)
        {
            answer.score = -5 * t.size();

            for (unsigned int i = 0; i < t.size(); i++)
            {
                answer.inst += "t";
            }
        }
    }

    else
    {
        string s1, t1, rem1, rem2;
        align_result sub, result1, result2, result3;

        // Case 1
        s1 = "";
        t1 = t.substr(0, 1);
        rem1 = t.substr(1, t.size());
        sub = align(s, rem1, memo);
        result1.score = compute(s1, t1).score + sub.score;
        result1.inst = compute(s1, t1).inst + sub.inst;

        // Case 2
        s1 = s.substr(0, 1);
        t1 = "";
        rem1 = s.substr(1, s.size());
        sub = align(rem1, t, memo);
        result2.score = compute(s1, t1).score + sub.score;
        result2.inst = compute(s1, t1).inst + sub.inst;

        // Case 3
        s1 = s.substr(0, 1);
        t1 = t.substr(0, 1);
        rem2 = t.substr(1, t.size());
        sub = align(rem1, rem2, memo);
        result3.score = compute(s1, t1).score + sub.score;
        result3.inst = compute(s1, t1).inst + sub.inst;

        align_result res[] = {result1, result2, result3};
        answer = res[0];

        for (int i = 0; i < 3; i++)
        {
            if (res[i].score > answer.score)
            {
                answer = res[i];
            }
        }

    }
    /* Before you return your calculated  align_result object,
       memoize it like so:*/
    
    memo[key] = answer;
    return answer;
}

/**
 * @brief Wrapper function to print the results of align
 */
void DNA_align(string s, string t) {
    cout << endl << "Calling DNA align on strings " << s << ", " << t << endl;
    cout << "size of s: " << s.size() << endl;
    cout << "size of t: " << t.size() << endl;
    // create the memoization system
    memo_type memo;

    align_result answer = align(s, t, memo);
    string ans = answer.inst;
    int score = answer.score;

    // Printing section
    // line where string s will be printed, spaces inserted
    string line1 = "";
    // line where string t will be printed, spaces inserted
    string line2 = "";
    // description of the relationship between s and t here (* | s t)
    string line3 = "";

    int j = 0;      // running index in s
    int k = 0;      // running index in t

    for (unsigned int m = 0; m < ans.length(); m++) {
        // i is the next element in our instruction string ans
        string i = ans.substr(m, 1);

        // only in s
        if(i.compare("s") == 0){
            line1 += s[j]; j++;
            line2 += " ";
            line3 += "s";
        }

        // only in t
        else if (i.compare("t") == 0){
            line1 += " ";
            line2 += t[k]; k++;
            line3 += "t";
        }

        // mismatch
        else if (i.compare("*") == 0){
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "*";
        }

        // match
        else {
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "|";
        }
    }

    cout << endl << "ALIGNMENT" << endl;
    cout << line1 << endl << line2 << endl << line3 << endl;
    cout << "Score for this alignment: " << score << endl;
}

int main(){
    // some test cases to begin with
    
    DNA_align("",   "a");
    DNA_align("b",  "");
    DNA_align("a", "a");
    DNA_align("b",  "a");
    DNA_align("b",  "ba");
    DNA_align("ab", "ba");
    DNA_align("ab", "b");
    DNA_align("ACTGGCCGT", "TGACGTAA");
    DNA_align("abracadabra", "avada kedavra");
    DNA_align("b", "ab");
    DNA_align("ab", "b");
    DNA_align("ba", "b");
    DNA_align("abc", "ac");
    DNA_align("abc", "adc");
    
    DNA_align
    (
        "cacgctacct aactgacatg actcttgaag aaatgtcaag ggactggttc atgctcatgc ccaaacagaa agtggcaggt tcactttgca tcaaaatgga ccaggcaata atggataaaa acatcatatt gaaagcaaac ttcagtgtaa tttttaaccg actggaagct ctaatactac ttagagcttt cacagaagaa ggagcaattg tgggagaaat ctcaccgtta ccttcttttc caggacatac tgatgaggat gtcaaaaatg caattggggt cctcatcggg ggacttgaat ggaatgataa cacagttcgg gtctctgaaa ctctacagag attcgcttgg agaaacagta atgaggatgg gagaccttca ctccctccaa agtagaaacg gaaaatggcg agaacaattg ggtcagaagt ttgaagaaat aagatggctg attgaagaag tacgacatag attgaagatt acagaaaata gcttcgaaca gataacgttt atgcaagcct tacaactatt gcttgaagtg gaacaagaga taagaacttt ctcgtttcag cttatttaat gataa",
        "gaggaaatgt caagggactg gtttatgctc atgcccaagc agaaagtgac aggttccctt tgcatcaaaa tggaccaggc aataatggat aaaaccataa tattgaaagc aaacttcagt gtgatttata accgattaga gaccctaata ctacttagag ctttcacaga agaaggaaca atcgtgggag aaatctcacc attaccttct cttccaggac atactagtga ggatgtcaaa aatgcaattg gcatcctcat cggaggactt gaatggaatg ataacacggt tcgagtctct gaaattgtac agagattcgc ttggagaagc attgatgagg atgggagact tccactccct tcagatcaga aacggaaaat ggcgagagca attgagtcag aagtttgaag aaataagatg gttgattgaa gaaatacgac atagattgaa aattacagaa aacagctttg aacagataac atttatgcaa gccttacaac tactgcttga agtggagcaa gagataagaa ccttctcgtt tcagcttatt taa"
        );
    return 0;
}
