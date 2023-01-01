#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<malloc.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>
//#include<sys/socket.h>
#include<winsock2.h>

#define size 5
#define numberOfPlaces 20

typedef struct{char place[30];}list;

typedef struct node{int data;struct node* next;}node;

typedef struct cart{char food[30];int price;struct cart* next;}cart;

typedef struct tree{char food[30];int price;struct tree* left;struct tree* right;}tree;

typedef struct{int front;int rear;char vals[size][30];}queue;

queue cabUsers,mealCustomers;

void init(queue* q)
{
    q->front=q->rear=-1;
}

int isFull(queue* q)
{
    return (q->rear==q->front-1 || (q->front==0 && q->rear==size-1));
}

int isEmpty(queue* q)
{
    return (q->rear==-1 && q->front==-1);
}

char* frontData(queue* q)
{
    char* a;
    a=(char*)malloc(sizeof(char)*40);
    strcpy(a,q->vals[q->front]);
    return a;
}

int isInQueue(queue* q,char* data)
{
    int i;
    for(i=q->front;i<=q->rear;i++)
        if(strcmp(q->vals[i],data)==0)
            return 1;
    return 0;



}

int insertData(queue* q,char* data)
{
    if(isFull(q))
        return 0;
    if(q->front==-1 && q->rear==-1)
    {
        q->rear=q->front=0;
    }
    else if(q->rear==size-1)
    {
        q->rear=0;
    }
    else
        q->rear++;
    strcpy(q->vals[q->rear],data);
    return 1;
}

int deleteData(queue* q,char* data)
{
    if(isEmpty(q))
        return 0;
    strcpy(data,q->vals[q->front]);
    if(q->front==q->rear)
        q->front=q->rear=-1;
    else if(q->front==size-1)
        q->front=0;
    else
        q->front++;
    return 1;
}

void display(queue* q)
{
    int i;
    if(isEmpty(q))
    {
        printf("\nEmpty queue\n");
        return;
    }
    printf("\n");
    if(q->front>q->rear)
    {
        for(i=q->front;i<size;i++)
            printf("%s  ",q->vals[i]);
        for(i=0;i<=q->rear;i++)
            printf("%s  ",q->vals[i]);
    }
    else
    {
        for(i=q->front;i<=q->rear;i++)
            printf("%s  ",q->vals[i]);
    }
    printf("\n");
}
//queue implementation ends

cart* createCart()
{
    cart* t=NULL;
    return t;
}

cart* makeCart(char* food,int price)
{
    cart* t=(cart*)malloc(sizeof(cart));
    strcpy(t->food,food);
    t->price=price;
    t->next=NULL;
    return t;
}

cart* insertCart(cart* root,char* food,int price)
{
    cart* t=makeCart(food,price);
    if(!root)
        return t;
    cart* p=root;
    while(p->next)
        p=p->next;
    p->next=t;
    return root;
}

cart* deleteCart(cart* root,char* food)
{
    if(!root)
        return root;
    if(strcmp(root->food,food)==0)
        return root->next;
    root->next=deleteCart(root->next,food);
    return root;
}

void displayCart(cart* root)
{
    int i=1,total=0;
    printf("\n            Your Cart is \n\n");
    while(root)
    {
        printf("            %2d.%-20s-  Rs.%d\n",i++,root->food,root->price);
        total+=root->price;
        root=root->next;
    }
    printf("\n            -----------------------------------------------------------\n");
    printf("            %-23s-  Rs.%d\n","Total",total);
    printf("\n            -----------------------------------------------------------\n");
    printf("\n");
}

node* createNode()
{
    node* temp=NULL;
    return temp;
}

node* makeNode(int data)
{
    node* temp=(node*)malloc(sizeof(node));
    temp->data=data;
    temp->next=NULL;
    return temp;
}

node* insertHead(node* root,int data)
{
    node* t=root;
    node* temp=makeNode(data);
    if(!t)
        return temp;
    temp->next=root;
    return temp;
}

tree* createTree()
{
    tree* t=NULL;
    return t;
}

tree* makeTree(char* food,int price)
{
    tree* t=(tree*)malloc(sizeof(tree));
    strcpy(t->food,food);
    t->price=price;
    t->left=NULL;
    t->right=NULL;
    return t;
}

tree* insertTree(tree* root,char* food,int price)
{
    tree* t=makeTree(food,price);
    if(!root)
        return t;
    if(strcmp(food,root->food)>0)
        root->right=insertTree(root->right,food,price);
    else
        root->left=insertTree(root->left,food,price);
    return root;
}

int findPrice(tree* root,char* food)
{
    if(!root)
        return 0;
    if(strcmp(root->food,food)>0)
        return findPrice(root->left,food);
    else if(strcmp(root->food,food)<0)
        return findPrice(root->right,food);
    else
        return root->price;
}

void printTree(tree* t)
{
    if(t)
    {
        printTree(t->left);
        printf("\n            %-20s - Rs. %d",t->food,t->price);
        printTree(t->right);
    }
}

void printPath(node* route,list* locations)
{
    printf("\n             Optimal route is \n\n             ");
    while(route->next)
    {
        printf("%s-->",locations[route->data].place);
        route=route->next;
    }
    printf("%s \n",locations[route->data].place);
}

bool isValidEmail(char* email)
{
    int i,j,l,flag=0,flag2=0;
    char n[30],pass[30],e[30];
    FILE* fp;
    fp=fopen("login.txt","r");
    if(fp==NULL)
        return false;
    while(!feof(fp))
    {
        fscanf(fp,"%s %s %s\n",n,pass,e);
        if(strcmp(e,email)==0)
        {
            printf("\nEmail already registered\n");
            return false;
        }
    }
    l=strlen(email);
    for(i=0;i<l;i++)
    {
        if(email[i]=='@')
        {
            flag=1;
            for(j=i+1;j<l;j++)
            {
                if(email[j]=='.')
                {
                    flag2=1;
                    if(j-i <= 4 )
                    {
                        printf("\nInvalid Email\n");
                        return false;
                    }
                    else if(strcmp(email+j,".com")!=0)
                    {
                        printf("\nInvalid Email\n");
                        return false;
                    }
                }
            }
        }
    }
    if(flag==0 || flag2==0)
    {
        printf("\nInvalid Email\n");
        return false;
    }
    return true;
}

bool isValidUsername(char* name)
{
    char n[30],pass[30],email[30];
    FILE* fp;
    fp=fopen("login.txt","r");
    if(fp==NULL)
        return false;
    while(!feof(fp))
    {
        fscanf(fp,"%s %s %s\n",n,pass,email);
        if(strcmp(n,name)==0)
            return false;
    }
    return true;
}

bool isStrong(char* pass)
{
    int n=0,c=0,s=0,i;
    for(i=0;pass[i]!='\0';i++)
    {
        if(pass[i]>='A' && pass[i]<='Z')
            c++;
        if(pass[i]>='0' && pass[i]<='9')
            n++;
        if(!((pass[i]>='a' && pass[i]<='z') || (pass[i]>='A' && pass[i]<='Z') || (pass[i]>='0' && pass[i]<='9')))
            s++;
    }
    if(s && n && c)
        return true;
    return false;
}

bool signUp()
{
    char name[50],password[30],email[50];
    int i;
    FILE* fp;
    fp=fopen("login.txt","a");
    if(fp==NULL)
    {
        printf("\n            Error...\n");
        return false;
    }
    else
    {
        usern:
        printf("\n            Create Username: ");
        scanf("%s",name);
        if(!isValidUsername(name))
        {
            printf("\n            Username already taken\n            Please try another username\n");
            goto usern;
            //return false;
        }
        pass:
        i=0;
        printf("\n            Create a strong Password: ");
        do
        {
            password[i]=getch();
            if(password[i]!='\r')
                printf("*");
            i++;
        }while(password[i-1]!='\r');
        password[i-1]='\0';
        if(!isStrong(password))
        {
            printf("\n            Use atleast 1 caps, 1 number and 1 special character to make a strong password\n");
            goto pass;
        }
        //scanf("%s",password);
        em:
        printf("\n\n            Enter Email address: ");
        scanf("%s",email);
        if(isValidEmail(email))
        {
            fprintf(fp,"%s %s %s\n",name,password,email);
            printf("\n            Successfully signed Up\n");
        }
        else
        {
            //printf("\nInvalid email\n");
            goto em;
            //return false;
        }
    }
    fclose(fp);
    return true;
}

bool login(char* user)
{
    char name[50],password[30],nameCheck[50],passwordCheck[30],email[50];
    int i=0;
    FILE* fp;
    fp=fopen("login.txt","r");
    if(fp==NULL)
    {
        printf("\n            Error...\n");
        return false;
    }
    else
    {
        printf("\n            Enter Username: ");
        scanf("%s",name);
        printf("\n            Enter password: ");
        do
        {
            password[i]=getch();
            if(password[i]!='\r')
                printf("*");
            i++;
        }while(password[i-1]!='\r');
        password[i-1]='\0';
        //scanf("%s",password);
        while(!feof(fp))
        {
            fscanf(fp,"%s %s %s\n",nameCheck,passwordCheck,email);
            if(strcmp(name,nameCheck)==0 && strcmp(password,passwordCheck)==0)
            {
                strcpy(user,name);
                return true;
            }

        }
    }
    fclose(fp);
    return false;
}

bool isPresent(char* place,list* locations,int* index)
{
    int i;
    for(i=0;i<20;i++)
    {
        if(strcmp(place,locations[i].place)==0)
        {
            *index=i;
            return true;
        }
    }
    return false;
}

int** memoryAllocate(int n)
{
    int** a,i;
    a=(int**)malloc(sizeof(int*)*n);
    for(i=0;i<n;i++)
        a[i]=(int*)malloc(sizeof(int)*n);
    return a;
}

int** createMap()
{
    int** map,i,j;
    map=memoryAllocate(20);
    FILE* fp=fopen("map.txt","r");
    for(i=0;i<20;i++)
    {
        for(j=0;j<20;j++)
        {
            fscanf(fp,"%d",&map[i][j]);
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
    return map;
}

void printMatrix(int** mat,int n)
{
    int i,j;
    printf("\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            if(mat[i][j]==INT_MAX)
                printf("  #");
            else
                printf("%3d",mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

int priceCalculate(int** map,int source,int destination)
{
    printf("\n            Cost for 1km travel is Rs.4\n");
    return map[source][destination]*4;
}

void shortestPath(int** map,list* locations,int n,int source,int destination)
{
    int** dist,i,j,k,**path;
    node* route=createNode();
    dist=memoryAllocate(n);
    path=memoryAllocate(n);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            dist[i][j]=map[i][j],dist[i][i]=0,path[i][j]=i;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<n;k++)
            {
                if(dist[i][j]>dist[i][k]+dist[k][j])
                {
                    dist[i][j]=dist[i][k]+dist[k][j];
                    path[i][j]=path[k][j];
                }
            }
        }
    }
    //printMatrix(dist,n);
    //printMatrix(path,n);
    route=insertHead(route,destination);
    i=destination;
    while(i!=source)
    {
        i=path[source][i];
        route=insertHead(route,i);
    }
    printf("\n             --------------------------------------------------- \n");
    printPath(route,locations);
    printf("\n             --------------------------------------------------- \n");
    int amount=priceCalculate(dist,source,destination);
    printf("\n            Total cost of journey is %d\n",amount);

}

bool cab(char* user)
{
    char source[30],destination[30];
    int s,d;
    char ch[4];
    printf("\n             --------------------------------------------------- \n");
    printf("            |  Services available for the following locations:  |\n");
    printf("            | Tambaram                                          |\n");
    printf("            | Chromepet                                         |\n");
    printf("            | Pallavaram                                        |\n");
    printf("            | Perungudi                                         |\n");
    printf("            | Park                                              |\n");
    printf("            | Central                                           |\n");
    printf("            | Chitlapaakam                                      |\n");
    printf("            | Airport                                           |\n");
    printf("            | Beach                                             |\n");
    printf("            | Meenambakkam                                      |\n");
    printf("            | Palathavangal                                     |\n");
    printf("            | Alandur                                           |\n");
    printf("            | Guindy                                            |\n");
    printf("            | Adayar                                            |\n");
    printf("            | Nungambakkam                                      |\n");
    printf("            | Egmore                                            |\n");
    printf("            | Koyambedu                                         |\n");
    printf("            | Porur                                             |\n");
    printf("            | Valechery                                         |\n");
    printf("            | Perungalathur                                     |\n");
    printf("             --------------------------------------------------- \n");
    printf("\n            Enter your location, %s : ",user);
    scanf("%s",source);
    printf("\n            Enter destination, %s : ",user);
    scanf("%s",destination);
    list locations[20];
    int** map;
    map=memoryAllocate(20);
    map=createMap(map);
    int i;
    FILE* fp=fopen("locations.txt","r");
    for(i=0;i<numberOfPlaces;i++)
    {
        fscanf(fp,"%s\n",locations[i].place);
    }
    if(isPresent(source,locations,&s) && isPresent(destination,locations,&d))
    {
        shortestPath(map,locations,numberOfPlaces,s,d);
        printf("\n            %s, are you sure You want to book ? ",user);
        scanf("%s",ch);
        if(strcmp(ch,"yes")==0 || strcmp(ch,"Yes")==0 || strcmp(ch,"YES")==0)
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

void displayMenu(tree* foodItems)
{
    printf("\n            MENU: \n");
    printTree(foodItems);
    printf("\n");
}

bool isInMenu(tree* foodItems,char* food)
{
    if(!foodItems)
        return 0;
    if(strcmp(foodItems->food,food)>0)
        return isInMenu(foodItems->left,food);
    else if(strcmp(foodItems->food,food)<0)
        return isInMenu(foodItems->right,food);
    else if(strcmp(foodItems->food,food)==0)
        return 1;
    return 0;
}

bool meals(char* user)
{
    FILE* fp=fopen("foodmenu.txt","r");
    int i,ch;
    char food[20];
    cart* order=createCart();
    tree* foodItems=createTree();
    int price,total=0;
    for(i=0;i<10;i++)
    {
        fscanf(fp,"%s %d\n",food,&price);
        foodItems=insertTree(foodItems,food,price);
    }
    while(1)
    {
        printf("\n            -----------------------------------------------------\n");
        printf("            |  1.Add Food to Cart                               |\n");
        printf("            |  2.Delete from Cart                               |\n");
        printf("            |  3.Display Cart                                   |\n");
        printf("            |  4.Place Order                                    |\n");
        printf("            |  5.Display Menu                                   |\n");
        printf("            |  6.Cancel Order                                   |\n");
        printf("            -----------------------------------------------------\n");
        printf("\n            Enter Your Choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                printf("\n            Enter your dish %s : ",user);
                scanf("%s",food);
                if(isInMenu(foodItems,food))
                {
                    price=findPrice(foodItems,food);
                    total+=price;
                    order=insertCart(order,food,price);
                }
                else
                {
                    printf("\n            This Item is not in the Menu\n");
                }
                break;
            case 2:
                printf("\n            Enter the dish to remove from cart: ");
                scanf("%s",food);
                total-=findPrice(foodItems,food);
                order=deleteCart(order,food);
                break;
            case 3:
                displayCart(order);
                break;
            case 4:
                printf("\n            Are you sure to place order,%s ? ",user);
                scanf("%s",food);
                if(strcmp(food,"yes")==0 || strcmp(food,"Yes")==0 || strcmp(food,"YES")==0)
                    return true;
                break;
            case 5:
                displayMenu(foodItems);
                break;
            case 6:
                return false;
            default:
                printf("\n            Please enter a valid choice\n");
        }
    }

    return true;
}

void shop(char* user)
{
    int ch;
    while(1)
    {
        printf("\n            -----------------------------------------------------\n");
        printf("            |  1.Book Cab                                       |\n");
        printf("            |  2.Order Food                                     |\n");
        printf("            |  3.Log Out                                        |\n");
        printf("            -----------------------------------------------------\n");
        printf("\n            Enter Your Choice %s : ",user);
        scanf("%d",&ch);
        system("cls");
        switch(ch)
        {
            case 1:
                if(cab(user))
                {
                    if(insertData(&cabUsers,user))
                        printf("\n            Cab successfully booked\n");
                    else
                        printf("\n            Sorry...queue is full..Please wait for a moment\n");
                }
                else
                    printf("\n            There was an error while booking..Please try again later\n");
                Sleep(800);
                system("cls");
                break;
            case 2:
                if(meals(user))
                {
                    if(insertData(&mealCustomers,user))
                        printf("\n            Order successfully placed\n");
                    else
                        printf("\n            Sorry...queue is full..Please wait for a moment\n");
                }
                else
                    printf("\n            There was an error while placing order..Please try again later\n");
                Sleep(800);
                system("cls");
                break;
            case 3:
                return;
        }
    }
}

int main()
{
    int ch;
    init(&cabUsers);
    init(&mealCustomers);
    char user[30];

    //change font color
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    SetConsoleTextAttribute(hConsole, saved_attributes);

    while(1)
    {
        printf("\n            -----------------------------------------------------\n");
        printf("            |                       UBER                        |\n");
        printf("            |  1.Create New account                             |\n");
        printf("            |  2.Login                                          |\n");
        printf("            |  3.Claim Order                                    |\n");
        printf("            |  4.Exit                                           |\n");
        printf("            -----------------------------------------------------\n");
        printf("\n            Enter Your Choice: ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                signUp();
                break;
            case 2:
                if(login(user))
                {
                    SetConsoleTextAttribute(hConsole, 2);
                    printf("\n\n            Successfully logged in");
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                    Sleep(1000);
                    system("cls");
                    shop(user);
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("\n\n            Login failed");
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                }
                break;
            case 3:
                if(login(user))
                {
                    if(strcmp(user,frontData(&mealCustomers))==0)
                    {
                        deleteData(&mealCustomers,user);
                        SetConsoleTextAttribute(hConsole, 2);
                        printf("\n\n            %s...Please pick your order",user);
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                    else if(isInQueue(&mealCustomers,user))
                    {
                        SetConsoleTextAttribute(hConsole, 4);
                        printf("\n\n            Kindly wait in the queue to get served");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                    else
                    {
                        SetConsoleTextAttribute(hConsole, 4);
                        printf("\n\n            Please order something to claim the order");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 4);
                    printf("\n\n            Invalid credentials");
                    SetConsoleTextAttribute(hConsole, saved_attributes);
                }
                break;
            case 4:
                exit(0);
            default:
                SetConsoleTextAttribute(hConsole, 4);
                printf("\n            Invalid input");
                SetConsoleTextAttribute(hConsole, saved_attributes);
                break;
        }
        Sleep(1000);
        system("cls");
    }
    return 0;
}
