#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>

//创建一个图的边
//所以我们首先需要创建一个点
using std::cout;


template<typename T>class Edge
{
    public:
        Edge(T v, int value)
        : _v(v), _edgeValue(value){}

    public:
        T _v;
        int _edgeValue;  //边权重 

    public:
        inline bool operator<(const Edge& e) const {return _v < e._v;}
        inline bool operator==(const Edge& e) const {return _v == e._v;}
            
        // unsigned int vertexNum(void) const {return (_v[1] - '0') - 1;}
        unsigned int vertexNum(void) const {return std::stoi(_v.substr(1)) - 1;}

};

template<typename T>class Graph
{
    public:
        Graph() = default;
        // Graph() = default;  //构造
        std::map<T, std::set<Edge<T>>> adj;

        //判断邻接表中是否有
        inline bool isContain(const T& vertex)
        {
            bool result = adj.find(vertex) != adj.end();
            if(!result){cout << vertex << " is not exist! \n";}
            return result;
        }

        inline bool isAdjacent(const T& v1, const T& v2)
        {
            //判断当前图中 是否 v1 和 v2已经是邻接的
            //判断 两个 点是否是邻接的
            if(v1 == v2)
            {
                cout << v1 << " = " << v2 << "not allow!\n";
                return false;
            }
            if(isContain(v1) && isContain(v2))
            {
                // if(adj[v1].find())
            }
            return false;
        }

        void addVertex(const T& vertex)
        {
            if(!isContain(vertex))
            {
                cout << vertex << "added success\n";
                adj[vertex];
            }
            else
            {
                cout << vertex << " has existed \n";
            }
        }

        void addEdge(const T& vertex, Edge<T>& edge)
        {   
            //判断 vertex 是否存在
            if(isContain(vertex))
            {
                //判断 edge 中需要邻接的点是否存在
                if(!isContain(edge._v))
                {
                    //如果 边不存在的话就添加 创建一个点并且把 原点 和 这个点加入
                    addVertex(edge._v);
                }
                //判断是否邻接
                // if(!isAdjacent())
            }
        }
        //打印 现有 的图
        void show(void)
        {
            cout << "show graph begin:\n";
            for(auto& vertex : adj)
            {
                cout << "-------------------------\n";
                for(auto& edge : adj[vertex.first])
                {
                    cout << vertex.first <<"->" << edge._v 
                         << " , value:"  << edge._edgeValue
                         << "\n";
                }
                cout << "-------------------------\n";
            }
            cout << "show graph end\n";
        }

};

template<>
class Graph<std::string>
{
    public:
        Graph() = delete;
        //创建 n 个图顶点
        Graph(int vertexNum);
        //将v1和v2连接，若已经连接则将权值刷新, 并可选是否是双向连接
        bool connect(const std::string& v1, const std::string& v2, int edgeVal, bool doubleConnect=true);    
        //邻接表中是否存在该节点
        inline bool isContain(const std::string& v1);
        int findShortestPath(void);
        void findPath(int index);

    public:
        //图结构， "a" Edge = "b",10
        std::map<std::string, std::set<Edge<std::string>>> adj;

    private:
        int _vertexNum = 0;
        std::vector<int> _dis;
        std::vector<std::string> _preNode;
};

Graph<std::string>::Graph(int vertexNum)
{
    _vertexNum = vertexNum;
    for(int i = 0;i < vertexNum;i++)
    {
        adj[std::string("v" + std::to_string(i+1))];
    }
}

bool Graph<std::string>::connect(const std::string& v1, const std::string& v2, int edgeVal, bool doubleConnect)
{
    //首先判断 v1 和 v2 是否存在
    if(isContain(v1))
    {
        if(isContain(v2))
        {
            //将 v1 连接 上 v2
            auto i = adj[v1].find(Edge(v2, edgeVal));
            if(i != adj[v1].end())
            {
                //之前存在连接，需要先擦除再连接
                adj[v1].erase(Edge(v2, edgeVal));
            }
            adj[v1].insert(Edge(v2, edgeVal));
            
            if(doubleConnect)
            {
                //v2 连接上 v1
                auto i = adj[v2].find(Edge(v1, edgeVal));
                if(i != adj[v2].end())
                {
                    //之前存在连接，需要先擦除再连接
                    adj[v2].erase(Edge(v1, edgeVal));
                }
                adj[v2].insert(Edge(v1, edgeVal));
            }
            return true;
        }
    }
    return false;
}

bool Graph<std::string>::isContain(const std::string& vertex)
{
    bool result = adj.find(vertex) != adj.end();
    if(!result) std::cout << vertex << " is not exist\r";
    return result;
}

int Graph<std::string>::findShortestPath(void)
{
    std::vector<int>            dis(_vertexNum, INT_MAX);
    std::vector<bool>           checkPoint(_vertexNum, false);
    std::vector<std::string>    preNode(_vertexNum, "");
    dis[0] = 0;
    checkPoint[0] = true;
    std::string startPoint = "v1";
    std::string currentPoint(startPoint);
    int currentPointIndex = 0;
    
    while(1)
    {
        //更新当前锁定节点的路径
        for(auto& edge : adj[currentPoint])
        {
            if(dis[currentPointIndex] + edge._edgeValue < dis[edge.vertexNum()])
            {
                dis[edge.vertexNum()] = dis[currentPointIndex] + edge._edgeValue;
                preNode[edge.vertexNum()] = currentPoint;
            }
        }


        //找出下一个要被更新的节点
        int tempMinDis   = INT_MAX;
        int tempMinIndex = 0;
        for(int i = 1;i < dis.size();i++)
        {
            if(tempMinDis >= dis[i] && checkPoint[i] != true)
            {
                tempMinDis = dis[i];
                tempMinIndex = i;
            }
        }
        
        //记录路径
        checkPoint[tempMinIndex] = true;
        currentPointIndex = tempMinIndex;
        currentPoint = "v" + std::to_string(tempMinIndex + 1);

        //终结条件
        if(checkPoint[dis.size() - 1] == true) break;
    }

    _dis = dis;
    _preNode = preNode;

    return _dis[_vertexNum - 1];
}

void Graph<std::string>::findPath(int index)
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
    std::string preNode(_preNode[index]);
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
        // int perNodeIndex = (preNode[1] - '0') - 1;  
        int perNodeIndex = std::stoi(preNode.substr(1)) - 1;

        preNode = _preNode[perNodeIndex];
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
