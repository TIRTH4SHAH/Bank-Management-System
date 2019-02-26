#include<iostream>
#include<fstream>//support input and output operation on files
#include<cstdlib>//converting data type
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;//provide output operation
using std::ifstream;//provide output operation
using std::ios;
class account_query
{
    private:
        char account_number[20];
        char firstName[10];
        char lastName[10];
        float total_Balance;
    public:
        void read_data();
        void show_data();
        void write_rec();
        void read_rec();
        void search_rec();
        void edit_rec();
        void delete_rec();
};
void account_query::read_data()
{
    cout<<"\nEnter Account Number: ";
    cin>>account_number;
    cout<<"Enter First Name: ";
    cin>>firstName;
    cout<<"Enter Last Name: ";
    cin>>lastName;
    cout<<"Enter Balance: ";
    cin>>total_Balance;
    cout<<endl;
}
void account_query::show_data()
{
    cout<<"Account Number: "<<account_number<<endl;
    cout<<"First Name: "<<firstName<<endl;
    cout<<"Last Name: "<<lastName<<endl;
    cout<<"Current Balance: Rs.  "<<total_Balance<<endl;
    cout<<"-------------------------------"<<endl;
}
void account_query::write_rec()
{
    ofstream outfile;//object of output file that manges the output stream
    outfile.open("record.bank", ios::binary|ios::app);//create binary file and append to end of file
    read_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this)); //starting adress of location where memory is
    outfile.close();//stored,write the data from the file into an object named this
}
void account_query::read_rec()
{
    ifstream infile;//object of input file that manges the input stream
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this))>0)
        {
            show_data();
        }
    }
    infile.close();
}
void account_query::search_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);//tellg gives current position of get pointer
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Search: ";
    cin>>n;
    infile.seekg((n-1)*sizeof(*this));//get pointer moves to specific location
    infile.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_data();
}
void account_query::edit_rec()
{
    int n;
    fstream iofile;
    iofile.open("record.bank", ios::in|ios::binary);
    if(!iofile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    iofile.seekg(0, ios::end);//go to the end to 0 position
    int count = iofile.tellg()/sizeof(*this);//tellg gives current position of get pointer
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    iofile.seekg((n-1)*sizeof(*this));
    iofile.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    show_data();
    iofile.close();
    iofile.open("record.bank", ios::out|ios::in|ios::binary);
    iofile.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    read_data();
    iofile.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void account_query::delete_rec()
{
    int n;
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    infile.seekg(0,ios::end);
    int count = infile.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank", ios::out|ios::binary);
    infile.seekg(0);//go to start
    for(int i=0; i<count; i++)
    {
        infile.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    infile.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
    cout<<"Your record is delete."<<endl;
}
int main()
{
    account_query A;
    int choice;
    cout<<"***Account Information System***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add record to file";
        cout<<"\n\t2-->Show record from file";
        cout<<"\n\t3-->Search Record from file";
        cout<<"\n\t4-->Update Record";
        cout<<"\n\t5-->Delete Record";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                A.write_rec();
                break;
            case 2:
                A.read_rec();
                break;
            case 3:
                A.search_rec();
                break;
            case 4:
                A.edit_rec();
                break;
            case 5:
                A.delete_rec();
                break;
            case 6:
                exit(0);
                break;
            default:
                cout<<"\nEnter corret choice";
                exit(0);
        }
    }
    system("pause");
    return 0;
}
