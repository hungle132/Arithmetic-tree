#include "arithmeticExpression.h"
arithmeticExpression::arithmeticExpression(const string & word){

    infixExpression = word;

    //root == nullptr;

}

void arithmeticExpression::infix(TreeNode* point){

    if ( point == nullptr ){
        return;
    }
    
    if(priority(point->data) != 0){

    cout << "(";
    
    }
    
    infix( point->left );
    
    cout << point->data;

    infix( point->right );

    
    if(priority(point->data) != 0 ){
    
    cout << ")";
    
    }
}
void arithmeticExpression::infix(){

    infix(root);

}
void arithmeticExpression::prefix(TreeNode * point){

    if ( point == nullptr ){
        return;
    }

    cout << point->data;
    
    prefix( point->left );

    prefix( point->right );

}
void arithmeticExpression::prefix(){

    prefix(root);

}
void arithmeticExpression::postfix(TreeNode * point){

    if ( point == nullptr ){
        return;
    }

    postfix( point->left );

    postfix( point->right );

    cout << point->data;

}
void arithmeticExpression::postfix(){

    postfix(root);

}

void arithmeticExpression::buildTree(){

   //arithmeticExpression temp = new arithmeticExpression (infixExpression);
   string post = infix_to_postfix();
   char letter = 'a';
   stack <TreeNode*> tree;
   for (unsigned int i = 0 ; i < post.size(); i++){
       if ((post.at(i) != '(') && (post.at(i) != ')') && (post.at(i) != '*') && (post.at(i) != '+') && (post.at(i) != '-') && (post.at(i) != '/')){ //checking for operators
           char key = letter;
           TreeNode* temp = new TreeNode (post.at(i), key);
           //TreeNode* point = temp;
           tree.push(temp);
           letter++;
       }
       else if (i == post.size()-1){ //last operator
           char key= post.at(i);
           TreeNode* temp = new TreeNode(post.at(i),key);
           TreeNode* r = tree.top();
           tree.pop();
           TreeNode* l = tree.top();
           tree.pop();
           temp->right = r;
           temp->left = l;
           root = temp;
           //cout << "here";
           //tree.push(temp);
       }
       else{ //for signs
           char key = post.at(i);
           TreeNode* r = tree.top();
           tree.pop();
           TreeNode* l = tree.top();
           tree.pop();
           TreeNode* sign = new TreeNode(post.at(i),key);
           sign->right = r;
           sign->left = l;
           //TreeNode* point = sign;
           tree.push(sign);
       }
   }
   //test for root
   //TreeNode* temp = root;
   //TreeNode* temp = tree.top();
   //cout << temp->data << endl;
   //cout << temp->left->data << endl;
   //cout << temp->right->data << endl;
   //tree.pop();
   //cout << temp->data << endl;
   //tree.pop();
   //cout << temp->data << endl;
}

int arithmeticExpression::priority(char op){
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}
/*
void arithmeticExpression::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
*/