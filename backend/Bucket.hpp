#ifndef _BUCKET_H
#define _BUCKET_H

class Bucket {
public:

	//default constructor
	Bucket() : from(0), to(0), count(0) {
	}

	//constructor
	Bucket (int low, int high, int cnt): from(low), to(high), count(cnt){
	}
	
	//[from:to] with count
	int from;
	int to;
	int count;
};

#endif