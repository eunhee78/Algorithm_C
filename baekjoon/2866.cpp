#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main() {
    int R, C;
    cin >> R >> C;
    vector <vector<char>> table(R, vector<char>(C));
    for(int i=0; i<R; i++) {
        string input;
        cin >> input;
        for(int j=0; j<C; j++) {
            table[i][j] = input[j];
        }
    }

    int start = 0, end = R - 1, mid;
    bool check = false;

    while(start <= end) {
        mid = (start + end) / 2;
        map <string, int> map;
        check = false;
        for(int i=0; i<C; i++) {
            string str = "";
            for(int j=mid; j<R; j++) {
                str += table[j][i];
            }
            if(map.find(str) == map.end()) {
                map.insert(make_pair(str, 1));
            }
            else {
                check = true;
                break;
            }
        }
        if(check) { // 중복된 문자가 존재하면
            end = mid - 1;
        }
        else { // 중복된 문자가 존재하지 않는다면
            start = mid + 1;
        }
    }

    if(check) {
        cout << mid - 1;
    }
    else {
        cout << mid;
    }

    return 0;
}
