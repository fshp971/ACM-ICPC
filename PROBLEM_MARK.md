## 子集卷积
关键在于如何正确划分集合，一般需要仔细观察下标之间的关系来进行划分。<br>

hdu-6057 (Claris)<br>
cf-914G<br>

## 区间问题常见思路
莫队分块 维护多项式 维护矩阵 取对数 泰勒展开<br>

## 一些带根号复杂度的题
cf-914F (字符串) <br>
hihoCoder-1629 (ICPC2017 北京) 莫队 (有空再做一遍)<br>

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
gym-101234D (16-17国立台湾大学WF选拔 by dreamoon) 树分治计数, FFT优化, 比较有意思<br>
hdu-5885 2016青岛online 二维坐标压成一维后进行FFT, 卡精度<br>
kattis - Probe Droids (NAIPC 2018 F) Stern–Brocot Tree & 类欧几里得<br>
bzoj-2187 形式特别的类欧<br>
bzoj-1938 类欧几里得, 思路比较有意思, 将模运算变换成减法<br>
hdu-6270 (CCPC2017 杭州) 容斥, NTT计算, 好题<br>
nc-140J (牛客多校day2) 二进制分解瞎搞<br>
hdu-6353, nowcoder-145I 树分治计数方法值得学习<br>
hdu-6372(多校6 K) 将原矩阵当成邻接矩阵后转换成图论, 再观察组合意义求解. 思路类似nc-139B(叉姐牛客多校)<br>
bzoj-5217 二维转一维FFT<br>
zoj-3982 (CCPC 2017 秦皇岛) 卡特兰数dp<br>
CodeChef - MANCBST 打表找规律, 推出递推式(类似伯努利数的递推形式), 然后多项式求逆<br>
hdu-4344 Miller Rabin素性检测, Pollared-Rho素数分解, 的优秀的测板题<br>
hdu-6275 (CCPC 2016 杭州) 类欧瞎搞<br>
XIX Open Cup GP of SPb C - Clique Festival 牛逼计数<br>

## 爆炸数据结构
cf-935F 复杂线段树<br>
Petrozavodsk Winter-2018 CMU Contest A - Mines 线段树优化建图, 经典套路<br>
bzoj-2286 虚树裸题<br>
Petrozavodsk Winter-2018. Jagiellonian U Contest K 启发式合并复杂度稳定O(nlogn)<br>
hdu-5993 (ICPC2016 青岛) (czk出线题) 树上dfs序维护区间点集直径, 需要RMQ预处理实现O(1)查询LCA (hdu又卡时间又卡空间, 现场可能不需要)<br>
hdu-5994 (ICPC2016 青岛) 一道具代表性的KD-tree, 深刻展现了KD-tree胡乱剪枝的精髓(然而出题人可能不太会英语, 题面全程不说人话)<br>
bzoj-3514 在线询问使用指定区间内的边时构成的联通块数量, 套路题, 首先用lct维护生成树计算出每条边的上一条冲突边(即会形成环), 然后建主席树瞎算算就好了<br>
bzoj-2957 线段树妙用, 复杂度O(n(logn)^2)<br>

#### nowcoder-104I 湖北省赛
首先将边的存在区间离线到线段树上(区间id直接用vector存), 之后回答询问相当于是在线段树上dfs<br>
dfs时, 通过栈来维护一个可回滚操作的并查集, 栈保存每次修改前的结点的相关信息<br>
由于此时的并查集不能进行路径压缩, 故应进行启发式合并, 这样可证明每次find操作是O(logn)的<br>
总时间复杂度大概是O(m(logm)(logn))<br>

cf-986E 素因数分解, 需要正确分析复杂度, 好题<br>
hdu-6333 (hdu多校2018 day4) 莫队 (可是为什么现场看不出来呢...<br>
luogu-3960 (NOIP2017 D2T3) jls的题, 强行上splay可过<br>
gym-101889D odt乱搞<br>

#### bzoj-4262
一个经典套路题. 首先离线将询问Q(l1,r1,l2,r2)拆成(Q(l1,r1,r2)-Q(l1,r2,l2-1))<br>
然后问题转化成求给定左端点区间[l,r], 右端点取[1,x]时的答案Q(l,r,x)<br>
然后就可以从小到大枚举x, 并用单调栈维护单增(单减)序列, 由于原数列的随机性, 使得单调栈期望深度为O(logn)<br>
因此对每个x分段更新线段树, 总时间复杂度O(nlog(logn))<br>
类似的题目: 计蒜客-31712 (ICPC2018 焦作网赛C), bzoj-4540<br>

## 智障DP
nowcoder-73C (Wannafly 11) 轮廓线dp思想<br>
Petrozavodsk Winter-2018 CMU Contest J  (重坑啊<br>
Petrozavodsk Winter-2018 CMU Contest I  经典dp大杂烩<br>
nowcoder-79D (Wannafly 12) 矩阵计数 (好像很经典啊<br>
hdu-6365 极角排序真有趣<br>
hdu-5735 (hdu多校2016) 通过将二进制分拆成前8位和后8位来平衡复杂度, 使得单次计算答案和更新dp数组复杂度均为2^8<br>
gym-101981B (ICPC2018南京 B) 王钦石二分<br>
gym-102012D (ICPC2018徐州 D) 首先可以将问题转变成在三维空间中求相同子序列对(tuple)的个数, 然后设状态为f\[i\]\[k\]\[j\], 表示第一维子序列在1~i中任取, 第二及第三维子序列末尾分别为k,j, 然后就可以胡乱转移了, 总复杂度O(n^3)<br>
cf-1129D 牛逼dp, 分块维护转移, 复杂度O(n\sqrt{n})<br>

## 弱鸡几何
zoj-4000 合理转换问题同时注意边界; atan2(y,x)可以直接求出(x,y)在(-Pi,Pi]范围内对应的弧度(当然要小心处理边界)<br>
cf-1059D 注意相对误差<br>

## 智商题
gym-101620K (CERC 2017) 差分, 思路极其巧妙<br>
XVII Open Cup ---- Moscow Workshops E - Jumping is Fun 考虑答案的二进制表示<br>
nowcoder-79E (Wannafly 12) 智商图论转换<br>
Petrozavodsk Winter-2018. Korea L - XOR Transformation 观察特性找规律 (观察能力不够优秀啊<br>
nc-139A (牛客多校day1) 思维题, 观察得组合意义<br>
nc-139B (牛客多校day1) 思维题, 观察矩阵实际意义<br>
hdu-6326 (hdu多校2018 day3) 根据性质贪心, 转换成子问题, 逐步缩小规模<br>
hdu-6387 (hdu多校2018 day7 by UESTC) 做法非常巧妙, 需要先将解所满足的性质用数学语言表述出, 然后再优化找解的过程<br>
cf-1041F 观察性质, 推出结论<br>
hdu-1055 根据性质贪心, 将结点权值合并到其父节点上, 转换成子问题缩小规模, hdu-6326和本题类似<br>
nowcoder-148B (2018 牛客多校10 by jls) 二进制优化暴力+线段树维护一些东西<br>

## xjb字符串
bzoj-3926 诸神们的幻想乡 经典魔改SAM<br>
XVII Open Cup ---- Moscow Workshops F - Online LCS 魔改SAM<br>

## 玄学图论
#### XVII Open Cup ---- Capitals J - Travelling to Random Cities
无向图多点对最短路查询, 由数据的随机性知大部分最短路不会太长<br>
于是可以先正向反向分别爆搜前几步, 若此时仍无解则再爆搜全图 (玄学调参即可通过<br>
cf-962F 通过维护dfs序找环, 思想值得学习<br>
cf-1009G 巧妙应用Hall定理<br>
hdu-6350 by SkyWalkerT 仙人掌图转成树来做, 比较有趣<br>
hdu-5960 (ICPC2016 沈阳) k长路, 建图思想是关键, 可用来测k长(短)路模板<br>
poj-2449 比较好的k短路模板测试题, 含重边, 自环, 图不保证连通<br>
nowcoder-203I (wannafly camp 2018 day3) 做法有点妙。。直接拿所有关键点作为源点跑最短路, 记录每个点是从哪个关键点扩展而来的, 然后枚举所有边, 如果某条边两端点分别从不同源点扩展而来, 就更新一下答案<br>
jisuanke-19979 (ICPC2017 南宁) 通过可达性图建立二分图然后跑最大匹配, n-匹配数就是答案(其实就是重新建图后求最大独立集, |最大独立集| = |V| - |最大匹配数|)<br>
NWERC-2018 F - Fastest Speedrun 使用类似于朱刘算法缩环重建图的方法来对原图重建边权, 然后跑最短路<br>

## 神题
#### XVII Open Cup ---- Khamovniki J - Stairways
首先要注意到dp状态: dp(i,k) 表示做到第i个人时, 次大队的最大值为k时的最小花费<br>
分析完转移方程后, 通过分块及斜率优化后进行转移, 时间复杂度O(n sqrt(n))<br>

## 类欧几里得算法待做题
~~bzoj-3817~~<br>
~~bzoj-2187~~<br>
bzoj-2712<br>
~~bzoj-2987~~<br>
~~bzoj-1938~~<br>

## 线段树优化建图
bzoj-3073<br>
bzoj-5017<br>
cf-786B<br>

## Pending List
Tsukuba 2017<br>
Tsukuba 2016<br>
gym-101611B<br>
bzoj-3073<br>
bzoj-3339<br>
xjb-training-9<br>
xjb-training-10 B I<br>
xjb-training-11<br>
~~xjb-training-12 M (学网络流)~~<br>
xjb-training-13 CCPC-FINAL<br>
xjb-training-14 ECL-FINAL<br>
SWERC-2017 (Claris博客有题解)<br>
计蒜之道2018复赛<br>
cf-505D<br>
SCUT 2018 暑假训练热身赛<br>
bzoj-3551<br>
51nod-1236 序列求和系列题<br>
cf-gym-100959A<br>
https://www.codechef.com/problems/BTREE<br>
loj-2469<br>
cerc 14-15 L<br>
hnoi-2010 动态树<br>
nowcoder-145I (牛客多校7) 等数据对拍<br>
hdu-6444 不知道错哪儿了啊(<br>
hdu-6359 大型数据结构题, 有空再补<br>
hdu-4656 大都会赛L原题(?)<br>
