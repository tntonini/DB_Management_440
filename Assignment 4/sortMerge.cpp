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
    int deptSize = dept.size();

    int count = 0;
    int mark = 0, r = 0, s = 0, empCount = 0, deptCount = 0;
    do
    {
        if (!mark)
        {
            //if the eid is less than managerid, incrfement it
            while (emp[r].eid < dept[s].managerid)
            {
                r++;
            }

            //if the managerid is less than eid, increment it
            if (emp[r].eid > dept[s].managerid)
            {
                s++;
            }
            mark = s;
        }

        //if they are they same element then print it to the .csv
        if (emp[r].eid == dept[s].managerid)
        {
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

    sortMerge(emp, dept);

    return 0;
}
