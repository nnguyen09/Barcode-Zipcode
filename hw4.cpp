/***********************************************
Author: <Ngan Nguyen>
Date: <09/28/2020>
Purpose: <encode and decode bar zipcode>
Sources of Help: <cplusplus library, lecture 567>
Time Spent: <10 hours >
***********************************************/

/*
Computing III -- COMP.2010 Honor Statement
The practice of good ethical behavior is essential for maintaining
good order in the classroom, providing an enriching learning
experience for students, and as training as a practicing computing
professional upon graduation. This practice is manifested in the
University’s Academic Integrity policy. Students are expected to
strictly avoid academic dishonesty and adhere to the Academic
Integrity policy as outlined in the course catalog. Violations will
be dealt with as outlined therein.
All programming assignments in this class are to be done by the
student alone. No outside help is permitted except the instructor and
approved tutors.
I certify that the work submitted with this assignment is mine and was
generated in a manner consistent with this document, the course
academic policy on the course website on Blackboard, and the UMass
Lowell academic code.
Date: Ngan Nguyen   
Name: 09/28/2020
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ZipCode{
public:
    //constructors 
    ZipCode(int zip):zipcode(zip){
    }     //take input zipcode as an integer
    ZipCode(string bar){
        int i=1;
        int countMistake=0;
        if(bar[0]!='1'||bar[26]!='1'){
            cout<<"Wrong start/end character in the barcode!\n";
        }
        while(i<26){
            if(bar[i]!='0'&&bar[i]!='1')
                countMistake++;
            i++;
        }     
        if(countMistake!=0){
            cout<<"Wrong barcode! A barcode can only contain '0' and '1'.\n";
        }
        zipcode=toZipCode(bar);
    }    //input bar code as a string 
    
    
    int getZipCode(void){
        return zipcode;
    }
    string getBarCode(void){
        
        return toBarcode();
    }
    

private:
    string barcode; 
    int zipcode; 
    string toBarcode(void);
    int toZipCode(string bar); 
    string getSum( int x, string bar);   
};


int main(int argc, char * argv[]) {
    ZipCode zip(99504),
    zip2("100101010011100001100110001"), 
    zip3(12345),
    zip4(67890);
    
    cout << zip.getZipCode() << "'s bar code is '"
    << zip.getBarCode() << "'" << endl;
    cout << zip2.getZipCode() << "'s bar code is '"
    << zip2.getBarCode() << "'" << endl;
    cout << zip3.getZipCode() << "'s bar code is '"
    << zip3.getBarCode() << "'" << endl;
    cout << zip4.getZipCode() << "'s bar code is '"
    << zip4.getBarCode() << "'" << endl;
    
    cout << endl;
    
    // Test a range of values by first constructing a zip code
    // with an integer, then retrieving the bar code and using
    // that to construct another ZipCode.
    int zip_int = 0;
    for (int i = 0; i < 25; i++)
    {
        // Make an aribrary 5-digit zip code integer, and use it
        // to construct a ZipCode
        int five_digit_zip = (zip_int * zip_int) % 100000;
        ZipCode z1(five_digit_zip);
        
        // Construct a second ZipCode from the first's bar code
        string z1_barcode = z1.getBarCode();
        ZipCode z2(z1_barcode);
        
        cout.width(3);
        cout << (i + 1) << ": ";
        cout.width(5);
        cout << z2.getZipCode() << " has code '"
        << z1_barcode << "'";
        
        if ((z1_barcode == z2.getBarCode()) &&
            (z1.getZipCode() == z2.getZipCode()) &&
            (z2.getZipCode() == five_digit_zip))
        {
            cout << " [OK]" << endl;
        }
        else
        {
            cout << " [ERR]" << endl;
        }
        
        // Increment the test value arbitrarily
        zip_int += (233 + zip_int % 7);
    }
    cout << endl;
    
    // Test some error conditions. This test assumes that
    // ZipCode will simply set its value to a flag that indicates
    // an error, and will not exit the program.
    int BAD_ZIP_COUNT = 2;
    string bad_zips[][2] = {
        { "100101010011100001100110000", "bad start/end character" },
        { "100101010011100001100110021", "bad digit" },
    };
    for (int i = 0; i < BAD_ZIP_COUNT; i++)
    {
        cout << "Testing: " << bad_zips[i][1] << " " << bad_zips[i][0] << endl;
        ZipCode test(bad_zips[i][0]);
        cout << endl;
    }
    
    cout << "Enter a character to quit." << endl;
    char c;
    cin >> c;
    return 0;

}

//zipcode to barcode 
string ZipCode::toBarcode (void){
    string temp = to_string(zipcode);
    string temp2 = "00000";
    barcode += "1";
    int i = 0;
    int m = 4;
    if(temp.length()<5){
        for(int j= temp.length(); j<5; j++)
            temp[j]+='0';

        for(int k =0; k<5; k++){
            temp2[k] = temp[m];
            m--;
        }
        temp=temp2;
    }
    while(i<temp.length()){
        switch(temp[i]){
            case '0': barcode += "11000";
                break;
            case '1': barcode += "00010";
                break;
            case '2': barcode += "00100";
                break;
            case '3': barcode += "00110";
                break;
            case '4': barcode += "01001";
                break;
            case '5': barcode += "01010";
                break;
            case '6': barcode += "01100";
                break;
            case '7': barcode += "10001";
                break;
            case '8': barcode += "10010";
                break;
            case '9': barcode += "10100";
                break;
        }
        i++;
    }
   return  barcode+= "1"; 

}

//change barcode to zipcode 
int ZipCode::toZipCode(string bar){
    int i=0;
    int j=0;
    int l = bar.length()-2;
    string strZ;
    while(i<l){
        strZ+=getSum(i, bar);
        i+=5;
    }
    return zipcode = atoi(strZ.c_str());
}

//help decoding string bar
string ZipCode::getSum( int x, string bar){
    string strSum;
    int sum =0;
            if(bar[x+1]=='1')
                sum+=7;
            if(bar[x+2]=='1')
                sum+=4;
            if(bar[x+3]=='1')
                sum+=2;
            if(bar[x+4]=='1')
                sum+=1;
            if(bar[x+5]=='1')
                sum+=0;
            if(sum==11)
                sum = 0;
    return strSum = to_string(sum);
}
            




