#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <map>

using namespace std;

bool custom(vector<int> a, vector<int> b){
    return a[0]<b[0];
}

void sccmatrix(vector<vector<int>> & matrix){

    // check time
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();
        
    // the node stack we want to obtain
    stack<int> vert;
    // stack resulting by dfs
    stack<int> tmp;
    // recurring stack
    stack<int> buffer;
    // visited vector
    vector<int> visited(matrix.size(),0);

    // do dfs and gather terminating sequence
    stack<int> path;
    for(int i = 0; i < matrix.size() ; i++){
        if(visited[i]==0){
            int curr=i;
            path.push(i);
            visited[i]=1;
            while(path.size()!=0){
                int flag = 0;
                for(int j = 0 ; j < matrix.size();j++){
                    if(matrix[curr][j]==1&&visited[j]==0){
                        path.push(j);
                        flag = 1;
                        visited[path.top()]=1;
                        curr = path.top();
                        break;
                    }
                }
                if(flag==0){
                    // nowhere to go!
                    vert.push(curr);
                    path.pop();
                    if(path.size()!=0) curr = path.top();
                }
            }
        }
    }

    // make a reverted graph
    vector<vector<int>> trans(matrix.size(),vector<int>(matrix.size(),0));

    for(int i = 0 ; i < matrix.size() ; i++){
        for(int j = 0 ; j < matrix.size() ; j++){
            trans[j][i]=matrix[i][j];
        }
    }

    // do dfs on trans by vert order
    for(int i = 0 ; i < visited.size() ; i++){
        visited[i]=0;
    }

    vector<vector<int>> result;

    while(vert.size()!=0){
        int i = vert.top();
        vert.pop();
        if(visited[i]==0){
            buffer.push(i);
            result.push_back(vector<int>());
            while(buffer.size()!=0){
                int curr = buffer.top();
                if(visited[curr]==0){
                    result[result.size()-1].push_back(buffer.top());
                    visited[curr]=1;
                }
                buffer.pop();
                for(int j = 0 ; j < trans[curr].size() ; j++){
                    if(trans[curr][j]==1&&visited[j]==0){
                        buffer.push(j);
                    }
                }
            }
        }
    }
    
    end = chrono::high_resolution_clock::now();


    // sort and print result
    for(int i = 0 ; i < result.size() ; i++){
        sort(result[i].begin(),result[i].end());
    }

    sort(result.begin(),result.end(),custom);

    ofstream out("out1.txt");

    for(int i = 0 ; i < result.size() ; i++){
        for(int j = 0 ; j < result[i].size();j++){
            if(j==result[i].size()-1){
                out << (result[i][j]+1) << " " << endl;
            }else{
                out << (result[i][j]+1) << " " ;
            }
        }
    }

    out.close();

    // print time
    chrono::duration<double> elapsed_seconds = end - start;
    cout << elapsed_seconds.count() << "s" << endl;

}

void filldfs(int curr, vector<int> & visited, vector<vector<int>> & list, stack<int> & vert){
    if(visited[curr]==1) return;
    visited[curr]=1;
    for(int i = 0 ;i<list[curr].size();i++){
        if(visited[list[curr][i]]==0) filldfs(list[curr][i],visited,list,vert);
    }
    vert.push(curr);
}

void scclist(vector<vector<int>> & list){

    // check time
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();
        
    // the node stack we want to obtain
    stack<int> vert;
    // stack resulting by dfs
    stack<int> tmp;
    // recurring stack
    stack<int> buffer;
    // visited vector
    vector<int> visited(list.size(),0);

    // do dfs and gather terminating sequence
    stack<int> path;
    cout << list.size() << endl;
    for(int i = 0; i < list.size() ; i++){
        if(visited[i]==0){
            int curr=i;
            path.push(i);
            visited[i]=1;
            while(path.size()!=0){
                int flag = 0;
                for(int j = 0 ; j < list[curr].size();j++){
                    if(visited[list[curr][j]]==0){
                        path.push(list[curr][j]);
                        flag = 1;
                        visited[path.top()]=1;
                        curr = path.top();
                        break;
                    }
                }
                if(flag==0){
                    // nowhere to go!
                    vert.push(curr);
                    path.pop();
                    if(path.size()!=0) curr = path.top();
                }
            }
        }
    }

    // make a reverted graph
    vector<vector<int>> trans(list.size(),vector<int>());

    for(int i = 0 ; i < list.size() ; i++){
        for(int j = 0 ; j < list[i].size() ; j++){
            trans[list[i][j]].push_back(i);
        }
    }

    // do dfs on trans by vert order
    for(int i = 0 ; i < visited.size() ; i++){
        visited[i]=0;
    }

    vector<vector<int>> result;

    while(vert.size()!=0){
        int i = vert.top();
        vert.pop();
        if(visited[i]==0){
            buffer.push(i);
            result.push_back(vector<int>());
            while(buffer.size()!=0){
                int curr = buffer.top();
                if(visited[curr]==0){
                    result[result.size()-1].push_back(buffer.top());
                    visited[curr]=1;
                }
                buffer.pop();
                for(int j = 0 ; j < trans[curr].size() ; j++){
                    if(visited[trans[curr][j]]==0){
                        buffer.push(trans[curr][j]);
                    }
                }
            }
        }
    }
    
    end = chrono::high_resolution_clock::now();


    // sort and print result
    for(int i = 0 ; i < result.size() ; i++){
        sort(result[i].begin(),result[i].end());
    }

    sort(result.begin(),result.end(),custom);

    ofstream out("out2.txt");

    for(int i = 0 ; i < result.size() ; i++){
        for(int j = 0 ; j < result[i].size();j++){
            if(j==result[i].size()-1){
                out << (result[i][j]+1) << " " << endl;
            }else{
                out << (result[i][j]+1) << " " ;
            }
        }
    }

    out.close();

    // print time
    chrono::duration<double> elapsed_seconds = end - start;
    cout << elapsed_seconds.count() << "s" << endl;
}

void sccarray(vector<int> & ref, vector<int> & seq){


    // check time
    chrono::time_point<chrono::high_resolution_clock> start, end;
    start = chrono::high_resolution_clock::now();
        
    // the node stack we want to obtain
    stack<int> vert;
    // stack resulting by dfs
    stack<int> tmp;
    stack<int> buffer;
    // visited vector
    vector<int> visited(ref.size(),0);

    // do dfs and gather terminating sequence
    stack<int> path;

    for(int i = 0; i < ref.size() ; i++){
        if(visited[i]==0){
            int curr=i;
            path.push(i);
            visited[i]=1;
            while(path.size()!=0){
                int flag = 0;
                
                    for(int j = (curr==0)?0:ref[curr-1] ; j <= ref[curr]-1;j++){
                        if(visited[seq[j]]==0){
                            path.push(seq[j]);
                            flag = 1;
                            visited[path.top()]=1;
                            curr = path.top();
                            break;
                        }
                    }
                
                if(flag==0){
                    // nowhere to go!
                    vert.push(curr);
                    path.pop();
                    if(path.size()!=0) curr = path.top();
                }
            }
        }
    }

    cout << "here" << endl;

    // fill buffer
    vector<vector<int>> buffer2(ref.size(),vector<int>());
    
    for(int i = 0 ; i < ref.size() ; i++){
            for(int j = (i==0)?0:ref[i-1];j<=ref[i]-1;j++){
                buffer2[seq[j]].push_back(i);
            }
        
    }
  
    cout << "done one " << endl;
    // make a reverted graph

    vector<int> tref(ref.size(),0);
    vector<int> tseq(seq.size(),0);

    tref[0] = buffer2[0].size();
    for(int i = 1 ; i < buffer2.size() ; i++){
        
            tref[i] = tref[i-1] + buffer2[i].size();
        
    }

    cout << "done two" << endl;

    int count = 0;
    for(int i = 0 ; i < buffer2.size() ; i++){
        for(int j = 0 ; j < buffer2[i].size() ; j++){
            if(count>=seq.size()) cout << "sakk" << endl;
            tseq[count] = buffer2[i][j];
            count++;
        }
    }


    cout << "trans done" << endl;
    // do dfs on trans by vert order
    for(int i = 0 ; i < visited.size() ; i++){
        visited[i]=0;
    }

    vector<vector<int>> result;

    while(vert.size()!=0){
        int i = vert.top();
        vert.pop();
        if(visited[i]==0){
            buffer.push(i);
            result.push_back(vector<int>());
            while(buffer.size()!=0){
                int curr = buffer.top();
                if(visited[curr]==0){
                    result[result.size()-1].push_back(buffer.top());
                    visited[curr]=1;
                }
                buffer.pop();
                
                    for(int j = (curr==0)?0:tref[curr-1] ; j <= tref[curr]-1 ; j++){
                        if(visited[tseq[j]]==0){
                            buffer.push(tseq[j]);
                        }
                    }
                
            }
        }
    }
    
    end = chrono::high_resolution_clock::now();


    // sort and print result
    for(int i = 0 ; i < result.size() ; i++){
        sort(result[i].begin(),result[i].end());
    }

    sort(result.begin(),result.end(),custom);

    ofstream out("out3.txt");

    for(int i = 0 ; i < result.size() ; i++){
        for(int j = 0 ; j < result[i].size();j++){
            if(j==result[i].size()-1){
                out << (result[i][j]+1) << " " << endl;
            }else{
                out << (result[i][j]+1) << " " ;
            }
        }
    }

    out.close();

    // print time
    chrono::duration<double> elapsed_seconds = end - start;
    cout << elapsed_seconds.count() << "s" << endl;

}

int main(int argc, char ** argv){
    
    // check arguments
    if(argc!=2){
        cout << "[ERROR] invalid arguments";
        return 0;
    }

    // open file and initialize graphs
    ifstream openfile(argv[1]);

    int n;
    openfile >> n;
    vector<vector<int>> matrix(n,vector<int>(n,0));
    vector<vector<int>> adjlist(n,vector<int>()); 
    vector<int> arref;
    vector<int> arseq;

    for(int i = 0 ; i < n ; i++){
        int x;
        openfile >> x;
        for(int j = 0 ; j < x ; j++){
            int tmp;
            openfile >> tmp;
            tmp--;
            matrix[i][tmp]=1;
            adjlist[i].push_back(tmp);
            arseq.push_back(tmp);
        }
        arref.push_back(arseq.size());
    }

    cout << "before function" << endl;
    // print results
    sccmatrix(matrix);
    scclist(adjlist);
    sccarray(arref, arseq);

    return 0;
}