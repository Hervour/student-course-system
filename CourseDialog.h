// CourseDialog.h
#pragma once
#include "afxdialogex.h"

// 前向声明
class CStudentCourseSystemDlg;

class CCourseDialog : public CDialogEx
{
public:
    CCourseDialog(CWnd* pParent = nullptr);
    virtual ~CCourseDialog();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_COURSE };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual void OnShowWindow(BOOL bShow, UINT nStatus);
    DECLARE_MESSAGE_MAP()

public:
    CButton m_radioFoundation;
    CButton m_radioBasic;
    CButton m_radioCore;
    CButton m_btnWithdraw;
    CListCtrl m_listCourses;
    CStatic m_staticCourseInfo;

    CStudentCourseSystemDlg* m_pParentDlg;

    int m_nCurrentCourseType;

    void InitData(CStudentCourseSystemDlg* pParent);
    void RefreshCourseList(int nType); // 0:学科基础课, 1:专业基础课, 2:专业核心课
    void DisplayCourseInfo(int nIndex);
    void DisplayStudentInfo();

    afx_msg void OnBnClickedRadioFoundation();
    afx_msg void OnBnClickedRadioBasic();
    afx_msg void OnBnClickedRadioCore();
    afx_msg void OnLvnItemchangedListCourses(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonConfirm();
    afx_msg void OnBnClickedButtonWithdraw();
    virtual BOOL OnInitDialog();
};