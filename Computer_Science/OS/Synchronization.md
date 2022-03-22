---
sort: 10
---

# Synchronization

* 사전적인 의미로 동기화란 동일 시간대에 데이터베이스 데이터를 일치화하는 작업

### Synchronization vs Asynchronization

**Synchronous**

* OS에서 Process/Thead 동기화인 경우, Request와 Response가 동시에 일어남을 의미
  * Request 후 일부 시간이 소요되더라도, Response 받고 나서 Process/Thread를 진행 (Transaction을 동시에 맞춤)

**Asynchronization**

* 비동기는 Process/Thread의 Request와 Response가 동시에 발생하지 않는 것을 의미
  * Request를 요청하고 작업을 계속 수행하는 병렬 처리 방식

![Synchronous](./Img/Synchronous.png)

<div style="text-align: right">Image Ref : https://www.koyeb.com/blog/introduction-to-synchronous-and-asynchronous-processing </div>

### Blocking vs Non Blocking

**Blocking I/O**

* 호출된 함수가 작업을 마칠때까지 호출한 함수에게 제어권을 넘기지 않음
  * 호출된 함수에게 제어권을 넘긴 상태로 유지하고, 실행이 종료되면 제어권 반납
* Response를 받기 전까지 호출한 함수는 대기 상태로 유지되며 프로세스를 진행할 수 없음
* Kernel Mode로 Context Switching하면서 System Call을 진행하고, Return을 받으며 User Mode로 돌아옴

**Non Blocking**

* 호출한 함수가 호출된 함수에게 제어권을 넘기지 않음
* 호출한 함수는 제어권을 가지고 있기 때문에, 계속해서 Process를 실행
  * 호출된 함수가 바로 Return하여 제어권 반납

![Blocking](./Img/Blocking.png)

<div style="text-align: right">Image Ref : http://faculty.salina.k-state.edu/tim/ossg/Device/blocking.html </div>

### Synchronous / Blocking Model

* 동기/비동기는 Process의 동시성, Blocking/NonBlocking은 Process의 즉각적인 Return이 중심

* A 함수 : 호출한 함수 / B 함수 : 호출된 함수

* Synchronous - Blocking

  * B함수에게 제어권을 넘겨주고 값을 response하기 전까지 대기 상태

  * A 함수가 return 값과 제어권을 돌려받으면 Process 진행

* ASynchronous - Blocking
  * Blocking이므로, A함수가 B함수에게 제어권과 Callback 함수를 넘겨줌
  * A함수는 제어권이 없기 때문에,  Response 받을때까지 대기 상태
    * Callback함수와 Return을 같이 Response하기 때문에 Synchronous - Blocking과 비슷하게 동작함

* Synchronous - NonBlocking
  * A함수는 B함수에게 제어권을 주지 않기 때문에, A함수를 계속 실행함
    * B함수는 Request를 받을 때마다 즉시 Response함
  * A함수가 Synchronous라서 지속적으로 B함수에게 Return을 전송할 수 있는 상황인지 확인
  * B함수가 실행을 완료하고 A함수의 Request를 받게 되면 Return 값을 Response

* ASynchronous - NonBlocking
  * A함수는 B함수에게 제어권을 넘겨주지 않기 때문에, A함수를 계속 실행함
  * A함수가 ASynchronous라서 B함수의 상태를 확인하지 않음
  * B함수 실행이 완료된 후 Callback을 통해 Response



---

### Critical Section

* 둘 이상의 Thread가 동시에 공유자원에 접근하는 현상을 방지하기 위해, 하나의 Thread만 접근할 수 있도록 보장하는 영역
* 요구조건
  * Mutual Exclusion : Process가 Critical Section에서 실행될 때, 다른 Process가 Critical Section에 진입할 수 없음
  * Progress : 임계구역에서 실행되는 Process가 없고 진입하려는 Process들이 있을 때, 제한된 시간 내 Critical Section에 진입할 Process를 선택해야 됨
  * Bounded Waiting : Process가 Critical Section에 진입하려고 요청을 하고 ACK 되기 전까지, 다른 Process들의 Critical Section 진입 횟수를 제한하여 Starvation을 방지

### DeadLock





### Peterson's Solution



### Mutex Locks



### Semaphore 





### Problems

**Producer and Consumer (유한버퍼, The Bounded Buffer)**





**Readers-Writers**



**Dining Philosophers**





