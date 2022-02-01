---
sort: 4
---

# Network Class

* IPv4 주소에서 제공하는 네트워크 주소(약 41억9천개)가 고갈되면서 IPv6로 조금씩 전환되고 있음
* 기존에 구축된 인프라를 이용하기 위해서 클래스라는 이름으로 네트워크를 나눔
* IPv4에서 IP 주소는 네트워크 주소와 호스트 주소의 결합으로 구성됨
  * 네트워크 주소 : 인터넷 상에서 네트워크를 구분
  * 호스트 주소 : 특정 네트워크 내에서 존재하는 기기들을 구분
* 32비트 내에서 몇가지 클래스가 존재하며 네트워크 주소와 호스트 주소의 범위가 다름

| 클래스 | 할당 가능 비트수                   | IP주소의 첫번째 옥텟의 범위 (32bit) | IP Address 범위           |
| ------ | ---------------------------------- | ----------------------------------- | ------------------------- |
| A      | $$2^7$$ = 128                      | 0xxxxxx (0~127)                     | 0.0.0.0~127.255.255.255   |
| B      | 2<sup>14</sup>= 16384              | 10xxxxxx  (128~191)                 | 128.0.0.0~191.255.255.255 |
| C      | 2<sup>21</sup> = 2097152           | 110xxxxx  (192~223)                 | 192.0.0.0~223.255.255.255 |
| D      | 2<sup>28</sup> (MultiCast Address) | 1110xxxx  (224 ~ 239)               | 224.0.0.0~239.255.255.255 |
| E      | Reserverd Address                  | 1111xxxx  (240~255)                 | 240.0.0.0~255.255.255.255 |

* A/B/C 클래스의 호스트주소에서 0/1 bit으로 채워진 주소는 사용하면 안 됨
  * A클래스 기준, 0.0.0 은 현재 네트워크 주소이고  255.255.255 는 브로드캐스트 주소이다.

**A클래스**

* 대규모 네트워크 환경에서 사용
* Network 대역 : 8bit / Host 대역이 24bit이므로 호스트 수는 (2<sup>24</sup> = 16777216)-2 가지
* Default Subnet Mask : 255.0.0.0

**B클래스**

* 중간 규모의 네트워크 환경에서 사용
* Network 대역 : 16bit / Host 대역이 16bit이므로 호스트 수는 (2<sup>16</sup> = 65536)-2 가지
* Default Subnet Mask : 255.255.0.0

**C클래스**

* 소규모 네트워크 환경에서 사용
* Network 대역 : 24bit / Host 대역이 8bit이므로 호스트 수는 (2<sup>8</sup> = 256)-2 가지
* Default Subnet Mask : 255.255.255.0

**D클래스 / E클래스** 

* ABC 클래스와는 다른 용도로 사용되며, 일반 IP주소처럼 사용할 수 없는 특수용도 IP주소임
* 네트워크 / 호스트 주소의 구분이 없음
* D클래스
  * MultiCast를 위해 존재하는 클래스
* E클래스
  * 연구용으로 유보되어 있음 (Reserved Class)