#include<thread>
#include<iostream>
#include<mutex>
#include<future>
#include<chrono>

using namespace std;
int main(){
  cout << "I wonder If I'll get deleted..." << endl;

  auto inputThread = async(launch::async,[]() {
    while (cin.get() != '\n') {};
   //cin.get();
    });

  while (inputThread.wait_for(0ms)!= future_status::ready) {
    char symbols[] = { '-','\\','|','/' };
    for (int i = 0; i < 4; ++i) {
        if (inputThread.wait_for(50ms) == future_status::ready) break;

        //Making the first \r separate makes the output not freak out as much for some reason
        //cout << "\r\x1B[?25l\x1B[92m Press Enter to Continue... " << symbols[i] <<  "\x1B[K\r\x1B[?25l";// added escape sequence to clear everything after the cursor
        cout << "\r\x1B[?25l\x1B[92mPress Enter to Continue... " << symbols[i] << "\x1B[K";

        this_thread::sleep_for(chrono::milliseconds(50));//              The A is cursor up
        //moves cursure up 1 and sets color white
    }
  }
  cout << "\x1B[97m\x1B[?25h";

  cout << "Stall successfully ended";
  /// cin.ignore(255,'\n');
  string test;
  getline(cin, test);

  cout << test.size() << " characters left in the stream.\n";
}