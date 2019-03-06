#include <iostream>
#include <fstream>

using namespace std;

struct getLCS{
  int **c;
  char **b;
};

/*function to set the maximum value for each subsquence for c matrix*/
int maxI(int a, int d){
  if(a>=d)
    return a;
  else
    return d;
}

/*function to set the maximum value for each subsquence for b matrix*/
char maxC(int a, int d){
  if(a>=d)
    return '|';
  else
    return '-';
}

/*This function prints the longest common subsequence found*/
void PrintLCS(char **b, char *X, int i, int j){
  if(i==0 || j==0){
    return;
  }
  else if (b[i][j] == '/'){
    PrintLCS(b, X, i-1, j-1);
    cout<<X[i];
  }
  else if (b[i][j] == '|') {
    PrintLCS(b, X, i-1, j);
  }
  else {
    PrintLCS(b, X, i, j-1);
  }
}

/*utility function that traverses both the sequences and provides the result*/ 
getLCS LCS(char *X, char *Y, int n, int m){

  getLCS o;

  o.c = new int*[n];
  o.b = new char*[n];

  for(int i=0; i<n; i++){
    o.c[i] = new int[m];
  }

  for(int i=1; i<n; i++){
    o.b[i] = new char[m];
  }
  for(int i=0; i<n; i++){
    o.c[i][0] = 0;
  }

  for(int j=0; j<m; j++){
    o.c[0][j] = 0;
  }

  for(int i=1; i<n; i++){
    for(int j=1; j<m; j++){
      if(X[i] == Y[j]){
        o.c[i][j] = o.c[i-1][j-1] + 1;
        o.b[i][j] = '/';
      }
      else{
        o.c[i][j] = maxI(o.c[i-1][j], o.c[i][j-1]);
        o.b[i][j] = maxC(o.c[i-1][j], o.c[i][j-1]);
      }
    }
  }

  return o;
}

int main(int argc, char const *argv[]){

  fstream input(argv[1]);
  getLCS o;
  //number of sets
  int num;

  //lengths of sequences X and Y respectively
  int n, m, n1,m1;

  char *X, *Y;

  if(!input){
    cout<<"Unable to read input";
    return -1;
  }
  input>>num;

  for(int l=0; l<num; l++){
    input>>n1>>m1;

    n=n1+1;
    m=m1+1;

    X = new char[n];
    Y = new char[m];

    //filling the sequences
    for(int i=1; i<n; i++){
      input>>X[i];
    }
    for(int i=1; i<m; i++){
      input>>Y[i];
    }
    o = LCS(X, Y, n, m);

    cout<<"The LCS is "<<endl;
    PrintLCS(o.b, X, n1, m1);
    cout<<endl;
  }
  input.close();
  return 0;

}
