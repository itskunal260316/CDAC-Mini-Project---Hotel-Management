#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <fstream>
#include <ctime>
#define totalRooms 50

using namespace std;


//consider that previously 2000 people were at the hotel
int totalCust = 2000;

//rents for each room Standard, Deluxe and Presidential Suite resp.
const int rentStd=3500;
const int rentDel=5500;
const int rentPs=70000;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////      CUSTOMER   CLASS    /////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

class Customer{

public:

    unsigned int customerId; //will be unique to each customer
    string name;
    char phoneNo[11];
    int guestNo;
    string city;

    Customer* assignRoom();

};

//////////////////////////////////////////////////////////////
////////////////   assignRoom Method    //////////////////////
//////////////////////////////////////////////////////////////

Customer* Customer :: assignRoom()
{
        Customer *cust = new Customer();
        cust->customerId += totalCust + 1;
        totalCust = totalCust++;
        cout<<endl<<endl<<"ENTER CUSTOMER DETAILS: "<<endl;
        cout<<endl<<"Enter name: ";
        cin.ignore();
        getline(cin,cust->name);
        cout<<endl<<"Enter number of guests: ";
        cin>>cust->guestNo;
        cin.ignore();
        cout<<endl<<"Enter Contact(10 Digit Number): ";
        cin.getline(cust->phoneNo,11);
        cout<<endl<<"Enter Home Town: ";
        getline(cin,cust->city);
        return cust;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////      ROOM   CLASS    ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

class Room{

public:

    int room_id;
    char type; // standard or deluxe or presidential suite
    int advPayment;
    char room_service;
    Customer *allocatedTo; //point to the customer obj for that particular room object
    bool status;
    int totalPaymentDue;

    friend class Customer;


    void createRoom(int);
    bool checkExists(int);//check of the room exits with the same room no
    bool checkStatus(int);//check if the room is booked or not



};


//////////////////////////////////////////////////////////////
////////////////   createRoom Method    //////////////////////
//////////////////////////////////////////////////////////////


Room roomArr[totalRooms];
int roomIndex=0;

 void Room::createRoom(int rno)
    {
        system("cls");
        Room temp;
        temp.room_id=rno;
        cout<<endl<<"______FILL OUT DETAILS FOR ROOM NO "<<rno<<"______";
        cout<<endl<<endl<<endl<<"Enter Room Type (S: Standard, D:Deluxe, P: Presidential Suite) :";
        cin.ignore();
        cin>>temp.type;
        cout<<endl<<"Advance Payment: ";
        cin.ignore();
        cin>>temp.advPayment;
        //compute the remainder of the payment depending on room type and adv payment
        if(temp.type=='s' || temp.type=='S')
        {
            temp.totalPaymentDue = rentStd - temp.advPayment;
        }
        else if(temp.type=='d' || temp.type=='D')
        {
            temp.totalPaymentDue = rentDel - temp.advPayment;
        }
        else if(temp.type=='p' || temp.type=='P')
        {
            temp.totalPaymentDue = rentPs - temp.advPayment;
        }
        cout<<endl<<"Room service (Y/N) ? : ";
        cin.ignore();
        cin>>temp.room_service;
        temp.allocatedTo=NULL;
        temp.status=false;
        roomArr[roomIndex]=temp;
        cout<<endl<<endl<<"ROOM CREATED";

}

//////////////////////////////////////////////////////////////
////////////////   checkExits Method    //////////////////////
//////////////////////////////////////////////////////////////

bool Room :: checkExists(int rno)
{
    for(int i=0; i<roomIndex; i++)
    {
        if(rno==roomArr[i].room_id)
        {
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////
////////////////   checkStatus Method    /////////////////////
//////////////////////////////////////////////////////////////

bool Room :: checkStatus(int rno)
{
    for(int i=0; i<roomIndex; i++)
    {
        if(roomArr[i].room_id==rno)
        {
            if(roomArr[i].status==0)
                return false;
            else
                return true;
        }
    }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////      MANAGE   CLASS    ///////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

class Manage : protected Room
{
public:

    void checkIN(int);
    void checkOUT(int);
    void viewDetails(int);
    void viewDetails(string);
    void viewBookedRooms();
    void viewVacantRooms();
    void manageRoomService(int);

};

//////////////////////////////////////////////////////////////
///////////////////   checkIN Method    //////////////////////
//////////////////////////////////////////////////////////////


void Manage :: checkIN(int rno)
{
     Room r;
     Customer c;
    if(roomIndex==0)
    {
        char newRoom;
        cout<<"INITIATE ROOM CREATION ? (Y/N) ? : ";
        cin>>newRoom;
        if(newRoom=='y' || newRoom=='Y')
        {
            r.createRoom(rno);
            roomArr[0].allocatedTo = c.assignRoom();
            roomArr[0].status=true;
            roomIndex++;
            cout<<endl<<"ROOM HAS BEEN BOOKED";
            getch();
            return;
        }

        else
            return;
    }
    else if(roomIndex > 0)
    {
        if(r.checkExists(rno))
        {
            if(r.checkStatus(rno))
            {
                cout<<endl<<"SORRY, Room is already booked";
                cout<<endl<<"TRY AGAIN PLEASE";
                cout<<endl<<endl<<"Press any key to continue";
                getch();
            }

            else
            {
                    for(int i=0; i<roomIndex; i++)
                    {
                        if(roomArr[i].room_id==rno)
                        {

                            roomArr[i].status=true;
                            cout<<endl<<"Enter Room Type (S: Standard, D:Deluxe, P: Presidential Suite) :";
                            cin.ignore();
                            cin>>roomArr[i].type;
                            cout<<endl<<"Advance Payment: ";
                            cin.ignore();
                            cin>>roomArr[i].advPayment;
                            if(roomArr[i].type=='s' || roomArr[i].type=='S')
                            {
                                roomArr[i].totalPaymentDue = rentStd - roomArr[i].advPayment;
                            }
                            else if(roomArr[i].type=='d' || roomArr[i].type=='D')
                            {
                                roomArr[i].totalPaymentDue = rentDel - roomArr[i].advPayment;
                            }
                            else if(roomArr[i].type=='p' || roomArr[i].type=='P')
                            {
                                roomArr[i].totalPaymentDue = rentPs - roomArr[i].advPayment;
                            }
                            cout<<endl<<"Room service (Y/N) ? : ";
                            cin.ignore();
                            cin>>roomArr[i].room_service;
                            roomArr[i].allocatedTo = c.assignRoom();
                            roomIndex++;
                            cout<<endl<<"ROOM HAS BEEN BOOKED";
                            getch();

                        }
                    }
            }
        }
        else
        {
            r.createRoom(rno);
            roomArr[roomIndex].allocatedTo = c.assignRoom();
            roomArr[roomIndex].status=true;
            roomIndex++;
            cout<<endl<<"ROOM HAS BEEN BOOKED";
            cout<<endl<<"Press any key to continue";
            getch();
        }
    }

}


//////////////////////////////////////////////////////////////
///////////////////   checkOUT Method    //////////////////////
//////////////////////////////////////////////////////////////


void Manage :: checkOUT(int rno)
{
    for(int i=0; i<roomIndex; i++)
    {
        if(roomArr[i].room_id==rno)
        {
            system("cls");
            cout<<endl<<"NAME : "<<roomArr[i].allocatedTo->name<<" | ";
            cout<<endl<<"CONTACT : "<<roomArr[i].allocatedTo->phoneNo<<" | ";
            cout<<endl<<"ROOM NO : "<<roomArr[i].room_id<<" | ";
            cout<<"ROOM TYPE : "<<roomArr[i].type;
            cout<<endl<<"ADVANCE PAYMENT : "<<roomArr[i].advPayment<<" | ";
            cout<<endl<<"PAYMENT DUE : "<<roomArr[i].totalPaymentDue<<" | ";
            cout<<endl<<"CHECK OUT (Y/N) ? : ";
            char co;
            cin>>co;
                if(co=='y')
                {
                    fstream log_file("CustomerLog.txt",ios::out | ios::app);
                    if(!log_file)
                    {
                        cout<<endl<<"No FILE CREATED";
                    }
                    time_t checkOutTime;
                    time(&checkOutTime);
                    log_file <<"DAY / DATE /TIME : "<<asctime(localtime(&checkOutTime))<<" | ";
                    log_file <<"CUSTOMER ID : "<<roomArr[i].allocatedTo->customerId<<" |  ";
                    log_file <<"NAME : "<<roomArr[i].allocatedTo->name<<" | \n";
                    log_file <<"CONTACT NO : "<<roomArr[i].allocatedTo->phoneNo<<" | \n";
                    log_file <<"ROOM NUMBER : "<<roomArr[i].room_id<<" | \n";
                    log_file <<"GUESTS : "<<roomArr[i].allocatedTo->guestNo<<" | \n";
                    log_file <<"ADDRESS : "<<roomArr[i].allocatedTo->city<<" | \n";
                    log_file <<"ROOM TYPE : "<<roomArr[i].type<<" | \n";
                    log_file <<"ROOM SERVICE : "<<roomArr[i].room_service<<" | \n";
                    log_file <<"ADVANCE PAYMENT : "<<roomArr[i].advPayment<<" | \n";
                    log_file <<"TOTAL RENT : "<<roomArr[i].advPayment + roomArr[i].totalPaymentDue<<" | \n";
                    log_file <<"\n------------------------------------------------\n\n";
                    log_file.close();
                    delete roomArr[i].allocatedTo;
                    roomArr[i].allocatedTo=NULL;
                    roomArr[i].status=false;
                    cout<<endl<<"CHECKED OUT";
                    cout<<endl<<"CUSTOMER LOG WAS ADDED TO LOG FILE.";
                    cout<<endl<<endl<<"Press any key to continue";
                    getch();
                }
                else
                    return;

        }
    }
}

//////////////////////////////////////////////////////////////
//////////////   viewDetails Method(INT)    //////////////////
//////////////////////////////////////////////////////////////


void Manage :: viewDetails(int rno)
{
    for(int i=0; i<roomIndex; i++)
    {
        if(rno==roomArr[i].room_id)
        {

            cout<<endl<<"_____ROOM DETAILS_____"<<endl<<endl;
            cout<<"CUSTOMER ID : "<<roomArr[i].allocatedTo->customerId<<" | ";
            cout<<"CUSTOMER NAME : "<<roomArr[i].allocatedTo->name;
            cout<<endl<<"CONTACT : "<<roomArr[i].allocatedTo->phoneNo;
            cout<<endl<<"ROOM ID : "<<roomArr[i].room_id<<" | ";
            cout<<"ROOM TYPE : "<<roomArr[i].type<<" | ";
            cout<<endl<<"View More details (Y/N) ?:  ";
            char more;
            cin>>more;
            if(more=='y')
            {
                system("cls");
                cout<<endl<<endl;
                cout<<endl<<"_____ROOM DETAILS_____"<<endl<<endl;
                cout<<"CUSTOMER ID : "<<roomArr[i].allocatedTo->customerId<<" | ";
                cout<<"CUSTOMER NAME : "<<roomArr[i].allocatedTo->name;
                cout<<endl<<"CONTACT : "<<roomArr[i].allocatedTo->phoneNo;
                cout<<endl<<"ROOM ID : "<<roomArr[i].room_id<<" | ";
                cout<<"OCCUPANTS : "<<roomArr[i].allocatedTo->guestNo<<" | ";
                cout<<"ROOM TYPE : "<<roomArr[i].type<<" | ";
                cout<<endl<<"ROOM SERVICE :"<<roomArr[i].room_service<<" | ";
                cout<<"ADVANCED PAYMENT :"<<roomArr[i].advPayment<<" | ";
                cout<<"PAYMENT DUE : "<<roomArr[i].totalPaymentDue<<" | ";
                cout<<endl<<"Press any key to continue";
                getch();
            }
        }
    }
}



//////////////////////////////////////////////////////////////
//////////////   viewDetails Method(STRING)    ///////////////
//////////////////////////////////////////////////////////////

void Manage :: viewDetails(string name)
{
    for(int i=0; i<roomIndex; i++)
    {

        if(roomArr[i].allocatedTo->name==name)
        {
            cout<<endl<<"ROOM DETAILS"<<endl<<endl;
            cout<<"CUSTOMER ID : "<<roomArr[i].allocatedTo->customerId<<" | ";
            cout<<"CUSTOMER NAME : "<<roomArr[i].allocatedTo->name;
            cout<<endl<<"CONTACT : "<<roomArr[i].allocatedTo->phoneNo;
            cout<<endl<<"ROOM ID : "<<roomArr[i].room_id<<" | ";
            cout<<"ROOM TYPE : "<<roomArr[i].type<<" | ";
            cout<<endl<<"View More details (Y/N)  ? :  ";
            char more;
            cin>>more;
            if(more=='y')
            {
                system("cls");
                cout<<endl<<endl;
                cout<<endl<<"ROOM DETAILS BOOKED UNDER : "<<roomArr[i].allocatedTo->name;
                cout<<endl<<"CONTACT : "<<roomArr[i].allocatedTo->phoneNo;
                cout<<endl<<"ROOM ID : "<<roomArr[i].room_id<<" | ";
                cout<<"OCCUPANTS : "<<roomArr[i].allocatedTo->guestNo<<" | ";
                cout<<"ROOM TYPE : "<<roomArr[i].type<<" | ";
                cout<<endl<<"ROOM SERVICE :"<<roomArr[i].room_service<<" | ";
                cout<<"ADVANCED PAYMENT :"<<roomArr[i].advPayment<<" | ";
                cout<<"PAYMENT DUE : "<<roomArr[i].totalPaymentDue<<" | ";
            }
        }
        else
            cout<<endl<<"No Bookings found";

        cout<<endl<<"Press any key to Continue";
        getch();
    }
}



//////////////////////////////////////////////////////////////
//////////////   viewBookedRooms Method    ///////////////////
//////////////////////////////////////////////////////////////

void Manage::viewBookedRooms()
{
   if(roomIndex!=0)
    {
        for(int i=0; i<roomIndex ; i++)
        {
            if(roomArr[i].status==true)
            {
                 cout<<roomArr[i].room_id<<" | ";
            }
        }
    }
    else
        cout<<endl<<"No rooms Created";
        cout<<endl<<"Press any key to Continue";
        getch();
}

//////////////////////////////////////////////////////////////
//////////////   viewVacantRooms Method    ///////////////////
//////////////////////////////////////////////////////////////


void Manage :: viewVacantRooms()
{
    for(int i=0;i<roomIndex;i++)
    {
        if(roomArr[i].status==0)
        {
            cout<<roomArr[i].room_id<<" | ";
        }
    }
    cout<<endl<<"Press any key to continue";
    getch();
}



//////////////////////////////////////////////////////////////
//////////////   manageRoomService Method    ///////////////////
//////////////////////////////////////////////////////////////

void Manage :: manageRoomService(int rno)
{
    for(int i=0;i<roomIndex;i++)
    {
        if(roomArr[i].room_id==rno)
        {
            if(roomArr[i].room_service=='y')
            {
                chooseService:
                system("cls");
                cout<<"CHOOSE SERVICE : "<<endl;
                cout<<"1. Food Order"<<endl;
                cout<<"2. Housekeeping"<<endl;
                cout<<"3. GO BACK"<<endl;
                int ser;
                cout<<"Choose the service :";
                cin>>ser;
                if(ser==1)
                {
                    system("cls");
                    cout<<"CHOOSE MEAL :";
                    cout<<endl<<"1. Breakfast";
                    cout<<endl<<"2. Lunch";
                    cout<<endl<<"3. Dinner";
                    cout<<endl<<"4. GO BACK";
                    cout<<endl<<"(ANY MEAL YOU ORDER IN THE ROOM WILL BE CHEF SPECIAL OF THE DAY)"<<endl;
                    int meal;
                    cout<<endl<<"Choose from the options above: ";
                    cin>>meal;
                    switch(meal)
                    {
                        case 1:{
                                    cout<<"Breakfast costs : 150"<<endl;
                                    char br;
                                    cout<<"Continue (Y/N) ? : Enter choice =>> ";
                                    cin>>br;
                                    if(br=='y')
                                    {
                                        cout<<"Meal for how many people ?:";
                                        int no;
                                        cin>>no;
                                        roomArr[i].totalPaymentDue += (150*no);
                                        cout<<endl<<"MEALS WILL BE DELIVERED SOON";
                                        cout<<endl<<"Press any key to continue";
                                        getch();
                                        break;
                                    }
                                    else
                                        goto chooseService;
                        }
                        case 2: {
                                    cout<<"Lunch costs : 300"<<endl;
                                    char br;
                                    cout<<"Continue (Y/N) ? :  ";
                                    cin>>br;
                                    if(br=='y')
                                    {
                                        cout<<"Meal for how many people ?:";
                                        int no;
                                        cin>>no;
                                        roomArr[i].totalPaymentDue += (300*no);
                                        cout<<endl<<"MEAL WILL BE DELIVERED SOON";
                                        cout<<endl<<"Press any key to continue";
                                        getch();
                                        break;
                                    }
                                    else
                                        goto chooseService;
                        }
                        case 3: {
                                    cout<<"Dinner costs : 250"<<endl;
                                    char br;
                                    cout<<"Continue (Y/N) ? :  ";
                                    cin>>br;
                                    if(br=='y')
                                    {
                                        cout<<"Meal for how many people ?:";
                                        int no;
                                        cin>>no;
                                        roomArr[i].totalPaymentDue += (250*no);
                                        cout<<endl<<"MEAL WILL BE DELIVERED SOON";
                                        cout<<endl<<"Press any key to continue";
                                        getch();
                                        break;
                                    }
                                    else
                                        goto chooseService;
                        }
                        default : {
                                    cout<<endl<<"INVALID COMMAMND";
                                    cout<<endl<<"Press any key to continue";
                                    getch();
                                    goto chooseService;
                        }
                    }
                }
                else if(ser==2)
                {
                    system("cls");
                    cout<<"______HOUSEKEEPING_____"<<endl;
                    cout<<endl<<"Housekeeping will cost Rs. 500.";
                    cout<<endl<<"Confirm Housekeeping (Y/N)? : Enter choice =>> ";
                    char hk;
                    cin>>hk;
                    if(hk=='y')
                    {
                        roomArr[i].totalPaymentDue += 500;
                        cout<<endl<<"ROOM WILL BE CLEANED AT THE EARLIEST CONVINIENCE.";
                        cout<<endl<<endl<<"Press any key to continue";
                        getch();
                        goto chooseService;
                    }
                    else
                        goto chooseService;
                }
                else
                {
                    return;
                }


            }
            else
            {
                cout<<endl<<"Customer has not chosen the Room Service Option";
                cout<<endl<<"Press any key to continue";
                getch();
                return;
            }

        }
    }
    cout<<endl<<"No such room exists, TRY AGAIN";
    return;
}










///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////      MAIN   FUNCTION    //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int opt=0;
    do{
        system("cls");
        cout<<"MAIN MENU"<<endl<<endl;
        cout<<"1. Check IN"<<endl;
        cout<<"2. Check OUT"<<endl;
        cout<<"3. View Booked Rooms"<<endl;
        cout<<"4. View Vacant Rooms"<<endl;
        cout<<"5. View Details"<<endl;
        cout<<"6. Room Services"<<endl;
        cout<<"7. Exit";

        cout<<endl<<"Choose Option: ";
        cin>>opt;

        switch(opt)
        {
            Manage m;
            case 1:{
                    system("cls");
                    cout<<"_____CHECK IN_____"<<endl<<endl;
                    int rno;
                    cout<<"Enter Room Number: ";
                    cin>>rno;
                    if(rno < 1 && rno > 51)
                    {
                        cout<<endl<<"Enter Valid Room Number from  [ 1 - 50 ].";
                        cout<<endl<<endl<<"Press any key to continue.",
                        getch();
                        break;
                    }
                    m.checkIN(rno);
                    //roomIndex++;
                    break;
            }
            case 2: {
                        cout<<endl<<"Enter the Room Number to check out: ";
                        int roomNo;
                        cin>>roomNo;
                        m.checkOUT(roomNo);
                        break;
            }
            case 3: {
                        m.viewBookedRooms();
                        break;
            }
            case 4:{
                        m.viewVacantRooms();
                        break;
            }
            case 5: {
                        system("cls");
                        cout<<"View details via NAME or ROOM NUMBER ?  :";
                        cout<<endl<<"<N>. NAME.";
                        cout<<endl<<"<R>. ROOM NUMBER.";
                        cout<<endl<<"(Enter N to search with NAME and R for ROOM NO) : ";
                        char view;
                        cin>>view;
                        if(view=='N' || view=='n')
                        {
                            cout<<"Enter name :";
                            string searchName;
                            cin.ignore();
                            getline(cin,searchName);
                            m.viewDetails(searchName);
                        }
                        else if(view=='R' || view=='r')
                        {
                            int roomNo;
                            cout<<endl<<"Enter room Number: ";
                            cin>>roomNo;
                            m.viewDetails(roomNo);
                        }
                        break;

            }
            case 6:{
                        cout<<endl<<"Enter the Room Number for further options :";
                        int roomNo;
                        cin>>roomNo;
                        m.manageRoomService(roomNo);
                        break;
            }
            case 7: {
                        cout<<endl<<"THANK YOU FOR CHOOSING US";
                        exit(1);
            }
        }

    }while(opt!=7);

    return 0;
}
