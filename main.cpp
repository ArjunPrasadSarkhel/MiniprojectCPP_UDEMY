#include <iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include<iomanip>

using namespace std;

//Creating a global var. for printing employees
const int empid_width = 8;
const int empname_width = 20;
const int empmail_width = 25;
const int empnumbers_width = 10;//for all numeric values like basic, pf etc;
const int total_width = 100;
//create structure to hold each of the empl. record
struct employee
{
    int emp_id;
    string emp_name;
    double emp_basic;
    double emp_pf;
    double emp_healthinsr;
    string emp_emailid;
};


void readfile(vector <employee>& e)//function to read line and store in the vector
{
    ifstream fin;
    string line;
    fin.open("emp.txt");
    while(!fin.eof())
    {
        std::getline(fin, line);//to read a complete line 1param  = source stream, 2param = where to store it
        //cout<<line<<endl;
        istringstream iss(line);
        string str_eid;
        string str_ename;
        string str_ebasic;
        string str_epf;
        string str_ehealthinsr;
        string str_emailid;
        //parsing all the strings
        std::getline(iss,str_eid,',');
        std::getline(iss,str_ename,',');
        std::getline(iss,str_ebasic,',');
        std::getline(iss,str_epf,',');
        std::getline(iss,str_ehealthinsr,',');
        std::getline(iss,str_emailid,',');

        employee temp;
        temp.emp_id = atoi(str_eid.c_str());//use atoi(ascii to int) to convert string to int only works in legacy c string not c++ normal string
        temp.emp_name = str_ename;
        temp.emp_basic = atof(str_ebasic.c_str());//use atof(ascii to float) to convert string to double only works in legacy c string not c++ normal string
        temp.emp_pf = atof(str_epf.c_str());//use atof(ascii to float) to convert string to double only works in legacy c string not c++ normal string
        temp.emp_healthinsr = atof(str_ehealthinsr.c_str());//use atof(ascii to float) to convert string to double only works in legacy c string not c++ normal string
        temp.emp_emailid = str_emailid;
        e.push_back(temp);//temp object is now inside the vector e


    }
    fin.close();
}


void printoptions()
{
    cout<<"1. Add an employ"<<endl;
    cout<<"2. Print employ report"<<endl;
    cout<<"3. Search an empploy"<<endl;
    cout<<"4. Delete employ"<<endl;
    cout<<"5. Save"<<endl;
    cout<<"6. Exit"<<endl;
}


int search_emp(vector <employee> e, int target_id)//no reference as its only a check
{
    for(int i  = 0; i < e.size(); i++)//linear search
    {
        if(e[i].emp_id == target_id)//target found
        {
            return i;
        }
    }
    return -1; //none of the employee found
}


void addemp(vector <employee>& e)//add an employ
{
    employee test_id;

    bool duplicatecheck = false;
    do{
        cout<<"Enter employee id";
        cin>>test_id.emp_id;
        duplicatecheck = false; // to check if duplicate or not
        if(search_emp(e,test_id.emp_id)!=-1)//means dupilcate there // if found index of emp. id in the vector, if not found then -1.
        {
            duplicatecheck = true;
            cout<<"An employee with an id"<<test_id.emp_id<<"exists, please input another id"<<endl;

        }

    }while(duplicatecheck);//will be true if dupilcate there and it will iterate again
    cout << "Name:  ";
    //After giving an id, user have to press enter to terminate, so to handle that we need to clear the cin, else it
    //cause problem in the getline method
    cin.clear();
    cin.ignore(INT_MAX,'\n');//going to ignore all the enter key in the cin, here '\n' means the enter key.
    // only when we going to take a single character then only we need to clear cin buffer.
    std::getline(cin, test_id.emp_name);

    cout<< "Basic salary:  ";
    cin>> test_id.emp_basic;
    cout<< "Provident fund:  ";
    cin>>test_id.emp_pf;
    cout<< "Health insurance:  ";
    cin>>test_id.emp_healthinsr;
    cin.clear();
    cin.ignore(INT_MAX,'\n');//as email id is a string so again we need to clear the buffer
    std::getline(cin, test_id.emp_emailid);

    e.push_back(test_id);//push the test_id object into the vector
    cout<<"Employee with id: "<<test_id.emp_id<<" added successfully"<<endl;
    cout<<"Total employees: "<<e.size();

}


double gross_sal(employee e)//to return gross salary
{
    return e.emp_basic - (e.emp_pf + e.emp_healthinsr);
}


void printemployee(employee e)//going to take the employee object and print employee objeect
{
    cout<<setw(empid_width)<<left<<e.emp_id
        <<setw(empname_width)<<left<<e.emp_name
        <<setw(empmail_width)<<left<<e.emp_emailid
        <<setw(empnumbers_width)<<setprecision(2)<<fixed<<right<<e.emp_basic
        <<setw(empnumbers_width)<<setprecision(2)<<fixed<<right<<e.emp_pf
        <<setw(empnumbers_width)<<setprecision(2)<<fixed<<right<<e.emp_healthinsr
        <<setw(empnumbers_width)<<setprecision(2)<<fixed<<right<<gross_sal(e)
        <<endl;
}


void printemployees(vector <employee> e)//for display
{
    cout<<endl;
    //first headings
    cout<<setw(empid_width)<<left<<"EID"
        <<setw(empname_width)<<left<<"Name"
        <<setw(empmail_width)<<left<<"Email"
        <<setw(empnumbers_width)<<right<<"Basic"
        <<setw(empnumbers_width)<<right<<"PF"
        <<setw(empnumbers_width)<<right<<"Hlth."
        <<setw(empnumbers_width)<<right<<"Net"
        <<endl;
    //to print the line after header(just to make it look good)
    cout<< setw(total_width) <<setfill('-') << " ";//for 100 col setfill will fill rest of the line with '-' character
    cout<< setfill(' ');//to reset the setfill

    //to store the total basic, pf etc.
    double tot_basic = 0.0;
    double tot_pf = 0.0;
    double tot_healthins = 0.0;
    double tot_netsal = 0.0;

    for(vector <employee>::iterator it = e.begin(); it != e.end(); it++)
    {
        //it pointing to first employee object, then second etc;
        printemployee(*it); //*it is the current employee object//printemployee is the function which is called here

        tot_basic += it->emp_basic;
        tot_pf += it->emp_pf;
        tot_healthins += it->emp_healthinsr;
        tot_netsal += gross_sal(*it);//going to return the net salary
    }
    cout<< setw(total_width) <<setfill('-') << " ";//for 100 col setfill will fill rest of the line with '-' character
    cout<< setfill(' ');
    cout << setw(empid_width)<<left<<"Total"
         << setw(empname_width)<<left<<"In"
         << setw(empmail_width)<<left<<" "
         << setw(empnumbers_width)<< setprecision(2)<<right<< fixed << tot_basic//setprecision used here to round-off two decimal digits
         << setw(empnumbers_width)<< setprecision(2)<<right<< fixed << tot_pf
         << setw(empnumbers_width)<< setprecision(2)<<right<< fixed << tot_healthins
         << setw(empnumbers_width)<< setprecision(2)<<right<< fixed << tot_netsal
         <<endl;
}


void savetofile(vector <employee> e)
{
    ofstream fout("emp.txt");
    if(!fout)
    {
        cout<<"Unable to open file";
    }
    int c = 0;
    for(vector <employee>::iterator it = e.begin(); it!=e.end(); it++)
    {
        fout << it->emp_id<<","<< it->emp_name<<","<<it->emp_basic<<","
             << it->emp_pf<<","<< it->emp_healthinsr<<","<<it->emp_emailid;
        c++;
        if (c != e.size())
        {
            fout<<endl;
        }
    }
    fout.close();
    cout<<"Total: "<<c<<" records added";
}


bool del_emp(vector <employee>& e, int target_id)//target_id is the id which we want to delete
{
    int index = search_emp(e, target_id);
    if(index==-1)
    {
        return false;
    }
    //record found
    cout<<"Employee with id: "<<target_id <<" found";
    printemployee(e[index]);
    cout<<"Are you sure you want to delete, Input 1 to delete, 0 to exit";
    int option;
    cin>>option;
    if(option == 1)
    {
        e.erase(e.begin() + index);//going to delete target record;
        return true;
    }
    return false;
}


void performtask(vector <employee>& e,int option)
{
    int targetemp_id;
    int index;
    switch(option)
    {
    case 1: addemp(e);
        //cout<<"Option 1. Add employee chosen"<<endl;
        break;
    case 2: printemployees(e);//cout<<"Option 2. Print employee chosen"<<endl;
        break;
    case 3: //cout<<"Option 3. Search employee chosen"<<endl;
        cout<<"Enter employee id to search";
        cin>>targetemp_id;
        index = search_emp(e, targetemp_id);
        if(index == -1)
        {
            cout<<"Target employee"<<targetemp_id<<"doesn't exits";
        }
        else
        {
            cout<<"Target employee found: "<<targetemp_id;
            printemployee(e[index]);

        }


        break;
    case 4: //cout<<"Option 4. Delete employee chosen"<<endl;
        cout<<"Enter employee id to delete";
        cin>>targetemp_id;
        if(del_emp(e, targetemp_id))
        {
            //if true
            cout<<"Employee delete successfully";
            cout<<"Press 5 to save it permanantly"<<endl;
        }
        else
        {
            cout<<"Not deleted";
        }
        break;
    case 5: savetofile(e); //cout<<"Option 5. Save employee chosen"<<endl;
        break;
    default:
        cout<<"Not a valid menu option, choose from 1-6"<<endl;
    }

}


int main()
{
    vector <employee> e; //store all the employee objects

    readfile(e);

    cout<<"Total"<<e.size()<<"no. of records read from file"<<endl;
    printoptions();
    bool exit = false;
    while(!exit)
    {
        int option;
        cout<<"Please enter what you want to perform";
        cin>>option;
        if(option == 6)
        {
            exit = true;
        }
        else
        {
            performtask(e,option);//passing vector of objects, options as parameter
        }


    }
}
