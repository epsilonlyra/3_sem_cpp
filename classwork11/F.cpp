#include<iostream>
#include<string>
#include<vector>
#include<map>


std :: vector<std :: string> findRepeatedDnaSequences(std :: string s, int N = 10) {
    std :: map<std :: string, int> dictionary;

    for (int i = 0; i < s.size() - N; i++) {
        auto substring = s.substr(i, N);

        dictionary[substring] = (dictionary.find(substring) != dictionary.end()) ? dictionary[substring] + 1 : 1;
    }

    std :: vector<std :: string> result;
    for (auto iter = dictionary.begin(); iter != dictionary.end(); ++iter) {
        if (iter->second > 1) {
            result.push_back(iter->first);
        }
    }

    return result;

}
int main() {
std :: string andrey = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
std :: vector<std :: string> answer = findRepeatedDnaSequences(andrey);

for (auto iter = answer.begin(); iter != answer.end(); ++iter) {
    std :: cout << *iter << ' ';
}

return 0;
}


