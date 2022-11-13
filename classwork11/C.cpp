#include<iostream>
#include<map>
#include<vector>
#include<algorithm>


std :: vector<std :: pair<int, int>> sorted_map (std :: map<int , int>& M) {

    std :: vector<std :: pair<int , int> > A;


    for (auto& it : M) {
        A.push_back(it);
    }


    std :: sort(A.begin(), A.end(),  [ ] (std :: pair<int, int>& a,
         std :: pair<int, int>& b) {
            if  (a.second == b.second) {
                return a.first > b.first;
            }

            else {
                return a.second > b.second;
                }
          });

    return A;

}

std ::vector<int> majorityElement(std :: vector<int>& nums) {

    std :: map<int, int> julia;
    for (auto iter  = nums.begin(); iter != nums.end(); ++iter) {
        if (julia.find(*iter) == julia.end()) {
            julia[*iter] = 1;
        }

        else {
            julia[*iter]++;
        }
    }

    std :: vector<int> result;

    for (auto iter  = julia.begin(); iter !=  julia.end(); ++iter) {
        if (iter->second >= nums.size() / 2) {
            result.push_back(iter->first);
            break;
        }
    }

    return result;
}


std ::vector<int> more_than_a_third(std :: vector<int>& nums) {

    std :: map<int, int> julia;
    for (auto iter  = nums.begin(); iter != nums.end(); ++iter) {
        if (julia.find(*iter) == julia.end()) {
            julia[*iter] = 1;
        }

        else {
            julia[*iter]++;
        }
    }

    std :: vector<int> result;

    for (auto iter  = julia.begin(); iter !=  julia.end(); ++iter) {
        if (iter->second >= nums.size() / 3) {
            result.push_back(iter->first);
        }
    }
    return result;
}

std ::vector<int> most_frequent(std :: vector<int>& num, int k) {
    /*
        returns k most frequent elements
        if frequency of elements is equal will return element with th biggest value
    */
    std :: map<int, int> julia;
    for (auto iter  = num.begin(); iter != num.end(); ++iter) {
        if (julia.find(*iter) == julia.end()) {
            julia[*iter] = 1;
        }

        else {
            julia[*iter]++;
        }
    }

    std :: vector<int> result;

    auto  sorted_vector = sorted_map(julia);
    int max_size = sorted_vector.size();

    for (int i = 0; i < std :: min(k, max_size); i++){
        result.push_back(sorted_vector[i].first);
    }

    return result;
}


int main() {


std :: vector<int> nums = {1, 1, 3, 3, 4, 6, 6, 6};
for (auto x : most_frequent(nums, 10)) {
    std :: cout << x << ' ';
}


return 0;
}
