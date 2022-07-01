#include <iostream>  //rand()
#include <vector>    // array vector<int>
#include <windows.h> // Sleep
#include <fstream>   // files
#include <sstream>   //concatenate string
#include <time.h>    // current time
using namespace std;

string ret_time()
{
    time_t tim = time(0);
    tm *ntime = localtime(&tim);
    string s = asctime(ntime);
    s.pop_back();
    return s;
}

class acc_open
{
    int acc_num;

protected:
    long long int mob_no;
    float balance;
    string type_acc, name, pass, dob, ctran;

public:
    // a=name b=mob_num i=dob t=type of account opening p=pass
    acc_open() {}
    // acc_open(string a, long long int b, string i, string p)
    // {
    //     name = a;
    //     mob_no = b;
    //     dob = i;
    //     pass = p;
    //     type_acc = "saving";

    //     srand(time(0));
    //     acc_num = rand();

    //     cout << "\t\t\tYour accout has been created succesfully..... \n";
    //     Sleep(2000);
    //     cout << "\t\t\tYour account number is " << acc_num << endl;
    //     Sleep(1000);

    //     balance = 0;

    //     ostringstream os;
    //     os << name << "_" << mob_no << ".txt";
    //     ctran = os.str();

    //     fstream out_tran(ctran, ios::app);
    //     out_tran << balance << ", ";
    //     out_tran << ret_time();
    //     out_tran.close();
    // }
    acc_open(string a, long long int b, string i, string p, string t)
    {
        name = a;
        mob_no = b;
        dob = i;
        pass = p;
        type_acc = t;
        srand(time(0));
        acc_num = rand();
        cout << "\t\t\tYour accout has been created succesfully..... \n";
        Sleep(2000);
        cout << "\t\t\tYour account number is " << acc_num << endl;
        Sleep(1000);

        if (type_acc == "fixed")
            balance = 1000;
        else if (type_acc == "saving")
            balance = 0;
        else
            balance = 10000;

        ostringstream os;
        os << name << "_" << mob_no << ".txt";
        ctran = os.str();

        fstream out_tran(ctran, ios::app);
        out_tran << balance << ", ";
        out_tran << ret_time();
        out_tran.close();
    }
    void save_data()
    {
        fstream aout("acc_detail.txt", ios::app);
        aout << acc_num << " ";
        aout << pass << " ";
        aout << name << " ";
        aout << balance << " ";
        aout << type_acc << " ";
        aout << mob_no << " \n";
        aout.close();
    }
    ~acc_open(){
        cout << "\t\t\tCongratulation's on becoming part of Virtual-Bank." << endl;
        Sleep(1000);
    }
};

class login : private acc_open
{
    void set_balance(float bal)
    {
        string s = ret_time();
        fstream out_tra(ctran, ios::app);
        out_tra << '\n';
        out_tra << bal << ',';
        out_tra << s;
        out_tra.close();
    }

public:
    login(string a, string type, string mob)
    {
        cout << "\n\t ********************************************************* \n\n";
        name = a;
        type_acc = type;
        balance = 0;

        ostringstream os;
        os << name << "_" << mob << ".txt";
        ctran = os.str();

        string a1, a2;
        fstream in_tran(ctran, ios::in);
        while (in_tran.eof() != 1)
        {
            getline(in_tran, a1, ',');
            getline(in_tran, a2, '\n');
            balance += stof(a1);
        }
        in_tran.close();

        cout << "\t\t Name :" << name << "\tBalance :" << balance << endl;
    }

    void transaction(float b)
    {
        balance += b;
        try
        {
            if (balance < 0)
                throw -1;

            if (type_acc == "fixed" && balance < 1000)
            {
                balance -= (balance / 5);
                set_balance(-(balance / 5));
            }

            if (type_acc == "current" && balance < 10000)
            {
                balance -= (balance / 7);
                set_balance(-(balance / 7));
            }

            set_balance(b);

            cout << "\t Current balance : " << balance << endl;
        }
        catch (int v)
        {
            cout << "\t Insufficient amount" << endl;
        }
    }

    void print_trans()
    {
        vector<int> s;
        string s1, s2;
        int a = 0;
        fstream in_tran(ctran, ios::in);
        while (in_tran.eof() != 1)
        {
            getline(in_tran, s1);
            s.push_back(s1.size());
        }
        int i = s.size();
        int n = i;
        int x = 0;
        while (i > n - 10 && i > 0)
        {
            a += s[i - 1];
            in_tran.seekg(-a - x, in_tran.end);
            getline(in_tran, s2, '\n');
            cout << s2 << endl;
            x += 2;
            i--;
        }
        in_tran.close();
    }

    ~login()
    {
        Sleep(2000);
        cout << "\tLog out....." << endl;
    }
};

bool validation(string p)
{
    int n = p.size();
    int arr[4] = {0}; // 0 0 0 0   Pri123@# 1 1 1 1
    if (!(n >= 8 && n <= 15))
    {
        cout << "\tLength must be more than 8 and less than 15" << endl;
        return false;
    }
    for (int i = 0; i < n; i++)
    {
        if (p[i] >= 'A' && p[i] <= 'Z')
        {
            arr[0] = 1;
            continue;
        }
        else if (p[i] >= 'a' && p[i] <= 'z')
        {
            arr[1] = 1;
            continue;
        }
        else if (p[i] >= '0' && p[i] <= '9')
        {
            arr[2] = 1;
            continue;
        }
        else if (p[i] == '#' || p[i] == '&' || p[i] == '@' || p[i] == '$' || p[i] == '%')
        {
            arr[3] = 1;
            continue;
        }
    }
    if (arr[0] == 0)
    {
        cout << "\tAdd capital letter's " << endl;
        return false;
    }
    if (arr[1] != 1)
    {
        cout << "\tAdd small letter's" << endl;
        return false;
    }
    if (arr[2] != 1)
    {
        cout << "\tAdd number's" << endl;
        return false;
    }
    if (arr[3] != 1)
    {
        cout << "\tAdd special character's like @#$%&" << endl;
        return false;
    }
    return true;
}

int main()
{
    cout << "\t\t\t Welcome To Virtual-Bank" << endl;

    string name, dob;
    long long int mob_num;
    string type, pass;

    int choose;
    cout << "\t\t\t    Sign-Up or Log-in \n"
         << "Enter 1 for account opening 2 for login : ";
    cin >> choose;

    if (choose == 1)
    {
        cout << "\t\t\t Enter personal details " << endl;

        cout << "\t Enter your name : ";
        cin >> name;

        cout << "\t Enter your Date of birth : ";
        cin >> dob;

        cout << "\t Enter your mobile number : ";
        cin >> mob_num;

        cout << "\t NOTE:- Password must include capital letter, small letter, number and special character's like @#$ \n"
             << "\t Length must be bet 8 to 16" << endl;

        while (true)
        {
            cout << "\t Enter password : ";
            cin >> pass;
            if (validation(pass))
                break;
            else
                continue;
        }

        cout << "\t Enter the type of account you want to start with : ";
        cin >> type;

        // if (type == "saving")
        // {
        //     cout << "\t\t We are opening your saving account \n"
        //          << "\t\t\t Please wait...." << endl;
        //     Sleep(5000);
        //     acc_open user(name, mob_num, dob, pass);
        //     user.save_data();
        // }

        if (type == "fixed" || type == "current" || type == "saving")
        {
            cout << "\t\t We are opening your saving account \n"
                 << "\t\t\t Please wait...." << endl;
            Sleep(5000);
            acc_open user(name, mob_num, dob, pass, type);
            user.save_data();
        }

        else
        {
            cout << "\tYou have enter wrong type of account number.."
                 << "\tPlease choose saving,fixed,current." << endl;
        }
        cout << "\t\t Do you want to log-in? (y/n)";
        char cho;
        cin >> cho;
        if (cho == 'y' || cho == 'Y')
            choose = 2;
        else
            return 0;
    }
    if (choose == 2)
    {
        string i1, i2, i3, i4, i5, i6;
        while (true)
        {
            cout << "\tEntr account number : ";
            string ac;
            cin >> ac;
            string p;
            cout << "\tEnter password : ";
            cin >> p;

            fstream ain("acc_detail.txt", ios::in);
            bool flag = 0;
            while (ain.eof() != 1)
            {
                ain >> i1;
                ain >> i2;
                if (i1 == ac && i2 == p)
                {
                    flag = 1;
                    ain >> i3;
                    ain >> i4;
                    ain >> i5;
                    ain >> i6;
                    break;
                }
                else
                    continue;
            }
            ain.close();
            if (flag)
                break;
            else
            {
                char s;
                cout << "\t\t Account number/Password is wrong" << endl;
                cout << "\t Do you want to try again? (y/n)";
                cin >> s;
                if (s == 'y' || s == 'Y')
                    continue;
                else
                    return 0;
            }
        }

        login obj(i3, i5, i6);
        int wide;
        cout << "\t\t Do you want to withdraw,deposite or see last transaction ? " << endl;
        cout << "\t\t\t 1 for Withdraw\n"
             << "\t\t\t 2 for Deposite\n"
             << "\t\t\t 3 for Last transaction\n\t\t\t";
        float amm;

        while (true)
        {
            cout << "\t 1-withdraw, 2-deposit, 3-transation : ";
            cin >> wide;
            switch (wide)
            {
            case 1:
                cout << "\t\t Enter the amount : ";
                cin >> amm;
                obj.transaction(-amm);
                break;

            case 2:
                cout << "\t\t Enter the amount : ";
                cin >> amm;
                obj.transaction(amm);
                break;

            case 3:
                obj.print_trans();
                break;

            default:
                cout << "\t\t Choose the correct option" << endl;
                break;
            }
            int c = 1;
            cout << "\t Do you want to log out or stay ?(1/2) ";
            cin >> c;
            if (c == 1)
                break;
            else
                continue;
        }
    }
    else
        cout << "\t\tChoose appropriate option " << endl;
    return 0;
}
