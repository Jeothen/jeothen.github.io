---
sort: 2
---

# Key Mapping

**Entity**

* @Entity

  * JPA에서 테이블과 Mapping 할 엔터티 클래스는 @Entity 어노테이션을 붙여야 함

* @Table

  * 엔터티와 매핑할 데이터베이스의 테이블을 지정

  * @Table이 생략되는 경우, Entity와 동일한 이름의 Table과 매핑됨

```java
@Entity
@Table(name="db_tbl")
public class member{
  
}
```

**DDL**

* 데이터베이스 스키마를 자동으로 생성할 수 있음

* JPA를 사용하기 위해 정의한 `persistence.xml` 파일 정의에서 value에 값 대입

  ```xml
  <property name="hibernate.hbm2ddl.auto" value="none" />
  ```

  * create : 기존 테이블을 삭제 후 다시 생성 (Drop / Create)
  * create-drop : create 진행 후 종료 시점에 Table을 Drop
  * update : Filed에 변경이 있을 때, 변경된 내용만 반영 (Alter)
  * validate : Entity와 테이블의 매핑이 제대로 되었는지 확인

* 운영 서버에서는 validate나 해당 기능을 사용하지 않는 것이 안전함

**Filed & Column**

* Cloumn과 Mapping 할 Filed에 대한 Annotation을 정의
* @Column
  * name, insertable/updatable, nullable 등 다양한 옵션이 있음
* @Temporal : 날짜 / 시간 관련 Mapping
  * java8 이후로 localdate/localdatetime을 지원하기 때문에 ``private LocalDate`로 정의하고 어노테이션은 사용하지 않음
* @Enumerate : enum 타입을 Mapping
  * default가 ORDINAL이지만 enum에 변경이 있는 순간 DB 관리가 어려워지기 때문에 , STRING TYPE으로 사용 권장
* @Lob : Large Object의 줄임말로, Byte Type인 Blob과 문자열 Type인 CLob으로 구분됨
  * 이미지 등 파일 형태를 주로 Lob 어노테이션으로 정의
* @Transient : 특정 Filed를 Mapping하지 않을 때 사용

**Primary Key**

* @Id : 기본키를 직접 할당하는 경우 @Id 어노테이션 사용

* @GeneratedValue : 대리키 사용 방식으로 자동으로 생성함

  ```java
  @GeneratedValue(strategy = GenerationType.TYPE)
  // TYPE에는 AUTO / IDENTITY / TABLE / SEQUENCE가 존재함
  ```

  * IDENTITY
    * MySql, SQL Server 등에서 사용하며 기본키 생성 방법을 데이터베이스에 위임
    * IDENTITY 전략은 persist() 시점에서 Insert 쿼리를 발생시킴
      * 일반적으로 persist 시점에 1차 캐시에 저장하고 Commit() 시점에서 쿼리 발생시킴
      * IDENTITY는 DB에서 KEY를 할당하기 때문에 Insert한 후 DB에서 KEY를 받아와서 사용할 수 있음
    * 여러 쿼리를 모아서 한번에 commit하는 쓰기 지연을 사용하지는 못함
  * TABLE
    * Key를 생성하는 테이블을 만들어서 사용하지만 여러 자식 테이블을 조회할 때 성능이 느려서 운영에서 잘 사용하지 않음
    * @TableGenerator 어노테이션을 사용하여 DB에 Table을 생성하기 때문에 다른 DB 시스템에서도 사용할 수 있음
    * 생성된 Table에서 Next Value로 PK 값을 지정
  * SEQUENCE
    * Oracle, Postgre 등에서 사용할 수 있는 데이터베이스 Sequence 기능을 사용
      * 유일값을 생성해주는 Sequence 객체를 만들어서 PK 값을 가져옴
    * @SequenceGenerator 어노테이션을 사용하여 Sequence를 생성할 수 있음
      * AllocationSize를 이용하여 한번에 가져오는 key 갯수를 조정하여 발생하는 쿼리를 줄일 수 있음
    * @Sequence 어노테이션에서 `generator=` 값에 SequenceGenerator에서 생성한 Sequence를 매핑
    * persist() 시점에서 call next value를 호출하여 DB에서 PK값만 얻어와서 1차 캐시에 객체를 저장함
    * 여러 쿼리를 모아서 한번에 commit 하는 쓰기 지연을 사용할 수 있음
  * AUTO : 위 3가지 방식 중 자동으로 선택해서 사용

