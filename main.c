/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// Define a struct for staff information
struct Staff {
    char name[50];
    char id[50];
    char department[50];
    char position[50];
    int annualLeave;
    int compassionateLeave;
    int emergencyLeave;
    int maternityLeave;
    int medicalLeave;
};

struct LeaveRecord{
    char name[50];
    char id[50];
    char leave_type[20];
    int day;
    int month;
    int year;
    int duration;
    char status[20];
};

void schoolpage();
void departmentpage();
int login();
void adminpage();
void staffpage();
void approverpage();

int main() {
    schoolpage();
    return 0;
}

void schoolpage() {
    int option;
    printf("Welcome APU Leave Management System\n");
    printf("1. School of Computing\n");
    printf("2. School Of Technology\n");
    printf("3. School of Information Technology\n");
    printf("0. Exit\n");
    printf("Please Select The School You Are Belong To : [1/2/3/0]:");
    scanf("%d", &option);

    switch(option) {
        case 1:
            departmentpage(); // prompt user to department page to select their department
            break;
        case 2:
            // empty
            break;
        case 3:
            // empty
            break;
        case 0:
            printf("Exiting the system...ByeBye\n");
            exit(0);
        default:
            printf("Invalid option. Please try again.\n\n");
            schoolpage();//avoid program stop running even if wrong input
    }
}

void departmentpage(){
    int choice;
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\nDepartment Page\n");
    printf("1. Academic Department\n");
    printf("2. Financial Department\n");
    printf("3. IT Department\n");
    printf("0. Back\n");
    printf("Please Select The Department You Are Belong To : [1/2/3/0]:");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            login();
            
            break;
        case 2:
            // Empty
            break;
        case 3:
            // Empty
            break;
        case 0:
            printf("Going Back....\n\n");
            schoolpage();
            break;
        default:
            printf("Invalid option. Please try again.\n\n");
            departmentpage();//avoid program stop running even if wrong input
    }
    
}


//the loop keep looping when valid=0, valid is set to 1 when username password corect, the loop stops
int login() {
    char username[50];
    char password[50];
    int valid = 0;
    while (!valid) {
        printf("\nEnter username: ");
        scanf("%s", username);
        printf("Enter password: ");
        scanf("%s", password);
        
        // check for admin login
        if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
            adminpage();
            valid = 1;
            break;
        }
        // check for staff login
        FILE *staff_file = fopen("staff.txt", "r");
        if (staff_file != NULL) {
            char staff_username[50];
            char staff_password[50];
            while (fscanf(staff_file, "%s %s",staff_username,staff_password) == 2) {//read 2 strings seperated by space
                if (strcmp(username, staff_username) == 0 && strcmp(password, staff_password) == 0) {
                    staffpage();
                    valid = 1;
                    break;
                }
            }
        fclose(staff_file);
        }
        // check for approver login
        FILE *approver_file = fopen("approver.txt", "r");
        if (approver_file != NULL) {
            char approver_username[50];
            char approver_password[50];
            while (fscanf(approver_file, "%s %s", approver_username, approver_password) == 2) {
                if (strcmp(username, approver_username) == 0 && strcmp(password, approver_password) == 0) {
                    approverpage();
                    valid = 1;
                    break;
                }
            }
        fclose(approver_file);
        }
        // if the valid is still 0, login failed
        if (!valid) {
            printf("Invalid username or password! Please reenter!\n");
            continue;
        }
    }
    return 0;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void add();
int update();
int reset();
void checkLeave();
void checkBalance();
void report();

void adminpage(){
    int choice;
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\nWelcome to the admin page!\n");
    printf("1. Add staff Information\n");
    printf("2. Update Leave Balance Manually\n");
    printf("3. Reset Leave Balance To Default\n");
    printf("4. Search Staff Leave Status\n");
    printf("5. Search Staff Leave Balance\n");
    printf("6. Generate Monthly Report\n");
    printf("0. Log out\n");
    printf("Please select which you want to proceed to : [1/2/3/4/5/6/0]:");
    scanf("%d", &choice);
    switch(choice) {
        case 1:
            add();
            adminpage();
            break;
        case 2:
            update();
            adminpage();
            break;
        case 3:
            reset();
            adminpage();
            break;
        case 4:
            checkLeave();
            adminpage();
            break;
        case 5:
            checkBalance();
            adminpage();
            break;
        case 6:
            report();
            adminpage();
            break;
        case 0:
            printf("Logging Out....\n\n");
            main();
        default:
            printf("Invalid option. Please try again.\n\n");
            adminpage();//avoid program stop running even if wrong input
    }
}
void add() {
    struct Staff staff;
    // Get staff information from user
    printf("Enter staff name: ");
    scanf("%s", staff.name);
    printf("Enter staff ID: ");
    scanf("%s", staff.id);
    printf("Enter department: ");
    scanf("%s", staff.department);
    printf("Enter position: ");
    scanf("%s", staff.position);
    printf("Enter annual leave balance: ");
    scanf("%d", &staff.annualLeave);
    printf("Enter compassionate leave balance: ");
    scanf("%d", &staff.compassionateLeave);
    printf("Enter emergency leave balance: ");
    scanf("%d", &staff.emergencyLeave);
    printf("Enter maternity leave balance: ");
    scanf("%d", &staff.maternityLeave);
    printf("Enter medical leave balance: ");
    scanf("%d", &staff.medicalLeave);

    // Save staff information to file
    FILE *fp = fopen("newstaff.txt", "a");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(fp, "%s %s %s %s %d %d %d %d %d\n", staff.name, staff.id, staff.department, staff.position, staff.annualLeave, 
            staff.compassionateLeave, staff.emergencyLeave, staff.maternityLeave, staff.medicalLeave);
    fclose(fp);
    printf("Staff information added successfully.\n");
}


int update(){
    //array of "staff" structure.
    struct Staff staff[100];
    int numStaff = 0;
    int i;
    //numStaff is the number of staff members that were successfully read from the file
    FILE *fp = fopen("newstaff.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    //read each line of the txt file and saves information into staff aray
    //fgets to read each line, sscanf to save data into struct variable
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s",line);
        //reads 9 value, thn increase numstaff
        if (sscanf(line, "%s %s %s %s %d %d %d %d %d", staff[numStaff].name, staff[numStaff].id, staff[numStaff].department, staff[numStaff].position, &staff[numStaff].annualLeave, &staff[numStaff].compassionateLeave, &staff[numStaff].emergencyLeave, &staff[numStaff].maternityLeave, &staff[numStaff].medicalLeave) == 9) {
            numStaff++;
        }
    }
    fclose(fp);
    int staffname = -1;
    int choice = -1;
    int newValue = -1;
    char name[50];
    printf("\n");
    printf("\nPlease Enter staff name to update leave balance: ");
    scanf("%s", name);
    // find the staff by name
    while (staffname == -1) {
        // find the staff by name
        for (int i = 0; i < numStaff; i++) {
            if (strcmp(staff[i].name, name) == 0) {
                staffname = i;
                break;
            }
        }
        //check whether valid staf name has been found
        if (staffname == -1) {
            printf("Staff not found. Please re-enter staff name: ");
            scanf("%s", name);

            }
        }
    

    printf("Choose field to update:\n");
    printf("1. Annual leave\n");
    printf("2. Compassionate leave\n");
    printf("3. Emergency leave\n");
    printf("4. Maternity leave\n");
    printf("5. Medical leave\n");
    printf("Enter field number: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("Enter new annual leave value: ");
            scanf("%d", &newValue);
            staff[staffname].annualLeave = newValue;//"stafname" variable stores the index of staff structure in the staff array
            break;
        case 2:
            printf("Enter new compassionate leave value: ");
            scanf("%d", &newValue);
            staff[staffname].compassionateLeave = newValue;
            break;
        case 3:
            printf("Enter new emergency leave value: ");
            scanf("%d", &newValue);
            staff[staffname].emergencyLeave = newValue;
            break;
        case 4:
            printf("Enter new maternity leave value: ");
            scanf("%d", &newValue);
            staff[staffname].maternityLeave = newValue;
            break;
        case 5:
            printf("Enter new medical leave value: ");
            scanf("%d", &newValue);
            staff[staffname].medicalLeave = newValue;
            break;
        default:
            printf("Invalid field number.\n");
            return 1;
    }
    // write the updated staff data back to the file
    fp = fopen("newstaff.txt", "w");
    fprintf(fp, "Name ID Department Position AnnualLeave CompassionateLeave EmergencyLeave MaternityLeave MedicalLeave\n");
    for (i = 0; i < numStaff; i++) {
        fprintf(fp,"%s %s %s %s %d %d %d %d %d\n", staff[i].name, staff[i].id, staff[i].department, staff[i].position, staff[i].annualLeave, staff[i].compassionateLeave, staff[i].emergencyLeave, staff[i].maternityLeave, staff[i].medicalLeave);
        
    } 
    printf("\nUpdated staff leave balance successfully!");
    fclose(fp);
    return 0;
}

int reset(){
    // array of "staff" structure
    struct Staff staff[100];
    int numStaff = 0;
    char filename[100];
    int i;
    int sure;
    printf("Do you sure you want to RESET leave balance to DEFAULT?(1 for YES/2 for NO):");
    scanf("%d",&sure);
    switch (sure){
        case 1:
            break;
        case 2:
            adminpage();
            break;
        default:
            printf("Invalid field number.\n");
            return 1;
    }
    FILE *fp = fopen("newstaff.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    // read each line of the txt file using fgets and save information into staff array using sscanf
    // fgets to read each line, sscanf to save data into struct variable
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%s %s %s %s %d %d %d %d %d", staff[numStaff].name, staff[numStaff].id, staff[numStaff].department, staff[numStaff].position, &staff[numStaff].annualLeave, &staff[numStaff].compassionateLeave, &staff[numStaff].emergencyLeave, &staff[numStaff].maternityLeave, &staff[numStaff].medicalLeave) == 9) {
            numStaff++;
        }
    }
    fclose(fp);
    // update all staff leave balances to default values
    for (i = 0; i < numStaff; i++) {
        staff[i].annualLeave = 8;
        staff[i].compassionateLeave = 3;
        staff[i].emergencyLeave = 2;
        staff[i].maternityLeave = 60;
        staff[i].medicalLeave = 14;
    }
    // write the updated staff data back to the file
    fp = fopen("newstaff.txt", "w");
    fprintf(fp, "Name ID Department Position AnnualLeave CompassionateLeave EmergencyLeave MaternityLeave MedicalLeave\n");
    for (i = 0; i < numStaff; i++) {
        fprintf(fp,"%s %s %s %s %d %d %d %d %d\n", staff[i].name, staff[i].id, staff[i].department, staff[i].position, staff[i].annualLeave, staff[i].compassionateLeave, staff[i].emergencyLeave, staff[i].maternityLeave, staff[i].medicalLeave);
    } 
    printf("\nAll staff leave balances have been reset to default values.");
    fclose(fp);
    return 0;
}





void report() {
    int month;
    printf("Enter a month (1-12) to generate leave statistics report: ");
    scanf("%d", &month);
    // Check if month is valid
    if (month < 1 || month > 12) {
        printf("Error: Invalid month\n");
        return;
    }
    // Open leaverecord.txt
    FILE* input_fp = fopen("leaverecord.txt", "r");
    if (input_fp == NULL) {
        printf("Error: Could not open leaverecord.txt\n");
        return;
    }
    // Open report.txt for writing
    FILE* output_fp = fopen("report.txt", "w");
    if (output_fp == NULL) {
        printf("Error: Could not open report.txt\n");
        fclose(input_fp);
        return;
    }
    // Write header to report.txt
    fprintf(output_fp, "Leave Applications Report for month %d:\n", month);
    fprintf(output_fp, "%-20s%-10s%-20s%-15s%s\n", "Name", "ID", "Type", "Date", "Status");
    fprintf(output_fp, "-----------------------------------------------------------------------\n");
    // Read each line of leaverecord.txt and write matching records to report.txt
    char line[256];
    while (fgets(line, 256, input_fp)) {
        char tempName[50], tempID[50], type[20], status[20];
        int day, recordMonth, year, duration;
        // Parse the line and extract the fields
        sscanf(line, "%s %s %s %d %d %d %d %s", tempName, tempID, type, &day, &recordMonth, &year, &duration, status);
        // Check if the record is for the specified month
        if (recordMonth == month) {
            fprintf(output_fp, "%-20s%-10s%-20s%02d/%02d/%-8d%s\n", tempName, tempID, type, day, recordMonth, year, status);
        }
    }
    // Close files
    fclose(input_fp);
    fclose(output_fp);
    printf("Report generated and saved to report.txt\n");
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void applyLeave();
void cancelLeave();



void staffpage() {
    int choice;
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\nWelcome to the staff page!\n");
    printf("1. Apply leave\n");
    printf("2. Cancel Leave\n");
    printf("3. Check leave status\n");
    printf("4. Check leave balance\n");
    printf("0. Log out\n");
    printf("Please select which you want to proceed to : [1/2/3/4/0]:");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            applyLeave();
            staffpage();
            break;
        case 2:
            cancelLeave();
            staffpage();
            break;
        case 3:
            checkLeave();
            staffpage();
            break;
        case 4:
            checkBalance();
            staffpage();
            break;
        case 0:
            printf("Logging Out....\n\n");
            main();
        default:
            printf("Invalid option. Please try again.\n\n");
            staffpage();//avoid program stop running even if wrong input
    }
}

void applyLeave(){
    char name[50], id[50], type[20], status[20]="Pending", confirm;
    int day, month, year, duration;
     // Get input from user
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your ID: ");
    scanf("%s", id);
    // Check if name and ID exist in newstaff.txt
    FILE* fp = fopen("newstaff.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open newstaff.txt\n");
        return;}
    //fgets used to read each line into 'line' character
    int find=0;
    char line[256];
    while (fgets(line, 256, fp)) {
        char tempName[50], tempID[10];
        sscanf(line, "%s %s", tempName, tempID);
        if (strcmp(tempName, name) == 0 && strcmp(tempID, id) == 0){
            find = 1;
            break;}
        }
    fclose(fp);
    // If name and/or ID not found, prompt user to re-enter
    if (!find) {
        printf("Error: Name or ID not found!!Please reenter!\n");
        applyLeave();
        return;
    }
    // Get input for leave details
    int valid_type = 0;
    while (!valid_type) {
        printf("Enter leave type (Annual/Medical/Emergency/Maternity/Compassionate): ");
        scanf("%s", type);
        if (strcmp(type, "Annual") != 0 && strcmp(type, "Medical") != 0 && strcmp(type, "Emergency") != 0
            && strcmp(type, "Maternity") != 0 && strcmp(type, "Compassionate") != 0) {
            printf("Error: Invalid leave type! Please re-enter.\n");
        } else {
            valid_type = 1;
        }
    }
    
    int valid_date = 0;
    while (!valid_date) {
        printf("Enter date (DD/MM/YYYY): ");
        scanf("%d/%d/%d", &day, &month, &year);
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2023) {
            printf("Invalid date entered. Please enter a valid date.\n");
        } else {
            valid_date = 1;
        }
    }
    
    printf("Enter duration(days): ");
    scanf("%d", &duration);

    // Get confirmation from user
    printf("Are you sure you want to apply for %s leave on %d/%d/%d? (Y/N): ", type, day, month, year);
    scanf(" %c", &confirm);

    // If confirmed, add leave record to file
    if (confirm == 'Y' || confirm == 'y') {
        FILE* fp = fopen("leaverecord.txt", "a");
        if (fp == NULL) {
            printf("Error: Could not open leaverecord.txt\n");
            return;
        }
        fprintf(fp, "%s %s %s %d %d %d %d %s\n", name, id, type, day, month, year, duration, status);
        fclose(fp);
        printf("Leave application submitted!\n");
    } else {
        printf("Leave application cancelled.\n");
    }
}

void cancelLeave(){
    struct LeaveRecord records[100];
    int i;
    int num_records=0;
    FILE *fp = fopen("leaverecord.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line),fp)) {
        if(sscanf(line, "%s %s %s %d %d %d %d %s", records[num_records].name, records[num_records].id,records[num_records].leave_type, 
        &records[num_records].day, &records[num_records].month, &records[num_records].year, 
        &records[num_records].duration, records[num_records].status)==8){
            num_records++;
        }
    }
    fclose(fp);
    int staffname = -1;
    char id[50];
    printf("\nPlease enter staff ID to cancel leave application: ");
    scanf("%s", id);
    while (staffname == -1) {
        for (int i = 0; i < num_records; i++) {
            if (strcmp(records[i].id, id) == 0) {
                staffname = i;
                break;
            }
        }
        if (staffname == -1) {
            printf("Staff not found. Please re-enter staff ID: ");
            scanf("%s", id);
        }
    }
    // Check if the leave application can be cancelled
    // Leave cannot be cancelled if status is Rejected
    if (strcmp(records[staffname].status, "Rejected") == 0) {
        printf("Leave application has been rejected.\n");
        return;
    }
    // Check if the leave application date has already passed
    int current_day = 1;
    int current_month = 3;
    int current_year = 2023;
    if (records[staffname].year < current_year || (records[staffname].year == current_year && records[staffname].month < current_month) 
    || (records[staffname].year == current_year && records[staffname].month == current_month && records[staffname].day < current_day)) {
        printf("Date has passed, cannot cancel.\n");
        return;
    }
    // Get the leave application details
    char leave_type[20];
    sprintf(leave_type, "%s", records[staffname].leave_type);
    char leave_date[20];
    sprintf(leave_date, "%d/%d/%d", records[staffname].day, records[staffname].month, records[staffname].year);
    int duration = records[staffname].duration;
    // Confirm with user that they want to cancel the leave application
    printf("\nDo you want to cancel the %s leave application for %s for %d days? (y/n): ", leave_type, leave_date, duration);
    char answer;
    scanf(" %c", &answer);
    if (answer == 'n' || answer == 'N') {
        return;
    }
    // Remove the leave application from the array
    for (i = staffname; i < num_records-1; i++) {
        records[i] = records[i+1];
    }
    num_records--;
    // Update the file with the new leave records
    fp = fopen("leaverecord.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    fprintf(fp,"Name ID LeaveType Day Month Year Duration Status\n");
    for (i = 0; i < num_records; i++) {
        fprintf(fp, "%s %s %s %d %d %d %d %s\n", records[i].name, records[i].id, records[i].leave_type, records[i].day, records[i].month, 
        records[i].year, records[i].duration, records[i].status);
    }
    fclose(fp);
    printf("\nLeave application has been cancelled.\n");
}


void checkLeave(){
    char nameid[50];
    int find = 0;
    
    // Get input from user
    printf("Enter name or ID: ");
    scanf("%s", nameid);
    
    
    
    // Check if name and ID exist in leaverecord.txt
    FILE* fp = fopen("leaverecord.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open leaverecord.txt\n");
        return;
    }
    
    // Read each line of the file
    char line[256];
    while (fgets(line, 256, fp)) {
        char tempName[50], tempID[50], type[20], status[20];
        int day, month, year, duration;
        // Parse the line and extract the fields
        sscanf(line, "%s %s %s %d %d %d %d %s", tempName, tempID, type, &day, &month, &year, &duration, status);
        
        // Check if the name and ID match
        if (strcmp(tempName, nameid) == 0 || strcmp(tempID, nameid) == 0) {
            find = 1;
            printf("\nLeave record found for Name/ID:%s\n", nameid);
            printf("Type: %s\n", type);
            printf("Date: %d/%d/%d\n", day, month, year);
            printf("Duration: %d day(s)\n", duration);
            printf("Status: %s\n", status);
            break;
        }
    }
    fclose(fp);
   
    if (!find) {
        printf("No leave record found for %s\n", nameid);
    }
}

void checkBalance(){
    char nameid[50];
    int find = 0;
    // Get input from user
    printf("Enter name or ID: ");
    scanf("%s", nameid);
    // Check if name and ID exist in newstaff.txt
    FILE* fp = fopen("newstaff.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open newstaff.txt\n");
        return;
    }
    // Read each line of the file
    char line[256];
    while (fgets(line, 256, fp)) {
        char tempName[50], tempID[50], department[20], position[20];
        int annualLeave, compassionateLeave, emergencyLeave, maternityLeave, medicalLeave;
        // Parse the line and extract the fields
        sscanf(line, "%s %s %s %s %d %d %d %d %d", tempName, tempID, department, position, &annualLeave, &compassionateLeave, &emergencyLeave, &maternityLeave, &medicalLeave);
        
        // Check if the name and ID match
        if (strcmp(tempName, nameid) == 0 || strcmp(tempID, nameid) == 0) {
            find = 1;
            printf("\nLeave Balance for Name/ID:%s\n", nameid);
            printf("Annual Leave: %d\n", annualLeave);
            printf("Compassionate Leave: %d\n", compassionateLeave);
            printf("Emergency Leave: %d\n", emergencyLeave);
            printf("Maternity Leave: %d\n", maternityLeave);
            printf("Medical Leave: %d\n", medicalLeave);
            break;
        }
    }
    fclose(fp);
    if (!find) {
        printf("No leave record found for %s\n", nameid);
    }
}




    
    
    



//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void searchLeave();
void approveLeave();

void approverpage() {
    int choice;

    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\nWelcome to the approver page!\n");
    printf("1. Approve/Reject applications\n");
    printf("2. Search Leave\n");
    printf("0. Log out\n");
    printf("Please select which you want to proceed to : [1/2/0]:");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            approveLeave();
            approverpage();
            break;
        case 2:
            searchLeave();
            approverpage();
            break;
        case 0:
            printf("Logging Out....\n\n");
            main();
        default:
            printf("Invalid option. Please try again.\n\n");
            approverpage();//avoid program stop running even if wrong input
    }
}

void approveLeave(){
    struct LeaveRecord records[100];
    int i;
    int num_records=0;
    // Open the file for reading
    FILE *fp = fopen("leaverecord.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    // Read each line and store the leave record in the array
    char line[100];
    while (fgets(line, sizeof(line),fp)) {
        printf("%s",line);
        if(sscanf(line, "%s %s %s %d %d %d %d %s", records[num_records].name, records[num_records].id, records[num_records].leave_type, &records[num_records].day, &records[num_records].month, &records[num_records].year, &records[num_records].duration, records[num_records].status)==8){
        num_records++;
    }
    }
    fclose(fp);
    int staffname = -1;
    int choice = -1;
    int newValue = -1;
    char name[50];
    printf("\n");
    printf("\nPlease Enter staff name to update leave application: ");
    scanf("%s", name);
     // find the staff by name
    while (staffname == -1) {
        for (int i = 0; i < num_records; i++) {
            if (strcmp(records[i].name, name) == 0) {
                staffname = i;
                break;
            }
        }
        //check whether valid staf name has been found
        if (staffname == -1) {
            printf("Staff not found. Please re-enter staff name: ");
            scanf("%s", name);
            }
        }
        
    //help me do this part i need to ask user whether toapprove or reject the leave application, then change he status fdrom "Pending" to Apprved
    // Prompt the user to approve or reject the leave application
    printf("\n");
    printf("\nDo you want to approve or reject the leave application?\n");
    printf("1. Approve\n");
    printf("2. Reject\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Update the leave status
    if (choice == 1) {
        strcpy(records[staffname].status, "Approved");
        printf("\nThe leave application has been approved.\n");
    } else if (choice == 2) {
        strcpy(records[staffname].status, "Rejected");
        printf("\nThe leave application has been rejected.\n");
    } else {
        printf("\nInvalid choice.\n");
        return;
    }    
    
    

    // Update the file with the new leave status
    fp = fopen("leaverecord.txt", "w");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return;
    }
    fprintf(fp,"Name ID LeaveType Day Month Year Duration Status\n");
    for (i = 0; i < num_records; i++) {
        fprintf(fp, "%s %s %s %d %d %d %d %s\n", records[i].name, records[i].id, records[i].leave_type, records[i].day, records[i].month, records[i].year, records[i].duration, records[i].status);
    }
    printf("\nStatus updated successfully!");

    fclose(fp);
}


void searchLeave(){
    int day, month, year, count = 0;
    printf("Enter the date to search for (DD/MM/YYYY): ");
    scanf("%d/%d/%d", &day, &month, &year);
    // Check if date is valid
    if (day < 1 || day > 31 || month < 1 || month > 12) {
        printf("Error: Invalid date!!!\n");
        return;
        
    } 
    // Open leaverecord.txt
    FILE* fp = fopen("leaverecord.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open leaverecord.txt\n");
        return;
    }
    // Search for leave records with the specified date
    char line[256];
    while (fgets(line, 256, fp)) {
        char tempName[50], tempID[50], type[20], status[20];
        int recordDay, recordMonth, recordYear, duration;
        // Parse the line and extract the fields
        sscanf(line, "%s %s %s %d %d %d %d %s", tempName, tempID, type, &recordDay, &recordMonth, &recordYear, &duration, status);
        // Check if the date matches
        if (recordDay == day && recordMonth == month && recordYear == year) {
            count++;
            printf("%s (ID: %s) applied for %s leave on %d/%d/%d, status: %s\n", tempName, tempID, type, recordDay, recordMonth, recordYear, status);
        }
    }
    fclose(fp);
    if (count == 0) {
        printf("No leave records found for %d/%d/%d\n", day, month, year);
    } else {
        printf("%d staff applied for leave on %d/%d/%d\n", count, day, month, year);
    }
}


    



