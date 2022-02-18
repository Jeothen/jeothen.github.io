---
sort: 12
---

# Cookie & Session

* HTTP Protocol의 특성 중 비연결성(Connectionless)과 무상태(Stateless)를 해결하기 위해 Cookie와 Session을 도입
  * 비연결성 : Client의 요청에 대한 Server의 응답이 끝나면 통신을 끊어버리는 성질
  * 비상태성 : 통신이 지속되지 않으면 Server는 Client의 이전 상태를 보존하지 않아서 식별할 수 없음

### Cookie

* Client가 웹 사이트에 접속할 때, Local PC에 Disk에 저장되는 작은 파일
  * Client의 State를 로컬 PC에 저장 및 참조
  * 사이트 방문에 대한 정보를 저장하여 다음번에 방문할 때 간편하고 유용하게 사용
* Client가 웹사이트를 방문할 때마다 새로운 정보로 Update
* Domain 및 브라우저마다 저장하는 쿠키가 다르기 때문에, 다른 Domain이나 브라우저에서 사용한 쿠키를 사용할 수 없음
* 서버에서 관리하는 것이 아니라 Local PC에서 관리하기 때문에 보안에 취약함
* 웹 브라우저마다 호환이 되지 않으며, 사용할 수 있는 Cookie의 갯수 및 크기가 제한적
* **구성요소**
  * Key : Cookie를 식별하는 데 사용되는 이름
  * Value : Cookie에 저장된 값
  * Expires : Cookie의 유지 시간. Default 시 Session Cookie로 취급하여 브라우저 종료시 파기
  * Domain : Cookie를 전달할 Domain을 지정. Default 시 Cookie를 생성할 때 위치한 Domain(현재 문서)으로 지정
  * Path : Cookie Header를 전송하기 전, 요청된 Resource가 있어야 하는 URL 경로. Default 시 현재 문서의 경로로 지정
  * Secure : SSL을 사용하는 HTTPS Protocol 사용할 때만 Cookie를 전송

* **Process**
  * Client가 웹 사이트에 접속하면서 데이터 요청
  * Server에서 Cookie를 생성하고, HTTP Header를 통해 Cookie를 전송
  * Clinet는 Local PC에 응답받은 Cookie를 저장
  * 이후에 Client가 웹 사이트에 접속 시 Cookie 정보를 HTTP Header에 포함시켜서 전송
  * 변경점이 있는 경우 Cookie 업데이트 진행

* **종류**
  * Session Cookie : 설정된 Expire date 내에서는 Memory에 Cookie를 저장하지만, 브라우저가 종료되면 파기
  * Persistent Cookie : 설정된 Max-Age 내에서 Disk에 파일로 저장하고, 브라우저가 종료되더라도 유지
  * Secure Cookie : SSL을 사용하는 HTTPS Protocol에서만 사용되고, Cookie 또한 암호화되어 제3자가 확인할 수 없음
  * HTTP Only Cookie : CSS 공격을 대비하기 위해 브라우저에서 Cookie로 접근할 수 없게 함

<br/>

### Session

* Cookie와 마찬가지로 데이터를 저장하지만, Local PC가 아니라 서버측에서 관리
  * Local PC에서는 SessionID만 보유하고 있기 때문에 보안성 우수
* Session은 브라우저 종료 시 파기
* SessionID를 이용하여 브라우저에 요청해야 되기 때문에, Local PC에서 사용하는 Cookie보다는 속도가 느림
* Cookie는 Text 형식으로 데이터를 저장하지만, Session은 객체로 저장
* Cookie와 다르게 사용할 수 있는 Session의 갯수 제한이 없음

* 서버에 정보를 저장하기 때문에 세션이 많아질수록 부하 증가

**Process**

* Client가 Server에 요청하면 Client에 대한 정보를 Update
* SessionID가 없는 경우, SessionID를 생성하고 Cookie로 응답
* Client는 SessionID를 Cookie로 저장하고, 이후에 다시 요청할 때 SessionID를 Server 함께 전달
* Server에서는 SessionID를 이용하여 Client의 정보를 활용

<br/>
