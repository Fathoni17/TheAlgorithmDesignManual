# Walking the Approximate Longest Path
> Hard (Success Rate: 73.30%)

### Problem
<p>Jenna is playing a computer game involving a large map with n cities numbered sequentially from 1 to n that are connected by m bidirectional roads. The game's objective is to travel to as many cities as possible without visiting any city more than once. The more cities the player visits, the more points they earn.

As Jenna's fellow student at Hackerland University, she asks you for help choosing an optimal path. Given the map, can you help her find a path that maximizes her score?

Note: She can start and end her path at any two distinct cities.</p>

### Input Sample
```
4 5         // n Cities, m Roads
3 1             // Road from City 3 to City 1
3 4
2 4
2 3
4 1
```

### Output
```
4
1 4 2 3
```
> Note: The second line is the path, but it is open solution, 1 3 2 4 also accepted

## Scoring Point
> (d/n)^2 * 100%
> @ Test Case max 1.0 (with 21 Test Cest, Max Score 70)

### Result
1. Failed. -> Heuristic Methods, From fewest neighbor to the every first input edge.
2. Accepted (Score: 57.58) -> Using boolean for visited cities, and always looking forward to fewest neighbor city. (DFS)
![Submition](img/submit_1.png)
3. Accepted (Score: 56.53) -> Using Djikstra Algoritm with uniform negatif edge, and get the minimum distance.
![Submition 2](img/submit_2.png)
