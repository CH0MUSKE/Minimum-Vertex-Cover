# Exact and Heuristic Algorithms for Minimum Vertex Cover

[![Language](https://img.shields.io/badge/Language-C-00599C?logo=c&logoColor=white)](https://en.cppreference.com/)
[![Focus](https://img.shields.io/badge/Focus-Combinatorial%20Optimization-blue)](#)
[![Complexity](https://img.shields.io/badge/Complexity-Branch%20%26%20Bound-green)](#)

> Implementation, theoretical bounds derivation, and empirical scalability analysis of exact **Branch & Bound** routines and approximation algorithms for the NP-hard **Minimum Vertex Cover** (MVC) problem.

📄 **[Read the Full Technical Report (PDF)](./report.pdf)**

---

## 📌 Overview

The **Vertex Cover** problem aims to identify a subset of vertices $C \subseteq V$ of minimal cardinality such that every edge in $E$ is incident to at least one vertex in $C$.

This repository evaluates exact exponential search strategies and polynomial-time approximations implemented from scratch in **C**. Using C provides fine-grained memory management and eliminates high-level language overhead, enabling accurate benchmarking across dense and sparse random graphs $G(n, p)$.

---

## 🔬 Algorithms & Pruning Strategies

### 1. Approximation & Baseline Heuristics
* **Greedy Heuristic (Max-Degree):** Iteratively selects the vertex with the maximum current degree. *The report proves this greedy strategy is not 1-approximate via an explicit counterexample ($\vert{}C\vert{}=10$ vs. optimal $\vert{}C^*\vert{}=9$).*
* **Maximal Matching 2-Approximation:** Computes an edge-disjoint matching $M$ to derive valid covers satisfying $\vert{}C\vert{} \ge \vert{}M\vert{}$.

### 2. Theoretical Lower Bounds for Pruning
To constrain the Branch & Bound search space, three admissible lower bounds $b(G)$ were derived and implemented:
* **Degree Bound ($b_1$):**
  $$\vert{}C\vert{} \ge \left\lceil \frac{m}{\Delta} \right\rceil$$
  where $m = \vert{}E\vert{}$ and $\Delta$ is the maximum graph degree.
* **Matching Bound ($b_2$):**
  $$\vert{}C\vert{} \ge \vert{}M\vert{}$$
  where $M$ is an independent edge matching.
* **Quadratic Density Bound ($b_3$):** Derived from upper-bounding edge counts between $C$ and $V \setminus C$:
  $$\vert{}C\vert{} \ge \left\lceil \frac{(2n - 1) - \sqrt{(2n - 1)^2 - 8m}}{2} \right\rceil$$

### 3. Branch & Bound Pruning & Reductions
* **Standard Branching:** Binary choice on edge $(u, v)$ with pruning triggered whenever current depth $+$ lower bound $\ge$ current upper bound.
* **Neighborhood Reduction:** If $u \notin C$, then all neighbors $N(u)$ must belong to $C$, eliminating $1 + \vert{}N(u)\vert{}$ vertices along that branch.
* **Degree-1 Vertex Elimination:** Theoretical guarantee that if $\deg(u) = 1$ with $(u, v) \in E$, there exists an optimal cover containing $v$ rather than $u$, allowing immediate reduction.
* **Maximum Degree Branching (`degMax`):** Priority branching on the vertex with the highest residual degree.

---

## 📊 Empirical Benchmarks & Performance Analysis

Benchmarked over Erdős–Rényi random graphs $G(n, p)$ across edge probabilities $p \in \{0.2, 0.5, 0.8, n^{-1/2}\}$:

| Algorithm Variant | Scalability Limit ($T < 1\text{s}$) | Pruning Effectiveness & Inferences |
| :--- | :---: | :--- |
| **Simple Branching** | $n \approx 18$ | Explores $\mathcal{O}(2^m)$ nodes; severely crippled by edge density. |
| **Standard B&B** | $n \approx 18$ | Passive bounds alone fail to trim the combinatorial explosion. |
| **B&B + Neighborhood Reduction** | $n \approx 60$ | Rapidly eliminates entire neighborhoods when $u \notin C$. |
| **B&B + `degMax`** | $n \approx 70$ | Pivoting on high-degree nodes triggers aggressive edge clearance. |
| **B&B + `degMax` + Deg-1 Reduction** | **$n > 100$** | **Sub-0.25s execution on $n=70$**; scales reliably beyond 100 vertices. |

### Density Inversion Dynamic
* In **naïve branching**, higher edge density ($p=0.8$) slows execution due to the quadratic growth of edges ($2^m$).
* In **optimized B&B (with neighborhood pruning)**, higher density ($p=0.8$) **accelerates** execution: selecting $u \notin C$ instantly forces a large set $N(u)$ into the cover, clearing the residual graph much faster.

---

## 🛠️ Repository Structure

```text
├── src/
│   ├── graph.c              # Adjacency list/matrix structures and graph generators G(n, p)
│   ├── greedy.c             # Greedy max-degree heuristic
│   ├── matching.c           # Maximal matching 2-approximation
│   ├── bounds.c             # Lower bound formulations (b1, b2, b3)
│   ├── branch_and_bound.c   # B&B search with neighborhood and degree-1 reductions
│   └── main.c               # Benchmarking harnesses and latency measurement
├── scripts/
│   └── plot_benchmarks.py   # Visualization scripts for runtime and scaling curves
├── report.pdf               # Theoretical analysis and experimental synthesis
└── README.md
```
## 🚀 Build & Run

### Compilation
Compile with `-O3` optimization for accurate performance measurements:

```bash
gcc -O3 -Wall -Wextra src/*.c -o mvc_benchmark -lm
```
### Run Benchmarks
```bash
./mvc_benchmark --vertices 100 --prob 0.5 --runs 50
```
