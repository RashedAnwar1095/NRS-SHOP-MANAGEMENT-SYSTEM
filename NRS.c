#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
// Color codes
#define RED "\033[31m"
#define GREEN "\033[32m"
#define GREEN1 "\033[1;32m"//bold green
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define BLUE1 "\033[1;34m"//bold blue
#define MAGENTA "\033[35m"
#define MAGENTA1 "\033[1;35m"//bold magenta
#define CYAN "\033[36m"
#define CYAN1 "\033[1;36m"//bold cyan
#define VIOLET "\033[35m"
#define VIOLET1 "\033[1;35m"//bold violet
#define RESET "\033[0m"

// coordinate count
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

typedef struct
{
    char id[100];
    char name[1000];
    double price;
    int amount;
}PRODUCT;
//find function
char *strstri(char a1[], char a2[]);
//Animate title
void animate(const char *title);
void border();
//Admin login
int admin();
//Main Interface
void mainmenu();
//Product Management
void productmanage();
//-->
void addproduct();
void viewproduct();
void updateproduct();
//-->
void update();
void deleteproduct();
void lowstock();
//Customer Management
void customermanage();
//-->
void viewcustomers();
void viewcuspro();
void srchcustomer();
//Sales Management
void salemanage();
//-->
void makesales();
void viewsales();
void dailyreport();

//MAIN FUNCTION...
int main()
{
    const char *title=
    "           _   _ ____  ____    ____  _   _  ___  ____    \n"
    "          | \\ | |  _ \\/ ___|  / ___|| | | |/ _ \\|  _ \\   \n"
    "          |  \\| | |_) \\___ \\  \\___ \\| |_| | | | | |_) |  \n"
    "          | |\\  |  _ < ___) |  ___) |  _  | |_| |  __/   \n"
    "          |_| \\_|_| \\_\\____/  |____/|_|_|_|\\___/|_|   \n"
    "\n"//for new line
    " __  __    _    _   _    _    ____ _____ __  __ _____ _   _ _____  \n"
    "|  \\/  |  / \\  | \\ | |  / \\  / ___| ____|  \\/  | ____| \\ | |_   _| \n"
    "| |\\/| | / _ \\ |  \\| | / _ \\| |  _|  _| | |\\/| |  _| |  \\| | | |   \n"
    "| |  | |/ ___ \\| |\\  |/ ___ \\ |_| | |___| |  | | |___| |\\  | | |   \n"
    "|_|  |_/_/   \\_\\_| \\_/_/   \\_\\____|_____|_|  |_|_____|_| \\_| |_|   \n";
border();
animate(title);
printf(GREEN1"                  >>Manage Your Shop With Ease<<\n"RESET);
Sleep(2000);
system("cls");

if(admin()){
    mainmenu();
    return 0;
}
else
    printf(RED"Too many failed log in attemps. Existing program...\n"RESET);
return 0;
}
/*******/
void border()
{
    int A = 0;
    printf(CYAN1);
    for (int i = 0; i <= 65; i++)
    {
        gotoxy(0 + i, 3);
        printf("%c", 42);
        fflush(stdout);
        Sleep(A);
    }

    for (int i = 0; i <= 65; i++)
    {
        gotoxy(65 - i, 19);
        printf("%c", 42);
        fflush(stdout);
        Sleep(A);
    }
    printf(RESET);
}

void animate(const char *title)
{
    printf(BLUE1);
    gotoxy(0,5);
    for(int i=0;title[i]!='\0';i++)
    {
        printf("%c", title[i]);
        fflush(stdout);
        Sleep(0);
    }
    printf("\n");
    printf(RESET);
}
//enter admin
int admin()
{
    while(1){
        char username[1000];
        char password[1000];
        char correctuser[1000];
        char correctpass[1000];
        int x;
        system("cls");
        printf(MAGENTA1"***Wellcome to NRS Shop Management System***\n\n"RESET);
        printf(MAGENTA"1. Log in\n\n");
        printf("**Not Registered?**\n\n");
        printf("2. Sign up\n\n");
        printf("Enter your choice: "RESET);
        scanf("%d", &x);
        switch(x)
        {
            case 1:
            for(int i=1;i<=4;i++)
            {
                system("cls");
                gotoxy(0,3);
                int f=0;
                printf(GREEN"Enter Username: "RESET);
                scanf(" %[^\n]", username);
                printf(GREEN"Enter Password: "RESET);
                scanf(" %s", password);
                FILE *fp = fopen("log.txt", "r");
                if(fp!=NULL)
                {
                    while(fscanf(fp, "%[^,],%s\n", correctuser,correctpass)==2){
                        if(strcmp(username,correctuser)==0 && strcmp(password,correctpass)==0)
                            f=1;
                    }
                    fclose(fp);
                    if(f)
                    {
                        printf(GREEN"Log in successful!!!"RESET);
                        return 1;
                    }
                    else
                    {
                        printf(RED"Incorrect Username or Password. Attempts left %d\n"RESET, 4-i);
                        Sleep(1000);
                    }
                }
                else
                {
                    printf(RED"\n\nAn Error Occured While Opening The File!"RESET);
                    Sleep(1000);
                }
            }
            return 0;
            break;
            case 2:
            system("cls");
            gotoxy(0,3);
            printf(GREEN"Enter Username: "RESET);
            scanf(" %[^\n]", username);
            printf(GREEN"Enter Password: "RESET);
            scanf(" %s", password);
            FILE *fc = fopen("log.txt", "a");
            if(fc!=NULL)
            {
                fprintf(fc, "%s,%s\n", username,password);
                printf(GREEN"\n\nSuccessfully Resgistered!"RESET);
                Sleep(1000);
            }
            else
            {
                printf(RED"\n\nAn Error Occured While Opening The File!"RESET);
                Sleep(1000);
            }
            fclose(fc);
            break;
        }
    }
}
//enter mainmenu
void mainmenu()
{
    int n;
    do{
    system("cls");
    gotoxy(0,2);
    printf(BLUE1"-------Main Menu-------\n\n"RESET);
    printf(BLUE"1. Product Management\n");
    printf("2. Customer Management\n");
    printf("3. Sales Management\n");
    printf("4. Exit\n\n"RESET);
    printf(YELLOW"Enter your choice: "RESET);
    scanf("%d",&n);
    if(n==1)
    {
        productmanage();
        break;
    }
    else if(n==2)
    {
        customermanage();
        break;
    }
    else if(n==3)
    {
        salemanage();
        break;
    }
    else if(n==4)
        printf(GREEN1"\n\nThank You for using NRS SHOP MANAGEMENT!!!\n"RESET);
    else
    {
        printf(RED"Invalid choice. Please try again...\n"RESET);
        Sleep(1000);
    }
    }
    while(n!=4);
}
//enter product management
void productmanage()
{
    int n;
    do{
    system("cls");
    gotoxy(0,2);
    printf(BLUE1"-------Product Management-------\n\n"RESET);
    printf(BLUE"1. Add Products\n");
    printf("2. View Products\n");
    printf("3. Update Products\n");
    printf("4. Delete Products\n");
    printf("5. View Low Stock\n");
    printf("6. Back to Main Menu\n\n"RESET);
    printf(YELLOW"Enter your choice: "RESET);
    scanf("%d",&n);
    switch(n)
    {
        case 1:
        addproduct();
        break;
        case 2:
        viewproduct();
        break;
        case 3:
        updateproduct();
        break;
        case 4:
        deleteproduct();
        break;
        case 5:
        lowstock();
        break;
        case 6:
        mainmenu();
        break;
        default:
        printf(RED"Invalid choice. Please try again...\n"RESET);
        Sleep(1000);
        break;
    }
    }
    while(n!=6);
}
//adding products here
void addproduct()
{
    PRODUCT add;
    char x;
    do
    {
        system("cls");
        int f=0;
        gotoxy(0,2);
        printf(VIOLET1"---------Add Product---------\n\n"RESET);
        printf(VIOLET"Enter Product ID: "RESET);
        scanf("%s", add.id);
        printf(VIOLET"Enter Product Name: "RESET);
        scanf(" %[^\n]", add.name);
        printf(VIOLET"Enter Product Price: "RESET);
        scanf("%lf", &add.price);
        printf(VIOLET"Enter Product Amount: "RESET);
        scanf("%d", &add.amount);

        FILE *Product = fopen("product.txt", "a");
        if(Product!=NULL)
        {
            fprintf(Product, "%s,%s,%.2lf,%d\n", add.id, add.name, add.price, add.amount);
            fclose(Product);
            printf(GREEN"\nProduct Added Successfully!!!\n"RESET);
        }
        else
        {
            printf(RED"\n\nAn Error Occured While Opening The File!"RESET);
            Sleep(1000);
            return;
        }
        again:
        printf(VIOLET"\nDo You Want To Add More Products?(Y/N): "RESET);
        scanf(" %c", &x);
        if(x!='Y' && x!='N' && x!='y' && x!='n')
        {
            printf(RED"Invalid Choice!\n"RESET);
            goto again;
        }
    } while (x!='N' && x!='n');
}
//viewing products here
void viewproduct()
{
    system("cls");
    PRODUCT view;
    FILE *Product = fopen("product.txt", "r");
    char buffer[100000]={0};
    if(Product != NULL)
    {
        printf(GREEN1"%-10s%-30s%-10s%-10s\n", "ID", "Name", "Price", "Stock"RESET);
        while(fgets(buffer, sizeof(buffer), Product) != NULL)
        {
            sscanf(buffer, "%[^,],%[^,],%lf,%d", view.id, view.name, &view.price, &view.amount);
            printf("%-10s%-30s%-10.2lf%-10d\n", view.id,view.name,view.price,view.amount);
        }
        fclose(Product);
        printf("\n");
        system("pause");
    }
    else
    {
        printf(RED"Couldn't Open File!\n"RESET);
        Sleep(1000);
        return;
    }
}
//updating products here
void updateproduct()
{
    system("cls");
    PRODUCT update;
    char name[1000];
    int f=0;
    printf(VIOLET1"--------Update Product--------\n\n"RESET);
    printf(MAGENTA"Enter Product ID/Name: "RESET);
    scanf(" %[^\n]", name);
    FILE *Product = fopen("product.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if(Product!=NULL || temp!=NULL)
    {
        while(fscanf(Product, "%[^,],%[^,],%lf,%d\n", update.id, update.name, &update.price, &update.amount)!=EOF)
        {
            char x[1000]={0},y[1000]={0};
            strcpy(x,update.name);//to avoid rewriting in the file.
            strcpy(y,name);
            if(strcmpi(update.id,name)==0 || strstri(x,y))
            {
                f=1;
                system("cls");
                printf(GREEN1"%-10s%-30s%-10s%-10s\n", "ID", "Name", "Price", "Stock"RESET);
                printf("%-10s%-30s%-10.2lf%-10d\n\n", update.id, update.name, update.price, update.amount);
                printf(MAGENTA"Enter New Product Price: "RESET);
                scanf("%lf", &update.price);
                printf(MAGENTA"Enter New Stock: "RESET);
                scanf("%d", &update.amount);
            }
            fprintf(temp, "%s,%s,%.2lf,%d\n", update.id, update.name, update.price, update.amount);
        }
        fclose(Product);
        fclose(temp);
        remove("product.txt");
        rename("temp.txt", "product.txt");
        if(f)
            printf(GREEN"\nProduct Updated Successfully!!!\n"RESET);
        else
            printf(RED"Product Not Found!\n"RESET);
    }
    else
        printf(RED"\n\nAn Error Occured While Opening The File!"RESET);
    Sleep(1000);
}
char *strstri(char a1[], char a2[])
{
    for(int i=0;a1[i]!='\0';i++)
        a1[i] = tolower(a1[i]);
    for(int j=0;a2[j]!='\0';j++)
        a2[j] = tolower(a2[j]);
    return strstr(a1,a2); //finds a2 in a1. a1 is x and a2 is y.
}
//deleting products here
void deleteproduct()
{
    system("cls");
    PRODUCT dlt;
    char name[1000];
    int f=0;
    printf(VIOLET1"--------Delete Product--------\n\n"RESET);
    printf(MAGENTA"Enter Product ID/Name: "RESET);
    scanf(" %[^\n]", name);
    FILE *Product = fopen("product.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    if(Product!=NULL || temp!=NULL)
    {
        while(fscanf(Product, "%[^,],%[^,],%lf,%d\n", dlt.id, dlt.name, &dlt.price, &dlt.amount)!=EOF)
        {
            char x[1000]={0},y[1000]={0};
            strcpy(x,dlt.name);//to avoid rewriting in the file.
            strcpy(y,name);
            if(strcmpi(dlt.id,name)==0 || strstri(x,y))
            {
                f=1;
                continue;
            }
            fprintf(temp, "%s,%s,%.2lf,%d\n", dlt.id, dlt.name, dlt.price, dlt.amount);
        }
        fclose(Product);
        fclose(temp);
        remove("product.txt");
        rename("temp.txt", "product.txt");
        if(f)
            printf(GREEN"\nProduct Deleted Successfully!!!\n"RESET);
        else
            printf(RED"Product Not Found!\n"RESET);
    }
    else
        printf(RED"\n\nAn Error Occured While Opening The File!"RESET);
    Sleep(1000);
}
//viewing lowstock here
void lowstock()
{
    system("cls");
    printf(VIOLET1"--------Low Stock--------\n\n"RESET);
    PRODUCT stock;
    FILE *Product = fopen("product.txt", "r");
    if(Product!=NULL)
    {
        printf(GREEN1"%-10s%-30s%-10s\n", "ID", "Name", "Stock"RESET);
        while(fscanf(Product, "%[^,],%[^,],%lf,%d\n", stock.id, stock.name, &stock.price, &stock.amount)!=EOF)
        {
            if(stock.amount < 7)
            {
                printf("%-10s%-30s%-10d", stock.id,stock.name,stock.amount);
                printf(RED"<---Low Stock\n"RESET);
            }
        }
        fclose(Product);
        printf("\n");
        system("pause");
    }
    else
    {
        printf(RED"\n\nAn Error Occured While Opening The File!"RESET);
        Sleep(1000);
        return;
    }
}
//end product management
// enter customer management
void customermanage()
{
    int n;
    do{
    system("cls");
    gotoxy(0,3);
    printf(BLUE"1. View All Customers\n");
    printf("2. View Customers With Products\n"); // date of purchase,customer info, and purchase info
    printf("3. Search Customer\n");
    printf("4. Back to Main Menu\n\n"RESET);
    printf(YELLOW"Enter your choice: "RESET);
    scanf("%d",&n);
    switch(n)
    {
        case 1:
        viewcustomers();
        break;
        case 2:
        viewcuspro();
        break;
        case 3:
        srchcustomer();
        break;
        case 4:
        mainmenu();
        break;
        default:
        printf(RED"Invalid choice. Please try again...\n"RESET);
        Sleep(1000);
        break;
    }
    }
    while(n!=4);
}

void viewcustomers()
{

}

void viewcuspro()
{

}

void srchcustomer()
{

}
//end customer management

void salemanage()
{
    int n;
    do{
    system("cls");
    gotoxy(0,3);
    printf(BLUE"1. Make Sales\n");
    printf("2. View All Sales\n"); // date of purchase,customer info, and purchase info
    printf("3. Daily Sales Report\n");
    printf("4. Back to Main Menu\n\n"RESET);
    printf(YELLOW"Enter your choice: "RESET);
    scanf("%d",&n);
    switch(n)
    {
        case 1:
        makesales();
        break;
        case 2:
        viewsales();
        break;
        case 3:
        dailyreport();
        break;
        case 4:
        mainmenu();
        break;
        default:
        printf(RED"Invalid choice. Please try again...\n"RESET);
        Sleep(1000);
        break;
    }
    }
    while(n!=4);
}

void makesales()
{

}

void viewsales()
{

}
void dailyreport()
{

}