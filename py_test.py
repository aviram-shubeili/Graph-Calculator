import graph as gw
g1 = gw.create()
g1 = gw.addVertex(g1, 'v1')
g1 = gw.addVertex(g1, 'v2')
g1 = gw.addVertex(g1, 'v3')
g1 = gw.addVertex(g1, 'v4')
g1 = gw.addEdge(g1, 'v1', 'v2')
g1 = gw.addEdge(g1, 'v1', 'v3')
g1 = gw.addEdge(g1, 'v2', 'v1')
null1 = gw.addEdge(g1, 'v1', 'v1')  # self loop
null1 = gw.addEdge(g1, 'v1', 'v2')  # edge already exists
print('printing g1:')
gw.disp(g1)
g2 = gw.create()
g2 = gw.addVertex(g2, 'u1')
g2 = gw.addVertex(g2, 'u2')
g2 = gw.addVertex(g2, 'u3')
g2 = gw.addVertex(g2, 'u4')
g2 = gw.addEdge(g2, 'u1', 'u2')
g2 = gw.addEdge(g2, 'u2', 'u1')
print('printing g2:')
gw.disp(g2)

print('addEdge not exist vertex1:')
null1 = gw.addEdge(g2, 'v1', 'u2')  # edge not exists
print('printing null1:')
gw.disp(null1)
print('addEdge not exist vertex2:')
null1 = gw.addEdge(g2, 'u1', 'v2')  # edge not exists
print('addEdge not exist vertex1 and 2:')
null1 = gw.addEdge(g2, 'v1', 'v2')  # edge not exists
print('addEdge to null:')
null1 = gw.addEdge(null1, 'v1', 'v2')  # null graph
print('addVertex to null:')
null1 = gw.addVertex(null1, 'u4')  # null graph
print('destroy null:')
gw.destroy(null1)  # null graph

# ************ operators ************

complement = gw.create()
united = gw.create()
intersect = gw.create()
diff = gw.create()
product = gw.create()

print('creating !g1:')
complement = gw.graphComplement(g1, complement)
print('printing !g1:')
gw.disp(complement)

print('creating g1+g2:')
united = gw.graphUnion(g1,g2,united)
print('printing g1+g2:')
gw.disp(united)

print('creating g1^g2:')
intersect = gw.graphIntersection(g1,g2,intersect)
print('printing g1^g2:')
gw.disp(intersect)

print('creating g1-g2:')
diff = gw.graphDifference(g1,g2,diff)
print('printing g1-g2:')
gw.disp(diff)

print('creating g1*g2:')
product = gw.graphProduct(g1,g2,product)
print('printing g1*g2:')
gw.disp(product)












