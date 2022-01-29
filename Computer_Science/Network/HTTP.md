---
sort: 2
---

### HTTP

* World Wide Web에서 주고 받을 수 있는 HyperText Transfer Protocol이다.
* 클라이언트와 서버 사이에 간 통신하는 request / response Protocol
  * request : Client -> Server로 전달하는 메시지로 Server에 동작을 발생시킴
  * response : Request에 대한 Server의 내부동작 후 Client로 전달하는 메시지 
* HTML 같은 리소스를 가져올 수 있는 프로토콜
  * HTTP를 통해 전달되는 자료는 URL을 통해 조회 가능하다
* HTTP의 General / Entity / Request / Response Header 등이 있다.
  * General Header는 Date / Connection / Cache-Control 등의 값을 설정하고, Request / Response Message에서 모두 사용할 수 있다.
  * Entity Header는 Content-Type/Language/Encoding/Length 등의 값을 설정하고, Request / Response Message에서 모두 사용됨
  * Request Header는 Request Message에서만 사용되며, HOST(domain-Name) / User-Agent / Accept (File Type) / Cookie / Origin 등의 값을 포함하고 있다.
  * Response Header는 Response Message에서만 사용되며, Server / Set-Cookie / Age / Access-Control-Allow-Origin / Allow (Http Method) 등의 값을 포함하고 있다.



**HTTP Method**

* GET
* POST
* PUT
* DELETE
* HEADER
* TRACE



### HTTPS

* 
