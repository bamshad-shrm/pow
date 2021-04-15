#include <bits/stdc++.h> 
#include <openssl/sha.h> // For sha1
#include <chrono> 

struct hms {
	int hour = 0;
	int min = 0;
	int sec = 0;
};

hms hmsTime(int seconds); 
void powProcess(std::string authdata ,char suffixVars[] , int suffixVarsSizeMinusOne, int suffixLength);
long long cnt = 0;
  
// Main function
int main(int argc, char *argv[]) {
    auto start = std::chrono::system_clock::now();       
    char suffixVars[] = "abcdefghij"; 
    int suffixLength = strtol(argv[1], nullptr, 0); 
	std::string authdata = "eTSlASZYlLNgKJuYeIQvGVbiAcLEEOVgAQPzSrtCOIwQxQHyFHcfjgRQJBJDlojx";
    powProcess(authdata, suffixVars, (sizeof(suffixVars)-1), suffixLength); 
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
		if ((hashValue[0] == 0) & (hashValue[1] == 0) & (hashValue[2] == 0) & (hashValue[3] == 0)) {
			for (int i = 0; i < 20; i++) {
				printf("%02x", hashValue[i]);
			} 
			std::cout << std::endl;
		}
		cnt++;
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







