import numpy as np
from collections import defaultdict

class Graph:

    def __init__(self):
        self.graph = defaultdict(list)

    def addEdge(self, u, v):
        self.graph[u].append(v)

    def DFSs(self, v, visited):
        visited.append(v) #aktualny wierzcholek oznaczami jako odwiedzony
        print(v),         #i go wypisujemy

        for neighbour in self.graph[v]: #powtarzamy dla kazdego z sasiadow
            if neighbour not in visited:
                print("Krawędź:", v, "-", neighbour)
                self.DFSs(neighbour, visited)

    def DFS(self, v):
        visited = [] #zapisywanie odwiedzonych wierzcholkow

        self.DFSs(v, visited) #wywolanie funkcji rekurencyjnej

    def BFS(self, s):
        visited = [False] * (max(self.graph) + 1) #wszystkie jako nieodwiedzone

        queue = []
        edges = []

        queue.append(s)
        visited[s] = True #wywolany wezel oznaczamy jako dowiedzony i kolejkujemy go

        while queue:
            s = queue.pop(0) #zdejmujemy wezel z kolejki i wypisujemy go
            print(s)

            for i in self.graph[s]: #pobieramy wszystkie wierzcholki polaczone z aktualnym
                if visited[i] == False:  #jezeli byly nieodwiedzone to
                    queue.append(i)      #kolekujemy je
                    edges.append([s, i]) #zapisujemy krawedz
                    visited[i] = True    #oznaczamy jako odwiedzone

        for edge in edges: #wypisujemy wszystkie krawedzie
            print("Krawędź:", end=' ')
            print(f'{edge[0]} - {edge[1]}')


file = open("matrix.txt", "r")

graph = Graph()

n = int(file.readline())
matrix = np.zeros((n, n))
i = 0
j = 0
for line in file:
    for number in line:
        if number == '1':
            matrix[i][j] = 1
        j += 1
    j = 0
    i += 1

for i in range(n):
    for j in range(n):
        if matrix[i][j] == 1:
            graph.addEdge(i, j)

print("DFS:")
graph.DFS(1)
#print("----------------")
#print("BFS:")
#graph.BFS(0)
#print("----------------")
#print("Maicerz sąsiedztwa:")
#print(matrix)
#print("----------------")
#print("Lista sąsiedztwa:")
#print(graph.graph)

