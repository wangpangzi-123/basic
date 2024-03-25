#include <iostream>
#include "graph.h"
#include <vector>
#include <stack>


using std::string;
using std::vector;
using std::cout;
using std::endl;



//找指定位置的 从 v1 -> index 的最短路径
void findPath(std::vector<std::string>& path, int index)
{
    if(index == 0)
    {
        std::cout << "v1 \n";
        return;
    }
    //使用栈作为答案最后去打印
    std::stack<std::string> ans;
    //装填需要打印的index
    ans.push(std::string("v" + std::to_string(index + 1)));
    
    //获取index的前一个的索引
    std::string preNode(path[index]);
    if(preNode == "")
    {
        std::cout << "current node can't arrival\n";
        return;
    }
    //如果没有找到起点就持续寻找
    while(preNode != "v1")
    {
        //加入前一个节点
        ans.push(preNode);
        //找到前一个节点的索引
        int perNodeIndex = (preNode[1] - '0') - 1;  
        //我们去
        preNode = path[perNodeIndex];
    }
    ans.push("v1");
    //去循环打印
    int pathLength = 0;
    while(!ans.empty())
    {
        if(pathLength != 0) std::cout << " -> ";
        std::cout << ans.top();
        ans.pop();
        pathLength++;
    }
    std::cout << "\n";
    std::cout << "path length: " << pathLength << '\n'; 
}



int main(int argc, char *argv[])
{

    
    // Graph<std::string> graph(6);

    // // std::set<Edge<std::string>> v1_edge;
    // // v1_edge.insert(Edge(string("v3"), 10));
    // // v1_edge.insert(Edge(string("v5"), 30));
    // // v1_edge.insert(Edge(string("v6"), 100));
    // // graph.adj["v1"] = v1_edge;
    // graph.connect("v1", "v3", 10);
    // graph.connect("v1", "v5", 30);
    // graph.connect("v1", "v6", 100);

    // // std::set<Edge<string>> v2_edge;
    // // v2_edge.insert(Edge(string("v3"), 5));
    // // graph.adj["v2"] = v2_edge;
    // graph.connect("v2", "v3", 5);


    // // std::set<Edge<string>> v3_edge;
    // // v3_edge.insert(Edge(string("v4"), 50));
    // // graph.adj["v3"] = v3_edge;
    // graph.connect("v3", "v4", 50);

    
    // // std::set<Edge<string>> v4_edge;
    // // v4_edge.insert(Edge(string("v6"), 10));
    // // graph.adj["v4"] = v4_edge;

    // graph.connect("v4", "v6", 10);
    // // std::set<Edge<string>> v5_edge;
    // // v5_edge.insert(Edge(string("v6"), 60));
    // // v5_edge.insert(Edge(string("v4"), 20));
    // // graph.adj["v5"] = v5_edge;
    // graph.connect("v5", "v6", 60);
    // graph.connect("v5", "v4", 20);
    // int res = graph.findShortestPath();

    // cout << res << std::endl;

    // graph.findPath(5);



    Graph<std::string> graph(11);


    graph.connect("v1", "v2", 2);
    graph.connect("v1", "v4", 3);
    
    graph.connect("v2", "v5", 3);
    graph.connect("v2", "v6", 1);
    graph.connect("v2", "v3", 1);

    graph.connect("v3", "v6", 2);
    graph.connect("v3", "v7", 3);
    graph.connect("v3", "v4", 3);
    
    graph.connect("v4", "v7", 5);

    graph.connect("v5", "v8", 5);
    graph.connect("v5", "v9", 4);
    graph.connect("v5", "v6", 1);


    graph.connect("v6", "v9",  3);
    graph.connect("v6", "v10", 4);
    graph.connect("v6", "v7",  1);

    graph.connect("v7", "v10", 6);

    graph.connect("v8", "v11", 3);
    graph.connect("v8", "v9",  1);

    graph.connect("v9", "v10", 1);

    graph.connect("v10", "v11", 2);


    int res = graph.findShortestPath();

    cout << res << std::endl;

    graph.findPath(10);






    // graph.show();
    // a.addVertex('a');

// const int nodeNum = 6;
//     //最后的类中应该提供一个 显示每个点的距离的功能
//     vector<int> dis(6, INT_MAX);
//     vector<bool> checkPoint(6, false);
//     vector<string> preNode(6, "");
//     dis[0] = 0;
//     checkPoint[0] = true;

//     string startPoint = "v1";
//     string currentPoint(startPoint);
//     int currentPointIndex = 0;

//     while(1)
//     {
//         //更新当前锁定节点的路径
//         for(auto& edge : graph.adj[currentPoint])
//         {
//             if(dis[currentPointIndex] + edge._edgeValue < dis[edge.vertexNum()])
//             {
//                 dis[edge.vertexNum()] = dis[currentPointIndex] + edge._edgeValue;
//                 preNode[edge.vertexNum()] = currentPoint;
//             }
//         }


//         //找出下一个要被更新的节点
//         int tempMinDis   = INT_MAX;
//         int tempMinIndex = 0;
//         for(int i = 1;i < dis.size();i++)
//         {
//             if(tempMinDis >= dis[i] && checkPoint[i] != true)
//             {
//                 tempMinDis = dis[i];
//                 tempMinIndex = i;
//             }
//         }
        
//         //记录路径
//         checkPoint[tempMinIndex] = true;
//         currentPointIndex = tempMinIndex;
//         currentPoint = "v" + std::to_string(tempMinIndex + 1);

//         //终结条件
//         if(checkPoint[dis.size() - 1] == true) break;
//     }

//     cout << dis[4] << "\n";
//     findPath(preNode, 4);
    cout << "------hm------" << endl;
    return 0;



    // std::map<char, std::set<Edge<char>>> adj;
    
    // // std::set<Edge<char>> s; 
    // // s.insert(Edge('b', 9));
    // // s.insert(Edge('c', 10));
    // adj['a'];
    // adj['a'].insert(Edge('b', 9));
    // // adj['a'].insert(Edge('b', 8));

    // // auto i = adj['a'].find(Edge('b', 9));
    // auto e = adj['a'].find(Edge('b', 8));
    // if(e != adj['a'].end())
    // {
    //     std::cout << "find \n";
    //     adj['a'].erase(Edge('b', 8));
    //     adj['a'].insert(Edge('b', 8));
    //     std::cout << e->_edgeValue;
    // }
    // if( (auto i = adj['a'].find(Edge('b', 9))) != adj['a'].end())
    // {
    //     std::cout << "find\n";
    // }

    // auto i = adj['a'].find(Edge('b', 9));
    // std::cout << i->_edgeValue;


    // adj['b'] = s;
    
    // std::set<Edge<char>> s1; 
    // s1.insert(Edge('d', 11));
    // s1.insert(Edge('e', 9));

    // adj['a'] = s1;

    // for(auto& ver : adj)
    // {
    //     std::cout << "ver:" <<ver.first << std::endl;
    //     for(auto& edge : adj[ver.first])
    //     {
    //         std::cout << "adj ver:" << edge._v << " " << "adj ver val:" << edge._edgeValue << '\n';
    //     }
    // }


    //******set 操作尝试********//

    // Edge<char> x('a',9);

    // std::set<Edge<char>> set;
    // set.insert(Edge('a',9));
    // set.insert(Edge('b',9));
    // if((set.find(x)) != set.end())
    // {
    //     cout << "ok";
    // }

    // //set打印
    // for(auto i = set.begin();i != set.end();i++)
    // {
    //     cout << i->_v << " " << i->_edgeValue << " " << '\n';
    // }
}