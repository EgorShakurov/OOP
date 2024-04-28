#include <sstream>
#include <iostream>
#include <list>
#include "header.h"
using namespace std;

wstring PrintTeamCoast( const What_coast Coast)
{
    switch(Coast)
    {
        case What_coast::East_coast : return L"Восточное побережье" ;
        case What_coast::West_coast : return L"Западное побережье" ;
        default : return L"Неизвестное побережье" ;
    }
}

Standart_team *Create_New_Team(What_coast Coast)
{
    switch(Coast)
    {
        case What_coast::East_coast : return new East_coast_team() ;
        case What_coast::West_coast : return new West_coast_team() ;
        default : return 0 ;
    }
}


void Task1_not_active(Iterator<TeamPtr> *Iterator)
{
    int teams_counter = 0 ;
    for (Iterator->First(); !Iterator->IsDone() ; Iterator->Next())
    {
        const TeamPtr current_team = Iterator->GetCurrent();
        current_team->ch_status(Team_statuses::Not_active_team) ;
        teams_counter++ ;


    }
    wcout << teams_counter << L" команд теперь неактивны." << endl ;
}


int main()
{
    setlocale(LC_ALL, "Russian");

    First_Container cont1;
    Second_cont cont2 ;

    for (int i=0; i < rand()%300+501; i++)
    {
        int rand_index = rand()%(2)+1;
        cont1.AddTeam(Create_New_Team(static_cast<What_coast>(rand_index)));
    }
    wcout << L"В списке: " << cont1.GetCount() << L" элемента/элементов" << endl ;

    for (int i=0; i < rand()%300+501; i++)
    {
        int rand_index = rand()%(2)+1;
        cont2.AddTeam(Create_New_Team(static_cast<What_coast>(rand_index)));
    }
    wcout << L"В списке: " << cont2.GetCount() << L" элемента/элементов" << endl ;

    Iterator<TeamPtr> *Iterator = new TeamStatusDecorator( new TeamCoastDecorator(cont1.GetIterator(), What_coast::East_coast), Team_statuses::Active_team ) ;
    Task1_not_active(Iterator) ;
    return 0;
}
