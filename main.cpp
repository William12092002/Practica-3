#include<iostream>
#include<bitset>
#include<fstream>
#include<string>
#include<stdlib.h>
#include <stdio.h>


using namespace std;    
string nombre,clave,cedula,saldo;
bool validacion( string nombre, string passwrd, ifstream &vali);
void registrar();
void consultarsaldo(string nom);
void sacardinero(string nom);
bool verificar (string nom);
bool validacion2(string nombre, string passwrd, ifstream &vali);
void encriptar();
void encripchar(int n);

int main(){
    bool validation,validation2;
    ifstream Vali;
    int validacionadmin,validacionuser,p;
    string usuario,password,nombreusu,passwordusu;

    cout<<"--CAJEROS ELECTRONICOS WILLIAM S.A.S--"<<endl<<endl<<"Bienvenido, por favor identificate"<<endl<<endl<<"Si eres administrador presiona '1', de otra forma presiona '2':  ";
    cin>>validacionadmin;
    
    if (validacionadmin==1){
        system("cls");
        cout<<"Dame tu nombre de usuario: ";
        cin>>usuario;
        cout<<"Dame tu clave: ";
        cin>>password;
        validation=validacion(usuario,password,Vali);
        if (validation==true){
            system("cls");
            cout<<"Regristro de nuevo usuario: "<<endl;
            registrar();  
        }
        else{
            cout<<"Tu usuario o contrasena es incorrecta";
        }

    }
    else if (validacionadmin==2){
        cout<<"¿Deseas ingresar como usuario?, Si es asi presiona 1: ";
        cin>>validacionuser;
        system("cls");
        cout<<"Nombre de usuario: ";
        cin>>nombreusu;
        cout<<"Clave: ";
        cin>>passwordusu;
        validation2=validacion2(nombreusu,passwordusu,Vali);
        if ( validation2==true){
            cout<<"Si deseas ver tu saldo, presiona  '1' "<<endl<<"Si deseas hacer una transaccion, presiona '2' ";
            cin>>p;
            if (p==1){
                consultarsaldo(nombreusu);
            }
            else if (p==2){
                sacardinero(nombreusu);
            }
        }
    }
    else{
        while (validacionadmin != 1 && validacionadmin != 2){
            cout<<"Ese no es un numero valido, intenta otra vez";
            cin>>validacionadmin;
        }
    }
    encripchar(2);

}


bool validacion(string nombre, string passwrd, ifstream &vali){
    bool comprobar;
    string nom,pass;
    vali.open("sudo.txt",ios::in);
    vali>>nom;
    vali>>pass;
    if(nom==nombre && pass==passwrd){
        comprobar=true;
    }
    else{
        comprobar=false;
    }
    vali.close();
    return comprobar;

 }


void registrar(){
    bool validar;
    string nombre,clave,cedula,saldo;
    ofstream agregar("usuarios.txt",ios::out|ios::app);
    cout<<"Nombre de usuario: ";
    cin>>nombre;
    cout<<"clave: ";
    cin>>clave;
    cout<<"Cedula: ";
    cin>>cedula;
    cout<<"Saldo: ";
    cin>>saldo;
    validar=verificar(nombre);
    if (validar==true){
        cout<<"El usuario ya esta en la base de datos";
    }
    else{
        agregar<<nombre<<" "<<clave<<" "<<" "<<cedula<<" "<<saldo<<'\n';
    }
   
    
    agregar.close();
   

 }



bool verificar (string nom){
    bool valor=false;
    ifstream archivo("usuarios.txt",ios::in);
    string nombre;
    archivo>>nombre;
    while(!archivo.eof()){
        archivo>>clave>>cedula>>saldo;
        if (nombre==nom){
            valor=true;
            break;
        }
        archivo>>nombre;
    }
    archivo.close();
    return valor; 
}

bool validacion2(string nombre, string passwrd, ifstream &vali){
    bool comprobar=false;
    string nom,pass;
    vali.open("usuarios.txt",ios::in);
    vali>>nom;
    vali>>pass;
    while (!vali.eof()){
     if(nom==nombre && pass==passwrd){
        comprobar=true;
        }
     vali>>nom;
     vali>>pass; 
    }
    vali.close();
    return comprobar;
    
}


void consultarsaldo(string nom){
    system("cls");
    int nuevosaldo;
    ifstream leera("usuarios.txt",ios::in);
    ofstream copia("copia.txt",ios::out|ios::app);
    leera>>nombre;
    while (!leera.eof()){
        leera>>clave>>cedula>>saldo;
        if( nom==nombre){
            if (stoi(saldo)>=1000){
                cout<<"Su saldo es: "<<saldo<<endl;
                nuevosaldo=stoi(saldo)-1000;
                copia<<nombre<<" "<<clave<<" "<<cedula<<" "<<nuevosaldo<<'\n';
                
            }
            else{
                cout<<"No tienes suficiente saldo para consultar el mismo: ";
                copia<<nombre<<" "<<clave<<" "<<cedula<<" "<<saldo<<'\n';   
            }
        }
        else{
            copia<<nombre<<" "<<clave<<" "<<cedula<<" "<<saldo<<'\n';
 
        }
        leera>>nombre;
    }
    leera.close();
    copia.close();
    remove("usuarios.txt");
    rename("copia.txt","usuarios.txt");
    
   

}
void sacardinero(string nom){
    system("cls");
    int nuevosaldo,retiro;
    ifstream leera("usuarios.txt",ios::in);
    ofstream copia("copia.txt",ios::out|ios::app);
    leera>>nombre;
    while (!leera.eof()){
        leera>>clave>>cedula>>saldo;
        if( nom==nombre){
            if (stoi(saldo)>=1000){
                cout<<"Dame tu valor a retirar: ";
                cin>>retiro;
                if(retiro>stoi(saldo)){
                    cout<<"Esa cantidad de dinero, supera lo que tienes en la cuenta, no puedo retirarlo. ";
                    copia<<nombre<<" "<<clave<<" "<<cedula<<" "<<saldo<<'\n';
                }
                else{
                    cout<<"Fue un placer servirte, esperamos que hayas quedado satisfecho. ";
                    nuevosaldo=(stoi(saldo)-retiro)-1000;
                    copia<<nombre<<" "<<clave<<" "<<cedula<<" "<<nuevosaldo<<'\n';
                }
            }
            else{
                cout<<"No tienes dinero para realizar la transaccion bancaria: ";
            }
        }
        else{
            copia<<nombre<<" "<<clave<<" "<<cedula<<" "<<saldo<<'\n';
        }
        leera>>nombre;

    }
    leera.close();
    copia.close();
    remove("usuarios.txt");
    rename("copia.txt","usuarios.txt");

}




void encripchar(int n) {

    ifstream archivo;
    archivo.open("usuarios.txt",ios::in);
    string encriptar,aux="",binario="";
    int i=0;
    if (archivo.fail()){
        cout<<"No se pudo abrir.";
    }
    while(!archivo.eof()){
        getline(archivo,encriptar);
        aux+=encriptar;
    }
    archivo.close();
    int encrip=aux.size();
    for (i=0;i<encrip;i++){
       binario+=bitset<8> (aux[i]).to_string()+" ";
    }

    

    

}