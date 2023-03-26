#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <time.h>


using namespace std;


class Card
{
private:
    char znak;
    char kolor;
    int value;
    bool is_visible;
    bool is_red;
public:
    Card(char znak,char kolor,int value,bool is_red)
    {
       this->znak=znak;
       this->kolor=kolor;
       this->value=value;
       this->is_visible=true;
       this->is_red=is_red;
    }
    char getZnak()
    {
        return this->znak;
    }
    char getKolor()
    {
        return this->kolor;
    }
    int getValue()
    {
        return this->value;
    }
    bool getVisible()
    {
        return this->is_visible;
    }
    void setVisible(bool x)
    {
        this->is_visible=x;
    }
    bool getRed()
    {
        return this->is_red;
    }
};

void tasowanie(vector<Card> &Talia,queue<Card> &Nierozdane,vector<vector<Card>> &Plansze)
{
    srand(time(NULL));
    for(int i=0;i<24;i++)
    {
        int liczba = rand()%Talia.size();
        Nierozdane.push(Talia[liczba]);
        Talia.erase(Talia.begin()+liczba);
    }
    for(int i=0;i<7;i++)
    {
        for(int g=0;g<i+1;g++)
        {
            int liczba = rand()%Talia.size();
            Plansze[i].push_back(Talia[liczba]);
            if(i!=0 and g!=i) Plansze[i][g].setVisible(false);
            Talia.erase(Talia.begin()+liczba);
        }  
    }
}
void inicjalizacja(vector<Card> &Talia)
{
    char kolor='h';
    bool is_red=true;
    for(int i=0;i<4;i++)
    {
        if(i==1)
        {
            kolor='s';
            is_red=false;
        }
        else if(i==2)
        {
            kolor='d';
            is_red=true;
        }
        else if(i==3)
        {
            kolor='c';
            is_red=false;
        }

        Talia.push_back(Card('A',kolor,1,is_red));
        Talia.push_back(Card('2',kolor,2,is_red));
        Talia.push_back(Card('3',kolor,3,is_red));
        Talia.push_back(Card('4',kolor,4,is_red));
        Talia.push_back(Card('5',kolor,5,is_red));
        Talia.push_back(Card('6',kolor,6,is_red));
        Talia.push_back(Card('7',kolor,7,is_red));
        Talia.push_back(Card('8',kolor,8,is_red));
        Talia.push_back(Card('9',kolor,9,is_red));
        Talia.push_back(Card('T',kolor,10,is_red));
        Talia.push_back(Card('J',kolor,11,is_red));
        Talia.push_back(Card('Q',kolor,12,is_red));
        Talia.push_back(Card('K',kolor,13,is_red));

    }
}

int znajdz_max(vector<vector<Card> > &Plansze)
{
    int max=0;
    for(int i=0;i<7;i++)
    {
        if(Plansze[i].size()>max) max=Plansze[i].size();
    }
    return max;
}

bool check_win(vector<stack<Card>> Stosy)
{
    if(Stosy[0].size()==13 and Stosy[1].size()==13 and Stosy[2].size()==13 and Stosy[3].size()==13  ) return true;
    else return false;
}

void kolejka_rozloz(queue<Card> &Nierozdane,vector<Card> &Widoczne)
{
       if(Nierozdane.size()>0)
       {
        if(Widoczne.size()==0)
        {
            Widoczne.push_back(Nierozdane.front());
            Nierozdane.pop();
        }
        else if(Widoczne.size()<3)
        {
            Widoczne.push_back(Nierozdane.front());
            Nierozdane.pop();
        }
        else
        {
            Nierozdane.push(Widoczne[0]);
            Widoczne.erase(Widoczne.begin());
            Widoczne.push_back(Nierozdane.front());
            Nierozdane.pop();
        }
       }
       else if(Widoczne.size()>0)
       {
           Widoczne.push_back(Widoczne[0]);
           Widoczne.erase(Widoczne.begin());
           Widoczne.push_back(Widoczne[0]);
           Widoczne.erase(Widoczne.begin());
           Widoczne.push_back(Widoczne[0]);
           Widoczne.erase(Widoczne.begin());
       }
       else cout<<"Nie ma juz kart!"<<endl;
    
}

void kolejka_plansza(vector<vector<Card>> &Plansze,queue<Card> &Kolejka,vector<Card> &Widoczne,int numer)
{
    if(Widoczne.size()>0)
    {
        Card karta = Widoczne.back();
        if((karta.getZnak()=='K' and Plansze[numer-1].size()==0) or (Plansze[numer-1].size() >0 and karta.getValue()==Plansze[numer-1][Plansze[numer-1].size()-1].getValue()-1 and karta.getRed()!=Plansze[numer-1][Plansze[numer-1].size()-1].getRed()))
        {
            Widoczne.pop_back();
            Plansze[numer-1].push_back(karta);
        }
        else
        {
            cout<<"Nie mozna wykonac takiego ruchu"<<endl;
        }
    }
    else cout<<"Nie mozna wykonac takiego ruchu"<<endl;

}

void kolejka_stos(vector<Card> &Widoczne,int numer,vector<stack<Card>> &Stosy,queue<Card> &Nierozdane)
{
    if(Widoczne.size()>0)
    {
        Card karta = Widoczne.back();
        if((karta.getZnak()=='A' and Stosy[numer-8].size()==0)or(Stosy[numer-8].size()>0 and karta.getValue()==Stosy[numer-8].top().getValue()+1 and karta.getKolor()==Stosy[numer-8].top().getKolor()))
        {
            Widoczne.pop_back();
            Stosy[numer-8].push(karta);
        }
        else
        {
            cout<<"Nie mozna wykonac takiego ruchu"<<endl;
        }
    }
    else cout<<"Nie mozna wykonac takiego ruchu"<<endl;
}

void stos_plansza(vector<stack<Card>> &Stosy,int numer_stosu,int numer_planszy,vector<vector<Card>> &Plansze)
{
    if(Stosy[numer_stosu-8].size()>0)
    {
        Card karta = Stosy[numer_stosu-8].top();
        if( (karta.getZnak()=='K' and Plansze[numer_planszy-1].size()==0) or (karta.getValue()==Plansze[numer_planszy-1][Plansze[numer_planszy-1].size()-1].getValue()-1 and karta.getRed()!=Plansze[numer_planszy-1][Plansze[numer_planszy-1].size()-1].getRed()))
        {
            Stosy[numer_stosu-8].pop();
            Plansze[numer_planszy-1].push_back(karta);
        }
        else cout<<"Nie mozna wykonac takiego ruchu"<<endl;

    }
    else cout<<"Nie mozna wykonac takiego ruchu"<<endl;
}

void plansza_stos(vector<vector<Card>> &Plansze,int numer_planszy,int numer_stosu,vector<stack<Card>> &Stosy)
{
    if(Plansze[numer_planszy-1].size()>0)
    {
        Card karta = Plansze[numer_planszy-1].back();
        if((karta.getZnak()=='A' and Stosy[numer_stosu-8].size()==0)or(Stosy[numer_stosu-8].size() >0 and Stosy[numer_stosu-8].size()>0 and karta.getValue()==Stosy[numer_stosu-8].top().getValue()+1 and karta.getKolor()==Stosy[numer_stosu-8].top().getKolor()))
        {
            Stosy[numer_stosu-8].push(karta);
            Plansze[numer_planszy-1].pop_back();
            if(Plansze[numer_planszy-1].size()>0 and Plansze[numer_planszy-1].back().getVisible()==false) Plansze[numer_planszy-1].back().setVisible(true);
        }
        else cout<<"Nie mozna wykonac takiego ruchu"<<endl;
    }
    else cout<<"Nie mozna wykonac takiego ruchu"<<endl;
}

void plansza_plansza(vector<vector<Card>> &Plansze,int numer_planszy1,int numer_planszy2,char znak,char kolor)
{
    if(Plansze[numer_planszy1-1].size()>0)
    {
    bool flaga=false;
    int pozycja;
    if(Plansze[numer_planszy1-1].size()>0)
    {
        for(int i=0;i<Plansze[numer_planszy1-1].size();i++)
        {
            if(Plansze[numer_planszy1-1][i].getZnak()==znak&&Plansze[numer_planszy1-1][i].getKolor()==kolor and Plansze[numer_planszy1-1][i].getVisible()==true)
            {
                flaga=true;
                pozycja=i;
            }
        }
        if(flaga)
        {
        Card karta = Plansze[numer_planszy1-1][pozycja];
        int rozmiar = Plansze[numer_planszy1-1].size()-1;
        if(flaga and ((karta.getZnak()=='K' and Plansze[numer_planszy2-1].size()==0) or (karta.getValue()==Plansze[numer_planszy2-1][Plansze[numer_planszy2-1].size()-1].getValue()-1 and karta.getRed()!=Plansze[numer_planszy2-1][Plansze[numer_planszy2-1].size()-1].getRed())and(Plansze[numer_planszy2-1].size()!=0)))
        {
            for(int i=pozycja;i<=rozmiar;i++)
            {
                Plansze[numer_planszy2-1].push_back(Plansze[numer_planszy1-1][pozycja]);
                Plansze[numer_planszy1-1].erase(Plansze[numer_planszy1-1].begin()+pozycja);
            }

            if(Plansze[numer_planszy1-1].size()>0 and Plansze[numer_planszy1-1].back().getVisible()==false)
            { 
                Plansze[numer_planszy1-1].back().setVisible(true);
            }
        }
        else
        {
            cout<<"Nie mozna wykonac takiego ruchu"<<endl;
        }
      }
      else
        { 
            cout<<"Nie mozna wykonac takiego ruchu"<<endl; 
        }
    }
    else
        {
            cout<<"Nie mozna wykonac takiego ruchu"<<endl;
        }
    }
    else
    { 
            cout<<"Nie mozna wykonac takiego ruchu"<<endl; 
    }
    
}


void wypisz(vector<vector<Card>> &Plansze,vector<stack<Card>> &Stosy,vector<Card> &Widoczne)
{
    cout<<"      0                             8   9   10  11   "<<endl;
    for(int i=0;i<50;i++) cout<<"-";
    cout<<endl;
    if(Widoczne.size()!=0)
    {
        cout<<"    ";
        for(int i=0;i<Widoczne.size();i++)
        {
            cout<<Widoczne[i].getZnak()<<Widoczne[i].getKolor()<<" ";
        }
    }
    
    cout<<"                        ";
    for(int i=0;i<4;i++)
    {
        if(Stosy[i].size()==0) 
        {
            cout<<"0   ";
        }
        else 
        {
            cout<<Stosy[i].top().getZnak()<<Stosy[i].top().getKolor()<<"   ";
        }
    }
    cout<<endl;
    for(int i=0;i<50;i++) cout<<"-";
    cout<<endl;
    int dlugosc = znajdz_max(Plansze);
    for(int i=0;i<dlugosc;i++)
    {
        cout<<"|";
        for(int g=0;g<7;g++)
        {
            if(Plansze[g].size()>i)
            {
                if(Plansze[g][i].getVisible()==true)
                {
                    cout<<"  "<<Plansze[g][i].getZnak()<<Plansze[g][i].getKolor()<<"  ";
                }
                else 
                {
                    cout<<" ===  ";
                }
            }
            else
            {
                cout<<"      ";
            }

            cout<<"|";
        }
        cout<<endl;
    }
    cout<<"    1      2      3      4      5      6     7"<<endl;
    

}


int main()
{
    vector<Card> Talia;
    inicjalizacja(Talia);
    vector<vector<Card>> Plansze(7);
    vector<stack<Card>> Stosy(4);
    queue<Card> Nierozdane;
    vector<Card> Widoczne;
    tasowanie(Talia,Nierozdane,Plansze);
    wypisz(Plansze,Stosy,Widoczne);
    bool flag = true;
    while(flag)
    {
        cout<<"Podaj ruch: ";
        int ruch;
        cin>> ruch;
        
            if(ruch==0)
            {
                string znak;
                cin>>znak;
                if(znak=="r") kolejka_rozloz(Nierozdane,Widoczne);
                else
                {
                    int numer;
                    cin>>numer;
                    if(numer>=1 and numer <=7)
                    {
                        kolejka_plansza(Plansze,Nierozdane,Widoczne,numer);
                    }
                    else if (numer>=8 and numer <=11)
                    {
                        kolejka_stos(Widoczne,numer,Stosy,Nierozdane);
                    }
                    else
                    {
                        cout<<"Nie ma takiego numeru"<<endl;
                    }
                    
                }
                
            }
            else if (ruch>=1 and ruch<=7)
            {
                char znak;
                char kolor;
                int numer;
                cin>>znak>>kolor;
                cin>>numer;
                if(numer>=8 and numer<=11)
                {
                    plansza_stos(Plansze,ruch,numer,Stosy);
                }
                else if(numer>=1 and numer <=7)
                {
                    plansza_plansza(Plansze,ruch,numer,znak,kolor);
                }
                else
                {
                    cout<<"Nie ma takiego numeru"<<endl;
                }
            }
            else if (ruch>=8 and ruch<=11)
            {
                char znak;
                char kolor;
                int numer;
                cin>>znak>>kolor;
                cin>>numer;
                if(numer>=1 and numer<=7)
                {
                    stos_plansza(Stosy,ruch,numer,Plansze);
                }
                else cout<<"Nie ma takiego ruchu"<<endl;

            }
            else
            {
                cout<<"Nie ma takiego numeru"<<endl;
            }
        
        wypisz(Plansze,Stosy,Widoczne);

        flag = not check_win(Stosy);
    }
    cout<<"Wygrana"<<endl;
    

    return 0;
}