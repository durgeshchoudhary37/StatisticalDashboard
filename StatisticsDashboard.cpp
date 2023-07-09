#include <bits/stdc++.h>
using namespace std;

using lli=long long int; //alias for long long

// function the maintain median after each query
struct maintain_median{
    multiset<lli> smaller,larger;
    
    // function to rearrange the integer added in the multisets
    void rearrange(){ 
        if(larger.size()>smaller.size()){
            smaller.insert(*larger.begin());
            larger.erase(larger.begin());
        }
        else if(smaller.size()-larger.size()>1){
            larger.insert(*smaller.rbegin());
            smaller.erase(--smaller.end());
        }
    }

    // adding integer according to the value and then rearranging
    void add(lli x){
        if(smaller.empty() || x<=*smaller.rbegin()){
            smaller.insert(x);
        }
        else{
            larger.insert(x);
        }

        rearrange();
    }

    // removing the integer if available and then rearranging
    void remove(lli x){
        if(smaller.find(x)!=smaller.end()){
            smaller.erase(smaller.find(x));
        }
        else if(larger.find(x)!=larger.end()){
            larger.erase(larger.find(x));
        }

        rearrange();
    }

    // function returns the median which can be a double if number of elements is even
    double get_median(){
        lli count=smaller.size()+larger.size();
        if(count%2==1){
            return *smaller.rbegin();
        }
        else{
            double value=*smaller.rbegin()+*larger.begin();
            return value/2;
        }
    }
};

// function to maintain mode after each query
struct maintain_mode{
    map<lli,lli> mp;
    multiset<pair<lli,lli>> mt;

    // adding a key to the map or increasing the frequency of the key if available
    void add(lli x){
        if(mp.find(x)!=mp.end()){
            mt.erase(mt.find(make_pair(mp[x],x)));
        }
        mp[x]++;
        mt.insert(make_pair(mp[x],x));
    }

    // reducing the frequency of the key if available
    void remove(lli x){
        if(mp.find(x)!=mp.end()){
            mt.erase(mt.find(make_pair(mp[x],x)));
        }
        mp[x]--;
        mt.insert(make_pair(mp[x],x));
    }

    // returns the mode
    lli get_mode(){
        auto it=mt.rbegin();
        lli value=it->second;
        return value;
    }


};

struct Dashboard{

    multiset<lli> mt;
    lli sum=0,count=0,sum_sq=0;
    maintain_median m;
    maintain_mode mymode;

    // adding integers
    void add(lli x){
        mt.insert(x);
        sum+=x;
        sum_sq+=x*x;
        count+=1;

        m.add(x);
        mymode.add(x);
    }

    // removing integers
    void remove(lli x){
        if(mt.find(x)!=mt.end()){
            mt.erase(mt.find(x));
            sum-=x;
            sum_sq-=x*x;
            count-=1;
            m.remove(x);
            mymode.remove(x);
        }
    }

    // getting the mean of the integers
    double get_mean(){
        return (double)sum/count;
    }

    // getting the variance of the integers
    double get_variance(){
        return (double)sum_sq/count - get_mean()*get_mean();
    }

    // getting the median of the integers
    double get_median(){
        return m.get_median();
    }   

    // getting the mode of the integers
    lli get_mode(){
        return mymode.get_mode();
    }

    // getting all the integers
    vector<lli> show_all(){
        vector<lli> temp;
        for(auto v:mt){
            temp.push_back(v);
        }
        return temp;
    }


};

void solve(){
    Dashboard dash;
    
    // explaining the functioning to the user
    cout<<"1. ADD an integer x"<<endl;
    cout<<"2. REMOVE an integer x"<<endl;
    cout<<"3. Get the MEAN of integers in the dashboard"<<endl;
    cout<<"4. Get the VARIANCE of integers in the dashboard"<<endl;
    cout<<"5. Get the MEDIAN of integers in the dashboard"<<endl;
    cout<<"6. Get the MODE of integers in the dashboard"<<endl;
    cout<<"7. Show all integers in the dashboard"<<endl;
    cout<<"8. Exit"<<endl;
    cout<<"Enter the query type and an integer for queries 1 and 2"<<endl<<endl;

    // working with the queries and calling the required functions
    lli t,x;
    while(true){
        cin>>t;
        if(t==1){
            cin>>x;
            dash.add(x);
        }
        else if(t==2){
            cin>>x;
            dash.remove(x);
        }
        else if(t==3){
            cout<<"The MEAN of numbers in the dashboard is "<<dash.get_mean()<<endl;
        }
        else if(t==4){
            cout<<"The VARIANCE of numbers in the dashboard is "<<dash.get_variance()<<endl;
        }
        else if(t==5){
            cout<<"The MEDIAN of numbers in the dashboard is "<<dash.get_median()<<endl;
        }
        else if(t==6){
            cout<<"The MODE of numbers in the dashboard is "<<dash.get_mode()<<endl;
        }
        else if(t==7){
            vector<lli> temp=dash.show_all();
            cout<<"The numbers in the dashboard are: ";
            for(auto v:temp){
                cout<<v<<" ";
            }
            cout<<endl;
        }
        else if(t==8){
            cout<<"Exiting the dashboard..."<<endl;
            return;
        }
        else{
            cout<<"Invalid query... try again"<<endl;
        }
    }

    
}

// defining the main function and optimizing input and output functions
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    solve();
}