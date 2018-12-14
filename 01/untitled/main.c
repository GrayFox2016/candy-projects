#include <stdio.h>
#include "math.h"

// 第n层有m个节点，计算总节点的函数
int count_nodes(int n, int m) {
    // 计算第n层的节点数
    int layer_node_count = (int)pow(2, (n - 1));
    // 计算从根节点到第n层所有的节点数
    int total_layer_node_count = (int)(pow(2, (n)) - 1);

    // 加上n+1层的节点数
    return total_layer_node_count + (layer_node_count - m) * 2;
}

int main() {
    printf("total nodes: %d\n", count_nodes(7, 10));
    return 0;
}


