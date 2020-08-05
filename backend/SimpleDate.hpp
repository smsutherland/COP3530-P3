#pragma once

#include <string>

struct SimpleDate{
    int year = 0;
    int month = 0;
    int day = 0;

    SimpleDate(int year_ = 0, int month_ = 0, int day_ = 0) : year(year_), month(month_), day(day_) {}
    SimpleDate(std::string str);
    //SimpleDate(const SimpleDate& other) : year(other.year), month(other.month), day(other.day) {}
    
    bool operator>(const SimpleDate& other);
    bool operator>=(const SimpleDate& other);
    bool operator<(const SimpleDate& other);
    bool operator<=(const SimpleDate& other);
    bool operator==(const SimpleDate& other);
    bool operator!=(const SimpleDate& other);
};

SimpleDate::SimpleDate(std::string str){
    month = stoi(str.substr(0, 2));
    day = stoi(str.substr(3,5));
    year = stoi(str.substr(6, 10));
}

bool SimpleDate::operator>(const SimpleDate& other){
    if(year != other.year){
        return year > other.year;
    }
    if(month != other.month){
        return month > other.month;
    }
    if(day != other.day){
        return day > other.day;
    }
    return false;
}

bool SimpleDate::operator>=(const SimpleDate& other){
    return (*this > other) || (*this == other);
}

bool SimpleDate::operator<(const SimpleDate& other){
    return !(*this > other) && (*this != other);
}

bool SimpleDate::operator<=(const SimpleDate& other){
    return (*this < other) || (*this == other);
}

bool SimpleDate::operator==(const SimpleDate& other){
    return (year == other.year) && (month == other.month) && (day = other.day);
}

bool SimpleDate::operator!=(const SimpleDate& other){
    return !(*this == other);
}