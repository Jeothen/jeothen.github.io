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



* 기본값 타입인 경우 =으로 값을 복사하면 새로운 메모리에 저장
* 객체 타입의 경우 = 으로 값을 복사하면 주소값만 복사하는 복사 참조가 발생함
* 객체 타입을 수정할 수 없는 불변 객체로 설계하면 Side-Effect를 방지할 수 있음
  * Setter를 제거하여 값을 생성자에서만 값을 지정
  * 값을 변경할 때는 새로운 객체를 만들어야 됨

```java
Address address = new Address("city_val", "zipcode_val", "street_val");
Member member1 = new Member();
member1.setUsername("USERNAME");
member1.setAddress(address);
member1.setPeroid(new Peroid());
em.persist(member1);

Address address2 = new Address(address.getCity(), address.getZipcode(), address.getStreet());
Member member2 = new Member();
member2.setUsername("USERNAME2");
member2.setAddress(address2); // address1이 들어가는 순간, 객체 참조가 발생하여 값을 공유함
member2.setPeroid(new Peroid());
```

* 기본값 타입은 동일성 비교 (identity,  `==` 비교)를 이용하여 비교할 수 있지만, 객체 타입에서는 동일한 value가 저장되어 있더라도 `==` 비교를 할 수 없음
  * 객체 타입은 동등성 비교(equivalanc, `equals()` ) 를 사용
  * equals()도 동일성 비교를 기본으로 하기 때문에, equals()를 생성하면 Overriding해서 사용함

```java
public class Address {
  
   @Override // equals() 생성
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Address address = (Address) o;
        return Objects.equals(city, address.city) && Objects.equals(zipcode, address.zipcode) && Objects.equals(street, address.street);
    }
}

address1.equals(address2); // True를 반환함
```



**Value Type Collection**

* 값 타입 컬렉션은 값 타입을 하나 이상 저장할 때 사용
* 컬렉션을 저장하기 위해서는 별도의 테이블이 필요하고, @JoinColumn 어노테이션으로 외래키 매핑

* Collection Type이 아니라, 단일한 자료형을 갖는 경우, @Column(name) 어노테이션을 사용할 수 있음
  * FAVORITE_FOOD Table을 생성 (MemberID - Food_Name)
  * ADDRESS Table에 MemberID - Collection(CITY - STREET - ZIPCODE) 저장됨
* 생명주기가 member에 소속되어 관리됨
  * 영속성 전이(CasCade) + 고아객체 제거 기능을 필수로 가지고 있음
* @ElementCollection(fetch)는 Default가 LAZY라 지연로딩 전략을 사용함
* 수정할 땐, Value Type이므로 값을 변경하지 않고 새로운 인스턴스로 덮어써야됨
  * 변경할 때, 주인 Entity와 연관된 모든 데이터를 삭제한 후 현재값을 다시 저장
    * @orderColumn(name) 어노테이션을 사용하면 delete가 아니라 update query 발생하지만, 정확한 데이터를 입력하지 않았을 때 유지보수가 어려움
    * Table의 모든 Column을 묶어서 PK를 구성해야됨
* 실무에서는 값타입 데이터보다는 1:N 관계를 사용하는 게 좋음
  * CASCADE ALL 및 고아객체를 사용하고, @OneToMany 단방향으로 설정
  * 변경하기 위해 생성자 parameter를 만든 후 새로운 인스턴스로 덮어씀
  * 일대다 단방향 Mapping인 경우, Update query 발생 (다른 Table에 외래키가 존재하기 때문)

```java
@ElementCollection
@CollectionTable(name="FAVORITE_FOOD", joinColumns = @JoinColumn(name="MEMBER_ID")) // 외래키로 mapping
// @OrderColumn(name = "address_history_order")
@Column(name="FOOD_NAME") // String 단일 타입이라서 Column 이름을 정의할 수 있음
private Set<String> favoriteFoods = new HashSet<>();


@ElementCollection
@CollectionTable(name="ADDRESS", joinColumns = @JoinColumn(name="MEMBER_ID"))
private List<Address> addressesHistory = new ArrayList<>();

------------------

Member member = new Member();
member.setUsername("member1");
member.setAddress(new Address("city1", "street1", "zipcode1"));

member.getFavoriteFoods().add("Food1");
member.getFavoriteFoods().add("Food2");
member.getFavoriteFoods().add("Food3");

member.getAddressesHistory().add(new Address("city2", "street2", "zipcode2"));
member.getAddressesHistory().add(new Address("city3", "street3", "zipcode3"));

em.persist(member);

/// EDIT

Address addr = findmember.getAddress();
findmember.setAddress(new Address("new City",addr.getStreet(),addr.getZipcode()));

findmember.getFavoriteFoods().remove("Food1"); // String 자체가 값 타입이므로 제거 후 새로 등록
findmember.getFavoriteFoods().add("newFood1");
```





<div style="text-align: right"> Image ref : https://www.inflearn.com/course/ORM-JPA-Basic/dashboard</div> 





