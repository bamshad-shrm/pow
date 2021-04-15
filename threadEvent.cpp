// Compile command:
// g++ threadEvent.cpp -pthread -o threadEvent

#include <iostream>
#include <unistd.h> // For usleep()
#include <thread> // For threading
#include <ctime> // For time()
#include <string> // For rand() 
#include <vector> // For vector

using namespace std;

bool continueThread  = true;

void process(int);

int main() {

	int numberOfThreads = 3;
	vector<thread *> z;

	for (int i = 0; i < numberOfThreads; ++i) {
		z.push_back(new thread(process,continueThread));
	}

	for (int i = 0; i < numberOfThreads; ++i) {
		z[i]->join();
	}

	if (!continueThread) {
		cout << "Killing the threads" << endl;
		for (int i = 0; i < numberOfThreads; ++i) {
			delete z[i];
		}
	}
 
}

void process(int) {
	std::thread::id this_id = std::this_thread::get_id();
	srand(time(0));
	int randomNumber;
	while(continueThread) {
		randomNumber = rand() % 10;
		cout << this_id << " " << continueThread << " " << randomNumber << endl;
		/* 
			We must use usleep otherwise the threads would not work at the same time.
			First t1 will perform and then t2.
		*/
		usleep(10); // Sleep for 10 microseconds.
		if(randomNumber == 7) {
			continueThread = false;
			break;
		}
	}
}





