// ResultDialog.h
#pragma once
#include "afxdialogex.h"

// Ç°ÏòÉùÃ÷
class CStudentCourseSystemDlg;

class CResultDialog : public CDialogEx
{
public:
    CResultDialog(CWnd* pParent = nullptr);
    virtual ~CResultDialog();

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_RESULT };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

    DECLARE_MESSAGE_MAP()

public:
    CListCtrl m_listSelected;
    CStatic m_staticTotal;

    CStatic m_staticStudentType;
    CStatic m_staticStudentId;
    CStatic m_staticStudentName;
    CStatic m_staticAdvisor;
    CStatic m_staticCourseCount;
    CStatic m_staticTotalCredits;
    CStatic m_staticTuitionFee;

    CStudentCourseSystemDlg* m_pParentDlg;

    void InitData(CStudentCourseSystemDlg* pParent);
    void RefreshSelectedCourses();
    virtual BOOL OnInitDialog();
};