#include "pch.h"
#include "UGStudent.h"
#include "Course.h"

UGStudent::UGStudent(const std::string& id, const std::string& n, const std::string& advisor)
    : Student(id, n), advisorName(advisor) {
}

std::string UGStudent::getAdvisorInfo() const {
    return "班导师: " + advisorName;
}

double UGStudent::calculateTuition() {
    double fee = 0.0;
    for (const auto& course : getSelectedCourses()) {
        if (course->getType() == "学科基础") {
            fee += 1200;
        }
        else if (course->getType() == "专业基础") {
            fee += 1000;
        }
        else if (course->getType() == "专业核心") {
            fee += 800;
        }
    }
    return fee;
}