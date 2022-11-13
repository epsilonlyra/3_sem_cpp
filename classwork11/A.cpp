#include<iostream>
#include<set>
#include<vector>

int numRabbits(std :: vector<int>& answers) {
    int NumberRabbits = 0;
    std :: set<int> given_answers;


    for (std :: vector<int> :: iterator answer_iter = answers.begin(); answer_iter != answers.end(); ++answer_iter) {
        if (given_answers.count(*answer_iter) ==  0) {
            NumberRabbits += 1 + *answer_iter;
            given_answers.insert(*answer_iter);
        }
    }
    return NumberRabbits;
}

int main() {


std ::vector<int> elena  = {10, 10, 10};

std :: cout << numRabbits(elena);

return 0;
}
