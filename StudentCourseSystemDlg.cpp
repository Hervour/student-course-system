
// StudentCourseSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "StudentCourseSystemDlg.h"
#include "afxdialogex.h"
#include "StudentDialog.h"
#include "CourseDialog.h"
#include "ResultDialog.h"
#include "Course.h"
#include "UGStudent.h"
#include "GStudent.h"

#include <vector>
#include <string>

CStudentCourseSystemDlg::CStudentCourseSystemDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_STUDENTCOURSESYSTEM_DIALOG, pParent)
    , m_pDlgStudent(nullptr)
    , m_pDlgCourse(nullptr)
    , m_pDlgResult(nullptr)
    , m_pCourses(nullptr)
    , m_pUndergraduates(nullptr)
    , m_pGraduates(nullptr)
    , m_pCurrentStudent(nullptr)
{
    // 初始化数据指针
    m_pCourses = new std::vector<Course>();
    m_pUndergraduates = new std::vector<UGStudent>();
    m_pGraduates = new std::vector<GStudent>();
}

CStudentCourseSystemDlg::~CStudentCourseSystemDlg()
{
    // 清理数据
    if (m_pCourses)
    {
        delete static_cast<std::vector<Course>*>(m_pCourses);
        m_pCourses = nullptr;
    }

    if (m_pUndergraduates)
    {
        delete static_cast<std::vector<UGStudent>*>(m_pUndergraduates);
        m_pUndergraduates = nullptr;
    }

    if (m_pGraduates)
    {
        delete static_cast<std::vector<GStudent>*>(m_pGraduates);
        m_pGraduates = nullptr;
    }
}

void CStudentCourseSystemDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TAB_MAIN, m_tabMain);
}

BEGIN_MESSAGE_MAP(CStudentCourseSystemDlg, CDialogEx)
    ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CStudentCourseSystemDlg::OnTcnSelchangeTabMain)
    ON_WM_DESTROY()  // 添加 ON_WM_DESTROY() 消息映射
END_MESSAGE_MAP()

void CStudentCourseSystemDlg::OnDestroy()
{

    // 清理对话框对象
    if (m_pDlgStudent)
    {
        m_pDlgStudent->DestroyWindow();
        delete m_pDlgStudent;
        m_pDlgStudent = nullptr;
    }

    if (m_pDlgCourse)
    {
        m_pDlgCourse->DestroyWindow();
        delete m_pDlgCourse;
        m_pDlgCourse = nullptr;
    }

    if (m_pDlgResult)
    {
        m_pDlgResult->DestroyWindow();
        delete m_pDlgResult;
        m_pDlgResult = nullptr;
    }
    // 调用基类的 OnDestroy
    CDialogEx::OnDestroy();
}

BOOL CStudentCourseSystemDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置对话框图标
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);

    // 添加三个Tab页面
    m_tabMain.InsertItem(0, _T("学生注册"));
    m_tabMain.InsertItem(1, _T("课程选择"));
    m_tabMain.InsertItem(2, _T("选课结果"));

    // 创建子对话框
    m_pDlgStudent = new CStudentDialog();
    m_pDlgCourse = new CCourseDialog();
    m_pDlgResult = new CResultDialog();

    m_pDlgStudent->Create(IDD_DIALOG_STUDENT, &m_tabMain);
    m_pDlgCourse->Create(IDD_DIALOG_COURSE, &m_tabMain);
    m_pDlgResult->Create(IDD_DIALOG_RESULT, &m_tabMain);

    // 初始化数据
    InitData();

    // 显示第一个页面
    UpdateTab(0);

    // 初始化子对话框
    m_pDlgStudent->InitData(this);

    return TRUE;
}

void CStudentCourseSystemDlg::OnTcnSelchangeTabMain(NMHDR* pNMHDR, LRESULT* pResult)
{
    int nTab = m_tabMain.GetCurSel();
    UpdateTab(nTab);
    *pResult = 0;
}

void CStudentCourseSystemDlg::UpdateTab(int nTab)
{
    CRect rect;
    m_tabMain.GetClientRect(&rect);
    rect.top += 25;     // 为Tab标签留出空间
    rect.bottom -= 5;
    rect.left += 5;
    rect.right -= 5;

    // 隐藏所有对话框
    if (m_pDlgStudent) m_pDlgStudent->ShowWindow(SW_HIDE);
    if (m_pDlgCourse) m_pDlgCourse->ShowWindow(SW_HIDE);
    if (m_pDlgResult) m_pDlgResult->ShowWindow(SW_HIDE);

    // 显示当前对话框
    switch (nTab)
    {
    case 0:
        if (m_pDlgStudent)
        {
            m_pDlgStudent->MoveWindow(&rect);
            m_pDlgStudent->ShowWindow(SW_SHOW);
            m_pDlgStudent->InitData(this);
        }
        break;
    case 1:
        if (m_pDlgCourse)
        {
            m_pDlgCourse->MoveWindow(&rect);
            m_pDlgCourse->ShowWindow(SW_SHOW);
            m_pDlgCourse->InitData(this);
        }
        break;
    case 2:
        if (m_pDlgResult)
        {
            m_pDlgResult->MoveWindow(&rect);
            m_pDlgResult->ShowWindow(SW_SHOW);
            m_pDlgResult->InitData(this);
        }
        break;
    }
}

void CStudentCourseSystemDlg::InitData()
{
    std::vector<Course>* pCourses = static_cast<std::vector<Course>*>(m_pCourses);
    std::vector<UGStudent>* pUndergraduates = static_cast<std::vector<UGStudent>*>(m_pUndergraduates);
    std::vector<GStudent>* pGraduates = static_cast<std::vector<GStudent>*>(m_pGraduates);

    // 初始化课程数据
    pCourses->clear();
    pCourses->push_back(Course(1, "学科基础", "英语口语", 3));
    pCourses->push_back(Course(2, "学科基础", "高等数学", 4));
    pCourses->push_back(Course(3, "学科基础", "大学物理", 4));
    pCourses->push_back(Course(4, "学科基础", "政治经济学", 3));
    pCourses->push_back(Course(5, "专业基础", "程序设计", 2));
    pCourses->push_back(Course(6, "专业基础", "数据结构", 2));
    pCourses->push_back(Course(7, "专业基础", "计算机原理", 3));
    pCourses->push_back(Course(8, "专业基础", "汇编语言", 3));
    pCourses->push_back(Course(9, "专业核心", "OOP程序设计", 3));
    pCourses->push_back(Course(10, "专业核心", "编译原理", 3));
    pCourses->push_back(Course(11, "专业核心", "微机原理", 3));
    pCourses->push_back(Course(12, "专业核心", "计算机网络", 3));

    // 初始化本科生数据（30人）
    pUndergraduates->clear();
    pUndergraduates->push_back(UGStudent("2014001", "李强", "张老师"));
    pUndergraduates->push_back(UGStudent("2014002", "王娜", "李老师"));
    pUndergraduates->push_back(UGStudent("2014003", "李飞", "王老师"));
    pUndergraduates->push_back(UGStudent("2014004", "王小明", "张老师"));
    pUndergraduates->push_back(UGStudent("2014005", "陈小霞", "李老师"));
    pUndergraduates->push_back(UGStudent("2014006", "李玉刚", "王老师"));
    pUndergraduates->push_back(UGStudent("2014007", "钟丽丽", "张老师"));
    pUndergraduates->push_back(UGStudent("2014008", "谢飞翔", "李老师"));
    pUndergraduates->push_back(UGStudent("2014009", "吴胜利", "王老师"));
    pUndergraduates->push_back(UGStudent("2014010", "程思青", "张老师"));
    pUndergraduates->push_back(UGStudent("2014011", "邹安邦", "李老师"));
    pUndergraduates->push_back(UGStudent("2014012", "曹思青", "王老师"));
    pUndergraduates->push_back(UGStudent("2014013", "卢永祥", "张老师"));
    pUndergraduates->push_back(UGStudent("2014014", "王凯", "李老师"));
    pUndergraduates->push_back(UGStudent("2014015", "王胜利", "王老师"));
    pUndergraduates->push_back(UGStudent("2014016", "李珊", "张老师"));
    pUndergraduates->push_back(UGStudent("2014017", "魏星", "李老师"));
    pUndergraduates->push_back(UGStudent("2014018", "史东", "王老师"));
    pUndergraduates->push_back(UGStudent("2014019", "谢喜莲", "张老师"));
    pUndergraduates->push_back(UGStudent("2014020", "鲁迪", "李老师"));
    pUndergraduates->push_back(UGStudent("2014021", "程长喜", "王老师"));
    pUndergraduates->push_back(UGStudent("2014022", "齐莉莉", "张老师"));
    pUndergraduates->push_back(UGStudent("2014023", "何正明", "李老师"));
    pUndergraduates->push_back(UGStudent("2014024", "赵祥海", "王老师"));
    pUndergraduates->push_back(UGStudent("2014025", "卢志胜", "张老师"));
    pUndergraduates->push_back(UGStudent("2014026", "谢喜贤", "李老师"));
    pUndergraduates->push_back(UGStudent("2014027", "邹安青", "王老师"));
    pUndergraduates->push_back(UGStudent("2014028", "蔡飞翔", "张老师"));
    pUndergraduates->push_back(UGStudent("2014029", "吴东升", "李老师"));
    pUndergraduates->push_back(UGStudent("2014030", "李建军", "王老师"));

    // 初始化研究生数据（15人）
    pGraduates->clear();
    pGraduates->push_back(GStudent("2014101", "李小强", "张教授"));
    pGraduates->push_back(GStudent("2014102", "王妮娜", "李教授"));
    pGraduates->push_back(GStudent("2014103", "李红飞", "王教授"));
    pGraduates->push_back(GStudent("2014104", "王大明", "张教授"));
    pGraduates->push_back(GStudent("2014105", "陈飞霞", "李教授"));
    pGraduates->push_back(GStudent("2014106", "李成刚", "张教授"));
    pGraduates->push_back(GStudent("2014107", "钟环丽", "张教授"));
    pGraduates->push_back(GStudent("2014108", "谢卫翔", "李教授"));
    pGraduates->push_back(GStudent("2014109", "吴卫国", "张教授"));
    pGraduates->push_back(GStudent("2014110", "程思思", "张教授"));
    pGraduates->push_back(GStudent("2014111", "邹爱国", "李教授"));
    pGraduates->push_back(GStudent("2014112", "曹宝清", "张教授"));
    pGraduates->push_back(GStudent("2014113", "卢新阳", "张教授"));
    pGraduates->push_back(GStudent("2014114", "王大凯", "李教授"));
    pGraduates->push_back(GStudent("2014115", "王福利", "张教授"));
}

// StudentCourseSystemDlg.cpp 中添加
void CStudentCourseSystemDlg::RefreshAllTabs()
{
    // 刷新所有标签页
    if (m_pDlgStudent && m_pDlgCourse && m_pDlgResult)
    {
        // 刷新学生注册页面
        m_pDlgStudent->RefreshStudentList(m_pDlgStudent->m_radioUG.GetCheck() == BST_CHECKED ? 0 : 1);

        // 刷新课程选择页面 - 使用正确的逻辑
        int nCourseType = 0; // 默认学科基础课
        if (m_pDlgCourse->m_radioBasic.GetCheck() == BST_CHECKED)
        {
            nCourseType = 1; // 专业基础课
        }
        else if (m_pDlgCourse->m_radioCore.GetCheck() == BST_CHECKED)
        {
            nCourseType = 2; // 专业核心课
        }
        // 注意：这里假设有三个单选按钮：Foundation, Basic, Core
        // 如果课程对话框有更多按钮，需要相应修改

        m_pDlgCourse->RefreshCourseList(nCourseType);

        // 刷新选课结果页面
        m_pDlgResult->RefreshSelectedCourses();
    }
}

void CStudentCourseSystemDlg::RefreshResultTabOnly()
{
    // 只刷新选课结果页面
    if (m_pDlgResult)
    {
        m_pDlgResult->RefreshSelectedCourses();
    }
}