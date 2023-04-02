import sys
n, m = map(int, sys.stdin.readline().split())
tree = list(map(int, sys.stdin.readline().split()))
def treeSum(mid):
    tot = 0
    for i in range(n):
        if tree[i] >= mid:
            tot += tree[i] - mid
    return tot
def binarySearch():
    left = 0
    right = max(tree)
    while left <= right:
        mid = (left + right) // 2
        tot = treeSum(mid)
        if tot >= m:
            ans = mid
            left = mid+1
        else:
            right = mid-1
    return ans
print(binarySearch())