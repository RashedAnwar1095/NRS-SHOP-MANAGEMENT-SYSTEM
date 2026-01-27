#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
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

// Sales structure
struct Sale
{
    char saleId[10];
    char customerName[50];
    char productName[50];
    int quantity;
    float price;
    char date[20];
};

//Customer structure
typedef struct
{
    char id[20];
    char name[50];
    char mobile[20];
} CUSTOMER;

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
void about();
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
    int A = 10;
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
        Sleep(1);
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
        printf("2. Sign up\n\n"RESET);
        printf(YELLOW"Enter your choice: "RESET);
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
                        printf(GREEN"\nLog in successful!!!"RESET);
                        Sleep(1000);
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
    printf("4. About\n");
    printf("5. Exit\n\n"RESET);
    printf(YELLOW"Enter your choice: "RESET);
    scanf("%d",&n);
    switch(n)
    {
        case 1:
        productmanage();
        break;
        case 2:
        customermanage();
        break;
        case 3:
        salemanage();
        break;
        case 4:
        about();
        break;
        case 5:
        printf(GREEN1"\n\nThank You for using NRS SHOP MANAGEMENT!!!\n"RESET);
        return;
        break;
        default:
        printf(RED"Invalid choice. Please try again...\n"RESET);
        Sleep(1000);
        break;
    }
    }
    while(n!=5);
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
    if(Product!=NULL && temp!=NULL)
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
//The srch funtion...
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
//Customer structure...
typedef struct
{
    char id[20];
    char name[50];
    char mobile[20];
} CUSTOMER;

    system("cls");
    CUSTOMER c;
    FILE *fp = fopen("customer.txt", "r");
    if (fp == NULL)
    {
        printf(RED "Customer file not found!\n" RESET);
        Sleep(1000);
        return;
    }

    printf(GREEN1 "%-15s%-30s%-15s\n", "Customer ID", "Customer Name", "Mobile" RESET);

    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n", c.id, c.name, c.mobile) == 3)
    {
        printf("%-15s%-30s%-15s\n", c.id, c.name, c.mobile);
    }

    fclose(fp);
    printf("\n");
    system("pause");
}

void viewcuspro()
{
    system("cls");
    struct Sale s;
    FILE *fp;

    fp = fopen("sales.txt", "rb");
    if (fp == NULL)
    {
        printf(RED "No sales record found!\n" RESET);
        Sleep(1500);
        return;
    }

    printf(CYAN1 "=== CUSTOMERS WITH PRODUCTS ===\n\n" RESET);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {
        printf(GREEN"Customer : %s\n", s.customerName);
        printf("Product  : %s\n", s.productName);
        printf("Quantity : %d\n", s.quantity);
        printf("Date     : %s\n"RESET, s.date);
        printf(CYAN"-------------------------------\n"RESET);
    }

    fclose(fp);
    system("pause");
}


void srchcustomer()
{
typedef struct
{
    char id[20];
    char name[50];
    char mobile[20];
} CUSTOMER;

    system("cls");
    CUSTOMER c;
    char key[100];
    int found = 0;

    printf(MAGENTA "Enter Customer Name or ID: " RESET);
    scanf(" %[^\n]", key);

    FILE *fp = fopen("customer.txt", "r");
    if (fp == NULL)
    {
        printf(RED "Customer file not found!\n" RESET);
        Sleep(1000);
        return;
    }

    while (fscanf(fp, "%[^,],%[^,],%[^\n]\n", c.id, c.name, c.mobile) == 3)
    {
        if (strcasecmp(c.id, key) == 0 || strcasecmp(c.name, key) == 0)
        {
            found = 1;
            printf(GREEN1 "\nCustomer Found!\n" RESET);
            printf(GREEN "Customer ID   : %s\n", c.id);
            printf("Customer Name : %s\n", c.name);
            printf("Mobile        : %s\n\n" RESET, c.mobile);
            break;
        }
    }

    if (!found)
        printf(RED "\nCustomer not found!\n" RESET);

    fclose(fp);
    system("pause");
}
//end customer management
//enter sales management
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
    struct Sale s;
    CUSTOMER c;
    FILE *fp;
    FILE *fp2;
    time_t t;

    fp = fopen("sales.txt", "a");
    if (fp == NULL)
    {
        printf(RED "File not found!\n" RESET);
        return;
    }

    fp2 = fopen("customer.txt", "a");
    if (fp2 == NULL)
    {
        printf(RED "File not found!\n" RESET);
        return;
    }

    system("cls");
    printf(CYAN1 "=== MAKE SALES ===\n\n" RESET);

    printf("Enter Sale ID: ");
    scanf(" %[^\n]", s.saleId);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", s.customerName);

    printf("Enter Customer Id: ");
    scanf(" %[^\n]", c.id);
    
    printf("Enter Customer Mobile: ");
    scanf(" %[^\n]", c.mobile);

    printf("Enter Product Name: ");
    scanf(" %[^\n]", s.productName);

    printf("Enter Quantity: ");
    scanf("%d", &s.quantity);

    printf("Enter Price: ");
    scanf("%f", &s.price);

    printf(GREEN "Total Price: %.2f\n" RESET ,(s.quantity*s.price));

    time(&t);
    strftime(s.date, sizeof(s.date), "%d/%m/%Y", localtime(&t));

    fwrite(&s, sizeof(s), 1, fp);
    fprintf(fp2, "%s,%s,%s\n", c.id,s.customerName,c.mobile);

    fclose(fp);
    fclose(fp2);

    printf(GREEN "\nSale added successfully!\n" RESET);
    Sleep(1500);
}

void viewsales()
{
    struct Sale s;
    FILE *fp;

    fp = fopen("sales.txt", "r");
    if (fp == NULL)
    {
        printf(RED "No sales record found!\n" RESET);
        Sleep(1500);
        return;
    }

    system("cls");
    printf(CYAN1 "=== ALL SALES RECORD ===\n\n" RESET);

    while (fread(&s, sizeof(s), 1, fp))
    {
        printf(GREEN"Sale ID     : %s\n", s.saleId);
        printf("Customer    : %s\n", s.customerName);
        printf("Product     : %s\n", s.productName);
        printf("Quantity    : %d\n", s.quantity);
        printf("Price       : %.2f\n", s.price);
        printf("Total Price : %.2f\n", (s.quantity*s.price));
        printf("Date        : %s\n"RESET, s.date);
        printf(CYAN"----------------------------\n"RESET);
    }

    fclose(fp);
    system("pause");
}

void dailyreport()
{
    struct Sale s;
    FILE *fp;
    char searchDate[20];
    float total = 0;

    fp = fopen("sales.txt", "r");
    if (fp == NULL)
    {
        printf(RED "No sales record found!\n" RESET);
        Sleep(1500);
        return;
    }

    system("cls");
    printf(CYAN1 "=== DAILY SALES REPORT ===\n\n" RESET);

    printf(YELLOW"Enter Date (dd/mm/yyyy): "RESET);
    scanf("%s", searchDate);

    while (fread(&s, sizeof(s), 1, fp))
    {
        if (strcmp(s.date, searchDate) == 0)
        {
            printf(GREEN"Customer : %s\n", s.customerName);
            printf("Product  : %s\n", s.productName);
            printf("Quantity : %d\n", s.quantity);
            printf("Amount   : %.2f\n\n"RESET, s.price);

            total += (s.quantity*s.price);
        }
    }

    printf(CYAN "Total Sales Amount: %.2f\n" RESET, total);

    fclose(fp);
    system("pause");
}
void about()
{
    system("cls");
    printf(GREEN1"============================================================================="RESET);
    char *print = "\n\nThe NRS Shop Management CRM provides a complete mini solution for small shops.\n"
            "It manages customers, products, sales, invoices, inventory, and reporting efficiently\n" 
            "using C file handling.\n\n";
    printf(CYAN1"%s"RESET, print);
    printf(GREEN1"Developer Team:\n\n"RESET);
    printf(CYAN1"1. Mohammad Rashed Anwar Ovi    C253104\n");
    printf("2. Saroar Alam                  C253031\n");
    printf("3. Ahmad Nayeem Uddin khan      C253026\n\n"RESET);
    printf(GREEN1"=============================================================================\n\n"RESET);
    system("pause");
}