create table HOTEL(
id integer primary key auto_increment,
nom varchar(30),
Adresse varchar(30),
nb_chambres integer,
nb_etoile integer);

create table EMPLOYE(
id integer primary key auto_increment,
nom varchar(30),
password varchar(100),
email varchar(100));

create table droit_acces(
id integer references hotel(id),
id_2 integer references EMPLOYE(id));

create table CHAMBRES(
numero_chambre integer primary key auto_increment,
type_chambre varchar(30),
prix integer,
id integer references hotel(id));

create table CLIENTS(
numero_reservation integer primary key auto_increment,
nom varchar(30),
adresse varchar(100),
telephone integer,
date_reservation date);



create table RESERVATIONS(
numero_reservation integer primary key auto_increment,
date_debut date,
date_fin date,
id integer references CLIENT(id));

create table est_reserve(
numero_chambre integer references CHAMBRES(id),
numero_reservation integer references RESERVATION(id));




