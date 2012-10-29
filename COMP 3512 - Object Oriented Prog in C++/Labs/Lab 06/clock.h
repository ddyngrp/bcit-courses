/*
 *  clock.h
 *  Lab 06
 *
 *  Created by Steffen L. Norgren on 21/10/08.
 *  Copyright 2008 Esurient Systems Inc.. All rights reserved.
 *
 */

class Clock {
public:
	Clock(int hour = 0, int min = 0);
	
	Clock(const std::string& s) {
		int hour, min;
		char seperator;		
		std::istringstream iss(s);
		
		if (!(iss >> hour >> seperator >> min)) {
			std::cout << "Clock::Clock(" << s << "): invalid arguments form(H:M)" << std::endl;
		}
		
		if (hour > 24 || hour < 0 || min > 59 || min < 0) {
			std::cout << "Clock::Clock(" << s << "): invalid arguments form(H:M)" << std::endl;
		}
		else {
			hour_ = hour;
			min_ = min;
		}
	}
	
	// compiler-generated copy ctor, dtor & assignment operator
	Clock& operator++() {	// increment by 1-minute (prefix)
		if (++min_ > 59) {
			min_ = 0;
			if (++hour_ > 23) {
				hour_ = 0;
			}
		}
		return *this;
	}
	
	Clock operator++(int) {	// increment by 1-minute (postfix)
		Clock copy(*this);
		++*this;
		return copy;
	}
	
//	~Clock& operator++(int) {	// destroy our copy
//		free(copy);
//	}
	
	void print() const {	// print as a 12-hour clock
		std::cout << std::setfill('0');
		if(hour_ > 11) {
			std::cout << std::setw(2) << hour_ -12 << ":"
				<< std::setw(2) << min_ << "PM" << std::endl;
		}
		else {
			int hourMod = 0;
			if (hour_ == 0) {
				hourMod = 12;
			}
			std::cout << std::setw(2) << hour_ + hourMod << ":"
				<< std::setw(2) << min_ << "AM" << std::endl;
		}
		std::cout << std::setfill(' ');
	}
	
	// add friend declaration for comparison operators & operator<<
	friend bool operator == (const Clock& clock1, const Clock& clock2);
	
	friend bool operator != (const Clock& clock1, const Clock& clock2);
	
	friend std::ostream& operator << (std::ostream& os, const Clock& clock);
	
private:
	int hour_;	// 0 - 23
	int min_;	// 0 - 59
};

// non-member comparison operators: ==, !=
bool operator == (const Clock& clock1, const Clock& clock2) {
	if (clock1.hour_ != clock2.hour_ || clock1.min_ != clock2.min_) {
		return false;
	}
	return true;
}

bool operator != (const Clock& clock1, const Clock& clock2) {
	return !(clock1==clock2);
}

std::ostream& operator << (std::ostream& os, const Clock& clock) {
	os << std::setfill('0');
	
	os << std::setw(2) << clock.hour_ << ":"
		<< std::setw(2) << clock.min_;
	
	os << std::setfill(' ');
	return os;		
}
