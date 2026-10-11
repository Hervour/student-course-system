#pragma once
#include <string>
#include <vector>

class Course;

class Student {
protected:
    std::string studentId;
    std::string name;
    std::vector<Course*> selectedCourses;
    double tuitionFee;

public:
    Student(const std::string& id = "", const std::string& n = "");
    virtual ~Student() {}

    // Getter方法
    std::string getId() const { return studentId; }
    std::string getName() const { return name; }
    double getTuitionFee() const { return tuitionFee; }
    int getSelectedCoursesCount() const { return (int)selectedCourses.size(); }
    int getTotalCredits() const;
    std::vector<Course*> getSelectedCourses() const { return selectedCourses; }

    // 纯虚函数
    virtual std::string getAdvisorInfo() const = 0;
    virtual double calculateTuition() = 0;

    // 选课操作方法
    int selectCourse(Course* course);
    //退课操作方法
    int withdrawCourse(Course* course);

    // 显示信息
    virtual void displayInfo() const;
};