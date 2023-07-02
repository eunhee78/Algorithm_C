#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m;
queue <pair<int, int>> tmp;

void move(int dx, int dy, vector <vector<int>> &chess) {
    while(!tmp.empty()) {
        pair<int, int> now = tmp.front(); // 현재 위치
        tmp.pop();
        int nx = now.first + dx;
        int ny = now.second + dy;
        if(nx > 0 && nx <= n && ny > 0 && ny <= m) {
            if(chess[nx][ny] == 0 || chess[nx][ny] == 4) {
                chess[nx][ny] = 4;
                tmp.push({nx, ny});
            }
            else {
                while(!tmp.empty()) tmp.pop();
                break;
            }
        }
    }
}

void queen(int x, int y, vector <vector<int>> &chess) {
    int dx[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dy[8] = {0, 0, -1, 1, -1, 1, -1, 1};
    for(int i=0; i<8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 1 || nx > n || ny < 1 || ny > m) continue; // 벗어남
        if(chess[nx][ny] == 0 || chess[nx][ny] == 4) { // 장애물이 없다면
            tmp.push({nx, ny}); // 다음 위치
            chess[nx][ny] = 4;
            move(dx[i], dy[i], chess);
        }
    }
}

void knight(int x, int y, vector <vector<int>> &chess) {
    int dx[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[8] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for(int i=0; i<8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx < 1 || nx > n || ny < 1 || ny > m) continue; // 벗어남
        if(chess[nx][ny] == 0) {
            chess[nx][ny] = 4;
        }
    }
}

int main() {
    int t = 3, cnt = 0;
    cin >> n >> m; // 체스 행, 열
    vector <vector<int>> chess(n + 1, vector<int>(m + 1, 0)); // 체스판
    for(int block=1; block<=t; block++) {
        int n;
        cin >> n;
        for(int i=0; i<n; i++) {
            int x, y;
            cin >> x >> y;
            chess[x][y] = block;
        }
    }

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(chess[i][j] == 1) {
                queen(i, j, chess);
            }
            if(chess[i][j] == 2) {
                knight(i, j, chess);
            }
        }
    }
    
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=m; j++) {
            if(chess[i][j] == 0) {
                cnt++;
            }
        }
    }
    
    cout << cnt;

    return 0;
}
