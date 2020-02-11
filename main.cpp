#include <iostream>
#include <vector>
#include <typeinfo>
#include <string.h>
using namespace std;

class Locuinta
{
    string nume_client;
    int discount;
    static int nr_loc;
public:
    Locuinta();
    Locuinta(string nu, int a);
    Locuinta (const Locuinta &);
    Locuinta& operator=(const Locuinta &);
    ~Locuinta();
    static int get_total()
    {
        return nr_loc;
    }
    void set_nume(string nume)
    {
        nume_client=nume;
    }
    void set_disc(int dis)
    {
        discount=dis;
    }
    string get_nume()
    {
        return this->nume_client;
    }
    double get_disc()
    {
        return this->discount;
    }
    friend istream& operator>> (istream &, Locuinta*);
    friend ostream& operator<< (ostream &, const Locuinta &);
    virtual int chirie() =0;
    virtual void afisare (ostream &out)
    {
        out<<"Nume client: "<<nume_client<<"\n "<<"Discount: "<<discount<<endl;
    };
};

int Locuinta:: nr_loc;
class Apartament: public Locuinta
{
    int pret;
    int etaj;
    int supr_utila;
public:
    Apartament();
    Apartament(int i, int j, int k, string a, int dis);
    Apartament(const Apartament& ob): Locuinta(ob)
    {
        etaj=ob.etaj;
        pret=ob.pret;
        supr_utila=ob.supr_utila;
    };
    Apartament& operator= (const Apartament&);
    ~Apartament();
    friend istream& operator>>(istream &, Apartament*);
    friend ostream& operator<< (ostream&, Apartament&);
    int chirie();
    void afisare(ostream &out)
    {
        Locuinta:: afisare(out);
        out<<"\n";
        out<<"Pretul este: "<<pret<< " \n";
        out<<"Etajul ap: "<<etaj<<" \n";
        out<<"Supr utila: "<<supr_utila<<" \n";
        out<<"Chiria ap este: "<<this->chirie();
        //out<<this->chirie();
    }

};

class Etaj
{
    int nr_etaj;
    int supr;
public:
    Etaj();
    Etaj(int a, int b): nr_etaj(a), supr(b) {}
    Etaj (const Etaj&);
    Etaj& operator=  (const Etaj&);
    ~Etaj();
    friend istream& operator>> (istream&, Etaj&);
    friend ostream& operator<< (ostream&, const Etaj&);
    int get_supr_etaj()
    {
        return supr;
    }

};

class Casa: public Locuinta
{
    int supr_curte;
    int pret_int;
    int pret_curte;
    int nr_etaje;
    Etaj *v;
public:
    Casa();
    Casa(int su, int nr,int p1, int p2);
    Casa (const Casa& ob): Locuinta(ob)
    {
        supr_curte=ob.supr_curte;
        nr_etaje=ob.nr_etaje;
        pret_curte=ob.pret_curte;
        pret_int=ob.pret_int;
        delete[]v;
        v=new Etaj[nr_etaje];
        for(int i=0; i<nr_etaje; i++)
            v[i]=ob.v[i];
    }
    Casa& operator= (const Casa&);
    ~Casa();
    friend istream& operator>>(istream &, Casa*);
    friend ostream& operator<< (ostream&,  Casa&);
    virtual void afisare(ostream &out)
    {
        Locuinta:: afisare(out);
        out<<"Suprafata_curte: "<<supr_curte<<" \n"<<"Nr de etaje ale casei: "<<nr_etaje<<endl;
        int i;
        for(i=0; i<nr_etaje; i++)
            out<<v[i]<<endl;
        out<<"Pretul pe metru de curte: "<<pret_curte<<endl;
        out<<"Pretul pe metru interior: "<<pret_int<<endl;
        out<<"Chiria casei: "<<this->chirie();
    }
    int chirie() ;
};
Etaj:: Etaj()
{
    nr_etaj=0;
    supr=0;
}

Etaj:: Etaj(const Etaj& ob)
{
    nr_etaj=ob.nr_etaj;
    supr=ob.supr;
}

Etaj& Etaj:: operator=(const Etaj& ob)
{
    if (this!=&ob)
    {
        nr_etaj=ob.nr_etaj;
        supr=ob.supr;

    }
    return *this;
}

Etaj:: ~Etaj()
{
    cout<<"Destructor etaj"<<endl;
}

istream& operator>>(istream& in, Etaj& ob)
{
    cout<<"Dati numarul etajului: ";
    in>>ob.nr_etaj;
    cout<<"Dati supr etaj: ";
    in>>ob.supr;
    return in;
}

ostream& operator<<(ostream& out, const Etaj &ob)
{
    out<<"Etajul nr: "<<ob.nr_etaj<<" cu suprafata de: "<<ob.supr<<" \n";
    return out;
}

Locuinta:: Locuinta()
{
    nume_client="";
    nr_loc++;
    discount=0;
}

Locuinta:: Locuinta(string nu, int a)
{
    this->nume_client=nu;
    this->discount=a;
    nr_loc++;
}

Locuinta:: Locuinta(const Locuinta& ob)
{
    this->nume_client=ob.nume_client;
    this->discount=ob.discount;
    nr_loc++;
}

Locuinta& Locuinta:: operator= (const Locuinta &ob)
{
    if (this!=&ob)
    {
        this->nume_client=ob.nume_client;
        this->discount=ob.discount;
        nr_loc++;
    }
    return *this;
}

Locuinta:: ~Locuinta()
{
    cout<<"\nDestruct Locuinta\n";
    nr_loc--;
}

istream& operator>> (istream & in, Locuinta *ob)
{
    cout<<"Dati nume client: ";
    in>>ob->nume_client;
    cout<<endl<<"Dati discount: ";
    in>>ob->discount;
    return in;
}

ostream& operator<< (ostream &out,  Locuinta &ob)
{
    ob.afisare(out);
    return out;
}


Apartament:: Apartament()
{
    etaj=0;
    pret=0;
    supr_utila=0;
}

Apartament:: Apartament(int i, int j, int k, string a, int dis):  Locuinta(a,dis)
{
    pret=i;
    etaj=j;
    supr_utila=k;

}

Apartament& Apartament:: operator= (const Apartament& ob)
{
    if (this!=&ob)
    {
        this->Locuinta:: operator=(ob);
        pret=ob.pret;
        supr_utila=ob.supr_utila;
        etaj=ob.etaj;
    }
    return *this;
}

Apartament:: ~Apartament()
{
    cout<<"\n Destructor apartament";
}

int Apartament:: chirie()
{
    int d;
    int su;
    d=this->get_disc();
    su=this->supr_utila;
    int pretd;
    int p;
    p=su*pret;
    pretd=p-(d*p)/100;
    return pretd;

}
istream& operator>> (istream& in, Apartament * ob)
{
    in>>(Locuinta*) ob;
    cout<<"\n Dati etajul ap: ";
    in>>ob->etaj;
    cout<<"\n Dati suprafata ap: ";
    in>>ob->supr_utila;
    cout<<"\n Dati pretul ap: ";
    in>>ob->pret;
    return in;
}

ostream& operator<< (ostream& out,   Apartament &ob)
{
    /* out<<ob.get_nume()<<" "<<ob.<<" "<<ob.get_disc()<<" "<<ob.etaj<<endl;
     out<<"cu chiria de "<<ob.chirie();
     out<<endl;
     return out; */
    // out<<(Locuinta&) ob;
    ob.afisare(out);
    cout<<"Chiria ap: "<<ob.chirie();
    return out;
}

int Casa:: chirie()
{
    int suma=0;
    int disc=this->get_disc();
    suma=supr_curte*pret_curte;
    for(int i=0; i<nr_etaje; i++)
    {
        int k=v[i].get_supr_etaj();
        suma=suma+k*pret_int;
    }
    suma=suma-suma*disc/100;
    return suma;
}

Casa:: Casa()
{
    supr_curte=0;
    nr_etaje=0;
    pret_curte=0;
    pret_int=0;
    v=NULL;
}

Casa:: Casa(int i, int j, int p1, int p2)
{
    supr_curte=i;
    nr_etaje=j;
    pret_int=p1;
    pret_curte=p2;
    v=NULL;
}

Casa& Casa:: operator=(const Casa& ob)
{
    if (this!=&ob)
    {
        this->Locuinta:: operator=(ob);
        supr_curte=ob.supr_curte;
        nr_etaje=ob.nr_etaje;
        pret_curte=ob.pret_curte;
        pret_int=ob.pret_int;
        delete[]v;
        int i;
        v=new Etaj[nr_etaje];
        for(i=0; i<nr_etaje; i++)
            v[i]=ob.v[i];
    }
    return *this;
}

Casa:: ~Casa()
{
    delete[]v;
    cout<<"\n Destructor casa\n";
}

istream& operator>> (istream &in, Casa* ob)
{
    in>>(Locuinta*) ob;
    cout<<"\nDati supr curte: ";
    in>>ob->supr_curte;
    cout<<"\nDati pretul pe metru de curte: ";
    in>>ob->pret_curte;
    cout<<"\nDati pretul pe metru interior: ";
    in>>ob->pret_int;
    cout<<"\nDati nr de etaje ale casei: ";
    in>>ob->nr_etaje;
    ob->v=new Etaj[ob->nr_etaje];
    for(int i=0; i<ob->nr_etaje; i++)
        cin>>ob->v[i];
    return in;
}

ostream& operator<< (ostream &out, Casa& ob)
{
    out<<(Locuinta&) ob;
    out<<"Chiria case: "<<ob.chirie();
    out<<endl;
    return out;
}

template <class T>
class Gestiune
{
    int index;
    vector <Locuinta*> lista;
    vector <T> clienti;
public:
    Gestiune(int a=0);
    Gestiune (const Gestiune&);
    Gestiune& operator= (const Gestiune &);
    ~Gestiune();
    void adaug_type_T()
    {
        T a;
        cout<<"\nDati valoarea lui Type T(pentru int: varsta) : \n";
        cin>>a;
        clienti.push_back(a);
    }
    void afis_categorii()
    {
        cout<<"Indexul total: "<<index<<endl;
        for(int i=0; i<index; i++)
        {
            Casa *ptr=dynamic_cast<Casa*>(lista[i]);
            if(ptr!=NULL)
            {
                //ptr->afisare(out);
                cout<<*ptr;
                cout<<endl;
            }

        }
    }
    Gestiune& operator += (Locuinta&);
    friend ostream& operator<< (ostream& out, const Gestiune& ob)
    {
        out<<"\n Total clienti: "<<ob.index;
        for(int i=0; i<ob.index; i++)
        {
            out<<endl;
            out<<"\nIndex client: "<<i;
            out<<endl;
            out<<*ob.lista[i]<<endl;
            out<<"Cu varsta de: "<<ob.clienti[i];
            out<<endl;
        }

    }
};

template<>
class Gestiune<char*>
{
    int index;
    vector <Locuinta*> lista;
    vector <char*> clienti;
public:
    Gestiune(int a=0);
    Gestiune (const Gestiune&);
    Gestiune& operator= (const Gestiune &);
    ~Gestiune();
    Gestiune& operator += (Locuinta&);
    void adaug_type_T()
    {
        char *a;
        a=new char[20];
        cout<<"\nDati strada locuintei: \n";
        cin>>a;
        cout<<a;
        clienti.push_back(a);
    }
    friend ostream& operator<< (ostream& out, const Gestiune& ob)
    {
        out<<"\n Total clienti: "<<ob.index;
        for(int i=0; i<ob.index; i++)
        {
            out<<endl;
            out<<"\nIndex client: "<<i;
            out<<endl;
            out<<*ob.lista[i]<<endl;
            out<<"Strada locuintei: "<<ob.clienti[i];
            out<<endl;
        }

    }
};

template <class T>
Gestiune <T>:: Gestiune (int a)
{
    index=a;
}

template <class T>
Gestiune <T>:: Gestiune (const Gestiune& ob)
{
    index=ob.index;
    lista.clear();
    for(int i=0; i<index; i++)
    {

        Casa *casaptr=dynamic_cast<Casa*>(ob.lista[i]);
        if(casaptr!=NULL)
            lista.push_back(new Casa(*casaptr));
        else
        {
            Apartament *apptr=dynamic_cast<Apartament*>(ob.lista[i]);
            if(apptr!=NULL)
                lista.push_back(new Apartament(*apptr));
        }

    }
    clienti=ob.clienti;

}

template <class T>
Gestiune<T>& Gestiune <T>:: operator=(const Gestiune& ob)
{
    if(this!=&ob)
    {
        lista.clear();
        index=ob.index;
        for(int i=0; i<index; i++)
        {

            Casa *casaptr=dynamic_cast<Casa*>(ob.lista[i]);
            if(casaptr!=NULL)
                lista.push_back(new Casa(*casaptr));
            else
            {
                Apartament *apptr=dynamic_cast<Apartament*>(ob.lista[i]);
                if(apptr!=NULL)
                    lista.push_back(new Apartament(*apptr));
            }

        }
        clienti=ob.clienti;
    }
    return *this;
}

template <class T>
Gestiune <T> :: ~Gestiune()
{
    lista.clear();
}

template <class T>
Gestiune<T>& Gestiune <T>:: operator+=(Locuinta &ob)
{
    lista.push_back(&ob);
    index++;
    return *this;
}


Gestiune <char*>:: Gestiune (int a)
{
    index=a;
}


Gestiune <char*>:: Gestiune (const Gestiune& ob)
{
    index=ob.index;
    lista.clear();
    for(int i=0; i<index; i++)
    {

        Casa *casaptr=dynamic_cast<Casa*>(ob.lista[i]);
        if(casaptr!=NULL)
            lista.push_back(new Casa(*casaptr));
        else
        {
            Apartament *apptr=dynamic_cast<Apartament*>(ob.lista[i]);
            if(apptr!=NULL)
                lista.push_back(new Apartament(*apptr));
        }

    }
    clienti.clear();
    for(int i=0; i<index; i++)
    {
        clienti.push_back(ob.clienti[i]);
    }

}


Gestiune<char*>& Gestiune <char*>:: operator=(const Gestiune& ob)
{
    if(this!=&ob)
    {
        lista.clear();
        index=ob.index;
        for(int i=0; i<index; i++)
        {

            Casa *casaptr=dynamic_cast<Casa*>(ob.lista[i]);
            if(casaptr!=NULL)
                lista.push_back(new Casa(*casaptr));
            else
            {
                Apartament *apptr=dynamic_cast<Apartament*>(ob.lista[i]);
                if(apptr!=NULL)
                    lista.push_back(new Apartament(*apptr));
            }

        }
        clienti.clear();
        for(int i=0; i<index; i++)
        {
            clienti.push_back(ob.clienti[i]);
        }
    }
    return *this;
}


Gestiune <char*> :: ~Gestiune()
{
    lista.clear();
    clienti.clear();
}


Gestiune<char*>& Gestiune <char*>:: operator+=(Locuinta &ob)
{
    lista.push_back(&ob);
    index++;
    return *this;
}


int main()
{
    int gest;
    cout<<"Dati 1 pentru template(int) sau 2 pentru specializare(char*): ";
    cin>>gest;
    if(gest==1)
    {
        Gestiune <int>v;
    cout<<"Dati nr de elemnte: ";
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int opt;
        cout<<"Dati 0 pentru casa, 1 pentru apartament: ";
        cin>>opt;
        try
        {
            if (opt!=0 && opt!=1)
                throw opt;
        }
        catch(int opt)
        {
            cout<<"Input-ul este invalid\n";
        }
        if(opt==0)
        {
            Casa *b=new Casa;
            cin>>b;
            v.adaug_type_T();
            v+=*b;
        }
        if(opt==1)
        {
            Apartament *b=new Apartament;
            cin>>b;
            v.adaug_type_T();
            v+=*b;
        }

    }
    cout<<v;
    }
    else {
    Gestiune <char*>v;
    cout<<"Dati nr de elemnte: ";
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        int opt;
        cout<<"Dati 0 pentru casa, 1 pentru apartament: ";
        cin>>opt;
        try
        {
            if (opt!=0 && opt!=1)
                throw opt;
        }
        catch(int opt)
        {
            cout<<"Input-ul este invalid\n";
        }
        if(opt==0)
        {
            Casa *b=new Casa;
            cin>>b;
            v.adaug_type_T();
            v+=*b;
        }
        if(opt==1)
        {
            Apartament *b=new Apartament;
            cin>>b;
            v.adaug_type_T();
            v+=*b;
        }

    }
    cout<<v;}


}
