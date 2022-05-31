---
sort: 5
---

# Value Type

**Entity Type**

* @Entity로 정의하는 객체로, 식별자가 있기 때문에 데이터가 변경되어도 추적 가능

**Value Type**

* Integer나 String 같이 식별자가 없어서 값 변경시 추적 불가능
* Value Type에는 기본값 / 임베디드 / 컬렉션 값 타입이 존재

**기본값 타입 (Primitive Value Type)**

* 생명 주기가 Entity에 의존되며, 기본값 타입은 공유되지 않음
* Integer / String  같은 클래스는 복사 시, 주소값을 복사하기 때문에 공유는 가능하지만 부작용을 방지하기 위해 값은 변경할 수 없음

```java
int a = 10
int b = a
b = 20
// a = 10, b = 20
  
Integer a = new Integer(10);
Integer = b;
```



**Embedded Tyoe**

* 복합 값 타입 (Composite Value Type)이라고도 하며, 사용자가 타입을 정의할 수 있음
* Value Type으로 값 변경시 추적 불가능

* 객체와 테이블을 세밀하게 매핑할 수 있음
* 클래스에 @Embeddable을 사용하고, 멤버에 @Embedded를 사용하여 Mapping
* 하나의 Entity에서 같은 Embedded Type을 사용할 때는  @AttributeOverrides를 사용하여 Override

```java
@Embeddable
public class Address {
    private String city;
    private String zipcode;
    private String street;

    public Address(){

    }

    public Address(String city, String zipcode, String street) {
        this.city = city;
        this.zipcode = zipcode;
        this.street = street;
    }
}

public class Member {
  @Embedded
  private Peroid peroid;
  @Embedded
  private Address address;
  
  @Embedded
  @AttributeOverrides({
    @AttributeOverride(name = "city", column = @Column(name = "work_city")),
    @AttributeOverride(name = "street", column = @Column(name = "work_street")),
    @AttributeOverride(name = "zipcode", column = @Column(name = "work_zipcode"))
  })
  private Address workAddress;
}

Member member = new Member();
member.setUsername("USERNAME");
member.setAddress(new Address("city_val", "zipcode_val","street_val"));
member.setPeroid(new Peroid());

em.persist(member);
```







<div style="text-align: right"> Image ref : https://www.inflearn.com/course/ORM-JPA-Basic/dashboard</div> 





