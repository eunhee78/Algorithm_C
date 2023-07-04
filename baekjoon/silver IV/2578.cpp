#include <iostream>
#include <map>
using namespace std;

int check[5][5];

int bingo_check() {
    int cnt = 0;
    for(int i=0; i<5; i++) {
        int col_flag = 0, row_flag = 0;
        for(int j=0; j<5; j++) {
            if(check[i][j]) col_flag++;
            if(check[j][i]) row_flag++;
        }
        if(col_flag == 5) cnt++;
        if(row_flag == 5) cnt++;
    }

    int left_cross = 0, right_cross = 0;
    for(int i=0; i<5; i++) {
        if(check[i][i]) left_cross++;
        if(check[4-i][i]) right_cross++;
    }

    if(left_cross == 5) cnt++;
    if(right_cross == 5) cnt++;

    return cnt;
}

int main() {
    int bingo_cheolsu[5][5], bingo_order[5][5]; // 철수의 빙고, 사회자의 빙고
    map <int, pair<int, int>> pos;
    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            cin >> bingo_cheolsu[i][j];
            pos.insert({bingo_cheolsu[i][j], {i, j}});
        }
    }

    for(int i=0; i<5; i++) {
        for(int j=0; j<5; j++) {
            cin >> bingo_order[i][j];
            pair <int, int> idx = pos[bingo_order[i][j]];
            check[idx.first][idx.second] = 1;
            if(bingo_check() >= 3) {
                cout << i * 5 + (j+1);
                exit(0);
            }
        }
    }

    return 0;
}
