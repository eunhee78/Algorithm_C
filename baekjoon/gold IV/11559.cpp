#include <iostream>
#include <string>
#include <queue>
using namespace std;

char puyo[12][6];
int row = 12, col = 6, check[12][6];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 상하좌우
queue <pair<int, int>> remove_list; // 제거할 뿌요 리스트

int find_puyo(int x, int y) {
    int link[12][6] = {0}, cnt = 1;
    queue <pair<int, int>> visit;
    visit.push({x, y});
    link[x][y] = 1;

    // 연결된 같은 뿌요 찾기
    while(!visit.empty()) {
        pair <int, int> pos = visit.front();
        visit.pop();

        for(int i=0; i<4; i++) {
            int nx = pos.first + dir[i][0];
            int ny = pos.second + dir[i][1];

            if(nx < 0 || ny < 0 || nx >= row || ny >= col) continue;
            if(puyo[pos.first][pos.second] != puyo[nx][ny]) continue;
            if(check[nx][ny] == 0 && link[nx][ny] == 0) {
                cnt++;
                link[nx][ny] = 1;
                visit.push({nx, ny});
            }
        }
    }

    if(cnt >= 4) {
        for(int i=0; i<row; i++) {
            for(int j=0; j<col; j++) {
                if(link[i][j]) {
                    remove_list.push({i, j});
                    check[i][j] = 1;
                }
            }
        }
    }

    return cnt;
}

void bomb_puyo() {
    while(!remove_list.empty()) {
        int x = remove_list.front().first;
        int y = remove_list.front().second;
        remove_list.pop();

        puyo[x][y] = '.';
    }
}

void setting() {
    for(int i=0; i<col; i++) {
        for(int j=row-1; j>=0; j--) {
            if(puyo[j][i] != '.') {
                pair <int, int> idx(-1, -1);
                for(int k=row-1; k>j; k--) {
                    if(puyo[k][i] == '.') {
                        idx = {k, i};
                        break;
                    }
                }

                if(idx.first != -1 && idx.second != -1) {
                    puyo[idx.first][idx.second] = puyo[j][i];
                    puyo[j][i] = '.';
                }
            }
        }
    }
}

main() {
    // 1. 필드 정보 입력받기    
    for(int i=0; i<row; i++) {
        string input;
        cin >> input;
        for(int j=0; j<input.length(); j++) {
            puyo[i][j] = input[j];
        }
    }

    int answer = 0; // 연쇄 횟수

    while(1) {
        // 2. 4개 이상의 연결된 뿌요가 있는지 체크
        bool flag = false;
        for(int i=0; i<row; i++) {
            for(int j=0; j<col; j++) {
                if(puyo[i][j] != '.' && check[i][j] == 0) {
                    check[i][j] = 1;
                    int n = find_puyo(i, j);
                    if(n >= 4) flag = true;
                }
            }
        }

        // 3. 터질 뿌요가 있다면 터트리기
        if(flag) {
            answer++;
            bomb_puyo();
            setting();
        }

        else {
            break;
        }
        
        fill(&check[0][0], &check[row][0], 0);
    }

    cout << answer;
    
    return 0;
}
