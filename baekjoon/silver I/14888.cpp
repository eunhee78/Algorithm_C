#include <iostream>
#include <vector>
using namespace std;

int N, arr[12], operate[4], min_value = 2147000000, max_value = -2147000000;

void dfs(int idx, int sum) {
    if(idx == N - 1) { // 마지막 숫자
        min_value = min(min_value, sum);
        max_value = max(max_value, sum);
        return;
    }

    else {
        for(int i=0; i<4; i++) {
            if(operate[i] > 0) {
                operate[i]--;
                if(i == 0) { // 더하기
                    dfs(idx + 1, sum + arr[idx + 1]);
                    operate[i]++;
                }
                if(i == 1) { // 빼기
                    dfs(idx + 1, sum - arr[idx + 1]);
                    operate[i]++;
                }
                if(i == 2) { // 곱하기
                    dfs(idx + 1, sum * arr[idx + 1]);
                    operate[i]++;
                }
                if(i == 3) { // 나누기
                    if(sum < 0 && arr[idx + 1] > 0) {
                        dfs(idx + 1, ((-1) * sum / arr[idx + 1]) * (-1));
                    }
                    else {
                        dfs(idx + 1, sum / arr[idx + 1]);
                    }
                    operate[i]++;
                }
            }
        }
    }
}

int main() {
    cin >> N; // 숫자 개수

    for(int i=0; i<N; i++) {
        cin >> arr[i]; // 수열
    }

    for(int i=0; i<4; i++) {
        cin >> operate[i]; // 연산자 개수
    }

    dfs(0, arr[0]);

    cout << max_value << endl;
    cout << min_value << endl;

    return 0;
}
