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
    vector<vector<int>> adjMatrix;
    Wiki(string fileName)
    {
        cin.open(fileName);
        if (cin.is_open())
        {
            string line;
            getline(cin, line); //ignore the top line since its just words
        }
        else
        {
            cout <<"invalid filename" << endl;
        }

    }

    void run()
    {
        makeEdges();
        listShortestDistance(adjList, 12, 752);
        //makeTest();
        //cout << adjList.size();
        //printRaw();
    }



    ~Wiki()
    {
        cin.close();
    }

    void makeTest()
    {
        adjList.resize(6);
//        adjList[0].push_back(1);
//        adjList[1].push_back(3);
//        adjList[2].push_back(1);
//        adjList[3].push_back(2);
//        adjList[4].push_back(1);
//        adjList[5].push_back(3);
        adjList[0].push_back(1);
        adjList[1].push_back(2);
        adjList[2].push_back(3);
        adjList[3].push_back(4);
        adjList[5].push_back(4);
        adjList[0].push_back(5);
        this->listShortestDistance(adjList, 0, 4);
        adjMatrix = vector<vector<int>> (6, vector<int> (6,0));
//        adjMatrix[0][1] = 1;
//        adjMatrix[1][3] = 1;
//        adjMatrix[2][1] = 1;
//        adjMatrix[3][2] = 1;
//        adjMatrix[4][1] = 1;
//        adjMatrix[5][3] = 1;
        adjMatrix[0][1] = 1;
        adjMatrix[1][2] = 1;
        adjMatrix[2][3] = 1;
        adjMatrix[3][4] = 1;
        adjMatrix[5][4] = 1;
        adjMatrix[0][5] = 1;
        this->matrixShortestDistance(adjMatrix, 0, 4);
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

    bool listBFS(vector<vector<int>> &adjList, int src, int dest, vector<int> &pred)
    {

        queue<int> q;

        vector<bool> visited;
        visited.resize(adjList.size());


        for (int i = 0; i < adjList.size(); i++)
        {
            visited.at(i) = false;
            pred[i] = -1;
        }

        visited[src] = true;
        q.push(src);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < adjList[u].size(); i++)
            {
                if (!visited[adjList[u][i]])
                {
                    visited[adjList[u][i]] = true;
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

    void listShortestDistance(vector<vector<int>> adjList, int src, int dest)
    {
        vector<int> pred;
        pred.resize(adjList.size());

        if (!listBFS(adjList, src, dest, pred))
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
        cout << endl << "Calculate shortest path using adjList and BFS" << endl;
        cout << "Shortest path length: " << path.size() << " (" << path.size()-1 << " clicks)" << endl;
        cout << "Path is: ";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << path[i] << " ";
        }


    }

    bool matrixBFS(vector<vector<int>> &adjMatrix, int src, int dest, vector<int> &pred)
    {

        queue<int> q;

        vector<bool> visited;
        visited.resize(adjMatrix.size());


        for (int i = 0; i < adjMatrix.size(); i++)
        {
            visited.at(i) = false;
            pred[i] = -1;
        }

        visited[src] = true;
        q.push(src);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (int i = 0; i < adjMatrix[u].size(); i++)
            {
                if (!visited[i] && adjMatrix[u][i] ==1)
                {
                    visited[i] = true;
                    pred[i] = u;
                    q.push(i);

                    if (i == dest)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    void matrixShortestDistance(vector<vector<int>> adjMatrix, int src, int dest)
    {
        vector<int> pred;
        pred.resize(adjMatrix.size());

        if (!matrixBFS(adjMatrix, src, dest, pred))
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
        cout << endl << "Calculate shortest path using asjMatrix and BFS" << endl;
        cout << "Shortest path length: " << path.size() << " (" << path.size()-1 << " clicks)" << endl;
        cout << "Path is: ";
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
/*    //input the name of the csv file here
    auto start = chrono::high_resolution_clock::now();
    string file = "Test900000.csv";
    Wiki wiki(file);
    wiki.run();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    //printer(wiki);
    cout << "Time to create graph: " << duration.count() << " seconds." << endl;
    */
    Wiki wiki("dummy filename");
    wiki.makeTest();
    return 0;


}