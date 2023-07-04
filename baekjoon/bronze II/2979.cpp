#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    int fee[3], total; // 트럭의 개수에 따른 요금(1, 2, 3)
    vector <pair<int, int>> truck(3);
    cin >> fee[0] >> fee[1] >> fee[2];

    for(int i=0; i<3; i++) {
        cin >> truck[i].first >> truck[i].second; // 입차시간, 출차시간
    }

    sort(truck.begin(), truck.end());

    queue <int> parking;
    int idx = 0;
    for(int i=1; i<100; i++) {
        while(truck[idx].first == i) {
            parking.push(truck[idx++].second);
        }
        int n = parking.size();
        while(n--) {
            if(parking.front() != i) {
                parking.push(parking.front());
            }
            parking.pop();
        }
        n = parking.size();
        total += n * fee[n-1]; 
    }

    cout << total;

    return 0;
}
