#ifndef BASKETBALL_TEAMS
#define BASKETBALL_TEAMS
#include <string>
#include <vector>
#include "iterators.h"
using namespace std;


enum class Team_statuses : int
{
    Active_team = 1,
    Not_active_team  = 2,
    Unknown = 0
};

enum class What_coast : int
{
    West_coast = 1,
    East_coast = 2,
    Unknown_coast = 0
};

class Standart_team
{
    protected:
    string team_name = "No_team_name";
    int members_count = 4;
    Team_statuses team_status = static_cast<Team_statuses>(rand()%(2)+1) ;
    What_coast current_coast = static_cast<What_coast>(rand()%(2)+1) ;
    public:
        Standart_team()
        {

        }
        virtual void PlayMatch() const = 0 ;
        virtual void Slam_dunk() const {wcout << L"Отличный Slam-dunk!!!" << endl ;}
        What_coast what_current_coast() const {return current_coast ; }
        void ch_status(Team_statuses new_status)
        {
            team_status = new_status ;
        }
        Team_statuses current_status() const {return team_status ;}
};




typedef Standart_team *TeamPtr ;


class West_coast_team : public Standart_team
{
    protected:
    string team_name = "West-coast-team" ;
    public:
        West_coast_team() : Standart_team() {current_coast =  What_coast::West_coast ;}
        void PlayMatch() const override {wcout << L"Играет команда Западного побережья"<< endl ;}
        void Shuffle() const {wcout << L"Ведение мяча" << endl ; }
};


#endif // BASKETBALL_TEAMS
