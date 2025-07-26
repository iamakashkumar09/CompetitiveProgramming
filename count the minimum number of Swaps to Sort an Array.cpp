// count the minimum number of Swaps to Sort an Array

int count(vector<int>&arr){
    vector<int>a=arr;
    sort(a.begin(),a.end());
    unordered_map<int,int>um;
    for(int i=0;i<a.size();i++){
        um[a[i]]=i;
    }
    vector<bool>visited(arr.size(),false);
    int ans=0;
    for(int i=0;i<arr.size();i++){
        if(visited[i]||um[arr[i]]==i) continue;
        int j=i;
        int cycle=0;
        while(!visited[j]){
            visited[j]=true;
            j=um[arr[j]];
            cycle++;
        }

        if(cycle>1){
            ans+=cycle-1;
        }
    }
    return ans;
}
