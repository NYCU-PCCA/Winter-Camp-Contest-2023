slide mode: https://hackmd.io/@iris2617/2023pcca_editorial

# NYCU PCCA

## Winter Camp Contest 2023<br>題解

---

## 封板前解題隊伍數量

----

```vega
{
  "data": {
    "values": [
      {"Problem":"A", "group": "封板前", "solve":44},
      {"Problem":"B", "group": "封板前", "solve":24},
      {"Problem":"C", "group": "封板前", "solve":1},
      {"Problem":"D", "group": "封板前", "solve":31},
      {"Problem":"E", "group": "封板前", "solve":21},
      {"Problem":"F", "group": "封板前", "solve":1},
      {"Problem":"G", "group": "封板前", "solve":9},
      {"Problem":"H", "group": "封板前", "solve":4},
      {"Problem":"I", "group": "封板前", "solve":3},
      {"Problem":"J", "group": "封板前", "solve":2},
      {"Problem":"K", "group": "封板前", "solve":2},
      {"Problem":"L", "group": "封板前", "solve":0},
      {"Problem":"M", "group": "封板前", "solve":2},
      {"Problem":"N", "group": "封板前", "solve":34}
    ]
  },
   "layer": [
    {"mark": "bar"},
    {
      "mark": {
        "type": "text",
        "align": "center",
        "baseline": "middle",
        "dx": 0,
        "dy": -5
      },
      "encoding": {
        "text": {"field": "solve", "type": "quantitative", "format": ".2"}
      }
    }
  ],
  "encoding": {
    "x": {
        "field": "Problem",
        "sort": {
            "op": "sum",
            "field": "solve",
            "order": "descending"
        }
    },
    "y": {
        "field": "solve",
        "type": "quantitative"
    },
    "xOffset": {
        "field": "group"
    },
    "color": {
        "field": "group"
    }
  }
}
```

---

## A. ATCG

首殺 @ 2 min by <span style="color:yellow">List of worse teams:</span>
AC 隊伍數 @ 封版：44

----

### 題目大意

給定一個 5' 到 3' 的 DNA 序列，
求與之對應的 5' 到 3' DNA 序列。

----

### 題解

- 簽到題
- 將 `ATCG` 分別對應到 `TAGC` 之後倒著輸出就好

---

## N. Nancy's Numbers

首殺 @ 2 min by <span style="color:yellow">桃園金牌葉大大</span>
AC 隊伍數 @ 封版：34

----

### 題目大意

給定 $n$ 個整數，你每次可以把其中一個整數 $+1$，問你最少需要幾次操作才能讓所有數字都不一樣。

----

### 解法

- 我們從小到大決定最後每個數字要是什麼
- 改變後和改變前的大小關係不會改變，所以我們可以對 $a$ 排序。以下都假設 $a$ 已經排序

----

### 解法

- 可以注意到如果 $a_i$ 是 $x$，那下一個數字至少要是 $\max(a_i,x+1)$，而可以證明 $a_{i+1}$ 設定成  $\max(a_i,x+1)$ 一定最優。
- 從 $a_1$ 到 $a_n$ 一路決定 $a_i$ 的值即可。

---

## D. Duo of Magicians

首殺 @ 25 min by <span style="color:yellow">123</span>
AC 隊伍數 @ 封版：31

----

### 題目大意

- 給你一個 $1$ 到 $n$ 的排列
- 請輸出字典序遞增的一組交換順序 $(x_i, y_i)$
- 目標是將陣列排序好
- （$\sum n \le 10^6$、最多交換 $n$ 次）

----

### 暴力作法

- 我們直接進行 $n$ 次操作
- 固定第 $i$ 次交換的數字是 $(i, p_i)$
- 也就是每次找 $a_i, a_{i+1}, \ldots, a_n$ 最小的並交換到位置 $i$
- 你會想到什麼？

----

### 暴力作法

- Selection Sort !
- 用線段樹維護區間最小值
- 支援單點修改
- AC !

----

### 暴力作法

- 時間複雜度：$\mathcal{O}(n \lg n)$
- 還可以更好

----

### 更快的作法

- 如果在 $(i, a_i)$ 之間建一條邊

![](https://i.imgur.com/vNBXWNi.png =x200)

- 變成很多環
- 維護好環上的前一個跟後一個點
    - 環狀 linked list

----

### 更快的做法

```cpp=
void solve() { // 0-based
    int N; cin >> N;
    
    vector<int> A(N), inv(N);
    for (int i = 0; i < N; ++i) cin >> A[i], --A[i], inv[A[i]] = i;
    
    vector<pair<int, int>> ops;
    for (int i = 0; i < N; ++i) {
        if (A[i] == i) continue;
        ops.emplace_back(i, inv[i]);
        A[inv[i]] = A[i], inv[A[i]] = inv[i];
        A[i] = inv[i] = i;
    }
    
    cout << ops.size() << "\n";
    for (auto [x, y] : ops) cout << x+1 << " " << y+1 << "\n";
}
```

- $\mathcal{O}(n)!$

---

## B. Buying Mascots

首殺 @ 10 min by <span style="color:yellow">089487</span>
AC 隊伍數 @ 封版：24

----

#### 題目大意

- 總共有 $n$ 天，token 上限為 $m$
- 給定 $a$, $b$ 兩個序列，
  在第 $i$ 天可以選擇拿 $a_i$ 個 token
  (超過 $m$ 則為 $m$)
  或是拿 $b_i$ 個 token 換 $b_i$ 個 mascot
- 求最多可以拿到幾個 mascot。

----

### 題解

- 簡單 DP，設 $dp[i][j]$ 為第 $i$ 天時，持有 $j$ 個 token 的情況下能拿到的最多 mascot。
- 轉移式如下
```cpp=
if (j >= b[i]) dp[i+1][j-b[i]] = max(dp[i+1][j-b[i]], dp[i][j]+b[i]);
dp[i+1][min(m, j+a[i])] = max(dp[i+1][min(m, j+a[i])], dp[i][j]);
```
- 將最後一天持有任何 token 的情況取 max 就是答案。
- 因為每天都只有用到前一天的資訊，所以可以滾動 DP。
    - 總時間複雜度 $\mathcal{O}(nm)$
    - 空間複雜度 $\mathcal{O}(n+m)$。

---

## E. Exterior

首殺 @ 17 min by <span style="color:yellow">桃園金牌葉大大</span>
AC 隊伍數 @ 封版：21

----

### 題目大意

- 給一張 $n$ 個點 $m$ 條邊的圖
- 另外每個點有點權，
  可以花 $a_i+a_j$ 從 $i$ 傳送到 $j$，
- 求從 $1$ 到 $n$ 的最短路。

----

### 題解

- 另外建一個虛點
- 把他跟所有人連邊
- 連到 $i$ 的邊權是 $a_i$。

---

## G. Genetic Sequence Searching

首殺 @ 30 min by <span style="color:yellow">桃園金牌葉大大</span>
AC 隊伍數 @ 封版：9

----

### 題目大意

給定兩個字串 $s$ 和 $t$，請你在 $s$ 中找出 $t$ 所有 occurrence，最多可以差一個字元。

----

### 作法一：Z value

- 考慮使用 Z value 算出對於每個 $s$ 的後綴可以 match $t$ 的前綴多長。
- $s$ 和 $t$ 翻轉以後再做一次。
- 則可以發現，一個長度為 $|t|$ 的子字串和 $t$ 最多差一個字元若且唯若兩邊匹配長度總和 $\geq |t|-1$。
    - 可以注意到如果差一個字元總和會是 $|t|-1$，完整配對的話總和會是 $2|t|$，剩下情況都會 $<|t|-1$。

----

### 作法二：hash

- 對於每個 $i$，去二分搜第一個 $j$ 使得 $s_{i}\ldots s_{i+j-1}$ 和 $t_{1}\ldots t_{j}$ hash 值不一樣。
- 找到那個 $j$ 以後，嘗試把 $s_{i+j-1}$ 修改成 $t_j$ 後重新計算 hash 值，並且看和 $t$ 的是否相同。

----

### 小技巧

- hash 的解法要特別注意碰撞的問題。
- 使用隨機生成的 $x$，就算 mod 是一樣的也可以降低碰撞的機率。

---

## H. Heritage in the PCCA Kingdom

首殺 @ 53 min by <span style="color:yellow">List of worse teams:</span>
AC 隊伍數 @ 封版：4

----

### 題目大意

給定一個大三角形，大三角形被若干條邊分割成許多小三角形，一開始邊分成充能或者未充能。將一個符石放到一個小三角形裡，可以使小三角形的三條邊都變成充能狀態，詢問最少需使用多少符石才能使所有邊都成為充能狀態。

----

### 觀察

- 每條邊都連接兩個三角形。
- 三角形可以被分成正三角和倒三角兩類。
- 嘗試將三角形之間的關係轉換成一張圖。以三角形為點，未充能邊相鄰的兩個三角形之間建邊，可得一張二分圖。
- 選擇最少的點，使得所有邊都被至少一個點覆蓋。
  - 二分圖最小點覆蓋問題
  - 等價於二分圖最大匹配

----

![](https://i.imgur.com/1HIds3V.png)


----

### 作法

- 將圖建起來
  - $n$ 層小三角形，總共有 $n^2$ 個點。
  - 每個點的度數不超過 $3$ ，所以邊數有 $\mathcal{O}(n^2)$ 條。
- 可以用 Dinic 做：時間複雜度 $\mathcal{O}(\sqrt{V}E)$。
- 匈牙利演算法：時間複雜度 $\mathcal{O}(VE)$
	- 看起來很不合理，但是似乎有隊伍用匈牙利解掉了（？）

---

## I. Interval Cover

首殺 @ 128 min by <span style="color:yellow">hank55663</span>
AC 隊伍數 @ 封版：3

----

### 題目大意

給你一些數線上的區間，詢問需要增加多少個區間才能使整個數線被平均覆蓋，並支援動態修改。

----

### 觀察

- 可以將這些區間的覆蓋次數累加起來形成像這樣的圖
![](https://i.imgur.com/LhWENdh.png)

----

- 對於這樣的圖，答案會是下圖紅線部分的垂直線段總和的一半
![](https://i.imgur.com/ZuJl8SO.png)

----

### 作法

為了得到紅線的垂直部分的總和，我們需要區間最大值以及每個點的變化量的絕對值總和。區間最大值的部分可以使用線段樹，變化量的部分只需要用一個 array 去累加線段的變化量就可以了。

----

### code

```cpp=
#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1 << 20;
 
int cnt[maxn], val[maxn], tag[maxn];
int n, m, L, ans;
 
void pull(int x) {
    val[x] = max(val[x << 1], val[(x << 1) | 1]);
}
 
void push(int x) {
    if(tag[x]) {
        val[x << 1] += tag[x];
        tag[x << 1] += tag[x];
        val[(x << 1) | 1] += tag[x];
        tag[(x << 1) | 1] += tag[x];
        tag[x] = 0;
    }
}
 
void upd(int x, int L, int R, int l, int r, int v) {
    if(l <= L && R <= r) {
        tag[x] += v; val[x] += v;
        return;
    }
    push(x);
    int mid = (L + R) >> 1;
    if(l <= mid) upd(x << 1, L, mid, l, r, v);
    if(r > mid) upd((x << 1) | 1, mid + 1, R, l, r, v);
    pull(x);
}
 
void add(int l, int r) { // [l, r)
    ans -= abs(cnt[l]);
    ans -= abs(cnt[r]);
    cnt[l]++; cnt[r]--;
    ans += abs(cnt[l]);
    ans += abs(cnt[r]);
}
 
void Kill(int l, int r) { // [l, r)
    ans -= abs(cnt[l]);
    ans -= abs(cnt[r]);
    cnt[l]--; cnt[r]++;
    ans += abs(cnt[l]);
    ans += abs(cnt[r]);  
}
 
void solve() {
    ans = 0;
    memset(cnt, 0, sizeof(cnt));
    memset(val, 0, sizeof(val));
    memset(tag, 0, sizeof(tag));
    scanf("%d%d", &n, &L);
    for(int i = 0; i < n; i++) {
        int l, r; 
        scanf("%d %d", &l, &r);
        add(l, r); upd(1, 0, L - 1, l, r - 1, 1);
    }
    int op, l, r;
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d %d", &l, &r);
            add(l, r); upd(1, 0, L - 1, l, r - 1, 1);
        }
        else if(op == 2) {
            scanf("%d %d", &l, &r);
            Kill(l, r); upd(1, 0, L - 1, l, r - 1, -1);
        }
        else {
            int tmp = ans - abs(cnt[0]) + abs(cnt[0] - val[1]) - abs(cnt[L]) + abs(cnt[L] + val[1]);
            printf("%d\n", tmp / 2); 
        }
    }
}

```

---

## J. Jewelry Box

首殺 @ 94 min by <span style="color:yellow">hank55663</span>
AC 隊伍數 @ 封版：2

----

![](https://i.imgur.com/P9WGhyS.png)
要讓最多對的寶石相連

----

![](https://i.imgur.com/Vr65GrR.png)
是不是發現了什麼呢?

----

### 喵

```
AFF...FFC
BFF...FFD
AFF...FFC
  ..  .
  . . .
  .  ..
BFF...FFD
AFF...FFC
BFF...FFD
```

----

### 邊界 case

```
#.#     #F#
... =X> ...
#..     #FC
```

---

## K. $k$-restricted Induced Subgraphs

首殺 @ 75 min by <span style="color:yellow">kenorzkenorzkenorz</span>
AC 隊伍數 @ 封版：2

----

### 題目大意

給一張有點權的無向圖，求點權全距不超過 $k$，點數最多的連通子圖。

----

### 題解

相當於每次查詢只有點權在 $i$ 到 $i+k$ 之間的圖的最大連通塊，因此可以用上課教的時間線段樹來解決。

---

## M. Mini Factorization Challenge

首殺 @ 125 min by <span style="color:yellow">hank55663</span>
AC 隊伍數 @ 封版：2

----

### 題目大意

你本來有 $n$ 跟 $k = d(n)$，但是現在只剩下 $n'$ 跟 $k'$，而「$n$ 和 $n'$」以及「$k$ 和 $k'$」都只有恰一位數不同。
已知 $n$ 是若干 $\le 100$ 的正整數之乘積，請還原出最小可能的 $n$ 以及對應的 $k$。

- $n < 10^{100}$
- $k < 10^{18}$

----

### 題解

- 數字範圍很大，你有兩種選擇
    1. 手刻 C++ 大數
    2. python

----

### 題解

- 由小到大枚舉所有可能的 $n''$
    - 注意首位為 $0$、$n'' = n'$ 的 case
- 檢查 $n''$ 是否只包含 $\le 100$ 的因數
    - $\le 100$ 的質數有 $25$ 個
- 若可以則算出因數個數 $k'' = d(n'')$，進一步比較是否和 $k'$ **恰**一位數不同
- 如果是就代表 $(n'', k'') = (n, k)$

---

## C. Colorful Pictures

首殺 @ 160 min by <span style="color:yellow">hank55663</span>
AC 隊伍數 @ 封版：1

----

### 題目大意

給定一棵樹和一個 permutation $a = [1,2,\ldots,n]$。你可以做很多次操作，每次你可以選樹上的一條邊 $(u,v)$，交換 $a_u$ 和 $a_v$。每條邊最多只能被選一次。

問可以產生多少種 $a$。

----

### 這題的簡單版

- 如果要求要把樹上所有邊都選完，那答案會是多少？
- $\displaystyle\prod_{i=1}^{n} (d_i!)$，其中 $d_i$ 是第 $i$ 個點的度數

----

### 簡要證明

- 我們可以想像樹上每個節點上有一顆球，那每次的交換都是把球沿著邊走。可以觀察到每個球都有一個軌跡
- 如果把所有軌跡都畫在樹上，可以發現每條邊都被覆蓋到 $2$ 次
- 並且注意到整個 permutation 只有一個環（不然就會有邊沒被蓋到或者是蓋到兩次以上），所以沿著所有軌跡走會是一個樹的 DFS 順序

----

### 簡要證明

- 全部總共有 $\displaystyle\prod_{i=1}^{n} ((d_i-1)!)$ 種 DFS 順序，而環入出度都是 $1$，有 $d_i$ 種切法，所以總共有 $\displaystyle\prod_{i=1}^{n} (d_i!)$ 種 permutation

----

### 原題

- 考慮所有拔掉的邊的 edge set，那對於這個 set 來說的答案就是每個連通塊答案的乘積，其實就是每個點度數階乘的乘積。
- 同時可以發現不同 edge set 能排出的 permutation 一定不一樣，所以這題就相當於對於所有 $2^{n-1}$ 個 edge set，求出每個點度數階乘乘積的總和。

----

### 原題

- 把樹定根以後，考慮樹 DP
- 令 $dp_{i,0}$ 和 $dp_{i,1}$ 分別代表 $i$ 的子樹所有點的階乘乘積的總和，其中 $dp_{i,0}$ 代表不包含 $i$ 上面那條邊，$dp_{i,1}$ 代表包含。
- 轉移的部份，假設 $u$ 底下有 children set $S = \{v_1,\cdots,v_m\}$，則有以下轉移式：
    - $\scriptsize dp_{u,0} = \sum_{i=0}^{m} i! (\sum_{T \subseteq S, |T| = i} (\prod_{v \in T} dp_{v,1} \cdot \prod_{v \in S - T} dp_{v,0}))$
    - $\scriptsize dp_{u,1} = \sum_{i=0}^{m} (i+1)! (\sum_{T \subset S, |T| = i} (\prod_{v \in T} dp_{v,1} \cdot \prod_{v \in S - T} dp_{v,0}))$

----

### 原題

- 直接枚舉所有 subset 計算的話會太慢，但是可以注意到一件事：考慮多項式 $A = \prod_{i=1}^{m} (dp_{{v_i},1} x + dp_{{v_i},0})$，則 $A$ 的 $x^i$ 的係數會恰好是 $\sum_{T \subseteq S, |T| = i} (\prod_{v \in T} dp_{v,1} \cdot \prod_{v \in S - T} dp_{v,0})$。
- 考慮直接計算 $A$，藉此算出 $dp_{u,0}$ 和 $dp_{u,1}$。
- $A$ 可以使用分治 + NTT 在 $\mathcal{O}(n \log^2 n)$ 時間內算出。

---

## F. Formidable Team

首殺 @ 66 min by <span style="color:yellow">hank55663</span>
AC 隊伍數 @ 封版：1

----

### 題目大意
從 $n$ 人挑 $m$ 人出來，挑出來的每人各選一個不重複的能力，求最大總和及組合
- $1 \le n \le 1.5 \cdot 10^5$
- $1 \le m \le 60$
- $m \le n$
- $n \times m \le 2 \cdot 10^6$
- $1 \le a_{i,j} \le 10^9$

----

### 題解

可以先將題目敘述轉換成一個二分圖：一邊節點是每個成員，另一邊則是每個技能。
而圖上的帶權邊則是 $i$ 成員對 $j$ 技能的值

轉換成圖後，將成員連接至源點，技能連至匯點，就能發現題目是個「最小費用最大流」

![](https://i.imgur.com/UN4LcWf.png =320x200)


----

### 優化

接著可以發現因為一個隊伍只有 $m$ 人，
對於每個能力，可以保證前 $m$ 大的一定有人會被選擇；反之，如果有人的各項能力都在第 $m+1$ 之後，可以放心將他移除圖
這麼一來，我們能將左邊的節點的數量級從 $n$ 減少至 $O(m^2)$
![](https://i.imgur.com/uPKoWjS.png =320x200)

----

### 進一步優化

減少完節點的數量後，邊的數量級為$O(m^3)$
用 mcmf $O(VE)$，總複雜度還是高達 $O(m^5)$，會吃TLE，因此還需要進一步修剪：可以觀察出，並非所有的邊都會用上，對於每個能力值，只有前 $m$ 大的邊才有可能用到，將多餘的邊移除後，邊的數量級只剩下$O(m^2)$
![](https://i.imgur.com/6oLi3VX.png =320x200)

----

### 結論

根據上述的分析，將輸入的資料轉成對應的圖，得到 $O(m^2)$ 的邊數和 $O(m^2)$ 的節點數。套 mcmf 後就能得到正解了

----

將每個技能前 $m$ 大的挑出並建邊

```cpp=
// skill[i][j] : {a[j][i], i}
// s: 0, t: n + m + 1
// member_idx: 1 ~ n
// skill_idx: n + 1 ~ n + m
set<ll> members;
for (int i = 1; i <= m; i++) {
    nth_element(skill[i] + 1, skill[i] + m + 1, skill[i] + n + 1, greater<pll>());
    for (int j = 1; j <= m; j++) {
        members.insert(skill[i][j].second);
        mcmf.add_edge(skill[i][j].second, n + i, 1, C - skill[i][j].first);
    }
    mcmf.add_edge(n + i, t, 1, 0); // skills -> t
}
for(auto member : members){
    mcmf.add_edge(s, member, 1, 0); // s -> members
}
```

----

mcmf 部分，就只是模板...

```cpp=
struct MCMF { // 0-base
    struct edge {
        ll from, to, cap, flow, cost, rev;
    } *past[MAX_N];
    vector<edge> G[MAX_N];
    bitset<MAX_N> inq;
    ll dis[MAX_N], up[MAX_N], s, t, mx, n;
    bool BellmanFord(ll &flow, ll &cost) {
        fill(dis, dis + n, INF);
        queue<ll> q;
        q.push(s), inq.reset(), inq[s] = 1;
        up[s] = mx - flow, past[s] = 0, dis[s] = 0;
        while (!q.empty()) {
            ll u = q.front();
            q.pop(), inq[u] = 0;
            if (!up[u]) continue;
            for (auto &e : G[u]){
                if (e.flow != e.cap && dis[e.to] > dis[u] + e.cost) {
                    dis[e.to] = dis[u] + e.cost, past[e.to] = &e;
                    up[e.to] = min(up[u], e.cap - e.flow);
                    if (!inq[e.to]) inq[e.to] = 1, q.push(e.to);
                }
            }
        }
        if (dis[t] == INF) return 0;
        flow += up[t], cost += up[t] * dis[t];
        for (ll i = t; past[i]; i = past[i]->from) {
            auto &e = *past[i];
            e.flow += up[t], G[e.to][e.rev].flow -= up[t];
        }
        return 1;
    }
    ll MinCostMaxFlow(ll _s, ll _t, ll &cost) {
        s = _s, t = _t, cost = 0;
        ll flow = 0;
        while (BellmanFord(flow, cost));
        return flow;
    }
    void init(ll _n, ll _mx) {
        n = _n, mx = _mx;
        for (int i = 0; i < n; ++i) G[i].clear();
    }
    void add_edge(ll a, ll b, ll cap, ll cost) {
        G[a].pb(edge{a, b, cap, 0, cost, G[b].size()});
        G[b].pb(edge{b, a, 0, 0, -cost, G[a].size() - 1});
    }
    void solve(int n){
        
        ll ans = 0;
        mcmf.MinCostMaxFlow(s, t, ans);
        
        cout << C * m - ans << endl; // max cost
        
        for(auto e : G[s]){
            if(e.cap == e.flow){ // used
                cout << e.to << ' ';
                for(auto f : G[e.to]){ // skill
                    if(f.cap == f.flow){
                        cout << f.to - n << "\n";
                        break;
                    }
                }
            }
        }
    }
}mcmf;
```

----

### 簡單版本 

題目的內容不變，但 $m$ 的最大值只有$14$

----

### DP 解

一樣每個技能先挑前 $m$ 個人，接著對 $m^2$ 個人之中做位元DP
狀態為[已挑選的技能組合, 前 $i$ 個人] -> 最佳解

其中挑選的組合為 $[0, 2^m - 1)$，每個bit代表是否已選取該技能
對於每個特定的組合，
DP[新組合, $i$] = max(DP[舊組合 + 新技能, $i - 1$], DP[新組合, $i$])

複雜度：
遍歷成員：$O(m^2)$
遍歷狀態：$O(2^m)$
轉移：$O(m)$
整體複雜度：$O(m^32^m)$

----

### 程式碼


```cpp=
// fromLastSkill -> trace parent
// val -> maximum
int dpSize = 1 << m, dpidx = 0;
vector<int> memberId;
for(auto member : members){
    dpidx++;
    memberId.push_back(member.first);
    for(int i = 0; i < dpSize; i++){
        if(dp[dpidx][i].val <= dp[dpidx - 1][i].val){
            dp[dpidx][i].val = dp[dpidx - 1][i].val;
            dp[dpidx][i].fromLastSkill = -1;
        }
        for(auto ski : member.second){
            if(i & (1 << ski.first - 1)) continue;
            int ii = i | (1 << ski.first - 1);
            if(dp[dpidx][ii].val < dp[dpidx - 1][i].val + ski.second){
                dp[dpidx][ii].val = dp[dpidx - 1][i].val + ski.second;
                dp[dpidx][ii].fromLastSkill = ski.first;
            }
        }
    }
}
```


---

## L. Linear Classifers

AC 隊伍數 @ 封版：0

----

### 題目大意

給定平面上 $n$ 個點，點都不重複且三點不共線。請你找到兩條線，使得分成的 $4$ 個 region 都包含恰有 $\frac{n}{4}$ 個點。

----

### 觀察

- 假設有兩條垂直的線，每條線兩邊都有 $\frac{n}{2}$ 個點。
- 我們把這兩條線的角度從 $\theta = 0$ 轉到 $\theta = \frac{\pi}{2}$，一直保持兩邊都各有 $\frac{n}{2}$ 個點
- 可以證明一定存在一個角度 $\theta$ 是答案

----

### 簡要證明

- 假設在 $\theta = 0$ 的時候其中一個 region 有 $a$ 個點
- 那在轉到 $\theta = \frac{\pi}{2}$ 時那個 region 會有 $\frac{n}{2} - a$ 個點
- 注意到 $\frac{n}{4}$ 介於 $a$ 和 $\frac{n}{2} - a$ 之間，而 $\theta$ 在變動的時候每次最多只會 $+1, -1$ 或不變，所以一定存在一個角度使得那個 region 有 $\frac{n}{4}$ 個點。

----

### 實作

- 這裡我們選用整數二分搜避免浮點數誤差。
- 注意到二分搜的精度至少要 $10^{-8}$ 左右，因為是可以構造出答案夾角很小的測資的。

```
4
0 0
1 1
9998 9999
9999 10000
```

----

### 參考作法

- 隨意選一個大質數。這個大質數至少要是 $C^2$ 量級（ $C$ 是點的值域。以這題來說至少要是 $10^8$）。假設是 $m$。
- 二分搜的過程是整數二分搜。每次的兩條線是 $\tan \theta  =\frac{a}{m}$ 的線和另一條和他垂直的線，看 $ax+my$ （跟另一條線）前 $\frac{n}{4}$ 小的重疊的部份是不是恰好是 $\frac{n}{4}$。
- 如果一開始水平或垂直線有多於一個點的話，可以對那個斜率周圍枚舉一下，找到適當的二分搜範圍。

----

### 參考作法

```cpp=
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
using pll = pair<ll, ll>;
constexpr ll base = 998244353; // any large prime would do the work
vector<pll> points;

int number_of_points_in_corner(ll a) {
  int n = points.size();
  vector<pll> orderx, ordery;
  vector<int> cnt(n);
  ll b = base;
  for (int i = 0; i < n; i++) {
    ll x = points[i].first, y = points[i].second;
    orderx.emplace_back(-a * x + b * y, i);
    ordery.emplace_back(b * x + a * y, i);
  }
  sort(orderx.begin(), orderx.end());
  sort(ordery.begin(), ordery.end());
  for (int i = 0; i + 1 < n; i++) {
    if (orderx[i].first == orderx[i + 1].first)
      return -1;
    if (ordery[i].first == ordery[i + 1].first)
      return -1;
  }
  for (int i = 0; i < n / 2; i++) {
    cnt[orderx[i].second]++;
    cnt[ordery[i].second]++;
  }
  int ret = 0;
  for (int i = 0; i < n; i++)
    ret += (cnt[i] == 2);
  return ret;
}

void print_answer(ll a) {
  int n = points.size();
  vector<pll> orderx, ordery;
  ll b = base;
  for (int i = 0; i < n; i++) {
    ll x = points[i].first, y = points[i].second;
    orderx.emplace_back(-a * x + b * y, i);
    ordery.emplace_back(b * x + a * y, i);
  }
  sort(orderx.begin(), orderx.end());
  sort(ordery.begin(), ordery.end());
  cout << 1 << ' ' << -a << ' ' << 1 << ' ' << b << ' ' << 2 << ' '
       << (orderx[n / 2 - 1].first + orderx[n / 2].first) << '\n';
  cout << 1 << ' ' << b << ' ' << 1 << ' ' << a << ' ' << 2 << ' '
       << (ordery[n / 2 - 1].first + ordery[n / 2].first) << '\n';
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  points.resize(n);
  for (auto &[x, y] : points)
    cin >> x >> y;

  ll L = -1, R = base * 10001;
  ll numL = number_of_points_in_corner(L), numR = number_of_points_in_corner(R);
  if (numL == n / 4) {
    print_answer(L);
    return 0;
  }
  if (numR == n / 4) {
    print_answer(R);
    return 0;
  }
  // cout << numL << ' ' << numR << '\n';
  while (R - L > 2) {
    ll M = (L + R) >> 1;
    if (M % base == 0)
      M--; // to prevent colinear
    ll numM = number_of_points_in_corner(M);
    if (numM == n / 4) {
      print_answer(M);
      return 0;
    }
    if ((numL - n / 4) * (numM - n / 4) < 0)
      R = M;
    else
      L = M;
  }
  for (auto i = L; i <= R; i++) {
    if (number_of_points_in_corner(i) == n / 4) {
      print_answer(i);
      return 0;
    }
  }
}
```

---

## 開版

---

## 封板後解題隊伍數量

----

```vega
{
  "data": {
    "values": [
      {"Problem":"A", "group": "封板前", "solve":44},
      {"Problem":"A", "group": "封板後", "solve":0},
      {"Problem":"B", "group": "封板前", "solve":24},
      {"Problem":"B", "group": "封板後", "solve":1},
      {"Problem":"C", "group": "封板前", "solve":1},
      {"Problem":"C", "group": "封板後", "solve":1},
      {"Problem":"D", "group": "封板前", "solve":31},
      {"Problem":"D", "group": "封板後", "solve":2},
      {"Problem":"E", "group": "封板前", "solve":21},
      {"Problem":"E", "group": "封板後", "solve":0},
      {"Problem":"F", "group": "封板前", "solve":1},
      {"Problem":"F", "group": "封板後", "solve":2},
      {"Problem":"G", "group": "封板前", "solve":9},
      {"Problem":"G", "group": "封板後", "solve":0},
      {"Problem":"H", "group": "封板前", "solve":4},
      {"Problem":"H", "group": "封板後", "solve":2},
      {"Problem":"I", "group": "封板前", "solve":3},
      {"Problem":"I", "group": "封板後", "solve":2},
      {"Problem":"J", "group": "封板前", "solve":2},
      {"Problem":"J", "group": "封板後", "solve":2},
      {"Problem":"K", "group": "封板前", "solve":2},
      {"Problem":"K", "group": "封板後", "solve":3},
      {"Problem":"L", "group": "封板前", "solve":0},
      {"Problem":"L", "group": "封板後", "solve":2},
      {"Problem":"M", "group": "封板前", "solve":2},
      {"Problem":"M", "group": "封板後", "solve":0},
      {"Problem":"N", "group": "封板前", "solve":34},
      {"Problem":"N", "group": "封板後", "solve":1}
    ]
  },
   "layer": [
    {"mark": "bar"},
    {
      "mark": {
        "type": "text",
        "align": "center",
        "baseline": "middle",
        "dx": 0,
        "dy": -5
      },
      "encoding": {
        "text": {"field": "solve", "type": "quantitative", "format": ".2"}
      }
    }
  ],
  "encoding": {
    "x": {
        "field": "Problem",
        "sort": {
            "op": "sum",
            "field": "solve",
            "order": "descending"
        }
    },
    "y": {
        "field": "solve",
        "type": "quantitative"
    },
    "xOffset": {
        "field": "group"
    },
    "color": {
        "field": "group"
    }
  }
}
```
