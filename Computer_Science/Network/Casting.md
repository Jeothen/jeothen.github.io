---
sort: 6
---

# Casting

### UniCast

* TCP/UDP 모두 지원하며, Source Mac주소에서 Destination Mac주소에 1:1(one-to-one)로 패킷 또는 메시지를 전송

* 다수의 Destination에 패킷을 전송할 때는 반복 작업을 해야되므로 비효율적
* 스위치를 통해 유니캐스트 패킷이 들어왔을 때, 통신 가능한 모든 포트로 브로드캐스트를 수행함
  * **ARP** : 브로드 캐스트를 통해 모든 통신 가능한 호스트에 전송하며, 패킷을 전송받은 호스트는 Destination 주소와 자신의 Mac 주소를 비교
  * Mac주소가 다른 PC(랜카드)는 Packet을 제거하기 때문에 CPU 부하가 없음
  * 동일한 Mac 주소를 가지는 랜카드는 패킷을 CPU에서 처리
* Destination에 대한 정보가 스위치의 포워딩 테이블에 없는 경우, 유니캐스트 플러드로 처리함
  * 유니캐스트 플러딩 : MAC 주소를 모르는 Destination을 스위치가 유니캐스트로 처리할 수 없기 때문에 브로드캐스트 진행

<br/>

### BroadCast

* UDP 통신만 지원하며, 자신과 동일한 네트워크에 속한 모든 호스트에 패킷을 전송
  * Flooding 방식과 비슷하지만, 브로드캐스트는 모든 네트워크에 동시에 보내고 동일한 링크를 통해 동일한 패킷을 한번만 전송하지만, 플러딩은 동시에 보내지 않고 동일한 링크를 통해 동일한 패킷을 여러번 보낼 수 있음
* 목적지를 브로드캐스트 주소로 전송하며, 랜카드에서 브로드캐스트 주소로 수신받으면 CPU에 패킷을 전달하여 처리
  * 전체적인 트래픽 증가 유발
  * CPU에 전달하면서 인터럽트 발생 및 CPU 부하 증가

* 지정된 방식의 브로드캐스트를 이용하는 경우, 일반적으로 라우터에서 브로트캐스트 방식을 사용했을 때 패킷을 버리기때문에 필요시에는 라우터에 예약되어 있는 브로드캐스트 주소를 이용
* 제한된 방식의 브로드캐스트를 이용하는 경우, 패킷이 라우터를 넘어가지 않기 때문에 항상 브로드캐스팅 가능

<br/>

### MultiCast

* UDP 통신만 지원하며, 설정해놓은 특정 그룹에 속한 하나 이상의 호스트에게 패킷을 전송
* 다수의 호스트 수만큼 유니캐스트로 전송을 하게 된다면 CPU에 부하가 상당할 것이고, 브로드캐스트로 전송시 패킷이 불필요한 호스트에게 전송되는 단점을 보완
* 네트워크 클래스 중 D클래스를 이용하여 특정 그룹을 만듦
  * 수신할 호스트에서 D클래스에 등록하게 되면, D클래스에 속한 모든 호스트에 패킷을 전송하는 방식

* 패킷을 한번만 전송하기 때문에 네트워크 인프라를 효율적으로 이용
* 발신자와 무관한 ASM (Any-Source-MultiCast)은 Group-Shared Tree (Core-Based Tree)
  * MultiCast 트래픽의 source를 찾기 위해 특별한 프로토콜(RP, MSDP)를 사용해야되는데 라우터에 부하를 발생시킴
  * 망 내의에서 하나의 라우터를 root 라우터를 설정하고 이를 통해 패킷 전달
  * delay time은 증가하지만, 확장성으로 인해 대규모망에서 주로 사용
* 발신자가 필요한 SSM (Source-Specified-MultiCast)은 Source-Based Tree
  * Tree의 left node를 root 라우터로 설정하여 delay time이 짧아서 소규모망에서 주로 사용
  * 모든 leaf에서 멀티캐스트에 대한 정보를 가지고 있어서 비효율적이고, 확장성이 부족함 
  * 서버에 장애가 발생시 문제가 되는 라우터만 영향을 끼침
* 스위치 / 라우터가 멀티캐스트를 지원해야 사용할 수 있음
  * 스위치에서 미지원시 브로드캐스트로 처리
  * 라우터에서 미지원시 지정된 방식의 브로드캐스트처럼 패킷을 버림
    * 패킷에 터널링에 대한 정보를 캡슐화하여 유니캐스트와 동일한 방식으로 라우팅 필요

<br/>

### AnyCast

* 단일 소스에서 가장 가까운 노드와 통신
* 가장 가까운 노드와 통신하기 때문에 다수의 노드들 전송될 수도 있음
  * 동일한 destination 주소로 취급

* 가장 큰 목적은 트래픽 Load Balancing
  * 하나의 destination으로 유니캐스트 되는 현상을 방지
* 서버에 문제가 생겼을 때 동일 anycast로 운용되는 다른 서버로 이중화
