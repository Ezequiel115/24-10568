#include<iostream>
#include<string>
using namespace std;

int main()

{
    string pais;
    cout<< "De donde eres?"<<endl;
    getline(cin,pais);
    int edad;
    string respuesta;
    

    if(pais=="venezuela")
    {
        cout<<"puedes ingresar"<<endl;
    }

    else if(pais=="peru")
    {
        cout<<"puedes ingresar"<<endl;
    }

     else if(pais=="colombia")
     {
        cout<<"puedes ingresar"<<endl;
    }

   else if (pais=="costa rica")
   {
    cout<<"puedes ingresar"<<endl;
   }

   else if(pais=="estados unidos")
   {
    cout<<"puedes ingresar"<<endl;
   }

   else {
    cout<<"tu region no esta disponible, pero puedos ayudarte si nos mencionas tu edad"<<endl;

cin>>edad;

cin.ignore();

if(edad>=18)
{
    cout<<"bienveido al sitio"<<endl;

    getline(cin,respuesta);

    if(respuesta=="gracias")
    {
        cout<<"de nada"<<endl;
    }
    else
    {
        cout<<"no te inculcaron modales?"<<endl;}

}

else if(edad<0)
{cout<<"no existes"<<endl;}

else if(edad<18)
{cout<<"no puedes ingresar al sitio web por ser menor de edad"<<endl;}

   }


    return 0;
}

