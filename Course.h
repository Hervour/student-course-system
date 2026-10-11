#pragma once
#include <string>

class Course {
private:
    int courseId;
    std::string courseType;
    std::string courseName;
    int credits;
    int currentEnrollment;

public:
    Course(int id = 0, const std::string& type = "", const std::string& name = "", int credit = 0);

    // Getter方法
    int getId() const { return courseId; }
    std::string getType() const { return courseType; }
    std::string getName() const { return courseName; }
    int getCredits() const { return credits; }
    int getEnrollment() const { return currentEnrollment; }

    // 课程操作方法
    int enroll();
    int withdraw();
};