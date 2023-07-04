#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int R, C, k; // 방의 세로, 가로, 장애물 개수
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 로봇 방향
pair <int, int> robot; // 로봇의 위치
queue <pair<int, int>> route; // 이동한 곳

// 3. 벽이 아니거나 
void move_bfs(vector <int> direct, vector<vector<int>> room, vector<vector<int>> &visit) {
    while(1) {
        bool flag = false; // 이동 가능 여부
        for(int i=0; i<4; i++) {
            int dx = dir[direct[i]][0];
            int dy = dir[direct[i]][1];
            int nx = robot.first + dx;
            int ny = robot.second + dy;

            while(1) {
                if(nx < 0 || ny < 0 || nx >= R || ny >= C) break; // 범위 벗어난 경우 끝내기
                if(room[nx][ny] || visit[nx][ny]) break; // 벽이 있거나 방문했던 곳이라면 끝내기
                visit[nx][ny] = 1;
                flag = true;
                nx += dx;
                ny += dy;
            }

            robot = {nx - dx, ny - dy};
        }
        if(!flag) break;
    }
}

int main() {
    // 1. 입력 받기
    cin >> R >> C >> k;
    vector <vector<int>> room(R, vector<int>(C, 0)); // 방의 상태
    for(int i=0; i<k; i++) {
        int x, y;
        cin >> x >> y;
        room[x][y] = 1; // 벽(장애물) 설치
    }
    cin >> robot.first >> robot.second;

    vector <vector<int>> visit(R, vector<int>(C, 0)); // 방문 여부
    visit[robot.first][robot.second] = 1; // 로봇 처음 위치 방문 체크

    // 2. 이동 방향의 순서 입력 받기
    // 사용자가 지정한 다음 방향이 없다면 맨 처음 방향으로 돌아가서 위의 과정을 반복
    vector <int> direct;
    for(int i=0; i<4; i++) {
        int n;
        cin >> n;
        direct.push_back(n-1);
    }
    
    move_bfs(direct, room, visit);

    // 3. 로봇의 마지막 위치 출력
    cout << robot.first << " " << robot.second;

    return 0;
}
