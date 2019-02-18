#include <algorithm>
#include <iostream>
#include <vector>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif
#include <queue>
#include <algorithm>
class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  std::vector<int> level_nodes(n, 0);
  std::vector<Node> nodes;
  nodes.resize(n);
  int root_index;
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
	if (parent_index >= 0)
		nodes[child_index].setParent(&nodes[parent_index]);
	else
		root_index = child_index;
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
  //intialize the root_index as level 1
  level_nodes[root_index] = 1;
  int tmp_level;
  Node tmp_node;
  std::queue<Node> Q;
  Q.push(nodes[root_index]);
  while (!Q.empty()) {
	  tmp_node = Q.front();
	  Q.pop();
	  //childern will have one + parent level
	  tmp_level = level_nodes[tmp_node.key] + 1;
	  for (int index = 0; index < tmp_node.children.size(); index++) {
		  Node child = *(tmp_node.children[index]);
		  level_nodes[child.key] = tmp_level;
		  Q.push(child);
	  }
  }

  std::cout << *std::max_element(level_nodes.begin(),level_nodes.end()) << std::endl;
  //int maxHeight = 0;
  //for (int leaf_index = 0; leaf_index < n; leaf_index++) {
  //  int height = 0;
  //  for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
  //    height++;
  //  maxHeight = std::max(maxHeight, height);
  //}
  //  
  //std::cout << maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
