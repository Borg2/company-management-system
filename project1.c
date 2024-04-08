#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int day;
    int month;
    int year;
} Date;

typedef struct
{
    int id;
    char lastname[30];
    char firstname[30];
    float salary;
    Date DOB;
    char address[100];
    char number[15];
    char email[60];
} Employee;

Employee e[100];
int isValidID(char*ID)
{
    int i,n=strlen(ID);
    for(i=0; i<n; i++)
        if(!(ID[i]<='9'&&ID[i]>='0'))
        {
            printf("ID is invalid!\nEnter valid ID:");
            return 0;
        }
    return 1;
}
int isValidnumber(char*nu)
{
    int i,n=strlen(nu);
    for(i=0; i<n; i++)
        if(!(nu[i]<='9'&&nu[i]>='0'))
        {
            return 0;
        }
    return 1;
}
int subchar(char*st,char a,char b)
{
    int i,index1=0,index2=0;
    for(i=0; st[i]!='\0'; i++)
    {
        if(st[i]==a)
            index1=i;
        if(st[i]==b)
            index2=i;
    }
    if((index1<index2)&&(index1>0)&&(index2>0))
        return 1;
    else
        return 0;
}
void load(int*n)
{
    int count=0;
    FILE *f;
    f=fopen("Employees.txt","r");
    while(!feof(f))
    {
        fscanf(f,"%d,",&e[count].id);
        fscanf(f,"%[^,],",e[count].lastname);
        fscanf(f,"%[^,],",e[count].firstname);
        fscanf(f,"%f,",&e[count].salary);
        fscanf(f,"%d-%d-%d,",&e[count].DOB.day,&e[count].DOB.month,&e[count].DOB.year);
        fscanf(f,"%[^,],",e[count].address);
        fscanf(f,"%[^,],",e[count].number);
        fscanf(f,"%s\n",e[count].email);
        count++;
    }
    *n=count;
    fclose(f);
}
void query(int*n)
{
    int i,flag=0;
    char lname[30];//the last name that will be compared to the employees' last name
    printf("Enter the employee's last name: ");
    scanf("%s",lname);
    for(i=0; i<*n; i++)
    {
        if(strcasecmp(e[i].lastname,lname)==0)
        {
            printf("id :%d\n",e[i].id);
            printf("last name:%s\n",e[i].lastname);
            printf("first name :%s\n",e[i].firstname);
            printf("salary:%.2f\n",e[i].salary);
            printf("date of birth:%d-%d-%d\n",e[i].DOB.day,e[i].DOB.month,e[i].DOB.year);
            printf("address:%s\n",e[i].address);
            printf("phone number:%s\n",e[i].number);
            printf("e-mail:%s\n\n",e[i].email);
            flag=1;
        }
    }
    if(!flag)
        printf("Employee not found\n");
}
void add (int*n)
{
    printf("Enter ID: ");
    char ID[10];
    do
    {
        scanf("%s",ID);
    }
    while(!isValidID(ID));
    e[*n].id=atoi(ID);
    printf("Enter last name: ");
    scanf("%s",e[*n].lastname);
    printf("Enter first name: ");
    scanf("%s",e[*n].firstname);
    printf("Enter salary: ");
    scanf("%f",&e[*n].salary);
    while (1)
    {
        printf("enter year of birth :");
        scanf("%d",&e[*n].DOB.year);
        printf("enter month of birth:");
        scanf("%d",&e[*n].DOB.month);
        printf("enter day of birth:");
        scanf("%d",&e[*n].DOB.day);
        if (e[*n].DOB.day<32 && e[*n].DOB.month<13 && e[*n].DOB.year <2023)
            break;
        printf ("date of birth is not valid ! \n");
    }
    printf("Enter address: ");
    getchar();
    gets(e[*n].address);
    while (1)
    {
        printf("enter phone number: ");
        scanf("%s",e[*n].number);
        if ((strlen(e[*n].number) == 11)&&(isValidnumber(e[*n].number)))
        {
            break ;
        }
        printf ("the number you entered is not valid !\n");
    }
    char s1='@',s2='.';
    while (1)
    {
        printf("Enter e-mail:");
        scanf("%s",e[*n].email);
        if (subchar(e[*n].email,s1,s2))
            break ;
        printf ("email is invalid ! \n");
    }

    printf("employee added\n");
    (*n)++;
}
void Delete(int*n)
{
    int i,j;
    char fname[30];
    char lname[30];
    printf("To delete data please \nEnter empolyee's first name: ");
    scanf("%s",fname);
    printf("Employee's last name: ");
    scanf("%s",lname);
    int flag =0;
    for(i=0; i<*n; i++)
    {
        if((strcasecmp(fname,e[i].firstname)==0)&&(strcasecmp(lname,e[i].lastname)==0))
        {
            flag=1;
            for(j=i; j<*n; j++)
                e[j]=e[j+1];
            i--;
            (*n)--;
            printf("employee deleted\n");
        }
    }
    if(!flag)
        printf("\n employee not found \n");
}
void modify (int*n)
{
    int id,m,i,j,numofmod,flag=0;
    printf("Enter ID of empolyee: ");
    char ID[10];
    do
    {
        scanf("%s",ID);
    }
    while(!isValidID(ID));
    id=atoi(ID);
    for(i=0; i<(*n); i++)
    {
        if(e[i].id==id)
        {
            printf("how many number of modify you want: ");
            scanf("%d",&numofmod);

            flag=1;
            printf("Enter 1 : modify in last name  \n");
            printf("enter 2 : modify in first name \n");
            printf("enter 3 : modify in salary  \n");
            printf("enter 4 : modify in date of birth \n");
            printf("enter 5 : modify in address \n");
            printf("enter 6 : modify in phone number \n");
            printf("enter 7 : modify in email \n");
            printf("enter the number of first modification\n");
            for(j=0; j<numofmod; j++)
            {
                if(j)
                    printf("enter the number of next modification: ");
                scanf("%d",&m);
                if(m==1)
                {
                    printf("the new last name :");
                    scanf("%s",e[i].lastname);
                }
                if(m==2)
                {
                    printf("the new first name :");
                    scanf("%s",e[i].firstname);
                }
                if(m==3)
                {
                    printf("the new salary :");
                    scanf("%f",&e[i].salary);
                }
                if(m==4)
                {
                    while (1)
                    {
                        printf("the new year of birth :");
                        scanf("%d",&e[i].DOB.year);
                        printf("the new month of birth:");
                        scanf("%d",&e[i].DOB.month);
                        printf("the new day of birth:");
                        scanf("%d",&e[i].DOB.day);
                        if (e[i].DOB.day<32 && e[i].DOB.month<13 && e[i].DOB.year <2023)
                            break;
                        printf ("date of birth is not valid ! \n");
                    }
                }
                if(m==5)
                {
                    printf("the new address :");
                    scanf("%s",&e[i].address);
                }
                if(m==6)
                {
                    while (1)
                    {
                        printf("the new modification in phone number: ");
                        scanf("%s",e[i].number);
                        if ((strlen(e[i].number) == 11)&&(isValidnumber(e[i].number)))
                            break ;
                        printf ("the number you entered is not valid !\n");

                    }
                }
                if(m==7)
                {
                    char s1='@',s2='.';
                    while (1)
                    {
                        printf("the new email :");
                        scanf("%s",e[i].email);
                        if (subchar(e[i].email,s1,s2))
                            break ;
                        printf ("email is invalid ! \n");
                    }
                }
            }
        }
    }
    if(!flag)
        printf("No employee with this id \n");
}
void sortBYLname(int *n)
{
    int i,j;
    for (j=0; j<*n; j++)
    {
        for(i=j+1; i<*n; i++)
            if(strcasecmp(e[j].lastname,e[i].lastname)>0)
            {
                Employee temp;
                temp=e[i];
                e[i]=e[j];
                e[j]=temp;
            }
    }
}
void sortBySalary(int *n)
{
    int i,j;
    for (j=0; j<*n; j++)
    {
        for(i=j+1; i<*n; i++)
            if(e[j].salary < e[i].salary)
            {
                Employee temp;
                temp=e[i];
                e[i]=e[j];
                e[j]=temp;
            }
    }
}
void sortByDOB(int *n)
{
    int i,j;
    for (j=0; j<*n; j++)
    {
        for(i=j+1; i<*n; i++)
            if(e[j].DOB.year > e[i].DOB.year)
            {
                Employee temp;
                temp=e[i];
                e[i]=e[j];
                e[j]=temp;
            }
            else if (e[j].DOB.year == e[i].DOB.year)
            {
                if(e[j].DOB.month > e[i].DOB.month)
                {
                    Employee temp;
                    temp=e[i];
                    e[i]=e[j];
                    e[j]=temp;
                }
                else if (e[j].DOB.month == e[i].DOB.month)
                {
                    if(e[j].DOB.day > e[i].DOB.day)
                    {
                        Employee temp;
                        temp=e[i];
                        e[i]=e[j];
                        e[j]=temp;
                    }
                }
            }
    }
}

void print(int*n)
{
    int i,x;
    printf("Enter 1: sort by last name\nEnter 2: sort by salary\nEnter 3: sort by date of birth\n");
    scanf("%d",&x);
    switch (x)
    {
    case 1:
        sortBYLname(n);
        break ;
    case 2:
        sortBySalary(n);
        break ;
    case 3:
        sortByDOB(n);
        break ;
    }

    for(i=0; i<*n; i++)
    {
        printf("id :%d\n",e[i].id);
        printf("last name:%s\n",e[i].lastname);
        printf("first name :%s\n",e[i].firstname);
        printf("salary:%.2f\n",e[i].salary);
        printf("date of birth:%d-%d-%d\n",e[i].DOB.day,e[i].DOB.month,e[i].DOB.year);
        printf("address:%s\n",e[i].address);
        printf("phone number:%s\n",e[i].number);
        printf("e-mail:%s\n\n",e[i].email);
    }

}
void save (int *n)
{
    int i;
    FILE *f;
    f=fopen("Employees.txt","w");
    for(i=0; i<*n; i++)
    fprintf(f,"%d,%s,%s,%f,%d-%d-%d,%s,%s,%s\n",e[i].id,e[i].lastname,e[i].firstname,e[i].salary,e[i].DOB.day,e[i].DOB.month,e[i].DOB.year,e[i].address,e[i].number,e[i].email);
    fclose(f);
    printf("data saved\n");
}

int main()
{
    int n,x,z,s=0;
    printf("                                          Company Management System\n\n\n");
    load(&n);
    while(1)
    {
        printf("Menu:\n");
        printf("enter 1 : to search\n");
        printf("enter 2 : to add\n");
        printf("enter 3 : to delete\n");
        printf("enter 4 : to modify\n");
        printf("enter 5 : to print\n");
        printf("enter 6 : to save\n");
        printf("enter 7 : to exit\n");
        scanf("%d",&x);
        if (x>7)
            printf("invalid number please enter a valid number \n");
        switch(x)
        {

        case 1:
            query(&n);
            break;

        case 2:
            add(&n);
            break;

        case 3:
            Delete(&n);
            break;

        case 4:
            modify(&n);
            break;

        case 5:
            print(&n);
            break;

        case 6:
            save(&n);
            s=1;
            break;

        case 7:
            if(!s)
            {
                printf("Are you sure you want to exit without saving!\nEnter 1 to save before exit or 2 to exit without saving: ");
                scanf("%d",&z);
                if (z==1)
                    save(&n);
            }
            exit(0);
            break;
        }
    }

    return 0;
}
