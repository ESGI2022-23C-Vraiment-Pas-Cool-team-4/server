/*
 * Created by : Charbel SALHAB, Andrei MALICEK, Janin MICHEL-MATHIAS
 * Date : 24/02/2023
 * "program allowing you to create your own hotel with number of rooms and type of room and service offered.
 * The rooms can be reserved by customers according to the criteria of the hotel."
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GetHotel{
    int id;
}GetHotel;

typedef struct GetHotelReturn{
    int id;
    char *nom;
    char *adresse;
    int  nombre_de_chambres;
    int  nombre_d_etoile;
}GetHotelReturn;

typedef struct CreateHotel{
    int id;
    char *nom;
    char *adresse;
    int  nombre_de_chambres;
    int  nombre_d_etoile;
}CreateHotel;

typedef struct CreateHotelReturn{
    int id;
    char *nom;
    char *adresse;
    int  nombre_de_chambres;
    int  nombre_d_etoile;
}CreateHotelReturn;

typedef struct UpdateHotel{
    int id;
    char *nom;
    char *adresse;
    int  nombre_de_chambres;
    int  nombre_d_etoile;
}UpdateHotel;

typedef struct UpdateHotelReturn{
    int id;
    char *nom;
    char *adresse;
    int  nombre_de_chambres;
    int  nombre_d_etoile;
}UpdateHotelReturn;

typedef struct DeleteHotel{
    int id;
}DeleteHotel;

typedef struct DeleteHotelReturn{
    int id;
    char *nom;
    char *adresse;
    int  nombre_de_chambres;
    int  nombre_d_etoile;
}DeleteHotelReturn;

typedef struct GetRoom{
    int numero_chambre;
}GetRoom;

typedef struct GetRoomReturn{
    int numero_chambre;
    char *type_chambre;
    int capacite;
    float prix;
}GetRoomReturn;

typedef struct CreateRoom{
    int numero_chambre;
    char *type_chambre;
    int capacite;
}CreateRoom;

typedef struct CreateRoomReturn{
    int numero_chambre;
    char *type_chambre;
    int capacite;
    float prix;
}CreateRoomReturn;

typedef struct UpdateRoom{
    int numero_chambre;
    char *type_chambre;
    int capacite;
    float prix;
}UpdateRoom;

typedef struct UpdateRoomReturn{
    int numero_chambre;
    char *type_chambre;
    int capacite;
    float prix;
}UpdateRoomReturn;

typedef struct DeleteRoom{
    int numero_chambre;
}DeleteRoom;

typedef struct DeleteRoomReturn{
    int numero_chambre;
    char *type_chambre;
    int capacite;
    float prix;
}DeleteRoomReturn;


typedef struct GetReservation{
    int numero_reservation;
}GetReservation;

typedef struct GetReservationReturn{
    int numero_reservation;
    char *date_debut;
    char *date_fin;
}GetReservationReturn;

typedef struct CreateReservation{
    int numero_reservation;
    char *date_debut;
    char *date_fin;
}CreateReservation;

typedef struct CreateReservationReturn{
    int numero_reservation;
    char *date_debut;
    char *date_fin;
}CreateReservationReturn;

typedef struct UpdateReservation{
    int numero_reservation;
    char *date_debut;
    char *date_fin;
}UpdateReservation;

typedef struct UpdateReservationReturn{
    int numero_reservation;
    char *date_debut;
    char *date_fin;
}UpdateReservationReturn;

typedef struct DeleteReservation{
    int numero_reservation;
}DeleteReservation;

typedef struct DeleteReservationReturn{
    int numero_reservation;
    char *date_debut;
    char *date_fin;
}DeleteReservationReturn;

typedef struct GetClient{
    int id;
}GetClient;

typedef struct GetClientReturn{
    int id;
    char *nom;
    char *adresse;
    char *phone;
    char *date_de_reservation;
}GetClientReturn;

typedef struct CreateClient{
    int id;
    char *nom;
    char *adresse;
    char *phone;
    char *date_de_reservation;
}CreateClient;

typedef struct CreateClientReturn{
    int id;
    char *nom;
    char *adresse;
    char *phone;
    char *date_de_reservation;
}CreateClientReturn;

typedef struct UpdateClient{
    int id;
    char *nom;
    char *adresse;
    char *phone;
    char *date_de_reservation;
}UpdateClient;

typedef struct UpdateClientReturn{
    int id;
    char *nom;
    char *adresse;
    char *phone;
    char *date_de_reservation;
}UpdateClientReturn;

typedef struct DeleteClient{
    int id;
}DeleteClient;

typedef struct  DeleteClientReturn{
    int id;
    char *nom;
    char *adresse;
    char *phone;
    char *date_de_reservation;
}DeleteClientReturn;

typedef struct GetEmployee{
    int id;
}GetEmployee;

typedef struct GetEmployeeReturn{
    int id;
    char *nom;
    char *mot_de_passe;
    char *adresse_mail;
}GetEmployeeReturn;

typedef struct CreateEmployee{
    int id;
    char *nom;
    char *mot_de_passe;
    char *adresse_mail;
}CreateEmployee;

typedef struct CreateEmployeeReturn{
    int id;
    char *nom;
    char *mot_de_passe;
    char *adresse_mail;
}CreateEmployeeReturn;

typedef struct UpdateEmployee{
    char *nom;
    char *mot_de_passe;
    char *adresse_mail;
}UpdateEmployee;

typedef struct UpdateEmployeeReturn{
    int id;
    char *nom;
    char *mot_de_passe;
    char *adresse_mail;
}UpdateEmployeeReturn;

typedef struct DeleteEmployee{
    int id;
}DeleteEmployee;

typedef struct DeleteEmployeeReturn{
    int id;
    char *nom;
    char *mot_de_passe;
    char *adresse_mail;
}DeleteEmployeeReturn;