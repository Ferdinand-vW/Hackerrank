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
    Workshop *workshops; 
};

Available_Workshops* initialize(int start_time[],int duration[], int n) {
    Workshop *workshops = new Workshop[n];
    for (int i = 0; i < n; i ++) {
        workshops[i] = Workshop { start_time[i], duration[i], start_time[i] + duration[i] };
    }
 
    return new Available_Workshops { n, workshops };  
}


int CalculateMaxWorkshops(Available_Workshops* ptr) {
    std::map<int,int> maxWorkShops;
    auto av_ws = ptr->workshops;
    std::sort(av_ws,av_ws+ ptr->n,[](Workshop &w1, Workshop &w2) { return w1.start_time < w2.start_time 
                                                                       || (w1.start_time == w2.start_time 
                                                                       && w1.end_time <= w2.end_time); });

    std::map<int,std::vector<int>> table;
    for (int i = ptr->n - 1; i >= 0 ;i--) {
        auto currWs = av_ws[i];
        std::vector<std::pair<int,std::vector<int>>> validWs;
        std::set<int> toRemoveWs;

        for(auto p : table) {
            if (currWs.end_time <= av_ws[p.first].start_time) {
                validWs.push_back(p);
            }
        }

        for(auto p : validWs) {
            for (auto ws : p.second) {
                table.erase(ws);
            }
        }

        validWs.push_back(std::pair<int,std::vector<int>>(0,{})); // ensure vector is non-empty
        auto maxPath = std::max_element(validWs.begin(),validWs.end(),[](std::pair<int,std::vector<int>> &p1,std::pair<int,std::vector<int>> &p2) { return p1.second.size() <= p2.second.size(); });
        maxPath->second.push_back(i);

        table.insert(std::pair<int,std::vector<int>>(i,maxPath->second));

    }

    auto max = std::max_element(table.begin(),table.end()
                               ,[](const std::pair<int,std::vector<int>> &p1,const std::pair<int,std::vector<int>> &p2) 
                                    { return p1.second.size() <= p2.second.size(); }
                                );
    return max->second.size();
    
    //std::max(table.begin()->second.first,table.begin()->second.second);   
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
