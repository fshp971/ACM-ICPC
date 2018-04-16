## 子集卷积
关键在于如何正确划分集合，一般需要仔细观察下标之间的关系来进行划分。<br>

hdu-6057 (Claris)<br>
cf-914G<br>

## 区间问题常见思路
莫队分块 维护多项式 维护矩阵 取对数 泰勒展开<br>

## 一些带根号复杂度的题
cf-914F (字符串) <br>
hihoCoder-1629 (ICPC2017 北京) 莫队<br>

## 杂乱数学题
cf-932E 生成函数<br>
csa-round71-Losing-Nim 和按位有关的精妙dp<br>
gym-101620G (CERC 2017) 有趣的概率/期望题<br>
arc089-E 类线性规划题<br>
nowcoder-73F (Wannafly 11) 分治NTT, 优先队列优化<br>
nowcoder-73E (Wannafly 11) 循环卷积NTT, 和毕姥爷出过的某题做法一样<br>
XVII Open Cup ---- Two Capitals H - Sophie’s Sets 搜索剪枝 (别负优化<br>
Petrozavodsk Winter-2018. Jagiellonian U Contest J (对数乱搞<br>
cf-961G 斯特林数<br>

## 爆炸数据结构
cf-935F 复杂线段树<br>
Petrozavodsk Winter-2018 CMU Contest A - Mines 线段树优化建图, 经典套路<br>
bzoj-2286 虚树裸题<br>
Petrozavodsk Winter-2018. Jagiellonian U Contest K 启发式合并复杂度稳定O(nlogn)<br>

## 智障DP
nowcoder-73C (Wannafly 11) 轮廓线dp思想<br>
Petrozavodsk Winter-2018 CMU Contest J  (重坑啊<br>
Petrozavodsk Winter-2018 CMU Contest I  经典dp大杂烩<br>
nowcoder-79D (Wannafly 12) 矩阵计数 (好像很经典啊<br>

## 智商题
gym-101620K (CERC 2017) 差分, 思路极其巧妙<br>
XVII Open Cup ---- Moscow Workshops E - Jumping is Fun 考虑答案的二进制表示<br>
nowcoder-79E (Wannafly 12) 智商图论转换<br>

## xjb字符串
bzoj-3926 诸神们的幻想乡 经典魔改SAM<br>
XVII Open Cup ---- Moscow Workshops F - Online LCS 魔改SAM<br>

## 玄学图论
#### XVII Open Cup ---- Capitals J - Travelling to Random Cities
无向图多点对最短路查询, 由数据的随机性知大部分最短路不会太长<br>
于是可以先正向反向分别爆搜前几步, 若此时仍无解则再爆搜全图 (玄学调参即可通过<br>
cf-962F 通过维护dfs序找环, 思想值得学习<br>

## 神题
#### XVII Open Cup ---- Khamovniki J - Stairways
首先要注意到dp状态: dp(i,k) 表示做到第i个人时, 次大队的最大值为k时的最小花费<br>
分析完转移方程后, 通过分块及斜率优化后进行转移, 时间复杂度O(n sqrt(n))<br>

## 类欧几里得算法待做题
~~bzoj-3817~~<br>
bzoj-2187<br>
bzoj-2712<br>
bzoj-2987<br>
bzoj-1938<br>

## 线段树优化建图
bzoj-3073<br>
bzoj-5017<br>
cf-786B<br>

## 虚树
bzoj-3572<br>
~~bzoj-3991~~<br>

## Waitting
Tsukuba 2017<br>
Tsukuba 2016<br>
