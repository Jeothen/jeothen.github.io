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

* HTTP Body는 데이터의 컨텐츠 및 Message나 데이터를 해석할 수 있는 정보 등이 제공됨
  * 모든 HTTP Request들이 Body를 포함하는 것은 아님
    * 대부분의 GET Request는 Body를 포함하고 있지 않아서 빈 값으로 전송
    * Post인 경우, Body에 데이터를 포함하여 전송
    * Header의 Content-Type Field에 어떤 데이터 타입인지 명시
  * HTML 코드, Image, CSS, JS 코드 등이 포함되어 전송됨



**HTTP request Method**

---

**GET** : 지정된 리소스에서 데이터를 요청할 때 사용 (SELECT)

* query는 get요청의 url로 전송됨
* cache 가능하고, 브라우저에 기록이 남아있음
* URL의 길이 제한은 브라우저 종류/버전 등에 의해 달라지지만, 일반적으로 MS에서 제공하는 브라우저(IE, Edge)나 Chrome은 2048자(2MB)이고, Firefox / Safari 등은 64k 이상 지원
* 일반적으로 body를 사용하지 않고 

```apl
GET /form/1 HTTP/1.1
Host : ~
User-Agent : ~
~
```

**HEAD** : GET 요청과 동일하지만, Response의 Body가 없다

* body 외 다른 정보만 필요할 때 유용하게 사용할 수 있음



**POST** : 리소스를 생성하거나 업데이트하기 위해 서버를 데이터에 보낼 때 사용 (INSERT)

* Request요청에 포함된 Entity(Body)를 Request-URI에 정의된 Resource의 Subordinate Entity로 생성한다
  * Request-URI는 Collection-URI이다

* 일반적으로 cache 불가능하고, 브라우저에 기록이 남지 않음
  * Cache-Control-header를 이용하여 Caching을 구현하여 응답할 수는 있음 (300번대-redirect로 응답)
* URL의 길이 제한이 없다

```apl
POST /form HTTP/1.1
Host: ~
User-Agent : ~
{
	param1:value1
	param2:value2
}
```

**PUT** : 리소스를 생성하거나 업데이트하기 위해 서버를 데이터에 보낼 때 사용	(UPDATE)

* POST Method와 다르게 PUT Method는 Idempotent(멱등)함
  * PUT으로 동일한 요청을 여러번 보낼 때 동일한 결과값을 보냄
    * Resource가 존재하면 Update하고, 존재하지 않으면 Create함
  * 반면, POST Request는 동일한 요청을 보낼 때마다 resource를 생성한다.
    * primary key가 다른 데이터를 생성
    * 생성하는 data를 unique key로 설정하면 중복된 데이터 생성을 막을 수 있다.
  * Idempotent하지만, response를 cache하지 않음
* 클라이언트가 변경 대상의 Resource-URI를 지정하여 사용
  * Post는 request URI에 `/Collection URI` 까지 표현하지만, PUT은 `/Collection URI/Resource Identifier`가 포함됨

```apl
PUT /form/1 HTTP/1.1
Host : ~
User-Agent : ~
{
	param1:value1
	param2:value2
}
```

**PATCH** : PUT과 마찬가지로 데이터를 Update에 주로 사용하지만, PATCH는 변경되는 값만 보내줘도 된다.

* PUT에서 `param2:value4` 로 업데이트 하기 위해서는 `param1:value1 & param2:value4` 를 Resource-URI 주소와 보내줘야 하지만, PATCH에서는 Resource-URI에서 변경되는 값만 보내줘도 된다.
  * PUT에서 `param2:value4`만 전송하게 되면 `param1` 은 default값으로 대체됨

**DELETE** : resource를 삭제할 때 사용

* resource를 삭제하기 때문에 명확한 Resource-URI가 필요

```apl
DELETE /form/1 HTTP/1.1
Host : ~
User-Agent : ~
```



**TRACE** : 서버에 전송한 request 메시지의 복사본을 받기 위해 사용

* request가 제대로 전송되었는지 주로 디버깅 목적으로 사용됨

* target resource에 대한 경로를 따라서 message loopback 테스트를 수행
  * Message에 문제가 생겼거나 어떻게 변경되었는지 확인
* Indempotent하며 캐시 불가능한 Method
* XST (Cross Site Tracing) Attack
  * 서버에서 trace method를 지원하고 있을 때, XSS Cookie의 httponly 옵션을 우회하여 session cookie를 탈취
  * Trace Method를 허용하는 브라우저에서 Trace method를 사용하면 request message를 그대로 받아오는 것을 이용
  * 현재 대부분의 브라우저에서는 클라이언트-서버 사이에 proxy 서버가 존재하는 경우 Trace Method를 비활성화하여 사용 못하게 했음

```apl
TRACE /form
Host : ~
```



### HTTPS

* 
