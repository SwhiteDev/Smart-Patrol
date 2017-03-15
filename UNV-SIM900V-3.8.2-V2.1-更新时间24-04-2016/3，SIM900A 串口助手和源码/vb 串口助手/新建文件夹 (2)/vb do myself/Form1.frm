VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   9165
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8535
   LinkTopic       =   "Form1"
   ScaleHeight     =   9165
   ScaleWidth      =   8535
   StartUpPosition =   3  '窗口缺省
   Begin VB.Frame Frame1 
      Caption         =   "绘图区"
      Height          =   3135
      Left            =   120
      TabIndex        =   23
      Top             =   5880
      Width           =   8295
      Begin VB.PictureBox Picture1 
         Height          =   2655
         Left            =   2760
         ScaleHeight     =   2595
         ScaleWidth      =   4995
         TabIndex        =   27
         Top             =   240
         Width           =   5055
      End
      Begin VB.CommandButton Command1 
         Caption         =   "Command1"
         Height          =   495
         Left            =   240
         TabIndex        =   25
         Top             =   1320
         Width           =   1215
      End
      Begin VB.Timer Timer2 
         Left            =   6600
         Top             =   480
      End
      Begin VB.TextBox Text1 
         Height          =   375
         Left            =   240
         TabIndex        =   24
         Text            =   "Text1"
         Top             =   720
         Width           =   1215
      End
      Begin VB.Label Label4 
         Caption         =   "Label4"
         Height          =   375
         Left            =   240
         TabIndex        =   26
         Top             =   360
         Width           =   1215
      End
   End
   Begin VB.TextBox Text_rec 
      Height          =   4215
      Left            =   1440
      Locked          =   -1  'True
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   22
      Text            =   "Form1.frx":0000
      Top             =   120
      Width           =   6975
   End
   Begin VB.CommandButton Cmd_cls_send 
      Caption         =   "清除发送区"
      Height          =   375
      Left            =   120
      TabIndex        =   21
      Top             =   5400
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_clsrec 
      Caption         =   "清除接收区"
      Height          =   375
      Left            =   120
      TabIndex        =   19
      Top             =   2640
      Width           =   1215
   End
   Begin VB.Timer Timer1 
      Left            =   4200
      Top             =   1920
   End
   Begin MSCommLib.MSComm MSComm1 
      Left            =   4200
      Top             =   1080
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.TextBox Text_timer 
      Height          =   270
      Left            =   120
      TabIndex        =   17
      Text            =   "Text1"
      Top             =   4080
      Width           =   855
   End
   Begin VB.CheckBox Check_autosend 
      Caption         =   "自动发送"
      Height          =   255
      Left            =   120
      TabIndex        =   16
      Top             =   3720
      Width           =   1095
   End
   Begin VB.CheckBox Check_hex_send 
      Caption         =   "hex发送"
      Height          =   375
      Left            =   120
      TabIndex        =   15
      Top             =   3360
      Width           =   1215
   End
   Begin VB.CheckBox Check_hex_dis 
      Caption         =   "hex 显示"
      Height          =   495
      Left            =   120
      TabIndex        =   14
      Top             =   3000
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_clsnum 
      Caption         =   "清除计数"
      Height          =   375
      Left            =   1440
      TabIndex        =   13
      Top             =   5400
      Width           =   1215
   End
   Begin VB.CommandButton cmd_openport 
      Caption         =   "Command2"
      Height          =   495
      Left            =   120
      TabIndex        =   12
      Top             =   2040
      Width           =   1215
   End
   Begin VB.ComboBox Combo_stopbyte 
      Height          =   300
      Left            =   120
      TabIndex        =   7
      Text            =   "Combo1"
      Top             =   1200
      Width           =   1215
   End
   Begin VB.ComboBox Combo_jiaoyan 
      Height          =   300
      Left            =   120
      TabIndex        =   6
      Text            =   "Combo1"
      Top             =   1560
      Width           =   1215
   End
   Begin VB.ComboBox Combo_databyte 
      Height          =   300
      Left            =   120
      TabIndex        =   5
      Text            =   "Combo1"
      Top             =   840
      Width           =   1215
   End
   Begin VB.ComboBox Combo_rate 
      Height          =   300
      Left            =   120
      TabIndex        =   4
      Text            =   "Combo1"
      Top             =   480
      Width           =   1215
   End
   Begin VB.ComboBox Comb_comport 
      Height          =   300
      Left            =   120
      TabIndex        =   3
      Text            =   "combo1"
      Top             =   120
      Width           =   1215
   End
   Begin VB.TextBox Text_send 
      Height          =   615
      Left            =   1440
      MultiLine       =   -1  'True
      TabIndex        =   2
      Text            =   "Form1.frx":0008
      Top             =   4440
      Width           =   6975
   End
   Begin VB.CommandButton Cmd_send 
      Caption         =   "发送"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   4560
      Width           =   1215
   End
   Begin VB.CommandButton cmd_quit 
      Caption         =   "退出"
      Height          =   375
      Left            =   7440
      TabIndex        =   0
      Top             =   5400
      Width           =   975
   End
   Begin VB.Label Label2 
      Caption         =   "Label2"
      Height          =   375
      Left            =   5760
      TabIndex        =   20
      Top             =   5160
      Width           =   2655
   End
   Begin VB.Label Label5 
      Caption         =   "ms"
      Height          =   375
      Left            =   1080
      TabIndex        =   18
      Top             =   4200
      Width           =   375
   End
   Begin VB.Label Label_num_rec 
      Caption         =   "Label4"
      Height          =   375
      Left            =   4200
      TabIndex        =   11
      Top             =   5160
      Width           =   975
   End
   Begin VB.Label Label3 
      Caption         =   "已接收"
      Height          =   375
      Left            =   3360
      TabIndex        =   10
      Top             =   5160
      Width           =   735
   End
   Begin VB.Label Label_num_send 
      Caption         =   "Label2"
      Height          =   375
      Left            =   2400
      TabIndex        =   9
      Top             =   5160
      Width           =   855
   End
   Begin VB.Label Label1 
      Caption         =   "已发送"
      Height          =   255
      Left            =   1440
      TabIndex        =   8
      Top             =   5160
      Width           =   735
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim auto_send_flag  As Integer
Dim hex_send_flag As Integer
Dim text_send_preserve As String
Dim flag_ok As Integer
Dim flag_ok1 As Integer
Dim startlen As Integer
Dim stoplen As Integer
Dim hex_rec_flag As Integer



Private Sub Check_autosend_Click()
    If Check_autosend.Value = vbChecked And cmd_openport.Caption = "关闭串口" Then
        Timer1.Enabled = True
        auto_send_flag = 1
    Else
         If Check_autosend.Value = vbUnchecked Then
         auto_send_flag = 0
        Timer1.Enabled = False
        End If
        
    End If
    
End Sub
Function send_hex()
    If Check_hex_send.Value = vbChecked Then
        hex_send_flag = 1
    Else
        hex_send_flag = 0
    End If
    
    
End Function

Private Sub Check_hex_dis_Click()
    If Check_hex_dis.Value = vbChecked Then
        hex_rec_flag = 1
    Else
        hex_rec_flag = 0
    End If
End Sub

Private Sub Check_hex_send_Click()
    If Check_hex_send.Value = vbChecked Then
        hex_send_flag = 1
    Else
        hex_send_flag = 0
    End If
End Sub

Private Sub Cmd_changshang_Click()
    MSComm1.Output = "AT+CGMI" & vbCrLf
End Sub

Private Sub Cmd_cls_send_Click()
    Text_send.Text = ""
End Sub

Private Sub Cmd_cls_sended_Click()
    Text_sended.Text = ""
End Sub

Private Sub Cmd_clsnum_Click()
'    MSComm1.PortOpen = False
    Label_num_rec.Caption = "0"
    Label_num_send.Caption = "0"
End Sub

Function send_data()
    
    If hex_send_flag = 0 Then
        MSComm1.Output = Text_send.Text
        'Label_num_send.Caption = Chr(Len(Text_send.Text) + Len(Label_num_send))
        Label_num_send.Caption = Val(Label_num_send.Caption) + Len(Text_send.Text)
    Else
        Call hexSend
    End If
End Function

Private Sub Cmd_clsrec_Click()
    Text_rec.Text = ""
End Sub

Private Sub Cmd_devicetype_Click()
MSComm1.Output = "at+cgmm" & vbCr
End Sub

Private Sub Cmd_divicenum_Click()
    MSComm1.Output = "at+cgsn" & vbCr
End Sub

Private Sub Cmd_gprs_show_Click()
    If Cmd_gprs_show.Caption = "打开GPRS调试" Then
        Cmd_gprs_show.Caption = "关闭GPRS调试"
        Form2.Show
    Else
        Cmd_gprs_show.Caption = "打开GPRS调试"
            Form2.Hide
    End If
End Sub

Private Sub Cmd_gprsstatus_Click()
    MSComm1.Output = "at+cipstatus" & vbCr
End Sub

Private Sub CMD_NETSTA_Click()
    MSComm1.Output = "at+cops?" & vbCr
End Sub

Private Sub Cmd_quit_Click()
    Unload Me
End Sub

Private Sub Cmd_send1_Click()
    
    Dim temp_text As String
    Dim temp As String
    temp = """"
    temp_text = Time & "  " & Text_send1.Text & " " & Text_send2.Text & vbCrLf
    Text_sended.SelStart = Len(Text_sended.Text)
    Text_sended.Text = Text_sended.Text & temp_text
    startlen = Val(Trim(Text_rec.Text))
    
    On Error Resume Next
    If Err = 8018 Then
        MsgBox ("设备未打开")
    End If
    Debug.Print "abc" ' Print "abc"
    Select Case Comb_mode.Text
        Case "发送短信"
           MSComm1.Output = "at+cnmi=2,1" & vbCr    'open diplay
            Select Case Comb_type.Text
                Case "英文发送"
                    Timer2.Enabled = True
                    Timer2.Interval = 3000
                Case "中文发送"
                    Timer2.Enabled = True
                    Timer2.Interval = 3000
            End Select
        Case "读取短信"
           Select Case Comb_type.Text
                Case "打开回显"
                Timer2.Enabled = True
                Timer2.Interval = 3000
           End Select
        Case "GPRS"
            Select Case Comb_type.Text
                Case "UDP"
                    Timer2.Enabled = True
                    Timer2.Interval = 3000
                     MSComm1.Output = "at+clport=" & temp & "UDP" & temp & "," & temp & "1001" & temp & vbCr
                Case "TCP"
                    Timer2.Enabled = True
                    Timer2.Interval = 3000
                     MSComm1.Output = "at+clport=" & temp & "TCP" & temp & "," & temp & "1001" & temp & vbCr
            End Select
    End Select
    
End Sub


Private Sub Cmd_SIMSTA_Click()
    MSComm1.Output = "at+cpin?" & vbCr
End Sub

Private Sub Combo1_Change()

End Sub

Private Sub Comb_mode_click()
    Comb_type.Clear
    Text_send1.Visible = True
    Text_send2.Visible = True
    Select Case Comb_mode.Text
        Case "发送短信"
            With Comb_type
                .AddItem "英文发送"
                .AddItem "中文发送"
                .Text = "请选择"
            End With
            Label6.Caption = "选择短信发送方式"
            
            
        Case "读取短信"
            With Comb_type
                .AddItem "打开回显"
                .Text = "请选择"
            End With
            Label6.Caption = "打开回显并等待"
            Text_send1.Text = "请输入所要读取短信所在的位置号"
            'Text_send1.Visible = False
            Text_send2.Visible = False
        Case "GPRS"
            With Comb_type
                .AddItem "UDP"
                .AddItem "TCP"
                .Text = "请选择"
            End With
            Label6.Caption = "选择GPRS方式"
            Text_send1.Text = "请输入对方的IP地址,端口号"
            Text_send2.Text = "请输入要发送的内容"
    End Select
End Sub

Private Sub Command3_Click()
    Text_sended.Text = ""
End Sub

Private Sub Comb_type_click()
    Select Case Comb_type.Text
        Case "英文发送"
            Text_send1.Text = "请输入要发送的电话号码"
            Text_send2.Text = "请输入要发送的内容"
        Case "中文发送"
            Text_send1.Text = "请输入要发送的的字符串数"
            Text_send2.Text = "请输入要发送的内容（PDU码）"
    End Select
End Sub

Private Sub Text_rec_Change()
    Text_rec.SelStart = Len(Text_rec.Text)
    'Text1.SelLength = Len(Text1.Text)
    Text_rec.SelLength = Len(Text_rec.Text)
    If (Val(Len(Text_rec.Text)) > 5000) Then
        Call Cmd_clsrec_Click
    End If
End Sub


Private Sub Text_send_Change()
    text_send_preserver = Text_send.Text
End Sub

Private Sub Text_send1_click()
    Text_send1.Text = ""
    'Text_send2.Text = ""
End Sub

Private Sub Text_send2_click()
    Text_send2.Text = ""
End Sub

Private Sub Text_sended_Change()
    Text_sended.SelLength = Len(Text_sended.Text)
End Sub

Sub Timer1_Timer()
    Timer1.Interval = Val(Text_timer.Text)
    'Timer1.Enabled = True
    Call send_data
End Sub
Sub mscomm1_oncomm()
   Dim temp_rec() As Byte
   Dim temp As String
   Dim temp_text As String
   temp = "OK"
   'Dim stoplen As Integer
   Select Case MSComm1.CommEvent
        Case comEvReceive
          
            temp_rec() = MSComm1.Input
            Label_num_rec.Caption = str(Val(Label_num_rec) + UBound(temp_rec()) + 1)
            For i = 0 To UBound(temp_rec())
                If hex_rec_flag = 0 Then
                    Text_rec.Text = Text_rec.Text & Chr(Val(temp_rec(i)))
                    'Text_rec.SelStart = Len(Text_rec.Text)
            
                Else
                    Text_rec.Text = Text_rec.Text & Right("0" & Hex(Val(Trim(temp_rec(i)))), 2) & "  "    '十六进制接收
                End If
            Next i
        
   End Select
End Sub

Private Sub Cmd_openport_Click()
    Dim a As String
    If cmd_openport.Caption = "打开串口" Then
e1:
        MSComm1.CommPort = Val(Right(Comb_comport.Text, 1))
        On Error Resume Next        '判断该串口是否被打开
        MSComm1.PortOpen = True
        If Err = 8005 Then
            MSComm1.PortOpen = False
            a = MsgBox("串口被占用", 21)
            If a = 4 Then           '如果按下重试按键 重复执行
                GoTo e1
            End If
        
        Else
        With MSComm1
            .Settings = Trim(Combo_rate.Text) & "," & Left(Trim(Combo_jiaoyan.Text), 1) & "," & Trim(Combo_databyte.Text) & "," & Trim(Combo_stopbyte)
            .RThreshold = 1
            .InputMode = comInputModeBinary
        End With
        cmd_openport.Caption = "关闭串口"
        'Cmd_openport.Enabled = False
        Cmd_send.Enabled = True
        a = MSComm1.Input
        Comb_comport.Enabled = False
        Combo_rate.Enabled = False
        Combo_databyte.Enabled = False
        Combo_stopbyte.Enabled = False
        Combo_jiaoyan.Enabled = False
        
        If Check_autosend.Value = vbChecked Then
            auto_send_flag = 1
            Timer1.Enabled = True
            Timer1.Interval = Val(Text_timer.Text)
        Else
            auto_send_flag = 0
            Timer1.Enabled = False
        End If
        
        If Check_hex_send.Value = vbChecked Then
            hex_send_flag = 1
        Else
            hex_send_flag = 0
        End If
        
'        Check_hex_dis.Enabled = False
'        Check_hex_send.Enabled = False
'        Check_autosend.Enabled = False
        'Call rec_data
        'Call send_data
        'Call auto_send
        Label2.Caption = Comb_comport.Text & " " & "已打开" & " " & Combo_rate.Text & " " & Combo_databyte.Text & " " & Combo_stopbyte.Text & " " & Combo_jiaoyan.Text
        End If
    Else
        MSComm1.PortOpen = False
        
        cmd_openport.Caption = "打开串口"
        cmd_openport.Enabled = True
        Combo_rate.Enabled = True
        Comb_comport.Enabled = True
        Combo_databyte.Enabled = True
        Combo_stopbyte.Enabled = True
        Combo_jiaoyan.Enabled = True
        
        Cmd_send.Enabled = False
        Check_hex_dis.Enabled = True
        Check_hex_send.Enabled = True
        Check_autosend.Enabled = True
        Timer1.Enabled = False
        
        Label2.Caption = Comb_comport.Text & " " & "已关闭" & " " & Combo_rate.Text & " " & Combo_databyte.Text & " " & Combo_stopbyte.Text & " " & Combo_jiaoyan.Text
    End If

    
    
    
End Sub

Private Sub Cmd_send_Click()
    Call send_data
End Sub

Private Sub Form_Load()
    Dim i As Integer
    Dim comport_use() As String
    'call comport_get(comport_use() as string)
    Call comport_get(comport_use())
    For i = 0 To UBound(comport_use()) - 1
        Comb_comport.AddItem "com" & comport_use(i)
        
    Next i
    Comb_comport.Text = "com" & comport_use(0)
    
    
    Combo_rate.AddItem 110
    For i = 0 To 7
        Combo_rate.AddItem 300 * 2 ^ i
    Next i
    With Combo_rate
        .AddItem 14400, 7
        .AddItem 56000
        .AddItem 57600
        .AddItem 115200
        .AddItem 128000
        .AddItem 256000
    End With

    Combo_rate.Text = "9600"
    For i = 4 To 8
        Combo_databyte.AddItem i
    Next i
    Combo_databyte.Text = "8"
    Combo_stopbyte.AddItem "1"
    Combo_stopbyte.AddItem "1.5"
    Combo_stopbyte.AddItem "2"
    Combo_stopbyte.Text = "1"
    
    Text_send1.Text = ""
    Text_send2.Text = ""
    
    Combo_jiaoyan.AddItem "NONE"
    Combo_jiaoyan.AddItem "Odd"
    Combo_jiaoyan.AddItem "EVEN"
    Combo_jiaoyan.Text = "NONE"
    Text_sended.Text = ""
    Label7.Caption = "已发送区"
    Comb_type.Text = "请选择"
    Comb_mode.Text = "请选择"
    
    Label4.Caption = "通信模式"
    Label6.Caption = "方式选择"
    
    Text_sended.BackColor = &HFFFFC0
    Text_rec.BackColor = &HFFFFC0
    
    With Comb_mode
        .AddItem "发送短信"
        .AddItem "读取短信"
        .AddItem "GPRS"
       ' .Text = "发送短信"
    End With
    
    cmd_openport.Caption = "打开串口"
    Cmd_send.Enabled = False
    
    num_show_form2 = 0
    
    Label_num_send.Caption = "0"
    Label_num_rec.Caption = "0"
    
    Text_rec.Text = ""
    'Text_rec.Enabled = False
    Text_send.Text = ""
    Text_timer.Text = "1000"
    
    Text_send.Text = text_send_preserver
    
    Form1.Caption = "串口助手 v1.0"
    
    Label2.Caption = Comb_comport.Text & " " & "已关闭" & " " & Combo_rate.Text & " " & Combo_databyte.Text & " " & Combo_stopbyte.Text & " " & Combo_jiaoyan.Text
    
End Sub
Function comport_get(comport() As String)
    Dim i As Integer
    ReDim Preserve comport(0)
    For i = 1 To 255
        On Error Resume Next
        MSComm1.CommPort = i
        MSComm1.PortOpen = True
        If Err = 0 Or Err = 8005 Then
        comport(UBound(comport())) = i
        ReDim Preserve comport(UBound(comport()) + 1)
        MSComm1.PortOpen = False
        End If
    Next i
End Function

Private Sub Text1_Change()

End Sub

Private Sub timer2_timer()
    Dim temp As String
    temp = """"
    Timer2.Enabled = False
    Select Case Comb_type.Text
        Case "英文发送"
            MSComm1.Output = "at+cmgf=1" & vbCr
        Case "中文发送"
            MSComm1.Output = "at+cmgf=0" & vbCrLf
        Case "打开回显"
            MSComm1.Output = "at+cnmi=2,1" & vbCr
        Case "UDP"
            'Text_send1.Text = temp & Left(Text_send1.Text, 3) & temp & Mid(Text_send1.Text, 4, 1) & temp & Right(Text_send1.Text, 4) & temp
            'MSComm1.Output = "at+clport" & Trim(Text_send1.Text) & vbCr
             MSComm1.Output = "at+cipstart=" & temp & "UDP" & temp & "," & temp & Left(Text_send1.Text, Len(Text_send1.Text) - 4) & temp & "," & temp & Right(Text_send1.Text, 4) & temp & vbCr
            'MSComm1.Output = "at+clport=" & temp & UDP & temp & "," & temp & "1001" & temp & vbCr
        Case "TCP"
            MSComm1.Output = "at+cipstart=" & temp & "TCP" & temp & "," & temp & Left(Text_send1.Text, Len(Text_send1.Text) - 4) & temp & "," & temp & Right(Text_send1.Text, 4) & temp & vbCr
            'MSComm1.Output = "at+clport=" & temp & "TCP" & temp & "," & temp & "1001" & temp & vbCr
            'Text_send1.Text = temp & Left(Text_send1.Text, 3) & temp & Mid(Text_send1.Text, 4, 1) & temp & Right(Text_send1.Text, 4) & temp
            'MSComm1.Output = "at+clport" & Trim(Text_send1.Text) & vbCr
    End Select
    
    Timer3.Interval = 3000
    Timer3.Enabled = True
    Debug.Print "timer2 ok"
    

End Sub

Private Sub Timer3_Timer()
    Debug.Print "timer3 begin"
    Timer3.Enabled = False
    Dim temp As String
    temp = """"
    Select Case Comb_type.Text
        Case "英文发送"
            'Text_send1.Text = temp & Trim(Text_send1.Text) & temp
            Timer3.Enabled = False
            MSComm1.Output = "at+cmgs=" & temp & Trim(Text_send1.Text) & temp & vbCr
        Case "中文发送"
            MSComm1.Output = "at+cmgs=" & Val(Trim(Text_send1.Text)) & vbCrLf
        Case "打开回显"
            MSComm1.Output = "at+cmgr=" & Val(Trim(Text_send1.Text)) & vbCrLf
        Case "UDP"
            MSComm1.Output = "AT+CIPSEND" & vbCr
        Case "TCP"
            MSComm1.Output = "AT+CIPSEND" & vbCr
        
        End Select
    Timer4.Interval = 3000
    Timer4.Enabled = True

    Debug.Print "error"
End Sub

Private Sub Timer4_Timer()
    Debug.Print "timer4 begin"
    Timer4.Enabled = False
    Select Case Comb_type.Text
        Case "英文发送"
            MSComm1.Output = Trim(Text_send2.Text)
        Case "中文发送"
            MSComm1.Output = Trim(Text_send2.Text)
        Case "UDP"
            MSComm1.Output = Trim(Text_send2.Text)
        Case "TCP"
            MSComm1.Output = Trim(Text_send2.Text)
    End Select
    Timer5.Interval = 3000
    Timer5.Enabled = True
End Sub

Private Sub Timer5_Timer()
    Debug.Print "timer5 begin"
    Dim temp(0) As Byte
    Timer5.Enabled = False
    temp(0) = &H1A
    MSComm1.Output = temp
  
    
End Sub
Private Sub hexSend()
On Error Resume Next
     Dim outputLen As Integer                                                         '  发送数据长度
     Dim outData As String                                                            '  发送数据暂存
     Dim SendArr() As Byte                                                            '  发送数组
     Dim TemporarySave As String                                                      '  数据暂存
     Dim dataCount As Integer                                                         '  数据个数计数
     Dim i As Integer                                                                 '  局部变量
     
     outData = UCase(Replace(Text_send.Text, Space(1), Space(0)))                         '  先去掉空格，再转换为
     outData = UCase(outData)                                                         '  转换成大写
     outputLen = Len(outData)                                                         '  数据长度
     
    For i = 0 To outputLen
        TemporarySave = Mid(outData, i + 1, 1)                                       '  取一位数据
        If (Asc(TemporarySave) >= 48 And Asc(TemporarySave) <= 57) Or (Asc(TemporarySave) >= 65 And Asc(TemporarySave) <= 70) Then
             dataCount = dataCount + 1
        Else
            Exit For
            Exit Sub
        End If
    Next
     
    If dataCount Mod 2 <> 0 Then                                                     '  判断十六进制数据是否为双数
         dataCount = dataCount - 1                                                    '  不是双数，则减1
    End If
     
     outData = Left(outData, dataCount)                                               '  取出有效的十六进制数据
     
    ReDim SendArr(dataCount / 2 - 1)                                                 '  重新定义数组长度
    For i = 0 To dataCount / 2 - 1
        SendArr(i) = Val("&H" + Mid(outData, i * 2 + 1, 2))                          '  取出数据转换成十六进制并
    Next
     
    sendcount = dataCount / 2                                          '  计算总发送数
    Label_num_send.Caption = Val(Trim(Label_num_send.Caption)) + sendcount
    Debug.Print "hex"
    Text_send.Text = SendArr
    MSComm1.Output = SendArr                                                          '  发送数据
End Sub
'**********************************************************************
'hexTochar(strText As String, bytByte() As Byte) 十六进制转字节型函数（两位转换方式，不通用）
'strText 十六进制参数，字符串型
'hexTochar(strText As String, bytByte() As Byte) 返回长整型    0：正常转换 -1：无可转换数据
'**********************************************************************
Function hexTochar(strText As String, bytByte() As Byte) As Long
Dim strHex As String
Dim i As Integer
If Len(strText) > 1 Then
    ReDim bytByte(0)
    i = 1
    Do
        strHex = Mid(strText, i, 2)
        If i = 1 Then
            bytByte(0) = HexToDec(strHex)
        Else
            ReDim Preserve bytByte(UBound(bytByte) + 1)
            bytByte(UBound(bytByte)) = HexToDec(strHex)
        End If
        i = i + 2
    Loop Until i > Int(Len(strText) / 2) * 2
    hexTochar = 0
Else
    hexTochar = -1
End If
End Function


'**********************************************************************
'HexToDec(str) 十六进制转十进制函数
'str 十六进制参数，字符串型
'HexToDec(str) 返回整型
'**********************************************************************
Function HexToDec(str As String) As Integer
Dim temp As String
Dim TempInt As Integer
Dim n As Integer
For i = 0 To Len(str) - 1
    temp = Mid(str, Len(str) - i, 1)
    If Asc(temp) >= 65 Then
        For j = 65 To 70
            If j = Asc(temp) Then TempInt = j - 55
        Next j
    Else
        TempInt = Val(temp)
    End If
    n = TempInt * 16 ^ i + n
Next i
HexToDec = n
End Function

