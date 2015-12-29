#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <string.h> 
#include <fstream>
#include <iostream>
#include<sstream>

using namespace std; 

double distance ( vector<double> , vector<double> , double);
vector <double> knn ( vector< vector<double> > , vector<double> , int , int ); 


int main (void){
	
	std::fstream  testdata,output ;
    testdata.open( "dataset.csv" , std::ios::in ) ;
	output.open("output.csv",std::ios::out);
	vector< vector<double> > data;
	string temp;
	getline(testdata,temp);
	
	printf("Loading data...\n");
	for ( int i=0 ; i < 1000 ; i++){ 
		vector<double> temp;
		for ( int j=0 ; j<1807 ; j++ ){
			double var; char dot;
			testdata >> var;
			if ( j!=1806 ) 
				testdata >> dot;
			temp.push_back(var);
		}
		data.push_back(temp);
		temp.clear();
	}
	
	int k,mode;
	printf("Please enter K = ");
	scanf("%d",&k);
	printf("Please enter your mod ( 0:categorical  1:numerical )");
	scanf("%d",&mode);
	printf("Please wait,processing...");
	for ( int w=1 ; w<=k ; w++ )
		output << "NO." << w << ",";
	output << "prediction,True lable" << endl;
	
	for ( int i=0 ; i<1000 ; i++ ){
		vector<double> anser = knn ( data , data[i] , k , mode );
		for ( int j=0 ; j<k ; j++)
			output << anser[j] << ",";
		
		if ( anser[k+1] == 0 )
			if ( mode == 0 ){
				output << "A,";
				if ( anser[k] == 0 )output << "A" << endl;
				else output << "B" << endl;
			}
			else output << "0," << anser[k] << endl;
		else
			if ( mode == 1 )output << "1," << anser[k] << endl;
			else {
				output << "B,";
				if ( anser[k] == 0 )output << "A" << endl;
				else output << "B" << endl;
			}
	}
	output.close();
	testdata.close();
	return 0;
}

double distance ( vector<double> v1 , vector<double> v2 , double x){
	for ( int i=0 ; i<v1.size()-1 ; i++ )
		x += (v1[i]-v2[i])*(v1[i]-v2[i]);
	return sqrt(x);
}

vector<double> knn ( vector< vector<double> > data , vector<double> query, int k, int mode){
	vector< vector<double> > point;
	vector<double> temp;
	temp.push_back(-1);
	temp.push_back(-1);
	point.push_back(temp);
	temp.clear();
	for ( int j=0 ; j<1000 ; j++ ){
		double x = distance(query,data[j],0);
		for ( int w=0 ; w<k ; w++ ){
			if ( x <= point[w][1] || point[w][1] == -1 ){
				vector< vector<double> >::iterator theIterator = point.begin()+w;
				temp.push_back(j);
				temp.push_back(x);
				temp.push_back(data[j][1806]);
				point.insert(theIterator,1,temp);
				temp.clear();
				point.resize(k);
				break;
			}
		}
	}
	vector<double> anser;
	double target=0;
	for ( int w=0 ; w<k ; w++ ){
		anser.push_back(point[w][0]);
		target += point[w][2];
	}
	
	
	anser.push_back(point[0][2]);
	point.clear();
	if ( target/k < 0.5 ){
		anser.push_back(0);
		return anser;
	}
	else {
		anser.push_back(1);
		return anser;
	} 
} 
