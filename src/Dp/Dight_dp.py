
def dfs(当前位数 x, 当前状态 y, 前导零限制 st, 上界限制 limit):
    if 到达边界 and 符合要求 then 
    返回边界的合法答案
  if 到达边界 and 不符合要求 then
    返回边界的不合法答案          # 这个一般不会有，一般枚举填数的时候如果没有限制就会有（只要会访问到边界不合法情况就要加上）。 

  if 当前的状态已经记忆化过 then
    返回记录的答案

  var result = 0         # 记录答案
    var up = 9           # 当前位填数的上限
    if 有上界限制 then
        up = 当前位在 n 当中的数字       # n 是要求的 F(n) 的自变量

    for 枚举当前位的填数值 from 0 to up :
        if 当前位填的数不符合限制 then
            continue
        if 有前导零限制 and 当前填写的是 0 then
            result += dfs(x - 1, 下一个状态, True, 是否触碰上界限制)
        else then
            result += dfs(x - 1, 下一个状态, False, 是否触碰上界限制)

  记录当前状态的答案 f[x][y] = result
  返回答案 result


def solve(要求的 F 的自变量 n):
    存储每一位数字的 vector 清空
    while n != 0 then:
        vector <-- n % base           # base表示是哪一个进制
        n /= base
    清空状态数组
    返回对应状态的答案（调用 dfs）
