#include<bits/stdc++.h>
using namespace std;
vector<int> v[100001];vector<pair<int,int> >ans[100001];
int visit[100001],a[100001],f[1000001],maxdepth;
struct compare{
  bool operator()(pair<int,int> a,pair<int,int> b){
      if(a.first==b.first){
          return a.second<b.second;
          
      }
      return a.first<b.first;
  }  
};
void dfs(int i,int l){
    visit[i]=1;
    maxdepth=max(maxdepth,l);
    ans[l].push_back({f[a[i]],i});
    int j=0;
    while(j<v[i].size()){
        if(visit[v[i][j]]==0){
            dfs(v[i][j],l+1);
        }
        j++;
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for(int i=1;i<=1000000;i++){
        int j=1;
        while(j<=sqrt(i)){
            if(i%j==0){
                if(i/j==j){
                    f[i]++;
                }
                else{
                    f[i]+=2;
                }
            }
            j++;
        }
    }
    int n,q;cin>>n>>q;
    for(int i=0;i<n-1;i++){
        int x,y;cin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    dfs(1,1);
    vector<pair<int,int> > si;
    for(int i=1;i<=maxdepth;i++){
        sort(ans[i].begin(),ans[i].end());
        si.push_back({ans[i][0].first,i});
    }
    sort(si.begin(),si.end(),compare());
    int idx[maxdepth]={0};
    idx[0]=si[0].second;
    for(int i=1;i<maxdepth;i++){
        if(idx[i-1]>si[i].second){
            idx[i]=si[i].second;
        }
        else{
            idx[i]=idx[i-1];
        }
    }
   /* for(int i=0;i<maxdepth;i++){
        cout<<idx[i]<<" ";
    }
    cout<<endl; */
    //cout<<q<<endl;
 
    while(q--){
      //  cout<<"fuck"<<endl;
        int x;cin>>x;
        x=f[x];
        if(x<=si[0].first){
            cout<<"-1"<<endl;
            continue;
        }
        
        int low=0,high=maxdepth-1,lev;
        while(low<=high){
            int mid=(low+high)/2;
            if(si[mid].first==x){
                lev=idx[mid-1];
                high=mid-1;
            }
            else if(si[mid].first>x){
                high=mid-1;
            }
            else{
                low=mid+1;
            }
        }
        lev=idx[low-1];
        int tans=ans[lev][0].second;
        for(int j=1;j<ans[lev].size();j++){
            if(ans[lev][j].first<x){
                tans=min(tans,ans[lev][j].second);
            }
            else{
                break;
            }
        }
        cout<<tans<<endl;
    } 
}