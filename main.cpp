#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <ios>

using namespace std;

// This code converts Roman numerals to their corresponding Arabic numbers and vice versa

// The "database" variable is set to the name of the text file that will be used to store the data.
const string database = "numbers.txt"; 

// The "RomanToArabic" function takes a string (representing a Roman numeral) and converts it to an Arabic number.
int RomanToArabic(string line){
    // Create a map to store the relationship between Roman numerals and Arabic numbers
    map<char, int> romanValues = {{'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
    
    int arabicNumb = 0; // Will be holding the arabic values
    long unsigned int i; 
    
    // The function uses a loop to go through each character in the string and checks its value.
    // Depending on the value, the function adds the corresponding Arabic number to a total.
    for(i = 0; i < line.size(); i++){
        // If the current character is smaller than the next character, subtract its value from the total
        if(romanValues[line[i]] < romanValues[line[i+1]]){
            arabicNumb -= romanValues[line[i]];
        }
        // Otherwise, add its value to the total
        else{
            arabicNumb += romanValues[line[i]];
        }
    }
    
    // The total is then returned as the Arabic number equivalent of the Roman numeral.
    return arabicNumb;
}

// This function takes in an Arabic numeral as an int and 
// converts it to its equivalent Roman numeral in the form of a string.
string arabicToRoman (int arabicNumb){
    // Create a map to store the relationship between Arabic numbers and Roman numerals
    map<int, string> arabicValues = {{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
    
    string romanNumb; // Will be holding the roman values
    
    // Iterate through the map in reverse order (from largest to smallest)
    for(auto it = arabicValues.rbegin(); it != arabicValues.rend(); it++){
        // While the current Arabic number can be subtracted from the input number
        while(arabicNumb >= it->first){
            // Subtract the current Arabic number from the input number
            arabicNumb -= it->first;
            // Add the corresponding Roman numeral to the result string
            romanNumb += it->second;
        }
    }
    
    return romanNumb;
}

/*
The overall function takes in a string of a line from an input file and checks if it is a valid line by checking if the first 17 characters 
are Roman numerals and the last 4 characters are digits. If both conditions are met, the function returns true, 
indicating that the line is valid. If either of the conditions are not met, the function returns false.
*/
bool isValid(string line){
    for(int i = 0; i < 17; i++){
        char ch = line[i];
        if(ch == 'I' || ch == 'V' || ch == 'X' || ch == 'L' || ch == 'C' 
        || ch == 'D' || ch == 'M'){
            return true;
            
            break;
            }
    }
        // Check if the last 4 characters are digits
    for(int i = 17; i < 21; i++){
        char ch = line[i];
        if(isdigit(ch)){
            return true;
            break;
        }
    }
    
    return false;
}

int main(){
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
   string temp;  //variable for database filename
   string batch; //variable for batch filename

   cout<<"Enter File Name: ";
   cin>>temp;

   ifstream infile(temp, ios::binary);
   ofstream outfile(database, ios::binary);
   string line;
   if (infile)
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
                outfile << line << "\n";
        }

   infile.close();
   outfile.close();
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
    
    infile.open(temp, ios::binary);
    outfile.open(database, ios::binary | ios::ate);
    
    char ch;
    int arabicNumb; // Holds the arabic numbers
    bool isRoman = false;
    bool isArabic = false;
    

    if(infile){
        
        //The "getline" function reads a line from the input file (infile) and stores it in the string "line". 
        //The while loop will continue to execute as long as there are lines left to read in the input file.
        
        while(getline(infile, line)){
    
            stringstream lineStream(line);
        
            while(lineStream >> ch){
            
                if((isdigit(ch))){ // If it's a digit, set the "isArabic" flag to true.
                
                    isArabic = true;
                
                }
                if(ch == 'I' || ch == 'V' || ch == 'X' || ch == 'L' || ch == 'C' 
                || ch == 'D' || ch == 'M'){ // If it's a Roman numeral character, set the "isRoman" flag to true.
                    isRoman = true;
                }

            }
            
                
            
            if(!line.empty() && line[0] == ' '){
// If the line is not empty and the first character is a space
                
                if(isArabic){
                    // This will try to convert the string "line" into an integer.
                    try{
                        line = line.substr(16);
                        arabicNumb = stoi(line);
                        line = arabicToRoman(arabicNumb);
                    }
                    // If any error is caused, then it will not proceed but will make string "line" a blank space instead
                    catch(const std::invalid_argument& ia){
                        line = " ";
                    }
                }
            }
            else{
            
            // If it's a Roman numeral, the "RomanToArabic" function is called to convert it to an Arabic number.
            
                if(isRoman){
                arabicNumb = RomanToArabic(line);
                }        
            }
       
            string romanNumeral = line;
    
            if(isRoman){
            
                arabicNumb = RomanToArabic(line);
                
                // This adds the necessary lines in the roman numeral field to keep each line the same length
                
                int spaces = 17 - romanNumeral.length();
                
                for(int i = 0; i < spaces; i++){
                romanNumeral += " ";
                }
            }
            if(isValid(line)){
                string arabicNumeral = to_string(arabicNumb);
                
                // This adds the necessary lines in the arabic numeral field to keep each line the same length

                int spaces = 4 - arabicNumeral.length();
    
                for(int i = 0; i < spaces; i++){
                    
                    // Add spaces to the front of the arabic numeral string until it reaches the desired length.
                    
                    arabicNumeral = " " + arabicNumeral;
                }
                
                // Output the Roman numeral and the Arabic numeral to the output file.
                
                outfile << setw(17) << left << arabicToRoman(arabicNumb) << setw(4) << left << arabicNumb << endl; 
            }
            else{
                // If the line contains any invalid characters, then the line will be overwritten by 21 spaces
                outfile << "                     " << endl;             
                
            }

            
            
    
        }
    
    }
    else{ // If file fails to open, output this
        cout << "Error. File failed to open." << endl;
    }
    
    infile.close();
    outfile.close();
    
    return 0;
}