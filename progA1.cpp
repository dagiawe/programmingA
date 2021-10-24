
#include<iostream>
#include "version.h"
#include<string>

#include "version.cpp" 

using namespace std;






int main()
{
 


	displayVersion();


cout<<"i am making change for part 3"<<endl;

    //String for each part of the URL as well as temporary  
    string Protocol, Domain, DomainPort, PortString, Filepath, Parameters, temp, zcheck, ckeckdomain, Filepathcheck;
    //Boolean  for flaging errors
    bool errProtocol = false, errDomin = false, errFilePath = false, errPort = false, errDominzcheck = false, Portinvalid = false, errfilepathend = false;
    cout << "Enter any URL(valid/invalid)?" << endl;
    string urlin;//URL to be pearsed  
    cin >> urlin;
    Protocol = urlin.substr(0, urlin.find_first_of(":"));//geting the protocol by the substr


    if (Protocol == "http" || Protocol == "https" || Protocol == "ftp" || Protocol == "ftps")//cheack if the protocole is correct and flage  
        errProtocol = false;
    else
        errProtocol = true;



    temp = urlin.substr(urlin.find("://") + 3);//assigning  the urlin after the protocol to temp

    DomainPort = temp.substr(0, temp.find_first_of("/"));//geting the domian with the the portal if ther is any
    Domain = DomainPort.substr(0, DomainPort.find_last_of(":"));//separating the domain and assigning to in string  
    zcheck = Domain.substr(Domain.find_last_of(".") + 1);//geting the last part of the domain <z> to cheack if it is correct

    //using a while loop that loopes for every point "."
    string dom = Domain;
    int a = 0;
    while (dom.length() > Domain.substr(Domain.find_last_of(".")).length())
    {
        dom = dom.substr(dom.find(".") + 1);
        a++;
    }


    //chacking the zchaeck for the domain .but first chaking it it has the right form.if it is not right then flage

    if (Domain.find_first_of(".") != 0 && a == 2)
    {

        if ((zcheck == "com" || zcheck == "net" || zcheck == "biz" || zcheck == "edu" || zcheck == "gov"))
        {
            errDominzcheck = false;

        }
        else
        {
            errDominzcheck = true;

        }
    }
    else
    {
        if ((zcheck != "com" || zcheck != "net" || zcheck != "biz" || zcheck != "edu" || zcheck != "gov"))
        {
            errDominzcheck = true;
            errDomin = true;
        }
        else {
            errDomin = true;

        }

    }


    PortString = DomainPort.substr(DomainPort.find_last_of(":") + 1);//geting the port string only from the string domainport
    //which contain bothe the domain and the port

    int port = 0;//assinging 0 to the port so that i can know the if it has a port or not /
    /*at the time of output only*/
    if (PortString != DomainPort)//if it dosent have a port the substr function assignes the domainport value to the port string
    //using this to chaeck if it has a string form of port to convert to int
    {


        try
        {
            port = stoi(PortString);//changing the port string to int port using "stoi "from the string libraery

            if (port <= 65535 && port >= 1)//chaking the range and flaging
            {
                errPort = false;
            }
            else if (port > 65535 || port < 1)
            {
                errPort = true;

            }

        }
        catch (std::invalid_argument )//exsption to handel invalid inputs form the portal in the urlin
        { //if so flaging


            Portinvalid = true;

        }


    }

    //chaecking if the file path is acctaly in the urlin  
    if (temp.find_first_of("/") < temp.length())
    {
        temp = temp.substr(temp.find_first_of("/"));//assging the filepath and the parameter if any to the string temp
        //chacking if we have "/ " and "?' in the file path and?or paramert
        if (temp.find_last_of("?") < temp.length()) {


            if (temp.substr(temp.find_last_of("?")).find("/") < temp.substr(temp.find_last_of("?")).length())
            {
                Filepath = temp;//if we dont have parameter then  temp is filepath
                Parameters = "";//we dont have paramter
            }
            else
            {
                Filepath = temp.substr(0, temp.find_last_of("?"));//if we have paramter the assing the fillpath to its own and the preamenter it its own
                Parameters = temp.substr(temp.find_last_of("?") + 1);
            }

            //chaecking if the file name is acctualy valid  and flaging if it is not
            if (Filepath.find_last_of(".") < Filepath.length())
            {
                Filepathcheck = Filepath.substr(Filepath.find_last_of("."));
                if (Filepathcheck != ".html" && Filepathcheck != ".htm")
                {
                    errfilepathend = true;

                }
            }

        }
        else if (temp.find_last_of("?") > temp.length())//if ther is no "? then tehe file path will be all the way to the end from"/"
        {
            Filepath = temp.substr(temp.find_first_of("/"));

            if (Filepath.find_last_of(".") < Filepath.length())
            {
                Filepathcheck = Filepath.substr(Filepath.find_last_of("."));
                if (Filepathcheck != ".html" && Filepathcheck != ".htm")
                {
                    errfilepathend = true;

                }
            }
        }


    }
    else
    {
        //flaging if we dont have a file path inthe url
        errFilePath = true;
    }

    //managing what we flaged and out puting if ther is an error
    if (errProtocol != false || errDomin != false || errFilePath != false
        || errPort != false || errDominzcheck != false || Portinvalid != false ||
        errfilepathend != false) {
        cout << "Invalid URL with following erroneous components:" << endl;

        if (errProtocol)
        {
            cout << "ERROR on Protocol     " + Protocol << endl;
        }
        if (errDomin)
        {
            cout << "ERROR on Domain form   " + Domain << endl;
        }
        if (errDominzcheck)
        {
            cout << "ERROR ON Domain <Z>  : " + zcheck + "   isinvalid" << endl;

        }
        if (errFilePath)
        {
            cout << "ERROR ON FilePath  : FilePath not found isinvalid" << endl;
        }
        if (errfilepathend)
        {
            cout << "ERROR ON filepathend  : " + Filepathcheck + "    isinvalid" << endl;
        }
        if (Portinvalid)
        {
            cout << "port is invalid(is not an intger)" + PortString << endl;
        }
        if (errPort)
        {
            cout << "ERROR on Port(not on the range) :  ";
            cout << port;
            cout << " ->port number must be between 1 and 65535" << endl;
        }
    }
    else
    {
        //if ther is no error then display the parts of the url


        cout << "Protocol:     " + Protocol << endl;
        cout << "Domain:       " + Domain << endl;
        if (port != 0)//chaking if we have a pota illustrated above
        {
            cout << "Port:         ";
            cout << port << endl;
        }
        cout << "File path :   " + Filepath << endl;
        if (!Parameters.empty())//chaeacking if we have parameters
        {
            cout << "Parameters:   " + Parameters << endl;
        }

    }

}
