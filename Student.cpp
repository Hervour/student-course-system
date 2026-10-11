#include "pch.h"
#include "Student.h"
#include "Course.h"
#include <algorithm>

Student::Student(const std::string& id, const std::string& n)
    : studentId(id), name(n), tuitionFee(0.0) {
}

int Student::getTotalCredits() const {
    int total = 0;
    for (const auto& course : selectedCourses) {
        total += course->getCredits();
    }
    return total;
}

int Student::selectCourse(Course* course) {
    if (selectedCourses.size() >= 5) {
        return 0; // 最多只能选5门
    }

    // 检查是否已选该课程
    for (const auto& selected : selectedCourses) {
        if (selected->getId() == course->getId()) {
            return 0; // 已经选过
        }
    }

    // 检查课程是否有空位
    if (course->enroll() == 0) {
        return 0; // 课程已满
    }

    selectedCourses.push_back(course);
    tuitionFee = calculateTuition();
    return 1;
}

void Student::displayInfo() const {
    // MFC中不需要控制台输出
}

int Student::withdrawCourse(Course* course) {
    if (selectedCourses.empty()) {
        return 0; // 没有选课
    }

    // 查找课程
    auto it = std::find_if(selectedCourses.begin(), selectedCourses.end(),
        [course](Course* c) { return c->getId() == course->getId(); });

    if (it != selectedCourses.end()) {
        // 从学生选课列表中移除
        selectedCourses.erase(it);

        // 减少课程选课人数
        course->withdraw();

        // 重新计算学费
        tuitionFee = calculateTuition();

        return 1; // 退课成功
    }

    return 0; // 没有找到这门课
}