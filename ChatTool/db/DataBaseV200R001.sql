use ChatTool;

Alter table dbo.userinfo add dept char(20);
Alter table dbo.userinfo add post char(20);
Alter table dbo.userinfo add name nchar(30);

sp_columns userinfo;