#include <iostream>
#include <queue>
using namespace std;

int N, M, map[100][100], check[100][100];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 상하좌우
queue <pair<int, int>> outAir; // 외부 공기

void air_change() {
    while(!outAir.empty()) { // 외부 공기 찾아서 check 값을 -1로
        int x = outAir.front().first;
        int y = outAir.front().second;
        check[x][y] = -1;
        outAir.pop();

        for(int i=0; i<4; i++) {
            int nx = x + dir[i][0];
            int ny = y + dir[i][1];

            if(nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
            if(map[nx][ny] == 0 && check[nx][ny] == 0) {
                check[nx][ny] = -1;
                outAir.push({nx, ny});
            }
        }
    }
}

void remove_cheese(vector <pair<int, int>> &cheese) {
    for(int i=0; i<cheese.size(); i++) {
        int x = cheese[i].first;
        int y = cheese[i].second;
        
        int air = 0;
        for(int j=0; j<4; j++) {
            int nx = x + dir[j][0];
            int ny = y + dir[j][1];

            if(nx < 0 || ny < 0 || nx >= N || ny >= M) continue;
            if(map[nx][ny] == 0 && check[nx][ny] == -1) {
                air++;
            }
        }

        if(air >= 2) {
            map[x][y] = 0;
            outAir.push({x, y});
            cheese[i] = {-1, -1};
        }
    }
}

int main() {
    cin >> N >> M;

    vector <pair<int, int>> cheese; // 녹일 치즈
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> map[i][j];
            if(map[i][j] == 1) {
                cheese.push_back({i, j});
            }
        }
    }

    // 1. 외부 공기, 내부 공기 구분하기
    outAir.push({0, 0});
    check[0][0] = -1;
    air_change();

    // 2. 녹을 수 있는 치즈 찾아 녹이고 외부 공기와 내부 공기 연결
    int cnt = 0;
    while(1) {
        remove_cheese(cheese);
        if(outAir.empty()) {
            cout << cnt;
            break;
        }
        air_change();
        cnt++;
    }

    return 0;
}
