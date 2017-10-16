#include<gtk/gtk.h>
#include<mysql.h>
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-pdf.h>

// SQL setup
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;

//start_window
GtkWidget *start_window;
GtkWidget *t_spin;
GtkWidget *t_progress;
GtkWidget *t_label;
GtkWidget *t_id;
GtkWidget *t_label2;
GtkWidget *t_button1;
GtkWidget *t_label3;
int t_i=0;
static gboolean inc_progress();

//main_window
GtkWidget *main_window;

    //Billing
    GtkWidget *t_combobox1;
    GtkWidget *t_combobox2;
    GtkWidget *t_combobox3;
    GtkWidget *t_label4;
    GtkWidget *t_label5;
    GtkWidget *t_label6;
    GtkWidget *t_label_Insufficient_Balance;
    GtkWidget *t_status_label;
    GtkWidget *t_datetimedisplay;
    GtkWidget *t_checkbox;
    GtkWidget *t_labelc;
    GtkWidget *t_entry1;

    GtkMessageDialog *t_Invalid_entries;
    GtkMessageDialog *t_Invalid_ID;
    GtkMessageDialog *t_Insufficient_Balance;
    int t_sum=0;
    char *t_items[100][50];
    char *t_quantities[100][50];
    char *t_prices_of_items[100][50];
    char *t_invoice_no[100];
    int counter=0;

    //Menu
    GtkWidget *t_menu_combobox1;
    GtkWidget *t_menu_combobox2;
    GtkWidget *t_menu_entry4;
    GtkWidget *t_menu_entry3;
    GtkWidget *t_menu_entry2;
    GtkWidget *t_menu_entry1;
    GtkWidget *t_menu_label1;
    GtkMessageDialog *t_menu_Menu_items_not_filled;

    //Customer Accounts
    GtkEntry* g_new_name;
    GtkEntry* g_new_number;
    GtkEntry* g_new_amount;
    GtkLabel* g_new_id;
    GtkLabel* g_empty_field1;
    GtkLabel* g_empty_field2;
    GtkLabel* g_empty_field3;

    GtkComboBoxText* g_id_update;
    GtkLabel* g_name_selected;
    GtkEntry* g_recharge;
    GtkLabel* g_balance_updated;
    GtkLabel* g_empty_field4;
    GtkLabel* g_empty_field5;

    GtkComboBoxText* g_delete_id;
    GtkLabel* g_delete_name;
    GtkLabel* g_deleted;
    GtkMessageDialog* delete_warning_;
    int delete_flag;

    //Income Manager
    GtkWidget *combobox1daily;
    GtkWidget *combobox2daily;
    GtkWidget *combobox3daily;

    GtkWidget *combobox4monthly;
    GtkWidget *combobox6monthly;
    GtkWidget *combobox9yearly;

    GtkWidget *Totalsalesdaily;
    GtkWidget *MSIdailyquantity;
    GtkWidget *MSInamedaily;

    GtkWidget *Totalsalesyearly;
    GtkWidget *Totalsalesmonthly;
    GtkWidget *MSImonthlyquantity;
    GtkWidget *MSInamemonthly;
    GtkWidget *MSIyearlyquantity;
    GtkWidget *MSInameyearly;

    GtkWidget *messagedialog1;
    GtkWidget *messagedialog2;
    GtkWidget *messagedialog3;
    GtkWidget *messagedialog4;
    GtkWidget *aboutdialog1;


int main(int argc, char* argv[])
{
    //SQL Connection
    char *server = "localhost";
    char *user = "root";
    char *password = "danimithil123";
    char *database = "gtk";

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server,user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    //GTK setup
    GtkBuilder      *builder;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "Canteen_Management_1_28-03-2017.glade", NULL);

    start_window = GTK_WIDGET(gtk_builder_get_object(builder, "start_window"));
    gtk_builder_connect_signals(builder, NULL);

    //loading start_window
    t_spin = GTK_WIDGET(gtk_builder_get_object(builder,"t_spinner1"));
    t_progress = GTK_WIDGET(gtk_builder_get_object(builder,"t_progressbar1"));
    t_label = GTK_WIDGET(gtk_builder_get_object(builder,"t_label1"));
    t_id = GTK_WIDGET(gtk_builder_get_object(builder,"t_entry1"));
    t_label2 = GTK_WIDGET(gtk_builder_get_object(builder,"t_label2"));
    t_button1 = GTK_WIDGET(gtk_builder_get_object(builder,"t_button1"));
    t_label3 = GTK_WIDGET(gtk_builder_get_object(builder,"t_label6"));


    //Processing start_window
    gtk_spinner_start(t_spin);
    gtk_progress_bar_set_show_text(t_progress,TRUE);
    g_timeout_add(100,inc_progress,t_progress);

    g_object_unref(builder);
    gtk_widget_show(start_window);
    gtk_main();

    //Close SQL connection
    mysql_close(conn);
    mysql_free_result(res);

    return 0;
}

float percent=0.0;
gboolean inc_progress()
{
    if(t_i%3==0)
    {
        percent=percent+0.07;
    }
    else if(t_i%3==1)
    {
        percent=percent+0.05;
    }
    else if(t_i%3==2)
    {
        percent=percent+0.03;
    }
    t_i++;
    gtk_progress_bar_set_fraction(t_progress,percent);

    if(percent>=0 && percent<=0.2)
    {
        gtk_label_set_text(t_label,"Loading windows...");
    }
    else if(percent>=0.2 && percent<=0.4)
    {
        gtk_label_set_text(t_label,"Initializing menus...");
    }
    else if(percent>=0.4 && percent<=0.6)
    {
        gtk_label_set_text(t_label,"Processing buttons...");
    }
    else if(percent>=0.6 && percent<=0.8)
    {
        gtk_label_set_text(t_label,"Building application...");
    }
    else if(percent>=0.8 && percent<=1.0)
    {
        gtk_label_set_text(t_label,"Starting application...");
    }
    else if(percent>1.0)
    {
        gtk_spinner_stop(t_spin);
        gtk_widget_set_visible(t_spin,FALSE);
        gtk_widget_set_visible(t_label,FALSE);
        gtk_widget_set_visible(t_progress,FALSE);
        gtk_widget_set_visible(t_label2,TRUE);
        gtk_widget_set_visible(t_id,TRUE);
        gtk_widget_set_visible(t_button1,TRUE);
        gtk_entry_set_visibility(t_id,FALSE);
        return FALSE;
    }
}

G_MODULE_EXPORT void on_t_button1_clicked() //Login
{
    const char *input1 = (const char *)malloc(20);
    input1 = gtk_entry_get_text(t_id);

    if(strcmp(input1,"admin")==0)
    {
        gtk_widget_hide(start_window);
        gtk_widget_set_visible(t_label3,FALSE);
        GtkBuilder *builder;
        //GtkWidget *main_window;

        builder=gtk_builder_new();
        gtk_builder_add_from_file(builder,"Canteen_Management_1_28-03-2017.glade",NULL);

        main_window=GTK_WIDGET(gtk_builder_get_object(builder,"main_window"));
        gtk_builder_connect_signals(builder,NULL);

        //loading main_window
            //Billing
            t_combobox1=GTK_WIDGET(gtk_builder_get_object(builder,"t_comboboxtext1"));
            t_combobox2=GTK_WIDGET(gtk_builder_get_object(builder,"t_comboboxtext2"));
            t_combobox3=GTK_WIDGET(gtk_builder_get_object(builder,"t_comboboxtext3"));

            t_label4=GTK_WIDGET(gtk_builder_get_object(builder,"t_label7"));
            t_label5=GTK_WIDGET(gtk_builder_get_object(builder,"t_label9"));
            t_label6=GTK_WIDGET(gtk_builder_get_object(builder,"t_label11"));
            t_labelc=GTK_WIDGET(gtk_builder_get_object(builder,"t_label13"));
            t_status_label=GTK_WIDGET(gtk_builder_get_object(builder,"status_label"));
            t_label_Insufficient_Balance = GTK_WIDGET(gtk_builder_get_object(builder,"label_Insufficient_Balance"));
            t_datetimedisplay=GTK_WIDGET(gtk_builder_get_object(builder,"t_datetimedisplay"));

            t_entry1=GTK_WIDGET(gtk_builder_get_object(builder,"t_entry2"));
            t_checkbox=GTK_WIDGET(gtk_builder_get_object(builder,"t_checkbutton1"));

            t_Invalid_entries=GTK_WIDGET(gtk_builder_get_object(builder,"Entries_not_selected"));
            t_Invalid_ID=GTK_WIDGET(gtk_builder_get_object(builder,"Id_not_existing"));
            t_Insufficient_Balance=GTK_WIDGET(gtk_builder_get_object(builder,"Insufficient_Balance"));


            //Menu
            t_menu_combobox1=GTK_WIDGET(gtk_builder_get_object(builder,"comboboxtext4"));
            t_menu_combobox2=GTK_WIDGET(gtk_builder_get_object(builder,"comboboxtext5"));
            t_menu_entry1=GTK_WIDGET(gtk_builder_get_object(builder,"entry3"));
            t_menu_entry2=GTK_WIDGET(gtk_builder_get_object(builder,"entry4"));
            t_menu_entry3=GTK_WIDGET(gtk_builder_get_object(builder,"entry5"));
            t_menu_entry4=GTK_WIDGET(gtk_builder_get_object(builder,"entry6"));
            t_menu_label1=GTK_WIDGET(gtk_builder_get_object(builder,"label17"));
            t_menu_Menu_items_not_filled=GTK_WIDGET(gtk_builder_get_object(builder,"Menu_items_not_filled"));


            //Customer Accounts
            g_new_name = GTK_ENTRY(gtk_builder_get_object(builder, "new name entry"));
            g_new_number = GTK_ENTRY(gtk_builder_get_object(builder,"new number entry"));
            g_new_amount = GTK_ENTRY(gtk_builder_get_object(builder,"new amount entry"));
            g_new_id = GTK_LABEL(gtk_builder_get_object(builder,"new id label"));
            g_empty_field1 = GTK_LABEL(gtk_builder_get_object(builder, "emptyfield1"));
            g_empty_field2 = GTK_LABEL(gtk_builder_get_object(builder, "emptyfield2"));
            g_empty_field3 = GTK_LABEL(gtk_builder_get_object(builder, "emptyfield3"));
            g_id_update = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "id combobox"));
            g_name_selected = GTK_LABEL(gtk_builder_get_object(builder, "name label"));
            g_recharge = GTK_ENTRY(gtk_builder_get_object(builder,  "recharge entry"));
            g_balance_updated = GTK_LABEL(gtk_builder_get_object(builder, "balance updated label"));
            g_empty_field4 = GTK_LABEL(gtk_builder_get_object(builder, "emptyfield4"));
            g_empty_field5 = GTK_LABEL(gtk_builder_get_object(builder, "emptyfield5"));
            g_delete_id = GTK_COMBO_BOX_TEXT(gtk_builder_get_object(builder, "delete id combo box"));
            g_delete_name = GTK_LABEL(gtk_builder_get_object(builder, "delete name label"));
            g_deleted = GTK_LABEL(gtk_builder_get_object(builder, "deleted label"));
            delete_warning_ = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "delete warning popup"));

            //Income Manager
            messagedialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "messagedialog1"));
            messagedialog2 = GTK_WIDGET(gtk_builder_get_object(builder, "messagedialog2"));
            messagedialog3 = GTK_WIDGET(gtk_builder_get_object(builder, "messagedialog3"));
            messagedialog4 = GTK_WIDGET(gtk_builder_get_object(builder, "messagedialog4"));
            aboutdialog1 = GTK_WIDGET(gtk_builder_get_object(builder, "aboutdialog1"));


            combobox1daily=GTK_WIDGET(gtk_builder_get_object(builder,"comboboxtext1daily"));
            combobox2daily=GTK_WIDGET(gtk_builder_get_object(builder,"comboboxtext2daily"));
            combobox3daily=GTK_WIDGET(gtk_builder_get_object(builder,"comboboxtext3daily"));


            combobox4monthly=GTK_WIDGET(gtk_builder_get_object(builder,"comboboxtext4monthly"));
            combobox6monthly=GTK_WIDGET(gtk_builder_get_object(builder,"comboboxtext6monthly"));
            combobox9yearly=GTK_WIDGET(gtk_builder_get_object(builder,"comboboxtext9yearly"));


            Totalsalesdaily=GTK_WIDGET(gtk_builder_get_object(builder,"Totalsalesdaily"));
            Totalsalesyearly=GTK_WIDGET(gtk_builder_get_object(builder,"Totalsalesyearly"));
            Totalsalesmonthly=GTK_WIDGET(gtk_builder_get_object(builder,"Totalsalesmonthly"));

            MSImonthlyquantity=GTK_WIDGET(gtk_builder_get_object(builder,"MSImonthlyquantity"));
            MSInamemonthly=GTK_WIDGET(gtk_builder_get_object(builder,"MSInamemonthly"));
            MSIyearlyquantity=GTK_WIDGET(gtk_builder_get_object(builder,"MSIyearlyquantity"));
            MSInameyearly=GTK_WIDGET(gtk_builder_get_object(builder,"MSInameyearly"));

            MSInamedaily=GTK_WIDGET(gtk_builder_get_object(builder,"MSInamedaily"));
            MSIdailyquantity=GTK_WIDGET(gtk_builder_get_object(builder,"MSIdailyquantity"));

        //Processing main_window
            //Billing
            int i;
            for(i=1;i<=5;i++)
            {
                int temp_variable=i;
                char buffer[3];
                snprintf(buffer, 3, "%d", temp_variable);
                gtk_combo_box_text_append_text(t_combobox3,buffer);
            }
            if(mysql_query(conn,"select distinct type from menu_items")!=0)
            {
                printf("Error in query tangerine\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            gtk_combo_box_text_append_text(t_combobox1,row[j]);
                            gtk_combo_box_text_append_text(t_menu_combobox1,row[j]);
                        }
                    }
                }
            }

            //Customer Accounts   (displaying id in comboboxes)
            if (mysql_query(conn, "SELECT id FROM customers")) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                exit(1);
            }
            res = mysql_use_result(conn);
            char statement[100];
            while ((row=mysql_fetch_row(res)) != NULL){
                snprintf(statement, 100, "%s", row[0]);
                gtk_combo_box_text_append_text(g_id_update, statement);
                gtk_combo_box_text_append_text(g_delete_id, statement);
            }
            mysql_free_result(res);

            //Income Manager
            char query3[200];
            snprintf(query3,200,"select distinct orderyear from sample2");
            if(mysql_query(conn,query3)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        if(j==columns-1)
                        {
                            gtk_combo_box_text_append_text(combobox6monthly,row[j]);
                        }
                        else
                        {
                            gtk_combo_box_text_append_text(combobox6monthly,row[j]);
                        }
                    }
                }
            }
            else
            {
                if(mysql_field_count(conn)==0)
                    printf("Non-Select query executed successfully");
                else
                    printf("Error in reading result");
            }

            char query2[200];
            snprintf(query2,200,"select distinct orderyear from sample2");

            if(mysql_query(conn,query2)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        if(j==columns-1)
                           gtk_combo_box_text_append_text(combobox1daily,row[j]);
                        else
                            gtk_combo_box_text_append_text(combobox1daily,row[j]);
                    }
                }
            }
            else
            {
                if(mysql_field_count(conn)==0)
                    printf("Non-Select query executed successfully");
                else
                    printf("Error in reading result");
            }

            char query4[200];
            snprintf(query4,200,"select distinct orderyear from sample2");
            if(mysql_query(conn,query4)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        if(j==columns-1)
                           gtk_combo_box_text_append_text(combobox9yearly,row[j]);
                        else
                            gtk_combo_box_text_append_text(combobox9yearly,row[j]);
                    }
                }
            }
            else
            {
                if(mysql_field_count(conn)==0)
                    printf("Non-Select query executed successfully");
                else
                    printf("Error in reading result");
            }

        g_object_unref(builder);
        gtk_widget_show(main_window);
        gtk_main();
    }
    else
        gtk_widget_set_visible(t_label3,TRUE);
}

//Billing functions
G_MODULE_EXPORT void on_t_comboboxtext1_changed()
{
    gtk_combo_box_text_remove_all(t_combobox2);
    char query1[200]="select item from menu_items where type='";
    strcat(query1,gtk_combo_box_text_get_active_text(t_combobox1));
    strcat(query1,"'");

    if(mysql_query(conn,query1)!=0)
    {
        printf("Error in query\n");
        return 0;
    }
    else
    {
        if(res=mysql_store_result(conn))
        {
            int records=mysql_num_rows(res);
            int columns=mysql_num_fields(res);
            int i,j;

            for(i=0;i<records;i++)
            {
                row=mysql_fetch_row(res);
                for(j=0;j<columns;j++)
                {
                    gtk_combo_box_text_append_text(t_combobox2,row[j]);
                }
            }
        }
    }

    mysql_free_result(res);
}

G_MODULE_EXPORT void on_t_button2_clicked()
{
    int flag=0;

    if((gtk_combo_box_text_get_active_text(t_combobox3)==NULL) || (gtk_combo_box_text_get_active_text(t_combobox1)==NULL || gtk_combo_box_text_get_active_text(t_combobox2)==NULL))
    {
        flag=1;
    }

    if(flag==1)
    {
        gtk_dialog_run(t_Invalid_entries);
    }

    if(flag==0)
    {
        char quantity[20];
        strcpy(quantity,gtk_combo_box_text_get_active_text(t_combobox3));

        char query1[200]="select price from menu_items where item='";
        strcat(query1,gtk_combo_box_text_get_active_text(t_combobox2));
        strcat(query1,"'");
        char price[10];

        if(mysql_query(conn,query1)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                       strcpy(price,row[j]);
                    }
                }
            }
        }

        int i;
        int matching_id=0;
        int exists=0;
        for(i=0;i<=counter;i++)
        {
            if(strcmp(gtk_combo_box_text_get_active_text(t_combobox2),t_items[i])==0)
            {
               exists=1;
               matching_id=i;
               break;
            }
        }
        if(exists==0)
        {
            strcpy(t_items[counter],gtk_combo_box_text_get_active_text(t_combobox2));
            strcpy(t_quantities[counter],quantity);
            strcpy(t_prices_of_items[counter],price);
        }
        else
        {
            int torenew=atoi(t_quantities[matching_id]);
            torenew=torenew+atoi(quantity);

            int temp=torenew;
            char buffer[5];
            snprintf(buffer,5,"%d",temp);

            strcpy(t_quantities[matching_id],buffer);
        }

        char *label1text[10000];
        strcpy(label1text,"");
        char *label2text[10000];
        strcpy(label2text,"");
            for(i=0;i<=counter;i++)
            {
                strcat(label1text,t_items[i]);
                strcat(label1text,"\n");
                strcat(label2text,t_quantities[i]);
                strcat(label2text,"\n");
            }

        gtk_label_set_text(t_label5,label1text);
        gtk_label_set_text(t_label6,label2text);

        if(exists==0)
        {
            counter++;
        }

        int p=atoi(price);
        int q=atoi(quantity);

        t_sum=t_sum+(p*q);

        int temp=t_sum;
        char buffer[10];
        snprintf(buffer,10,"%d",temp);

        gtk_label_set_text(t_label4,buffer);
        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_t_button4_clicked()
{
    if(t_sum!=0)
    {
        if(gtk_toggle_button_get_active(t_checkbox))
        {
            char customer_name[200];
            strcpy(customer_name,gtk_entry_get_text(t_entry1));

            int customer_balance_existing;
            char query2[200];
            snprintf(query2,200,"select Balance from customers where id='%s'",customer_name);

            if(mysql_query(conn,query2)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;
                    if(records==0)
                    {
                        gtk_dialog_run(t_Invalid_ID);
                        goto label ;
                    }
                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            customer_balance_existing=atoi(row[j]);
                        }
                    }
                }
            }
            if(customer_balance_existing>=t_sum)
            {
                int new_balance=customer_balance_existing-t_sum;

                char query3[200];
                snprintf(query3,300,"update customers set Balance='%d' where id='%s'",new_balance,customer_name);

                if(mysql_query(conn,query3)!=0)
                {
                    printf("Error in query\n");
                }
            }
            else
            {
                char error_message_for_customer[500];
                snprintf(error_message_for_customer,500,"Current balance ( in Rs.): %d",customer_balance_existing);

                gtk_label_set_text(t_label_Insufficient_Balance,error_message_for_customer);
                gtk_dialog_run(t_Insufficient_Balance);
                goto label ;
            }
        }

        char query1[200];
        snprintf(query1,200,"insert into sample2(bill) values ('%d')",t_sum);

        if(mysql_query(conn,query1)!=0)
        {
            printf("Error in query\n");
            return 0;
        }

        /*we get a unique id for bill , so now we retrieve that id and store it in "id_of_bill"
        This will help us insert menu_item values directly to that row with id=id_of_bill
        */
        char id_of_bill[10000];
        if(mysql_query(conn,"select id from sample2")!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        if(i==records-1)
                        {
                            strcpy(id_of_bill,row[j]);
                            strcpy(t_invoice_no,row[j]);
                        }
                    }
                }
            }
        }

        int f;
        for(f=0;f<=counter-1;f++)
        {
            //This loop will loop through each data item of items array and store it in sample2 table at appropriate position
            char item_name[200];
            strcpy(item_name,t_items[f]);

            char id_in_menu[200];
            /*Since we named column names in the table sample2 as I5, for item in table menu_item having ID 5,
            we first need to get that id of item from menu_item
            Below query2 executes that and stores id in id_in_menu for item_name=items[f]
            */
            char query2[200];
            snprintf(query2,200,"select id from menu_items where item='%s'",item_name);

            if(mysql_query(conn,query2)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            strcpy(id_in_menu,row[j]);
                        }
                    }
                }
            }

            /*
            Now we finally know the id of the item , thus we add its quantity in the appropriate column name in table sample2
            */

            char query3[200];
            snprintf(query3,200,"update sample2 set I%s='%s' where id='%s' ",id_in_menu,t_quantities[f],id_of_bill);

            if(mysql_query(conn,query3)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            gtk_label_set_text(t_status_label,"Bill added successfully");
        }

        if(FALSE)
        {
            label: ;
        }
    }
    else
    {
        gtk_label_set_text(t_status_label,"Bill amount must be greater than zero!");
    }

    char query5[200];
    snprintf(query5,200,"update sample2 set ordermonth= month(date) where ordermonth is NULL ");

    if(mysql_query(conn,query5)!=0)
    {
        printf("Error1 in query\n");
        return 0;
    }
    else
    {
        if(res=mysql_store_result(conn))
        {
            int records=mysql_num_rows(res);
            int columns=mysql_num_fields(res);
            int i,j;

            for(i=0;i<records;i++)
            {
                row=mysql_fetch_row(res);
                for(j=0;j<columns;j++)
                {

                }
            }
        }
    }

    char query6[200];
    snprintf(query6,200,"update sample2 set orderyear= year(date) where orderyear is NULL ");

    if(mysql_query(conn,query6)!=0)
    {
        printf("Error2 in query\n");
        return 0;
    }
    else
    {
        if(res=mysql_store_result(conn))
        {
            int records=mysql_num_rows(res);
            int columns=mysql_num_fields(res);
            int i,j;

            for(i=0;i<records;i++)
            {
                row=mysql_fetch_row(res);
                for(j=0;j<columns;j++)
                {

                }
            }
        }
    }

    char query7[200];
    snprintf(query7,200,"update sample2 set orderday= day(date) where orderday is NULL ");

    if(mysql_query(conn,query7)!=0)
    {
        printf("Error3 in query\n");
        return 0;
    }
    else
    {
        if(res=mysql_store_result(conn))
        {
            int records=mysql_num_rows(res);
            int columns=mysql_num_fields(res);
            int i,j;

            for(i=0;i<records;i++)
            {
                row=mysql_fetch_row(res);
                for(j=0;j<columns;j++)
                {

                }
            }
        }
    }

    SYSTEMTIME str_t;
    GetLocalTime(&str_t);
    char time [100];
    snprintf(time,100,"Date:%d/%d/%d\n Time: %d:%d:%d\n",str_t.wDay,str_t.wMonth,str_t.wYear,str_t.wHour,str_t.wMinute,str_t.wSecond);
    gtk_label_set_text(t_datetimedisplay,time);

    mysql_free_result(res);
}

G_MODULE_EXPORT void on_t_button3_clicked()
{
    t_sum=0;
    int x;
    for(x=0;x<=counter-1;x++)
    {
        strcpy(t_items[x],"");
        strcpy(t_quantities[x],"");
        strcpy(t_prices_of_items[x],"");
    }
    counter=0;
    strcpy(t_invoice_no,"");

    gtk_label_set_text(t_label4,"...");
    gtk_label_set_text(t_label5,"...");
    gtk_label_set_text(t_label6,"...");
    gtk_label_set_text(t_status_label,"");

    gtk_toggle_button_set_active(t_checkbox,FALSE);
    gtk_widget_set_visible(t_labelc,FALSE);
    gtk_entry_set_text(t_entry1,"");
    gtk_widget_set_visible(t_entry1,FALSE);
}

G_MODULE_EXPORT void on_t_checkbutton1_toggled()
{
    gtk_widget_set_visible(t_labelc,TRUE);
    gtk_widget_set_visible(t_entry1,TRUE);
}

G_MODULE_EXPORT void on_close_Entries_not_selected_clicked()
{
    gtk_widget_hide(t_Invalid_entries);
}

G_MODULE_EXPORT void on_close_Id_not_existing_clicked()
{
    gtk_widget_hide(t_Invalid_ID);
}

G_MODULE_EXPORT void on_close_Insufficient_Balance_clicked()
{
    gtk_widget_hide(t_Insufficient_Balance);
}

G_MODULE_EXPORT void on_t_button5_clicked()
{
    if(t_sum!=0)
    {
        cairo_surface_t *surface;

        cairo_t *cr;

        SYSTEMTIME str_t;
        GetLocalTime(&str_t);

        char bill_pdf_name[500];
        snprintf(bill_pdf_name,500,"Bill_on_(%d-%d-%d_%d-%d-%d).pdf",str_t.wHour,str_t.wMinute,str_t.wSecond,str_t.wDay,str_t.wMonth,str_t.wYear);

        surface = cairo_pdf_surface_create(bill_pdf_name, 504, 648);
        cr = cairo_create(surface);

        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face (cr, "Times New Roman", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);

        cairo_set_font_size (cr, 25.0);

        cairo_move_to(cr, 150.0, 50.0);
        cairo_show_text(cr, "S.P.I.T CANTEEN");

        cairo_move_to(cr,100.0,70.0);
        cairo_set_font_size(cr,10.0);
        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_ITALIC,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_show_text(cr,"Bhavan's Campus, Munshi Nagar, Andheri(West), Mumbai-400 058");


        cairo_move_to(cr,300,100.0);
        cairo_set_font_size(cr,12.0);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
        char bill_id[100];
        snprintf(bill_id,100,"Invoice No.:%s",t_invoice_no);
        cairo_show_text(cr,bill_id);

        double xpos=50.0,ypos=120.0;
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 12.0);

        cairo_move_to(cr,xpos,ypos);
        cairo_show_text(cr,"Item");
        xpos+=150.0;
        cairo_move_to(cr,xpos,ypos);
        cairo_show_text(cr,"Quantity");
        xpos+=70.0;
        cairo_move_to(cr,xpos,ypos);
        cairo_show_text(cr,"Price");
        xpos+=50.0;
        cairo_move_to(cr,xpos,ypos);
        cairo_show_text(cr,"Amount");
        xpos=50.0;
        ypos=140.0;

        cairo_set_font_size (cr, 12.0);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        int x=0;
        for(x=0;x<=counter-1;x++)
        {
            cairo_move_to(cr,xpos,ypos);
            cairo_show_text(cr,t_items[x]);
            xpos+=150.0;
            cairo_move_to(cr,xpos,ypos);
            cairo_show_text(cr,t_quantities[x]);
            xpos+=70.0;
            cairo_move_to(cr,xpos,ypos);
            cairo_show_text(cr,t_prices_of_items[x]);

            int q=atoi(t_quantities[x]);
            int p=atoi(t_prices_of_items[x]);
            int amount=p*q;
            char famount[100];
            snprintf(famount,100,"%d",amount);

            xpos+=50.0;
            cairo_move_to(cr,xpos,ypos);
            cairo_show_text(cr,famount);

            xpos=50.0;
            ypos+=20.0;
        }
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
        cairo_move_to(cr,270.0,ypos);
        cairo_show_text(cr,"Total:");

        char total[100];
        snprintf(total,100,"%d",t_sum);

        cairo_move_to(cr,320.0,ypos);
        cairo_show_text(cr,total);

        ypos+=30;
        cairo_set_font_size(cr,12.0);
        cairo_move_to(cr,50,ypos);
        cairo_select_font_face (cr, "Cambria Math", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);


        char date [100];
        snprintf(date,100,"Date: %d-%d-%d ",str_t.wDay,str_t.wMonth,str_t.wYear);
        cairo_show_text(cr,date);

        cairo_move_to(cr,350,ypos);
        char time [100];
        snprintf(time,100,"Time: %d:%d:%d",str_t.wHour,str_t.wMinute,str_t.wSecond);
        cairo_show_text(cr,time);


        ypos+=30;
        cairo_set_font_size(cr,10.0);
        cairo_select_font_face (cr, "Sans", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_move_to(cr,190.0,ypos);
        cairo_show_text(cr,"Thank You. Do Visit Again");

        cairo_show_page(cr);

        cairo_surface_destroy(surface);
        cairo_destroy(cr);

        gtk_label_set_text(t_status_label,"Bill generated successfully");
    }
    else
    {
        gtk_label_set_text(t_status_label,"Bill amount must be greater than zero!");
    }
}

//Menu functions
G_MODULE_EXPORT void on_button_new1_clicked()
{
    gtk_entry_set_text(t_menu_entry1,"");
    gtk_entry_set_text(t_menu_entry2,"");
    gtk_entry_set_text(t_menu_entry3,"");
    gtk_widget_set_visible(t_menu_label1,FALSE);
}

G_MODULE_EXPORT void on_button6_clicked()
{
    char type[100],item[100],price[100];
    strcpy(type,gtk_entry_get_text(t_menu_entry1));
    strcpy(item,gtk_entry_get_text(t_menu_entry2));
    strcpy(price,gtk_entry_get_text(t_menu_entry3));

    int check=Validation_Of_New_Menu_Item(type,item,price);
    printf("%d\n",check);

    if(check==1)
    {
        char query[400];
        snprintf(query,400,"insert into menu_items(type,item,price) values('%s','%s','%s')",type,item,price);
        printf("%s\n",query);

        if(mysql_query(conn,query)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
            gtk_widget_set_visible(t_menu_label1,TRUE);

        /*Code for editing the sample2 table according to the menu_items*/
        char t_menu_id_of_last_item[500];
        char query2[500];
        snprintf(query2,500,"select id from menu_items order by id desc limit 1");

        if(mysql_query(conn,query2)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        strcpy(t_menu_id_of_last_item,row[j]);
                    }
                }
            }
         }

         char query3[500];
         snprintf(query3,500,"alter table sample2 add I%s int(5) default '0'",t_menu_id_of_last_item);

        if(mysql_query(conn,query3)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
    }
    else
        gtk_dialog_run(t_menu_Menu_items_not_filled);

    mysql_free_result(res);
}

int Validation_Of_New_Menu_Item(char a[],char b[],char c[])
{
    if(strcmp(a,"") && (strcmp(b,"") && strcmp(c,"")) )
    {
        int checker=1;
        int i;
        for(i=0;i<strlen(c);i++)
        {
            int ch=c[i];
            if(ch>=48 && ch<=57)
                continue;
            else
            {
                checker=0;
                break;
            }
        }

        if(checker==0)
            return 0;
        else
            return 1;
    }
    else
        return 0;
}

G_MODULE_EXPORT void on_close_Menu_items_not_filled_clicked()
{
    gtk_widget_hide(t_menu_Menu_items_not_filled);
}

G_MODULE_EXPORT void on_comboboxtext4_changed()
{
    gtk_combo_box_text_remove_all(t_menu_combobox2);
    char query1[200]="select item from menu_items where type='";
    strcat(query1,gtk_combo_box_text_get_active_text(t_menu_combobox1));
    strcat(query1,"'");

    if(mysql_query(conn,query1)!=0)
    {
        printf("Error in query\n");
        return 0;
    }
    else
    {
        if(res=mysql_store_result(conn))
        {
            int records=mysql_num_rows(res);
            int columns=mysql_num_fields(res);
            int i,j;

            for(i=0;i<records;i++)
            {
                row=mysql_fetch_row(res);
                for(j=0;j<columns;j++)
                {
                    gtk_combo_box_text_append_text(t_menu_combobox2,row[j]);
                }
            }
        }
    }

    mysql_free_result(res);
}

G_MODULE_EXPORT void on_button7_clicked()
{
    char new_price[200];
    strcpy(new_price,gtk_entry_get_text(t_menu_entry4));

    if(gtk_combo_box_text_get_active_text(t_menu_combobox2)!=NULL && Validation_of_Edit_menu_item(new_price)==1)
    {
        char query1[500];
        snprintf(query1,500,"update menu_items set price='%s' where item='%s'",new_price,gtk_combo_box_text_get_active_text(t_menu_combobox2));

        if(mysql_query(conn,query1)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
    }
    else
    {
        gtk_dialog_run(t_menu_Menu_items_not_filled);
    }
    mysql_free_result(res);
}

int Validation_of_Edit_menu_item(char c[])
{
    if(strcmp(c,""))
    {
        int checker=1;
        int i;
        for(i=0;i<strlen(c);i++)
        {
            int ch=c[i];
            if(ch>=48 && ch<=57)
                continue;
            else
            {
                checker=0;
                break;
            }
        }

        if(checker==0)
            return 0;
        else
            return 1;
    }
    else
        return 0;
}

//Customer Accounts functions
G_MODULE_EXPORT void add_new_customer()
{
    gtk_label_set_text(g_new_id, " ");
    gtk_label_set_text(g_empty_field1, " ");
    gtk_label_set_text(g_empty_field2, " ");
    gtk_label_set_text(g_empty_field3, " ");

    char *name = gtk_entry_get_text(g_new_name);
    char *number = gtk_entry_get_text(g_new_number);
    char *amount = gtk_entry_get_text(g_new_amount);
    char statement[1024];
    int flag = 0;
    if (!strcmp("", name)){
        gtk_label_set_text(g_empty_field1, "This field can't be empty!");
        flag = 1;
    }
    if (!strcmp("", number)){
        gtk_label_set_text(g_empty_field2, "This field can't be empty!");
        flag = 1;
    }
    if (!strcmp("", amount)){
        gtk_label_set_text(g_empty_field3, "This field can't be empty!");
        flag = 1;
    }

    if (flag == 0)
    {
        //sending query
        snprintf(statement, 1024,"INSERT INTO customers(Customer_Name, Contact_Number, Balance) VALUES('%s','%s','%s')", name, number, amount);
        if (mysql_query(conn, statement))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            gtk_label_set_text(g_new_id, "Error!");
            exit(1);
        }

        /* displaying new customer id */
        if (mysql_query(conn, "SELECT id FROM customers ORDER BY id DESC LIMIT 1"))
        {
            fprintf(stderr, "%s\n", mysql_error(conn));
            gtk_label_set_text(g_new_id, "Error!");
            exit(1);
        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        char statement2[50];
        snprintf(statement2, 50, "Customer's ID: %s", row[0]);
        gtk_label_set_text(g_new_id, statement2);

        snprintf(statement2, 50, "%s", row[0]);
        gtk_combo_box_text_append_text(g_id_update, statement2);   //this will add new customer's id in combobox of update balance
        gtk_combo_box_text_append_text(g_delete_id, statement2);

        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void view_all_customers()
{
    cairo_surface_t *surface;
    cairo_t *cr;

    char statement[100];
    SYSTEMTIME str_t;
	GetLocalTime(&str_t);
    snprintf(statement, 100, "Customers(%d.%d.%d__%d-%d-%d).pdf", str_t.wHour, str_t.wMinute, str_t.wSecond, str_t.wDay, str_t.wMonth, str_t.wYear);
    surface = cairo_pdf_surface_create(statement, 595, 842);
    cr = cairo_create(surface);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_select_font_face (cr, "Times New Roman", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (cr, 25.0);
    cairo_move_to(cr, 200, 30.0);
    cairo_show_text(cr,"S.P.I.T. CANTEEN"); //Header

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_ITALIC,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr, 12.0);
        cairo_move_to(cr, 120, 50);
        cairo_show_text(cr,"Bhavan's Campus, Munshi Nagar, Andheri(West), Mumbai-400 058");
        cairo_set_font_size (cr, 16.0);

    cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
    cairo_move_to(cr, 225, 100);
    cairo_show_text(cr,"CUSTOMERS DATA");

    if (mysql_query(conn, "SELECT * FROM customers")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    double xpos1 = 100.0, xpos2 = 210.0, xpos3 = 320.0, xpos4 = 430.0, ypos = 130;

    cairo_set_font_size (cr, 12.0);
    cairo_move_to(cr, xpos1, ypos);
    cairo_show_text(cr, "Customer Id");
    cairo_move_to(cr, xpos2, ypos);
    cairo_show_text(cr, "Customer Name");
    cairo_move_to(cr, xpos3, ypos);
    cairo_show_text(cr, "Contact Number");
    cairo_move_to(cr, xpos4, ypos);
    cairo_show_text(cr, "Balance");
    ypos+=5;

    while ((row = mysql_fetch_row(res)) != NULL)
    {
        ypos+=20;
        if (ypos > 820.0)
        {
            ypos-= 805.0;
            cairo_surface_create_similar(surface, cairo_surface_get_content(surface), 595, 842);
            cairo_surface_show_page(surface);
            cairo_move_to(cr, xpos1, ypos);
            cairo_show_text(cr, "Customer Id");
            cairo_move_to(cr, xpos2, ypos);
            cairo_show_text(cr, "Customer Name");
            cairo_move_to(cr, xpos3, ypos);
            cairo_show_text(cr, "Contact Number");
            cairo_move_to(cr, xpos4, ypos);
            cairo_show_text(cr, "Balance");
            ypos+=25;

        }
        cairo_move_to(cr, xpos1, ypos);
        snprintf(statement, 100, "%s", row[0]);
        cairo_show_text(cr, statement);
        cairo_move_to(cr, xpos2, ypos);
        snprintf(statement, 100, "%s", row[1]);
        cairo_show_text(cr, statement);
        cairo_move_to(cr, xpos3, ypos);
        snprintf(statement, 100, "%s", row[2]);
        cairo_show_text(cr, statement);
        cairo_move_to(cr, xpos4, ypos);
        snprintf(statement, 100, "%s", row[3]);
        cairo_show_text(cr, statement);
    }
    cairo_show_page(cr);

    cairo_surface_destroy(surface);
    cairo_destroy(cr);
    gtk_dialog_run(GTK_DIALOG(messagedialog3));
    gtk_widget_hide(messagedialog3);
    mysql_free_result(res);

}

G_MODULE_EXPORT void id_selected_in_update_balance()
{
    if (delete_flag == 1)
        return;
    else
    {
        gtk_label_set_text(g_empty_field4, "");
        gtk_label_set_text(g_empty_field5, "");
        gtk_label_set_text(g_balance_updated, "");

        char *id = gtk_combo_box_text_get_active_text(g_id_update);
        char statement[100];
        snprintf(statement, 100, "SELECT Customer_Name FROM customers WHERE id = %s", id);
        if (mysql_query(conn, statement)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        gtk_label_set_text(g_name_selected, row[0]);

        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_recharge_button_clicked()
{
    gtk_label_set_text(g_balance_updated, " ");
    gtk_label_set_text(g_empty_field4, " ");
    gtk_label_set_text(g_empty_field5, " ");

    char *id = gtk_combo_box_text_get_active_text(g_id_update);
    char *recharge = gtk_entry_get_text(g_recharge);

    int flag = 0;
    if (id == NULL){
        gtk_label_set_text(g_empty_field4, "This field can't be empty!");
        flag = 1;
    }
    if (!strcmp("", recharge)){
        gtk_label_set_text(g_empty_field5, "This field can't be empty!");
        flag = 1;
    }

    if (flag == 0)
    {
        //retrieving previous balance
        char statement[50];
        snprintf(statement, 50, "SELECT Balance FROM customers WHERE id = %s", id);
        if (mysql_query(conn, statement)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        char *previous_balance = row[0];

        //updating balance
        char new_balance[50];
        snprintf(new_balance, 50, "%d", (atoi(recharge)+atoi(previous_balance)));

        snprintf(statement, 50, "Updated Balance: %s", new_balance);
        gtk_label_set_text(g_balance_updated, statement);

        snprintf(statement,  50, "UPDATE customers SET Balance = %s WHERE id = %s", new_balance, id);
        mysql_free_result(res);
        if (mysql_query(conn, statement)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void id_selected_in_delete_id()
{
    if (delete_flag == 1)
        return;
    else
    {
        gtk_label_set_text(g_deleted, "");

        char *id = gtk_combo_box_text_get_active_text(g_delete_id);
        char statement[100];
        snprintf(statement, 100, "SELECT Customer_Name FROM customers WHERE id = %s", id);
        if (mysql_query(conn, statement)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }
        res = mysql_use_result(conn);
        row = mysql_fetch_row(res);
        gtk_label_set_text(g_delete_name, row[0]);

        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void delete_warning()
{
    gtk_dialog_run(delete_warning_);
}

G_MODULE_EXPORT void delete_id()
{
    delete_flag = 1;
    gtk_widget_hide(delete_warning_);

    //deleting id
    char* id = gtk_combo_box_text_get_active_text(g_delete_id);
    char statement[100];
    snprintf(statement, 100, "DELETE FROM customers WHERE id = %s", id);
    if (mysql_query(conn, statement)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    snprintf(statement, 100, "Successfully Deleted ID: %s", id);
    gtk_label_set_text(g_deleted, statement);

    //removing id from combo boxes
    gtk_combo_box_text_remove_all(g_id_update);
    gtk_combo_box_text_remove_all(g_delete_id);

    if (mysql_query(conn, "SELECT id FROM customers")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    res = mysql_use_result(conn);
    while ((row=mysql_fetch_row(res)) != NULL){
        snprintf(statement, 100, "%s", row[0]);
        gtk_combo_box_text_append_text(g_id_update, statement);
        gtk_combo_box_text_append_text(g_delete_id, statement);
    }

    gtk_label_set_text(g_delete_name,"--NOT SELECTED--");
    mysql_free_result(res);
    delete_flag = 0;
}

G_MODULE_EXPORT void dont_delete()
{
    gtk_widget_hide(delete_warning_);
}


//Income manager functions
G_MODULE_EXPORT void on_comboboxtext1daily_changed()
{
    //updating combobox
    gtk_combo_box_text_remove_all(combobox2daily);

    char query4[200]="select distinct ordermonth from sample2 where orderyear='";
    strcat(query4,gtk_combo_box_text_get_active_text(combobox1daily));
    strcat(query4,"'");

    if(mysql_query(conn,query4)!=0)
    {
        printf("Error in query\n");
        return 0;
    }
    else
    {
        if(res=mysql_store_result(conn))
        {
            int records=mysql_num_rows(res);
            int columns=mysql_num_fields(res);
            int i,j;

            for(i=0;i<records;i++)
            {
                row=mysql_fetch_row(res);
                for(j=0;j<columns;j++)
                {
                    if(j==columns-1)
                    {
                        gtk_combo_box_text_append_text(combobox2daily,row[j]);
                    }
                    else
                    {
                        gtk_combo_box_text_append_text(combobox2daily,row[j]);
                    }
                }
            }
        }
    }
    mysql_free_result(res);
}

G_MODULE_EXPORT void on_comboboxtext2daily_changed()
{
    //updating combobox
    gtk_combo_box_text_remove_all(combobox3daily);

    char query5[200]="select  distinct orderday from sample2 where ordermonth='";
    strcat(query5,gtk_combo_box_text_get_active_text(combobox2daily));
    strcat(query5,"'");

    if(mysql_query(conn,query5)!=0)
    {
        printf("Error in query\n");
        return 0;
    }
    else
    {
        if(res=mysql_store_result(conn))
        {
            int records=mysql_num_rows(res);
            int columns=mysql_num_fields(res);
            int i,j;

            for(i=0;i<records;i++)
            {
                row=mysql_fetch_row(res);
                for(j=0;j<columns;j++)
                {
                    if(j==columns-1)
                    {
                        gtk_combo_box_text_append_text(combobox3daily,row[j]);
                    }
                    else
                    {
                        gtk_combo_box_text_append_text(combobox3daily,row[j]);
                    }
                }
            }
        }
    }
    mysql_free_result(res);
}

G_MODULE_EXPORT void on_comboboxtext6monthly_changed()
{
    //updating combobox
    gtk_combo_box_text_remove_all(combobox4monthly);

    char query4[200];
    snprintf(query4,200,"select distinct ordermonth from sample2 where orderyear=%s",gtk_combo_box_text_get_active_text(combobox6monthly));
    if(mysql_query(conn,query4)!=0)
    {
        printf("Error in query\n");
        return 0;
    }
    else
    {
        if(res=mysql_store_result(conn))
        {
            int records=mysql_num_rows(res);
            int columns=mysql_num_fields(res);
            int i,j;

            for(i=0;i<records;i++)
            {
                row=mysql_fetch_row(res);
                for(j=0;j<columns;j++)
                {
                    if(j==columns-1)
                    {
                        gtk_combo_box_text_append_text(combobox4monthly,row[j]);
                    }
                    else
                    {
                        gtk_combo_box_text_append_text(combobox4monthly,row[j]);
                    }
                }
            }
        }
    }
    mysql_free_result(res);
}

G_MODULE_EXPORT void on_calculatebuttonyearly_clicked()
{
    //Invalid entry Dialoguebox display
    if(gtk_combo_box_text_get_active_text(combobox9yearly)== NULL)
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog1));
        gtk_widget_hide(messagedialog1);
    }
    else    /*Program Execution*/
    {
        char sum [1000];
        char query6[200];
        snprintf(query6,200,"select sum(bill) from sample2 where orderyear =%s",gtk_combo_box_text_get_active_text(combobox9yearly));

        if(mysql_query(conn,query6)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        strcpy(sum,row[j]);
                    }
                }
            }
        }
        gtk_label_set_text(Totalsalesyearly,sum);
        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_calculatemonthly_clicked()
{
    if((gtk_combo_box_text_get_active_text(combobox6monthly)== NULL)||(gtk_combo_box_text_get_active_text(combobox4monthly)==NULL))
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog1));
        gtk_widget_hide(messagedialog1);
    }
    else
    {
        char summonth [1000];
        char query7[200];
        snprintf(query7,200,"select sum(bill) from sample2 where orderyear =%s AND  ordermonth=%s",
                 gtk_combo_box_text_get_active_text(combobox6monthly),gtk_combo_box_text_get_active_text(combobox4monthly));

        if(mysql_query(conn,query7)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        strcpy(summonth,row[j]);
                    }
                }
            }
        }

        gtk_label_set_text(Totalsalesmonthly,summonth);
        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_calculatebuttondaily_clicked()
{
    if((gtk_combo_box_text_get_active_text(combobox1daily)== NULL)||
       (gtk_combo_box_text_get_active_text(combobox2daily)== NULL)||
       (gtk_combo_box_text_get_active_text(combobox3daily)== NULL))
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog1));
        gtk_widget_hide(messagedialog1);
    }
    else
    {
        char sumday [1000];
        char query8[200];
        snprintf(query8,200,"select sum(bill) from sample2 where orderyear =%s AND  ordermonth =%s AND  orderday=%s",
                 gtk_combo_box_text_get_active_text(combobox1daily),gtk_combo_box_text_get_active_text(combobox2daily),
                 gtk_combo_box_text_get_active_text(combobox3daily));
        if(mysql_query(conn,query8)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        strcpy(sumday,row[j]);
                    }
                }
            }
        }

        gtk_label_set_text(Totalsalesdaily,sumday);
        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_MSIyearly_clicked()
{
    if(gtk_combo_box_text_get_active_text(combobox9yearly)== NULL)
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog1));
        gtk_widget_hide(messagedialog1);
    }
    else
    {
        int n;
        int sum [1000];
        char query8 [200];
        snprintf(query8,200,"select id from menu_items Order By id desc limit 1");

        if(mysql_query(conn,query8)!=0)
        {
            printf("Error1 in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        n=atoi(row[j]);
                    }
                }
            }
        }

        char query7[200];
        char query1[200];
        int number ;
        int id [n];

        for(number=0; number<n ; number++)
        {
            snprintf(query7,200,"select sum(I%d) from sample2 where orderyear =%s",number+1,
                     gtk_combo_box_text_get_active_text(combobox9yearly));
            if (mysql_query(conn,query7)!=0)
            {
                printf("Error2 in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            sum[number]=atoi(row[j]);
                        }
                    }
                }
            }
        }

        int c; int maximum ;
        maximum= sum[0];

        for (c = 0; c < n; c++)
        {
            if (sum[c] > maximum)
            {
                maximum  = sum[c];

                char item [100];
                char query2[200];
                snprintf(query2,200,"select item from menu_items where id='%d'",c+1);

                if(mysql_query(conn,query2)!=0)
                {
                    printf("Error3 in query\n");
                    return 0;
                }
                else
                {
                    if(res=mysql_store_result(conn))
                    {
                        int records=mysql_num_rows(res);
                        int columns=mysql_num_fields(res);
                        int i,j;

                        for(i=0;i<records;i++)
                        {
                            row=mysql_fetch_row(res);
                            for(j=0;j<columns;j++)
                            {
                                strcpy(item,row[j]);
                            }
                        }
                    }
                }
                gtk_label_set_text(MSInameyearly,item);
            }
        }

        char most_sales [10];
        itoa(maximum,most_sales,10); // for decimal value use 10

        gtk_label_set_text(MSIyearlyquantity,most_sales);
        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_MSImonthly_clicked()
{
    if((gtk_combo_box_text_get_active_text(combobox4monthly)== NULL)||(gtk_combo_box_text_get_active_text(combobox6monthly)==NULL))
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog1));
        gtk_widget_hide(messagedialog1);
    }
    else
    {
        int n;
        int sum [1000];
        char query8 [200];
        snprintf(query8,200,"select id from menu_items Order By id desc limit 1");

        if(mysql_query(conn,query8)!=0)
        {
            printf("Error1 in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        n=atoi(row[j]);
                    }
                }
            }
        }

        char query7[200];
        int number ;
        for(number=0; number<n ; number++)
        {
            snprintf(query7,200,"select sum(I%d) from sample2 where orderyear =%s and ordermonth=%s ",number+1,
                     gtk_combo_box_text_get_active_text(combobox6monthly),gtk_combo_box_text_get_active_text(combobox4monthly));
            if(mysql_query(conn,query7)!=0)
            {
                printf("Error2 in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            sum[number]=atoi(row[j]);
                        }
                    }
                }
            }
        }

        int c; int maximum ;
        maximum= sum[0];

        for (c = 0; c < n; c++)
        {
            if (sum[c] > maximum)
            {
                maximum  = sum[c];
                char item [10];
                char query2[200];
                snprintf(query2,200,"select item from menu_items where id='%d'",c+1);

                if(mysql_query(conn,query2)!=0)
                {
                    printf("Error3 in query\n");
                    return 0;
                }
                else
                {
                    if(res=mysql_store_result(conn))
                    {
                        int records=mysql_num_rows(res);
                        int columns=mysql_num_fields(res);
                        int i,j;

                        for(i=0;i<records;i++)
                        {
                            row=mysql_fetch_row(res);
                            for(j=0;j<columns;j++)
                            {
                                strcpy(item,row[j]);
                            }
                        }
                    }
                }

                gtk_label_set_text(MSInamemonthly,item);
            }
        }

        char most_sales [10];
        itoa(maximum,most_sales,10); // for decimal value use 10

        gtk_label_set_text(MSImonthlyquantity,most_sales);

        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_MSIdaily_clicked()
{
    //Error Popup display
    if((gtk_combo_box_text_get_active_text(combobox3daily)== NULL)||(gtk_combo_box_text_get_active_text(combobox2daily)==NULL)||(gtk_combo_box_text_get_active_text(combobox1daily)==NULL))
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog1));
        gtk_widget_hide(messagedialog1);
    }
    else
    {
        //program execution
        int n;
        int sum [1000];
        char query8[200];
        snprintf(query8,200,"select id from menu_items Order By id desc limit 1");
        if(mysql_query(conn,query8)!=0)
        {
            printf("Error1 in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        n=atoi(row[j]);
                    }
                }
            }
        }

        char query7[200];
        int number ;

        for(number=0; number<n ; number++)
        {
            snprintf(query7,200,"select sum(I%d) from sample2 where orderyear =%s and ordermonth=%s and orderday=%s",
                     number+1,gtk_combo_box_text_get_active_text(combobox1daily),gtk_combo_box_text_get_active_text(combobox2daily),
                     gtk_combo_box_text_get_active_text(combobox3daily));

            if(mysql_query(conn,query7)!=0)
            {
                printf("Error2 in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            sum[number]=atoi(row[j]);
                        }
                    }
                }
            }
        }

        //To sort out the maximum value

        int c; int maximum ;
        maximum= sum[0];

        for (c = 0; c < n; c++)
        {
            if (sum[c] > maximum)
            {
                maximum  = sum[c];
                char item [10];
                char query2[200];
                snprintf(query2,200,"select item from menu_items where id='%d'",c+1);

                if(mysql_query(conn,query2)!=0)
                {
                    printf("Error3 in query\n");
                    return 0;
                }
                else
                {
                    if(res=mysql_store_result(conn))
                    {
                        int records=mysql_num_rows(res);
                        int columns=mysql_num_fields(res);
                        int i,j;
                        for(i=0;i<records;i++)
                        {
                            row=mysql_fetch_row(res);
                            for(j=0;j<columns;j++)
                            {
                                strcpy(item,row[j]);
                            }
                        }
                    }
                }
                gtk_label_set_text(MSInamedaily,item);
            }
        }

        char most_sales [10];
        itoa(maximum,most_sales,10); // for decimal value use 10
        gtk_label_set_text(MSIdailyquantity,most_sales);
        mysql_free_result(res);
    }
}

G_MODULE_EXPORT void on_quit_clicked()
{
    gtk_dialog_run(GTK_DIALOG(messagedialog2));
    gtk_widget_hide(GTK_DIALOG(messagedialog2));
}

G_MODULE_EXPORT void on_dialogbox_yes_clicked()
{
    gtk_widget_destroy(main_window);
}

G_MODULE_EXPORT void on_dialogbox_no_clicked()
{
    gtk_widget_hide(messagedialog2);
}

G_MODULE_EXPORT void on_pdfreportdaily_clicked()
{
    //Error dialogue box display
    if((gtk_combo_box_text_get_active_text(combobox3daily)== NULL)||
       (gtk_combo_box_text_get_active_text(combobox2daily)== NULL)||
       (gtk_combo_box_text_get_active_text(combobox1daily)== NULL))
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog4));
        gtk_widget_hide(messagedialog4);
    }
    else
    {
        // program execution
        cairo_surface_t *surface;
        cairo_t *cr;
        cairo_content_t content;

        char Report_pdf_name[500];
        snprintf(Report_pdf_name,500,"Report_of_(%s-%s-%s).pdf",gtk_combo_box_text_get_active_text(combobox3daily),
                 gtk_combo_box_text_get_active_text(combobox2daily), gtk_combo_box_text_get_active_text(combobox1daily));

        surface = cairo_pdf_surface_create(Report_pdf_name, 600, 600); //Giving file name and page size to pdf
        cr = cairo_create(surface);
        cairo_set_source_rgb(cr, 0, 0, 0);

        cairo_select_font_face (cr, "Times New Roman", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 25.0);
        cairo_move_to(cr, 200, 30.0);
        cairo_show_text(cr,"S.P.I.T. CANTEEN"); //Header

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_ITALIC,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr, 12.0);
        cairo_move_to(cr, 120, 50);
        cairo_show_text(cr,"Bhavan's Campus, Munshi Nagar, Andheri(West), Mumbai-400 058");

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr,20.0);
        cairo_move_to(cr, 175.0, 90.0);
        cairo_show_text(cr,"CANTEEN SALES REPORT");

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr, 16.0);
        cairo_move_to(cr, 50.0, 130);

        char sum[100];
        int item_quantities[100];
        int n;
        char query8 [200];
        snprintf(query8,200,"select id from menu_items Order By id desc limit 1");

        if(mysql_query(conn,query8)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
             if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        n=atoi(row[j]);
                    }
                }
            }
        }

        char query7[200];
        char query1[200];
        int number ;

        for(number=0; number<n ; number++)
        {
            snprintf(query7,200,"select sum(I%d) from sample2 where orderyear =%s and ordermonth=%s and orderday=%s",
                     number+1,gtk_combo_box_text_get_active_text(combobox1daily),gtk_combo_box_text_get_active_text(combobox2daily),
                     gtk_combo_box_text_get_active_text(combobox3daily));
            if(mysql_query(conn,query7)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            item_quantities[number]=atoi(row[j]);
                        }
                    }
                }
            }
        }

        char a[1000];
        snprintf(a,1000,"Report of Date : %s/%s/%s",gtk_combo_box_text_get_active_text(combobox3daily),gtk_combo_box_text_get_active_text(combobox2daily),gtk_combo_box_text_get_active_text(combobox1daily));
        cairo_show_text(cr, a);

        int i=0;
        double ypos=150;
        for(i=0;i<n;i++)
        {
            cairo_set_font_size (cr, 10.0);
            char temp[1000];
            char query[1000];
            char item_name[100];

            snprintf(query,1000,"select item  from menu_items where id=%d",i+1);
            if(mysql_query(conn,query)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            strcpy(item_name,row[j]);
                        }
                    }
                }
                else
                {
                    if(mysql_field_count(conn)==0)
                    {
                        printf("Non-Select query executed successfully");
                    }
                    else
                    {
                        printf("Error in reading result");
                    }
                }
            }

            /*Code for adding a page if ypos exceed 550.0*/
            if(ypos>550.0)
            {
                ypos=ypos-520.0;
                cairo_surface_create_similar(surface,content,600,600);
                cairo_surface_show_page(surface);
            }
            cairo_move_to(cr,50.0,ypos);
            snprintf(temp,1000,"%d) %s : %d",i+1,item_name,item_quantities[i]);
            cairo_show_text(cr, temp);
            ypos=ypos+20;
      }

      cairo_show_page(cr);
      cairo_surface_destroy(surface);
      cairo_destroy(cr);

      mysql_free_result(res);
      gtk_dialog_run(GTK_DIALOG(messagedialog3));
      gtk_widget_hide(messagedialog3);

      return 0;
    }
}

G_MODULE_EXPORT void on_pdfreportmonthly_clicked()
{
    if((gtk_combo_box_text_get_active_text(combobox6monthly)== NULL)||(gtk_combo_box_text_get_active_text(combobox4monthly)==NULL))
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog4));
        gtk_widget_hide(messagedialog4);
    }
    else
    {
        cairo_surface_t *surface;
        cairo_t *cr;
        cairo_content_t content;

        char Report_pdf_name[500];
        snprintf(Report_pdf_name,500,"Report_of_(%s-%s).pdf",gtk_combo_box_text_get_active_text(combobox4monthly)
                                                            ,gtk_combo_box_text_get_active_text(combobox6monthly));
        surface = cairo_pdf_surface_create(Report_pdf_name, 600, 600);

        cr = cairo_create(surface);
        cairo_set_source_rgb(cr, 0, 0, 0);

        cairo_select_font_face (cr, "Times New Roman", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 25.0);
        cairo_move_to(cr, 200, 30.0);
        cairo_show_text(cr,"S.P.I.T. CANTEEN");

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_ITALIC,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr, 12.0);
        cairo_move_to(cr, 120, 50);
        cairo_show_text(cr,"Bhavan's Campus, Munshi Nagar, Andheri(West), Mumbai-400 058");

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr,20.0);
        cairo_move_to(cr, 175.0, 90);
        cairo_show_text(cr,"CANTEEN SALES REPORT");

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr, 16.0);
        cairo_move_to(cr, 50.0, 130);

        char sum[100];
        int item_quantities[100];
        int n;
        char query8 [200];
        snprintf(query8,200,"select id from menu_items Order By id desc limit 1");

        if(mysql_query(conn,query8)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        n=atoi(row[j]);
                    }
                }
            }
        }

        char query7[200];
        char query1[200];
        int number ;

        for(number=0; number<n ; number++)
        {
            snprintf(query7,200,"select sum(I%d) from sample2 where orderyear =%s and ordermonth=%s ",
                     number+1,gtk_combo_box_text_get_active_text(combobox6monthly),gtk_combo_box_text_get_active_text(combobox4monthly));

            if(mysql_query(conn,query7)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            item_quantities[number]=atoi(row[j]);
                        }
                    }
                }
            }
        }

        char a[1000];
        snprintf(a,1000,"Report of the Month : %s ,%s",gtk_combo_box_text_get_active_text(combobox4monthly),gtk_combo_box_text_get_active_text(combobox6monthly));
        cairo_show_text(cr, a);

        int i=0;
        double ypos=150.0;
        for(i=0;i<n;i++)
        {
            cairo_set_font_size (cr, 10.0);
            cairo_move_to(cr,50.0,ypos);
            char temp[1000];
            char query[1000];
            char item_name[100];

            snprintf(query,1000,"select  item  from menu_items where id=%d",i+1);
            if(mysql_query(conn,query)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            strcpy(item_name,row[j]);
                        }
                    }
                }
                else
                {
                    if(mysql_field_count(conn)==0)
                    {
                        printf("Non-Select query executed successfully");
                    }
                    else
                    {
                        printf("Error in reading result");
                    }
                }
            }

            /*Code for adding a page if ypos exceed 550.0*/
            if(ypos>550.0)
            {
                ypos=ypos-520.0;
                cairo_surface_create_similar(surface,content,600,600);
                cairo_surface_show_page(surface);
            }
            cairo_move_to(cr,50.0,ypos);
            snprintf(temp,1000,"%d) %s : %d",i+1,item_name,item_quantities[i]);
            cairo_show_text(cr, temp);
            ypos=ypos+20;
        }

        cairo_show_page(cr);
        cairo_surface_destroy(surface);
        cairo_destroy(cr);
        mysql_free_result(res);

        gtk_dialog_run(GTK_DIALOG(messagedialog3));
        gtk_widget_hide(messagedialog3);

        return 0;
    }
}

G_MODULE_EXPORT void on_pdfreportyearly_clicked()
{
    if(gtk_combo_box_text_get_active_text(combobox9yearly)== NULL)
    {
        gtk_dialog_run(GTK_DIALOG(messagedialog4));
        gtk_widget_hide(messagedialog4);
    }
    else
    {
        cairo_surface_t *surface;
        cairo_t *cr;
        cairo_content_t content;

        char Report_pdf_name[500];
        snprintf(Report_pdf_name,500,"Report_of_(%s).pdf",gtk_combo_box_text_get_active_text(combobox9yearly));
        surface = cairo_pdf_surface_create(Report_pdf_name, 600, 600);

        cr = cairo_create(surface);
        cairo_set_source_rgb(cr, 0, 0, 0);

        cairo_select_font_face (cr, "Times New Roman", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_BOLD);
        cairo_set_font_size (cr, 25.0);
        cairo_move_to(cr, 200, 30.0);
        cairo_show_text(cr,"S.P.I.T. CANTEEN");

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_ITALIC,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr, 12.0);
        cairo_move_to(cr, 120, 50);
        cairo_show_text(cr,"Bhavan's Campus, Munshi Nagar, Andheri(West), Mumbai-400 058");

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr,20.0);
        cairo_move_to(cr, 175.0, 90);
        cairo_show_text(cr,"CANTEEN SALES REPORT");

        cairo_select_font_face (cr, "Arial", CAIRO_FONT_SLANT_NORMAL,CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size (cr, 16.0);
        cairo_move_to(cr, 50.0, 130);

        char sum[100];
        int item_quantities[100];
        int n;
        char query8 [200];

        snprintf(query8,200,"select id from menu_items Order By id desc limit 1");

        if(mysql_query(conn,query8)!=0)
        {
            printf("Error in query\n");
            return 0;
        }
        else
        {
            if(res=mysql_store_result(conn))
            {
                int records=mysql_num_rows(res);
                int columns=mysql_num_fields(res);
                int i,j;

                for(i=0;i<records;i++)
                {
                    row=mysql_fetch_row(res);
                    for(j=0;j<columns;j++)
                    {
                        n=atoi(row[j]);
                    }
                }
            }
        }

        char query7[200];
        char query1[200];
        int number ;

        for(number=0; number<n ; number++)
        {
            snprintf(query7,200,"select sum(I%d) from sample2 where orderyear =%s",
                     number+1,gtk_combo_box_text_get_active_text(combobox9yearly));

            if(mysql_query(conn,query7)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            item_quantities[number]=atoi(row[j]);
                        }
                    }
                }
            }
        }

        char a[1000];
        snprintf(a,1000,"Report of the Year: %s",gtk_combo_box_text_get_active_text(combobox9yearly));
        cairo_show_text(cr, a);

        int i=0;
        double ypos=150.0;
        for(i=0;i<n;i++)
        {
            cairo_set_font_size (cr, 10.0);
            cairo_move_to(cr, 50.0,ypos);
            char temp[1000];
            char query[1000];
            char item_name[100];

            snprintf(query,1000,"select  item  from menu_items where ID=%d",i+1);
            if(mysql_query(conn,query)!=0)
            {
                printf("Error in query\n");
                return 0;
            }
            else
            {
                if(res=mysql_store_result(conn))
                {
                    int records=mysql_num_rows(res);
                    int columns=mysql_num_fields(res);
                    int i,j;

                    for(i=0;i<records;i++)
                    {
                        row=mysql_fetch_row(res);
                        for(j=0;j<columns;j++)
                        {
                            strcpy(item_name,row[j]);
                        }
                    }

                }
                else
                {
                    if(mysql_field_count(conn)==0)
                    {
                        printf("Non-Select query executed successfully");
                    }
                    else
                    {
                        printf("Error in reading result");
                    }
                }
            }

            /*Code for adding a page if ypos exceed 500.0*/
            if(ypos>550.0)
            {
                ypos=ypos-520.0;
                cairo_surface_create_similar(surface,content,600,600);
                cairo_surface_show_page(surface);
            }

            cairo_move_to(cr,50.0,ypos);
            snprintf(temp,1000,"%d) %s : %d",i+1,item_name,item_quantities[i]);
            cairo_show_text(cr, temp);
            ypos=ypos+20;
        }

        cairo_show_page(cr);
        cairo_surface_destroy(surface);
        cairo_destroy(cr);
        mysql_free_result(res);

        gtk_dialog_run(GTK_DIALOG(messagedialog3));
        gtk_widget_hide(messagedialog3);
            return 0;
    }
}

G_MODULE_EXPORT void on_about_clicked()
{
    gtk_dialog_run(GTK_DIALOG(aboutdialog1));
    gtk_widget_hide(GTK_DIALOG(aboutdialog1));
}