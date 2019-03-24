/**********************************************************
 * Author        : zhao peng
 * Email         : z.play@foxmail.com
 * Last modified : 2019-3-24 11:39
 * Filename      : main.cpp * Description   :
 * *******************************************************/
#include<bits/stdc++.h>
using namespace std;


vector< vector <long long> > v2d;

void init();
void input(char f[]);
void output();

int main() {
                init();
                input("inputtest1.txt");
                output();

                cout<<"*******refresh*****"<<endl;

                input("inputtest2.txt");
                output();
                return 0;
}
void init(){
                for(int i = 0; i < 500; i++){
                            v2d.push_back(vector<long long >());
                }
}
void input( char f[] ){
                        ifstream infile;
                        long long t1;
                        infile.open(f);
                        if(!infile)
                                cout<<"Input file open failed!"<<endl;
                        while(infile>>t1){
                                v2d[t1%500].push_back(t1);
                        }
                        infile.close();
}
void output(){
                ofstream outfile;
                outfile.open("outputtest.txt");
                if(!outfile)
                        cout<<"Output file open failed!"<<endl;
                for(int i = 0; i < 500; i++){
                                for(int j = 0; j < v2d[i].size(); j++){
                                            cout<<v2d[i][j]<<endl;
                                            outfile<<v2d[i][j]<<endl;
                                }
                }
                outfile.close();
}
