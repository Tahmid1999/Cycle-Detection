///Cycle detection.

///For cycle detection I use the idea of disjoint set.
///But I implement it differently.
///My implementation is array based.

#include<iostream>
#include<ctime>
#include<iomanip>
#include<windows.h>


using namespace std;


class Lebel{
 private:
    int field;
    bool flag;


  public:


      void set_field(int y){

      field=y;
      }

      void set_flag(bool z){

      flag=z;
      }


      int get_field(){
            return field;
      }

      bool get_flag(){
            return flag;

      }

  };


///Prototypes
void create_graph(int** &, int );
void populate_graph(int** X,int s,int low,int high,int parcentage);
void display_graph(int** X,int s,int mx);
int max(int** X, int s);
int num_dig(int n);
void cycle_detection(int** G,int n);
bool find_i_j(Lebel* A,int n,int i,int j);
void union_i_j(Lebel* &A,int i,int j);



int main(){
   int **G;
   int n;
   int p;
   int low;
   int high;
   int s;
   int d;
   bool desicion=false;
   cout<<"Enter number of nodes :";
   cin>>n;
   create_graph(G,n);
   cout<<"How much connectedness do you want(your input consider as percentage): ";
   cin>>p;
   while(p>100){
    cout<<"Invalid!!! Please input value within 100 "<<endl;
    cout<<"How much connectedness do you want(your input consider as percentage): ";
    cin>>p;
   }
   cout<<"Enter the lowest weight :";
   cin>>low;
   cout<<"Enter the highest weight :";
   cin>>high;
   populate_graph(G,n,low,high,p);
   display_graph(G,n,max(G,n));
   cycle_detection(G,n);
   system("pause");
   return 0;

}

void create_graph(int** &X, int sz){
	X =new int*[sz];
    for(int i = 0; i < sz; i++)
    X[i] = new int[sz];
}

void populate_graph(int** X,int s,int low,int high,int parcentage){

 int count=0;

 double edges=parcentage/100.0;
 int max_edges=(s*(s-1))/2;
 double estimated_edges=(parcentage*max_edges)/100.00;

 if((estimated_edges-(int)estimated_edges)>=0.50)estimated_edges=(int)estimated_edges+1;


 cout<<"Your "<<parcentage<<"% densely graph is creating..........";

 clock_t start;
 double duration;

 start = clock(); // get current time


 while(true){
   srand(time(0));
   for(int i=0;i<s;i++){
     for(int j=0;j<s;j++){
        if(j==i){
            X[i][j]=0;
        }

        else if(j<i){
            X[i][j]=X[j][i];
        }

        else if(j>i){
              double val=(double)rand()/RAND_MAX;
               if(val<=edges){
                        X[i][j] = low+rand()%(high+1-low);
                        count++;
            }
            else {
                X[i][j]=-1;
            }
        }

      }

    }

    if(count==(int)estimated_edges){

    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    system("cls");
    cout << "Your graph generation took "<< duration << " seconds" <<endl;
    break;

       }
   count=0;

   }

}


int max(int** X, int s){
	int mx=X[0][0];
	for(int i=0;i<s;i++){
      for(int j=0;j<s;j++){
		if(X[i][j]>mx)mx=X[i][j];
	}
	}
	return mx;
}



int num_dig(int n){
	if(n<10)return 1;
	return 1+num_dig(n/10);
}

void display_graph(int** X,int s,int mx){
  cout<<endl;
  for(int i=0;i<s;i++){
      for(int j=0;j<s;j++){
            cout<<setw(num_dig(mx)+2)<<X[i][j];
      }
      cout<<endl;
  }

}





void cycle_detection(int** G,int n){


Lebel *A=new Lebel[n];
bool desicion=true;

for(int i=0;i<n;i++){
    A[i].set_field(-1);
    A[i].set_flag(false);
}



for(int i=0; i<n; i++){
    if(desicion==false){
        break;
    }
    for(int j=0;j<n;j++){
        if( G[i][j]>0 && !A[j].get_flag()){
          bool match=find_i_j(A,n,i,j);
            if(match==false){
                union_i_j(A,i,j);
            }
            else {
                cout<<"Graph contains cycle"<<endl;
                desicion=false;
                break;
            }
           }

        }
         A[i].set_flag(true);
    }
 if(desicion==true){
    cout<<"Graph don't contains cycle"<<endl;
 }

}





bool find_i_j(Lebel* A,int n,int i,int j){

bool match_i=false;
bool match_j=false;


 if(A[i].get_field()==1){
    match_i=true;
 }

 if(A[j].get_field()==1){
    match_j=true;
 }

if (match_i==true && match_j==true){
    return true;
}

else return false;


}

void union_i_j(Lebel* &A,int i,int j){


if(A[i].get_field()==-1){
    A[i].set_field(1);
}

if(A[j].get_field()==-1){
    A[j].set_field(1);
}

}
