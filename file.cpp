#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define DATA_FILE "data.csv"
using namespace std;
// Student create();
struct Course
{
    // int id;
    string name;
    // int credit;
    // int hours;
    // int grade;
};
class Student
// struct Student
{
    private:
    // static fstream DataFile;
    
    int id = -1;
    string fname;
    string lname;
    int age;
    float gpa;
    string address;
    string phone;
    string email;
    string major;
    Course courses[6];

    public:
    Student()
    {
        
    }
    ~Student()
    {
        
    }
    void getDataFromUser(){
        // get data from the user
        cout << "Enter student id: ";
        cin >> id;
        cout << "Enter student first name: ";
        cin >> fname;
        cout << "Enter student last name: ";
        cin >> lname;
        cout << "Enter student age: ";
        cin >> age;
        cout << "Enter student gpa: ";
        cin >> gpa;
        cout << "Enter student address: ";
        cin >> address;
        cout << "Enter student phone: ";
        cin >> phone;
        cout << "Enter student email: ";
        cin >> email;
        cout << "Enter student major: ";
        cin >> major;
        // get courses data from the user
        for (int i = 0; i < 6; i++)
        {
            cout << "Enter course name ("<<i+1<<"): ";
            cin >> courses[i].name;
        }
    }
    void print()
    {
        if(id == -1)
        {
            cout << "No student data to print" << endl;
            return;
        }
        cout << "Student id: " << id << endl;
        cout << "Student first name: " << fname << endl;
        cout << "Student last name: " << lname << endl;
        cout << "Student age: " << age << endl;
        cout << "Student gpa: " << gpa << endl;
        cout << "Student address: " << address << endl;
        cout << "Student phone: " << phone << endl;
        cout << "Student email: " << email << endl;
        cout << "Student major: " << major << endl;
        for (int i = 0; i < 6; i++)
        {
            cout << "Course name ("<<i+1<<"): " << courses[i].name << endl;
        }
    }

    void writeToFileAsCSV(fstream& outFile)
    {
        outFile << studentToStringstream(*this).str() << endl;
    }
    void readFromFileAsCSVByID(fstream& inFile, int id)
    {
        bool found = false;
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            *this=stringstreamToStudent(ss);
            
            if (this->id == id)
            {
                found = true;
                break;
            }
        }
        if (found)
        {
            cout << "Student found!" << endl;
            // print();
        }
        else
        {
            this->id = -1;
            cout << "Student not found!" << endl;
        }


    }
    Student stringstreamToStudent(stringstream& ss)
    {
        Student s;
        string token;
        int i = 0;
        while (getline(ss, token, ','))
        {
            if (i == 0)
            {
                s.id = stoi(token);
            }
            else if (i == 1)
            {
                s.fname = token;
            }
            else if (i == 2)
            {
                s.lname = token;
            }
            else if (i == 3)
            {
                s.age = stoi(token);
            }
            else if (i == 4)
            {
                s.gpa = stof(token);
            }
            else if (i == 5)
            {
                s.address = token;
            }
            else if (i == 6)
            {
                s.phone = token;
            }
            else if (i == 7)
            {
                s.email = token;
            }
            else if (i == 8)
            {
                s.major = token;
            }
            else if (i > 8)
            {
                s.courses[i - 9].name = token;
            }
            i++;
        }
        return s;
    }


    void removeFromCSVByID(fstream& File, int id){
        // create a temp file to store the output file
        fstream tempFile;
        tempFile.open("temp.csv", ios::out);
        // read from the file and write to the temp file
        string line;
        while (getline(File, line))
        {
            stringstream ss(line);
            Student s = stringstreamToStudent(ss);
            if(s.id != id){
                s.writeToFileAsCSV(tempFile);
            }
        }
        // close the file
        File.close();
        // close the temp file
        tempFile.close();
        // delete the original file
        remove(DATA_FILE);
        // rename the temp file to the original file
        rename("temp.csv", DATA_FILE);

        // if (found)
        // {
        //     cout << "Student found!" << endl;
        //     // print();
        // }
        // else
        // {
        //     this->id = -1;
        //     cout << "Student not found!" << endl;
        // }
    }

    void updateCSVByID(fstream& File, int id){
        readFromFileAsCSVByID(File, id);
        cout<< "Old student info:-" << endl;
        print();
        removeFromCSVByID(File, id);
        cout<< "Enter new student info:-" << endl;
        getDataFromUser();
        writeToFileAsCSV(File);
    
    }
    void updateCSVByIDOld(fstream& File, int id){
        


        // create a temp file to store the output file
        fstream tempFile;
        tempFile.open("temp.csv", ios::out);
        // read from the file and write to the temp file
        string line;
        while (getline(File, line))
        {
            stringstream ss(line);
            Student s = stringstreamToStudent(ss);
            if(s.id == !id){
                s.writeToFileAsCSV(tempFile);
            }else{
                cout<<"test";
            }
            
        }
        readFromFileAsCSVByID(File, id);
        cout << "Old student info: " << endl;
        print();

        cout << "Enter the new information: " << endl;
        Student newStudent;
        newStudent.getDataFromUser();
        newStudent.writeToFileAsCSV(tempFile);

        // close the file
        File.close();
        // close the temp file
        tempFile.close();
        // delete the original file
        remove(DATA_FILE);
        // rename the temp file to the original file
        rename("temp.csv", DATA_FILE);
    }
    stringstream studentToStringstream(Student s){
        stringstream ss;
        ss << s.id << "," << s.fname << "," << s.lname << "," << s.age << "," << s.gpa << "," << s.address << "," << s.phone << "," << s.email << "," << s.major << ",";
        for (int i = 0; i < 6; i++)
        {
            ss << s.courses[i].name << ",";
        }
        return ss;
    }
    



};

// class DataBase
// {
// private:
//     /* data */
// public:
//     DataBase(/* args */);
//     ~DataBase();
// };

// DataBase::DataBase(/* args */)
// {
// }

// DataBase::~DataBase()
// {
// }

int main(int argc, char *argv[])
{
    while (true)
    {
        
        // print menu to create, read, update, delete, and exit
        cout << "1: Create" << endl;
        cout << "2: Read" << endl;
        // cout << "3: Update" << endl;
        cout << "4: Delete" << endl;
        cout << "0: Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        
        if(choice == 1)
        {
            // create a new student
            fstream fdata;
            // opens an existing csv file or creates a new file.
            fdata.open(DATA_FILE, ios::out | ios::app);

            Student student;
            student.getDataFromUser();
            student.writeToFileAsCSV(fdata);
            // student.readFromFileAsCSVByID(fdata, 12345);
            // student.print();

        }
        else if(choice == 2)
        {
            // read a student
            fstream fdata;
            fdata.open(DATA_FILE, ios::in);
            Student student;
            int id;
            cout << "Enter student id: ";
            cin >> id;
            student.readFromFileAsCSVByID(fdata, id);
            student.print();



        }
        else if(choice == 3)
        {
            cout << "Sorry, this feature is not available yet." << endl;
            // // update
            // fstream fdata;
            // fdata.open(DATA_FILE, ios::in | ios::out);
            // Student student;
            // int id;
            // cout << "Enter student id: ";
            // cin >> id;
            // student.updateCSVByID(fdata, id);
            // student.print();


        }
        else if(choice == 4)
        {
            // delete
            fstream fdata;
            fdata.open(DATA_FILE, ios::in);
            Student student;
            int id;
            cout << "Enter student id to delete: ";
            cin >> id;
            student.removeFromCSVByID(fdata, id);
        }
        else if(choice == 0) exit(0);
        else cout << "Invalid choice" << endl;
    }

    return 0;
}

