
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

int main() {
   string password;
   bool validPassword = false;

   while (!validPassword) {
      try {
         cin >> password;

         if (password.length() < 8) {
            throw runtime_error("Invalid");
         }

         validPassword = true;
         cout << "Accepted" << endl;
      }
      catch (runtime_error& excpt) {
         cout << "Error: " << excpt.what() << endl;
      }
   }

   return 0;
}