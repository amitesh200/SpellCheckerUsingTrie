#include<bits/stdc++.h>
using namespace std;

struct TrieNode
{
    struct TrieNode* children[26];
    bool endofWord;
};

struct TrieNode* getNode()
{
    struct TrieNode* root = new TrieNode;
    for(int i =0;i< 26; i++){
        root->children[i]=NULL;
    } 
    root->endofWord=false;
    return root;
}

void insertWord(struct TrieNode** root , string str){
    struct TrieNode* ptr = *root;
    int len = str.length();
    for(int i=0;i<len;i++){
        int index =str[i] - 'a';
        if(!ptr->children[index]){
            ptr->children[index]=getNode();
        }
        ptr=ptr->children[index];
    }
    ptr->endofWord=true;
}

bool searchWord(struct TrieNode* root ,string str){
    int len = str.length();
    for(int i=0;i<len;i++){
        int index =str[i] - 'a';
        if(root->children[index]==NULL){
            return false;
        }
        root=root->children[index];
    }
    return (root && root->endofWord);
}

void replace(struct TrieNode* root,string w){
    int len=w.length();
    int i;

  for(i=0;i<len;i++)
  {
      char c=w[i];
      char ch;
    for(ch='a';ch<='z';ch++)
    {   if(ch!=c)
        {
         w[i]=ch;

         if(searchWord(root,w)==true){
            cout<<w<<endl;}
        }
    }
  w[i]=c;
  }
}

void addLetter(struct TrieNode* root,string word){
        string  alphabets = "abcdefghijklmnopqrstuvwxyz";
        for(char c : alphabets){
            for(int i=0;i<=word.length();i++) {
                string newWord = word.substr(0,i) + c + word.substr(i,word.length());
                if(searchWord(root,newWord)){
                    cout<<newWord<<endl;
                    break;
                }
            }
        }
    }



int main()
{

    struct TrieNode* root =getNode();

    string line;
  ifstream myfile ("dictionary.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      insertWord(&root,line);
    }
    myfile.close();
  }


    string g;
   cout<<"Enter (mis-spelled)word:\n";
    cin>>g;

     bool i=searchWord(root,g);
        if(i==true)
            printf("FOUND");
  else
  {
  cout<<"do you mean"<<endl;
  replace(root,g);
  addLetter(root,g);
  }

return 0;
}
