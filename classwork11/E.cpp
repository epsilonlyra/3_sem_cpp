#include<iostream>
#include<vector>

int removeDuplicates(std :: vector<int>& nums) {
    auto iter = nums.begin();
    auto iter_next = ++nums.begin();

    while (iter!= nums.end()) {

        if ((*iter_next) == *iter) {

            iter = nums.erase(iter_next);
            iter_next = iter;
            if (iter_next == nums.end()) {
                break;
            }
            ++iter;
        }

        else {
            ++iter;
            ++iter_next;
        }
    }

    return nums.size();
}


int main() {

std :: vector<int> alice = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
std :: cout << removeDuplicates(alice) << '\n';

for (int x : alice ) {
    std :: cout << x << ' ';
}




return 0;
}
