#include<iostream>
#include<set>
#include<random>
#include<chrono>

class RandomizedSet {
    private:
        std :: set<int> core_set;

    public:
        bool insert(int val) {
            if (core_set.count(val) == 0){
                core_set.insert(val);
                return true;
            }
            return false;
        }

        bool remove(int val) {
            if (core_set.count(val) != 0){
                core_set.erase(val);
                return true;
            }
            return false;
        }

        int getRandom()  {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std :: default_random_engine generator(seed);
            std :: uniform_int_distribution<int> distribution (0, core_set.size() - 1 );


            auto iter = core_set.begin();


            std :: advance(iter, distribution(generator) );
            return *(iter);
        }



};

int main() {


RandomizedSet randomizedSet;

randomizedSet.insert(1); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomizedSet.remove(2); // Returns false as 2 does not exist in the set.
randomizedSet.insert(2); // Inserts 2 to the set, returns true. Set now contains [1,2].

std :: cout << randomizedSet.getRandom(); // getRandom() should return either 1 or 2 randomly.
randomizedSet.remove(1); // Removes 1 from the set, returns true. Set now contains [2].
randomizedSet.insert(2); // 2 was already in the set, so return false.
std :: cout << randomizedSet.getRandom(); // Since 2 is the only number in the set, getRandom() will always return 2.


return 0;
}
