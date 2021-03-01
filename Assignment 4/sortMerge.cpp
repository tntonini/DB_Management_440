#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

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

struct JoinBlock
{
    int id;
    string ename;
    int age;
    double salary;
    int did;
    string dname;
    double budget;
};

// Grab a single block from the emp.csv file, in theory if a block was larger than
// one tuple, this function would return an array of EmpBlocks and the entire if
// and else statement would be wrapped in a loop for x times based on block size
EmpBlock grabEmp(fstream &empin)
{
    string line, word;
    EmpBlock emp;
    // grab entire line
    if (getline(empin, line, '\n'))
    {
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word, ',');
        emp.eid = stoi(word);
        getline(s, word, ',');
        emp.ename = word;
        getline(s, word, ',');
        emp.age = stoi(word);
        getline(s, word, ',');
        emp.salary = stod(word);
        return emp;
    }
    else
    {
        emp.eid = -1;
        return emp;
    }
}

// Grab a single block from the dept.csv file, in theory if a block was larger than
// one tuple, this function would return an array of DeptBlocks and the entire if
// and else statement would be wrapped in a loop for x times based on block size
DeptBlock grabDept(fstream &deptin)
{
    string line, word;
    DeptBlock dept;
    if (getline(deptin, line, '\n'))
    {
        stringstream s(line);
        getline(s, word, ',');
        dept.did = stoi(word);
        getline(s, word, ',');
        dept.dname = word;
        getline(s, word, ',');
        dept.budget = stod(word);
        getline(s, word, ',');
        dept.managerid = stoi(word);
        return dept;
    }
    else
    {
        dept.did = -1;
        return dept;
    }
}

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
bool compareEmp(EmpBlock const &lhs, EmpBlock const &rhs)
{
    return lhs.eid < rhs.eid;
}

bool compareDept(DeptBlock const &lhs, DeptBlock const &rhs)
{
    return lhs.did < rhs.did;
}

void sortMerge(vector<EmpBlock> emp, vector<DeptBlock> dept)
{
    //Sort emp block
    sort(emp.begin(), emp.end(), compareEmp);

    //Sort dept block
    sort(dept.begin(), dept.end(), compareDept);

    cout << "lol" << endl;
    return;
}

int main()
{
    // open file streams to read and write
    fstream empin;
    fstream deptin;
    fstream joinout;

    //open files
    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);
    joinout.open("Join.csv", ios::out);

    //structs
    vector<EmpBlock> empBlock;
    vector<DeptBlock> deptBlock;

    EmpBlock emp;
    DeptBlock dept;

    string line, word;


    if (!empin || !deptin)
    {
        cerr << "File can't be opened! " << endl;
        exit(1);
    }

    //Read in from emp file
    while(getline(empin, line) && !line.empty()){
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        emp.eid = stoi(word);
        getline(s, word, ',');
        emp.ename = word;
        getline(s, word, ',');
        emp.age = stoi(word);
        getline(s, word, ',');
        emp.salary = stod(word);

        empBlock.push_back(emp);
    }

        //Read in from dept file
    while(getline(deptin, line) && !line.empty()){
        // turn line into a stream
        stringstream s(line);
        // gets everything in stream up to comma
        getline(s, word,',');
        dept.did = stoi(word);
        getline(s, word, ',');
        dept.dname = word;
        getline(s, word, ',');
        dept.budget = stoi(word);
        getline(s, word, ',');
        dept.managerid = stoi(word);

        deptBlock.push_back(dept);
    }


    sortMerge(empBlock, deptBlock);


    return 0;
}
