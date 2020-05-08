#include <iostream>
#include <vector>
#include <algorithm> //for sort 

using namespace std;

void sortingofArrays(){
    // creatign a vector of vector
    vector<vector<int>> vectVariable{{5,6,7},
                                    {53,66,56},
                                    {8,9,10}};
    for(int i=0;i<vectVariable.size();i++){
        for(int j=0;j<vectVariable[i].size();j++){
            cout<<vectVariable[i][j]<<"\t";
        }
        cout<<endl;
    }

    sort(vectVariable[0].begin(),vectVariable[0].end());
    for(int i=0;i<vectVariable.size();i++){
        for(int j=0;j<vectVariable[i].size();j++){
            cout<<vectVariable[i][j]<<"\t";
        }
        cout<<endl;
    }
}
void passingVectorByReference(vector<int> &temp){
    for(auto i  =temp.begin();i!=temp.end();++i){
        cout<<*i<<"t";

    }
}

int main(){
    vector<int> g1;
    for(int i=1;i<=5;i++){
        g1.push_back(i);
    }
    for(auto i=g1.cbegin();i!=g1.cend();i++){
        cout<<*i<<"";
    }
    cout<<endl;

    sortingofArrays();
    vector<int> temp = {1,2,3};
    passingVectorByReference(temp);


 
}


