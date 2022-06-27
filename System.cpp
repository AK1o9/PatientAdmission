#include <iostream>
#include <iomanip>
#include <string>  
#include <sstream>
#include <cstring> 
#include <stdlib.h>
#include <cstdlib>
#include <ctime> 
#pragma warning (disable: 4996)
using namespace std;

//Patient Queue list
struct Patient {
    int PID;
    string FName;
    string LName;
    int Age;
    string Gender;
    string phone;
    string address;
    string SicknessDescription;
    string visitTimeStamp;
    string DoctorName;
    string MedicineInfo;

    Patient* next;
};
Patient* Head = NULL;

//Patient Visit History list
struct VisitHistory {
    int PID;
    string FName;
    string LName;
    int Age;
    string Gender;
    string phone;
    string address;
    string SicknessDescription;
    string visitTimeStamp;
    string DoctorName;
    string MedicineInfo;

    VisitHistory* history_next;
};
VisitHistory* history_head = NULL;

//Nasser
void NursesMenu();
void DoctorMenu();
int main();
void InsertArbitraryPatientWaitingList(int PID, string  FName, string LName, string Gender, string address, string visitTimeStamp, int Age, string phone, int nodePostion);
void InsertPatientToVisitHistoryList(int PID, string  FName, string LName, string Gender, string address, string visitTimeStamp, int Age, string phone);
void AddPatientToQueue();
void ViewWaitingList(Patient* Head);
void CallPatientToBeTreated(Patient* Head);
void DeletePatientFromWaitingList(Patient* position);

//Sarah
void SearchPatientFirstName();
void SearchPatientByID();
void SearchPatientFromWaitingList(Patient* Head);
void sortWaitingListByTime(struct Patient** head_ref, struct Patient* new_node);
void insertionSortWaitingListByTime(struct Patient** head_ref);
void ViewWaitingListPageByPage();
Patient* SearchPaitentID(int id, Patient* Head);

//Ahmed
void ViewHistoryList(VisitHistory* history_head);
void SearchPatientFromVisitHistory(VisitHistory* history_head);
void sortHistoryListByTime_DESC(struct VisitHistory** head_ref, struct VisitHistory* new_node);
void insertionSortVisitHistoryListByTime(struct VisitHistory** head_ref);
void UpdatePatientRecord(VisitHistory* history_head);

//Global value declarations:
int nodePosition = 0;
int PID = 1;
int listSize = 0;
int history_listSize = 0;
int MenuVisits = 0; //Note: Counter for the amount of times the menu is visited.


void InsertArbitraryPatientWaitingList(int PID, string  FName, string LName, string Gender, string address, string visitTimeStamp, int Age, string phone, int nodePostion) {
    Patient* newNode = new Patient;
    //init the reocord info
    newNode->PID = PID;
    newNode->FName = FName;
    newNode->LName = LName;
    newNode->Gender = Gender;
    newNode->address = address;
    newNode->visitTimeStamp = visitTimeStamp;
    newNode->Age = Age;
    newNode->phone = phone;
    newNode->DoctorName = "";
    newNode->MedicineInfo = "";
    newNode->SicknessDescription = "";
    newNode->next = NULL;

    if (nodePosition > listSize)
    {
        nodePosition = listSize;
    }

    if (Head == NULL)
    {
        Head = newNode;
    }
    else if (nodePostion == 1)
    {
        newNode->next = Head;
        Head = newNode;
    }
    else
    {
        Patient* current = Head;
        Patient* previous = Head;
        current = Head->next;
        int i = 2;
        while (nodePostion != i && current != NULL)
        {
            previous = current;
            current = current->next;
            i++;
        }
        newNode->next = current;
        previous->next = newNode;
    }
}

void InsertPatientToVisitHistoryList(int PID, string  FName, string LName, string Gender, string address, string visitTimeStamp, int Age, string phone) {
    VisitHistory* newNode = new VisitHistory;
    //init the record info
    newNode->PID = PID;
    newNode->FName = FName;
    newNode->LName = LName;
    newNode->Gender = Gender;
    newNode->address = address;
    newNode->visitTimeStamp = visitTimeStamp;
    newNode->Age = Age;
    newNode->phone = phone;
    //will be null at the start
    newNode->DoctorName = "";
    newNode->MedicineInfo = "";
    newNode->SicknessDescription = "";
    newNode->history_next = NULL;;
    if (history_head == NULL) //insert at the beginning 
    {
        newNode->history_next = history_head;
        history_head = newNode;
    }
    else {
        VisitHistory* current = history_head;
        while (current->history_next != NULL)
        {
            current = current->history_next;
        }
        current->history_next = newNode;
    }
    history_listSize++;
}

void AddPatientToQueue() {
    char confirm;
    //patient info
    string FName, LName, Gender, address, visitTimeStamp = "", phone;
    int Age;

    getchar();//clear the cache
    cout << "\nEnter Patient First Name: "; getline(cin, FName, '\n');
    cout << "\nEnter Patient Last Name : "; getline(cin, LName, '\n');
    cout << "\nEnter Patient Gender [M/F/X]    : "; getline(cin, Gender, '\n');
    if (Gender!="M" && Gender!="m" && Gender != "Male" && Gender != "male" && Gender != "F" && Gender != "f" && Gender != "Female" && Gender != "female" && Gender != "X" && Gender != "x" && Gender != "Other")
    {
        cout << "\n<<Error: Invalid data detected!>>" << endl;
        cout << "- Please enter a valid gender next time." << endl;
        return;
    }
    cout << "\nEnter Patient Address    : "; getline(cin, address, '\n');
    cout << "\nEnter Patient Phone No  : "; getline(cin, phone, '\n');

    time_t result = time(nullptr);
    visitTimeStamp = asctime(localtime(&result));
    cout << "\nCurrent Time            : " << visitTimeStamp;
    cout << "\nEnter Patient Age       : "; cin >> Age;
    if (Age<0 || Age>150)   //Note (LOGIC): Age = 0 is valid for infants.
    {
        cout << "\n<<Error: Invalid data detected!>>" << endl;
        cout << "- Please enter a valid age next time." << endl;
        return;
    }
    cout << "\nEnter where you want to insert the record(Queue NO): "; cin >> nodePosition;
    cout << "\nWould you like to confirm the details (y,n): "; cin >> confirm;
    if (confirm == 'Y' || confirm == 'y')
    {
        //send the data to the insert function
        InsertArbitraryPatientWaitingList(PID, FName, LName, Gender, address, visitTimeStamp, Age, phone, nodePosition);
        listSize++;
        PID++;
        cout << "\nThe record has been added successfully !\n";
    }
    else {
        cout << "\nThe record cancelled !\n";
    }
}

void ViewWaitingList(Patient* Head) {
    Patient* current = Head;
    if (current == NULL || listSize == 0)
    {
        cout << "\nThere is no record yet, please add first !\n";
    }
    else
    {
        while (current != NULL)
        {
            cout << "\nPatient ID Number   : " << current->PID;
            cout << "\nPatient First Name  : " << current->FName;
            cout << "\nPatient Last Name   : " << current->LName;
            cout << "\nPatient Gender      : " << current->Gender;
            cout << "\nPatient Adress      : " << current->address;
            cout << "\nPatient visit Time  : " << current->visitTimeStamp;
            cout << "\nPatient Age         : " << current->Age;
            cout << "\nPatient Phone No    : " << current->phone;
            cout << "\n----------------->>><><><><<<------------------\n";
            current = current->next;
        }
    }
}

void CallPatientToBeTreated(Patient* Head) {
    Patient* current = Head;
    int toSearch, toDelete;
    bool flag = false;
    if (current == NULL)
    {
        cout << "\nThere is no record yet, please add first !\n";
    }
    else
    {
        cout << "Enter Patient ID to Call: ";
        cin >> toSearch;
        while (current != NULL)
        {
            if (toSearch == current->PID) {
                //update flag status
                flag = true;
                //display current patient to be treated
                cout << "\nThe current patient to be treated: \n";
                cout << "\nPatient ID Number   : " << current->PID;
                cout << "\nPatient First Name  : " << current->FName;
                cout << "\nPatient Last Name   : " << current->LName;
                cout << "\nPatient Gender      : " << current->Gender;
                cout << "\nPatient Adress      : " << current->address;
                cout << "\nPatient visit Time  : " << current->visitTimeStamp;
                cout << "\nPatient Age         : " << current->Age;
                cout << "\nPatient Phone No    : " << current->phone;
                cout << "\n----------------->>><><><><<<------------------\n";
                //adding the patient to the visit history list
                time_t result = time(nullptr);
                string visitDoctorTimeStamp = asctime(localtime(&result));
                InsertPatientToVisitHistoryList(current->PID, current->FName, current->LName,
                    current->Gender, current->address, visitDoctorTimeStamp, current->Age, current->phone);
                toDelete = current->PID;
            }
            current = current->next;
        }
        if (flag == false) {
            cout << "\nThe entered patient ID is not available, please try again !\n";
            return;
        }
        else {

            //removing the patient from the waiting list
            DeletePatientFromWaitingList(SearchPaitentID(toDelete, Head));
        }

    }
    return;
}

Patient* SearchPaitentID(int id, Patient* Head)
{
    Patient* current = Head;
    if (Head == NULL) {
        cout << "\nNo record added yet\n";
    }
    while (current != NULL) {
        if (current->PID == id) {
            return current;
        }
        else {
            current = current->next;
        }
    }
    return NULL;
}

void DeletePatientFromWaitingList(Patient* position) {

    if (position == NULL) {
        cout << "\nThe given ID is not found\n";
        return;
    }
    else if (position == Head) {
        Head = Head->next;
        delete position;
        listSize--;
        return;
    }
    else {
        Patient* current = Head;
        while (current != NULL) {
            if (current->next == position) {
                current->next = position->next;
                delete position;
                listSize--;
                return;
            }
            current = current->next;
        }
        return;
    }


}

void SearchPatientFirstName() {
    Patient* current = Head;
    string keyword;
    getchar();
    cout << "\nEnter the Patient's first name: ";
    getline(cin, keyword, '\n');
    if (current == NULL) {
        cout << "\nNo record added yet\n";
    }
    while (current != NULL)
    {
        if (keyword == current->FName)
        {
            cout << "\nThe following record has been found: \n";
            cout << "\nPatient ID Number   : " << current->PID;
            cout << "\nPatient First Name  : " << current->FName;
            cout << "\nPatient Last Name   : " << current->LName;
            cout << "\nPatient Gender      : " << current->Gender;
            cout << "\nPatient Adress      : " << current->address;
            cout << "\nPatient visit Time  : " << current->visitTimeStamp;
            cout << "\nPatient Age         : " << current->Age;
            cout << "\nPatient Phone No    : " << current->phone;
            cout << "\n----------------->>><><><><<<------------------\n";
        }
        current = current->next;
    }
}

void SearchPatientByID() {
    Patient* current = Head;
    int value;
    cout << "Enter the Patient's ID Number: ";
    cin >> value;
    if (current == NULL) {
        cout << "\nNo record added yet\n";
    }
    while (current != NULL)
    {
        if (value == current->PID) {
            cout << "\nThe following record has been found: \n";
            cout << "\nPatient ID Number   : " << current->PID;
            cout << "\nPatient First Name  : " << current->FName;
            cout << "\nPatient Last Name   : " << current->LName;
            cout << "\nPatient Gender      : " << current->Gender;
            cout << "\nPatient Adress      : " << current->address;
            cout << "\nPatient visit Time  : " << current->visitTimeStamp;
            cout << "\nPatient Age         : " << current->Age;
            cout << "\nPatient Phone No    : " << current->phone;
            cout << "\n----------------->>><><><><<<------------------\n";
        }
        current = current->next;
    }
}

void SearchPatientFromWaitingList(Patient* Head) {
    system("cls");
    char select;
    do
    {
        cout << "\nPlease enter: ";
        cout << "\n'1' for searching by Patient first name ";
        cout << "\n'2' for searching by Patient ID ";
        cout << "\n'3' to return to main menu";
        cout << "\nEnter your option: ";
        cin >> select;
        switch (select)
        {
        case '1':
            SearchPatientFirstName();
            break;
        case '2':
            SearchPatientByID();
            break;
        case '3':
            NursesMenu();
            break;
        default:
            cout << "\nWrong option, retry again!\n";
            break;
        }
        system("pause");
        system("cls");

    } while (select != '3');
}

void sortWaitingListByTime(struct Patient** head_ref, struct Patient* new_node)
{
    struct Patient* current;

    if (*head_ref == NULL || (*head_ref)->visitTimeStamp >= new_node->visitTimeStamp)
    {
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->next != NULL && current->next->visitTimeStamp < new_node->visitTimeStamp)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void insertionSortWaitingListByTime(struct Patient** head_ref)
{
    struct Patient* sorted = NULL;

    struct Patient* current = *head_ref;

    while (current != NULL)
    {
        //store 'next' for next iteration
        struct Patient* next = current->next;

        sortWaitingListByTime(&sorted, current);

        current = next;
    }

    *head_ref = sorted;

}

void ViewWaitingListPageByPage() {
    if (Head == NULL)
    {
        return;
    }
    Patient* current = Head;
    Patient* prev = Head;
    int current_position = 1, decision = 1;
    system("cls");
    while (decision != 0)
    {
        cout << "\nPatient ID Number   : " << current->PID;
        cout << "\nPatient First Name  : " << current->FName;
        cout << "\nPatient Last Name   : " << current->LName;
        cout << "\nPatient Gender      : " << current->Gender;
        cout << "\nPatient Adress      : " << current->address;
        cout << "\nPatient visit Time  : " << current->visitTimeStamp;
        cout << "\nPatient Age         : " << current->Age;
        cout << "\nPatient Phone No    : " << current->phone;
        cout << "\n\n=========================================================================\n";
        cout << "1. Previous Patient\t 2.Next Patient\t 0.Exit";
        cout << "\n=========================================================================\n";
        cout << "\nSelect your next option: ";
        cin >> decision;

        //Next Patient
        if (decision == 2 && current->next != NULL)
        {
            current = current->next;
            current_position++;
        }
        //Previous Patient
        else if (decision == 1 && (current != Head || current_position != 1))
        {
            prev = Head;
            for (int i = 1; i < current_position - 1; i++)
            {
                prev = prev->next;
            }
            current = prev;
            current_position--;
        }
        else if (decision == 0)
        {
            return;
        }
        else if (decision != 1 && decision != 2 && decision != 0)
        {
            cout << "Invalid input! Retry again." << endl;
            system("pause");
        }
        else
        {
            cin.ignore();
            cout << "There are no more records available for display." << endl;
            system("pause");
        }
        system("cls");
    }
}

void ViewHistoryList(VisitHistory* history_head) {
    VisitHistory* current = history_head;
    if (current == NULL)
    {
        cout << "\nThere is no record yet, please add first !\n";
    }
    else
    {
        while (current != NULL)
        {
            cout << "\nPatient ID Number   : " << current->PID;
            cout << "\nPatient First Name  : " << current->FName;
            cout << "\nPatient Last Name   : " << current->LName;
            cout << "\nPatient Gender      : " << current->Gender;
            cout << "\nPatient Address     : " << current->address;
            cout << "\nPatient Visit Time  : " << current->visitTimeStamp;
            cout << "\nPatient Age         : " << current->Age;
            cout << "\nPatient Phone No    : " << current->phone;
            cout << "\nDoctor's Name       : " << current->DoctorName;
            cout << "\nMedicine Information: " << current->MedicineInfo;
            cout << "\nSickness Description: " << current->SicknessDescription;
            cout << "\n----------------->>><><><><<<------------------\n";
            current = current->history_next;
        }
    }
}

void SearchPatientFromVisitHistory(VisitHistory* history_head) {
    VisitHistory* current;
    //situation 1: directly check whether the list is empty or not
    if (history_head == NULL)
    {
        cout << "\nList is empty! Please retry again after calling in some patients!" << endl;
        return;
    }

    //situation 2: the list is not empty
    current = history_head;
    string pat_fname;
    string sickness;

    int selection;
    bool matches_found = false;

    cout << "\n\n1.To search for a patient by their first name";
    cout << "\n2.To search for a patient by their sickness' description";
    cout << "\n\nYour option: ";
    cin >> selection;
    cin.ignore();

    //Search by first name
    if (selection==1)
    {
        cout << "Please enter the first name of the patient(s)/record(s) you'd like to view: ";
        getline(cin, pat_fname);

        while (current != NULL)
        {
            if (current->FName == pat_fname) {
                cout << "\nPatient ID Number   : " << current->PID;
                cout << "\nPatient First Name  : " << current->FName;
                cout << "\nPatient Last Name   : " << current->LName;
                cout << "\nPatient Gender      : " << current->Gender;
                cout << "\nPatient Address     : " << current->address;
                cout << "\nPatient Visit Time  : " << current->visitTimeStamp;
                cout << "\nPatient Age         : " << current->Age;
                cout << "\nPatient Phone No    : " << current->phone;
                cout << "\nDoctor's Name       : " << current->DoctorName;
                cout << "\nMedicine Information: " << current->MedicineInfo;
                cout << "\nSickness Description: " << current->SicknessDescription;
                cout << "\n----------------->>><><><><<<------------------\n";
                if (matches_found == false)
                {
                    matches_found = true;
                }
            }
            current = current->history_next;
        }
    }

    //Search by sickness
    else if (selection == 2)
    {
        cout << "Please enter the sickness description of the record(s) you'd like to view: ";
        getline(cin, sickness);
        while (current != NULL)
        {
            if (current->SicknessDescription == sickness) {
                cout << "\nPatient ID Number   : " << current->PID;
                cout << "\nPatient First Name  : " << current->FName;
                cout << "\nPatient Last Name   : " << current->LName;
                cout << "\nPatient Gender      : " << current->Gender;
                cout << "\nPatient Address     : " << current->address;
                cout << "\nPatient Visit Time  : " << current->visitTimeStamp;
                cout << "\nPatient Age         : " << current->Age;
                cout << "\nPatient Phone No    : " << current->phone;
                cout << "\nDoctor's Name       : " << current->DoctorName;
                cout << "\nMedicine Information: " << current->MedicineInfo;
                cout << "\nSickness Description: " << current->SicknessDescription;
                cout << "\n----------------->>><><><><<<------------------\n";
                if (matches_found == false)
                {
                    matches_found = true;
                }
            }
            current = current->history_next;
        }
    }
    //Invalid input
    else {
        cout << "Error: Invalid input! Retry again." << endl;
        return;
    }

    //If record(s) doesn't doesn't exist.
    if (matches_found == false)
    {
        cout << "Sorry, no such patient exists within our records! Retry again." << endl;
    }

}

void UpdatePatientRecord(VisitHistory* history_head) {
    VisitHistory* current;
    //situation 1: directly check whether the list is empty or not
    if (history_head == NULL)
    {
        cout << "List is empty! Please retry again after calling in some patients!" << endl;
        return;
    }

    //situation 2: the list is not empty
    current = history_head;
    int pat_id;

    while (current != NULL)
    {
        cout << "\nPatient ID Number   : " << current->PID;
        cout << "\nPatient First Name  : " << current->FName;
        cout << "\nPatient Last Name   : " << current->LName;
        cout << "\nPatient Gender      : " << current->Gender;
        cout << "\nPatient Adress      : " << current->address;
        cout << "\nPatient visit Time  : " << current->visitTimeStamp;
        cout << "\nPatient Age         : " << current->Age;
        cout << "\nPatient Phone No    : " << current->phone;
        cout << "\nDoctor's Name       : " << current->DoctorName;
        cout << "\nMedicine Information: " << current->MedicineInfo;
        cout << "\nSickness Description: " << current->SicknessDescription;
        cout << "\n----------------->>><><><><<<------------------\n";
        current = current->history_next;
    }

    current = history_head;
    cout << "\n\nPlease enter the Patient ID of the record you'd like to edit: ";
    cin >> pat_id;
    cin.ignore();

    while (current != NULL)
    {
        if (current->PID == pat_id) {
            system("cls");
            cout << "<< PATIENT FOUND >>" <<endl;
            cout << "\nEnter the new details as follows: " << endl;
            
            string newVisitTimeStamp = "";
            time_t result = time(nullptr);
            newVisitTimeStamp = asctime(localtime(&result));
            cout << "1. New Visit Time & Date: " << newVisitTimeStamp; //new current time
            current->visitTimeStamp = newVisitTimeStamp;

            cout << "2. Doctor's Name:  " ;
            getline(cin, current->DoctorName);            

            cout << "3. Medicine Information:  ";
            getline(cin, current->MedicineInfo);

            cout << "4. Sickness Description:   ";
            getline(cin, current->SicknessDescription);            

            cout << "\nPatient "<< current->PID <<"'s records have been updated succesfully!" << endl;
            return;
        }
        current = current->history_next;
    }

    cout << "Sorry, that patient doesn't exist within our records! Retry again." << endl;
}

void sortHistoryListByTime_DESC(struct VisitHistory** head_ref, struct VisitHistory* new_node)
{
    struct VisitHistory* current;

    if (*head_ref == NULL || (*head_ref)->visitTimeStamp <= new_node->visitTimeStamp)
    {
        new_node->history_next = *head_ref;
        *head_ref = new_node;
    }
    else
    {
        current = *head_ref;
        while (current->history_next != NULL && current->history_next->visitTimeStamp > new_node->visitTimeStamp)
        {
            current = current->history_next;
        }
        new_node->history_next = current->history_next;
        current->history_next = new_node;
    }
}

void insertionSortVisitHistoryListByTime(struct VisitHistory** head_ref)
{
    struct VisitHistory* sorted = NULL;

    struct VisitHistory* current = *head_ref;

    while (current != NULL)
    {
        //store 'next' for next iteration
        struct VisitHistory* next = current->history_next;

        sortHistoryListByTime_DESC(&sorted, current);

        current = next;
    }

    *head_ref = sorted;
}

void ViewHistoryListPageByPage()
{
    if (history_head == NULL)
    {
        return;
    }
    VisitHistory* current = history_head;
    VisitHistory* prev;
    int current_position = 1, decision = 1;
    system("cls");
    while (decision != 0)
    {
        cout << "\nPatient ID Number   : " << current->PID;
        cout << "\nPatient First Name  : " << current->FName;
        cout << "\nPatient Last Name   : " << current->LName;
        cout << "\nPatient Gender      : " << current->Gender;
        cout << "\nPatient Address     : " << current->address;
        cout << "\nPatient Visit Time  : " << current->visitTimeStamp;
        cout << "\nPatient Age         : " << current->Age;
        cout << "\nPatient Phone No    : " << current->phone;
        cout << "\nDoctor's Name       : " << current->DoctorName;
        cout << "\nMedicine Information: " << current->MedicineInfo;
        cout << "\nSickness Description: " << current->SicknessDescription;
        cout << "\n=========================================================================\n";
        cout << "1. Previous Patient\t 2.Next Patient\t 0.Exit";
        cout << "\n=========================================================================\n";
        cout << "Select your next option: ";
        cin >> decision;

        //Next page
        if (decision == 2 && current->history_next != NULL)
        {
            current = current->history_next;
            current_position++;
        }
        //Previous page
        else if (decision == 1 && (current != history_head || current_position != 1))
        {
            prev = history_head;
            for (int i = 1; i < current_position-1; i++)
            {
                prev = prev->history_next;
            }
            current = prev;
            current_position--;
            
        }
        else if (decision == 0)
        {
            return;
        }
        else if (decision != 1 && decision != 2 && decision != 0)
        {
            cout << "Invalid input! Retry again." << endl;
            system("pause");
        }
        else
        {
            cin.ignore();
            cout << "There are no more records available for display." << endl;
            system("pause");
        }
        system("cls");
    }
}


void AddSampleData() 
{
    //Predefined data records:

    //1. Waiting List Data
    string PredefinedData[5][5] = {
    {"Ahmed", "Ali", "Male", "Bukit Jalil", "0123123123"},
    {"Nasser", "Yousif", "Male", "Bandar Sunway","0123412341"},
    {"Sarah", "Shariff", "Female", "Cheras", "0123451234"},
    {"Alyssa", "Thornberry", "Female", "Johor", "0123456123"},
    {"Allen", "Lee", "Male", "Bukit Bintang", "0123456712"}
    };
    int NumericalData[5][3] = { //Consisting of Patient ID number, age and node position. This integer array acts as a continuation to the above array.
    {1,19,1},
    {2,19,2},
    {3,19,3},
    {4,23,4},
    {5,41,5}
    };

    //2. Visit History Data
    string PredefinedData2[5][5] = {
    {"Saad", "Baha", "Male", "Bukit Jalil", "0123123123"},
    {"Mansour", "Hisham", "Male", "Bandar Sunway","0123412341"},
    {"Zainab", "Bakry", "Female", "Cheras", "0123451234"},
    {"Amanda", "Thornberry", "Female", "Johor", "0123456123"},
    {"Bruce", "Lee", "Male", "Bukit Bintang", "0123456712"}
    };
    int NumericalData2[5][2] = { //Consisting of Patient ID number & age. This integer array acts as a continuation to the above array.
    {6,19},
    {7,19},
    {8,19},
    {9,23},
    {10,41}
    };

    //Visit date & time
    string SampleVisitTime = "";
    time_t result = time(nullptr);
    SampleVisitTime = asctime(localtime(&result));

    if (listSize == 0 && history_listSize == 0)
    {
        InsertArbitraryPatientWaitingList(NumericalData[0][0], PredefinedData[0][0], PredefinedData[0][1], PredefinedData[0][2], PredefinedData[0][3], SampleVisitTime, NumericalData[0][1], PredefinedData[0][4], NumericalData[0][2]);
        listSize++;
        PID++;
        InsertArbitraryPatientWaitingList(NumericalData[1][0], PredefinedData[1][0], PredefinedData[1][1], PredefinedData[1][2], PredefinedData[1][3], SampleVisitTime, NumericalData[1][1], PredefinedData[1][4], NumericalData[1][2]);
        listSize++;
        PID++;
        InsertArbitraryPatientWaitingList(NumericalData[2][0], PredefinedData[2][0], PredefinedData[2][1], PredefinedData[2][2], PredefinedData[2][3], SampleVisitTime, NumericalData[2][1], PredefinedData[2][4], NumericalData[2][2]);
        listSize++;
        PID++;
        InsertArbitraryPatientWaitingList(NumericalData[3][0], PredefinedData[3][0], PredefinedData[3][1], PredefinedData[3][2], PredefinedData[3][3], SampleVisitTime, NumericalData[3][1], PredefinedData[3][4], NumericalData[3][2]);
        listSize++;
        PID++;
        InsertArbitraryPatientWaitingList(NumericalData[4][0], PredefinedData[4][0], PredefinedData[4][1], PredefinedData[4][2], PredefinedData[4][3], SampleVisitTime, NumericalData[4][1], PredefinedData[4][4], NumericalData[4][2]);
        listSize++;
        PID++;
   
        InsertPatientToVisitHistoryList(NumericalData2[0][0], PredefinedData2[0][0], PredefinedData2[0][1], PredefinedData2[0][2], PredefinedData2[0][3], SampleVisitTime, NumericalData2[0][1], PredefinedData2[0][4]);
        history_listSize++;
        PID++;
        InsertPatientToVisitHistoryList(NumericalData2[1][0], PredefinedData2[1][0], PredefinedData2[1][1], PredefinedData2[1][2], PredefinedData2[1][3], SampleVisitTime, NumericalData2[1][1], PredefinedData2[1][4]);
        history_listSize++;
        PID++;
        InsertPatientToVisitHistoryList(NumericalData2[2][0], PredefinedData2[2][0], PredefinedData2[2][1], PredefinedData2[2][2], PredefinedData2[2][3], SampleVisitTime, NumericalData2[2][1], PredefinedData2[2][4]);
        history_listSize++;
        PID++;
        InsertPatientToVisitHistoryList(NumericalData2[3][0], PredefinedData2[3][0], PredefinedData2[3][1], PredefinedData2[3][2], PredefinedData2[3][3], SampleVisitTime, NumericalData2[3][1], PredefinedData2[3][4]);
        history_listSize++;
        PID++;
        InsertPatientToVisitHistoryList(NumericalData2[4][0], PredefinedData2[4][0], PredefinedData2[4][1], PredefinedData2[4][2], PredefinedData2[4][3], SampleVisitTime, NumericalData2[4][1], PredefinedData2[4][4]);
        history_listSize++;
        PID++;

    }
}


//User Menus
void NursesMenu() {
    system("cls");
    char choice;
    do
    {
        cout << "\n-----------> Welcome to Nurse Page <-------------\n\n";
        cout << "\n1. Add a new patient on the waiting list.";
        cout << "\n2. View all the patients on the original waiting list.";
        cout << "\n3. Calling the Patient to be treated.";
        cout << "\n4. Search patient from the waiting list.";
        cout << "\n5. Sort the waiting list by patient's current visit time in ascending order";
        cout << "\n6. Logout. ";
        cout << "\nEnter your option: ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            AddPatientToQueue();
            break;
        case '2':
            ViewWaitingList(Head);
            break;
        case '3':
            ViewWaitingList(Head);
            //choose the patient to be treated
            CallPatientToBeTreated(Head);
            break;
        case '4':
            SearchPatientFromWaitingList(Head);
            break;
        case '5':
            insertionSortWaitingListByTime(&Head);
            ViewWaitingListPageByPage();
            break;
        case '6':
            main();
            break;
        default:
            cout << "\nWrong option, retry again!\n";
            break;
        }
        system("pause");
        system("cls");

    } while (choice != '6');
}

void DoctorMenu() {
    system("cls");
    char choice;
    do
    {
        cout << "\n-----------> Welcome to Doctor Page <-------------\n\n";
        cout << "\n1. View all patients on the original waiting list";
        cout << "\n2. Search and modify patient record from the patient's visit history";
        cout << "\n3. Sort and display all records from the patient's visit history list in descending order (One by One)";
        cout << "\n4. Search patients from the patient's visit history list";
        cout << "\n5. View all patients on the patient's visit history list (All)";
        cout << "\n6. Logout. ";
        cout << "\nEnter your option: ";
        cin >> choice;
        switch (choice)
        {
        case '1':
            ViewWaitingList(Head);
            break;
        case '2':
            UpdatePatientRecord(history_head);
            break;
        case '3':
            insertionSortVisitHistoryListByTime(&history_head);
            ViewHistoryListPageByPage();
            break;
        case '4':
            SearchPatientFromVisitHistory(history_head);
            break;
        case '5':
            ViewHistoryList(history_head); //(extra function)
            break;
        case '6':
            main();
            break;
        default:
            cout << "\nWrong option, retry again!\n";
            break;
        }
        system("pause");
        system("cls");
    } while (choice != '6');
}


int main() {
    system("cls");
    system("color E1");
    char option;
    string password;

    //Sample data:

    MenuVisits++;

    if (MenuVisits == 1)
    {
        AddSampleData();    //Note: Data's only added the first time the menu is run.
    }      
    
    //Main menu:
    do
    {
        cout << "\n-----------> Welcome to Patient's Queue based Management System <-------------\n\n";
        cout << "\n1. Nurse Page";
        cout << "\n2. Doctor Page";
        cout << "\n3. Exit";
        cout << "\nEnter your option: ";
        cin >> option;
        switch (option)
        {
        case '1':
            cout << "\nEnter the Nurses' Password (G39): ";
            cin >> password;
            if (password == "G39") {
                NursesMenu();
            }
            else {
                cout << "\nWrong Password, Please try again !\n";
            }
            break;
        case '2':
            cout << "\nEnter the Doctors' Password (G39): ";
            cin >> password;
            if (password == "G39") {
                DoctorMenu();
            }
            else {
                cout << "\nWrong Password, Please try again !\n";
            }
            break;
        case '3':
            cout << "\n Bye \n See you soon :> \n";
            system("pause");
            exit(1);
            break;
        default:
            cout << "\nWrong option, retry again!\n";
            break;
        }
    } while (option != '3');
    return 0;
}
