drop table if exists vftb;
create table vftb(
  id integer primary key,
  product text not null,
  nickname text unique,
  serverip text not null,
  username text not null,
  password text not null,
  domain text not null,
  autolink blob default 0
);

drop table if exists vfidv;
create table vfidv(
  name text primary key,
  autostart text,
  cpu text not null,
  memory text not null,
  sdisk text not null,
  sdisk_restore text,
  ddisk text,
  ddisk_restore text,
  cdrom text,
  floppy text,
  boot text,
  nettype text,
  ipaddr text,
  netmask text,
  gateway text,
  dns text,
  pci text,
  port text
);

drop table if exists vfpswd;
create table vfpswd(
  id integer primary key,
  passwd text not null
);

drop table if exists vfmgmt;
create table vfmgmt(
  id integer primary key,
  uuid text not null,
  ip text not null
);
