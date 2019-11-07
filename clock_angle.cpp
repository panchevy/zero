#include <iostream>
#include <string>
using namespace std;

 

// prototypes:
bool getTime(string t, int *h, int *m);
void getAngle(string *t, int h, int m);

int main()
{
	string time = "";
	int hour = 0;
	int minutes = 0;

	while (true)
	{
		cout << "E to Exit" << endl;
		cout << "Enter any time of day" << endl;
		cout << "Examples: 3, 11, 8:25" << endl;
		cout << "Time: ";

		getline(cin, time);

		if (time == "E")
		{
			exit(1);
		} 

		if (getTime(time, &hour, &minutes))
		{
			getAngle(&time, hour, minutes);
		}
	}

	system("pause");
	return 0;

} // End Main

// getTime returns true if valid time, and stores hours and minutes in h and m respectively
// else returns false, and displays error message.
bool getTime(string t, int *h, int *m)
{
	string tempHour = "";
	string tempMin = "";
	bool atToken = false; // true when ':' is reached.

	
	// if time was entered in hours only, assume minutes == 0
	if (t.length() <= 2)
	{
		if ((t.length() == 2 && isdigit(t[0]) && isdigit(t[1])) ||
			t.length() == 1 && isdigit(t[0]))
		{
			if (t == "12")
			{
				*h = 0;
				*m = 0; 
			}
			else
			{
				*h = stoi(t);
				*m = 0;
			}


			return 1;
		}
		else { goto Error; }
	}

	// Loop through string time
	for (int i = 0; i < t.length(); i++)
	{
		if (t[i] == ':')
		{
			atToken = true; 
			continue;
		}
		if (isdigit(t[i]) && !atToken)
		{
			tempHour += t[i];
		}
		else if (isdigit(t[i]) && atToken)
		{
			tempMin += t[i];
		}
		else { goto Error; }
	}
	if (stoi(tempHour) <= 12 && stoi(tempMin) < 60)
	{
		*h = stoi(tempHour);
		*m = stoi(tempMin);
	}
	else { goto Error; }

	return 1;

	Error:
		cout << "\'" << t << "\'" << " is not a valid time. Please try again." << endl;
		cout << endl;

		return 0;

}

void getAngle(string *t, int h, int m)
{
	double angleBetween = 0;
	double minDegs = 0;
	double hrDegs = 0;


	// Get angle in degrees of minute hand by multiplying
	// minutes by 6 (each minute is 6 degrees).
	minDegs = m * 6;

	// get angle in degrees of hour hand by dividing half
	// the minutes by 30 (the hour hand moves 30 degrees
	// per hour), adding the result to the hours, and
	// multiplying by 30.
	hrDegs = (((0.5 * m) / 30) + h) * 30;

	// Get the angle between the two hands by finding the 
	// difference between the larger angle and the smaller
	// angle.
	if (hrDegs > minDegs)
	{
		angleBetween = hrDegs - minDegs;
	}
	else
	{
		angleBetween = minDegs - hrDegs;
	}

	cout << "The angle between the hour hand and the minute hand at " << *t << " is: ";
	cout << angleBetween << " degrees" << endl;
	cout << endl;

}