#include<iostream>
#include<map>
#include<vector>

std :: vector<int> twoSum(std :: vector<int>& nums, int target) {

    std :: map<int, int> search_map;
    std :: vector<int> result;

    for (int i = 0; i < nums.size(); i++) {

        auto iter = search_map.find(nums[i]);


        if (iter != search_map.end()) {
            result = {i, iter->second};
        }

        else {
            search_map.insert(std :: pair<int, int>(target - nums[i], i));
        }
    }


    return result;
}

int main() {


std :: vector<int> kolya = {3, 2, 4, 6};

std :: vector<int> result = twoSum(kolya, 6);

std :: cout << '[' << result[0] << ',' <<  result[1] << ']';


return 0;
}
