#include <stdio.h>
#include<iostream>
#include <vector>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctime>
#include <algorithm>

using namespace std;

void displayVect(vector<string>& vect) {

    cout << endl;

    for (int i = 0; i < vect.size(); i++) {
        cout << vect[i] << endl;
    }

    cout << endl;

}

string trimSpace(string &str) {

    string resultStr;

    for (int i = 0; i < str.length();) {
        if (str[i] == ' ') {
            if (i == str.length() || i == 0) {
                i++;
                continue;
            }

            while (str[i + 1] == ' ') {
                i++;
            }
        }
        resultStr += str[i++];
    }

    return resultStr;
}

bool isCharBetweenChars (string line, char charToFind, char begChar, char endChar) {

    int starPos = 0;
    int endPos = 0;

    for (int i = 0; i < line.size(); i++) {
        if (line[i] == begChar) {
            starPos = i;
            break;
        }
    }

    for (int i = line.size(); i >= 0; i--) {
        if (line[i] == endChar) {
            endPos = i;
            break;
        }
    }

    for (int i = starPos; i < endPos; i++) {
        if (line[i] == charToFind) {
            return true;
        }
    }

    return false;

}

vector<string> partSplit (string line, char separator){ // copied from common.cpp from PA 1
	vector<string> result;

    int startQuo = 0;
    int endQuo = 0;
    int quotePos;

    string cutQuo = "";




    if (line.find('<') != string::npos) {

        if (line[line.find('<') + 1] != ' ') {
            line.insert(line.find('<') + 1, " ");
        }

        if (line[line.find('<') - 1] != ' ') {
            line.insert(line.find('<') - 1, " ");
        }
        
    }


    if (line.find('>') != string::npos) {

        if (line[line.find('>') + 1] != ' ') {


            line.insert(line.find('>') + 1, " ");
        }

        if (line[line.find('>') - 1] != ' ') {


            line.insert(line.find('>') - 1, " ");
        }
 
        
    }



    // size_t quotation = line.find_first_of("\"\'");
    if (line.find('\'') != string::npos || (line.find('\"') != string::npos)) {
        // cout << "Found quotation at: " << quotation << endl;

        for (int i  = 0; i < line.size(); i++) {
            if (line[i] == '\'' || line[i] == '\"') {
                startQuo = i;
                // cout << "Starting quo: " << startQuo << endl;
                break;
            }
        }

        for (int i = line.size(); i >= 0; i--) {
            if (line[i] == '\'' || line[i] == '\"') {
                endQuo = i;
                // cout << "Ending quo: " << endQuo << endl;
                break;
            }
        }

        for (int i = startQuo; i <= endQuo; i++) {
            cutQuo+=line[i];
        }

            // cout << "SUBSTR W QUOTES: " << cutQuo << endl;

        quotePos = line.find(cutQuo);

        line.erase(quotePos, cutQuo.size());

        // cout << "Position that CUTQUO was erased: " << quotePos << endl;


        // cout << "RESULT VECTOR OUTPUT: ";

        // for (int i = 0; i < result.size(); i++) {
        //     cout << result[i] << " ";
        // }

        // cout << endl;


        // cout << "RESULTS VECTOR SIZE: " << result.size() << endl;

    }

    // bool isFlagExist = false;


    // if (line.find("-e") != string::npos) {

    //     isFlagExist = true;

    // } else {
    //     isFlagExist = false;
    // }

    



        // cout << "Line after quote erasure is: " << line << endl;
        



	while (line.size()){

        
		size_t found = line.find_first_of (separator);
        

		if (found!=std::string::npos){

			string part = line.substr(0, found);
            // cout << part << endl;
			result.push_back(part);
			line = line.substr (found+1);
		}
		else{
			result.push_back (line);
			break;
		}
    }

    int counter = 0;
    // int eFlagPos = 0;


    if (cutQuo != "") {


        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[i].size(); j++) {
                // cout << result[i][j] << " ";
                counter++;

                
                if (counter == (quotePos - 1)) {

    

                    result.insert(result.begin() + (1+i), cutQuo);
                    break;
       
                }
            }
        }
        // result.push_back(cutQuo);

    
        // cout << "PUSH BACKED!" << endl;

        // for (int i = 0; i < result.size(); i++) {
        //     cout << result[i] << " ";
        // }

        // cout << endl;
    }

    // cout << endl;

    // cout << endl;



    // cout << endl;

    // cout << "CharCount = " << counter << endl;

    const char *pathDirectory = getenv("PATH");


    for (int i = 0; i < result.size(); i++) {
        if (result[i] == "-e" && ((cutQuo[0] == '\'')|| (cutQuo[0] == '\"'))) {
            result.insert(result.begin() + (1 + i), cutQuo);
        }

        if (result[i] == "$PATH" || result[i] == "\"PATH\"" || result[i] == "\'PATH\'") {
            result[i] = pathDirectory;
        }
    }

    // displayVect(result);



    

    // cout << endl;


    // result.push_back(cutQuo);
    
	return result;
}


vector<string> pipeSplit (string line, char separator){ // copied from common.cpp from PA 1
	vector<string> result;

                // vector<string> pipeVect = pipeSplit(trimSpace(inputline), '|');



    if (isCharBetweenChars(line, '|','\'','\'')) {

        result = partSplit(trimSpace(line), ' '); 







        // cout << "yes" << endl;



        return result;
    }

    if (isCharBetweenChars(line, '|','\"','\"')) {
        result = partSplit(trimSpace(line), ' '); 


        // cout << "Display results vector with double qyotes: " << endl;

        // displayVect(result);





        // cout << "yes" << endl;
        return result;
    }



	while (line.size()){

        
		size_t found = line.find_first_of (separator);
        

		if (found!=std::string::npos){

			string part = line.substr(0, found);
            // cout << part << endl;
			result.push_back(part);
			line = line.substr (found+1);
		}
		else{
			result.push_back (line);
			break;
		}
    }


    
	return result;
}






int main (){

    time_t now = time(0);
    char* dt = ctime(&now);

    string dateTime = dt;

    // int input = dup(0);
    // int output = dup(1);

    dup2(0, 10);

    // cout << dateTime

    dateTime.erase(remove(dateTime.begin(), dateTime.end(), '\n'), dateTime.end());


    // dateTime.erase(remove(dateTime.begin(), dateTime.end(), '\n'), dateTime.end());

    vector<string> parts;
    vector<int> process;

    

    const char *homeDirectory = getenv("USER");

    char* directory[1024];




    // const char* env_p = getenv("PATH");

    while (true){


        char directory[1024];
        // string currentDirect = getcwd(directory, sizeof(directory));

        // dup2(input, 0);
        // dup2(output, 1);

        dup2(10, 0);

        cout << "My Shell:" << homeDirectory << ":" << dateTime << "$ "; 
        // cout << "My Shell$ ";

        string inputline;
        getline (cin, inputline);   // get a line from standard input

        // int startQuo;
        // int endQuo;

        string combinedStr = "";

        char doubleQuo = '\"';
        char singleQuo = '\'';

        // vector<int> process;

        for (int i = 0; i < process.size(); i++) {
            if(waitpid(process[i], 0, WNOHANG) == process[i]) {
                process.erase(process.begin() + i);
                i--;
            }
        }

        bool isBackgroundExist = false;

        if (inputline == string("exit")){
            cout << "Bye!! End of shell" << endl;
            break;
        } else {
        
            vector<string> pipeVect = pipeSplit(trimSpace(inputline), '|');


            // for (int i = 0; i < pipeVect.size(); i++) {
            //     cout << pipeVect[i] << " ";
            // }

            // cout << endl;

            // cout << "PIPEVECT DISPLAY: " << endl;

            // displayVect(pipeVect);

        


            // parts = split(trimSpace(inputline), ' ');




            for (int i = 0; i < pipeVect.size(); i++) {
                int fd[2];
                pipe(fd);

                inputline = trimSpace(pipeVect[i]);

                // cout << "INPUT AFTER PIPEVECT BEFORE PARTSVECT: " << inputline << endl;

                // parts = partSplit(trimSpace(inputline), ' ');

                // // displayVect(parts);

                // // cout << "bruh it gets here" << endl;  

                // cout << "parts[parts.size() - 1]: " << parts[parts.size() - 1] << endl; 

                // cout << "Parts vector: " << endl;

                // displayVect(parts); 

            

                if (parts[parts.size() - 1] == "&") {

                    // cout << "bruh this shiut dont woerk" << endl;
                    isBackgroundExist = true;
                    parts.erase(parts.begin() + (parts.size() - 1));
                }


                int pid = fork();

                if (!pid) {


                    if (parts[0] == "echo") {

                        // const char *pathDirectory = getenv("PATH");

                    

                        for (int j = 0; j < parts.size(); j++) {
                            if (parts[j][0] == '\"' || parts[j][0] == '\'') {

                                parts[j] = parts[j].substr(1, parts[j].size() - 2);
                                break;
                            }
                        }



                    }


                    if (parts[0] == "awk") {

                        for (int j = 0; j < parts.size(); j++) {
                            if (parts[j][0] == '\"' || parts[j][0] == '\'') {

                                parts[j] = parts[j].substr(1, parts[j].size() - 2);
                                break;
                            }
                        }
                    }




                    if (parts[0] == "cd") {

                        char tempDir[1024];
                    
                        if (parts.size() == 1) {
                            getcwd(directory, sizeof(directory));
                            chdir("/home");
                        } else if (parts[1] == "-") {

                            getcwd(tempDir, sizeof(tempDir));

                            chdir(directory);

                            for (int i = 0; i < (sizeof(tempDir)/sizeof(tempDir[0])); i++) {
                                directory[i] = tempDir[i];
                            }

                        } else {
                            getcwd(directory, sizeof(directory));
                            chdir(parts[1].c_str());

                        }

                    }


                    if (find(parts.begin(), parts.end(), ">") != parts.end()) {

                        int index = (find(parts.begin(), parts.end(), ">")) - parts.begin();

                        string fileName = parts[index + 1];

                        parts.erase(parts.begin() + index);
                        parts.erase(parts.begin() + index);

                        int fdDup = open(fileName.c_str(), O_WRONLY | O_CREAT | O_RDONLY, S_IWUSR | S_IRUSR);

                        dup2(fdDup, 1);
                        close(fdDup);

                    }

                    if (find(parts.begin(), parts.end(), "<") != parts.end()) {


                        int index = (find(parts.begin(), parts.end(), "<")) - parts.begin();

                        string fileName = parts[index + 1];

                        parts.erase(parts.begin() + index);
                        parts.erase(parts.begin() + index);

                        int fdDup = open(fileName.c_str(), O_RDONLY | O_CREAT, S_IWUSR | S_IRUSR);
                        dup2(fdDup, 0);
                        close(fdDup);
                    }

                    if (i < pipeVect.size() - 1) {
                        dup2(fd[1], 1);
                        close(fd[1]);
                    }
                    

                    char* args [parts.size() + 2] = {NULL};

                    // args[parts.size() + 2] = NULL;

                    // displayVect(parts);

            

                    for (int i = 0; i < parts.size(); i++) {
                        args[i] = (char *)parts.at(i).c_str();
                        // cout << args[i] << " ";
                    }


                    // cout << "PART VECTOR DISPLAY: ";

                    // displayVect(parts);


                    execvp (args [0], args);

                }else{

                    if (isBackgroundExist == false) {
                        if (i == pipeVect.size() - 1) {
                            waitpid(pid, 0, 0);
                        } else {
                            process.push_back(pid);
                        }
                        // waitpid (pid, 0, 0); 


                    } else {
                        process.push_back(pid);
                    }

                    dup2(fd[0], 0);
                    close(fd[1]);
                    
                    // we will discuss why waitpid() is preferred over wait()
                }


            }
            
        }

    }
}