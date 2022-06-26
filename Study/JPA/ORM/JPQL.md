---
sort: 8
---

# JPQL

* JPA에서 제공하는 SQL을 추상화 한 언어
* 데이터베이스 대상이 아니라, 객체를 대상으로 쿼리 
  * 객체를 대상으로 쿼리를 작성하지만, 내부에서 SQL로 변형되어 실행됨
* Query를 String으로 작성하기 때문에 오류 발생 가능성 존재
  * Criteria나 QueryDSL 같은 빌더를 이용하여 쿼리를 Method 조합으로 사용하면 Compile 시점에 오류를 캐치할 수 있음
  * Criteria는 복잡한 Query를 작성할 때 디버깅 및 실무에서 적용하기 어려움
  * QueryDSL은 Criteria와 마찬가지로 엔터티 기반으로 쿼리를 작성할 수 있으나 단순하고 직관적임

* Native SQL을 사용하여 JPQL이 제공하지 않는 특정 데이터베이스에서만 사용하는 쿼리를 작성
* JPQL 외 JDBCTemplate / Mybatis 등을 함께 사용하여 복잡한 쿼리를 할 수도 있음

---

* JPQL은 SQL을 추상화했기 때문에 특정 DB에 의존하지 않으며, SQL로 변환하여 실행됨

* JPQL은 기본적으로 테이블의 이름이 아닌 Entity의 이름으로 접근함

**TypeClass / Query** 

* 반환 타입이 명확한 경우 Typeclass 를 사용하고, 명확하지 않을 때 Query 사용

```java
TypedQuery<Member> query1 = em.createQuery("select m from Member m", Member.class);

TypedQuery<String> query2 = em.createQuery("select m.username from Member m", String.class);
Query query3 = em.createQuery("select m.username, m.age from Member m");
```

**Single / List Result**

* ResultList는 결과가 하나 이상일 때 List를 반환하고, 없는 경우 빈 리스트를 반환
* SingleResult는 결과가 하나가 아닌 경우, Exception 발생

```java
TypedQuery<Member> query1 = em.createQuery("select m from Member m", Member.class);
List<Member> resultList = query1.getResultList();
for (Member member1 : resultList){
    System.out.println("member1 = " + member1);
}

TypedQuery<Member> query2 = em.createQuery("select m from Member m", Member.class);
Member singleResult = query1.getSingleResult();
System.out.println("result = " + singleResult);
```

* Query Tuning을 해야되는 상황이 있기 때문에 SQL과 비슷하게 작성하는 것이 좋음 (명시적 JOIN)

```java
TypedQuery<Member> query2 = em.createQuery("select m.team from Member m", Team.class); // X (묵시적 JOIN)
TypedQuery<Member> query2 = em.createQuery("select t from Member m join m.team t", Team.class);
```

**Projection Return**

* Object Type
  * Type을 정의할 수 없을 때, Object Type으로 Return 받음
  * List Generic을 Obejct로 선언한 경우 바로 Return 받아서 Object로 변환하는 과정을 생략할 수 있음
    * 패키지명을 포함한 전체 클래스를 입력해야되고, 순서와 타입이 일치하는 생성자 필요

```java
Member member = new Member();
member.setUsername("Member1");
member.setUsername("10");
em.persist(member);

em.flush();
em.clear();

// List -> Object Type
List resultList2 = em.createQuery("select m.username, m.age from Member m").getResultList();
Object o = resultList2.get(0);
Object[] res = (Object[]) o;
System.out.println("name = " + res[0]);
System.out.println("age = " + res[1]);

// Object Type
List<Object[]>resultList2 = em.createQuery("select m.username, m.age from Member m").getResultList();
Object[] res = resultList2.get(0);
System.out.println("name = " + res[0]);
System.out.println("age = " + res[1]);

// NEW Construction


public class MemberDTO {
    private String username;
    private int age;
    
    public MemberDTO(String username, int age) {
        this.username = username;
        this.age = age;
    }
}


List<MemberDTO> resultList2 = em.createQuery("select new JPQL.MemberDTO(m.username, m.age) from Member m",
                                             MemberDTO.class).getResultList();
MemberDTO memberDTO = resultList2.get(0);
System.out.println("name = " + memberDTO.getUsername());
System.out.println("age = " + memberDTO.getAge());
```

---

**Paging**

* Paging을 사용하면 데이터베이스의 종류와 관계없이 기본 SQL 문법으로 작성
* `persistence.xml` 에 설정한 Database의 종류에 맞는 Query로 변환

```java
<property name="hibernate.dialect" value="org.hibernate.dialect.Oracle12cDialect"/>  // Oracle에서 Paging을 사용

  
List<Member> resultList = em.createQuery("select m from Member m order by m.age desc", Member.class).
setFirstResult(1).
setMaxResults(10).
getResultList();

System.out.println("size = " + resultList.size());
for (Member m: resultList){
  System.out.println("Member = " + m);
}
```

**JOIN**

* JOIN을 사용할 때는 (INNER) JOIN / (LEFT) OUTER JOIN / THETA JOIN을 사용할 수 있음
* theta join은 cross join이라고도 하며, 2개의 Entity에 있는 데이터를 Cross 비교하여 결과 출력

```java
@Entity
public class Team {
    @OneToMany(mappedBy = "team")
    private List<Member> members = new ArrayList<>();
    public List<Member> getMembers() {
        return members;
    }
}

@Entity
public class Member {
    @ManyToOne(fetch = FetchType.LAZY)
    @JoinColumn(name = "TEAM_ID")
    private Team team;
    public void changeTeam(Team team){
        this.team = team;
        team.getMembers().add(this);
    }
}


Team team = new Team();
team.setName("TEAM1");
em.persist(team);

Member member = new Member();
member.setUsername("Member1");
member.setUsername("10");
member.setTeam(team);
em.persist(member);

em.flush();
em.clear();

String query = "select m from Member m inner join m.team t";  // inner join
String query = "select m from Member m left outer join m.team t"; // outer join
String query = "select m from Member m, Team t where m.username = t.name";  // theta join	
List<Member> resultList = em.createQuery(query, Member.class).getResultList();
```

* JOIN 대상 필터링 

  ```java
  select m, t from Member m LEFT JOIN m.team t on t.name = "A"
    
  String query = "select m from Member m left join m.team t on t.name = 'TEAM1'";
  ```

* 연관관계가 없는 Entity 외부 JOIN

  ```java
  select m, t from Member m LEFT JOIN Team t on m.username = t.name
  
  String query = "select m from Member m left join Team t on m.username = t.name";
  ```



**Sub query**

* JPA는 WHERE / HAVING 절에서만 Sub Query 사용 가능

  * Hibernate를 이용하면 SELECT 절에서도 사용 가능
  * FROM 절에서는 사용할 수 없음
  * Native Query나 JOIN으로 해결해야 됨
  * ALL / ANY / SOME / IN / EXISTS 등의 옵션 사용 가능

  ```java
  select (select avg(m1.age) from Member m1) as avgAge m from Member m
  ```



****

**경로 표현식**

* `.`을 이용하여 객체 그래프를 탐색

```java
select m.username // 상태 필드
from Member m
join m.team t  // 단일값 연관 필드
join m.orders o  // 컬렉션 값 연관 필드
where t.name = 'TeamA'
```

* 상태필드 : 단순하게 값을 저장하기 위한 필드
  * 경로 탐색의 끝으로 탐색이 불가능
* 연관 필드
  * 단일값 연관 필드: `@ManyToOne` , `OneToOne` 처럼 Target 대상이 Entity
    * 묵시적인 Inner Join 발생하고, 추가적인 탐색을 할 수 있음 
      * ex) `m.team.name` 
    * `select m.team from Member m`이라는 query에서 묵시적 JOIN 쿼리가 발생하므로 유지 보수에 어려움이 있음
    * DB가 큰 경우, 연쇄된 INNER JOIN이 발생하여 성능에 영향을 줄 수도 있음
  * 컬렉션값 연관 필드: `@OneToMany`, `@ManyToMany` 처럼 Target 대상이 Collection
    * 묵시적인 Inner Join이 발생하지만, 추가적인 탐색을 할 수 없음
    * 명시적인 JOIN을 사용해서 별칭을 얻은 후에 추가적인 탐색 가능
      * `select m.username from Team t join t.member m` 

**Fetch JOIN**

* FETCH를 사용하지 않고 LAZY만으로 조회하는 경우, Member에서 getteam().getname을 호출하는 시점마다 쿼리 발생

  * 처음에 Member를 가져오기 위한 쿼리 발생
  * Member1의 팀을 조회하는 경우 쿼리 발생
  * Member2는 1의 팀과 동일하고, 영속성 컨텍스트에 존재하기 때문에 쿼리 미발생
  * Member3에서 새로운 팀의 조회를 하기 때문에 쿼리 발생
  * N+1 Problem이 발생하는데, Fetch JOIN으로 해결해야 됨

  ```java
  public class Member {
      @ManyToOne(fetch = FetchType.LAZY)
      @JoinColumn(name = "TEAM_ID")
      private Team team;
  }
  
  Team team = new Team();
  team.setName("TEAM1");
  em.persist(team);
  
  Team team2 = new Team();
  team2.setName("TEAM2");
  em.persist(team2);
  
  Member member1 = new Member();
  member1.setUsername("Member1");
  member1.setTeam(team);
  em.persist(member1);
  
  Member member2 = new Member();
  member2.setUsername("Member2");
  member2.setTeam(team);
  em.persist(member2);
  
  Member member3 = new Member();
  member3.setUsername("Member3");
  member3.setTeam(team2);
  em.persist(member3);
  
  em.flush();
  em.clear();
  
  String query = "select m From Member m";
  List<Member> resultList = em.createQuery(query, Member.class).getResultList();
  for (Member member: resultList){
    System.out.println("member = " + member.getUsername() +", " + member.getTeam().getName());
  }
  ```

* Entity Fetch Join : 특정 엔터티를 조회할 때 연관된 엔터티도 함께 조회

  `select m from Member m join fetch m.team`

  * Member를 조회할 때 Team도 함께 JOIN으로 조회함
  * 이후 Member를 조회할 때 Team에 대한 데이터도 함께 들고오기 때문에 추가 쿼리가 발생하지 않음

* Collection Fetch Join: OneToMany, ManyToMany 같은 Collection 대상으로 사용

  `select t from Team t join fetch t.members` 

  * 일대다로 가져오기 때문에 중복된 데이터를 가져올 수 있음
    * JPQL의 DISTINCT를 사용하면 SQL에 DISTINCT를 추가 (DB수준), 애플리케이션 수준에서 엔터티 중복 삭제
    * 다대일에서는 중복된 데이터를 가져오지 않음
  * 조회한 Collection에는 동일한 Team을 가져올 수 있으나, 영속성 컨텍스트에는 하나만 올림
    * 하나의 영속성 컨텍스트에 두개의 Member에 대한 정보를 가지고 있음

  ```java
  String query = "select t From Team t join fetch t.members";
  List<Team> resultList = em.createQuery(query, Team.class).getResultList();
  for (Team team: resultList){
  	System.out.println("team = " + team.getName() +", members =" + team.getMembers().size());
  }
  
  
  // DISTINCT - JPA에서 중복된 Entity 추가로 삭제 진행
  String query = "select distinct t From Team t join fetch t.members";
  List<Team> resultList = em.createQuery(query, Team.class).getResultList();
  for (Team team: resultList){
  	System.out.println("team = " + team.getName() +", members =" + team.getMembers().size());
  }
  ```

* Fetch Join 대상에는 Alias를 적용할 수 없음

  * 필요한 데이터만 가져오기 때문에 누락된 데이터를 가져올 수 있으므로 쓰지 않는 것이 관례

  `select t from Team t join fetch t.members alias` 

  * 둘 이상의 Collection은 Fetch Join 할 수 없음
    * 데이터 Matching도 어렵고, 가능할 때도 조회수가 급격하게 증가함
  * Collection Fetch Join 할 때 페이징을 사용할 수 없음
    * 하나의 Entity에서 여러개의 데이터를 가져올 수 있는데, 동일한 엔터티에서 일부 데이터만 짤라서 가져오면 문제가 발생
    * `select m from Member m join fetch m.team` 과 같이 Entity의 순서를 바꿔서 다대일인 경우 페이징을 사용할 수 있음 

* Batch

  * Team을 가져올 때 Member가 Lazy Loading 상태인 경우, Member를 조회할 때마다 쿼리 발생
  * Batch를 설정하면 Lazy Loading이 설정되었을 때, List에서 한번에 Batch Size 개의 Team Entity를 한번에 가져옴
    * List가 300개 / BatchSize가 100인 경우 Team을 조회할 때 1번, 이후 3번의 쿼리가 발생하므로 N+1 Problem을 해결할 수 있음

  ```java
  @Entity
  public class Team {
      @BatchSize(size=100)
      @OneToMany(mappedBy = "team")
      private List<Member> members = new ArrayList<>();
  }
  
  String query = "select t From Team t";
  List<Team> resultList = em.createQuery(query,Team.class).setFirstResult(0).setMaxResults(2).getResultList();
  for (Team team: resultList){
    System.out.println("team = " + team.getName() +", members =" + team.getMembers().size());
    for (Member member: team.getMembers()){
      System.out.println("->Member = " + member);
    }
  }
  ```

  * `Persistence.xml` 에서 Hibernate의 default로 설정할 수도 있음

  ```xml
  <property name="hibernate.default_batch_fetch_size" value="100"/>
  ```

* Fetch Join은 객체 그래프를 유지할 때 효과적임
  * `.` 을 기준으로 객체를 찾아감
* 여러 테이블을 조인한 후 변형된 데이터가 필요한 경우, New Operation으로 DTO를 반환하는 것이 좋음

**Named Query**

* 미리 이름을 정의하여 사용하는 JPQL로 정적쿼리에 사용 가능
  * 정적 쿼리에 사용하기 때문에 애플리케이션 로딩 시점에서 검증할 수 있음
  * Entity에서 정의할 수도 있지만, xml 파일에서도 정의할 수 있음

```java
@Entity
@NamedQuery(
        name = "Member.findByUsername",
        query = "select m from Member m where m.username = :username"
)
public class Member {
}


Member member1 = new Member();
member1.setUsername("Member1");
member1.setTeam(team1);
em.persist(member1);


List<Member> resultList = em.createNamedQuery("Member.findByUsername", Member.class)
  .setParameter("username", "Member1")
  .getResultList();

for (Member member: resultList){
  System.out.println("member = " + member);
}
```

**Bulk Operation**

* 한번의 쿼리로 여러 엔터티의 값을 변경함
* 영속성 컨텍스트를 무시하고 DB에 바로 쿼리 발생
  * Bulk 연산 실행한 후 영속성 컨텍스트 초기화 필요

```java
// flush() 자동 호출됨 - commit 또는 쿼리가 발생할 때 flush() 실행

int res_cnt = em.createQuery("update Member m set m.age = 20")
	.executeUpdate();
// 영속성 컨텍스트에는 age = 20이 반영되어 있지 않음 / DB에는 20으로 update 되어 있음

em.clear();  // 영속성 컨텍스트를 초기화
Member findmember = em.find(Member.class, member1.getId()); // DB에서 값을 가져와서 영속성 컨텍스트에 저장
System.out.println("findMember = " + findmember);
```

