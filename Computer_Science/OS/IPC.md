---
sort: 8
---

# Inter Process Communication (IPC)

### PIPE

* FIFO(First In First Out) 구조로 동작
* PIPE는 Blocking을 지원하기 때문에 반이중(Half-Duplex) 통신
  * 반이중 : 양방향 전송은 가능하나, 동시에 양쪽 방향에서 전송할 수 없음
* 한쪽 방향으로만 통신이 가능하고 각각의 PIPE는 Read(수신)/Write(송신) 중 하나의 기능만 제공함
  * 하나의 Process는 Read만 하고, 다른 하나의 Process는 Write만 할 때 유용하게 사용할 수 있음
  * Process 간 송수신을 하기 위해서는 2개의 Pipe를 구현해야 됨
* 익명 PIPE인 경우, 동일한 PPID인 부모와 자식 Process 간 통신할 때 사용
  * Fork 함수를 이용하여 자식 Process를 만든 후 PIPE를 이용하여 통신
* Named PIPE인 경우, 부모/자식 Process 외 모든 프로세스 간 통신을 지원
  * mkfifo 함수를 이용하여 이름과 Mode를 가지는 FIFO파일을 생성
* FIFO는 파일 이름을 통해 접근할 수 있고, PIPE는 이름을 가지지 못함

![PIPE_Same_PPID](./Img/PIPE_Same_PPID.png)

### Message Queue

* PIPE와 동일하게 FIFO(Queue) 자료구조를 기반으로 통신 
* 여러 프로세스에서 커널에서 관리하는 공유 메모리에 접근할 수 있음
* 비동기 Message를 사용하는 프로세스 간 데이터 통신하는 것을 MOM(Message Oriented Middleware)이라고 하는데, Message Queue는 MOM을 구현한 것임
  * AMQP(Advanced Message Queuing Protocol)는 MOM을 위한 표준 프로토콜로 Queuing, Routing, Security 등의 기능이 있음
* RabbitMQ, MSMQ 등 AMQP를 이용한 Software들을 주로 사용
* Producer Process에서 생성한 Message를 Queue에 Routing을 하고, Consumer Process는 Queue에 있는 Message를 가져옴
  * msqid로 Message Queue를 식별

![Messge_queue](./Img/Messge_queue.png)



<div style="text-align: right"> Image ref : https://medium.com/must-know-computer-science/system-design-message-queues-245612428a22 </div>

**Apache Kafka**

* ....



### Shared Memory

* 



### Semaphore





### Socket





### RPC (Remote Procedure Call)
