//
//  main.cpp
//  C++ Terminal
//
//  Created by Jiaqi Li on 2019/12/29.
//  Copyright © creation date - 2020 Jiaqi Li. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    
    int T;
    int N;
    int K;
    cin >> T;
    for (int i = 0; i < T; i++){
        cin >> N;
        int *arr = new int [N];
        
        for (int a = 0; a < N; a++){
            cin >> arr[a];
        };
        
        
        sort(arr, arr + N);
        
        cin >> K;
        cout << arr[K-1] << endl;
        
        delete [] arr;
        
    };
    
    return 0;
}




