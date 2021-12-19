#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define DATA_FILE "data.csv"
using namespace std;

struct Course
{
    // int id;
    string name;
    // int credit;
    // int hours;
    // int grade;
};
struct Student
{
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
};

Student generateNewStudent(int id=-1){
    Student s;
    if(id != -1){
        s.id = id;
    }else{
        cout << "Enter student id: ";
        cin >> s.id;
    }
    cout << "Enter student first name: ";
    cin >> s.fname;
    cout << "Enter student last name: ";
    cin >> s.lname;
    cout << "Enter student age: ";
    cin >> s.age;
    cout << "Enter student gpa: ";
    cin >> s.gpa;
    cout << "Enter student address: ";
    cin >> s.address;
    cout << "Enter student phone: ";
    cin >> s.phone;
    cout << "Enter student email: ";
    cin >> s.email;
    cout << "Enter student major: ";
    cin >> s.major;
    for (int i = 0; i < 6; i++)
    {
        cout << "Enter course name ("<<i+1<<"): ";
        cin >> s.courses[i].name;
    }
    return s;
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
string studentToString(Student s)
{
    stringstream ss;
    if(s.id == -1)
    {
        ss << "No student data to print" << endl;
        return ss.str();
    }
    ss << "Student id: " << s.id << endl;
    ss << "Student first name: " << s.fname << endl;
    ss << "Student last name: " << s.lname << endl;
    ss << "Student age: " << s.age << endl;
    ss << "Student gpa: " << s.gpa << endl;
    ss << "Student address: " << s.address << endl;
    ss << "Student phone: " << s.phone << endl;
    ss << "Student email: " << s.email << endl;
    ss << "Student major: " << s.major << endl;
    for (int i = 0; i < 6; i++)
    {
        ss << "Course name ("<<i+1<<"): " << s.courses[i].name << endl;
    }
    
    return ss.str();
}
Student stringstreamToStudent(stringstream& ss)
{
    Student s;
    string token;
    int i = 0;
    while (getline(ss, token, ','))
    {
        if (i == 0) s.id = stoi(token);
        else if (i == 1) s.fname = token;
        else if (i == 2) s.lname = token;
        else if (i == 3) s.age = stoi(token);
        else if (i == 4) s.gpa = stof(token);
        else if (i == 5) s.address = token;
        else if (i == 6) s.phone = token;
        else if (i == 7) s.email = token;
        else if (i == 8) s.major = token;
        else if (i > 8) s.courses[i - 9].name = token;
        i++;
    }
    return s;
}

class DataBase
{
    private:
    Student student;
    fstream dbFile;
    public:
    void addStudent(Student student)
    {
        dbFile.open(DATA_FILE, ios::out | ios::app);
        dbFile << studentToStringstream(student).str() << endl;
        dbFile.close();
    }
    Student findStudent(int id)
    {
        Student s;
        dbFile.open(DATA_FILE, ios::in);
        string line;
        while (getline(dbFile, line))
        {
            stringstream ss(line);
            s=stringstreamToStudent(ss);
            if(s.id == id)
            {
                dbFile.close();
                return s;
            }
        }
        dbFile.close();
    }
    void removeStudent(int id){
        dbFile.open(DATA_FILE, ios::in);
        fstream tempFile;
        tempFile.open("temp.csv", ios::out| ios::app);
        string line;
        while (getline(dbFile, line))
        {
            stringstream ss(line);
            Student s = stringstreamToStudent(ss);
            if(s.id != id){
                tempFile << studentToStringstream(s).str() << endl;
            }
        }
        dbFile.close();
        tempFile.close();
        remove(DATA_FILE);
        rename("temp.csv", DATA_FILE);
    }
};

int main(int argc, char *argv[])
{
    while (true)
    {
        cout << "1: Add student" << endl;
        cout << "2: Find student" << endl;
        cout << "3: Update student" << endl;
        cout << "4: Delete student" << endl;
        cout << "0: Exit" << endl;
        cout << "Enter your choice: ";

        DataBase db;
        int id;
        int choice;
        cin >> choice;
        
        if(choice == 1) // add new student
        {
            db.addStudent(generateNewStudent());
        }
        else if(choice == 2) // find a student
        {
            cout << "Enter student id: ";
            cin >> id;
            cout<<studentToString(db.findStudent(id));
        }
        else if(choice == 3) // remove a student
        {
            int id;
            cout << "Enter student id to update: ";
            cin >> id;
            Student oldStudent = db.findStudent(id);
            db.removeStudent(id);
            // add new student
            cout << "Enter new student info: " << endl;
            db.addStudent(generateNewStudent(id));
        }
        else if(choice == 4) // delete a student
        {
            int id;
            cout << "Enter student id to delete: ";
            cin >> id;
            db.removeStudent(id);
        }
        else if(choice == 0) exit(0);
        else cout << "Invalid choice" << endl;
    }
    return 0;
}