def solution(n, results):
    wins, loses = {}, {} #딕셔너리

    for i in range(1, n+1):
        wins[i], loses[i] = set(), set() #딕셔너리 안에 셋으로 정의
    for i in range(1, n+1):
        for r in results:
            #i번 선수가 이겼을 때 i번에게 진 선수들 모음
            if r[0] == i:
                wins[i].add(r[1])
            #i번 선수가 졌을 때 i번에게 이긴 선수들 모음
            if r[1] == i:
                loses[i].add(r[0])
        #i번 선수에게 이긴 선수들은 i번에게 진 선수들은 무조건 이긴다는 의미
        for winner in loses[i]:                
            wins[winner].update(wins[i])
        #i번 선수에게 진 선수들은 i번에게 이긴 선수들한테 무조건 진다는 의미
        for loser in wins[i]:
            loses[loser].update(loses[i])
    cnt = 0
    for i in range(1, n+1):                   
        if len(wins[i]) + len(loses[i]) == n-1:
            cnt += 1
    return cnt