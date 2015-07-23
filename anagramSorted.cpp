#include <iostream>
#include <string>
#include <map>
#include <vector>
#include<fstream>
#include<algorithm>

using namespace std;


map <string,pair<vector<string>,int> > hashMap;
pair<vector<string>,int> maxValueString;

ifstream file;

string hash( string str ) {
   string sortedString = str;
   sort(sortedString.begin(),sortedString.end());
   return sortedString ;
}


void combinationUtil(char arr[], char data[], int start, int end, int index, int r)
{
    if (index == r)
    {

        string combString;
        combString = data[0];
        for (int j=1; j<r; j++)
         {
       //   cout << data[j];
          combString = combString + data[j];
         }

        printf("\n");
        sort(combString.begin(),combString.end());
        if(hashMap.find(combString)!=hashMap.end()) {
            pair<vector<string>,int> tempPair = hashMap[combString];
            if(tempPair.second > maxValueString.second)
               maxValueString = tempPair;
        }

        combString.clear();
        return;
    }

    for (int i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, data, i+1, end, index+1, r);
    }
}


void printAnagrams() {
    for ( map<string, pair<vector<string>,int> >::const_iterator i = hashMap.begin(); i != hashMap.end(); ++i) {
        vector<string> wordList= i->second.first;

        for ( int j = 0; j < wordList.size(); j++ ) {
            cout << wordList[j] << "\t";
        }
        cout << endl;

    }
}

int find_score(string s)
{
    int scores[26];
    for(int i=0;i<26;i++)
    {
        scores[i] = i+1;
    }
    int score=0;

    for (int i=0;i<s.length();i++)
    {
        score=score+scores[s[i]-'a'];
    }
    return score;
}

void processDictionary( string filePath )
{
    file.open( filePath.c_str() );
    string word;

    while( getline( file, word ))
    {
        string hashValue = hash( word );

        if ( hashMap.find( hashValue ) == hashMap.end() ) {
        pair<vector<string>,int> wordList;
        wordList.first.push_back(word);
        wordList.second = find_score(hashValue);;
        hashMap.insert( make_pair(hashValue,wordList) );
        }
        else {
            hashMap[ hashValue ].first.push_back( word);

        }

    }

    printAnagrams();
}


int main() {
    maxValueString.second = 0;
    processDictionary( "sowpods.txt" );

    int j,n;
    cin >> n ;
    char inputArray[n];
    for(int i=0;i<n;i++)
     cin >> inputArray[i];

for(int r=n;r>1;r--)
    {
    char data[r];
    combinationUtil(inputArray, data, 0, n-1, 0, r);
    }
    cout << "max score" << maxValueString.second << endl;
    for(j=0;j<maxValueString.first.size();j++)
    {
        cout << maxValueString.first[j] << endl;
    }
}
