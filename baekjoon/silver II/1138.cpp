#include <iostream>
#include <vector>
using namespace std;

int people[10]; // 키 정보

int main() {
    int N; // 사람의 수
    cin >> N;
    vector <int> result(N, 0);
    for(int i=0; i<N; i++) {
        cin >> people[i];
    }

    for(int i=0; i<N; i++) {
        int cnt = 0;
        for(int j=0; j<N; j++) {
            if(result[j] == 0) cnt++;
            if(cnt == people[i] + 1) {
                result[j] = i + 1;
                break;
            }
        }
    }

    for (int n : result) cout << n << " ";
    
    return 0;
}
