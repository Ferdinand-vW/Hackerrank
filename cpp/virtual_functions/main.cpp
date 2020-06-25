#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

class Person{

  public:
    std::string name;
    int age;
    virtual void getdata(){};
    virtual void putdata(){};

};

class Professor : public Person {

  public:
    int publications;
    static int cur_id;
    int id;
    Professor() {
      id = cur_id;
      cur_id++;
    }
    virtual void getdata() {
      std::cin >> name >> age >> publications;
    }
    virtual void putdata() {
      std::cout << name << " " << age << " " << publications << " " << id << std::endl;
    }
};

class Student : public Person {
  public:
    int marks[6];
    static int cur_id;
    int id;
    Student() {
      id = cur_id;
      cur_id++;
    }
    virtual void getdata() {
      std::cin >> name >> age >> marks[0] >> marks [1] >> marks[2] >> marks[3] >> marks[4] >> marks[5];
    }
    virtual void putdata() {
      int sum = std::accumulate(marks,marks+6,0);
      std::cout << name << " " << age << " " << sum << " " << id << std::endl;
    }
};
int Professor::cur_id = 1;
int Student::cur_id = 1;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}
