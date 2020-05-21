
#include<iostream>
#include<vector>
#include<bits/stdc++.h>
#include <fstream>
#include <omp.h>


using namespace std;

void printLCS(char *b,char X[],int i,int j,int lenght_Y){
    if (i<0 || j<0){
        return ;
    }
    else if (*((b+i*(lenght_Y))+j) == '^')
    {

        printLCS(b,X,i-1,j-1,lenght_Y);
        cout<<X[i]<<" ";

    }
    else if (*((b+i*(lenght_Y))+j) == '>')
    {

        printLCS(b,X,i-1,j,lenght_Y);

    }
    else{

        printLCS(b,X,i,j-1,lenght_Y);

    }


}

char* randomDNAStrandGenerator(int lenOfStrand){

    char BASES[4] = {'A','C','T','G'};
    char* temp_X = (char *)malloc(lenOfStrand*sizeof(char));
    for(int i=0;i<lenOfStrand;i++){
        temp_X[i] = BASES[rand() % 4];
        //cout<<temp_X[i]<<"\t";
    }
    cout<<endl;
    return temp_X;

}

int lcsWithoutMem(char *X, char *Y, int m , int n){
int temp1, temp2, temp3;
    if(m==0 || n==0){
        return 0;
    }
    else if(X[m-1]==Y[n-1]){
        #pragma omp task shared(temp3)  firstprivate(X,Y,m,n)
         temp3 = 1+ lcsWithoutMem(X,Y,m-1,n-1);
        return temp3;
    }
    else {
        #pragma omp task shared(temp1)  firstprivate(X,Y,m,n)
        temp1 =lcsWithoutMem(X,Y, m,n-1);
        #pragma omp task shared(temp2)  firstprivate(X,Y,m,n)
         temp2 = lcsWithoutMem(X,Y,m-1,n);

        #pragma omp taskwait
        return (temp1 > temp2)? temp1 : temp2;
    }
}

int lcswithMem( int lenght_x , int lenght_y, char *X, char *Y ){
    int c[lenght_x+1][lenght_y+1];
      for(int i=1;i<lenght_x+1;i++){
        c[i][0] = 0;
    }
    for (int i = 0; i<lenght_y+1;i++){
        c[0][i] = 0;
    }


    for(int i=1; i<=(lenght_x);i++){

        for(int j=1;j<=(lenght_y);j++){
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
    int lenght_y ;
    ofstream Datafile;
    //char X[]= {'A','C','C','G','G','T','C','G','A','G','T','G','C','G','C','G','G','A','A','G','C','C','G','G','C','C','G','A','A'};
    //char Y[]= {'G','T','C','G','T','T','C','G','G','A','A','T','G','C','C','G','T','T','G','C','T','C','T','G','T','A','A','A'};

    //char X[] = { 'A','B', 'C', 'B', 'D', 'A', 'B' };
    //char Y[] = { 'B', 'D', 'C', 'A', 'B', 'A' };
    //lenght_y =sizeof(Y);
    //lenght_x = sizeof(X);


   
    clock_t start, end;
    






   


    Datafile.open("run_time_openmp_nomemonic.txt");
    int k=0;
    double time_taken_withoutmem;
     char* X;
        char* Y;
    #pragma omp parallel  private(X,Y, lenght_x,lenght_y,k,start,end,time_taken_withoutmem) shared(Datafile)
    {

    #pragma omp for
    for( k=1;k<50;k++){
        cout<<"I am the thread that is executing :"<<omp_get_thread_num()<<endl;
       
        lenght_x = lenght_y  = k;

    cout<<"lenght of strand X: "<<lenght_x<<"\n"<<"lenght of strand Y: "<<lenght_y<<endl;
        X = randomDNAStrandGenerator(lenght_x);
        Y = randomDNAStrandGenerator(lenght_y);
        //clock_gettime(CLOCK_MONOTONIC, &start); 
        start = clock();
        int lengthWithoutMem = lcsWithoutMem(X,Y,lenght_x,lenght_y);
        end= clock();
       // clock_gettime(CLOCK_MONOTONIC, &end); 
         
        time_taken_withoutmem =  double(end - start) / double(CLOCKS_PER_SEC);
       // time_taken_withoutmem = (end.tv_sec - start.tv_sec) * 1e9; 
       // time_taken_withoutmem = (time_taken_withoutmem + (end.tv_nsec - start.tv_nsec)) * 1e-9;
       //start = clock();
        //clock_gettime(CLOCK_MONOTONIC, &start); 
       // int lengthWithMem = lcswithMem(lenght_x,lenght_y,X,Y);
       // clock_gettime(CLOCK_MONOTONIC, &end);
         //end= clock();
        //double time_taken_withmem;
       // time_taken_withmem = (end.tv_sec - start.tv_sec) * 1e9; 
       // time_taken_withmem = (time_taken_withmem + (end.tv_nsec - start.tv_nsec)) * 1e-9;
       //time_taken_withmem = double(end - start) / double(CLOCKS_PER_SEC);

       // cout<<"lenght of the Longest common subsequence is "<<lengthWithMem<<endl;
        cout << "Time taken by program recusively is : " << fixed << time_taken_withoutmem << setprecision(15) <<endl;
        //cout<< "Time taken by program with memonization :"<< fixed<<time_taken_withmem<<setprecision(15)<<endl; 

        Datafile<<lenght_x<<","<<time_taken_withoutmem<<"\n";

        free(X);
        free(Y);
    }
    #pragma omp critical 
    {
    Datafile.close();
}
}
   


    
    /*cout<<"LCS of X and Y is ....."<<endl;
    printLCS((char *)b,X,lenght_x-1,lenght_y-1,lenght_y);
    cout<<endl;*/
    
   
}

