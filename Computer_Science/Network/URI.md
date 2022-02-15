---
sort: 9
---

# URI & URL & URN

### URI

* 통합 자원 식별자 URI (Uniform Resource Identifier)로 인터넷 상의 Resource를 나타내는 유일한 주소
* 인터넷에서 요구되는 기본 사항으로, 인터넷 프로토콜과 항상 같이 사용됨

### URL

* 통합 자원 지시자 URL(Uniform Resource Locator)로 일반적으로 인터넷 사이트 도메인을 의미
  * 웹 주소뿐만 아니라, 컴퓨터 네트워크의 자원을 모두 나타낼 수 있음
* 주소에 접속하기 위해서는 주소와 동일한 프로토콜을 사용해야 됨 (HTTPS / FTP 등)
* URL에서 사용하는 Parameter를 URL Parameter(or Query Parameter)라고 함
  * URL 주소에서 `?` 이후에 사용하는 문자열

```asp
FTP : ftp://jeothen:1234@192.168.0.1:8081/D:/~
HTTPS: https://jeothen.github.io
```

### URN

* 통합 자원 이름 URN(Uniform Resource Name)이며 Resource를 이름을 기준으로 식별
* URL과 다르게 Resource의 위치가 변경되더라도 영향을 받지 않음
* 프로토콜을 사용하지 않음 (isbn / tel 같이 이름을 기준으로 고유하게 식별할 수 있을 때 사용)

```asp
URN : urn:isbn:123456767 
```



![URI](./Img/URI.png)


