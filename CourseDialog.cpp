#include "pch.h"
#include "CourseDialog.h"
#include "StudentCourseSystemDlg.h"
#include "Course.h"
#include "Student.h"
#include "UGStudent.h"
#include "GStudent.h"
#include "afxdialogex.h"

#include <vector>
#include <string>

CCourseDialog::CCourseDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_COURSE, pParent)
    , m_pParentDlg(nullptr)
    , m_nCurrentCourseType(0)  // 默认学科基础课
{
}

CCourseDialog::~CCourseDialog()
{
    // 清理代码（如果有）
}

void CCourseDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RADIO_FOUNDATION, m_radioFoundation);
    DDX_Control(pDX, IDC_RADIO_BASIC, m_radioBasic);
    DDX_Control(pDX, IDC_RADIO_CORE, m_radioCore);
    DDX_Control(pDX, IDC_LIST_COURSES, m_listCourses);
    DDX_Control(pDX, IDC_STATIC_COURSE_INFO, m_staticCourseInfo);
    DDX_Control(pDX, IDC_BUTTON_WITHDRAW, m_btnWithdraw);
}

BEGIN_MESSAGE_MAP(CCourseDialog, CDialogEx)
    ON_BN_CLICKED(IDC_RADIO_FOUNDATION, &CCourseDialog::OnBnClickedRadioFoundation)
    ON_BN_CLICKED(IDC_RADIO_BASIC, &CCourseDialog::OnBnClickedRadioBasic)
    ON_BN_CLICKED(IDC_RADIO_CORE, &CCourseDialog::OnBnClickedRadioCore)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_COURSES, &CCourseDialog::OnLvnItemchangedListCourses)
    ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &CCourseDialog::OnBnClickedButtonConfirm)
    ON_BN_CLICKED(IDC_BUTTON_WITHDRAW, &CCourseDialog::OnBnClickedButtonWithdraw)
END_MESSAGE_MAP()

BOOL CCourseDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 初始化列表控件
    m_listCourses.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);
    m_listCourses.InsertColumn(1, _T("课程名称"), LVCFMT_LEFT, 150);
    m_listCourses.InsertColumn(2, _T("课程类型"), LVCFMT_LEFT, 100);
    m_listCourses.InsertColumn(3, _T("学分"), LVCFMT_LEFT, 80);
    m_listCourses.InsertColumn(4, _T("选课人数"), LVCFMT_LEFT, 100);

    m_listCourses.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    // 设置单选按钮的选中状态
    CheckRadioButton(IDC_RADIO_FOUNDATION, IDC_RADIO_CORE, IDC_RADIO_FOUNDATION);

    return TRUE;
}

void CCourseDialog::InitData(CStudentCourseSystemDlg* pParent)
{
    m_pParentDlg = pParent;
    // 使用保存的课程类型，而不是默认值
    RefreshCourseList(m_nCurrentCourseType);
    DisplayStudentInfo();
}

void CCourseDialog::RefreshCourseList(int nType)
{
    // 更新当前课程类型
    m_nCurrentCourseType = nType;

    // 确保单选按钮状态正确
    if (nType == 0) // 学科基础课
    {
        CheckRadioButton(IDC_RADIO_FOUNDATION, IDC_RADIO_CORE, IDC_RADIO_FOUNDATION);
    }
    else if (nType == 1) // 专业基础课
    {
        CheckRadioButton(IDC_RADIO_FOUNDATION, IDC_RADIO_CORE, IDC_RADIO_BASIC);
    }
    else // 专业核心课
    {
        CheckRadioButton(IDC_RADIO_FOUNDATION, IDC_RADIO_CORE, IDC_RADIO_CORE);
    }

    m_listCourses.DeleteAllItems();

    if (!m_pParentDlg) return;

    std::vector<Course>* pCourses =
        static_cast<std::vector<Course>*>(m_pParentDlg->GetCourses());

    if (!pCourses) return;

    int nItemIndex = 0;
    for (int i = 0; i < (int)pCourses->size(); i++)
    {
        Course& course = (*pCourses)[i];
        std::string courseType = course.getType();

        // 根据课程类型筛选
        if ((nType == 0 && courseType == "学科基础") ||
            (nType == 1 && courseType == "专业基础") ||
            (nType == 2 && courseType == "专业核心"))
        {
            CString strIndex, strName, strType, strCredits, strEnrollment;
            strIndex.Format(_T("%d"), nItemIndex + 1);
            strName = course.getName().c_str();
            strType = courseType.c_str();
            strCredits.Format(_T("%d"), course.getCredits());
            strEnrollment.Format(_T("%d"), course.getEnrollment());

            int nItem = m_listCourses.InsertItem(nItemIndex, strIndex);
            m_listCourses.SetItemText(nItem, 1, strName);
            m_listCourses.SetItemText(nItem, 2, strType);
            m_listCourses.SetItemText(nItem, 3, strCredits);
            m_listCourses.SetItemText(nItem, 4, strEnrollment);
            nItemIndex++;
        }
    }

    // 如果列表中有项目，默认选中第一项
    if (nItemIndex > 0)
    {
        m_listCourses.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
        m_listCourses.SetSelectionMark(0);
        DisplayCourseInfo(0);
    }
}

void CCourseDialog::OnBnClickedRadioFoundation()
{
    RefreshCourseList(0);
}

void CCourseDialog::OnBnClickedRadioBasic()
{
    RefreshCourseList(1);
}

void CCourseDialog::OnBnClickedRadioCore()
{
    RefreshCourseList(2);
}

void CCourseDialog::OnLvnItemchangedListCourses(NMHDR* pNMHDR, LRESULT* pResult)
{
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

    if (pNMLV->iItem >= 0 && (pNMLV->uChanged & LVIF_STATE))
    {
        DisplayCourseInfo(pNMLV->iItem);
    }

    *pResult = 0;
}

void CCourseDialog::DisplayCourseInfo(int nIndex)
{
    if (!m_pParentDlg) return;

    std::vector<Course>* pCourses =
        static_cast<std::vector<Course>*>(m_pParentDlg->GetCourses());

    if (!pCourses) return;

    // 根据选中的单选按钮确定过滤类型
    int nFilterType = 0;
    CString strFilter;

    if (m_radioFoundation.GetCheck() == BST_CHECKED)
    {
        nFilterType = 0;
        strFilter = _T("学科基础");
    }
    else if (m_radioBasic.GetCheck() == BST_CHECKED)
    {
        nFilterType = 1;
        strFilter = _T("专业基础");
    }
    else
    {
        nFilterType = 2;
        strFilter = _T("专业核心");
    }

    // 根据列表中的序号找到对应的课程
    int count = 0;

    for (int i = 0; i < (int)pCourses->size(); i++)
    {
        Course& course = (*pCourses)[i];
        std::string courseType = course.getType();

        if (courseType == CStringA(strFilter).GetString())
        {
            if (count == nIndex)
            {
                CString strInfo;
                strInfo.Format(_T("课程详细信息:\n\n")
                    _T("课程名称: %s\n")
                    _T("课程类型: %s\n")
                    _T("课程学分: %d\n")
                    _T("当前选课人数: %d/15\n")
                    _T("课程状态: %s"),
                    course.getName().c_str(),
                    courseType.c_str(),
                    course.getCredits(),
                    course.getEnrollment(),
                    course.getEnrollment() >= 15 ? _T("已满") : _T("可选"));
                m_staticCourseInfo.SetWindowText(strInfo);

                // 检查该课程是否已被当前学生选中
                Student* pCurrentStudent = static_cast<Student*>(m_pParentDlg->GetCurrentStudent());
                bool isSelected = false;

                if (pCurrentStudent)
                {
                    const std::vector<Course*>& selectedCourses = pCurrentStudent->getSelectedCourses();
                    for (const auto& selected : selectedCourses)
                    {
                        if (selected->getId() == course.getId())
                        {
                            isSelected = true;
                            break;
                        }
                    }
                }

                // 根据课程是否已选来设置退课按钮状态
                m_btnWithdraw.EnableWindow(isSelected && pCurrentStudent != nullptr);

                break;
            }
            count++;
        }
    }
}

void CCourseDialog::OnBnClickedButtonConfirm()
{
    if (!m_pParentDlg) return;

    Student* pCurrentStudent = static_cast<Student*>(m_pParentDlg->GetCurrentStudent());
    if (!pCurrentStudent)
    {
        MessageBox(_T("请先到'学生注册'页面选择一个学生！"), _T("提示"), MB_OK | MB_ICONWARNING);
        return;
    }

    int nIndex = m_listCourses.GetSelectionMark();
    if (nIndex < 0)
    {
        MessageBox(_T("请选择一门课程！"), _T("提示"), MB_OK | MB_ICONWARNING);
        return;
    }

    // 检查是否已选满5门课
    if (pCurrentStudent->getSelectedCoursesCount() >= 5)
    {
        MessageBox(_T("该学生已选满5门课程，不能再选！"), _T("提示"), MB_OK | MB_ICONWARNING);
        return;
    }

    std::vector<Course>* pCourses =
        static_cast<std::vector<Course>*>(m_pParentDlg->GetCourses());

    if (!pCourses) return;

    // 根据当前课程类型确定过滤条件
    CString strFilter;
    switch (m_nCurrentCourseType)
    {
    case 0:
        strFilter = _T("学科基础");
        break;
    case 1:
        strFilter = _T("专业基础");
        break;
    case 2:
        strFilter = _T("专业核心");
        break;
    }

    // 根据列表中的序号找到对应的课程
    int count = 0;

    for (int i = 0; i < (int)pCourses->size(); i++)
    {
        Course& course = (*pCourses)[i];
        std::string courseType = course.getType();

        if (courseType == CStringA(strFilter).GetString())
        {
            if (count == nIndex)
            {
                // 检查是否已选过该课程
                const std::vector<Course*>& studentCourses = pCurrentStudent->getSelectedCourses();
                for (const auto& selected : studentCourses)
                {
                    if (selected->getId() == course.getId())
                    {
                        MessageBox(_T("该学生已选过这门课程！"), _T("提示"), MB_OK | MB_ICONWARNING);
                        return;
                    }
                }

                // 检查课程是否已满
                if (course.getEnrollment() >= 15)
                {
                    MessageBox(_T("该课程已满，无法选择！"), _T("提示"), MB_OK | MB_ICONWARNING);
                    return;
                }

                // 执行选课操作
                int result = pCurrentStudent->selectCourse(&course);
                if (result == 1)
                {
                    CString strMsg;
                    strMsg.Format(_T("选课成功！\n\n")
                        _T("课程名称: %s\n")
                        _T("课程类型: %s\n")
                        _T("学分: %d\n")
                        _T("当前选课人数: %d\n\n")
                        _T("已选课程数: %d/5"),
                        course.getName().c_str(),
                        courseType.c_str(),
                        course.getCredits(),
                        course.getEnrollment(),
                        pCurrentStudent->getSelectedCoursesCount());

                    MessageBox(strMsg, _T("成功"), MB_OK | MB_ICONINFORMATION);

                    // 刷新当前课程类型的列表（保持当前课程类型不变）
                    RefreshCourseList(m_nCurrentCourseType);

                    // 显示学生信息
                    DisplayStudentInfo();

                    // 刷新选课结果页面（但不刷新课程选择页面，因为已经刷新过了）
                    // 注意：这里直接调用m_pParentDlg->RefreshResultTabOnly()
                    m_pParentDlg->RefreshResultTabOnly();
                }
                else
                {
                    MessageBox(_T("选课失败！"), _T("错误"), MB_OK | MB_ICONERROR);
                }
                break;
            }
            count++;
        }
    }
}

void CCourseDialog::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialogEx::OnShowWindow(bShow, nStatus);

    if (bShow)
    {
        // 每次显示窗口时，使用保存的课程类型
        RefreshCourseList(m_nCurrentCourseType);

        // 显示学生信息
        DisplayStudentInfo();

        // 初始化退课按钮为不可用
        m_btnWithdraw.EnableWindow(FALSE);
    }
}
// CourseDialog.cpp
void CCourseDialog::DisplayStudentInfo()
{
    if (!m_pParentDlg) return;

    Student* pCurrentStudent = static_cast<Student*>(m_pParentDlg->GetCurrentStudent());
    if (!pCurrentStudent)
    {
        m_listCourses.EnableWindow(FALSE);
        m_radioFoundation.EnableWindow(FALSE);
        m_radioBasic.EnableWindow(FALSE);
        m_radioCore.EnableWindow(FALSE);
        m_btnWithdraw.EnableWindow(FALSE);
        GetDlgItem(IDC_BUTTON_CONFIRM)->EnableWindow(FALSE);

        CString strInfo = _T("请先到'学生注册'页面选择一个学生");
        m_staticCourseInfo.SetWindowText(strInfo);
        return;
    }

    m_listCourses.EnableWindow(TRUE);
    m_radioFoundation.EnableWindow(TRUE);
    m_radioBasic.EnableWindow(TRUE);
    m_radioCore.EnableWindow(TRUE);

    GetDlgItem(IDC_BUTTON_CONFIRM)->EnableWindow(TRUE);

    // 显示学生已选课程信息
    int selectedCount = pCurrentStudent->getSelectedCoursesCount();
    int totalCredits = pCurrentStudent->getTotalCredits();

    UGStudent* pUGStudent = dynamic_cast<UGStudent*>(pCurrentStudent);
    GStudent* pGStudent = dynamic_cast<GStudent*>(pCurrentStudent);

    CString strStudentInfo;

    if (pUGStudent)
    {
        strStudentInfo.Format(_T("当前选课学生:\n")
            _T("姓名: %s (本科生)\n")
            _T("已选课程数: %d/5\n")
            _T("已获学分: %d\n")
            _T("应缴学费: %.2f元")
            _T("提示: 选中已选的课程后，可点击'退选该课程'按钮退课"),
            pCurrentStudent->getName().c_str(),
            selectedCount,
            totalCredits,
            pCurrentStudent->getTuitionFee());
    }
    else if (pGStudent)
    {
        strStudentInfo.Format(_T("当前选课学生:\n")
            _T("姓名: %s (研究生)\n")
            _T("已选课程数: %d/5\n")
            _T("已获学分: %d\n")
            _T("应缴学费: %.2f元")
            _T("提示: 选中已选的课程后，可点击'退选该课程'按钮退课"),
            pCurrentStudent->getName().c_str(),
            selectedCount,
            totalCredits,
            pCurrentStudent->getTuitionFee());
    }

    // 获取当前课程信息
    CString strCurrentInfo;
    m_staticCourseInfo.GetWindowText(strCurrentInfo);

    // 合并信息
    CString strNewInfo;
    if (!strCurrentInfo.IsEmpty())
    {
        strNewInfo = strStudentInfo + _T("\n\n") + strCurrentInfo;
    }
    else
    {
        strNewInfo = strStudentInfo + _T("\n\n请选择一门课程查看详细信息");
    }

    m_staticCourseInfo.SetWindowText(strNewInfo);
}

void CCourseDialog::OnBnClickedButtonWithdraw()
{
    if (!m_pParentDlg) return;

    Student* pCurrentStudent = static_cast<Student*>(m_pParentDlg->GetCurrentStudent());
    if (!pCurrentStudent)
    {
        MessageBox(_T("请先到'学生注册'页面选择一个学生！"), _T("提示"), MB_OK | MB_ICONWARNING);
        return;
    }

    int nIndex = m_listCourses.GetSelectionMark();
    if (nIndex < 0)
    {
        MessageBox(_T("请选择一门要退的课程！"), _T("提示"), MB_OK | MB_ICONWARNING);
        return;
    }

    std::vector<Course>* pCourses =
        static_cast<std::vector<Course>*>(m_pParentDlg->GetCourses());

    if (!pCourses) return;

    // 根据选中的单选按钮确定过滤类型
    CString strFilter;
    if (m_radioFoundation.GetCheck() == BST_CHECKED)
    {
        strFilter = _T("学科基础");
    }
    else if (m_radioBasic.GetCheck() == BST_CHECKED)
    {
        strFilter = _T("专业基础");
    }
    else
    {
        strFilter = _T("专业核心");
    }

    // 根据列表中的序号找到对应的课程
    int count = 0;

    for (int i = 0; i < (int)pCourses->size(); i++)
    {
        Course& course = (*pCourses)[i];
        std::string courseType = course.getType();

        if (courseType == CStringA(strFilter).GetString())
        {
            if (count == nIndex)
            {
                // 确认是否要退课
                CString strConfirm;
                strConfirm.Format(_T("确定要退选以下课程吗？\n\n课程名称: %s\n课程类型: %s\n学分: %d"),
                    course.getName().c_str(),
                    courseType.c_str(),
                    course.getCredits());

                if (MessageBox(strConfirm, _T("确认退课"), MB_YESNO | MB_ICONQUESTION) != IDYES)
                {
                    return;
                }

                // 执行退课操作
                int result = pCurrentStudent->withdrawCourse(&course);
                if (result == 1)
                {
                    CString strMsg;
                    strMsg.Format(_T("退课成功！\n\n")
                        _T("已退课程: %s\n")
                        _T("当前选课人数: %d\n\n")
                        _T("剩余课程数: %d/5"),
                        course.getName().c_str(),
                        course.getEnrollment(),
                        pCurrentStudent->getSelectedCoursesCount());

                    MessageBox(strMsg, _T("成功"), MB_OK | MB_ICONINFORMATION);

                    // 刷新当前课程类型的列表
                    RefreshCourseList(m_nCurrentCourseType);

                    // 显示学生信息
                    DisplayStudentInfo();

                    // 刷新选课结果页面
                    if (m_pParentDlg && m_pParentDlg->m_pDlgResult)
                    {
                        m_pParentDlg->RefreshResultTabOnly();
                    }
                }
                else
                {
                    MessageBox(_T("退课失败！该课程未被选中或学生未选择该课程。"), _T("错误"), MB_OK | MB_ICONERROR);
                }
                break;
            }
            count++;
        }
    }
}