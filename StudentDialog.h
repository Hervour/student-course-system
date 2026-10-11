#pragma once
#include "afxdialogex.h"

class CStudentCourseSystemDlg;

class CStudentDialog : public CDialogEx
{
public:
    CStudentDialog(CWnd* pParent = nullptr);    
    virtual ~CStudentDialog();
    // 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_STUDENT };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

public:
    CButton m_radioUG;
    CButton m_radioG;
    CListCtrl m_listStudents;
    CStatic m_staticInfo;

    CStudentCourseSystemDlg* m_pParentDlg;

    void InitData(CStudentCourseSystemDlg* pParent);
    void RefreshStudentList(int nType); // 0:本科生, 1:研究生
    void DisplayStudentInfo(int nIndex);

    afx_msg void OnBnClickedRadioUg();
    afx_msg void OnBnClickedRadioG();
    afx_msg void OnLvnItemchangedListStudents(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnBnClickedButtonSelect();
    virtual BOOL OnInitDialog();
};