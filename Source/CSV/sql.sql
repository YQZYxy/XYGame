show databases; create database if not exists Name;  drop database if exists Name; select database(); show tables; show create table Name; desc Name;
 --ALTER TABLE 表名 ADD 字段名 类型 (长度) [ COMMENT 注释 ] [ 约束 ];   --ALTER TABLE 表名 CHANGE 旧字段名 新字段名 类型 (长度) [ COMMENT 注释 ] [ 约束 ];
alter table (emp) ADD (Name) (Tapy) COMMENT 'Name';   ALTER TABLE emp CHANGE nickname username varchar(30) COMMENT '昵称';

--删除-                                    --修改表名- 
ALTER TABLE 表名 DROP 字段名;               ALTER TABLE 表名 RENAME TO 新表名;
--表重命名
alter table emp rename to employee;
--增
INSERT INTO emp(id, workno, name, gender, age, idcard, entrydate, username) 
VALUES (3,1,'ARXH', '男', 50, '452702200001158250', '2023-7-10', 'yqzy');
INSERT INTO emp
VALUES (3,1,'ARXH', '男', 50, '452702200001158250', '2023-7-10', 'yqzy'),
(3,1,'ARXH', '男', 50, '452702200001158250', '2023-7-10', 'yqzy');
--改
update employee set name = 'yqzy' where id = 3;
UPDATE employee set name = 'xiaoyu' , gender = '女' , age= '18' where id = 3;
update employee set entrydate = '1949-10-1';
--删
delete from employee WHERE id = 1;
DELETE from emp; 
drop table employee;

SELECT a.money from account a, account b WHERE a.money <=b.money GROUP BY a.money having count(DISTINCT b.money) = 2;
SELECT a.money ,count(DISTINCT b.money) from account a, account b WHERE a.money <=b.money GROUP BY a.money;

------DQl
--查指定字段                           --所有                   --别名     as '工作地址'                        --去重   DISTINCT distinct
select name, workno, age from emp;     select * from emp;       select workaddress as '工作地址' from emp;      select DISTINCT workaddress as '工作地址' from emp;
--**条件查询**  SELECT 字段列表 FROM 表名 WHERE 条件列表 ;
--查询空    is NULL  或非空     is not NULL            --区间     between and                                --在in之后的列表中的值，多选一  in(15 , 20, 30)               
select * from emp where idcard  is not NULL ;         select * from emp where age between 15 and 20;        select * from emp where age in(15 , 20, 30);
--模糊匹配(_匹配单个字符, %匹配任意个字符)  LIKE 占位符          --查询身份证最后一位为x        LIKE '%X'  或者  LIKE '________________X'
select * from emp where name LIKE '__';                          select * from emp where idcard LIKE '%X';  
--**聚合**  SELECT 聚合函数(字段列表) FROM 表名 ;
--统计字段数量,不计算NULL              --字段平均                      --最大max 最小min               --字段求和 sum()
select count(idcard) from emp;        select avg(age) from emp;     select max(age) from emp;        select sum(age) from emp where workaddress = '西安';
--**分组** SELECT 字段列表 FROM 表名 [ WHERE 条件 ] GROUP BY 分组字段名 [ HAVING 分组后过滤条件 ];
-- 男性 女性数量     --男女年龄平均值   **gender,avg(age)          --年龄小于45,根据工作地址分组,获取员工数量大于3的工作地址       **having
select gender,count(*) from emp group by gender;                        select workaddress,count(*) from emp where age < 45 group by workaddress  having count(*)>3;
select workaddress, gender,count(*) from emp group by workaddress,gender;   --统计各个工作地址上班的男性及女性员工的数量
--**排序**  SELECT 字段列表 FROM 表名 ORDER BY 字段1 排序方式1 , 字段2 排序方式2 ;
-- 默认升序                  --降序                                       --多字段排序,当第一个字段值相同时，才会根据第二个字段进行排序 
select * from emp order by age asc;    select * from emp order by age desc;         select * from emp order by age asc, entrydate desc;
--**分页查询**  SELECT 字段列表 FROM 表名 LIMIT 起始索引, 查询记录数 ;      起始索引 = （查询页码 - 1）* 每页显示记录数。
select * from emp limit 10 , 10;

--**权限**  数据库管理员操作
--创建用户
create user 'itcast'@'localhost' identified by '123456';        create user 'yqzy'@'%' IDENTIFIED by '123456'; --所有主机可访问
--修改用户
alter user 'yqzy'@"%" IDENTIFIED WITH mysql_native_password by '456789';
--删除用户
drop user 'itcast'@'localhost';
--**DCL**        GRANT 权限列表 ON 数据库名.表名 TO '用户名'@'主机名';
--查询权限                       --授权                                         --撤销权限
show grants for 'yqzy'@'%';      grant all on *.* to 'yqzy'@'%';           revoke all on itcast.* from 'yqzy'@'%';

---*****函数*********
--拼接                       全部转小写  大写    左右填充                  去除空格       截取子字符串
concat('Hello' , ' MySQL')  lower() upper()   lpad('01', 5, '-')  rpad()   trim()       select substring('Hello MySQL',1,5);
--向上取整      向下取整    返回x/y的模     返回0~1内的随机数   求参数x的四舍五入的值，保留y位小数
ceil(x)          FLOOR(x)       MOD(x,y)    RAND()               ROUND(x,y) 
--当前日期  当前时间    日期和时间      年              月              日
CURDATE()   CURTIME()   NOW()           YEAR(date)      MONTH(date)     DAY(date)
--返回一个日期/时间值加上一个时间间隔expr后的时间值         返回起始时间date1 和 结束时间date2之间的天数
DATE_ADD(date, INTERVAL exprtype);                           DATEDIFF(date1,date2);
 
SELECT name ,DATEDIFF(CURDATE(),entrydate) '入职天数' from emp order by DATEDIFF(CURDATE(),entrydate) DESC;

--****约束****  NOT NULL    (unique)UNIQUE      (primary)PRIMARY KEY     (defuse)DEFAULT '1'     (check)CHECK(name>0) primary    (after)AFTER "id"
create table wholesale(
    id int unsigned primary key auto_increment COMMENT '编号',
    name varchar(20) not NULL unique COMMENT '产品名字',
    status char(1) DEFAULT '1' COMMENT '状态',
    num int unsigned check(num>0) COMMENT '数量',
    PurchaseDate DATETIME COMMENT '采购日期',
    Unitprice int unsigned check(Unitprice>0) COMMENT '单价',
    shelf_id int unsigned COMMENT '货架编号'
)comment '批发商品表';
---外键约束    
create table shelf(
    id int unsigned primary key auto_increment COMMENT '编号',
    name varchar(20) not NULL unique COMMENT '货架名字'
)comment '货架表';

insert into shelf(id,name)  values (1,'货架1'),(2,'货架2'),(3,'货架3');
insert into wholesale(id ,name, num, PurchaseDate, Unitprice,shelf_id)  values (1,'白菜',20,'2023-03-16', 2,1),(2,'胡萝卜',50,'2023-03-16', 5,1),(3,'西洋菜',30,'2023-03-16', 3,2),(4,'鸡',100,'2023-03-16', 100,3),(5,'鸭',20,'2023-03-16', 150,3),(6,'猪肉',20,'2023-03-16', 13,3);
--**添加外键    ALTER TABLE 表名 ADD      CONSTRAINT 外键名称 FOREIGN KEY (外键字段名) REFERENCES 主表 (主表列名) ;
alter table wholesale add constraint fk_wholesale_shelf_id foreign key (shelf_id) references shelf(id) on update cascade on delete set NULL ;
--**删除外键    ALTER TABLE 表名 DROP FOREIGN KEY 外键名称;
alter table wholesale drop foreign key fk_wholesale_shelf_id;
--**删除更新约束***    RESTRICT 有则不删除/更新     CASCADE 有，则也删除/更新子表记录   set NULL 置空或者置默认值 set defuse ''
on update set null on delete set null;


--*******多表查询******
--**隐式内连接**                别名操作:  select e.name, d.name from emp e, dept d where d.id = e.dept_id  order by e.id;
select emp.name, dept.name from emp, dept where dept.id = emp.dept_id  order by emp.id;
--**显示内连接**    ...inner join....on...
select e.name, d.name from emp e inner join dept d on  d.id = e.dept_id ;
--**左外连接**      left outer join...on            outer可以省略
select e.*, d.name from emp e left outer join dept d on  d.id = e.dept_id ;
--**右外连接**      right outer join...on
select e.name, d.* from emp e right outer join dept d on  d.id = e.dept_id ;
--**自连接**
select e.name, m.name from emp e join emp m on  e.managerid = m.id ;
select e.name, m.name from emp e join emp m on  e.id = m.managerid ;
select e.name, m.name from emp e left join emp m on  e.managerid = m.id ;
---**联合查询******           union all  去重删除 all   对于联合查询的多张表的列数必须保持一致，字段类型也需要保持一致
select * from emp where salary<5000
union all
select * from emp where age>50;
---*******子查询******           INSERT / UPDATE / DELETE / SELECT
select * from emp where dept_id = (select id from dept where dept.name = '销售部');   --标量子查询 = > < !=
--**列子查询**    IN 、NOT IN 、 ANY 、SOME 、 ALL
select * from emp where dept_id in(select id from dept where dept.name = '销售部' or dept.name = '市场部');   -- in 在指定的集合范围之内，多选一
select * from emp where salary > all ( select salary from emp where dept_id =(select id from dept where name = '财务部') );   -- all 子查询返回列表的所有值都必须满足
select * from emp where salary > any ( select salary from emp where dept_id =(select id from dept WHERE name = '研发部') );   -- any 子查询返回列表中，有任意一个满足即可
--**行子查询**
select * from emp where  (salary, managerid) = (SELECT salary,managerid from emp where name='张无忌') and name != '张无忌';
--**表子查询****
select * from emp where (job, salary) in(SELECT job,salary from emp where name='鹿杖客' or name ='宋远桥');
select e.*,dept.* FROM (select * from emp where entrydate > '2006-01-01') e left join dept on e.dept_id = dept.id;        --先筛选再连接



------*******事务*********
----***手动开关事务***
select @@autocommit;       set @@autocommit = 1;
--提交事务  commit         回滚事务 rollback
commit;                    rollback;

SELECT money from account where name= '张三';
update account set money = money -1000 where name='张三';
程序报错...
update account set money = money +1000 where name='李四';

----*****开启事务**
start transaction;      BEGIN;                  --两种事务开启方式
--提交事务  commit         回滚事务 rollback
commit;                    rollback;

----******事务隔离级别          事务隔离级别越高，数据越安全，但是性能越低。
SELECT @@transaction_isolation;  ---查看事务级别    SELECT @@TRANSACTION_ISOLATION;
--111               011                 001                         000         脏读  不可重复读  幻读
Read uncommitted    Read committed      Repeatable Read(默认)       Serializable;
SET [ SESSION | GLOBAL ] TRANSACTION ISOLATION LEVEL { READ UNCOMMITTED | READ COMMITTED | REPEATABLE READ | SERIALIZABLE };
set session transaction isolation Level      read uncommitted;
set session transaction isolation Level      Read committed;
set session transaction isolation Level      Repeatable Read;    --默认
set session transaction isolation Level      Serializable;