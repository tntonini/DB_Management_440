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
bool compareEmp(const EmpBlock &lhs, const EmpBlock &rhs)
{
	return lhs.eid < rhs.eid;
}

bool compareDept(DeptBlock const &lhs, DeptBlock const &rhs)
{
	return lhs.did < rhs.did;
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

	joinout << "hi hi hi" << endl;

	//Sort emp block
	sort(emp.begin(), emp.end(), compareEmp);
	for(int i = 0; i < 30; i++){
		cout << endl;
		cout << emp[i].eid << emp[i].ename << emp[i].age << emp[i].salary;

	}

	//Sort dept block
	sort(dept.begin(), dept.end(), compareDept);

	int mark = 0, r = 0, s = 0, count = 0;
	do{
		if (!mark){
			for(int i = 0; i < 30; i++){
				if(emp[r].eid < dept[s].managerid){
					//while(emp[i].eid < dept[j].managerid){
					// cout << "in first loop" << endl;
					// cout << "  j " << j << " " << dept[j].managerid << endl;;
            		cout << emp[r].eid << emp[r].ename << emp[r].age << emp[r].salary << endl;
                    r++;
                }

                if (emp[r].eid == dept[s].managerid)
                    {
                        cout << "equal in first" << endl;
                        break;
                    }
			}
            cout << "after for loop" << endl;

			for(int i = 0; i < 15; i++){
                    if (emp[r].eid == dept[s].managerid)
                    {
                        cout << "equal in 2nd" << endl;
                        break;
                    }

				if(emp[r].eid > dept[s].managerid){
					//	while(emp[i].eid > dept[j].managerid){
					// cout << "s " << s << endl;
					cout << "in second loop" << endl;
                    s++;
				}


			}
			mark = s;
		}
		if(emp[r].eid == dept[s].managerid){
			cout << " r = s" << endl;

			joinout << "hi" << endl;
            cout << emp[r].eid << ", " << emp[r].ename << ", " << emp[r].age << ", "
			<< emp[r].salary << ", " << dept[s].did << ", " << dept[s].dname << ", "
			<< dept[s].budget << "\n";

            joinout << "helloooo" << endl;
			// joinout << emp[r].eid << ", " << emp[r].ename << ", " << emp[r].age << ", "
			// 	<< emp[r].salary << ", " << dept[s].did << ", " << dept[s].dname << ", "
			// 	<< dept[s].budget << "\n";

			s++;
			count++;
		}
		else{
			s = mark;
			r++;
			mark = 0;
		}
	}while(count < 30);


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
			vector<EmpBlock> emp;
			vector<DeptBlock> dept;

			string line, word;


			if (!empin || !deptin)
			{
				cerr << "File can't be opened! " << endl;
				exit(1);
			}

			//Read in from emp file
			while(getline(empin, line) && !line.empty()){
				emp.push_back(EmpBlock());

				// turn line into a stream
				stringstream s(line);
				// gets everything in stream up to comma
				getline(s, word,',');
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
			while(getline(deptin, line) && !line.empty()){
				dept.push_back(DeptBlock());

				// turn line into a stream
				stringstream s(line);
				// gets everything in stream up to comma
				getline(s, word,',');
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
