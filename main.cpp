//
//  main.cpp
//  BreakingBad
//
//  Created by Stefán Hafsteinsson on 11/12/14.
//  Copyright (c) 2014 Stefán Hafsteinsson. All rights reserved.
//

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

vector <int> adj[100000];
vector<int> side(100000, -1);
//For vertexes that have no restrictions.
bool isInGraph[100000];
bool isBipartite = true;


struct Vertex
{
    int v;
    string item;
    
    Vertex(int vert, string itm)
    {
        v = vert;
        item = itm;
    }
};

int getVertex(vector<Vertex> v, string s)
{
    int vertex = 0;
    
    for(int i = 0; i <  v.size(); i++)
    {
        if(v[i].item == s)
        {
            vertex = v[i].v;
            break;
        }
    }
    
    return vertex;
}

void checkBipartite(int u)
{
    for(int i = 0; i < adj[u].size(); i++)
    {
        int v = adj[u][i];
        if(side[v] == -1)
        {
            side[v] = 1 - side[u];
            isInGraph[v] = true;
            checkBipartite(v);
        }
        else if(side[v] == side[u])
        {
            isBipartite = false;
        }
    }
}

int main(int argc, const char * argv[]) {
    
    int N, M;
    
    vector<Vertex> vertices;
    //For searcing purpose of vertexes number.
    map<string, int> items;
    
    scanf("%d", &N);
    
    //Get all items.
    for(int i = 0; i < N; i++)
    {
        string item;
        cin >> item;
        vertices.push_back(Vertex(i, item));
        items.insert(pair<string, int>(item, i));
    }
    
    scanf("%d", &M);
    //Set illegal items together.
    for(int i = 0; i < M; i++)
    {
        string first, second;
        cin >> first >> second;
        int v = items.find(first)->second;
        int w = items.find(second)->second;
        
        adj[v].push_back(w);
        adj[w].push_back(v);
    }
    
    //Check if graph is bipartite.
    for(int i = 0; i < N; i++)
    {
        if(side[i] == -1)
        {
            side[i] = 0;
            isInGraph[i] = true;
            checkBipartite(i);
        }
    }
    
    
    if(isBipartite)
    {
        string walter = "", jesse = "";
        for(int i = 0; i < N; i++)
        {
            if(side[i] == 0 || !isInGraph[i])
            {
                walter += vertices[i].item + " ";
            }
            else if(side[i] == 1)
            {
                jesse += vertices[i].item + " ";
            }
        }
        
        cout << walter << endl << jesse << endl;
    }
    else
    {
        cout << "impossible" << endl;
    }
    
    return 0;
}
