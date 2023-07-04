#include <iostream>
#include <string>
#include <vector>
using namespace std;

int N, M;
int check[51][51];
char tree[51][51];

void dfs(int x, int y) {
    if(tree[x][y] == '-') {
        if(y + 1 < M && check[x][y + 1] == 0 && tree[x][y + 1] == '-') {
            check[x][y + 1] = 1;
            dfs(x, y + 1);
        }
        else return;
    }
    else {
        if(x + 1 < N && check[x + 1][y] == 0 && tree[x + 1][y] == '|') {
            check[x + 1][y] = 1;
            dfs(x + 1, y);
        }
        else return;
    }
}

int main() {
    int cnt = 0;
    cin >> N >> M;

    for(int i=0; i<N; i++) {
        string input;
        cin >> input;
        for(int j=0; j<M; j++) {
            tree[i][j] = input[j];
        }
    }

    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if(check[i][j] == 0) {
                cnt++;
                check[i][j] = 1;
                dfs(i, j);
            }
        }
    }

    cout << cnt;

    return 0;
}
