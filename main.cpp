// Wikipedia Associated Article Project
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
using namespace std;


class Wiki
{
public:
    vector<vector<int>> adjList;

    Wiki(string fileName)
    {
        cin.open(fileName);
        string line;
        getline(cin, line); //ignore the top line since its just words
    }

    void run()
    {
        makeEdges();
        //cout << adjList.size();
        //printRaw();
    }

    ~Wiki()
    {
        cin.close();
    }
private:
    ifstream cin;
    pair<int, int> parseLine(string line) //parses a line from the csv
    {
        /*
         * each line is made of 4 elements
         * fromId, fromTitle, toId, toTitle
         * for some reason there are a variable amount of spaces between these elements
         * we shave off the spaces between the elements
         * we only want the first and the third values which are fromId, and toId
         * return a pair of these ids
         */

        vector<string> out;
        istringstream ss(line);
        string s;

        while(getline(ss, s, '\t'))
            out.push_back(s);

        /*for (int i = 0; i < out.size(); i++)
        {
            cout << out[i] << endl;
        }*/

        return make_pair(stoi(out[0]), stoi(out[2]));
    }

    void makeEdges()
    {
        /*
         * Create the adjacency list
         * Every edge can be represented as a pair, from -> to
         * Parse each line and create a vector of a bunch of pairs
         * Then push into the adjacency list
         */
        string line;
        vector<pair<int, int>> edges;
        while(getline(cin, line))
        {
            edges.push_back(parseLine(line));
            /*pair<int, int> pairs = parseLine(line);
            cout << pairs.first << " " << pairs.second << endl;*/
        }

        adjList.resize(edges.size());

        for (int i = 0; i < edges.size(); i++)
        {
            //cout << edges[i].first << " " << edges[i].second << endl;
            adjList[edges[i].first].push_back(edges[i].second);
        }

    }

    void printRaw()
    //function to debug and print the file literally
    {
        string line;
        while(getline(cin, line))
        {
            cout << line << endl;
        }
    }

};

void printer(Wiki const& wiki)
{
    //this is a function to visualize the adjacency list
    for (int i = 0; i < wiki.adjList.size(); i++)
    {
        if (wiki.adjList[i].size() == 0) //there are some ids that aren't used
            continue;

        cout << i << " -> ";
        for (int v : wiki.adjList[i])
        {
            cout << v << " ";
        }
        cout << endl;
    }
}
int main() {
    //input the name of the csv file here
    string file = "Test10000.csv";
    Wiki wiki(file);
    wiki.run();
    printer(wiki);
    return 0;
}