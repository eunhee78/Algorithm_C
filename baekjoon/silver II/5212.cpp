#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int visit[10][10];

int main() {
    int R, C;
    cin >> R >> C;
    vector <vector<char>> map(R, vector<char>(C)); // 다도해 지도 (R * C)
    queue <pair<int, int>> island;

    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cin >> map[i][j];
            if(map[i][j] == 'X') { // 섬일 경우 push !
                island.push({i, j});
            }
        }
    }

    int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 상, 하, 좌, 우
    pair <int, int> start, end;
    bool check = false;

    while(!island.empty()) {
        pair<int, int> now = island.front();
        island.pop();

        int cnt = 0;
        for(int i=0; i<4; i++) {
            int nx = now.first + dir[i][0];
            int ny = now.second + dir[i][1];

            if(nx < 0 || nx >= R || ny < 0 || ny >= C) {
                cnt++;
                continue;
            }

            if(map[nx][ny] == '.' && !visit[nx][ny]) {
                cnt++;
            }
        }

        if(cnt >= 3) { // 섬이 잠긴 경우
            map[now.first][now.second] = '.';
            visit[now.first][now.second] = 1;
        }
        else {
            if(!check) { // 처음일 경우 start, end 대입
                check = true;
                start = now;
                end = now;
            }

            else {
                if(start.second > now.second) {
                    start.second = now.second;
                }
                if(end.first < now.first) {
                    end.first = now.first;
                }
                if(end.second < now.second) {
                    end.second = now.second;
                }
            }
        }
    }

    if(start == end) {
        cout << 'X';
    }

    else {
        for(int i=start.first; i<=end.first; i++) {
            for(int j=start.second; j<=end.second; j++) {
                cout << map[i][j];
            }
            cout << endl;
        }
    }

    return 0;
}
