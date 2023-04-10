#include<iostream>
#include<fstream>
#include<string>
#include<bitset>

using namespace std;


void write();
void read();
void encripchar(int n);

 
int main(){
   
   write();
   cout<<"--BIENVENIDO--"<<endl;
   int semilla,n;
   cout<<"Si quieres usar la codificacion por char, presiona '1'"<<endl<< "Si quieres usar la codificacion por string, presiona '2' ";
   cin>>n;
   cout<<"Bien, ahora dame un numero entero, este sera la semilla para codificar tu archivo ";
   cin>>semilla;
   

    return 0;

}

void write(){

    ofstream encripta2;
    
    encripta2.open("sudo.txt",ios::out|ios::app);
    if (encripta2.fail()){

        cout<<"No se pudo crear el archivo :c ";

        }
    encripta2<<"";
    encripta2.close();
    
}

void read (ifstream archivo){

    string encriptar;
    string nombre="archivo.txt";
    archivo.open(nombre,ios::in);

    while(!archivo.eof()){
        getline(archivo,encriptar);
    }
    archivo.close();
    
}

void encripchar(int n) {

    ifstream archivo;
    string encriptar,binario="";
    int i=0;
    string nombre="archivo.txt";
    archivo.open(nombre,ios::in);

    while(!archivo.eof()){
        getline(archivo,encriptar);
    }
    archivo.close();

    for (i=0;i<encriptar.size();i++){

       binario+=bitset<8> (encriptar[i]).to_string()+" ";
    }

    cout<<binario;

    

}
