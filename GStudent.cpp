#include "pch.h"
#include "GStudent.h"
#include "Course.h"

GStudent::GStudent(const std::string& id, const std::string& n, const std::string& advisor)
    : Student(id, n), advisorName(advisor) {
}

std::string GStudent::getAdvisorInfo() const {
    return "导师: " + advisorName;
}

double GStudent::calculateTuition() {
    double fee = 0.0;
    for (const auto& course : getSelectedCourses()) {
        if (course->getType() == "学科基础") {
            fee += 400 * course->getCredits();
        }
        else if (course->getType() == "专业基础") {
            fee += 350 * course->getCredits();
        }
        else if (course->getType() == "专业核心") {
            fee += 300 * course->getCredits();
        }
    }
    return fee;
}