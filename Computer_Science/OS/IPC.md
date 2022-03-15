---
sort: 8
---

# Inter Process Communication (IPC)



### PIPE (Same PPID) 

* FIFO 구조로 동작하며, 부모와 자식 Process 간 통신할 때 사용
* 한쪽 방향으로만 통신이 가능하고 각각의 PIPE는 Read(수신)/Write(송신) 중 하나의 기능만 제공함
  * 하나의 Process는 Read만 하고, 다른 하나의 Process는 Write만 할 때 유용하게 사용할 수 있음
* Process 간 송수신을 하기 위해서는 2개의 Pipe를 구현해야 됨
* PIPE는 Blocking을 지원하기 때문에 반이중(Half-Duplex) 통신
  * 반이중 : 양방향 전송은 가능하나, 동시에 양쪽 방향에서 전송할 수 없음

![PIPE_Same_PPID](./Img/PIPE_Same_PPID.png)

### PIPE (Different PPID)

* 



### Message Queue



### Shared Memory



### Semaphore



### Socket



### RPC (Remote Procedure Call)
