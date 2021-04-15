#include <bits/stdc++.h> 
#include <openssl/sha.h> // For sha1
#include <thread> // For threading
#include <chrono>

long long cnt = 0;

struct hms {
	int hour = 0;
	int min = 0;
	int sec = 0;
};

hms hmsTime(int seconds); 
void powProcess(std::string authdata ,char suffixVars[] , int suffixVarsSizeMinusOne, int suffixLength);
  
// Main function
int main(int argc, char *argv[]) {  

    auto start = std::chrono::system_clock::now();
     
	char suffixVarsA[] = "abcdefghij";
	char suffixVarsB[] = "klmnopqrst";
	char suffixVarsC[] = "uvwxyzABCD";
	char suffixVarsD[] = "EFGHIJKLMN";
	char suffixVarsE[] = "OPQRSTUVWX";
	char suffixVarsF[] = "YZ~`!@#$%^";
	char suffixVarsG[] = "&*()-_=+{["; 
	char suffixVarsH[] = "]};:|<,.>?"; 
 
	std::string authdata = "eTSlASZYlLNgKJuYeIQvGVbiAcLEEOVgAQPzSrtCOIwQxQHyFHcfjgRQJBJDlojx";

    int suffixLength = strtol(argv[1], nullptr, 0); 

	std::thread tA(powProcess, authdata, suffixVarsA, (sizeof(suffixVarsA)-1), suffixLength);	
	//std::thread tB(powProcess, authdata, suffixVarsB, (sizeof(suffixVarsB)-1), suffixLength);	
	//std::thread tC(powProcess, authdata, suffixVarsC, (sizeof(suffixVarsC)-1), suffixLength);	
	//std::thread tD(powProcess, authdata, suffixVarsD, (sizeof(suffixVarsD)-1), suffixLength);	
	//std::thread tE(powProcess, authdata, suffixVarsE, (sizeof(suffixVarsE)-1), suffixLength);	
	//std::thread tF(powProcess, authdata, suffixVarsF, (sizeof(suffixVarsF)-1), suffixLength);	
	//std::thread tG(powProcess, authdata, suffixVarsG, (sizeof(suffixVarsG)-1), suffixLength);	
	//std::thread tH(powProcess, authdata, suffixVarsH, (sizeof(suffixVarsH)-1), suffixLength);

	tA.join();
	//tB.join();
	//tC.join();
	//tD.join();
	//tE.join();
	//tF.join();
	//tG.join();
	//tH.join();


    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
	int seconds = elapsed_seconds.count();
	struct hms runningDuration = hmsTime(seconds);  
	std::cout << "Running duration: " << runningDuration.hour << ":" << runningDuration.min << ":" << runningDuration.sec << std::endl;
	std::cout << cnt << std::endl;

	return 0;  
} 

void powProcess(std::string authdata ,char suffixVars[] , int suffixVarsSizeMinusOne, int suffixLength) {
	if (suffixLength == 0) { 
		// Here authdata = suffixAuthdata 
		// Because in the next for loop we set the first argument of powProcess (which is authdata) with suffixAuthdata.  
		unsigned char suffixAuthdataChar[authdata.length() + 1];
		// Note: we should use (char*) because we wan to convert string to unsigned char and NOT char. 
		strcpy((char*)suffixAuthdataChar, authdata.c_str());
		unsigned char hashValue[20];
		SHA1(suffixAuthdataChar,sizeof(suffixAuthdataChar),hashValue);
		cnt++;
		if ((hashValue[0] == 0) & (hashValue[1] == 0) & (hashValue[2] == 0) & (hashValue[3] == 0)) {
			for (int i = 0; i < 20; i++) {
				printf("%02x", hashValue[i]);
			} 
			std::cout << std::endl;
		}
		return;				 
	} 

	for (int i = 0; i < suffixVarsSizeMinusOne; i++) {
		std::string suffixAuthdata;           
		suffixAuthdata = authdata + suffixVars[i];        
		powProcess(suffixAuthdata, suffixVars, suffixVarsSizeMinusOne, suffixLength - 1);
	} 
  
} 
  
hms hmsTime(int seconds) {
	struct hms elapsedTime;	
	elapsedTime.hour = seconds/3600;
	seconds = seconds%3600;
	elapsedTime.min = seconds/60;
	seconds = seconds%60;
	elapsedTime.sec = seconds;
	return elapsedTime;
}








