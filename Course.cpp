#include "pch.h"
#include "Course.h"

Course::Course(int id, const std::string& type, const std::string& name, int credit)
    : courseId(id), courseType(type), courseName(name), credits(credit), currentEnrollment(0) {
}

int Course::enroll() {
    if (currentEnrollment >= 15) {
        return 0; // ¿Î³ÌÒÑÂú
    }
    currentEnrollment++;
    return 1;
}

int Course::withdraw() {
    if (currentEnrollment <= 0) {
        return 0;
    }
    currentEnrollment--;
    return 1;
}