---
sort: 11
---

# Memory

주기억장치를 의미하는 메모리는 일반적으로 휘발성 메모리인 RAM(Random Access Memory)을 표현할 때 사용됨

* Memory operand : Load-Store 구조로, Register operand를 위해 Memory의 데이터를 Register로 Load 및 operating하고 다시 Memory에 Store

메모리 Allocation에는 Placement(Where? Disk to Memory), Fetch(When? Disk to Memory),Replacement(Not Allocated, Which Process Removed from the Memory) 3가지 운영정책이 있음

32bit/64bit은 Word Size를 의미하는데, 32bit System은 Register에서 데이터 처리 단위가 32bit이고, 64bit System은 Register에서 데이터 처리 단위가 64bit임. 

메모리 주소 모드는 바이트 당 주소를 하나 할당하는 방식으로 동작하기 때문에 32bit와 64bit에서 사용할 수 있는 메모리 영역이 다름

* 64bit OS인 Windows10의 인식 가능 메모리는 128GB ~ 6TB까지 여러가지 버전이 있음
  * 이론상으로는 $$2^{64}$$byte = 18.4Eb까지 인식할 수 있지만, 메인보드에서 지원하는 범위까지 인식할 수 있음
* 32bit Application의 최대 사용 가능 메모리는 4GB($$2^{32}$$ byte)
  * 4GT : 일반적으로 Process에게 할당해주는 가상 메모리는 Kernel 영역 2GB, User 영역 2GB을 사용하는 4GB(/2GB) 로 사용하지만, 사용자 설정에 따라 Kernel 영역 1GB, User 영역 3GB를 사용하는 4GB(/3GB)를 사용할 수 있음
  * 실제 사용할 수 있는 메모리를 4GB보다 적은데 Memory Section이 Memory-Mapped Interface를 위해 별도로 설정됨
  * PAE : 리눅스 Kernel에서 PAE(Physical Address Extension)를 지원하는 버전에서는 32bit System을 36bit까지 확장할 수 있어서 최대 64GB 메모리에 접근할 수 있음 (Windows에서는 128GB까지 가능한 OS도 있다고 함)
    * OS가 PAE Mode를 사용할 때만 가능하며, 이때 Virtual Memory의 Address에서 PDPT(Page Directory Pointer Table)이 추가됨

**MMIO**

* 메모리 맵 입출력(Memory-mapped I/O) 

**Endian**



### Virtual Memory

* 프로그램이 실행될 때, CPU에 의해 Logical Address가 생성됨

  * Logical Address는 물리적으로 존재하지 않기 때문에 Virtual Address라고 하며, 메모리 위치를 참조하는데 사용됨

  * 각 프로그램은 Entry Point를 가지고 있으며, MMU에서 Logical Address + Entry Point = Physical Address를 계산

* Physical Address는 





![MMU_Virtual](./Img/MMU_Virtual.png)

<div style="text-align: right">Image Ref : https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-004-computation-structures-spring-2017/c16/c16s1/</div>







### Fragmentation 

* 메모리 단편화





### Paging



### Segmentation



### Memory Pool





