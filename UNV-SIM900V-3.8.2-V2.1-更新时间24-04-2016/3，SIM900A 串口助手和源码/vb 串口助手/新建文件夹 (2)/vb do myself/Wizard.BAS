Attribute VB_Name = "modWizard"
Option Explicit

Global Const WIZARD_NAME = "WizardTemplate"

Declare Function WritePrivateProfileString& Lib "Kernel32" Alias "WritePrivateProfileStringA" (ByVal AppName$, ByVal KeyName$, ByVal keydefault$, ByVal FileName$)

'WinHelp 命令
Declare Function WinHelp Lib "user32" Alias "WinHelpA" (ByVal hwnd As Long, ByVal lpHelpFile As String, ByVal wCommand As Long, ByVal dwData As Long) As Long
Public Const HELP_QUIT = &H2              '  终止帮助
Public Const HELP_CONTENTS = &H3&         '  显示索引/上下文
Public Const HELP_CONTEXT = &H1           '  在 ulTopic 中显示标题
Public Const HELP_INDEX = &H3             '  显示索引

Global Const APP_CATEGORY = "Wizards"

Global Const CONFIRM_KEY = "ConfirmScreen"
Global Const DONTSHOW_CONFIRM = "DontShow"


'--------------------------------------------------------------------------
'这个程序必须在立即窗口被执行
'它将添加条目到 VBADDIN.INI ,如果此文件不存在
'在下次加载 VB 时此外接程序将生效
'--------------------------------------------------------------------------
Sub AddToINI()
    Debug.Print WritePrivateProfileString("Add-Ins32", WIZARD_NAME & ".Wizard", "0", "VBADDIN.INI")
End Sub

Function GetResString(nRes As Integer) As String
    Dim sTmp As String
    Dim sRetStr As String
  
    Do
        sTmp = LoadResString(nRes)
        If Right(sTmp, 1) = "_" Then
            sRetStr = sRetStr + VBA.Left(sTmp, Len(sTmp) - 1)
        Else
            sRetStr = sRetStr + sTmp
        End If
        nRes = nRes + 1
    Loop Until Right(sTmp, 1) <> "_"
    GetResString = sRetStr
  
End Function

Function GetField(sBuffer As String, sSep As String) As String
    Dim p As Integer
    
    p = InStr(sBuffer & sSep, sSep)
    GetField = VBA.Left(sBuffer, p - 1)
    sBuffer = Mid(sBuffer, p + Len(sSep))
  
End Function

Sub LoadResStrings(frm As Form)
    On Error Resume Next
    
    Dim ctl As Control
    Dim obj As Object
    
    '设置窗体的标题
    If IsNumeric(frm.Tag) Then
        frm.Caption = LoadResString(CInt(frm.Tag))
    End If
    
    '对菜单项使用 caption 属性,对其他控件
    '使用 Tag 属性来设置控件的标题
    For Each ctl In frm.Controls
        If TypeName(ctl) = "Menu" Then
            If IsNumeric(ctl.Caption) Then
                If Err = 0 Then
                    ctl.Caption = LoadResString(CInt(ctl.Caption))
                Else
                    Err = 0
                End If
            End If
        ElseIf TypeName(ctl) = "TabStrip" Then
            For Each obj In ctl.Tabs
                If IsNumeric(obj.Tag) Then
                    obj.Caption = LoadResString(CInt(obj.Tag))
                End If
                '检查一条提示
                If IsNumeric(obj.ToolTipText) Then
                    If Err = 0 Then
                        obj.ToolTipText = LoadResString(CInt(obj.ToolTipText))
                    Else
                        Err = 0
                    End If
                End If
            Next
        ElseIf TypeName(ctl) = "Toolbar" Then
            For Each obj In ctl.Buttons
                If IsNumeric(obj.Tag) Then
                    obj.ToolTipText = LoadResString(CInt(obj.Tag))
                End If
            Next
        ElseIf TypeName(ctl) = "ListView" Then
            For Each obj In ctl.ColumnHeaders
                If IsNumeric(obj.Tag) Then
                    obj.Text = LoadResString(CInt(obj.Tag))
                End If
            Next
        Else
            If IsNumeric(ctl.Tag) Then
                If Err = 0 Then
                    ctl.Caption = GetResString(CInt(ctl.Tag))
                Else
                    Err = 0
                End If
            End If
            '检查一条提示
            If IsNumeric(ctl.ToolTipText) Then
                If Err = 0 Then
                    ctl.ToolTipText = LoadResString(CInt(ctl.ToolTipText))
                Else
                    Err = 0
                End If
            End If
        End If
    Next

End Sub

'==================================================
'目的: 用翻译后内容代替资源文件字符串中
'         <TOPIC_TEXT> 的相对位置中的字符串
'
'输入:  sString = 用来搜索并且替代的字符串
'         sReplacement = 代替被占据的字符串
'         sReplacement2 = 代替被占据第二个字符串
'
'输出: 占据全部需替代位置的新的字符串
'==================================================
Function ReplaceTopicTokens(sString As String, _
                            sReplacement As String, _
                            sReplacement2 As String) As String
    On Error Resume Next
    
    Dim p As Integer
    Dim sTmp As String
    
    Const TOPIC_TEXT = "<TOPIC_TEXT>"
    Const TOPIC_TEXT2 = "<TOPIC_TEXT2>"
    
    sTmp = sString
    Do
        p = InStr(sTmp, TOPIC_TEXT)
        If p Then
            sTmp = VBA.Left(sTmp, p - 1) + sReplacement + Mid(sTmp, p + Len(TOPIC_TEXT))
        End If
    Loop While p
    
    If Len(sReplacement2) > 0 Then
        Do
            p = InStr(sTmp, TOPIC_TEXT2)
            If p Then
                sTmp = VBA.Left(sTmp, p - 1) + sReplacement2 + Mid(sTmp, p + Len(TOPIC_TEXT2))
            End If
        Loop While p
    End If
    
    ReplaceTopicTokens = sTmp
  
End Function

Public Function GetResData(sResName As String, sResType As String) As String
    Dim sTemp As String
    Dim p As Integer
  
    sTemp = StrConv(LoadResData(sResName, sResType), vbUnicode)
    p = InStr(sTemp, vbNullChar)
    If p Then sTemp = VBA.Left$(sTemp, p - 1)
    GetResData = sTemp
End Function

Function AddToAddInCommandBar(VBInst As Object, sCaption As String, oBitmap As Object) As Object   'Office.CommandBarControl
    On Error GoTo AddToAddInCommandBarErr
    
    Dim c As Integer
    Dim cbMenuCommandBar As Object   'Office.CommandBarControl  '命令栏对象
    Dim cbMenu As Object
    
    '察看是否能找到外接程序菜单
    Set cbMenu = VBInst.CommandBars("Add-Ins")
    If cbMenu Is Nothing Then
        '没有可用的菜单操作失败
        Exit Function
    End If
    
    '添加它到命令栏
    Set cbMenuCommandBar = cbMenu.Controls.Add(1)
    c = cbMenu.Controls.Count - 1
    If cbMenu.Controls(c).BeginGroup And _
        Not cbMenu.Controls(c - 1).BeginGroup Then
        '这是第一个被添加的外接程序,所以需要一个分隔符
        cbMenuCommandBar.BeginGroup = True
    End If
    '设置标题
    cbMenuCommandBar.Caption = sCaption
    '取消:设置所做操作 (在这点被要求)
    cbMenuCommandBar.OnAction = "hello"
    '复制图标到剪贴板
    Clipboard.SetData oBitmap
    '为按钮设制图标
    cbMenuCommandBar.PasteFace
  
    Set AddToAddInCommandBar = cbMenuCommandBar
    
    Exit Function
AddToAddInCommandBarErr:
  
End Function



