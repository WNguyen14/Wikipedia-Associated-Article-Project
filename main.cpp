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
    vector<pair<int, int>> edgeList;
    Wiki(string fileName)
    {

        //FullGraph.csv size = 163380007
        //adjList.resize(7000000);
        cin.open(fileName);
        cout << "Opening file: " << fileName << endl;
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
        //printShortestDistance(adjList, 12, 752);
        //makeTest();
        //cout << adjList.size()<< endl;
        //printRaw();
    }

    void rewrite()
    {
        output.open("REWRITE_Test10000.csv");
        string line;
        output << "page_id_from\tpage_id_to\n";
        while(getline(cin, line))
        {
            output << parseLine(line).first << "\t" << parseLine(line).second << "\n";
        }


    }

    void makePath(bool adjacencyList, int id_from, int id_to)
    {
        if (adjacencyList) {
            cout << "USING ADJACENCY LIST: \n";
            cout << "FROM: " << id_from << " "<< "TO: " << id_to << endl;
            listShortestDistance(adjList, id_from, id_to);
        }
        /*else {
            cout << "USING ADJACENCY MATRIX: \n";
            cout << "FROM: " << id_from << " "<< "TO: " << id_to << endl;
            matrixShortestDistance(adjMatrix, id_from, id_to);
        }*/
        else {
            cout << "USING EDGE LIST: \n";
            cout << "FROM: " << id_from << " "<< "TO: " << id_to << endl;
            //printNeighbors(edgeList, 336);
            edgeListShortestDistance(edgeList, id_from, id_to);
        }
    }

    ~Wiki()
    {
        cin.close();
    }
private:
    ifstream cin;
    ofstream output;

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
        /*if (out.size() < 3) //some entries in the csv file are broken, this skips over those
        {
            //cout << "busted" << endl;
            return make_pair(0, 0);
        }*/

        //cout << out[0] << " " << out[1] << endl;
        //return make_pair(stoi(out[0]), stoi(out[2]));
        return make_pair(stoi(out[0]), stoi(out[1]));
    }

    void makeEdges()
    {
        //adjMatrix = vector<vector<int>> (7000000, vector<int> (7000000,0));

        /*
         * Create the adjacency list & adjacency matrix
         * Every edge can be represented as a pair, from -> to
         * Parse each line and create a vector of a bunch of pairs
         * Then push into the adjacency list
         */
        string line;
        vector<pair<int, int>> edges;

        while(getline(cin, line))
        {

            edges.push_back(parseLine(line));
            //pair<int, int> pairs = parseLine(line);
            //cout << pairs.first << " " << pairs.second << endl;
        }

        adjList.resize(edges.size());
        adjMatrix.resize(edges.size());
        edgeList.resize(edges.size());
        for (int i = 0; i < edges.size(); i++)
        {
            //cout << edges[i].first << " " << edges[i].second << endl;

            adjList[edges[i].first].push_back(edges[i].second);
            //adjMatrix[edges[i].first][edges[i].second] = 1;
            edgeList.push_back(edges[i]);

        }
        //cout << "hey" << endl;

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

    vector<int> neighborsEdgeList(vector<pair<int, int>> edgeList, int id)
    {
        vector<int> neighbors;
        for (int i = 0; i < edgeList.size(); i++)
        {
            if (edgeList[i].first == id)
            {
                neighbors.push_back(edgeList[i].second);
            }
        }
        return neighbors;
    }

    void printNeighbors(vector<pair<int, int>> edgeList, int id)
    {
        vector<int> neighbors = neighborsEdgeList(edgeList, id);
        for (auto a : neighbors)
        {
            cout << a << endl;
        }
    }

    bool edgeListBFS(vector<pair<int, int>> &edgeList, int src, int dest, vector<int> &pred)
    {
        queue <int> q;
        vector<bool> visited;
        visited.resize(7000000);

        for (int i = 0; i < edgeList.size(); i++)
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
            vector<int> neighbors = neighborsEdgeList(edgeList, u);

            for (int i = 0; i < neighbors.size(); i++)
            {

                if (!visited[neighbors[i]])
                {
                    //cout << neighbors[i] << endl;
                    visited[neighbors[i]] = true;

                    pred[neighbors[i]] = u;

                    q.push(neighbors[i]);
                    if (neighbors[i] == dest)
                    {
                        return true;
                    }

                }

            }
            //cout << "HEY" << endl;
        }
        return false;
    }
    void edgeListShortestDistance(vector<pair<int, int>> edgeList, int src, int dest)
    {

        vector<int> pred;
        pred.resize(7000000);

        if (!edgeListBFS(edgeList, src, dest, pred))
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

        cout << endl << "Calculate shortest path using edgeList and BFS" << endl;
        cout << "Shortest path length: " << path.size() << " (" << path.size()-1 << " clicks)" << endl;
        cout << "Path is: ";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            cout << path[i] << " ";
        }


    }

    void listDFSHelper(vector<vector<int>> &adjList, int &v, vector<bool> &visited)
    {

        visited[v] = true;
        cout << v << " ";
        for (int i = 0; i < adjList[v].size(); i++)
        {
            int neighbor = adjList[v][i];
            if (visited[neighbor] == false)
            {
                listDFSHelper(adjList, neighbor, visited);
            }
        }
    }

    void listDFS(vector<vector<int>> &adjList, int src, int dest)
    {

    }

    bool listBFS(vector<vector<int>> &adjList, int src, int dest, vector<int> &pred)
    {

        queue<int> q;

        vector<bool> visited;
        visited.resize(7000000);


        for (int i = 0; i < adjList.size(); i++)
        {
            visited.at(i) = false;
            pred[i] = -1;
        }

        visited[src] = true;
        q.push(src);

        while (!q.empty())
        {
            //cout << q.size() << endl;
            int u = q.front();
            q.pop();

            for (int i = 0; i < adjList[u].size(); i++)
            {
                //cout << adjList[u][i] << endl;
                //cout << visited[adjList[u][i]] << endl;
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
            //cout << "HEY" << endl;

        }
        return false;
    }

    void listShortestDistance(vector<vector<int>> adjList, int src, int dest)
    {

        vector<int> pred;
        pred.resize(7000000);

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
        visited.resize(7000000);


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
        pred.resize(7000000);
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

void printer2(Wiki const& wiki)
{
    //this is a function to visualize the adjacency list
    for (int i = 0; i < wiki.adjMatrix.size(); i++)
    {
        if (wiki.adjMatrix[i].size() == 0) //there are some ids that aren't used
            continue;

        cout << i << " -> ";
        for (int v : wiki.adjMatrix[i])
        {
            cout << v << " ";
        }
        cout << endl;
    }
}

int main() {
    //input the name of the csv file here
    auto start = chrono::high_resolution_clock::now();
    string file = "Full_Graph_Cut.csv";
    Wiki wiki(file);
    wiki.run();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    printer2(wiki);
    cout << "Time to create graph: " << duration.count() << " seconds." << endl;
    wiki.makePath(false, 12, 752);
    return 0;
}
