#include<iostream>
#include<algorithm>
#include<list>
#include<iterator>
#include<forward_list>

//emplace(position,value) it is used ti insert an element at the postion specified
//emplace_back(value) add value at the end of the list
//emplace_front(value) add value at the front of the list
//list1.merge(list2): it is used to merge list2 with list1 if boht the lists are sorted in order then the resulting list will also be sorted
//remove_if(condition): this function removes the element from the list based on the conditions
//swap(lis2)
//splice(postion.list2): this is used to move the elements from one list to another based on the position specified


using namespace std;

void showlist(list<int> g){
    list<int> ::iterator it;
    for(it=g.begin();it!=g.end();++it){
        cout<<'\t'<<*it;
        
    }
    cout<<endl;
}
void task1(){
    int sum=0;
    list<int> temp_list{0,1,2,3,4,5,6,7,8,9};
    while(!temp_list.empty()){
        sum +=temp_list.front();
        temp_list.pop_front();

    }

    cout<<sum;
}


int main(){
    list<int> gqlist1,gqlist2;
    for(int i=0;i<10;i++)
    {
        gqlist1.push_back(i*1);
        gqlist2.push_back(i*2);


    }

    forward_list<int> forward_list_variable_1,forward_list_variable_2;
    forward_list_variable_1.assign({1,2,3});
    forward_list_variable_2.assign(10,10);
    forward_list_variable_1.push_front(56);// this places the foward list in the front of the element given as argument
    forward_list_variable_2.emplace_front(56);// simlar to the previuos one but it places the element given as argument in memory present at teh frot of the list
    for(auto &temp1:forward_list_variable_1){
        cout<<temp1<<" ";
    }
    cout<<endl;

    for(auto &temp2:forward_list_variable_2){
        cout<<temp2<<" ";
    }
    cout<<endl;
    list<int> temp_list{};
    if(temp_list.empty()){
        cout<<"True";
    }else{
        cout<<"False";
    }
    cout<<endl;
    task1();
    cout<<endl;
    

   



    




}