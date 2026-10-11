#include "pch.h"
#include "ResultDialog.h"
#include "StudentCourseSystemDlg.h"
#include "afxdialogex.h"

#include "Student.h"
#include "UGStudent.h"
#include "GStudent.h"
#include "Course.h"

#include <vector>
#include <string>

CResultDialog::CResultDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_RESULT, pParent)
    , m_pParentDlg(nullptr)
{
}

CResultDialog::~CResultDialog()
{
    // 清理代码（如果有）
}

void CResultDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST_SELECTED, m_listSelected);
    DDX_Control(pDX, IDC_STATIC_TOTAL, m_staticTotal);
    DDX_Control(pDX, IDC_STATIC_STUDENT_TYPE, m_staticStudentType);
    DDX_Control(pDX, IDC_STATIC_STUDENT_ID, m_staticStudentId);
    DDX_Control(pDX, IDC_STATIC_STUDENT_NAME, m_staticStudentName);
    DDX_Control(pDX, IDC_STATIC_ADVISOR, m_staticAdvisor);
    DDX_Control(pDX, IDC_STATIC_COURSE_COUNT, m_staticCourseCount);
    DDX_Control(pDX, IDC_STATIC_TOTAL_CREDITS, m_staticTotalCredits);
    DDX_Control(pDX, IDC_STATIC_TUITION_FEE, m_staticTuitionFee);
}

BEGIN_MESSAGE_MAP(CResultDialog, CDialogEx)
END_MESSAGE_MAP()

BOOL CResultDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 初始化列表控件
    m_listSelected.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);
    m_listSelected.InsertColumn(1, _T("课程名称"), LVCFMT_LEFT, 150);
    m_listSelected.InsertColumn(2, _T("课程类型"), LVCFMT_LEFT, 100);
    m_listSelected.InsertColumn(3, _T("学分"), LVCFMT_LEFT, 80);
    m_listSelected.InsertColumn(4, _T("选课人数"), LVCFMT_LEFT, 100);

    m_listSelected.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    return TRUE;
}

void CResultDialog::InitData(CStudentCourseSystemDlg* pParent)
{
    m_pParentDlg = pParent;
    RefreshSelectedCourses();
}

void CResultDialog::RefreshSelectedCourses()
{
    m_listSelected.DeleteAllItems();

    if (!m_pParentDlg) return;

    Student* pCurrentStudent = static_cast<Student*>(m_pParentDlg->GetCurrentStudent());
    if (!pCurrentStudent)
    {
        m_staticTotal.SetWindowText(_T("请先到'学生注册'页面选择一个学生"));
        m_staticStudentType.SetWindowText(_T(""));
        m_staticStudentId.SetWindowText(_T(""));
        m_staticStudentName.SetWindowText(_T(""));
        m_staticAdvisor.SetWindowText(_T(""));
        m_staticCourseCount.SetWindowText(_T(""));
        m_staticTotalCredits.SetWindowText(_T(""));
        return;
    }

    // 显示已选课程
    const std::vector<Course*>& selectedCourses = pCurrentStudent->getSelectedCourses();
    for (int i = 0; i < (int)selectedCourses.size(); i++)
    {
        Course* course = selectedCourses[i];

        CString strIndex, strName, strType, strCredits, strEnrollment;
        strIndex.Format(_T("%d"), i + 1);
        strName = course->getName().c_str();
        strType = course->getType().c_str();
        strCredits.Format(_T("%d"), course->getCredits());
        strEnrollment.Format(_T("%d"), course->getEnrollment());

        int nItem = m_listSelected.InsertItem(i, strIndex);
        m_listSelected.SetItemText(nItem, 1, strName);
        m_listSelected.SetItemText(nItem, 2, strType);
        m_listSelected.SetItemText(nItem, 3, strCredits);
        m_listSelected.SetItemText(nItem, 4, strEnrollment);
    }

    // 显示总计信息
    UGStudent* pUGStudent = dynamic_cast<UGStudent*>(pCurrentStudent);
    GStudent* pGStudent = dynamic_cast<GStudent*>(pCurrentStudent);

    CString strTotal;

    if (pUGStudent)
    {
        m_staticStudentType.SetWindowText(_T("本科生"));
    }
    else if (pGStudent)
    {
        m_staticStudentType.SetWindowText(_T("研究生"));
    }
    else
    {
        m_staticStudentType.SetWindowText(_T("未知类型"));
    }

    m_staticStudentId.SetWindowText(CString(pCurrentStudent->getId().c_str()));
    m_staticStudentName.SetWindowText(CString(pCurrentStudent->getName().c_str()));

    // 处理导师信息，去掉前缀
    std::string advisorInfo = pCurrentStudent->getAdvisorInfo();
    if (advisorInfo.find("班导师: ") == 0)
    {
        advisorInfo = advisorInfo.substr(8); // 去掉"班导师: "
    }
    else if (advisorInfo.find("导师: ") == 0)
    {
        advisorInfo = advisorInfo.substr(6); // 去掉"导师: "
    }
    m_staticAdvisor.SetWindowText(CString(advisorInfo.c_str()));

    CString strTemp;
    strTemp.Format(_T("%d/5"), pCurrentStudent->getSelectedCoursesCount());
    m_staticCourseCount.SetWindowText(strTemp);

    strTemp.Format(_T("%d"), pCurrentStudent->getTotalCredits());
    m_staticTotalCredits.SetWindowText(strTemp);

    strTemp.Format(_T("%.2f 元"), pCurrentStudent->getTuitionFee());
    m_staticTuitionFee.SetWindowText(strTemp);


    // 如果未选任何课程
    if (selectedCourses.empty())
    {
        strTotal += _T("\n\n该学生尚未选择任何课程。");
    }

    m_staticTotal.SetWindowText(strTotal);
}