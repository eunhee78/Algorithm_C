#include <iostream>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

int N, L, R; // 나라 크기(N*N), 인구 차이 최소, 최대
int country[50][50], visit[50][50]; // 나라 인구수, 방문 여부
int cnt[2501], total[2501];
int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 상하좌우

void dfs(int x, int y, int kind, queue<tuple<int, int, int>> &list, bool &check) {
    if(x < 0 || x >= N || y < 0 || y >= N) return;
    for(int i=0; i<4; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if(nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if(visit[nx][ny] == 0) {
            int diff = abs(country[x][y] - country[nx][ny]); // 인구 차이
            if(diff >= L && diff <= R) {
                visit[nx][ny] = 1;
                total[kind] += country[nx][ny];
                cnt[kind]++;
                list.push(make_tuple(kind, nx, ny));
                check = true;
                dfs(nx, ny, kind, list, check);
            }
        }
    }
}

int main() {
    int day = 0; // 총 인구 이동 날짜
    cin >> N >> L >> R;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> country[i][j];
        }
    }

    while(1) {
        int kind = 0;
        bool check = false;
        queue <tuple<int, int, int>> list;
        fill_n(cnt, 2501, 0);
        fill_n(total, 2501, 0);
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                if(visit[i][j] == 0) { // 처음 방문할 때
                    visit[i][j] = 1;
                    kind++;
                    cnt[kind]++; // 나라 수
                    total[kind] += country[i][j]; // 인구 수
                    list.push(make_tuple(kind, i, j));
                    dfs(i, j, kind, list, check);
                }
            }
        }

        if(!check) {
            break;
        }

        while(!list.empty() && check) {
            int idx = get<0>(list.front());
            int x = get<1>(list.front());
            int y = get<2>(list.front());
            list.pop();
            country[x][y] = total[idx] / cnt[idx];
            visit[x][y] = 0;
        }

        day++;
    }

    cout << day;

    return 0;
}
