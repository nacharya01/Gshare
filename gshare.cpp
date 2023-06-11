/*
  Name: Nirajan Acharya
  YID: Y00807637
  Course: Computer Architecture
  Project: Gshare Branch Predictor
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<stdio.h>
#include<algorithm>
#include"smithCounter.h"
#include"gshare.h"
using namespace std;

int main(int argc,char ** argv){
  gshare share;
  vector<string> branchAddress;
  vector<string> actualPrediction;

  //This line read branch address and actual prediction from branch_trace.dat file
  share.readData(branchAddress,actualPrediction,argv[1]);
  //This simulates as gshare branch predictor
  share.gshareSimulation(branchAddress,actualPrediction,share);
  return 0;
}
//End of the program
