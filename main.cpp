// Wikipedia Associated Article Project
#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>
#include <chrono>
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
        printShortestDistance(adjList, 12, 752);
        //makeTest();
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
        if (out.size() < 3) //some entries in the csv file are broken, this skips over those
        {
            //cout << "busted" << endl;
            return make_pair(0, 0);
        }
        //cout << out[0] << " " << out[2] << endl;
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

    void makeTest()
    {
        adjList[0].push_back(1);
        adjList[1].push_back(3);
        adjList[2].push_back(1);
        adjList[3].push_back(2);
        adjList[4].push_back(1);
        adjList[5].push_back(3);
        cout << "hey" << endl;
    }

    bool BFS(vector<vector<int>> adjList, int src, int dest, vector<int> pred, vector<int> dist)
    {

        queue<int> q;

        vector<bool> visited;
        visited.resize(adjList.size());


        for (int i = 0; i < adjList.size(); i++)
        {
            visited.at(i) = false;
            dist[i] = INT_MAX;
            pred[i] = INT_MIN;
        }

        visited[src] = true;
        dist[src] = 0;
        q.push(src);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < adjList[u].size(); i++)
            {
                cout << i << endl;
                cout << visited[adjList[u][i]];
                if (visited[adjList[u][i]] == false)
                {
                    visited[adjList[u][i]] = true;
                    dist[adjList[u][i]] = dist[u] + 1;
                    pred[adjList[u][i]] = u;
                    q.push(adjList[u][i]);

                    if (adjList[u][i] == dest)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    void printShortestDistance(vector<vector<int>> adjList, int src, int dest)
    {
        vector<int> pred;
        vector<int> dist;
        pred.resize(adjList.size());
        dist.resize(adjList.size());

        if (BFS(adjList, src, dest, pred, dist) == false)
        {

            cout << "Not connected" << endl;
            return;
        }
        vector<int> path;
        int crawl = dest;
        path.push_back(crawl);
        while(pred[crawl] != -1)
        {
            path.push_back(pred[crawl]);
            crawl = pred[crawl];
        }
        cout << "Shortest path length: " << dist[dest] << endl;
        cout << "Path is: " << endl;
        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << path[i] << " ";
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
    auto start = chrono::high_resolution_clock::now();
    string file = "Test900000.csv";
    Wiki wiki(file);
    wiki.run();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    //printer(wiki);
    cout << "Time to create graph: " << duration.count() << " seconds." << endl;

    return 0;
}
