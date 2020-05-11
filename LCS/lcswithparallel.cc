
#include<iostream>
#include<vector>
#include<bits/stdc++.h>
#include <fstream>
#include<omp.h>


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

int lcswithMem( int lenght_x , int lenght_y, char *X, char *Y ){
    int c[lenght_x+1][lenght_y+1];
    int i,j;
        
   
#pragma omp parallel for shared(X,Y,lenght_x,lenght_y,chunk,c) private(i) 
         for( i=1;i<lenght_x+1;i++){
         
        c[i][0] = 0;
    }
 #pragma omp parallel for shared(X,Y,lenght_x,lenght_y,chunk,c) private(i) 
    for (i = 0; i<lenght_y+1;i++){
        c[0][i] = 0;
    }
  #pragma omp parallel for collapse(2) shared(X,Y,lenght_x,lenght_y,chunk,c) private(i,j)
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
    
     
    return c[lenght_x][lenght_y];
}






int main(void){
	srand(time(NULL));
	int lenght_x;
	int lenght_y;
	ofstream Datafile;
	clock_t start, end;
	char* X;
	char* Y;
	int k,i;
	int lengthWithMem;
	
	
	Datafile.open("Memonic_with_para.txt");
	 #pragma omp parallel private(k,X,Y,start,end) shared(Datafile)
	{
	#pragma omp for 
	for (k=0;k<2000;k++){
		cout<<"thread Number"<<omp_get_thread_num()<<" "<<k<<endl;
		lenght_x= lenght_y=k;
		cout<<"lenght of strand X: "<<lenght_x<<"\n"<<"lenght of strand Y: "<<lenght_y<<endl;
		X = randomDNAStrandGenerator(lenght_x);
        Y = randomDNAStrandGenerator(lenght_y);
        	
        	start = clock();
       
         lengthWithMem = lcswithMem(lenght_x,lenght_y,X,Y);
         end= clock();
        double time_taken_withmem;
        
       
       time_taken_withmem = double(end - start) / double(CLOCKS_PER_SEC);
       cout<<"lenght of the Longest common subsequence is "<<lengthWithMem<<endl;
      
        cout<< "Time taken by program with memonization :"<< fixed<<time_taken_withmem<<setprecision(30)<<endl; 
       #pragma omp critical
        {
       Datafile<<lenght_x<<","<<time_taken_withmem<<"\n";
}
        delete[] X;
        delete[] Y;
	}
    
    
	
}

    
   Datafile.close();









}
