#ifndef GSHARE_H
#define GSHARE_H
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
#include"smithCounter.h"
using namespace std;

class gshare: public smithCounter{
  //BHT has 4 entries
  private: string Bhr;
  //Defination of the constructor
  public: gshare(){
    Bhr="00000";
  }
  public: string getBhr();
  public: void gshareSimulation(vector<string>, vector<string>, gshare );
};

//Defination of the function getBhr()
string gshare:: getBhr(){
  return Bhr;
}
//Defination of the gshareSimulation function
void gshare:: gshareSimulation(vector<string>branchAddress, vector<string>actualPrediction, gshare share){
  string Bhr= share.getBhr();
  int address,
      index,
      notTaken=0,
      taken=0,
      takenCorrect=0,
      notTakenCorrect=0,
      totalBranches=0,instruction=0;
  //This loop takes each branch address and makes a prediction
  for( int i=0;i<branchAddress.size();i++){
    //Hasing done to do indexing
    std::string binary = std::bitset<16>(stoi(branchAddress[i])).to_string();
    address=stoi(binary.substr(9,5),0,2);
    //Xored
    index= (address ^ stoi(Bhr,0,2));
    //If the counter value is less than 2
    if(share.getCounterValue()[index]==0||share.getCounterValue()[index]==1){
      //These 3 lines of codes are used to shift string left by  1
      reverse(Bhr.begin(),Bhr.begin()+1);
      reverse(Bhr.begin()+1,Bhr.end());
      reverse(Bhr.begin(),Bhr.end());
      //if the actual prediction is taken then increment the counter value
      if(actualPrediction[i]=="T"){
        share.updateCounter(index,1);
        Bhr[Bhr.length()-1]='1';
      }
      //if the actual prediction is not taken then decrement the counter value 
      else{
        share.updateCounter(index,-1);
        Bhr[Bhr.length()-1]='0';
        notTakenCorrect++;
      }
    }
    //If the counter value is greater or equal to 2 predict as taken
    else{
      //These 3 lines of codes are used to shift string left by  1
      reverse(Bhr.begin(),Bhr.begin()+1);
      reverse(Bhr.begin()+1,Bhr.end());
      reverse(Bhr.begin(),Bhr.end());
      if(actualPrediction[i]=="T"){
        share.updateCounter(index,1);
        //Inserting 1 as taken at last index of string  bhr
        Bhr[Bhr.length()-1]='1';
        takenCorrect++;
      }
      else{
        share.updateCounter(index,-1);
        //Inserting 0 as not taken at last index of string  bhr
        Bhr[Bhr.length()-1]='0';
      }
    }
    if(actualPrediction[i]=="T")taken++;
    if(actualPrediction[i]=="N")notTaken++;
    totalBranches++;
  }
  //Printing out the results that we got from the loop
  cout<<endl<<endl<<"----Gshare ----"<<endl<<endl;
  cout<<"Number of branches: "<<totalBranches<<endl;
  cout<<"Number of branches taken: "<<taken<<endl;
  cout<<"Number taken branches correctly predicted: "<<takenCorrect<<endl;
  cout<<"Number of branches not taken: "<<notTaken<<endl;
  cout<<"Number not taken branches correctly predicted: "<<notTakenCorrect<<endl;
  cout<<"Overall rate of correct predictions: "<<((takenCorrect+notTakenCorrect)/(float)totalBranches)*100.00<<"%"<<endl;
}

#endif
