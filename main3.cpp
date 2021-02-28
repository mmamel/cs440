#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;

struct EmpBlock {
    int eid;
    string ename;
    int age;
    double salary;
    int index_run;
    int offset;
    bool operator<(const EmpBlock& r) const
    {
        return eid <= r.eid;
    }
    bool operator>(const EmpBlock& r) const
    {
        return eid > r.eid;
    }
};
 
struct DeptBlock {
    int did;
    string dname;
    double budget;
    int managerid;
    int index_run;
    int offset;
    bool operator<(const DeptBlock& r) const
    {
        return did <= r.did;
    }
    bool operator>(const DeptBlock& r) const
    {
        return did > r.did;
    }
};


EmpBlock grabEmp(fstream &empin, int index_run) {
    string line, word;
    EmpBlock emp;
    // grab entire line
    if (getline(empin, line, '\n')) {
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
        emp.index_run = index_run;
        return emp;
    } else {
        emp.eid = -1;
        return emp;
    }
}


// Grab a single block from the dept.csv file, in theory if a block was larger than
// one tuple, this function would return an array of DeptBlocks and the entire if
// and else statement would be wrapped in a loop for x times based on block size
DeptBlock grabDept(fstream &deptin, int index_run) {
    string line, word;
    DeptBlock dept;
    if (getline(deptin, line, '\n')) {
        stringstream s(line);
        getline(s, word,',');
        dept.did = stoi(word);
        getline(s, word, ',');
        dept.dname = word;
        getline(s, word, ',');
        dept.budget = stod(word);
        getline(s, word, ',');
        dept.managerid = stoi(word);
        dept.index_run = index_run;

        return dept;
    } else {
        dept.did = -1;
        return dept;
    }
}

void grabEmpRun(fstream &fp, vector<EmpBlock> &vect, bool &outer_flag, int index_run){
    bool flag = true;
    int counter = 0;
    while (flag) {
        // FOR BLOCK IN RELATION EMP

        // grabs a block
        EmpBlock empBlock = grabEmp(fp, index_run);
        // checks if filestream is empty
        if (empBlock.eid == -1) {
            flag = false;
                outer_flag = false;
        } else {
                vect.push_back(empBlock);
                counter++;
            }
        bool iflag = true;
        // opens new filestream for dept relation (needs to read in a new one each time a new emp block is seen)
        if (counter == 11){
            flag = false;
        }
    }
}
void grabDeptRun(fstream &fp, vector<DeptBlock> &vect, bool &outer_flag, int index_run){
    bool flag = true;
    int counter = 0;
    while (flag) {
        // FOR BLOCK IN RELATION EMP

        // grabs a block
        DeptBlock deptBlock = grabDept(fp, index_run);
        // checks if filestream is empty
        if (deptBlock.did == -1) {
            flag = false;
                outer_flag = false;
        } else {
                vect.push_back(deptBlock);
                counter++;
            }
        bool iflag = true;
        // opens new filestream for dept relation (needs to read in a new one each time a new emp block is seen)
        if (counter == 11){
            flag = false;
        }
    }
}


void writeEmpRun(vector<EmpBlock> &vect, string runName, int index){
	fstream runs;
	runName += to_string(index);
    runs.open(runName, ios::out | ios::app);
    for (int i =0;i< vect.size();i++){
        runs << vect.at(i).eid  << "," << vect.at(i).ename << "," <<  vect.at(i).age << "," <<  vect.at(i).salary << "," << vect.at(i).index_run << "," << vect.at(i).offset << endl;
    }
    runs.close();
}
void writeDeptRun(vector<DeptBlock> &vect, string runName, int index){
	fstream runs;
	runName += to_string(index);
    runs.open(runName, ios::out | ios::app);
    for (int i =0;i< vect.size();i++){
        runs << vect.at(i).did  << "," << vect.at(i).dname << "," <<  vect.at(i).budget << "," <<  vect.at(i).managerid << vect.at(i).index_run << "," << vect.at(i).offset << endl;
    }
    runs.close();
}
EmpBlock grabEmpBlock(fstream &run, int offset){
    string line, word;
    EmpBlock emp;
    int lineNumber = 0;
    while(getline(run, line, '\n')){
        if (lineNumber == offset){
            stringstream s(line);
            getline(s, word, ',');
            emp.eid = stoi(word);
            getline(s, word, ',');
            emp.ename = word;
            getline(s, word, ',');
            emp.age = stoi(word);
            getline(s, word, ',');
            emp.salary = stod(word);
            getline(s, word, ',');
            emp.index_run = stod(word);
            getline(s, word, ',');
            emp.offset = stod(word); // set based on sorted run later
        
            return emp;
 
        }
        lineNumber++;
    }
}
 
DeptBlock grabDeptBlock(fstream &run, int offset){
    string line, word;
    DeptBlock dept;
    int lineNumber = 0;
    while(getline(run, line, '\n')){
        if (lineNumber == offset){
            // cout << "line: " << line << endl;
 
            stringstream s(line);
            getline(s, word, ',');
            dept.did = stoi(word);
            getline(s, word, ',');
            dept.dname = word;
            getline(s, word, ',');
            dept.budget = stoi(word);
            getline(s, word, ',');
            dept.managerid = stod(word);
            getline(s, word, ',');
            dept.index_run = stod(word);
            getline(s, word, ',');
            dept.offset = stod(word); // set based on sorted run later
        
            return dept;
 
        }
        lineNumber++;
    }
}

void initMerge(int empRunCt, int deptRunCt, vector<EmpBlock> &empRun, vector<DeptBlock> &deptRun){
    for(int i=0; i<empRunCt;i++){
        string name = "EmpRun";
        name += to_string(i);
        fstream fp;
        fp.open(name, ios::in);
        EmpBlock empBlock;
        empBlock = grabEmpBlock(fp,0);
        empRun.push_back(empBlock);
    }
    for(int i=0; i<deptRunCt;i++){
        string name = "DeptRun";
        name += to_string(i);
        fstream fp;
        fp.open(name, ios::in);
        DeptBlock deptBlock;
        deptBlock = grabDeptBlock(fp,0);
        deptRun.push_back(deptBlock);
    }
}

//pops and adds
//which 1 means emprun
//which 2 means dept run
void merge(int which, vector<EmpBlock> &empRun, vector<DeptBlock> &deptRun){
    if(which == 0){
        int index_run;
        int offset;
        index_run = empRun.at(0).index_run;
        offset = empRun.at(0).offset;
        fstream fp;
        string name = "EmpRun";
        name += to_string(index_run);
        empRun.erase(empRun.begin());
        fp.open(name, ios::in);
        EmpBlock empBlock;
        empBlock = grabEmpBlock(fp, offset+1);
        empRun.push_back(empBlock);
    }
    else{
        int index_run;
        int offset;
        index_run = deptRun.at(0).index_run;
        offset = deptRun.at(0).offset;
        fstream fp;
        string name = "DeptRun";
        name += to_string(index_run);
        deptRun.erase(deptRun.begin());
        fp.open(name, ios::in);
        DeptBlock deptBlock;
        deptBlock = grabDeptBlock(fp, offset+1);
        deptRun.push_back(deptBlock);
    }
}

int main() {
    // open file streams to read and write
    fstream empin;
    fstream deptin;
    fstream joinout;

    empin.open("Emp.csv", ios::in);
    deptin.open("Dept.csv", ios::in);
    joinout.open("Join.csv", ios::out | ios::app);
    // flags check when relations are done being read
    bool flag = true;


    vector<EmpBlock> empRun;
    vector<DeptBlock> deptRun;
    bool outer_flag = true;

    // grab emp records and put into runs
    int empRunCt = 0;
    while (outer_flag == true ) {
        grabEmpRun(empin, empRun, outer_flag, empRunCt);
        sort(empRun.begin(), empRun.end());
        for(int i=0;i<empRun.size();i++){
            empRun.at(i).index_run = empRunCt;
            empRun.at(i).offset = i;
            cout << empRun.at(i).eid << " ";
        }
            cout << endl;

        
        writeEmpRun(empRun, "EmpRun", empRunCt);
        empRun.clear();
        empRunCt++;
    }
    //grab dept records and put into runs
    outer_flag = true;
    int deptRunCt=0;
    while (outer_flag == true ) {
        grabDeptRun(deptin, deptRun, outer_flag, deptRunCt);
        sort(deptRun.begin(), deptRun.end());
        for(int i=0;i<deptRun.size();i++){
            deptRun.at(i).index_run = deptRunCt;
            deptRun.at(i).offset = i;
            cout << deptRun.at(i).did << " ";
        }
            cout << endl;

        
        writeDeptRun(deptRun, "DeptRun", deptRunCt);
        deptRun.clear();
        deptRunCt++;
    }

    empin.close();
    deptin.close();

    empRun.clear();
    deptRun.clear();
    initMerge(empRunCt, deptRunCt, empRun, deptRun);
    cout << "empRun: ";
    for(int i=0;i<empRun.size();i++){
            cout << empRun.at(i).eid << " ";
        }
        cout << endl;
        cout << "deptRun: ";
    for(int i=0;i<deptRun.size();i++){
            cout << deptRun.at(i).did << " ";
        }
        cout << endl;
    merge(0,empRun, deptRun);
    merge(1, empRun, deptRun);
    cout << "empRun: ";
    for(int i=0;i<empRun.size();i++){
            cout << empRun.at(i).eid << " ";
        }
        cout << endl;
        cout << "deptRun: ";
    for(int i=0;i<deptRun.size();i++){
            cout << deptRun.at(i).did << " ";
        }
        cout << endl;

}
