// StudentDialog.cpp
#include "pch.h"
#include "StudentDialog.h"
#include "StudentCourseSystemDlg.h"
#include "UGStudent.h"
#include "GStudent.h"
#include "afxdialogex.h"

#include <vector>
#include <string>

CStudentDialog::CStudentDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_STUDENT, pParent)
    , m_pParentDlg(nullptr)
{
}

CStudentDialog::~CStudentDialog()
{
}

void CStudentDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADIO_UG, m_radioUG);
    DDX_Control(pDX, IDC_RADIO_G, m_radioG);
    DDX_Control(pDX, IDC_LIST_STUDENTS, m_listStudents);
    DDX_Control(pDX, IDC_STATIC_INFO, m_staticInfo);
}

BEGIN_MESSAGE_MAP(CStudentDialog, CDialogEx)
    ON_BN_CLICKED(IDC_RADIO_UG, &CStudentDialog::OnBnClickedRadioUg)
    ON_BN_CLICKED(IDC_RADIO_G, &CStudentDialog::OnBnClickedRadioG)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_STUDENTS, &CStudentDialog::OnLvnItemchangedListStudents)
    ON_BN_CLICKED(IDC_BUTTON_SELECT, &CStudentDialog::OnBnClickedButtonSelect)
END_MESSAGE_MAP()

BOOL CStudentDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 初始化列表控件
    m_listStudents.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);
    m_listStudents.InsertColumn(1, _T("学号"), LVCFMT_LEFT, 100);
    m_listStudents.InsertColumn(2, _T("姓名"), LVCFMT_LEFT, 100);
    m_listStudents.InsertColumn(3, _T("导师"), LVCFMT_LEFT, 100);
    m_listStudents.InsertColumn(4, _T("选课数"), LVCFMT_LEFT, 80);
    m_listStudents.InsertColumn(5, _T("总学分"), LVCFMT_LEFT, 80);
    m_listStudents.InsertColumn(6, _T("学费"), LVCFMT_LEFT, 100);

    m_listStudents.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    // 默认选择本科生
    m_radioUG.SetCheck(BST_CHECKED);

    return TRUE;
}

void CStudentDialog::InitData(CStudentCourseSystemDlg* pParent)
{
    m_pParentDlg = pParent;
    RefreshStudentList(0);  // 默认显示本科生
}

void CStudentDialog::RefreshStudentList(int nType)
{
    // 确保单选按钮状态正确
    if (nType == 0) // 本科生
    {
        CheckRadioButton(IDC_RADIO_UG, IDC_RADIO_G, IDC_RADIO_UG);
    }
    else // 研究生
    {
        CheckRadioButton(IDC_RADIO_UG, IDC_RADIO_G, IDC_RADIO_G);
    }

    m_listStudents.DeleteAllItems();

    if (!m_pParentDlg) return;

    if (nType == 0) // 本科生
    {
        std::vector<UGStudent>* pUndergraduates =
            static_cast<std::vector<UGStudent>*>(m_pParentDlg->GetUndergraduates());

        if (!pUndergraduates) return;

        for (int i = 0; i < (int)pUndergraduates->size(); i++)
        {
            UGStudent& student = (*pUndergraduates)[i];

            CString strIndex, strId, strName, strAdvisor, strCount, strCredits, strFee;
            strIndex.Format(_T("%d"), i + 1);
            strId = student.getId().c_str();
            strName = student.getName().c_str();

            // 获取导师信息并去掉"班导师: "前缀
            std::string advisorInfo = student.getAdvisorInfo();
            if (advisorInfo.find("班导师: ") == 0)
            {
                advisorInfo = advisorInfo.substr(4);
            }
            strAdvisor = student.getAdvisorNameOnly().c_str();

            strCount.Format(_T("%d"), student.getSelectedCoursesCount());
            strCredits.Format(_T("%d"), student.getTotalCredits());
            strFee.Format(_T("%.2f"), student.getTuitionFee());

            int nItem = m_listStudents.InsertItem(i, strIndex);
            m_listStudents.SetItemText(nItem, 1, strId);
            m_listStudents.SetItemText(nItem, 2, strName);
            m_listStudents.SetItemText(nItem, 3, strAdvisor);
            m_listStudents.SetItemText(nItem, 4, strCount);
            m_listStudents.SetItemText(nItem, 5, strCredits);
            m_listStudents.SetItemText(nItem, 6, strFee);
        }
    }
    else // 研究生
    {
        std::vector<GStudent>* pGraduates =
            static_cast<std::vector<GStudent>*>(m_pParentDlg->GetGraduates());

        if (!pGraduates) return;

        for (int i = 0; i < (int)pGraduates->size(); i++)
        {
            GStudent& student = (*pGraduates)[i];

            CString strIndex, strId, strName, strAdvisor, strCount, strCredits, strFee;
            strIndex.Format(_T("%d"), i + 1);
            strId = student.getId().c_str();
            strName = student.getName().c_str();

            // 获取导师信息并去掉"导师: "前缀
            std::string advisorInfo = student.getAdvisorInfo();
            if (advisorInfo.find("导师: ") == 0)
            {
                advisorInfo = advisorInfo.substr(3);
            }
            strAdvisor = student.getAdvisorNameOnly().c_str();

            strCount.Format(_T("%d"), student.getSelectedCoursesCount());
            strCredits.Format(_T("%d"), student.getTotalCredits());
            strFee.Format(_T("%.2f"), student.getTuitionFee());

            int nItem = m_listStudents.InsertItem(i, strIndex);
            m_listStudents.SetItemText(nItem, 1, strId);
            m_listStudents.SetItemText(nItem, 2, strName);
            m_listStudents.SetItemText(nItem, 3, strAdvisor);
            m_listStudents.SetItemText(nItem, 4, strCount);
            m_listStudents.SetItemText(nItem, 5, strCredits);
            m_listStudents.SetItemText(nItem, 6, strFee);
        }
    }
}

void CStudentDialog::OnBnClickedRadioUg()
{
    RefreshStudentList(0);
}

void CStudentDialog::OnBnClickedRadioG()
{
    RefreshStudentList(1);
}

void CStudentDialog::OnLvnItemchangedListStudents(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    if (pNMLV->iItem >= 0 && (pNMLV->uChanged & LVIF_STATE))
    {
        if (!m_pParentDlg) return;

        CString strInfo;

        if (m_radioUG.GetCheck() == BST_CHECKED)
        {
            std::vector<UGStudent>* pUndergraduates =
                static_cast<std::vector<UGStudent>*>(m_pParentDlg->GetUndergraduates());

            if (pUndergraduates && pNMLV->iItem >= 0 && pNMLV->iItem < (int)pUndergraduates->size())
            {
                UGStudent& student = (*pUndergraduates)[pNMLV->iItem];

                std::string advisorInfo = student.getAdvisorInfo();

                strInfo.Format(_T("学生信息:\n\n学号: %s\n姓名: %s\n%s\n已选课程数: %d\n总学分: %d\n学费: %.2f元"),
                    student.getId().c_str(),
                    student.getName().c_str(),
                    advisorInfo.c_str(),
                    student.getSelectedCoursesCount(),
                    student.getTotalCredits(),
                    student.getTuitionFee());
            }
        }
        else
        {
            std::vector<GStudent>* pGraduates =
                static_cast<std::vector<GStudent>*>(m_pParentDlg->GetGraduates());

            if (pGraduates && pNMLV->iItem >= 0 && pNMLV->iItem < (int)pGraduates->size())
            {
                GStudent& student = (*pGraduates)[pNMLV->iItem];

                std::string advisorInfo = student.getAdvisorInfo();

                strInfo.Format(_T("学生信息:\n\n学号: %s\n姓名: %s\n%s\n已选课程数: %d\n总学分: %d\n学费: %.2f元"),
                    student.getId().c_str(),
                    student.getName().c_str(),
                    advisorInfo.c_str(),
                    student.getSelectedCoursesCount(),
                    student.getTotalCredits(),
                    student.getTuitionFee());
            }
        }

        m_staticInfo.SetWindowText(strInfo);
    }

    *pResult = 0;
}

void CStudentDialog::OnBnClickedButtonSelect()
{
    int nIndex = m_listStudents.GetSelectionMark();
    if (nIndex < 0)
    {
        MessageBox(_T("请先选择一个学生！"), _T("提示"), MB_OK | MB_ICONWARNING);
        return;
    }

    if (!m_pParentDlg) return;

    if (m_radioUG.GetCheck() == BST_CHECKED)
    {
        std::vector<UGStudent>* pUndergraduates =
            static_cast<std::vector<UGStudent>*>(m_pParentDlg->GetUndergraduates());

        if (pUndergraduates && nIndex >= 0 && nIndex < (int)pUndergraduates->size())
        {
            UGStudent& student = (*pUndergraduates)[nIndex];
            m_pParentDlg->SetCurrentStudent(&student);

            CString strMsg;
            strMsg.Format(_T("已选择本科生：%s\n学号：%s\n导师：%s\n已选课程：%d/5\n现在可以切换到'课程选择'页面进行选课。"),
                student.getName().c_str(),
                student.getId().c_str(),
                student.getAdvisorInfo().c_str(),
                student.getSelectedCoursesCount());
            MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONINFORMATION);

            // 刷新其他标签页
            m_pParentDlg->RefreshAllTabs();
        }
    }
    else
    {
        std::vector<GStudent>* pGraduates =
            static_cast<std::vector<GStudent>*>(m_pParentDlg->GetGraduates());

        if (pGraduates && nIndex >= 0 && nIndex < (int)pGraduates->size())
        {
            GStudent& student = (*pGraduates)[nIndex];
            m_pParentDlg->SetCurrentStudent(&student);

            CString strMsg;
            strMsg.Format(_T("已选择研究生：%s\n学号：%s\n导师：%s\n已选课程：%d/5\n现在可以切换到'课程选择'页面进行选课。"),
                student.getName().c_str(),
                student.getId().c_str(),
                student.getAdvisorInfo().c_str(),
                student.getSelectedCoursesCount());
            MessageBox(strMsg, _T("提示"), MB_OK | MB_ICONINFORMATION);

            // 刷新其他标签页
            m_pParentDlg->RefreshAllTabs();
        }
    }
}