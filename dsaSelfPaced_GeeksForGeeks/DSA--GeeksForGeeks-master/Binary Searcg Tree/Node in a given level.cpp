/*
if L is grater than max level return 0
*/

int Count(Node *node,int L){
    if(!node)
        return 0;
      queue<Node*> res;
      res.push(node);
      int level=0;
      while(!res.empty()){
          ++level;
        int nodesInQueue=res.size();
        for(int i=0;i<nodesInQueue;i++){
            Node *temp=res.front();
            res.pop();
            if(temp->left)
                res.push(temp->left);
            if(temp->right)
                res.push(temp->right);
        }
        if(level==L)
            return nodesInQueue;
      }
      return 0;
}
