#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <locale>
#include <algorithm>
#include <cstring>


using namespace std;


class FakeClass{
    private:
    vector<string> vec;

    public:
    FakeClass(){}

    FakeClass(vector<string> v){
        vec = v;
    }

    vector<string> getVec(){
        return vec;
    }

    void display(){
        for(int i = 0; i < vec.size(); i++){
            cout << vec[i] << endl;
        }
    }

};

string readLine(){
    string s;
    getline(cin, s);
    return s;
}


int main() {
    
    string s = "right way, wrong way, correct way,     hello";

    vector<string> vstrings;
    vstrings.push_back("right way");
    vstrings.push_back("wrong way");

    for(int i = 0; i < vstrings.size(); i++){
        cout << vstrings[i] << endl;
    }
    cout << "----------------" << endl;

    // check if "right way" is in the vector
    if(find(vstrings.begin(), vstrings.end(), "right way") != vstrings.end()){
        cout << "found" << endl;
    }else{
        cout << "not found" << endl;
        vstrings.push_back("right way");
    }

    for(int i = 0; i < vstrings.size(); i++){
        cout << vstrings[i] << endl;
    }

    // FakeClass fc = FakeClass(vstrings);
    // fc.display();

    s = readLine();
    s.erase(0, s.find_first_not_of(" "));

    cout << s << endl;

    s = "!@ 123 PieCe <>?_+{[]}";
    // to lower case
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    cout << s << endl;
    

    return 0;
}