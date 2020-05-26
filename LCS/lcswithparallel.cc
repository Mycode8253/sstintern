
#include<iostream>
#include<vector>
#include<bits/stdc++.h>
#include <fstream>
#include<omp.h>
#include<chrono>

using namespace std;
int chunk  = 10;




char* randomDNAStrandGenerator(int lenOfStrand){

    char BASES[4] = {'A','C','T','G'};
    char* temp_X = new char[lenOfStrand];//(char *)malloc(lenOfStrand*sizeof(char));
    for(int i=0;i<lenOfStrand;i++){
        temp_X[i] = BASES[rand() % 4];
        //cout<<temp_X[i]<<"\t";
    }
    cout<<endl;
    return temp_X;

}

void lcswithMem( int lenght_x , int lenght_y, char *X, char *Y ,double *temp,int num_of_thread){
    int c[lenght_x+1][lenght_y+1];
    int i,j;
//#pragma omp critical
//{
  omp_set_dynamic(0);
   auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel for shared(X,Y,lenght_x,lenght_y,chunk,c) private(i) num_threads(num_of_thread)
         for( i=1;i<lenght_x+1;i++){
         
        c[i][0] = 0;
    }
 #pragma omp parallel for shared(X,Y,lenght_x,lenght_y,chunk,c) private(i) num_threads(num_of_thread)
    for (i = 0; i<lenght_y+1;i++){
        c[0][i] = 0;
    }
  #pragma omp parallel for collapse(2) shared(X,Y,lenght_x,lenght_y,chunk,c) private(i,j) num_threads(num_of_thread)
    for( i=1; i<=(lenght_x);i++){
     
        for( j=1;j<=(lenght_y);j++){
            if (X[i-1] == Y[j-1]){
                c[i][j] = c[i-1][j-1] + 1;
                
            }
            else if (c[i-1][j]>=c[i][j-1]){
                c[i][j] = c[i-1][j];
              
            }
            else {
                c[i][j] = c[i][j-1];
                
            }
        }
        
        
    }
  	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end-start;
       temp[1] =elapsed.count();
    temp[0] = c[lenght_x][lenght_y];
	   
}






int main(void){
	srand(time(NULL));
	int lenght_x;
	int lenght_y;
	ofstream Datafile;

	char* X;
	char* Y;
	int k,i;
	int lengthWithMem;
	double temp_array[2];

	auto programstart= std::chrono::high_resolution_clock::now();
	
	Datafile.open("run_time_memonic_with_para.txt");
	 //#pragma omp parallel private(k,X,Y,temp_array) shared(Datafile)
	{
	for (k=1;k<=20;k+=1){
		cout<<"thread Number"<<omp_get_num_threads()<<" "<<k<<endl;
		lenght_x= lenght_y=100000;
		cout<<"lenght of strand X: "<<lenght_x<<"\n"<<"lenght of strand Y: "<<lenght_y<<endl;
		X = randomDNAStrandGenerator(lenght_x);
        Y = randomDNAStrandGenerator(lenght_y);
        	
        	
       
         lcswithMem(lenght_x,lenght_y,X,Y,temp_array,k);
         
        
       
       
       cout<<"lenght of the Longest common subsequence is "<<temp_array[0]<<endl;
      
        cout<< "Time taken by program with memonization :"<< fixed<<temp_array[1]<<setprecision(30)<<endl; 
       #pragma omp critical
        {
       Datafile<<k<<","<<temp_array[1]<<setprecision(30)<<"\n";
}
        delete[] X;
        delete[] Y;
	}
    
    
	
}

    
   Datafile.close();
	auto programend = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = programend-programstart;
	cout<<"Time takne by the program  to complete ::"<<elapsed.count()<<endl;







}
