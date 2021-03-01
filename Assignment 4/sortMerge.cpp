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

JoinBlock sortMerge(EmpBlock emp[], DeptBlock dept[])
{
    //Sort emp block
    sort(emp, emp + 30, &compareEmp);

    //Sort dept block
    sort(dept, dept + 15, &compareDept);
}

int main()
{
    // open file streams to read and write
    fstream empin;
    fstream deptin;
    fstream joinout;

    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);
    joinout.open("Join.csv", ios::out);

    EmpBlock empBlock[30];
    DeptBlock deptBlock[15];

    if (!empin || !deptin)
    {
        cerr << "File can't be opened! " << endl;
        exit(1);
    }
    for (int i = 0; i < 30; i++)
    {
        empin >> empBlock[i].eid >> empBlock[i].ename >> empBlock[i].age >> empBlock[i].salary;
    }
    for (int i = 0; i < 15; i++)
    {
        deptin >> deptBlock[i].did >> deptBlock[i].dname >> deptBlock[i].budget >> deptBlock[i].managerid;
    }

    sortMerge(empBlock, deptBlock);

    /*
    // flags check when relations are done being read
    bool flag = true;
    while (flag)
    {
        // FOR BLOCK IN RELATION EMP

        // grabs a block
        empBlock = grabEmp(empin);
        // checks if filestream is empty
        if (empBlock.eid == -1)
        {
            flag = false;
        }
        bool iflag = true;
        // opens new filestream for dept relation (needs to read in a new one each time a new emp block is seen)
        fstream deptin;
        deptin.open("Dept.csv", ios::in);
        while (iflag)
        {
            // FOR BLOCK IN RELATION DEPT
            deptBlock = grabDept(deptin);

            // in theory these would iterate through the two blocks: empBlock and deptBlock
            // but since both only contain one tuple, no iteration is needed
            if (deptBlock.did == -1)
            {
                iflag = false;
            }
            else
            {

                // check join condition and print join to output file
                if (deptBlock.managerid == empBlock.eid)
                {
                    printJoin(empBlock, deptBlock, joinout);
                }
            }
        }
    }
*/

    return 0;
}
