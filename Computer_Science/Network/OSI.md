---
sort: 1
---

# OSI 7 Layers

상당히 요약된 내용으로 추후에 각 Layer를 Category로 하여 정리

#### Description

* ISO에서 개발한 모델로, 네트워크 프로토콜 디자인과 통신을 계층으로 나누어 설명
* 기능별로 계층을 나누었기 때문에 유지보수에 용이

다중화 (Multiplexing) : 주로 Sender에서 동작하며, L7에서 L1으로 내려가면서 Header에 정보가 추가되는 방식

DeMultiplexing : 주로 Receiver에서 동작하며, Header에 있는 Data를 추출

<br/>

<br/>

### Layer 1. Physical Layer

**역할**

* 데이터 프레임의 옥텟(8bit 배열)을 송수신
* 반송파 감지, 무선매체 상태 (idle or busy) 확인 후 MAC 계층에 인폼 

**프로토콜** : Coax, Fiber, Wireleess

**장비** : Hub, Repeater, Cable&Connector

**유선 Lan 통신**

* 디지털 변조/복조 : Analog 신호와 Digital 신호 상호 변환
  * Transmitter : Analog -> Digital
  * Receiver : Digital -> Analog
* 케이블이 연결된 Lan Port를 보면 좌/우측 하단 LED로 통신 상태 확인 가능
* 좌측 LED : 주황색 - 연결됨  /  주황색(깜빡) - 데이터 전송중 / 꺼짐 - 연결 안 됨
* 우측 LED : 녹색 - 1Gbps로 연결 / 주황색 : 100Mbps로 연결 / 꺼짐 - 10Mbps로 연결

<br/>

**무선 Lan 통신**

* IEEE 802.11 규격사용

* PLCP (물리 계층 수렴 처리) Layer

  * DataLink의 MAC 계층과 무선전송 프레임을 연결

  * 무선매체의 상태를 확인하고 DataLink Mac 계층에 인폼

* PMD (물리매체 의존부) Layer

  * PLCP 계층으로부터 넘겨받은 정보를 안테나를 통해 무선매체(atmosphere)에 전송
  * 데이터 변조, 인코딩/디코딩 등 신호 처리

<br/>

* FHSS (주파수 도약 확산 스펙트럼)
  * 2.4GHz 대역에서 전송 신호를 만드는 기법
  * 시스템에 할당된 23개의 독립된 채널에서 약 79개의 주파수 내에서 작동
  * Random Hopping Sequence로 주파수 채널을 도약해서 데이터 송수신
    * 반송파 주파수가 일정하지 않아 주파수 도약이라고 함
  * 채널에 간섭이 있는 경우, 다른 채널로 도약하므로 Single Logic 채널로 안정된 데이터 송수신
  * 보안이 요구되는 곳에서 사용
* OFDM (직교 주파수 분할 다중화)
  * 5GHz ISM 대역에서 전송 신호를 만드는 기법
  * 고속의 데이터열을 여러개의 채널로 병렬로 전송
  * 동적 채널할당 기법으로 주파슈 효율을 향상시킬 수 있음
  * 높은 전송속도가 요구되는 곳에서 사용

<br/><br/>

### Layer 2. DataLink Layer

**역할**

* 물리계층에서 발생하는 오류를 감지하고 수정하며 신뢰성을 보장
* Flow Control : 메신지를 보낸 후, 응답을 받기 전까지 데이터 양을 제한
* Error Control : 손상된 패킷을 전송하지 못하도록 제어

**프로토콜** : Ethernet, SLIP, PPP, FDDI

**장비** : Bridge, Switch

**Frame**

* DataLink Layer의 전송 단위
* 이더넷 프레임의 경우 Data 크기가 46~1500바이트이며, 46보다 작은 경우 뒤에 Padding 적용
  * Preamble (7Byte) : 네트워크 장치가 수신기 클록을 쉽게 동기화 하여 비트 수준의 동기화 제공
  * Start Frame delimiter (1byte) : Preamble의 끝을 나타내는 값으로, 이데넷 프레임의 시작을 나타냄
  * Mac destinationa(6Byte) : 도착지 Mac 주소
  * Mac Source(6Byte) : 출발지 Mac 주소
  * 802.1Q Tag(4Byte, Option) : 가상 Lan을 지원하는 네트워크 표준
  * Type (2Byte) : 캡슐화 정의
  * Data
  * FCS (4Byte) : 오류 검출 부호에 추가된 통신 프로토콜
  * Gap (12Byte): 패킷 간 간격 
* Frame의 크기는 고정 크기와 가변 크기로 나뉨
  * Fixed-size Frame : ATM, WAN에서 사용되며, 프레임 간 경계 불필요
  * Variable-size Frame : LAN(Ethernet)에서 사용되며, 프레임 간 경계를 Stuffing으로 구분
* 전송할 수 있는 최대 크기인 MTU를 초과할 때는 Fragmentation/Segmentation 적용 필요

<br/>

* MAC (미디어 엑세스 제어) 계층
  * 물리적 영역이며, 매체 간 연결 방식을 제어. Physical Layer의 PLCP와 연결되어 있음
* LLC (논리 로직 제어) 계층
  * 논리적 영역이며, 프레임을 만듦. Network Layer와 연결되어 있음

<br/><br/>

### Layer 3. Network Layer

**역할**

* 다른 Network에 IP주소를 이용하여 패킷을 전송

* 여러개의 노드를 이용하여 경로를 찾아줌
* Routing : 네트워크 안에서 통신 데이터를 보낼 때 최적의 경로를 선택하거나 패킷을 전달하는 과정
  * 데이터 링크 계층에서 인접 노드의 물리 주소를 헤더에 첨부하여 목적지까지 전송
  * Shortest Path or Minimum time
* Logical Addressing : 상위 계층에서 받은 데이터에 목적지의 논리 주소를 헤더에 추가

**프로토콜** : IP, IPSec, ICMP, IGMP

**장비** : 라우터, Multilayer 스위치 

<br/>

* IPSec (Internet Protocol Security)
  * 각 IP패킷을 인증하고 암호화하는 IP Suite
* ICMP (Internet Contol Message Protocol)
  * IP 패킷을 처리할 때 발생되는 문제를 알려주는 Protocol
  * 목적지의 통신 상태가 비정상적인 경우에 에러를 파악하기 위해 사용
  * Unreachable, Timeout, Redirect 등 다양한 원인이 있음
  * Windows에서 통신 유무를 하기 위한 Ping도 여기에 속함
* IGMP (Internet Group Management Protocol)
  * 서브넷 간 멀티 캐스트 패킷의 목적을 관리하기 위한 Protocol
  * 호스트가 Multicast Group에 가입하거나 탈퇴하는데 사용
  * Multicast를 Group으로 관리하여 불필요한 트래픽을 줄일 수 있음

<br/><br/>

### Layer 4. Transport Layer

**프로토콜** : TCP, UDP, ECN, SCTP, DCCP







<br/><br/>

### Layer 5. Session Layer

**프로토콜** : API, Socket



<br/><br/>

### Layer 6. Presentation Layer

**프로토콜** : SSL, FTP, IMAP, SSH



<br/><br/>

### Layer 7. Application Layer

**프로토콜** : HTTP, FTP, IRC, SSH, DNS







<br/><br/>

### TCP/IP 인터넷 4계층

* 현재 수많은 프로그램의 통신 프로토콜로 TCP / IP이 사용되고 있기 때문에 OSI 7계층을  TCP/IP 4계층으로 표현하기도 하지만 수정이 필요한 표현임

  * TCP/IP 인터넷 4계층은 OSI 7계층의 하부 집합 중 하나 (네트워크 구조인 인터넷만을 기술)

  * **L1** Network Access Layer (**L1** Physical **+ L2** Data Link)
  * **L2** Internet Layer (**L3** Network)
  * **L3** Transport Layer (**L4** Transport)
  * **L4** Application Layer (**L5** Session + **L6** Presentation + **L7** Application )
