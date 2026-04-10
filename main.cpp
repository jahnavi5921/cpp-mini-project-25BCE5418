#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Product {
private:
    int id;
    string name;
    double price;
    int qty;

public:
    Product(int i=0,string n="",double p=0,int q=0){
        id=i; name=n; price=p; qty=q;
    }

    int getID(){ return id; }
    string getName(){ return name; }
    double getPrice(){ return price; }
    int getQty(){ return qty; }

    void setQty(int q){ qty=q; }

    void display(){
        cout<<"ID:"<<id<<" Name:"<<name<<" Price:"<<price<<" Qty:"<<qty<<endl;
    }

    void save(ofstream &f){
        f<<id<<" "<<name<<" "<<price<<" "<<qty<<endl;
    }
};

class Inventory {
private:
    vector<Product> p;

public:

    void add(){
        int id,q; string n; double pr;
        cout<<"Enter ID Name Price Qty:\n";
        cin>>id>>n>>pr>>q;

        for(auto &x:p)
            if(x.getID()==id){
                cout<<"ID exists\n";
                return;
            }

        p.push_back(Product(id,n,pr,q));
    }

    void buy(){
        int id,q;
        cout<<"Enter ID Qty:\n";
        cin>>id>>q;

        for(auto &x:p)
            if(x.getID()==id){
                x.setQty(x.getQty()+q);
                return;
            }
        cout<<"Not found\n";
    }

    void sell(){
        int id,q;
        cout<<"Enter ID Qty:\n";
        cin>>id>>q;

        for(auto &x:p)
            if(x.getID()==id){
                if(x.getQty()<q){
                    cout<<"No stock\n";
                    return;
                }
                x.setQty(x.getQty()-q);
                return;
            }
        cout<<"Not found\n";
    }

    void search(){
        int id;
        cout<<"Enter ID:\n";
        cin>>id;

        for(auto &x:p)
            if(x.getID()==id){
                x.display();
                return;
            }
        cout<<"Not found\n";
    }

    void deleteP(){
        int id;
        cout<<"Enter ID:\n";
        cin>>id;

        for(int i=0;i<p.size();i++){
            if(p[i].getID()==id){
                char c;
                cout<<"Confirm delete (y/n): ";
                cin>>c;
                if(c=='y') p.erase(p.begin()+i);
                return;
            }
        }
        cout<<"Not found\n";
    }

    void low(){
        int t;
        cout<<"Enter threshold:\n";
        cin>>t;

        for(auto &x:p)
            if(x.getQty()<t)
                x.display();
    }

    void total(){
        double sum=0;
        for(auto &x:p)
            sum+=x.getPrice()*x.getQty();
        cout<<"Total value:"<<sum<<endl;
    }

    void show(){
        for(auto &x:p) x.display();
    }

    void save(){
        ofstream f("data.txt");
        for(auto &x:p) x.save(f);
        cout<<"Saved\n";
    }

    void load(){
        ifstream f("data.txt");
        int id,q; string n; double pr;
        p.clear();

        while(f>>id>>n>>pr>>q)
            p.push_back(Product(id,n,pr,q));

        cout<<"Loaded\n";
    }
};

int main(){
    Inventory i;
    int ch;

    do{
        cout<<"\n1.Add 2.Buy 3.Sell 4.Search 5.Delete 6.Low 7.Total 8.Show 9.Save 10.Load 11.Exit\n";
        cin>>ch;

        switch(ch){
            case 1:i.add(); break;
            case 2:i.buy(); break;
            case 3:i.sell(); break;
            case 4:i.search(); break;
            case 5:i.deleteP(); break;
            case 6:i.low(); break;
            case 7:i.total(); break;
            case 8:i.show(); break;
            case 9:i.save(); break;
            case 10:i.load(); break;
        }
    }while(ch!=11);
}


