#ifndef GRAPHLIST_H
#define GRAPHLIST_H
#include <vector>
#include <map>
#include <queue>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <climits>


template <class T>
class Edge
{
    public:
        Edge(){}

        Edge(T src, T dest, int cost) : src(src), dest(dest), cost(cost){}

        Edge(const Edge &e){
            this->operator=(e);
        }

        Edge operator=(const Edge &e){
            src = e.src;
            dest = e.src;
            cost = e.cost;
            return *this;
        }


        friend std::ostream& operator<<(std::ostream &out, Edge<T> &e){
            out << e.src << " --------------> " << e.dest << " (" << e.cost << ")" << std::endl;
            return out;
        }
        friend bool operator ==(Edge<T> &lhs,Edge<T> &rhs){
            return (lhs.src==rhs.src&&lhs.dest==rhs.dest&&lhs.cost==rhs.cost);
        }
        friend bool operator !=(Edge<T> &lhs,Edge<T>&rhs){return !(lhs==rhs);}
        friend bool operator <(Edge<T> &lhs,Edge<T>&rhs){
            return (lhs.cost<rhs.cost);
        }
        friend bool operator >=(Edge<T> &lhs,Edge<T>&rhs){return !(lhs<rhs);}
        friend bool operator >(Edge<T> &lhs,Edge<T>&rhs){return (rhs<lhs);}
        friend bool operator <=(Edge<T> &lhs,Edge<T>&rhs){return !(lhs>rhs);}

        T src, dest;
        int cost;
};

//并查集，为了验证连通性
template <class T>
class UnionFindSet{
private:
    std::unordered_map<T, T> father;   // value表示父节点
    std::unordered_map<T, int> size;
public:
    UnionFindSet(std::vector<T> data){
        father.clear();
        size.clear();
        for(auto var : data){
            father.insert({var, var});
            size.insert({var, 1});
        }
    }

    T findRep(T node){
        while (father[node]!=node) {
            father[node] = father[father[node]];
            node = father[node];
        }
        //路径压缩
        return node;
    }

    bool connected(T a, T b){
        return findRep(a) == findRep(b);
    }

    void Union(T a, T b){
        T aRep = findRep(a);
        T bRep = findRep(b);
        if(aRep != bRep){
            int aSize = size[aRep];
            int bSize = size[bRep];
            if(aSize > bSize){
                father[bRep] = aRep;
                size[aRep] += size[bRep];
            }
            else{
                father[aRep] = bRep;
                size[bRep] += size[aRep];
            }
        }
    }
};

template <class NODE>
class GraphList
{
public:
    GraphList(){}

    bool addNode(NODE _node);
    bool addEdge(NODE from,NODE to,int _cost);
    bool addEdge(Edge<NODE>* edge);
    bool deleteNode(NODE _node);
    bool deleteEdge(NODE from,NODE to,int _cost);
    bool deleteEdge(Edge<NODE>*);

    bool isNodeAdded(NODE _node){
        auto search = graphList.find(_node);
        if(search == graphList.end())
            return false;
        else {
            return true;
        }
    }


    friend std::ostream& operator<<(std::ostream &out,GraphList<NODE> &gl){
        for(auto ve = gl.graphList.cbegin();ve!=gl.graphList.cend();ve++)
            for(auto ed :ve->second)
                out<<*ed;
        return out;
    }

    // prim 算法
    friend GraphList<NODE> prim(GraphList<NODE> &gl){
        GraphList<NODE> result;
        auto cmp = [](Edge<NODE> *left,Edge<NODE> *right){return left->cost>right->cost;};
        std::priority_queue<Edge<NODE>*,std::vector<Edge<NODE>*>,decltype (cmp)> pri_queue(cmp);

        //初始化优先队列
        auto m_it = gl.graphList.cbegin();
        if(m_it!=gl.graphList.cend()){
            result.addNode(m_it->first);
            for(auto ed:m_it->second)
                pri_queue.push(ed);
        }

            //添加新加入的节点
            //添加新加入节点与已有节点的边
            //讲新加入节点的边（去掉已经加入到的边）加入到优先队列
            //从优先队列选择下一个要加入的节点
        while ((result.graphList.size()<gl.graphList.size())&&(!pri_queue.empty())){
            if(!result.isNodeAdded(pri_queue.top()->dest)){//成功添加新节点
                auto t = pri_queue.top();
                pri_queue.pop();//弹出
                result.addNode(t->dest);//添加节点
                result.addEdge(t);//添加边
                for(auto ed:gl.graphList[t->dest]){
                    if(result.isNodeAdded(ed->dest))
                        continue;
                    pri_queue.push(ed);
                }
            }else {
                pri_queue.pop();
            }
        }
        return result;
    }

    //kruskal 算法
    friend GraphList<NODE> kruskal(GraphList<NODE> &gl){
        GraphList<NODE> result;
        auto cmp = [](Edge<NODE> *left,Edge<NODE> *right){return left->cost>right->cost;};
        std::priority_queue<Edge<NODE>*,std::vector<Edge<NODE>*>,decltype (cmp)> pri_queue(cmp);
        std::vector<NODE> nodeVec;
        //初始化
        for(auto m_it = gl.graphList.cbegin();m_it!=gl.graphList.cend();m_it++){
            nodeVec.push_back(m_it->first);
            for(auto ed:m_it->second)
                pri_queue.push(ed);
        }
        UnionFindSet<NODE> uset(nodeVec);
        while (!pri_queue.empty()) {
            auto t = pri_queue.top();
            auto u = t->src;
            auto v = t->dest;
            if(!uset.connected(u,v)){//不连通
                if(!result.isNodeAdded(u))    result.addNode(u);
                if(!result.isNodeAdded(v))    result.addNode(v);
                result.addEdge(t);
                uset.Union(u,v);//合并
            }
            pri_queue.pop();
        }
        return result;

    }


    //单源最短路径
    friend std::unordered_map<NODE,int> shortestPath(GraphList<NODE> &gl,NODE src){
        auto cmp = [](std::pair<NODE,int> left,std::pair<NODE,int> right){return left.second>right.second;};
        std::priority_queue<std::pair<NODE,int>,std::vector<std::pair<NODE,int>>,decltype(cmp)> pq(cmp);

        std::unordered_map<NODE,int> dist;
        for(auto m_it = gl.graphList.cbegin();m_it!=gl.graphList.cend();m_it++){
            dist.insert({m_it->first,INT_MAX});
        }
        pq.push(std::make_pair(src,0));
        dist[src] = 0;
        while (!pq.empty()) {
            auto u = pq.top().first;
            pq.pop();
            for(auto ed:gl.graphList[u]){
                auto v = ed->dest;
                auto cost = ed->cost;
                if(dist[v]>dist[u]+cost){
                    dist[v] = dist[u]+cost;
                    pq.push(std::make_pair(v,dist[v]));
                }
            }
        }
        return  dist;
    }

    //多段图
    friend int multistageGraph(GraphList<NODE> &gl,NODE from,NODE to){
        if(from == to ) return 0;
        int min = INT_MAX;
        for(auto ed:gl.vendList[to]){
            int temp = multistageGraph(gl,from,ed->src);//可以通过哈希存储来优化
            if(temp+ed->cost<min)
                min = temp+ed->cost;
        }
        return min;
    }

private:
    std::map<NODE,std::vector<Edge<NODE>*>> graphList;
    std::map<NODE,std::vector<Edge<NODE>*>> vendList;
};

template <class NODE>
bool GraphList<NODE>::addNode(NODE _node){
    auto search = graphList.find(_node);
    if(search == graphList.end()){
        std::vector<Edge<NODE>*> edges;
        graphList.insert(std::make_pair(_node,edges));
        vendList.insert(std::make_pair(_node,edges));
        return true;
    }else {
        std::cerr<<"The node "<<_node<<" is already added"<<std::endl;
        return false;
    }
}

template <class NODE>
bool GraphList<NODE>::addEdge(NODE from, NODE to, int _cost){
    auto search = graphList.find(from);
    if( search == graphList.end()){
        std::cerr<<"The node "<<from<<" is not added."<<std::endl;
        return false;
    }
    auto search2 = graphList.find(to);
    if(search2==graphList.end()){
        std::cerr<<"The node "<<to<<" is not added."<<std::endl;
        return false;
    }
    Edge<NODE>* e = new Edge<NODE>(from,to,_cost);
    search->second.push_back(e);
    Edge<NODE>* ve = new Edge<NODE>(from,to,_cost);
    vendList[to].push_back(ve);
    return true;

}

template <class NODE>
bool GraphList<NODE>::addEdge(Edge<NODE>* edge){
    return addEdge(edge->src,edge->dest,edge->cost);
}

template <class NODE>
bool GraphList<NODE>::deleteEdge(NODE from, NODE to,int _cost){
    auto search = graphList.find(from);
    if(search == graphList.end()){
        std::cerr<<"The edge ("<<from<<"------>"<<to<<") doesn't exist!"<<std::endl;
        return false;
    }else {
        Edge<NODE>* comp = new Edge<NODE>(from,to,_cost);
        for(auto edge = graphList[from].begin();edge!=graphList[from].end();edge++){
            if(comp == *edge){
                auto t = *edge;
                delete t;
                graphList[from].erase(edge);
            }
        }
        for(auto edge = vendList[to].begin();edge!=vendList[to].end();edge++){
            if(comp == *edge){
                auto t = *edge;
                delete t;
                vendList[to].erase(edge);
            }
        }
        delete comp;
        return true;
    }
}

template <class NODE>
bool GraphList<NODE>::deleteEdge(Edge<NODE>* edge){
    return deleteEdge(edge->src,edge->dest,edge->cost);
}

template <class NODE>
bool GraphList<NODE>::deleteNode(NODE _node){

    auto search = graphList.find(_node);
    if(search == graphList.end()){
        std::cerr<<"The node "<<_node<<"doesn't exist"<<std::endl;
        return false;
    }
    for(auto vedge :vendList[_node]){
        deleteEdge(vedge);
    }
    for(auto edge :graphList[_node]){
        deleteEdge(edge);
    }

    return true;

}


#endif // GRAPHMATRIX_H
