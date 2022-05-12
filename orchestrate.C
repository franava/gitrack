#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <ratio>
#include <chrono>

using namespace std ;
using namespace std::chrono ;
typedef duration<int, std::ratio<86400>> days_type ;


string install_folder = "INSTALL_PATH_FOLDER" ;
string logs_folder = install_folder + "/logs/" ; 
string project_list = install_folder + "/ProjectList" ; 
string run_update = install_folder + "/run_update.sh " ; 

void usage()
{
    cerr << "orchestrate usage: \n" ;
    cerr << "Execute Orchestration: \n" ;
    cerr << "$ ./orchestrate\n" ;
    cerr << "Track all repo for orchestration: \n" ;
    cerr << "$ ./orchestrate --track-all ( -t)\n" ;
    cerr << "Untrack all repos for  orchestration: \n" ;
    cerr << "$ ./orchestrate --untrack-all ( -u)\n" ;
    cerr << "Need help fororchestration? \n" ;
    cerr << "$ ./orchestrate --help ( -h) \n" ;
}

void help()
{
    cerr << "Orchestrate is used to check if any change has occurred since the last iteration of Orchestrate\n";
    cerr << "accross all the repos tracked by the ProjectList file.\n" ;
    cerr << "Each row of the ProjectList file contains:\n[1] the repo's name, \n[2] the repo's ssh retrieve url \n[3] if the repo has to be tracked [t] or not [u]\n";
    usage() ;

}

bool exists(const string& name)
{
    struct stat buffer ;
    return (stat ( name.c_str(), &buffer) == 0 ) ;
}

void orchestrate(char tracking)
{
    ostringstream name ;
    name << "report_" << time_point_cast<days_type>(system_clock::now()).time_since_epoch().count() << ".log" ;
    ostringstream suffix ;
    ostringstream fullname ;
    int iteration = 0 ;
   
    //checks for the first available logname adding numerical suffixes to a basename.
    while(true)
    {
        if (iteration != 0 )
        {
            suffix << '.' << iteration ;
        }
        ++iteration ;
        fullname << name.str() << suffix.str() ;
        if( ! exists(logs_folder + fullname.str()) )
            break ;
        else
        {
            suffix.str("");
            suffix.clear() ;
            fullname.str("") ;
            fullname.clear() ;
        }
    }


    ifstream in(project_list.c_str()) ;

    while (true)
    {
        string component, repo ;
        string mode ;
        in >> component ; //loading component from ProjectList
        in >> repo ; //loading repo from ProjectList
        in >> mode ;
        if (tracking == 1) //track all
            mode = "t" ;
        else if (tracking == 2) //untrack all
            mode = "f" ;
        else{} //follow the file specs

        if(in.eof())
            break ;
        string cmd = run_update + repo + " " + component + " " + fullname.str() + " " + mode;
        system(cmd.c_str()) ;
    }

}


int main( int argc, const char **argv )
{
    char track = 0;
    if(argc == 2) 
    {
        string mode = argv[1] ;
        if( mode == "--track-all"  || mode == "-t" )
        {
            track = 1 ;
        }
        else if( mode == "--untrack-all"  || mode == "-u" )
        {
            track = 2 ;
        }
        else if( mode == "--help" || mode == "-h" )
        {
            help() ;
            return 0 ; 
        }
        else
        {
            cerr << "Wrong mode" << endl ;
            return 1 ; 
        }
    }
    else if (argc > 2)
    {
        cerr << "Wrong Usage" << endl ;
        usage() ;
        return 1 ;
    }

    orchestrate(track) ;

    return 0 ;
}
