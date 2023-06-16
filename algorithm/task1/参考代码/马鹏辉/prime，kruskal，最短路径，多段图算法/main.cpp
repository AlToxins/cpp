#include <iostream>
#include "graphlist.h"
#include <string>

void prime();

int main()
{
    GraphList<std::string> list;

    /*
     *
     *
     *      |-------------|(4)-----|(9)
     *      |             |        |
     *      |             |        |
     *      A-----B(3)----C(2)-----D(7)------E(1)
     *            |       |------------------|(11)
     *            |--------------------------|(9)
     */

    list.addNode("A");list.addNode("C");
    list.addNode("B");list.addNode("D");
    list.addNode("E");
    list.addEdge("A","B",3);list.addEdge("B","A",3);
    list.addEdge("A","C",4);list.addEdge("C","A",4);
    list.addEdge("A","D",9);list.addEdge("D","A",9);
    list.addEdge("B","C",2);list.addEdge("C","B",2);
    list.addEdge("B","E",9);list.addEdge("E","B",9);
    list.addEdge("C","D",7);list.addEdge("D","C",7);
    list.addEdge("C","E",11);list.addEdge("E","C",11);
    list.addEdge("D","E",1);list.addEdge("E","D",1);

    std::cout<<list<<std::endl;

    std::cout<<"prim"<<std::endl;
    GraphList<std::string> pr = prim(list);
    std::cout<<pr<<std::endl;

    std::cout<<"kruskal"<<std::endl;
    GraphList<std::string> kr = kruskal(list);
    std::cout<<kr<<std::endl;

    std::unordered_map<std::string,int> result = shortestPath(list,"C");
    for(auto m_it = result.cbegin();m_it!=result.cend();m_it++){
        std::cout<<m_it->first<<"("<<m_it->second<<")"<<std::endl;
    }
//多段图
    /*
     *|----C(5)----|(1)
     *|            |------E--------|(3)
     *|            |               |
     *A----B(3)----|(2)            |-----G
     *|                            |
     *|                            |
     *|----D(2)----------F(5)------|(2)
     *
     *
     */
    GraphList<std::string> list2;
    list2.addNode("A");
    list2.addNode("B");
    list2.addNode("C");
    list2.addNode("D");
    list2.addNode("E");
    list2.addNode("F");
    list2.addNode("G");
    list2.addEdge("A","B",3);
    list2.addEdge("A","C",5);
    list2.addEdge("A","D",2);
    list2.addEdge("B","E",2);
    list2.addEdge("C","E",1);
    list2.addEdge("D","F",5);
    list2.addEdge("E","G",3);
    list2.addEdge("F","G",2);

    int t = multistageGraph(list2,"A","G");
    std::cout<<t<<std::endl;
    t = multistageGraph(list2,"A","E");
    std::cout<<t<<std::endl;

    return 0;
}

