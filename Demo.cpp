#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
using namespace std;

// Constants
string INPUT_FILENAME = "InputFile.txt";
string OUTPUT_FILENAME = "OutputFile.txt";
long double D_latitude = 53.339428;
long double D_longitude = -6.257664;

// degree to radian
long double convert_to_radian(long double degree)
{
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}

// Output to a file
void save_data(vector<pair<int,string>> data)
{
	ofstream fout;
	fout.open(OUTPUT_FILENAME);
	for(auto x: data)
	{
		fout<<x.first<<" "<<x.second<<endl;
	}
	fout.close();
}

// Calculate distance
int calculate_distance(long double latitude,long double longitude)
{
	long double latitude1 = convert_to_radian(D_latitude);
    long double longitude1 = convert_to_radian(D_longitude);
    latitude = convert_to_radian(latitude);
    longitude = convert_to_radian(longitude);

	long double dlong = longitude - longitude1;
    long double dlat = latitude - latitude1;
 
    long double ans = pow(sin(dlat / 2), 2) +
                          cos(latitude1) * cos(latitude) *
                          pow(sin(dlong / 2), 2);
 
    ans = 2 * asin(sqrt(ans));
    long double R = 6371;
    ans = ans * R;
	return ans;
}

// Read from a file
void populate_data()
{
	ifstream fin;
	string line;
	fin.open(INPUT_FILENAME);
	int count = 0;
	vector<pair<int,string>> data;
    while (fin) 
	{
        getline(fin, line);
		stringstream ss(line);
      	string token,userName;
		int userId;
		count=0;
		while(getline(ss, token, ','))
    	{	
			count++;
			token.erase(std::remove(token.begin(),token.end(),'\"'),token.end());
			double latitude, longitude;
			if(count==1)
				latitude =  stof(token.substr(token.find(":")+1,token.size()-1));
			else if(count==2)
				userId = stoi(token.substr(token.find(":")+1,token.size()-1));
			else if(count==3)
				userName = token.substr(token.find(":")+1,token.size()-1);
			
			if(count==4)
			{
				token.erase(std::remove(token.begin(),token.end(),'}'),token.end());
				longitude = stof(token.substr(token.find(":")+3,token.size()-1)) * -1;;

				if(calculate_distance(latitude,longitude)<=100)
				{
					data.push_back(make_pair(userId,userName));
				}
			}
    	}
	}
	fin.close();

	sort(data.begin(),data.end());
	save_data(data);
}

int main()
{
	cout<<"Intercom Test"<<endl;
	populate_data();
	cout<<"Thank You";
	return 0;
}