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


    return 0;
}
