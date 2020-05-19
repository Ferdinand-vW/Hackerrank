#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
struct Workshop {
    int start_time;
    int duration;
    int end_time;
};

struct Available_Workshops {
    int n;
    std::vector<Workshop> workshops; 
};

Available_Workshops* initialize(int start_time[],int duration[], int n) {
    std::vector<Workshop> workshops;
    for (int i = 0; i < n; i ++) {
        workshops.push_back( Workshop { start_time[i], duration[i], start_time[i] + duration[i] } );
    }
 
    return new Available_Workshops { n, workshops };  
}

int CalculateMaxWorkshops(Available_Workshops* ptr) {
    auto av_ws = ptr->workshops;
    std::sort(av_ws.begin(),av_ws.end()
            ,[](Workshop &w1, Workshop &w2) { 
                return w1.end_time < w2.end_time; 
                });

    std::vector<Workshop> maxWs;
    for (int i = 0; i < ptr->n; i++) {
        auto currWs = av_ws[i];
        maxWs.push_back(currWs);

        bool isOverlapping = true;
        while (isOverlapping && i - 1 < ptr->n) {
            if (currWs.end_time > av_ws[i+1].start_time) {
                i++;
            } else {
                isOverlapping = false;
            }
        }
    }

    return maxWs.size();   
}

int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}
