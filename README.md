# ACM-ICPC
fshp971的ACM代码<br>

Good Game * 2<br>
GG * 3<br>
~~老年选手即将开始最后一搏~~<br>

ICPC 2018 Shenyang, Gold (Rank 6)<br>
CCPC 2018 Guilin, Silver<br>
ICPC 2018 Qingdao, Silver<br>
ICPC 2018 Xian EC Final, Silver<br>

Thank you all.<br>

# Todo List
**准备类欧模板([coffee chicken](https://ac.nowcoder.com/acm/contest/view-submission?submissionId=32154316))**<br>
二次剩余<br>
~~卡特兰数~~DONE<br>
~~学一下二维凸包~~抄板（<br>
**简单计算几何**<br>
最大权闭合子图<br>
点分树<br>
~~uoj模板测试~~基本完成<br>
补一个欧氏筛法的板子<br>
~~洲阁筛~~(没看出比杜教筛高明到哪里去啊?)<br>
基尔霍夫矩阵<br>

## To Be Learned
二分图匹配/二分图最大权匹配/网络流/费用流<br>
单纯形算法<br>
~~2-sat~~扔给队友<br>
~~马尔可夫过程?~~ 考虑手推<br>

## 一些常用的，需要点的技能点
简单二分图+网络流<br>

## 每日训练
~~尽量保证每天至少一场cf div2~~<br>
**有大段时间时优先考虑打OpenCup，然后是区域赛题**<br>
**补题时注意效率**<br>
推荐打的比赛：cf/atcoder/csacademy/nowcoder/51nod<br>
无论是比赛还是补题，都要保持紧张感，尽可能还原现场赛状态<br>

## 近期计划
**单挑OpenCup**<br>
**刷cf ~~（上黄）~~** <br>
**Claris的~~FFT~~及String**<br>
**补一下2016青岛的概率DP**<br>
**51nod数学题泛做**<br>
~~重刷SAM（学习完平衡树后还要再做相关题目）~~<br>
clj计数<br>
计蒜之道数学题待补<br>
**重刷AC自动机**<br>
**学习Manacher算法**<br>
多项式取模（多项式gcd）<br>
母函数 **(其实就是求导泰勒展开什么的**<br>
**刷dp啊喂**<br>

## 数学
pollard-rho<br>
Miller\_Rabin隨機素數測試<br>
博弈論：零和博弈 非合作博弈 纳什均衡<br>

## 计算几何坑点
在使用反三角函数acos(), asin()时一定要检查输入值是否在函数值域( [-1,1] )内<br>
对于输出答案为0的数, 一定要手动判0, 否则可能会输出"-0"导致PE或WA<br>
尽可能减少sqrt或除法的使用以提高精度<br>
浮点数应typedef一个DB类型, 这样可以方便在卡精度时切换long double<br>
对于需要控制相对误差(而不是绝对误差)的题, 二分/三分时候应手动限制查找次数而不是使用while(r-l\>eps), 否则可能由于数值太大引起精度丢失, 最终陷入死循环(cf-1059D). **事实上, 若答案数值过大都应手动限制查找次数.**<br>

## 一些坑

### 浮点数误差研究
在非计算几何题中出现浮点数时, 优先不考虑使用cmp()函数. 如果一定要使用, eps要调的很高.
例题: hdoj-6224: eps=1e-10 WA; eps=1e-12 AC.
( 仔细想了想, 原因大概是因为计算几何中的误差主要是由乘除开方三角函数产生的,
  这样会使得某些本应是一样的值产生比较大的误差, 这时eps若太高则可能导致判断错误致使答案错误.
  而像hdoj-6224这道题, 主要运算是加法, 仅涉及少量乘法, 因此误差很小, 这时若eps太低则会导致答案错误.
  事实上, 这题无需使用cmp()函数即可通过.

## 待填坑
UVa-11019<br>
hdu-5962（dp，java，BigDecimal，然而过不了orz）<br>
POJ 3693<br>
UVa-10829 Suffix Array + RMQ = ???<br>
hdu-6120（多校2017 7）下标乘FFT中国剩余定理加速（看不懂啊喂）<br>
XVIII Open Cup ---- Khamovniki D 平衡树, 替罪羊树<br>
hdu-4093 FFT(不太可做)<br>
Petrozavodsk Winter 2018 -- Korea: J,K<br>
