#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// 定义图的邻接表
vector<vector<int>> graph = {
    {},         // 0
    {2, 3},     // 1
    {1, 4, 5},  // 2
    {1, 5},     // 3
    {2, 5},     // 4
    {2, 3, 4}   // 5
};

// 栈的定义
stack<int> st;

// 记录每个节点是否被访问过
vector<bool> visited(graph.size(), false);

// DFS函数
// 用栈来实现DFS，想要得到返回路径: 方法1. 标记每个节点是否被访问过，且每次只压入一次栈，类比递归实现(不适用于有环的图)
// 方法2. 用一个vector记录路径，每次出栈时，将路径记录到对应步数的vector中(可能是新增或覆盖)，最后输出vector(压栈时需要记录步数)
void dfs(int start, int target) {
    st.push(start);  // 将起始节点加入栈中
    visited[start] = true;  // 标记起始节点为已访问

    while (!st.empty()) {
        int curr = st.top();  // 取出栈顶元素
        st.pop();

        // 遍历当前节点的所有邻居节点
        for (int neighbor : graph[curr]) {
            if (!visited[neighbor]) {
                st.push(curr);  // 将当前节点重新压入栈中
                visited[neighbor] = true;  // 标记邻居节点为已访问
                if (neighbor == target) {  // 如果找到了目标节点，则输出路径
                    cout << "Path: ";
                    cout << neighbor ;
                    while (!st.empty()) {
                        cout << "<-" << st.top();
                        st.pop();
                    }
                    cout << endl;
                    return;
                }
                st.push(neighbor);  // 将邻居节点加入栈中，继续深度遍历
                break;
            }
        }
    }

    cout << "No path found." << endl;  // 如果没有找到目标节点，则输出无路径信息
}

int main() {
    dfs(1, 5);  // 从节点1开始搜索，搜索目标为节点5
    return 0;
}
