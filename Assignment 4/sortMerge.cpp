#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

struct EmpBlock
{
    int eid; //Key
    string ename;
    int age;
    double salary;
};

struct DeptBlock
{
    int did; //Key
    string dname;
    double budget;
    int managerid;
};

//Print out the attributes from emp and dept when a join condition is met
void printJoin(EmpBlock emp, DeptBlock dept, fstream &fout)
{
    fout << emp.eid << ',' << emp.ename << ',' << emp.age << ','
         << emp.salary << ',' << dept.did << ',' << dept.dname << ','
         << dept.budget << "\n";
}

/**
 * 
 * Sort algorthim referenced here 
 * https://stackoverflow.com/questions/873715/c-sort-with-structs/874352
 * 
 * */
bool compareEmp(const EmpBlock &lhs, const EmpBlock &rhs)
{
    return lhs.eid < rhs.eid;
}

bool compareDept(DeptBlock const &lhs, DeptBlock const &rhs)
{
    return lhs.managerid < rhs.managerid;
}

void sortMerge(vector<EmpBlock> emp, vector<DeptBlock> dept)
{

    fstream joinout;
    joinout.open("join.csv", ios::app);
    if (!joinout)
    {
        cerr << "File can't be opened! " << endl;
        exit(1);
    }

    //Sort emp block
    sort(emp.begin(), emp.end(), compareEmp);

    //Sort dept block
    sort(dept.begin(), dept.end(), compareDept);

    int empSize = emp.size();
    cout << empSize << endl;
    int deptSize = dept.size();
    cout << deptSize << endl;

    ofstream empSort;
    empSort.open("empsort.csv");
    empSort << "Eid, ename, age, salary" << endl;
    for (int i = 0; i < empSize; i++)
    {
        empSort << " " << emp[i].eid << " " << emp[i].ename << " " << emp[i].age << " " << emp[i].salary << " " << endl;
    }
    empSort.close();
    ofstream deptSort;
    deptSort.open("deptsort.csv");
    deptSort << "did, dname, budget, managerid" << endl;
    for (int i = 0; i < deptSize; i++)
    {
        deptSort << " " << dept[i].did << " " << dept[i].dname << " " << dept[i].budget << " " << dept[i].managerid << " " << endl;
    }
    deptSort.close();

    int count = 0;
    int mark = 0, r = 0, s = 0, empCount = 0, deptCount = 0;
    do
    {
        if (!mark)
        {
            while (emp[r].eid < dept[s].managerid)
            {
                cout << "Inside first while loop emp: " << emp[r].eid << " dept: " << dept[s].managerid << endl;
                r++;
            }

            if (emp[r].eid > dept[s].managerid)
            {
                cout << "Inside second while loop emp: " << emp[r].eid << " dept: " << dept[s].managerid << endl;
                s++;
            }
            mark = s;
        }
        if (emp[r].eid == dept[s].managerid)
        {
            cout << "Before adding to file emp: " << emp[r].eid << " dept: " << dept[s].managerid << endl;

            joinout << emp[r].eid << ", " << emp[r].ename << ", " << emp[r].age << ", "
                    << emp[r].salary << ", " << dept[s].did << ", " << dept[s].dname << ", "
                    << dept[s].budget << "\n";
            count++;
            s++;
        }
        else
        {
            s = mark;
            r++;
            mark = 0;
            count++;
        }
        // }while(count < 110);
    } while (r != empSize && s != deptSize);

    return;
}

int main()
{
    // open file streams to read and write
    fstream empin;
    fstream deptin;

    int i = 0;

    //open files
    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);

    //structs
    std::vector<EmpBlock> emp;
    std::vector<DeptBlock> dept;

    string line, word;

    if (!empin || !deptin)
    {
        cerr << "File can't be opened! " << endl;
        exit(1);
    }

    //Read in from emp file
    while (getline(empin, line) && !line.empty())
    {
        emp.push_back(EmpBlock());

        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word, ',');
        emp[i].eid = stoi(word);
        getline(s, word, ',');
        emp[i].ename = word;
        getline(s, word, ',');
        emp[i].age = stoi(word);
        getline(s, word, ',');
        emp[i].salary = stod(word);
        i++;
    }
    empin.close();
    i = 0;
    //Read in from dept file
    while (getline(deptin, line) && !line.empty())
    {
        dept.push_back(DeptBlock());

        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word, ',');
        dept[i].did = stoi(word);
        getline(s, word, ',');
        dept[i].dname = word;
        getline(s, word, ',');
        dept[i].budget = stoi(word);
        getline(s, word, ',');
        dept[i].managerid = stoi(word);
        i++;
    }
    deptin.close();
    cout << "here" << endl;

    sortMerge(emp, dept);

    return 0;
}
