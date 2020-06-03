#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
using namespace std;


struct contact
{
    int index, k_tel;
    char First_name[21], Last_name[21], Nr_tel[11][21];
    char Fields[6][51];
} contactList[1001];

int k, i, j;
bool sorted_alpha = false, sorted_tel = false;
char FieldsList[6][21] = {"E-mail", "Company", "Birthday", "Address", "Pseudonym"};
int nr_f = 5;

void Load()
{
    ifstream fin("contactList.txt");
    fin>>k;
    fin.get();
    for(i=1; i<=k ; i++)
    {
        fin.getline(contactList[i].First_name, 21);
        fin.getline(contactList[i].Last_name, 21);
        fin>>contactList[i].k_tel;
        fin.get();
        for(j = 1; j <= contactList[i].k_tel; j++)
            fin.getline(contactList[i].Nr_tel[j], 21);
        for(j = 0; j < nr_f; j++)
            fin.getline(contactList[i].Fields[j], 51);
    }

}

void Save()
{
    ofstream fout("contactList.txt");
    fout<<k<<endl;
    for(i=1; i<=k; i++)
    {
        fout<<contactList[i].First_name<<endl;
        fout<<contactList[i].Last_name<<endl;
        fout<<contactList[i].k_tel<<endl;
        for(j = 1; j <= contactList[i].k_tel; j++)
            fout<<contactList[i].Nr_tel[j]<<endl;
        for(j = 0; j < nr_f; j++)
            fout<<contactList[i].Fields[j]<<endl;

    }
}

void Alphabetical_sort()
{
    sorted_alpha = true;
    sorted_tel = false;
    for(i=1; i<k; i++)
        for(j=i+1; j<=k; j++)
        {
            if(strcmp(contactList[i].First_name, contactList[j].First_name)>0)
                swap(contactList[i], contactList[j]);
            else if(strcmp(contactList[i].First_name, contactList[j].First_name)==0)
            {
                if(strcmp(contactList[i].Last_name, contactList[j].Last_name)>0)
                    swap(contactList[i], contactList[j]);
                else if(strcmp(contactList[i].Last_name, contactList[j].Last_name)==0)
                {
                    int swaped = false;
                    for(int l=1; l<=min(contactList[i].k_tel, contactList[j].k_tel) && !swaped; l++)
                        if(strcmp(contactList[i].Nr_tel[l], contactList[j].Nr_tel[l]) > 0)
                            swap(contactList[i], contactList[j]), swaped = true;
                    if(!swaped && contactList[i].k_tel > contactList[j].k_tel)
                        swap(contactList[i], contactList[j]);

                }
            }
        }
}

void Telephone_sort()
{
    sorted_tel=true;
    sorted_alpha=false;
    for(i = 1; i < k; i++)
        for(j = i+1; j <= k; j++)
        {
            bool swaped = false;
            for(int l = 1; l <= min(contactList[i].k_tel, contactList[j].k_tel) && !swaped; l++)
                if(strcmp(contactList[i].Nr_tel[l], contactList[j].Nr_tel[l])>0)
                    swap(contactList[i], contactList[j]), swaped = true;
            if(!swaped && contactList[i].k_tel > contactList[j].k_tel)
                swap(contactList[i], contactList[j]);
        }
}

void Remove_contact(int n)
{
    for(i = n; i < k; i++)
        contactList[i] = contactList[i+1];
    k--;
    cout<<"#-Contact removed-#"<<endl;
}

void Show_contact(int n)
{
    cout<<"Name: ";
    if(strcmp(contactList[n].Last_name, "N/A") && strcmp(contactList[n].First_name, "N/A"))
        cout<<contactList[n].First_name<<' '<<contactList[n].Last_name;
    else if(!strcmp(contactList[n].Last_name, "N/A") && !strcmp(contactList[n].First_name, "N/A"))
        cout<<"N/A";
    else if(!strcmp(contactList[n].Last_name, "N/A"))
        cout<<contactList[n].First_name;
    else
        cout<<contactList[n].Last_name;
    cout<<endl;
    cout<<"Telephone number";
    if(contactList[n].k_tel > 1)
        cout<<"s:"<<endl;
    else
        cout<<':';
    for(j = 1; j <= contactList[n].k_tel; j++)
        cout<<"|> "<<contactList[n].Nr_tel[j]<<endl;
    for(j = 0; j < nr_f; j++) cout<<FieldsList[j]<<": "<<contactList[n].Fields[j]<<endl;
    cout<<endl;
}

int Edit_contact(int n,  int biased)
{
    if(biased != 2)
        cout<<"#-Edit contact-#"<<endl<<"--To skip a field, press the \'*\' button--"<<endl;
    cout<<"--To leave a field empty, press the \'^\' button--"<<endl
        <<"--To cancel editing at any time, press the \'&\' button--"<<endl;
    contact aux;
    char op[21], *p;
    bool acces;
    aux = contactList[n];
    aux.index = n;
    if(biased != 2)
        cout<<endl, Show_contact(n);
    cout<<"First Name:\n", cin.getline(aux.First_name ,21);
    if(strcmp(aux.First_name, "&")==0)
    {
        cout<<"#-Canceled-#"<<endl;
        return 0;
    }
    else if(strcmp(aux.First_name, "*")==0)
        strcpy(aux.First_name, contactList[n].First_name);
    else if(strcmp(aux.First_name, "^")==0 || aux.First_name[0] == NULL)
        strcpy(aux.First_name, "N/A");
    cout<<"Last Name:\n", cin.getline(aux.Last_name, 21);
    if(strcmp(aux.Last_name, "&")==0)
    {
        cout<<"#-Canceled-#"<<endl;
        return 0;
    }
    else if(strcmp(aux.Last_name, "*")==0)
        strcpy(aux.Last_name, contactList[n].Last_name);
    else if(strcmp(aux.Last_name, "^")==0 || aux.Last_name[0] == NULL)
        strcpy(aux.Last_name, "N/A");
    aux.Last_name[0] = toupper(aux.Last_name[0]);
    aux.First_name[0] = toupper(aux.First_name[0]);
    p = strchr(aux.Last_name, ' ');
    while(p!=NULL)
    {
        if(p - aux.Last_name > 0)
        {
            p[1] = toupper(p[1]);
            if(p[1] == ' ')
                strcpy(p, p + 1), p--;
        }
        p = strchr(p+1, ' ');
    }
    p = strchr(aux.First_name, ' ');
    while(p!=NULL)
    {
        if(p - aux.First_name > 0)
        {
            p[1] = toupper(p[1]);
            if(p[1] == ' ')
                strcpy(p, p + 1), p--;
        }
        p = strchr(p+1, ' ');
    }
    for(i = strlen(aux.First_name)-1 ; i>=0 && aux.First_name[i]==' '; i--);
    aux.First_name[i+1] = '\0';
    for(i = strlen(aux.Last_name)-1; i>=0 && aux.First_name[i]==' '; i--);
    aux.Last_name[i+1] = '\0';
    for(i = 0; aux.Last_name[i] && aux.Last_name[i]==' '; i++);
    strcpy(aux.Last_name, aux.Last_name + i);
    for(i = 0; aux.First_name[i] && aux.First_name[i]==' '; i++);
    strcpy(aux.First_name, aux.First_name + i);

    if(biased == 2)
    {
        aux.k_tel = 0;
        do
        {
            aux.k_tel++;
            cout<<"Telephone Number "<<aux.k_tel<<":\n", cin.getline(aux.Nr_tel[aux.k_tel], 21);
            while(((strcmp(aux.Nr_tel[aux.k_tel], "^")==0 || aux.Nr_tel[aux.k_tel][0] == NULL) && aux.k_tel == 1)
                    || (strspn(aux.Nr_tel[aux.k_tel], "0123456789+*#^&")!=strlen(aux.Nr_tel[aux.k_tel])
                        || (strspn(aux.Nr_tel[aux.k_tel], "+*#&^")==strlen(aux.Nr_tel[aux.k_tel]) && strcmp(aux.Nr_tel[aux.k_tel], "^") && strcmp(aux.Nr_tel[aux.k_tel], "&"))))
            {
                if(strcmp(aux.Nr_tel[aux.k_tel], "^")==0 && aux.k_tel == 1)
                    cout<<"x-Can't leave field empty-x";
                else
                    cout<<"x-Please enter a valid number-x";
                cout<<endl<<"Telephone Number "<<aux.k_tel<<":\n", aux.Nr_tel[aux.k_tel][0] = '\0', cin.getline(aux.Nr_tel[aux.k_tel], 21);
            }
            if(strcmp(aux.Nr_tel[aux.k_tel], "&")==0)
            {
                cout<<"#-Canceled-#"<<endl;
                aux.k_tel--;
                return 0;
            }
            else if((strcmp(aux.Nr_tel[aux.k_tel], "^")==0 || aux.Nr_tel[aux.k_tel][0] == NULL) && aux.k_tel != 1)
                aux.k_tel--;
            cout<<"Do you wish to:\n1.Add another telephone number\n2.Continue\n3.Cancel editing?\n";
            do
            {
                cin.getline(op, 21);
                for(i = 0; op[i] && op[i]==' '; i++);
                strcpy(op, op + i);
                for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
                op[i+1]='\0';
                if(atoi(op)<1 || atoi(op) > 3 || strspn(op, "0123456789")!=strlen(op))
                    cout<<"x-Invalid option-x"<<endl
                        <<"Try again: ";
            }
            while(atoi(op)<1 || atoi(op) > 3 || strspn(op, "0123456789")!=strlen(op));
            if(atoi(op) == 3)
            {
                cout<<"#-Canceled-#"<<endl;
                return 0;
            }
        }
        while(atoi(op) == 1);
    }
    else
    {
        aux.k_tel = 0;
        int lg = contactList[n].k_tel;
        for(i = 1; i <= contactList[n].k_tel ; i++)
        {
            aux.k_tel++;
            cout<<"New Telephone Number "<<i<<":\n", cin.getline(aux.Nr_tel[aux.k_tel], 21);
            while(strspn(aux.Nr_tel[aux.k_tel], "0123456789*^#&+")!=strlen(aux.Nr_tel[aux.k_tel])
                    || (strspn(aux.Nr_tel[aux.k_tel], "*^&+#")==strlen(aux.Nr_tel[aux.k_tel]) && strcmp(aux.Nr_tel[aux.k_tel], "*") && strcmp(aux.Nr_tel[aux.k_tel], "&") && strcmp(aux.Nr_tel[aux.k_tel], "^"))
                    || ((strcmp(aux.Nr_tel[aux.k_tel], "^")==0 || aux.Nr_tel[aux.k_tel][0] == NULL) && lg == 1))
            {
                if(strcmp(aux.Nr_tel[aux.k_tel], "^")==0 && lg == 1)
                    cout<<"x-Can't leave field empty-x"<<endl;
                else
                    cout<<"x-Please enter a valid number-x"<<endl;
                cout<<"New Telephone Number "<<i<<":\n", cin.getline(aux.Nr_tel[aux.k_tel], 21);
            }
            if(strcmp(aux.Nr_tel[aux.k_tel], "^")==0 || aux.Nr_tel[aux.k_tel]==NULL)
                aux.k_tel--, lg--;
            else if(strcmp(aux.Nr_tel[aux.k_tel], "&")==0)
            {
                cout<<"x-Canceled-x"<<endl;
                return 0;
            }
            else if(strcmp(aux.Nr_tel[aux.k_tel], "*")==0)
                strcpy(aux.Nr_tel[aux.k_tel], contactList[n].Nr_tel[i]);
        }
        cout<<"Do you wish to:\n1.Add another telephone number\n2.Continue\n3.Cancel editing?\n";
        do
        {
            cin.getline(op, 21);
            for(i = 0; op[i] && op[i]==' '; i++);
            strcpy(op, op + i);
            for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
            op[i+1]='\0';
            if(atoi(op)<1 || atoi(op) > 3 || strspn(op, "0123456789")!=strlen(op))
                cout<<"x-Invalid option-x"<<endl
                    <<"Try again: ";
        }
        while(atoi(op)<1 || atoi(op) > 3 || strspn(op, "0123456789")!=strlen(op));
        if(atoi(op) == 3)
        {
            cout<<"#-Canceled-#"<<endl;
            return 0;
        }
        while(atoi(op) == 1)
        {
            aux.k_tel++;
            cout<<"Telephone Number "<<aux.k_tel<<":\n", cin.getline(aux.Nr_tel[aux.k_tel], 21);
            while((strcmp(aux.Nr_tel[aux.k_tel], "*")==0
                    || (strspn(aux.Nr_tel[aux.k_tel], "0123456789+*#^&")!=strlen(aux.Nr_tel[aux.k_tel])
                        || (strspn(aux.Nr_tel[aux.k_tel], "*#+^&")==strlen(aux.Nr_tel[aux.k_tel]) && strcmp(aux.Nr_tel[aux.k_tel], "^") && strcmp(aux.Nr_tel[aux.k_tel], "&")))))
            {
                if(strcmp(aux.Nr_tel[aux.k_tel], "*")==0)
                    cout<<"x-Can't skip this field-x";
                else
                    cout<<"x-Please enter a valid number-x";
                cout<<endl<<"Telephone Number "<<aux.k_tel<<":\n", cin.getline(aux.Nr_tel[aux.k_tel], 21);
            }
            if(strcmp(aux.Nr_tel[aux.k_tel], "&")==0)
            {
                cout<<"#-Canceled-#"<<endl;
                aux.k_tel--;
                return 0;
            }
            else if((strcmp(aux.Nr_tel[aux.k_tel], "^")==0 || aux.Nr_tel[aux.k_tel][0] == NULL) && aux.k_tel != 1)
                aux.k_tel--;
            cout<<"Do you wish to:\n1.Add another telephone number\n2.Continue\n3.Cancel editing?\n";
            do
            {
                cin.getline(op, 21);
                for(i = 0; op[i] && op[i]==' '; i++);
                strcpy(op, op + i);
                for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
                op[i+1]='\0';
                if(atoi(op) < 1 || atoi(op) > 3 || strspn(op, "0123456789")!=strlen(op))
                    cout<<"x-Invalid option-x"<<endl
                        <<"Try again: ";
            }
            while(atoi(op) < 1 || atoi(op) > 3 || strspn(op, "0123456789")!=strlen(op));
            if(atoi(op) == 3)
            {
                cout<<"#-Canceled-#"<<endl;
                return 0;
            }
        }
    }
    do
    {
        cout<<"Other fields: "<<endl;
        for(i=0; i < nr_f; i++)
            cout<<i+1<<". "<<FieldsList[i]<<endl;
        cout<<"Choose a field number or press \'^\' to continue:\n";
        do
        {
            cin.getline(op, 21);
            for(i = 0; op[i] && op[i]==' '; i++);
            strcpy(op, op + i);
            for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
            op[i+1]='\0';
            if((atoi(op)<1 || atoi(op)>nr_f) && strcmp(op, "^") && strcmp(op, "&"))
                cout<<"x-Invalid option-x"<<endl
                    <<"Try again:\n";
        }
        while((atoi(op)<1 || atoi(op)>nr_f) && strcmp(op, "^") && strcmp(op, "&"));
        if(strcmp(op, "&")==0)
        {
            cout<<"#-Canceled-#"<<endl;
            return 0;
        }
        else if(strcmp(op, "^"))
        {
            if(atoi(op) == 3)
            {
                cout<<FieldsList[2]<<": ";
                if(biased != 2)
                    cout<<contactList[n].Fields[2]<<endl<<"New "<<FieldsList[2]<<":";
                cout<<'\n';
                bool valid;
                do
                {
                    valid = true;
                    for(i=1; i<=3 && valid; i++)
                    {
                        switch(i)
                        {
                        case(1):
                            cout<<"ZZ:\n";
                            break;
                        case(2):
                            cout<<"MM:\n";
                            break;
                        default:
                            cout<<"YYYY:\n";
                        }
                        cin.getline(op, 21);
                        if((strlen(op) != 2 && i<3) || (strlen(op) != 4 && i==3) || (i == 1 && (atoi(op) < 1 || atoi(op) > 31)) || (i == 2 && (atoi(op) < 1 || atoi(op) > 12)))
                            valid = false;
                        else if(i == 2 && (((atoi(op)==4 || atoi(op)==6 || atoi(op)==9 || atoi(op)==11) && atoi(aux.Fields[2])==31) || (atoi(op)==2 && atoi(aux.Fields[2]) > 29)))
                            valid = false;
                        else if(i == 3 && (atoi(op) % 4 != 0 && aux.Fields[2][4] == '2' && aux.Fields[2][3] == '0' && aux.Fields[2][0] == '2' && aux.Fields[2][1] == '9'))
                            valid = false;
                        else if(strcmp(op, "^")==0 || strcmp(op, "&")==0 || strcmp(op, "*")==0)
                            valid = false;
                        if(valid)
                        {
                            if(i == 1)
                                strcpy(aux.Fields[2], op);
                            else
                                strcat(aux.Fields[2], "/"), strcat(aux.Fields[2], op);
                        }
                    }
                    if(strcmp(op, "&")==0)
                    {
                        cout<<"#-Canceled-#"<<endl;
                        return 0;
                    }
                    else if(strcmp(op, "^")==0)
                        strcpy(aux.Fields[2], "N/A");
                    else if(strcmp(op, "*")==0)
                        strcpy(aux.Fields[2], contactList[n].Fields[2]);
                    else if(!valid)
                        cout<<"x-Invalid date-x"<<endl;


                }
                while(!valid && strcmp(op, "^") && strcmp(op, "*"));

            }
            else
            {
                int nr = atoi(op)-1;
                cout<<FieldsList[nr]<<": ";
                if(biased != 2)
                    cout<<contactList[n].Fields[nr]<<endl<<"New "<<FieldsList[nr]<<":";
                cout<<'\n';
                cin.getline(aux.Fields[nr], 51);
                if(strcmp(aux.Fields[nr], "&")==0)
                {
                    cout<<"x-Canceled-x"<<endl;
                    return 0;
                }
                else if(strcmp(aux.Fields[nr], "*")==0)
                    strcpy(aux.Fields[nr], contactList[n].Fields[nr]);
                else if(strcmp(aux.Fields[nr], "^")==0 || aux.Fields[nr][0]==NULL)
                    strcpy(aux.Fields[nr], "N/A");
                if(nr == 4)
                {
                    aux.Fields[nr][0] = toupper(aux.Fields[nr][0]);
                    p = strchr(aux.Fields[nr], ' ');
                    while(p!=NULL)
                    {
                        if(p - aux.Fields[nr] > 0)
                        {
                            p[1] = toupper(p[1]);
                            if(p[1] == ' ')
                                strcpy(p, p + 1), p--;
                        }
                        p = strchr(p+1, ' ');
                    }
                    for(i = 0; aux.Fields[nr][i] && aux.Fields[nr][i]==' '; i++);
                    strcpy(aux.Fields[nr], aux.Fields[nr] + i);
                    for(i = strlen(aux.Fields[nr])-1; i>=0 && aux.Fields[nr][i] == ' '; i--);
                    aux.Fields[nr][i+1]='\0';
                }
            }
        }
    }
    while(strcmp(op, "^"));
    cout<<"Do you wish to: 1.Save 2.Cancel?\n";
    do
    {
        cin.getline(op, 21);
        for(i = 0; op[i] && op[i]==' '; i++);
        strcpy(op, op + i);
        for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
        op[i+1]='\0';
        if(atoi(op)!=2 && atoi(op)!=1)
            cout<<"x-Invalid option-x"<<endl
                <<"Try again:\n";
    }
    while(atoi(op)!=2 && atoi(op)!=1);
    if(atoi(op)==1)
    {
        cout<<"#-Saved-#"<<endl;
        contactList[n] = aux;
        return 1;
    }
    cout<<"#-Canceled-#"<<endl;
    return 0;


}

void Interface()
{
    cout<<"#-Contact List Options-#"<<endl
        <<"1.Show contact list"<<endl
        <<"2.Add a new contact"<<endl
        <<"3.Search contact"<<endl
        <<"4.Exit"<<endl
        <<"Choose option:\n";
}

int Op_1()
{
    cout<<"#-Show contact list-#"<<endl<<"Total contacts: "<<k<<endl<<endl;
    char op[21];
    if(!sorted_alpha)
        Alphabetical_sort();
    for(i = 1; i <= k; i++)
        cout<<endl<<i<<'.', Show_contact(i);
    if(k == 0)
        return 0;
    cout<<endl
        <<"Do you wish to:\n1.Choose a contact to inspect?\n2.Cancel?\n";
    do
    {
        cin.getline(op, 21);
        for(i = 0; op[i] && op[i]==' '; i++);
        strcpy(op, op + i);
        for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
        op[i+1]='\0';
        if(atoi(op) < 1 || atoi(op) > 2 || strspn(op, "0123456789")!=strlen(op))
            cout<<"x-Invalid option-x"<<endl
                <<"Try again: ";
    }
    while(atoi(op) < 1 || atoi(op) > 2 || strspn(op, "0123456789")!=strlen(op));
    if(atoi(op) == 2)
    {
        cout<<"#-Canceled-#"<<endl;
        return 0;
    }
    else
    {
        do
        {
            cout<<"--Choose the index of the contact you wish to inspect--\n";
            do
            {
                cin.getline(op, 21);
                for(i = 0; op[i] && op[i]==' '; i++);
                strcpy(op, op + i);
                for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
                op[i+1]='\0';
                if(atoi(op) < 1 || atoi(op) > k || strspn(op, "0123456789")!=strlen(op))
                    cout<<"x-Invalid option-x"<<endl
                        <<"Try again: ";
            }
            while(atoi(op) < 1 || atoi(op) > k || strspn(op, "0123456789")!=strlen(op));
            Show_contact(atoi(op));
            cout<<"Do you wish to:\n1.Edit contact\n2.Remove contact\n3.Choose another contact\n4.Cancel?\n";
            do
            {
                cin.getline(op, 21);
                for(i = 0; op[i] && op[i]==' '; i++);
                strcpy(op, op + i);
                for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
                op[i+1]='\0';
                if(atoi(op) < 1 || atoi(op) > 4 || strspn(op, "0123456789")!=strlen(op))
                    cout<<"x-Invalid option-x"<<endl
                        <<"Try again:\n";
            }
            while(atoi(op) < 1 || atoi(op) > 4 || strspn(op, "0123456789")!=strlen(op));
            if(atoi(op) == 1)
                Edit_contact(atoi(op), 3);
            else if(atoi(op) == 2)
                Remove_contact(atoi(op));
            else if(atoi(op) == 4)
            {
                cout<<"#-Canceled-#"<<endl;
                return 0;
            }

        }
        while(atoi(op) == 3);

    }

}

int Op_2()
{
    k++;
    int ck = k;
    cout<<"#-Add contact-#"<<endl;
    contactList[k].index = k;
    strcpy(contactList[k].First_name, "N/A");
    strcpy(contactList[k].Last_name, "N/A");
    strcpy(contactList[k].Nr_tel[1], "N/A");
    for(i=0; i < nr_f; i++) strcpy(contactList[k].Fields[i], "N/A");
    int op = Edit_contact(k, 2);
    if(op == 0 && ck==k)
        k--;
}

int Op_3()
{
    char src[51], op[21], *p;
    int Match_list[1001];
    int k_m = 0;
    int found = -1;
    contact aux;
    cout<<"#-Search contact-#"<<endl;
    do
    {
        for(i = 0; op[i] && op[i]==' '; i++);
        strcpy(op, op + i);
        for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
        op[i+1]='\0';
        cout<<"--To cancel, press the \'$\' button--"<<endl
            <<"Type in your search:"<<endl;
        cin.getline(src, 51);
        char digits[]="0123456789+#*";
        if(strcmp(src, "$")==0)
        {
            cout<<"#-Canceled-#"<<endl;
            return 0;
        }
        if(strspn(src, digits)==strlen(src) && strspn(src, "+#*")!=strlen(src))
        {
            if(!sorted_tel)
                Telephone_sort();
            k_m = 0;
            for(i = 1; i <= k; i++)
            {
                int ok = 0;
                for(j = 1; j <= contactList[i].k_tel && !ok; j++)
                    if(strstr(contactList[i].Nr_tel[j], src))
                        Match_list[++k_m] = i, ok=1;
            }

        }
        else
        {
            k_m = 0;
            if(!sorted_alpha)
                Alphabetical_sort();
            strupr(src);
            p = strtok(src, " ");
            while(p!=NULL)
            {
                if(k_m == 0)
                    for(i=1; i<=k; i++)
                    {
                        aux = contactList[i];
                        if(strstr(strupr(aux.Last_name), p) || strstr(strupr(aux.First_name), p) || strstr(strupr(aux.Fields[4]), p))
                            Match_list[++k_m] = i;
                    }
                else
                    for(i=k_m; i>=1; i--)
                    {
                        aux = contactList[Match_list[i]];
                        if(!strstr(strupr(aux.Last_name), p) && !strstr(strupr(aux.First_name), p) && !strstr(strupr(aux.Fields[4]), p))
                        {
                            for(j = i; j < k_m; j++)
                                Match_list[j] = Match_list[j+1];
                            k_m--;
                        }
                    }
                p = strtok(NULL, " ");
            }
        }
        if(k_m == 0)
        {
            found=-1;
            cout<<"x-Contact not found-x"<<endl
                <<"Do you wish to: 1.Search for another contact 2.Cancel?\n";
            do
            {
                cin.getline(op, 21);
                for(i = 0; op[i] && op[i]==' '; i++);
                strcpy(op, op + i);
                for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
                op[i+1]='\0';
                if(atoi(op)!=1 && atoi(op)!=2 && strspn(op, "0123456789")==strlen(op))
                    cout<<"x-Invalid option-x"<<endl
                        <<"Try again:\n";
            }
            while(atoi(op)!=1 && atoi(op)!=2 && strspn(op, "0123456789")==strlen(op));
            if(atoi(op)==2)
            {
                cout<<"#-Canceled-#"<<endl;
                return 0;
            }

        }
        else if(k_m == 1)
            found = Match_list[1];
        else if(k_m > 1)
        {
            cout<<"--Total matching contacts found: "<<k_m<<"--"<<endl<<endl;
            for(i = 1; i <= k_m; i++)
                cout<<i<<'.', Show_contact(Match_list[i]), cout<<endl;
            cout<<"Do you wish to: \n1.Choose a contact to inspect\n2.Search for another contact\n3.Cancel?\n";
            do
            {
                cin.getline(op, 21);
                for(i = 0; op[i] && op[i]==' '; i++);
                strcpy(op, op + i);
                for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
                op[i+1]='\0';
                if(atoi(op) < 1 || atoi(op) > 3 || strspn(op, "0123456789")!=strlen(op))
                    cout<<"x-Invalid option-x"<<endl
                        <<"Try again: ";
            }
            while(atoi(op) < 1 || atoi(op) > 3 || strspn(op, "0123456789")!=strlen(op));
            if(atoi(op)==3)
            {
                cout<<"#-Canceled-#"<<endl;
                return 0;
            }
            else if(atoi(op) == 2)
                found = -1;
            else
            {
                cout<<"--Choose the index of the contact you wish to inspect--\n";
                do
                {
                    cin.getline(op, 21);
                    for(i = 0; op[i] && op[i]==' '; i++);
                    strcpy(op, op + i);
                    for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
                    op[i+1]='\0';
                    if(strspn(op, "0123456789")!=strlen(op) || atoi(op) > k_m || atoi(op) < 1)
                        cout<<"x-Invalid option-x"<<endl
                            <<"Try again: ";
                }
                while(strspn(op, "0123456789")!=strlen(op) || atoi(op) > k_m || atoi(op) < 1);
                found = Match_list[atoi(op)];
            }

        }
        if(found != -1)
        {
            cout<<"#-Contact found-#"<<endl<<endl;
            Show_contact(found);
            cout<<"Do you wish to:\n1.Edit contact\n2.Remove contact\n3.Search another contact\n4.Cancel?\n";
            do
            {
                cin.getline(op, 21);
                for(i = 0; op[i] && op[i]==' '; i++);
                strcpy(op, op + i);
                for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
                op[i+1]='\0';
                if(atoi(op)<1 || atoi(op)>4 || strspn(op, "0123456789")!=strlen(op))
                    cout<<"x-Invalid option-x"<<endl
                        <<"Try again:\n";
            }
            while(atoi(op)<1 || atoi(op)>4 || strspn(op, "0123456789")!=strlen(op));
            if(atoi(op)==1)
                Edit_contact(found, 3);
            else if(atoi(op)==2)
                Remove_contact(found);
            else if(atoi(op)==4)
            {
                cout<<"#-Canceled-#"<<endl;
                return 0;
            }
            else if(atoi(op) == 3)
                found = -1;
        }

    }
    while(found == -1);
    return 1;
}


int main()
{
    char op[21];
    Load();
    do
    {
        Interface();
        cin.getline(op, 21);
        for(i = 0; op[i] && op[i]==' '; i++);
        strcpy(op, op + i);
        for(i = strlen(op)-1; i>=0 && op[i]==' '; i--);
        op[i+1]='\0';
        cout<<endl;
        switch(atoi(op))
        {
        case 1:
            Op_1();
            break;
        case 2:
            Op_2();
            break;
        case 3:
            Op_3();
            break;
        case 4:
            cout<<"#-Exit-#"<<endl;
            cout<<"--All contacts have been saved--";
            break;
        default:
            cout<<"x-Invalid option-x"<<endl;
        }
        cout<<endl;
    }
    while(atoi(op)!=4);
    Save();
    return 0;
}

