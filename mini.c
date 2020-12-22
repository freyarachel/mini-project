#include<conio.h>  
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void clrscr(void)
{
    system("cls");
}

void gotoxy(int x,int y)    
{
    printf("%c[%d;%df",0x1B,y,x);
}

struct details
{
	char name[30];
	char pass[30];
}w[99];

struct Product
{
	int id;
	char name[20];
	int price;
	int qty;
}; 

struct Bill
{
	char user[30];
	int pid;
	char pname[20];
	int pprice;
};

static int i=0;	
int n;
int total=0;

void login(void);
void registration(void);
void OwnerLogin(void);
void manageProduct(void);
void addProduct(void);
void displayAllProducts(void);
void appendQuantity(void);
struct Product changeQuantity(int,int);
void allBills(void);
void specificBill(void);
void userBill(void);
void numberBill(void);
void totalPurchases(void);
void purchaseProduct(char[]);
void displayPreviousBills(char[]);
struct Product findProduct(int);
void updateProduct(int,int);
void generateBill(char[]);

int getID(void);
int billFileNo(void);

char fname[]={"product.dat"};
char fbill[]={"bill.dat"};
char fAll[]={"all.dat"};

int main()
{
	clrscr();
	gotoxy(50,10);
    printf("WELCOME ");
	gotoxy(50,11);
	printf("=======");
	gotoxy(40,15);
	printf("Click on Enter to proceed...");
	if(getch()==13)
		clrscr();
	X:
	printf("\n\n\n\n\t\t\t1. LOGIN(as customer)\t\t2. REGISTER\t\t3.LOGIN(as owner)\t\t4.Exit");
	printf("\n\n\n\t\t\t\tENTER YOUR CHOICE: ");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
		{
			clrscr();
			login();
			break;
		}
		case 2:
		{
			clrscr();
			registration();
			break;
		}
		case 3:
		{
			clrscr();
			OwnerLogin();
			break;
		}
		case 4:
		{
			break;
		}
		default: 
		{
			printf("\n\n\t\t\t\t INVALID CHOICE");
			printf("\n\n\t\t\tClick on Enter to re-Enter your choice...");
			if(getch()==13)
				clrscr();
			goto X;
		}
	}
	return 0;
}

void registration()
{
	FILE *fp,*fp1;
    char c,username[30];
	int z=0;
    fp=fopen("Web_reg.txt","ab");
	fp1=fopen("Web_reg.txt","rb");
	D:
    printf("\n\n\t\t\t\tWELCOME TO REGISTRATION ZONE");
    printf("\n\t\t\t\t----------------------------");
    for(i=0;i<100;i++)
    {
		printf("\n\n\t\t\t\t  ENTER USERNAME: ");
		scanf("%s",username);
        while(!feof(fp1))
        {
			fread(&w[i],sizeof(w[i]),1,fp1);
			if(strcmp(username,w[i].name)==0)
            {
                printf("\n\n\t\t\tTHIS USERNAME ALREDY EXISTS");
				getch();
				goto D;
            }
		}
		strcpy(w[i].name,username);
		fclose(fp1);
		printf("\n\n\t\t\t\t ENTER DESIRED PASSWORD: ");
		while((c=getch())!=13)
        {
			w[i].pass[z++]=c;
			printf("%c",c);
        }
		
		fwrite(&w[i],sizeof(w[i]),1,fp);
		fclose(fp);
		
        printf("\n\n\n\t\tPress enter if you agree with your Username and Password");
        if((c=getch())==13)
        {
			clrscr();
			printf("\n\n\t\tYour registration is completed successfully");
			printf("\n\n\t\tDo you want to login into your account ?\n\n\t\t  ");
			printf("> PRESS 1 IF 'YES'\n\n\t\t  > PRESS 2 IF 'NO'\n\n\t\t\t\t");
			scanf("%d",&n);
			switch(n)
			{
				case 1: 
				{
					clrscr();
                    login();
                    break;
				}
              case 2:
			  {
				    clrscr();
                    printf("\n\n\n\t\t\t\t\tTHANK YOU FOR REGISTERING");
                    break;
				}
			}
			break;
        }
        break;
    }
    getch();
}

void login()
{
    FILE *fp;
    char c,name[30],pass[30];
	int z=0,ch;
    int checku,checkp;
	
    fp=fopen("Web_reg.txt","rb");
	
    printf("\n\n\t\t\t\tWELCOME TO LOGIN ZONE");
    printf("\n\t\t\t\t---------------------");
    for(i=0;i<1000;i++)
    {
        printf("\n\n\t\t\t\t  ENTER USERNAME: ");
        scanf("%s",name);
        printf("\n\n\t\t\t\t  ENTER PASSWORD: ");
        while((c=getch())!=13)
        {
            pass[z++]=c;
            printf("%c",'*');
        }
        pass[z]='\0';
		
		if(fp==NULL)
		{
			printf("\n\n\n\t\t\tYou are not a Registered User\n\n \t\t\tPress enter to register yourself");
			if(getch()==13)
				clrscr();
			registration();
		}
			
		while(!feof(fp))
        {
			fread(&w[i],sizeof(w[i]),1,fp);
			
			checku=strcmp(name,w[i].name);
			checkp=strcmp(pass,w[i].pass);
			if(checku==0&&checkp==0)
			{
				clrscr();
				printf("\n\n\n\t\t\tYOU HAVE LOGGED IN SUCCESSFULLY!!");
				getch();
				while(1)
				{
					Y:
					clrscr();
					gotoxy(50,5);
					printf("Welcome !! Select one option");
					gotoxy(50,7);
					printf("----------------------------");
					gotoxy(50,10);
					printf("1.Purchase new products");
					gotoxy(50,13);
					printf("2.View previous purchases(bills)");
					gotoxy(50,16);
					printf("3.Log Out");
					gotoxy(53,20);
					printf("Enter your choice : ");
					scanf("%d",&ch);
					switch(ch)
					{
						case 1: purchaseProduct(name);break;
						case 2: displayPreviousBills(name);break;
						case 3: exit(0);
						default: 
						{
							gotoxy(50,24);
							printf("INVALID CHOICE");
							gotoxy(50,27);
							printf("Click on Enter to re-Enter your choice...");
							if(getch()==13)
								clrscr();
							goto Y;
						}
					}
				}
				break;
            }
			else if(checku==0&&checkp!=0)
			{
				printf("\n\n\n\t\t\tWRONG PASSWORD!!");
				printf("\n\n\t\t\t\t  (Press 'Y' to re-login)");
				if(getch()=='y'||getch()=='Y')
					login();
				break;
			}
		}
		if(feof(fp))
		{
			printf("\n\n\n\t\t\tYou are not a Registered User\n\n \t\t\tPress enter to register yourself");
			if(getch()==13)
				clrscr();
			registration();
		}
		break;
	}
	getch();
}

void OwnerLogin()
{
	gotoxy(50,7);
	printf("WELCOME TO LOGIN ZONE");
	gotoxy(50,8);
    printf("---------------------");
	char pass[4];
	char pin[]="1234";
	int x,y=3,ch;	

	for(x=1;x<5;x++)
	{
		gotoxy(50,12);
		printf("ENTER 4 DIGIT PIN: ");
		for(int p=0;p<4;p++)
		{
			pass[p]=getch();
			printf("*");
		}
		pass[4]='\0';
		getch();
		if (!strcmp(pass,pin))
		{
			clrscr();
			gotoxy(50,12);
			printf("YOU HAVE LOGGED IN SUCCESSFULLY!!");
			gotoxy(50,17);
			printf("Enter any key to cont...");
			x=0;
			getch();
			clrscr();
			while(1)
			{
				Z:
				clrscr();
				gotoxy(50,5);
				printf("CUSTOMER AND PRODUCT DETAILS");
				gotoxy(50,6);
			    printf("----------------------------");
				gotoxy(50,10);
			    printf("1.Manage Products");
				gotoxy(50,13);
				printf("2.View Bills of All Customers");
				gotoxy(50,16);
				printf("3.View specific Bill");
				gotoxy(50,19);
				printf("4.View Total Purchases");
				gotoxy(50,22);
				printf("5.Log Out");
				gotoxy(53,26);
				printf("Enter your choice : ");
				scanf("%d",&ch);
				
				switch(ch)
				{
					case 1: manageProduct();break;
					case 2: allBills();break;
					case 4: totalPurchases();break;
					case 3: specificBill();break;
					case 5: exit(0);
					default: 
					{
					    gotoxy(50,30);
						printf("INVALID CHOICE");
						gotoxy(50,33);
						printf("Click on Enter to re-Enter your choice...");
						if(getch()==13)
							clrscr();
						goto Z;
					}
				}
			} 
			break;
		}
		else
		{
			clrscr();
			gotoxy(50,2);
			printf("WRONG PASSWORD!! %d more chances",y);
			y--;
		}
	}
   getch();
}

int getID()
{
	FILE *fp;
	int value=0;
	
	fp=fopen("id.txt","r");
	
	if(fp==NULL)
	{
		fp=fopen("id.txt","w");
		fprintf(fp,"%d",0);
		fclose(fp);
		fp=fopen("id.txt","r");
	}
	
	fscanf(fp,"%d",&value);
	fclose(fp);
	
	fp=fopen("id.txt","w");
	
	fprintf(fp,"%d",value+1);
	fclose(fp);
	return value+1;
}

void manageProduct()
{
	int ch;
	int back=0;
	while(1)
	{
		A:
		clrscr();
		gotoxy(50,5);
		printf("Welcome to Product Management System");
		gotoxy(50,7);
		printf("------------------------------------");
		gotoxy(50,10);
		printf("1.Add New Product");
		gotoxy(50,13);
		printf("2.Display All Products");
		gotoxy(50,16);
		printf("3.Change Product Quantity");
		gotoxy(50,19);
		printf("4.Back");
		gotoxy(53,23);
		printf("Enter your choice : ");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1: addProduct();break;
			case 2: displayAllProducts();break;
			case 3: appendQuantity();break;
			case 4: back=1;break;
			default: 
			{
				gotoxy(50,24);
				printf("INVALID CHOICE");
				gotoxy(50,27);
				printf("Click on Enter to re-Enter your choice...");
				if(getch()==13)
					clrscr();
				goto A;
			}
		}
		if(back==1)
			break;
		else
			continue;
	}
}

void addProduct()
{
	FILE *fp;
	struct Product t1;
	
	fp=fopen(fname,"ab");
	clrscr();
	
	t1.id=getID();
	gotoxy(40,5);
	printf("--------Enter details of the product to be added--------");
	gotoxy(40,8);
	printf("Enter product name : ");
	scanf("%s",t1.name);
	gotoxy(40,11);
	printf("Enter product price>0 : ");
	PQ:
	scanf("%d",&t1.price);
	if(t1.price<=0)
	{
		printf(" -Enter price>'zero' : ");
		goto PQ;
	}
	
	gotoxy(40,14);
	printf("Enter available quantity>0 : ");
	MN:
	scanf("%d",&t1.qty);
	if(t1.qty<=0)
	{
		printf(" -Enter quantity>'zero' : ");
		goto MN;
	}
	
	fwrite(&t1,sizeof(t1),1,fp);
	fclose(fp);
}

void displayAllProducts()
{
	FILE *fp;
	struct Product t;
	clrscr();
	
	fp=fopen(fname,"rb");
	gotoxy(30,5);
	printf("========================================================");
	gotoxy(30,7);
	printf("\t\t\t List Of All Products");
	gotoxy(30,9);
	printf("========================================================");
	gotoxy(30,12);
	printf("ID");
	gotoxy(40,12);
	printf("Name");
	gotoxy(60,12);
	printf("Quantity");
	gotoxy(75,12);
	printf("Price");
	int a=15;
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
		{
			break;
		}
		gotoxy(30,a);
		printf("%d",t.id);
		gotoxy(40,a);
		printf("%s",t.name);
		gotoxy(60,a);
		printf("%d",t.qty);
		gotoxy(75,a);
		printf("%d",t.price);
		a=a+2;
	}
		gotoxy(30,a+1);
		printf("========================================================\n\n");
		
		fclose(fp);
		getch();
}

void appendQuantity()
{
	FILE *fp1;
	G:
	clrscr();
	int n,x,lastId;
	gotoxy(40,5);
	printf("Enter product ID : ");
	scanf("%d",&n);
	
	fp1=fopen("id.txt","r");
	fscanf(fp1,"%d",&lastId);
	fclose(fp1);
	
	if((lastId<n) || (n<=0))
	{
		gotoxy(35,10);
		printf("-->> There is no product with that ID !!");
		getch();
		goto G;
	}
	
	FILE *fp;
	struct Product t;
	
	fp=fopen(fname,"rb");
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
		{
			break;
		}
		if(t.id==n)
		{
			gotoxy(40,7);
			printf("Name of the product : %s",t.name);
			gotoxy(40,9);
			printf("Product quantity on display : %d",t.qty);
			break;
		}
	}
	fclose(fp);
	gotoxy(40,12);
	printf("Enter available product quantity : ");
	scanf("%d",&x);	
	changeQuantity(n,x);
	gotoxy(35,16);
	printf("-->> QUANTITY OF THE PRODUCT ON DISPLAY HAS BEEN CHANGED !!");
	getch();
}

struct Product changeQuantity(int id,int x)
{
	FILE *fp;
	struct Product t;
	
	fp=fopen(fname,"rb");
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
		{
			break;
		}
		if(t.id==id)
		{
			updateProduct(id,x);
			break;
		}
	}
	fclose(fp);
	return t;
}

void allBills()
{
	FILE *fp;
	struct Bill t;
	char bill[20];
	int value;
	fp=fopen("billNo.txt","r");
	fscanf(fp,"%d",&value);
	fclose(fp);
	
	for(int i=1;i<=value;i++)
	{
		clrscr();
		sprintf(bill,"%s%d","",i);
		strcat(bill,".dat");
		fp=fopen(bill,"rb");
		gotoxy(30,7);
		printf("Bill no : %d",i);
		gotoxy(30,12);
		printf("ID");
		gotoxy(40,12);
		printf("Name");
		gotoxy(60,12);
		printf("Price");
		int a=15;
		while(1)
		{
			fread(&t,sizeof(t),1,fp);
			if(feof(fp))
			{
				break;
			}
			gotoxy(30,9);
			printf("Username : %s",t.user);
			gotoxy(30,a);
			printf("%d\t",t.pid);
			gotoxy(40,a);
			printf("%s\t",t.pname);
			gotoxy(60,a);
			printf("%d\t\n",t.pprice);
			total=total+t.pprice;
			a=a+2;
		}
		gotoxy(35,a+2);
		printf("Total Bill Amount -->> Rs. %d ",total);
		fclose(fp);
		total=0;
		getch();
	}
}

void totalPurchases()
{
	FILE *fp;
	struct Bill t;
	clrscr();
	
	fp=fopen(fAll,"rb");
	gotoxy(30,5);
	printf("========================================================");
	gotoxy(30,7);
	printf("\t\t\t   Bill Details");
	gotoxy(30,9);
	printf("========================================================");
	gotoxy(30,12);
	printf("ID");
	gotoxy(40,12);
	printf("Name");
	gotoxy(60,12);
	printf("Price");
	int a=15;
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
		{
			break;
		}
		gotoxy(30,a);
		printf("%d\t",t.pid);
		gotoxy(40,a);
		printf("%s\t",t.pname);
		gotoxy(60,a);
		printf("%d\t\n",t.pprice);
		total=total+t.pprice;
		a=a+2;
	}
	gotoxy(35,a+2);
	printf("Total Bill Amount -->> Rs. %d ",total);
	
	fclose(fp);
	total=0;
	getch();
}

void purchaseProduct(char user[])
{
	char ch1;
	int id,lastId;
	clrscr();
	while(1)
	{
		displayAllProducts();
		fflush(stdin);
		
		printf("\n\nDo you want to purchase [y/n] : ");
		scanf("%c",&ch1);
		
		if(ch1=='y')
		{
			FILE *fp,*fp1;
			struct Bill t1;
			struct Product t2;
			
			fp=fopen(fbill,"ab");
			
			printf("\n\nEnter the Product ID to Purchase : ");
			scanf("%d",&id);
			
			fp1=fopen("id.txt","r");
	        fscanf(fp1,"%d",&lastId);
			fclose(fp1);
			
			if((lastId<id) || (id<=0))
			{
				printf("\n\n-> There is no product with that ID !");
				getch();
			}
			else
			{
				t2=findProduct(id);
				if(t2.qty!=0)
				{
					t1.pid=t2.id;
				    strcpy(t1.pname,t2.name);
					strcpy(t1.user,user);
				    t1.pprice=t2.price;
				    fwrite(&t1,sizeof(t1),1,fp);
				}
				else
				{
					printf("\n\n-> The product with this ID is OUT OF STOCK !");
					getch();
				}
			}
			fclose(fp);
		}
		fflush(stdin);
		clrscr();
		if(ch1=='n')
		{
			break;
		}
		if(ch1!='y' && ch1!='n')
		{
			printf("\n\n-->>Enter 'y' or 'n' !! \n\n\t\t Press any key to continue..");
			getch();
		}			
	}
	generateBill(user);
}

struct Product findProduct(int id)
{
	FILE *fp;
	struct Product t;
	
	fp=fopen(fname,"rb");
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
		{
			break;
		}
		if(t.id==id)
		{
			if(t.qty!=0)
			{
				updateProduct(id,t.qty-1);
			}
			break;
		}
	}
	fclose(fp);
	return t;
}

void updateProduct(int id,int qty)
{
	FILE *fp,*fp1;
	struct Product t,t1;
	int found=0;
	
	fp=fopen(fname,"rb");
	fp1=fopen("temp.dat","wb");
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
		{
			break;
		}
		if(t.id==id)
		{
			found=1;
			t.qty=qty;
			fwrite(&t,sizeof(t),1,fp1);
		}
		else
		{
			fwrite(&t,sizeof(t),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	
	if(found==0)
	{
		printf("\nProduct Not Found\n\n");
	}
	else
	{
		fp=fopen(fname,"wb");
		fp1=fopen("temp.dat","rb");
		
		while(1)
		{
			fread(&t,sizeof(t),1,fp1);
			
			if(feof(fp1))
			{
				break;
			}
			fwrite(&t,sizeof(t),1,fp);
		}
	}
	fclose(fp);
	fclose(fp1);
}

void generateBill(char user[])
{
	FILE *fp,*fp1,*fp2;
	struct Bill t;
	int id,found=0;
	char ch1;
	int brel=0;
	char billName[20]; 
	
	clrscr();
	
	fp=fopen(fbill,"rb");
	gotoxy(30,5);
	printf("========================================================");
	gotoxy(30,7);
	printf("\t\t\t   Bill Details");
	gotoxy(30,9);
	printf("========================================================");
	gotoxy(30,12);
	printf("ID");
	gotoxy(40,12);
	printf("Name");
	gotoxy(60,12);
	printf("Price");
	int a=15;
	
	while(1)
	{
		fread(&t,sizeof(t),1,fp);
		
		if(feof(fp))
		{
			break;
		}
		gotoxy(30,a);
		printf("%d\t",t.pid);
		gotoxy(40,a);
		printf("%s\t",t.pname);
		gotoxy(60,a);
		printf("%d\t\n",t.pprice);
		total=total+t.pprice;
		a=a+2;
	}
	gotoxy(35,a+2);
	printf("Total Bill Amount -->> Rs. %d ",total);
	
	fclose(fp);
	
	if(total!=0)
	{
		fflush(stdin);
		printf("\n\n\n\nDo you want to generate the Final Bill [y/n] : ");
		scanf("%c",&ch1);
		
		if(ch1=='y')
		{
			brel=billFileNo();
			sprintf(billName,"%s%d","",brel);
			strcat(billName,".dat");
			
			fp=fopen(fbill,"rb");
			fp1=fopen(billName,"wb");
			fp2=fopen(fAll,"ab");
			
			while(1)
			{
				fread(&t,sizeof(t),1,fp);
				
				if(feof(fp))
				{
					break;
				}
				fwrite(&t,sizeof(t),1,fp1);
				fwrite(&t,sizeof(t),1,fp2);
			}
			fclose(fp);
			fclose(fp1);
			fclose(fp2);
			
			fp=fopen(fbill,"wb");
			fclose(fp);
			total=0;
		}
		else
	    {
			total=0;
		    purchaseProduct(user);
	    }
	}
	else
	{
		printf("\n\n\n\n\t\t\t\t You have not purchased any product !! \n");
	}
}

int billFileNo()
{
	FILE *fp;
	int value=0;
	fp=fopen("billNo.txt","r");
	
	if(fp==NULL)
	{
		fp=fopen("billNo.txt","w");
		fprintf(fp,"%d",0);
		fclose(fp);
		fp=fopen("billNo.txt","r");
	}
	
	fscanf(fp,"%d",&value);
	fclose(fp);
	
	fp=fopen("billNo.txt","w");
	fprintf(fp,"%d",value+1);
	fclose(fp);
	return value+1;
}		

void displayPreviousBills(char name[])
{
	FILE *fp;
	struct Bill t;
	char bill[20];
	int value;
	fp=fopen("billNo.txt","r");
	fscanf(fp,"%d",&value);
	fclose(fp);
	
	for(int i=1;i<=value;i++)
	{
		clrscr();
		sprintf(bill,"%s%d","",i);
		strcat(bill,".dat");
		fp=fopen(bill,"rb");
		fread(&t,sizeof(t),1,fp);
		char a[30];
		strcpy(a,t.user);
		fclose(fp);
		fp=fopen(bill,"rb");
		if(!(strcmp(a,name)))
		{
			gotoxy(30,7);
			printf("Bill no : %d",i);
			gotoxy(30,12);
			printf("ID");
			gotoxy(40,12);
			printf("Name");
			gotoxy(60,12);
			printf("Price");
			int a=15;
			while(1)
			{
			    fread(&t,sizeof(t),1,fp);
			    if(feof(fp))
			    {
				    break;
			    }
			    gotoxy(30,9);
			    printf("Username : %s",t.user);
			    gotoxy(30,a);
			    printf("%d\t",t.pid);
			    gotoxy(40,a);
			    printf("%s\t",t.pname);
			    gotoxy(60,a);
			    printf("%d\t\n",t.pprice);
			    total=total+t.pprice;
			    a=a+2;
			}
		    gotoxy(35,a+2);
		    printf("Total Bill Amount -->> Rs. %d ",total);
			fclose(fp);
		    total=0;
		    getch();
		}
	}
}	
	
void specificBill()	
{
	int ch,back=0;
	while(1)
	{
		C:
		clrscr();
		gotoxy(40,10);
		printf("Find Bill Using : 1.Username\t2.Bill Number\t3.Back");
		gotoxy(40,13);
		printf("Enter your choice : ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: userBill();break;
			case 2: numberBill();break;
			case 3: back=1;break;
			default: 
			{
				gotoxy(40,17);
				printf("INVALID CHOICE");
				gotoxy(40,20);
				printf("Click on Enter to re-Enter your choice...");
				if(getch()==13)
					clrscr();
				goto C;
			}
		}
		if(back==1)
			break;
		else
			continue;
	}
}

void userBill()
{
	FILE *fp;
	struct Bill t;
	char bill[20],name[30];
	int value;
	clrscr();
	printf("\n\n\n\t\t->Enter Username of the Customer to view their bills : ");
	scanf("%s",name);
	fp=fopen("billNo.txt","r");
	fscanf(fp,"%d",&value);
	fclose(fp);
	
	for(int i=1;i<=value;i++)
	{
		clrscr();
		sprintf(bill,"%s%d","",i);
		strcat(bill,".dat");
		fp=fopen(bill,"rb");
		fread(&t,sizeof(t),1,fp);
		char a[30];
		strcpy(a,t.user);
		fclose(fp);
		fp=fopen(bill,"rb");
		if(!(strcmp(a,name)))
		{
			gotoxy(30,7);
			printf("Bill no : %d",i);
			gotoxy(30,12);
			printf("ID");
			gotoxy(40,12);
			printf("Name");
			gotoxy(60,12);
			printf("Price");
			int a=15;
			while(1)
			{
			    fread(&t,sizeof(t),1,fp);
			    if(feof(fp))
			    {
				    break;
			    }
			    gotoxy(30,9);
			    printf("Username : %s",t.user);
			    gotoxy(30,a);
			    printf("%d\t",t.pid);
			    gotoxy(40,a);
			    printf("%s\t",t.pname);
			    gotoxy(60,a);
			    printf("%d\t\n",t.pprice);
			    total=total+t.pprice;
			    a=a+2;
			}
		    gotoxy(35,a+2);
		    printf("Total Bill Amount -->> Rs. %d ",total);
			fclose(fp);
		    total=0;
		    getch();
		}
	}
}	

void numberBill()
{
	FILE *fp;
	struct Bill t;
	char bill[20];
	int value,n,i;
	fp=fopen("billNo.txt","r");
	fscanf(fp,"%d",&value);
	fclose(fp);
	clrscr();
	printf("\n\n\n\t\t->Enter Bill Number to view the bill : ");
	scanf("%d",&n);
	
	for(i=1;i<=value;i++)
	{
		sprintf(bill,"%s%d","",i);
		strcat(bill,".dat");
		fp=fopen(bill,"rb");
		if(i==n)
		{
			clrscr();
			gotoxy(30,7);
			printf("Bill no : %d",i);
			gotoxy(30,12);
			printf("ID");
			gotoxy(40,12);
			printf("Name");
			gotoxy(60,12);
			printf("Price");
			int a=15;
			while(1)
			{
			    fread(&t,sizeof(t),1,fp);
			    if(feof(fp))
			    {
				    break;
			    }
			    gotoxy(30,9);
			    printf("Username : %s",t.user);
			    gotoxy(30,a);
			    printf("%d\t",t.pid);
			    gotoxy(40,a);
			    printf("%s\t",t.pname);
			    gotoxy(60,a);
			    printf("%d\t\n",t.pprice);
			    total=total+t.pprice;
			    a=a+2;
			}
		    gotoxy(35,a+2);
		    printf("Total Bill Amount -->> Rs. %d ",total);
			fclose(fp);
		    total=0;
		    getch();
			break;
		}
	}
	if(i>value)
	{
		printf("\n\n\t->Bill no not found");
		getch();
	}
}
		