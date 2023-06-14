
//By Abbas and Melisa

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;
bool isvalidcc(const string&);

//If the root folder contains all 3 cpp files, to run, we must temporally change the main() of two files that we do not want to run.
//For example, we would change main() of TikTakToe to Amain(), and creditCard to Bmain(), so there is one valid main() for dictionary.
//Otherwise, as there are multiple cpp files in this folder with main(), programs won't run.
//Run the cpp files we want to run, repeat the step and run the other programs.
//Ignore if there are no issues with multiple main() errors, or know a better way around this, or running files separately.

int mainB()
{
	vector<string> cardnumbers = {
	"371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
	"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
	"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
	"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
	"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
	"372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
	"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
	"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2) << i << " "
			<< setw(17) << *itr
			<< ((isvalidcc(*itr)) ? " is valid" : " is not valid") << endl;
	}

	return 0;
}
bool isvalidcc(const string& ccNumber) {
	int len = ccNumber.length();
	int sum = 0;

	for (int i = len - 2; i >= 0; i = i - 2) {
		int digit = ((ccNumber[i] - 48) * 2);
		if (digit > 9) {
			digit = (digit / 10) + (digit % 10);
		}
		sum += digit;
	}
	for (int i = len - 1; i >= 0; i = i - 2) {
		sum += (ccNumber[i] - 48);
	}
	return sum % 10 == 0;
}
