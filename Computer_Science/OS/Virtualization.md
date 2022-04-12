---
sort: 14
---

# Virtualization

### Host 가상화

* 



![HOST_OS_Virtualization](./Img/HOST_OS_Virtualization.png)

<div style="text-align: right">Image Ref : https://www.researchgate.net/figure/Full-Virtualization-18_fig1_350400540 </div>

**Process 가상머신**

* 



### Hypervisor 가상화

* 하드웨어 가상 머신이라고도 하며, 물리적 컴퓨터와 동일한 환경을 소프트웨어로 구현하여 다중화(Multiplex)한 것
* 단일 호스트(물리적 컴퓨터)의 리소스를 가상으로 공유하기 때문에 게스트는 리소스가 있는 것으로 판단하고 독립적으로 프로그램을 실행할 수 있음
* 하이퍼바이저라는 소프트웨어 계층을 이용하여 운영 체제와 가상 머신의 리소스를 분리하여 VM을 생성 및 관리
  * 게스트의 커널 요청을 번역하여 H/W가 작업할 수 있게 지원
* 하이퍼바이저가 모든 명령을 처리해야 되기 때문에 효율 및 성능 저하 발생

![Hypervisor](./Img/Hypervisor.png)

<div style="text-align: right">Image Ref : https://www.researchgate.net/figure/OS-Layer-Virtualization-18_fig2_350400540</div>



**전가상화(Full Virtualization)**

* H/W를 가상화하여 
* dasdas

**반가상화(Para Virtualization)**

* asdasd
* asdasd

![Hypervisor_Full_Para](./Img/Hypervisor_Full_Para.png)

<div style="text-align: right">Image Ref : https://pediaa.com/what-is-the-difference-between-full-virtualization-and-paravirtualization-in-cloud/</div>



### Container 가상화

* Hypervisor 기반의 가상화에서 

![Container](./Img/Container.png)

<div style="text-align: right">Image Ref : https://www.researchgate.net/figure/Hypervisor-based-vs-Container-based-Virtualization_fig2_320223370 </div>

