---
sort: 1

---

# OOP(Object Oriented Programming)

Spring은 객체지향 언어가 가진 특징을 살려주는 프레임워크

객체지향은 다형성, 추상화, 상속, 캡슐화 4가지가 주요 특징

* 역할과 구현으로 구분하여, Client는 역할(Interface)만 알고 있고 내부 구현(Class)을 몰라도 됨

* 구현 객체가 변경되더라도 Interface가 동일하면 상관 없기 때문에 확장 가능한 설계가 가능

**다형성 (Polymorphism)**

* 동일한 이름의 Method를 이용하여 다른 결과를 만들어내어 확장성, 유연성을 제공
* Overloading은 컴파일 시점에, Overriding은 런타임시점에 Method가 결정됨

**추상화 (Abstraction)**

* 공통된 특징을 추출하여 Interface와 구현을 분리함
* 하나 이상의 Abstract Method를 가진 클래스를 추상클래스라고 하며, 추상클래스를 상속받는 구현클래스에서 추상 메서드를 구현해줘야 Instance로 만들 수 있음
  * 추상클래스로 객체를 생성할 수 없음
  * Abstract method는 C++의 순수가상함수와 비슷한 기능
* 상속 관계에서 상위 클래스일수록 추상화 되어있고, 하위 클래스일수록 세분화 되어있음

**상속(Inheritance)**

* 부모클래스의 기능을 자식클래스가 물려 받음
* 코드를 재사용하여 중복을 피할 수 있으나, 부모클래스의 불필요한 기능이 포함되기도 함
  * 코드의 재사용으로 인해 클래스 간 결합도가 높아져 수정에 어려움이 발생할 수도 있음
  * 일반적으로`Is-a` 관계가 충족될 때 효율적으로 사용할 수 있음

**캡슐화(Capsulation)**

* 연관된 변수와 함수를 클래스 단위로 묶어서 객체의 기능을 외부로부터 보호함
* default / private / protected / public 4가지 접근지정자(access modifier)가 있음
  * 동일한 패키지인지, 상속을 받는 관계인지 등에 따라 접근할 수 있는 범위를 제한할 수 있음



## SOLID

**SRP(Single Responsibility Principle)**



**OCP(Open Closed Principle)**



**LSP(Liskov's Substitution Principle)**



**ISP(Interface Segregation principle)**



**DIP(Dependency Inversion Principle)**

