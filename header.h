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
    int popularity = rand()%(10) ;
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

        bool IsPopularry() const
        {
            if (popularity > 7) {return true;}
            else {return false ;}
        }
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

class East_coast_team : public Standart_team
{
protected:
    string team_name = "East-coast-team";
public:
    East_coast_team() : Standart_team() {current_coast = What_coast::East_coast ;}
    void PlayMatch() const override {wcout << L"Играет команда Восточного побережья"<< endl ;}
};



class FirstContainerIterator : public Iterator<TeamPtr>
{
private:
    const list <TeamPtr> *First_team_cont ;
    list <TeamPtr>::const_iterator Iterator;
public:
    void First(){Iterator = First_team_cont->begin();}
    void Next() {Iterator++;}
    bool IsDone() const {return Iterator == First_team_cont->end();}
    TeamPtr GetCurrent() const {return *Iterator ;}
    FirstContainerIterator(const list<TeamPtr> *First_Team_cont)
    {
        First_team_cont = First_Team_cont;
        Iterator = First_team_cont->begin();
    }

};


class Container
{
public:
    virtual void AddTeam (TeamPtr NewTeam) = 0 ;
    virtual int GetCount() const = 0 ;
    virtual Iterator<TeamPtr> *GetIterator() = 0;
};

class First_Container : public Container
{
private:
    list<TeamPtr> Team_first_cont;

public:
    void AddTeam(TeamPtr new_team)
    {
        Team_first_cont.push_back(new_team);
    }
    int GetCount() const {return Team_first_cont.size() ;}

    Iterator<TeamPtr> *GetIterator()
    {
        return new FirstContainerIterator(&Team_first_cont);
    };
};


class Second_cont_iterator : public Iterator<TeamPtr>
{
private:
	const vector <TeamPtr> *Second_team_cont;
	vector <TeamPtr>::const_iterator Iterator;

public:
	void First(){Iterator = Second_team_cont->begin();}
	void Next() {Iterator++;}
	bool IsDone() const {return Iterator == Second_team_cont->end();}
	TeamPtr GetCurrent() const { return *Iterator; }
    Second_cont_iterator(const vector<TeamPtr> *Second_team_cont)
    {
		Second_team_cont = Second_team_cont;
		Iterator = Second_team_cont->begin();
	}
};



class Second_cont
{
private:
    vector<TeamPtr> Second_team_cont;

public:
    void AddTeam(TeamPtr New_team) {Second_team_cont.push_back(New_team);}
    int GetCount() const {return Second_team_cont.size();}
    TeamPtr GetByIndex(int index) {return Second_team_cont[index];}

   Iterator<TeamPtr> *GetIterator()
    {
        return new Second_cont_iterator(&Second_team_cont);
    };
};



class TeamCoastDecorator : public IteratorDecorator<TeamPtr>
{
private:
    What_coast TargetType;
public:
    TeamCoastDecorator(Iterator<TeamPtr> *Iterator, What_coast targetype) : IteratorDecorator(Iterator)
    {
        TargetType = targetype ;
    }

    void First()
    {
        Decorator->First();
        while (!Decorator->IsDone()&& Decorator->GetCurrent()->what_current_coast()!=TargetType)
        {
            Decorator->Next();
        }
    }

    void Next()
    {
        do
        {
            Decorator->Next();
        }
        while(!Decorator->IsDone()&&Decorator->GetCurrent()->what_current_coast()!= TargetType);
    }
};


class TeamStatusDecorator : public IteratorDecorator<TeamPtr>
{
private:
    Team_statuses StatusType;
public:
    TeamStatusDecorator(Iterator<TeamPtr> *Iterator, Team_statuses statustype) : IteratorDecorator(Iterator)
    {
        StatusType = statustype ;
    }

    void First()
    {
        Decorator->First();
        while (!Decorator->IsDone()&& Decorator->GetCurrent()->current_status()!=StatusType)
        {
            Decorator->Next();
        }
    }

    void Next()
    {
        do
        {
            Decorator->Next();
        }
        while(!Decorator->IsDone()&&Decorator->GetCurrent()->current_status()!= StatusType);
    }
};



class IsPopularDecorator : public IteratorDecorator<TeamPtr>
{
private:
    bool IsPopular;
public:
    IsPopularDecorator(Iterator<TeamPtr> *Iterator, bool isPopular) : IteratorDecorator(Iterator)
    {
        IsPopular = isPopular;
    }

    void First()
    {
        Decorator->First();
        while (!Decorator->IsDone()&& Decorator->GetCurrent()->IsPopularry()!=IsPopular)
        {
            Decorator->Next();
        }
    }

    void Next()
    {
        do
        {
            Decorator->Next();
        }
        while(!Decorator->IsDone()&&Decorator->GetCurrent()->IsPopularry()!= IsPopular);
    }
};

#endif // BASKETBALL_TEAMS
