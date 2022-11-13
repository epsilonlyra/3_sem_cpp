#include<iostream>
#include<vector>
#include<queue>

enum  color {WHITE, RED, BLUE};

/*
suppose that girls and  boys hate each other
*/

bool possibleBipartition(int n, std :: vector<std :: vector<int>>& dislikes) {


    std :: vector<std :: vector<int>> enemies(n + 1);

    std :: vector<int> color(n + 1, WHITE);

    std :: vector<bool> explored(n + 1, false);

    for (auto pair : dislikes)
    {
        int boy = pair[0];
        int girl = pair[1];
        enemies[boy].push_back(girl);
        enemies[girl].push_back(boy);
    }

    std :: queue<int> dfs_q;

    for (int i = 1 ; i < n + 1; ++i)
    {
        if (!explored[i])
        {
            color[i] = RED;
            dfs_q.push(i);


            while (!dfs_q.empty())
            {
                int boy = dfs_q.front();
                dfs_q.pop();


                if (explored[boy])
                {
                    continue;
                }

                explored[boy] = true;

                for (auto girl : enemies[boy])
                {
                    if (color[girl] == color[boy])
                    {
                        return false;
                    }

                    color[girl] = (color[boy] == RED) ? BLUE : RED;

                    dfs_q.push(boy);
                }
            }
        }
    }
    return true;

}


int main() {
std :: vector<std :: vector<int>> dislikes = {{1,2}, {1, 3}, {3, 2}};
std :: cout << possibleBipartition(4, dislikes);

return 0;
}
