#include <iostream>
#include <exception>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;


// класс даты
class Date {
public:
Date (const int& new_year, const int& new_month, const int& new_day) {
if (new_month<1 || new_month>12){
	throw out_of_range("Month value is invalid: " + to_string(new_month));
}
if (new_day<1 || new_day>31) {
	throw out_of_range("Day value is invalid: " + to_string(new_day));
}
y = new_year;
m = new_month;
d = new_day;
}
Date(){
y = 1;
m = 1;
d = 1;
} 
int GetYear() const {
  return y;
}
int GetMonth() const{
  return m;
}
int GetDay() const{
  return d;
}

private:
string date;
int y;
int m;
int d;
};
///////////////////////////////////////////////////////////
bool operator<(const Date& lhs, const Date& rhs) {
if (lhs.GetYear() < rhs.GetYear()) {
  return true;
} else if (lhs.GetMonth() < rhs.GetMonth() && lhs.GetYear() == rhs.GetYear()) {   return true;
} else if (lhs.GetMonth() == rhs.GetMonth() && lhs.GetYear() == rhs.GetYear() &&lhs.GetDay() < rhs.GetDay()) {
  return true;
} else return false;
};
///////////////////////////////////////////////////////////
ostream& operator<<(ostream& stream, const Date& date){
	stream << setfill('0') << setw(4) << to_string(date.GetYear());
	stream << "-";
	stream << setfill('0') << setw(2) << to_string(date.GetMonth());
	stream << "-";
	stream << setfill('0') << setw(2) << to_string(date.GetDay());
	return stream;
}
///////////////////////////////////////////////////////////
istream& operator>>(istream& stream, Date& date){
	int year, month, day;
  string vvod;
  int defis =0;
	set<char> natural = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-' };

	stream >> vvod;

	for (int i=0; i<vvod.size(); ++i){
		if (natural.count(vvod[i]) == 0){
			throw runtime_error("Wrong date format: " + vvod);
		}
    if (vvod[i] == '-') {
      ++defis;
    }
    if (vvod[i] == '-' && vvod[i-1] == '-' && vvod[i-2] == '-') {
      throw runtime_error("Wrong date format: " + vvod);
    }
    if (vvod[vvod.size()-1] == '-' || vvod[0] == '-' ) {
      throw runtime_error("Wrong date format: " + vvod);
    }
	}
  
  if (defis>4 || defis<2){
    throw runtime_error("Wrong date format: " + vvod);
  }

  istringstream potok(vvod);
	potok >> year;
	potok.ignore(1);
	potok >> month;
	potok.ignore(1);
	potok >> day;

	date = Date(year, month, day);
	return stream;
}
///////////////////////////////////////////////////////////
class Database {
public:
void AddEvent(const Date& date, const string& event) {
	unit[date].insert(event);
}

bool DeleteEvent(const Date& date, const string& event) {
  if (unit[date].erase(event)>0) {
    return true;
  } else {
    return false;
  }
}

  int  DeleteDate(const Date& date) {
	int N = 0;
  try {
    	  N = unit.at(date).size();
    	  if (N > 0) {
    		  unit.at(date).clear();
    	  }
      } catch (exception) {}
    return N;
  }

set<string> Find(const Date& date) const  {
  set<string> findres;
  if (unit.count(date)>0){
  findres = unit.at(date);
  }
  return findres;
}

void Print() const {
  for (const auto& item: unit) {
    for (auto x: item.second) {
      cout << item.first << ' ' << x << endl; 
    }    
  }

}

private:
map<Date, set<string>> unit;
};
////////////////////////////////////////////////////
int main() {
  Database db;
  string command;
  while (getline(cin, command)) { 
  if (command.empty() || command == " ") continue;
  stringstream ss(command);
  string com;
  Date date;
  string event;
  
  try {
  ss >> com;
  if (com == "Add") {
    ss >> date >> event;
    if (event != "" && event != " ") {
    db.AddEvent(date, event);
    }
  } 
  else if (com == "Del"){
    ss >> date >> event;
    if (event.empty()) {
      cout << "Deleted " << db.DeleteDate(date) << " events" << endl;
    }
    else {
    if (db.DeleteEvent(date, event)){
      cout << "Deleted successfully" << endl;
    }
    else {
      cout << "Event not found" << endl;
    }
    }
  } else if (com == "Find") {
    ss >> date;
    set<string>buffer = db.Find(date);
    for (auto a:buffer) {
      cout << a << endl;
    }
  } else if (com == "Print") {
    db.Print();
  } else {
    cout << "Unknown command: " << com << endl;
    return 0;
  }}
  catch (out_of_range& out){
	cout << out.what() << endl;
	return 0;
	}
  catch (runtime_error& run){
	cout << run.what() << endl;
  return 0;
  }
  catch (exception& ex){
	cout << ex.what() << endl;
	return 0;
  }
  }
  return 0;
}
