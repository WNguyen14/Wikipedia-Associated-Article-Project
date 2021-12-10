// Wikipedia Associated Article Project
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
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
    unordered_map<int, unordered_map<int, int>> adjMatrix;
    vector<pair<int, int>> edgeList;
    vector<string> path;

    Wiki(string fileName)
    {

        //FullGraph.csv size = 163380007
        adjList.resize(70000000);
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
        cout << "Rewriting.." << endl;
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
            path = convertIdToName(listShortestDistance(adjList, id_from, id_to));
            //listShortestDistance(adjList, id_from, id_to);
        }
        /*else {
            cout << "USING ADJACENCY MATRIX: \n";
            cout << "FROM: " << id_from << " "<< "TO: " << id_to << endl;
            matrixShortestDistance(adjMatrix, id_from, id_to);
        }*/
        else {
            cout << "USING ADJACENCY MATRIX: \n";
            cout << "FROM: " << id_from << " "<< "TO: " << id_to << endl;
            //printNeighbors(edgeList, 336);
            path = convertIdToName(matrixShortestDistance(adjMatrix, id_from, id_to));
            //matrixShortestDistance(adjMatrix, id_from, id_to);
        }
    }

    vector<string> getPath()
    {
        return path;
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
        //edgeList.resize(edges.size());
        //unordered_map<int, unordered_map<int, int>> adjMatrix;
        for (int i = 0; i < edges.size(); i++)
        {
            //cout << edges[i].first << " " << edges[i].second << endl;
            int a = edges[i].first;
            int b = edges[i].second;

            adjList[edges[i].first].push_back(edges[i].second);
            adjMatrix[a][b] = 1;
            //adjMatrix[edges[i].first][edges[i].second] = 1;
            //edgeList.push_back(edges[i]);

        }
        //cout << "hey" << endl;

    }

    bool listBFS(vector<vector<int>> &adjList, int src, int dest, vector<int> &pred)
    {

        queue<int> q;

        vector<bool> visited;
        visited.resize(70000000);


        for (int i = 0; i < adjList.size(); i++)
        {
            visited.push_back(false);
            pred[i] = -1;
        }

        visited[src] = true;
        q.push(src);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            //cout << adjList[u].size();

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

    vector<int> listShortestDistance(vector<vector<int>> &adjList, int src, int dest)
    {
        vector<int> output;
        output.push_back(0);
        vector<int> pred;
        pred.resize(70000000);

        if (!listBFS(adjList, src, dest, pred))
        {
            cout << "Not connected" << endl;
            return output;
            //return;
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
            //cout << path[i] << " ";
            output.push_back(path[i]);
        }
        //cout << "\n";
        //return;
        return output;

    }

    bool matrixBFS(unordered_map<int, unordered_map<int, int>> &adjMatrix, int src, int dest, unordered_map<int, int> &pred)
    {

        queue<int> q;

        unordered_map<int, bool> visited;
        int size = adjMatrix.size();

        for (auto it =adjMatrix.begin(); it!= adjMatrix.end(); ++it)
        {
            visited[it->first] = false;
            pred[it->first] = -1;
        }

        visited[src] = true;
        q.push(src);

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (auto it =adjMatrix[u].begin(); it!= adjMatrix[u].end(); ++it)
            {
                int x = it->first;
                if (!visited[it->first] && adjMatrix[u][it->first] ==1)
                {

                    visited[it->first] = true;
                    pred[it->first] = u;
                    q.push(it->first);

                    if (it->first == dest)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    vector<int> matrixShortestDistance(unordered_map<int, unordered_map<int, int>> &adjMatrix, int src, int dest)
    {
        unordered_map<int, int> pred;
        vector<int> output;
        output.push_back(0);
        if (!matrixBFS(adjMatrix, src, dest, pred))
        {
            cout << "Not connected" << endl;
            return output;
        }
        vector<int> path;
        int crawl = dest;
        path.push_back(crawl);
        while(pred[crawl] != -1)
        {
            path.push_back(pred[crawl]);
            crawl = pred[crawl];
        }
        cout << endl << "Calculate shortest path using adjMatrix and BFS" << endl;
        cout << "Shortest path length: " << path.size() << " (" << path.size()-1 << " clicks)" << endl;
        cout << "Path is: ";
        for (int i = path.size() - 1; i >= 0; i--)
        {
            //cout << path[i] << " ";
            output.push_back(path[i]);
        }
        return output;

    }


    string search()
    {
        string s = "<title>";
        ifstream inFile;
        string line;
        inFile.open("result.html");
        size_t pos;
        while(inFile.good())
        {
            getline(inFile, line);
            pos = line.find(s);
            if(pos!=string::npos)
                return line;
        }
        return " ";
    }

    string remover(string s, string remove)
    {
        auto n = s.find(remove);
        if(n != std::string::npos)
            s.erase(n, remove.length());
        return s;

    }

    vector<string> convertIdToName(vector<int> ids)
    {
        //cout << "CONVERTING" << endl;
        vector<string> output;
        for (int i = 0; i < ids.size(); i++)
        {
            //cout << ids[i] << " " << endl;
            string command = "wget --output-document=result.html https://en.wikipedia.org/?curid=";
            command += to_string(ids[i]);
            command += " >nul 2>nul";
            system(command.c_str());
            string title = search();
            //title is in format: <title> TITLE - Wikipedia </title>
            title = remover(title, "<title>");
            title = remover(title, "- Wikipedia</title>");
            output.push_back(title);
        }
        return output;
    }

};

int main() {

    //input the name of the csv file here
    auto start = chrono::high_resolution_clock::now();
    string file = "900000_Cut.csv";
    Wiki wiki(file);
    wiki.run();
    //wiki.rewrite();
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(stop - start);
    cout << "Time to create graph: " << duration.count() << " seconds.\n" << endl;
    wiki.makePath(true, 12, 752);
    //cout << "\n" << endl;
    vector<string> path = wiki.getPath();
    for (int i = 1; i < path.size(); i++)
    {
        cout << path[i] << " -> " ;
    }
    cout << "\n" << endl;
    wiki.makePath(false, 4621, 4620);
    path = wiki.getPath();
    for (int i = 1; i < path.size(); i++)
    {
        cout << path[i] << " -> " ;
    }
    //wiki.makePath(false, 16555375, 3526);
    /*
    path = wiki.getPath();
    for (auto s : path)
    {
        cout << s << " ";
    }*/

    return 0;
}
