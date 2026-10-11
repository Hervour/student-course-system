// StudentCourseSystemDlg.h
#pragma once
#include "afxcmn.h"

// 前向声明
class CStudentDialog;
class CCourseDialog;
class CResultDialog;

class CStudentCourseSystemDlg : public CDialogEx
{
public:
    CStudentCourseSystemDlg(CWnd* pParent = nullptr);
    virtual ~CStudentCourseSystemDlg();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_STUDENTCOURSESYSTEM_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual void OnDestroy();

    DECLARE_MESSAGE_MAP()

public:
    CTabCtrl m_tabMain;

    CStudentDialog* m_pDlgStudent;
    CCourseDialog* m_pDlgCourse;
    CResultDialog* m_pDlgResult;

    // 数据成员（在cpp中定义具体类型）
    void* m_pCourses;  // 指向 std::vector<Course>*
    void* m_pUndergraduates;  // 指向 std::vector<UGStudent>*
    void* m_pGraduates;  // 指向 std::vector<GStudent>*
    void* m_pCurrentStudent;  // 指向 Student*

    virtual BOOL OnInitDialog();
    afx_msg void OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult);

    void InitData();
    void UpdateTab(int nTab);
    void RefreshAllTabs();
    void RefreshResultTabOnly();  // 声明但不在这里实现

    // 获取数据的方法
    void* GetCourses() { return m_pCourses; }
    void* GetUndergraduates() { return m_pUndergraduates; }
    void* GetGraduates() { return m_pGraduates; }
    void* GetCurrentStudent() { return m_pCurrentStudent; }
    void SetCurrentStudent(void* pStudent) { m_pCurrentStudent = pStudent; }
};