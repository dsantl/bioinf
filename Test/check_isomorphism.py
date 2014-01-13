#!/usr/bin/env python

import sys

EPS = 1e-5


class Tree:
    def __init__(self, edges):
        self.adj = {}
        for edge in edges:
            a, b, c = edge[0], edge[1], edge[2]
            self.add_edge(a, b, c)
            self.add_edge(b, a, c)

    def add_edge(self, a, b, c):
        if not a in self.adj:
            self.adj[a] = []
        self.adj[a].append((b, c))

    def hash_set(self):
        result = []
        for root in self.adj.keys():
            result.append(self.hash(root))
        return result

    def any_hash(self):
        return self.hash(self.adj.keys()[0])

    def hash(self, node, prev=None):
        h = []
        for edge in self.adj[node]:
            if edge[0] == prev:
                continue
            h.append('(' + self.hash(edge[0], node) + ',' + str(edge[1]) + ')')
        return '(' + ''.join(sorted(h)) + ')'


def get_weight_map(edges):
    weights = []
    for graph_id in [0, 1]:
        for edge in edges[graph_id]:
            weights.append(float(edge.split()[2]))
    weights = sorted(weights)
    weight_map = {}
    weight_id = 0
    for i in xrange(len(weights)):
        if i > 0 and weights[i] - weights[i - 1] >= EPS:
            weight_id += 1
        weight_map[weights[i]] = weight_id
    return weight_map


def normalize_weights(edges):
    weight_map = get_weight_map(edges)
    for tree_id in [0, 1]:
        for i in xrange(len(edges[tree_id])):
            a, b, c = edges[tree_id][i].split()
            c = weight_map[float(c)]
            edges[tree_id][i] = (int(a), int(b), c)


def main():
    edges = []
    edges.append(open(sys.argv[1]).readlines())
    edges.append(open(sys.argv[2]).readlines())
    normalize_weights(edges)
    print int(Tree(edges[0]).any_hash() in Tree(edges[1]).hash_set())


if __name__ == '__main__':
    main()
