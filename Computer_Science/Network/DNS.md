---
sort: 7
---

# DNS

* 도메인 네임 시스템(Domain Name System)은 분산 데이터베이스 시스템으로 Domain Name Space, Name Server, Resolver로 구성되어 있음
* Domain Name Space
  * 계층 구조로 구성된 데이터베이스
  * 최상위 DNS Root가 존재하고 Trie 구조로 모든 호스트가 연결되어 있음
    * 상위 노드에 label을 Insert하는 방식으로 구성
  * TLD (Top-Level Domain)
* Name Server
  * 전세계적으로 분산되어 있어, 도메인 정보를 저장 및 관리하는 DNS 서버로 도메인 이름을 IP주소로 변환하는 Service 제공
  * 클라이언트의 DNS Query / Name Server 간 Query에 대한 응답 수행
* 신뢰할 수 있는 DNS
  * 신뢰할 수 없는 DNS 서버는 피싱, 해킹 등의 위험이 있으므로, 신뢰할 수 있는 DNS를 이용하는 것이 좋음
  * KT DNS, Google Public DNS, CISCO 등이 신뢰할 수 있는 DNS에 해당하며, 도메인에 대한 최종 권한을 가지고 있음
  * Recursive DNS NameServer에 IP주소가 포함된 응답을 보낼 의무가 있음

<br/>

**Type**

* **DNS Resolver** (DNS Recursor)
  * 재귀 DNS 해석기라고도 하며, DNS 쿼리를 날렸을 때 가장 먼저 진행하는 process
  * 클라이언트 요청을 Name Server로 Query 형태로 변환하여 전달하고, Name Server로부터 받은 응답을 클라이언트에게 제공
  * IP주소와 호스트 이름을 매핑하기 위해 1개 이상의 Name Server의 정보를 이용
  * UNIX에서는 `/etc/resolv.conf` 에 설정
* **Root Name Server**
  * UDP 패킷의 크기 제한으로 인해 13개의 Root NameServer가만 존재
  * TLD가 어떤 NameServer에 있는지 알고 있기 때문에, Resolver로부터 쿼리 요청이 오면 해당하는 NameServer의 이름, 주소 등을 제공
* **TLD Name Server**
  * Root 바로 아래 존재하는 최상위 도메인으로, URL의 마지막 '.' 이후에 있는 도메인 확장자에 있는 모든 도메인의 Host Name / IP Address 정보를 가지고 있음
  * TLD NameServer는 ICANN의 지사인 IANA가 관리하며, TLD를 2가지로 구분
    * ccTLD (Country Code Top-Level-Domain) : '.kr', '.uk' 같은 국가별로 운영하는 최상위 도메인
    * gTLD (generic Top-Level-Domain) : '.com','.org' 등과 같이 국가가 운영하지 않아, 어떤 국가의 어떤 이용자도 등록 가능
* **Authoritative Name Server**
  * TLD NameServer로부터 도메인에 대한 정보를 제공 받은 후 Authritative NameServer에 매핑되는 IP Address에 새로운 쿼리
  * '.' 단위로 Authoritative 주소가 구분되어 있으며, 이전에 받은 IP Address를 이용하여 재귀로 Authoritative NameServer에 쿼리
  * 최종 목적지의 IP를 획득하게 되면, Resolver로 응답을 하며, DNS Process가 종료됨
  * Primary Server와 Second Server가 존재하며, Primary Server에서는 Zone의 모든 Record를 최신 버전으로 관리해주고 Second Server에서는 Primary Server를 Backup

**Recursive DNS PROCESS**

* 캐싱되지 않은 일반적인 DNS를 조회할 때 아래와 같은 Process로 진행
* 재귀를 통해 얻은 IP 주소를 로컬 캐시에 저장하여 NameServer의 부하를 줄여줌

![DNS](./Img/DNS.png)

<div style="text-align: right"> Image ref :https://network.cmu.ac.th/wiki/index.php/Introduction_to_DNS</div>

