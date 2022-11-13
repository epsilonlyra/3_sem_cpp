#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>

struct Comparator_consistence {
    bool operator()(std :: string  left, std :: string right) {


        if (left.length() <  right.length()) {
                return true;
        }

        std :: sort(left.begin(), left.end());
        std :: sort(right.begin(), right.end());

        if (left.compare(right) < 0 ) {
                return true;
           }

        return  false;
    }
};



std :: vector<std :: vector<std :: string>> groupByName( std :: vector<std :: string>& strs) {

    std :: map <std :: string, std :: vector<std :: string>, Comparator_consistence> amogus;

    for (auto iter = strs.begin(); iter != strs.end(); ++iter) {



            if (amogus.find(*iter) == amogus.end()) {
                std :: vector <std :: string> a =  {*iter};
                amogus[*iter] = a;

            }

            else {
                (amogus.find(*iter)->second).push_back(*iter);
            }
    }

    std :: vector<std :: vector<std :: string>> result;

    for (auto iter = amogus.begin(); iter != amogus.end(); ++iter) {
        result.push_back(iter->second);
    }


    return result;

}
int main() {

std :: vector<std :: string> strs = { "bat", "nat", "tab", "ant", "tan"};

std :: vector<std :: vector<std :: string>> andrey = groupByName(strs);

for (auto x = andrey.begin(); x != andrey.end(); ++x) {

    for (auto iter = x->begin(); iter != x->end(); ++iter) {
        std :: cout << *iter << ' ';
    }
    std :: cout << std :: endl;
}


}
