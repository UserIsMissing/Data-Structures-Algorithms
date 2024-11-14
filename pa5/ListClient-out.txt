
A = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
A.position() = 0
B = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
B.position() = 0
C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
C.position() = 10
D = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
D.position() = 10

A = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
A.position() = 10
B = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
B.position() = 10
C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
C.position() = 0
D = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
D.position() = 0

B: 10 9 8 7 6 5 4 
B.position() = 3

C: 1 2 3 4 5 6 7 
C.position() = 7

A==B is false
B==C is true
C==D is false
D==A is true

5
(1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
(1, 2, 3, 4, 7, 8, 9, 10)
4
1
(3, 4, 7, 8, 9, 10)
0
-1
6
-1
0

A = (10, 1, 9, 2, 8, 3, 7, 4, 6, 5, 5, 6, 4, 7, 3, 8, 2, 9, 1, 10)
15
A = (10, 1, 9, 2, 8, 3, 7, 4, 6, 5)
10

E==A is true

F = (10, 1, 9, 2, 8, 3, 7, 4, 6, 5, 3, 4, 7, 8, 9, 10)
length: 16
front: 10
back: 10
position: 0
peekNext: 10
10
peekNext: 1
1
peekNext: 9
9
peekNext: 2
2
peekNext: 8
8
peekNext: 3
3
peekNext: 7
7
F = (-1, 10, -2, 1, -3, 9, -4, 2, -5, 8, -6, 3, -7, 7, 4, 6, 5, 3, 4, 7, 8, 9, 10)

test exceptions: 
A = (10, 1, 9, 2, 8, 3, 7, 4, 6, 5)
List: peekPrev(): cursor at front
   continuing without interruption
List: movePrev(): cursor at front
   continuing without interruption
List: setBefore(): cursor at front
   continuing without interruption
List: eraseBefore(): cursor at front
   continuing without interruption
List: peekNext(): cursor at back
   continuing without interruption
List: moveNext(): cursor at back
   continuing without interruption
List: setAfter(): cursor at back
   continuing without interruption
List: eraseAfter(): cursor at back
   continuing without interruption
List: front(): empty list
   continuing without interruption
List: back(): empty list
   continuing without interruption

