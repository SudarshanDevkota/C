#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#define USERNAME "admin"
#define PASSWORD "access"
struct student_info{
    char fName[10],lName[10],depart[10],student_id[10];
    long book_borrowed[5];

};
struct book_info{
    char book_id[10],name[10],catagory[10],author[20];
    float price;
};

void print_symbol(char ch,int x){
    printf("\n\t\t\t\t\t\t");
    for(int i=1;i<x;i++)
        printf("%c",ch);
    printf("\n");    
}

void clean(){
    system("clear");
}
int admin_menu(){
    clean();
    int ch;
    print_symbol('*',9);
    printf("\t\t\t\t\t\t*Admin*");
    print_symbol('*',9);
    printf("\n\n\n\n\n");
    print_symbol('-',30);
    printf("\t\t\t\t\t\t| %-25s |\n","1. ADD Student");
    printf("\t\t\t\t\t\t| %-25s |\n","2. UPDATE Student");
    printf("\t\t\t\t\t\t| %-25s |\n","3. VIEW Student");
    printf("\t\t\t\t\t\t| %-25s |\n","4. ADD Book");
    printf("\t\t\t\t\t\t| %-25s |\n","5. UPDATE Book ");
    printf("\t\t\t\t\t\t| %-25s |\n","6. VIEW Book");
    printf("\t\t\t\t\t\t| %-25s |","7. Back to Main Menu");
    print_symbol('-',30);

    admin_ch:
        scanf("%d",&ch);
        if(ch>=1 && ch<=7)
            return ch;
        else{            
            printf("Invalid Input. Enter Again...\n");
            goto admin_ch;
        }

}

void display_book(struct book_info books){
    clean();
    printf("ID: %s",books.book_id);
    printf("Name:%s\n",books.name);
    printf("Catagory:%s\n",books.catagory);
    printf("Author:%s\n",books.author);
    printf("Price:%f\n",books.price);
}
void book_input(){
    clean();
    struct book_info book;
    char choice,id[10];
    int count;
    FILE *fpt,*fp;
    fpt=fopen("bookInfo.txt","a+b");
    do{
    
        printf("Enter the book ID:\n");
        fp=fopen("bookID.txt","a+r");
        
        sc:
            count=0;
            scanf("%s",book.book_id);
        
            while(fscanf(fp,"%s",id)!=EOF){
            if(strcmp(id,book.book_id)==0)
                count++;
            }
            if(count==1){
                printf("Already Exists.Enter another one...\n");          
                goto sc;
            }
            else{
                
                fprintf(fp,"%s\n",book.book_id);
                fclose(fp);
            }
        printf("Enter the book's name:\n");
        scanf("%s",book.name);
        printf("Enter the book catagory:\n");
        scanf("%s",book.catagory);
        printf("enter the author of the book:\n");
        scanf("%s",book.author);
        printf("enter the price of the book:\n");
        scanf("%f",&book.price);
        
        fwrite(&book,sizeof(struct book_info),1,fpt);
        printf("Do you want to enter again?? Y or N\n");
        ch:
            scanf(" %c",&choice);
            if(toupper(choice)!='Y'&&toupper(choice)!='N'){
            printf("invlaid input\n");
            goto ch;
            }
    }while(toupper(choice)=='Y');
    fclose(fpt);
}

int student_menu(){
    clean();
    int ch; 
    print_symbol('*',10);
    printf("\t\t\t\t\t\t*Student*");
    print_symbol('*',10);
    printf("\n\n\n\n");
    print_symbol('-',25);
    printf("\t\t\t\t\t\t| %-20s |\n","1. Search Books");
    printf("\t\t\t\t\t\t| %-20s |\n","2. View Record");
    printf("\t\t\t\t\t\t| %-20s |","3. Back to Main Menu");
    print_symbol('-',25);
    st_menu:
        scanf("%d",&ch);
        if(ch==1||ch==2||ch==3)
            return ch;
        else{
            printf("Invalid input.Enter again");
            goto st_menu;
        }
}

void student_input(){
    struct student_info student;

    char choice,id[10];
    int count=0;
    FILE *fpt,*fp;
    fpt=fopen("studentInfo.txt","a+b");
    do{
    
        printf("Enter your ID:\n");
        fp=fopen("studentID.txt","a+r");
        sc:
            count=0;
            scanf("%s",student.student_id);
        
            while(fscanf(fp,"%s",id)!=EOF){
            if(strcmp(id,student.student_id)==0)
                count++;
            }
            if(count==1){
                printf("Already Exists.Enter another one\n");          
                goto sc;
            }
            else{
                
                fprintf(fp,"%s\n",student.student_id);
                fclose(fp);
            }
        printf("Enter your first name:\n");
        scanf("%s",student.fName);
        printf("Enter your last name:\n");
        scanf("%s",student.lName);
        printf("enter your department:\n");
        scanf("%s",student.depart);
        printf("enter the id of the books entered\n");
        for(int i=0;i<5;i++){
            scanf("%ld",&student.book_borrowed[i]);
        }
        fwrite(&student,sizeof(struct student_info),1,fpt);
        printf("Do you want to enter again?? Y or N\n");
        ch:
            scanf(" %c",&choice);
            if(toupper(choice)!='Y'&&toupper(choice)!='N'){
            printf("invlaid input\n");
            goto ch;
            }
    }while(toupper(choice)=='Y');
    fclose(fpt);
}
void display_student(struct student_info st){
    
    
    printf("ID: %s\n",st.student_id);
    printf("First Name:%s\n",st.fName);
    printf("last Name:%s\n",st.lName);
    printf("Department:%s\n",st.depart);
    printf("reserved books:\n");
    for(int i=0;i<5;i++)
        printf("%ld\n",st.book_borrowed[i]);
}
int main_menu(){
    fflush(stdin);
    clean();
    int ch;
    print_symbol('*',12);
    printf("\t\t\t\t\t\t* MAIN MENU *");
    print_symbol('*',12);
    printf("\n\n\n");
    print_symbol('-',23);
    printf("\t\t\t\t\t\t| %-18s |\n","1. Admin");
    printf("\t\t\t\t\t\t| %-18s |\n","2. Student");
    printf("\t\t\t\t\t\t| %-18s |","3. Qiut");
    print_symbol('-',23);
    main_choice:
    scanf("%d",&ch);   
    if(ch==1||ch==2||ch==3){
        return ch;
    }
    else
        printf("Invalid Input..Re enter \n");    
    goto main_choice;
    


}

void welcome_screen (){
    clean();
    print_symbol('*',40);
    printf("\t\t\t\t\t\t*WELCOME TO THE LIBRARY MANAGEMENT TOOL*");
    print_symbol('*',40);
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\tLoading ");
    for(int i=5;i>0;i--){
        printf(" # ");
        fflush(stdout);
        sleep(1);
     
    }
    printf("\n\n\t\t\t\t\t\tEnter any key to continue...");
    getchar();
    clean();
}


int main(){  
    FILE *fp;
    struct student_info student;
    struct book_info book;
    int main_choice,admin_choice,count,student_choice,recno;
    char AuserName[10],Apassword[10],StdID[10],scannID[10],choice;

    welcome_screen();
    main_choice=main_menu();

 //main menu 
 mn_ch:
    switch (main_choice)
    {
    case 1:
        admin_login:
            clean();
            printf("Enter your Username:\n");
            scanf("%s",AuserName);
            printf("Enter your Password:\n");
            scanf("%s",Apassword);
            if(strcmp(AuserName,USERNAME)==0 && strcmp(Apassword,PASSWORD)==0){
                admin_choice=admin_menu();
                goto ad_ch;
            }   
            else
            {
                goto admin_login;

            }
                


        break;
     case 2:
            printf("Enter your ID:\n");
            fp=fopen("studentID.txt","r");
            sc:
                count=0;
                scanf("%s",StdID);
                rewind(fp);
                while(fscanf(fp,"%s",scannID)!=EOF){
                     if(strcmp(StdID,scannID)==0)
                                count++;
                }
                if(count==1){
                    fclose(fp);
                    student_choice=student_menu();
                    goto st_ch;
                }
                else
                    {
                    printf("Invalid User..\n");
                    goto sc;
                    }
                            
                            
                    
        break;
     case 3:
            exit(0);
    
    
    }

 // Student Menu
 st_ch:
    switch(student_choice){
        case 1:
                clean();
            printf("enter the book id\n");
            fp=fopen("bookID.txt","r");
            books:
                
                count=0;
                
                scanf("%s",StdID);
                rewind(fp);
                while(fscanf(fp,"%s",scannID)!=EOF){
                     if(strcmp(StdID,scannID)==0)
                        count++;
                }
                if(count==0)
                    {
                    printf("invalid id. enter again\n");
                    goto books;
                    } 
                else{
                    fclose(fp);
                    fp=fopen("bookInfo.txt","r+b");
                    while(fread(&book,sizeof(struct book_info),1,fp)==1)
                        if(strcmp(StdID,book.book_id)==0){
                            clean();
                            display_book(book); 
                        }
                    fclose(fp);
                    
                }
                 printf("\n\n\t\t\t\t\tenter any key to go back\n");
            getchar();
            if(getchar())
                student_choice=student_menu(); 
            goto st_ch; 

            
                break;
        case 2:
        clean();
        fp=fopen("studentInfo.txt","r+b");
            while(fread(&student,sizeof(struct student_info),1,fp)==1)
                if(strcmp(StdID,student.student_id)==0){
                    display_student(student); 
                }                        
                fclose(fp);
          printf("\n\n\t\t\t\t\tenter any key to go back\n");
          getchar();
          if(getchar())
            student_choice=student_menu(); 
            goto st_ch;     
             
               
         break;   
    
    
        case 3:
            main_choice=main_menu();
            goto mn_ch;
    }

     
//admin menu
    ad_ch: 
     switch(admin_choice){
        
         case 1:
            clean();
            student_input();
            admin_choice=admin_menu();
            goto ad_ch;
            break;

        case 2:
            printf("Feature coming soon......\n");
            admin_choice=admin_menu();
            goto ad_ch;
           

        case 3:
            
            clean();
            printf("enter the id of the student\n");
            fp=fopen("studentID.txt","r");
            view:
                
                count=0;
                rewind(fp);                
                scanf("%s",StdID);
                rewind(fp);
                while(fscanf(fp,"%s",scannID)!=EOF){
                     if(strcmp(StdID,scannID)==0)
                        count++;
                }
                if(count==0)
                    {
                    printf("invalid id. enter again\n");
                    goto view;
                    } 
                else{
                    fclose(fp);
                    fp=fopen("studentInfo.txt","r+b");
                    while(fread(&student,sizeof(struct student_info),1,fp)==1)
                        if(strcmp(StdID,student.student_id)==0){
                            display_student(student); 
                        }
                    fclose(fp);
                    
                }
                         
            
                printf("\n\n\t\t\t\t\tenter any key to go back\n");
                getchar();
                if(getchar())
                    admin_choice=admin_menu(); 
                goto ad_ch;              
                break;   
    
        case 4:
            clean();
            book_input();
            admin_choice=admin_menu();
            goto ad_ch;
            break;
        case 5:
            printf("Feature coming soon......\n");
            admin_choice=admin_menu();
            goto ad_ch;

        case 6:
            clean();
            printf("enter thebook ID3\n");
            fp=fopen("bookID.txt","r");
            bk_sh:
                
                count=0;
                rewind(fp);
                scanf("%s",StdID);
                rewind(fp);
                while(fscanf(fp,"%s",scannID)!=EOF){
                     if(strcmp(StdID,scannID)==0)
                        count++;
                }
                if(count==0)
                    {
                    printf("invalid id. enter again\n");
                    goto bk_sh;
                    } 
                else{
                    fclose(fp);
                    fp=fopen("bookInfo.txt","r+b");
                    while(fread(&book,sizeof(struct book_info),1,fp)==1)
                        if(strcmp(StdID,book.book_id)==0){
                            display_book(book); 
                        }
                    fclose(fp);
                    
                }
                         
            
                printf("\n\n\t\t\t\t\tenter any key to go back\n");
                getchar();
                if(getchar())
                    admin_choice=admin_menu(); 
                goto ad_ch;              
                break;



        case 7:
            main_choice=main_menu();
            goto mn_ch;

     }
    
            

    
   return 0; 

}