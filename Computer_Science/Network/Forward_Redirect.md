---
sort: 8
---

# Forward & Redirect

* Forward와 Redirect는 작업 중인 페이지 같은 Resource를 다른 URL로 전속시키는 기술

### Forward

* Client가 Server에 요청했을 때 리소스의 변경이 필요한 경우, 데이터의 변경 없이 다른 URL에 Request를 전달
* 전달받은 Request를 Client에게 Response하지만, Client 입장에서는 내부적인 Forward를 확인할 수 없음
  * Request / Response 객체를 공유
* 동일한 Web Container에 있는 Resource 간 Forward 가능
* Session의 변화가 불필요한 조회의 경우 Forward를 사용하는 것이 적합

![Forward](./Img/Forward.png)

<div style="text-align: right"> Image ref : http://www.noobyard.com/article/p-nvtmjjiu-qp.html </div>

<br/>

### Redirect

* Client가 Server에 요청했을 때 Resource의 URL이 일치하지 않으면 Client에게 Redirect 요청
  * Redirect 요청에는 URL에 대한 정보가 들어있음
* Client는 Redirect에 포함된 URL로 Request
  * 처음 Request 했던 객체는 회수되어 더 이상 사용할 수 없음
    * 의도적인 새로고침(Request)를 수행할 때, 이전의 Request가 회수되기 때문에 중복으로 작업하지 않음
    * Forward의 경우, 지속적인 요청으로 중복으로 Request 작업을 수행

* Session의 변화가 필요한 추가 / 삭제 / 변경의 경우, Redirect가 적합



![Redirect](./Img/Redirect.png)

<div style="text-align: right"> Image ref : http://www.noobyard.com/article/p-nvtmjjiu-qp.html </div>
