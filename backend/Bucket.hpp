#ifndef _BUCKET_H
#define _BUCKET_H

class Bucket {
public:

	//default constructor
	Bucket() : from(0), to(0) {}

	//constructor
	Bucket (int from_, int to_): from(from_), to(to_){}
	
	//[from:to] with count
	int from;
	int to;

	bool in(int n) {return (n >= from) && (n <= to);}

	bool operator>(const Bucket& other) {return from > other.from;}
    bool operator>=(const Bucket& other) {return from >= other.from;}
    bool operator<(const Bucket& other) {return from < other.from;}
    bool operator<=(const Bucket& other) {return from <= other.from;}
    bool operator==(const Bucket& other) {return (from == other.from) && (to == other.to);}
    bool operator!=(const Bucket& other) {return !(*this == other);}
};

#endif