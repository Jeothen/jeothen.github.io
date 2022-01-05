---
sort: 1
---

# OSI 7 Layers

상당히 요약된 내용으로 추후에 각 Layer를 Category로 하여 정리

<br />

<br />

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

**역할**

* 애플리케이션 계층과 네트워크 계층 사이에서 프로세스 간 logical communication을 제공
  * Logical Communication : 프로세스 간 직접 연결된 것처럼 통신

* end to end 통신을 다루는 Host Layers의 최하위 계층으로 신뢰성, 오류검출, 흐름제어 등을 수헹
  * 상위 계층에서 데이터의 신뢰성, 효율성 등을 고려하지 않도록 함

* source port, target port, sequence number, Ack Number 등의 데이터를 header에 붙여 세그먼트라는 패킷을 만듦

**TCP/UDP**

* TCP : 연결지향, 신뢰성 있는(Ack Number)를 순차적 통신(sequence number)을 보장하며 연결시 3way handshaking, 해제시 4way handshaking으로 동작
  * Full Duplex, Point to Point 통신
    * Full Duplex : 전송이 양방향에서 동시에 발생할 수 있음
    * Point to Point 통신 : 통신이 정확히 2개의 종단점을 가지고 있음
  * 1 : 1 통신만 지원되며, 연결된 상태에서만 데이터 전송이 가능

* UDP : 비연결 지향으로 발신자가 일방적으로 데이터를 전송
  * 빠른 속도로 데이터를 전송하지만 신뢰성 부족
  * 데이터의 순서를 보장하지 않고 잘못된 path로 전송하며 데이터 유실 가능성도 있음
    * 데이터를 정상적으로 보내지 못하는 경우, 재전송하지 않음
  * 패킷의 오버헤드가 적어 네트워크 부하는 감소

**ECN(Explicit Congestion Notification)**

* 패킷을 삭제하지 않고 네트워크 정체에 대한 알림을 받을 수 있음
* ECN 지원 엔드 포인트 간 사용할 수 있는 선택적 기능
* 정체가 있는 경우, TCP/IP 통신에서는 패킷을 삭제하고 IP 헤더에 표시하여 정체를 알려줌
* 수신자는 혼잡 표시를 발신자에게 보내 누락된 패킷을 감지한 것처럼 전송 속도를 줄임

**SCTP(Stream Control Transmission Protocol)**

* TCP/UDP와 비슷한 역할을 하며, TCP의 연결 지향 프로토콜이며 혼잡 제어를 통해 신뢰성 있는 순차적 통신을 제공하며  UDP의 스트리밍 특징을 가지고 있는 프로토콜
* Multi Homing, Multi Streaming, 3Way/4Way Handshaking	
  * Multi Hominig : 한 세션에서 다중 IP 주소를 이용하여 다중으로 접속을 유지하는 기술. path fail 시 idle 경로를 찾아 신뢰성 있는 데이터 전송
  * Multi Streaming : 한 stream의 패킷 손실이 발생해도 다른 스트림에서도 데이터를 전송하기 때문에 연속적으로 전송 가능
    * FIFO로 구성되어 있기 때문에 여러 입력 포트에서 특정 출력 포트로 큐잉되는데, 패킷 손실 때 발생하는 Head of Blocking 문제 해결

<br/><br/>

### Layer 5. Session Layer

**프로토콜** : SSH, TLS 

**역할**

* 세션의 설정, 관리 ,해제할 수 있음
* Multiplexing
  * 전송 계층에 의해 제공되는 서비스로, 1개 이상의 메시지 스트림과 논리적인 연결을 할 수 있음
    * ex) 하나의 IP주소에서 동시에 여러개의 웹 사이트를 여는 것
* Dialogue 관리
  * 토큰을 교환함으로써 Dialogue를 확인할 수 있음
    * 토큰 : 데이터 토큰, 해제 토큰, 동기 토큰 등을 수행하는 권한
* 에러 복구
  * Dialogue를 그룹화하고 에러가 발했을 때 중단된 대화 단위부터 재전송

<br/><br/>

### Layer 6. Presentation Layer

**프로토콜** : SSL, TLS, ASCII, JPEG

**역할**

* 데이터를 표현할 수 있는 방식을 결정
* 데이터를 암호/복호화, 압축 등 Application layer간 통신할 때 메시지가 동일한 의미로 전달될 수 있게 변환

**SSH, SSL, TLS에 대해서는 따로 정리**

<br/><br/>

### Layer 7. Application Layer

**프로토콜** : HTTP, FTP, IRC, DNS, SMTP, POP3, IMAP 등

**역할**

* OSI 최상위 계층으로, 응용 프로그램 단에서 사용자에게 인터페이스를 통해 통신 서비스를 제공
* 프로세스 간 통신하기 위해 설계된 전송계층 프로토콜을 이용하여 연결



HTTP (HyperText Transfer Protocol) : W3 상에서 정보를 주고받을 수 있는 프로토콜

FTP (File Transfer Protocol) : TCP/IP 프로토콜을 이용하여 서버와 클라이언트 사이의 파일 전송

IRC (Internet Relay Chat) : 텍스트 형태의 커뮤니케이션을 제공하는 프로토콜

DNS (Domain Name System) : Url을 IP 주소로 변환하는 서비스

SMTP (Simple Main Transfer Protocol) : 이메일을 전송할 때 사용하는 프로토콜

POP3 (Post Office Protocol 3) : 이메일을 수신할 때 사용하는 프로토콜

* 서버에서 클라이언트 PC로 메일을 다운로드 하는 방식

IMAP (Internet Message Access Protocol) : 이메일을 수신할 때 사용하는 프로토콜

* 이메일 서버와 동기화되기 때문에 다양한 장치에서 확인

<br/><br/>

### TCP/IP 인터넷 4계층

* 현재 수많은 프로그램의 통신 프로토콜로 TCP / IP이 사용되고 있기 때문에 OSI 7계층을  TCP/IP 4계층으로 표현하기도 하지만 수정이 필요한 표현임

  * TCP/IP 인터넷 4계층은 OSI 7계층의 하부 집합 중 하나 (네트워크 구조인 인터넷만을 기술)

  * **L1** Network Access Layer (**L1** Physical **+ L2** Data Link)
  * **L2** Internet Layer (**L3** Network)
  * **L3** Transport Layer (**L4** Transport)
  * **L4** Application Layer (**L5** Session + **L6** Presentation + **L7** Application )
