#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

class UnionFind {
private:
    int* parent;  
    int* rank;     
    int size;      

public:
    UnionFind(int n);
    ~UnionFind();

    int find(int x);
    void unionSets(int x, int y);
    bool connected(int x, int y);
};

#endif
