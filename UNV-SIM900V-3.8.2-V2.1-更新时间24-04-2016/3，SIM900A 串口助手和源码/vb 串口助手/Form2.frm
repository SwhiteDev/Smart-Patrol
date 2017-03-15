VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "mswinsck.ocx"
Begin VB.Form Form2 
   Caption         =   "TCP/UDP TEST"
   ClientHeight    =   7350
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8505
   LinkTopic       =   "Form2"
   ScaleHeight     =   7350
   ScaleWidth      =   8505
   StartUpPosition =   3  '窗口缺省
   Begin VB.Timer Timer1 
      Left            =   2160
      Top             =   480
   End
   Begin VB.TextBox Text_time 
      Height          =   375
      Left            =   120
      TabIndex        =   17
      Text            =   "Text3"
      Top             =   4320
      Width           =   1215
   End
   Begin VB.CheckBox Check_auto_send 
      Caption         =   "AUTO SEND"
      Height          =   495
      Left            =   120
      TabIndex        =   15
      Top             =   3360
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_cls_rec 
      Caption         =   "CLS THE AREA OF REC"
      Height          =   495
      Left            =   120
      TabIndex        =   14
      Top             =   2760
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_quit 
      Caption         =   "QUIT"
      Height          =   375
      Left            =   7440
      TabIndex        =   13
      Top             =   4920
      Width           =   975
   End
   Begin VB.CommandButton Cmd_cls_send 
      Caption         =   "CLS THE AREA OF SEND"
      Height          =   375
      Left            =   1440
      TabIndex        =   12
      Top             =   4920
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_send 
      Caption         =   "SEND"
      Height          =   495
      Left            =   120
      TabIndex        =   10
      Top             =   4800
      Width           =   1215
   End
   Begin VB.TextBox Text_send 
      Height          =   1335
      Left            =   1440
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   9
      Text            =   "Form2.frx":0000
      Top             =   3480
      Width           =   6975
   End
   Begin VB.Frame Frame1 
      Caption         =   "THE STARUSGPRS"
      Height          =   1695
      Left            =   0
      TabIndex        =   4
      Top             =   5400
      Width           =   8535
      Begin VB.Label Label6 
         Caption         =   "Label6"
         Height          =   375
         Left            =   2280
         TabIndex        =   18
         Top             =   1200
         Width           =   3855
      End
      Begin VB.Label Label4 
         Caption         =   "Label4"
         Height          =   375
         Left            =   120
         TabIndex        =   8
         Top             =   1200
         Width           =   1935
      End
      Begin VB.Label Label3 
         Caption         =   "Label3"
         Height          =   375
         Left            =   5280
         TabIndex        =   7
         Top             =   240
         Width           =   2895
      End
      Begin VB.Label Label2 
         Caption         =   "Label2"
         Height          =   375
         Left            =   2400
         TabIndex        =   6
         Top             =   240
         Width           =   2655
      End
      Begin VB.Label Label1 
         Caption         =   "Label1"
         Height          =   495
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   2055
      End
   End
   Begin VB.ComboBox Combo_mode 
      Height          =   300
      Left            =   120
      TabIndex        =   3
      Text            =   "Combo1"
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_open 
      Caption         =   "START TO LISTEN"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   2040
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_bulid 
      Caption         =   "CREAT GPRS"
      Height          =   495
      Left            =   120
      TabIndex        =   1
      Top             =   1320
      Width           =   1215
   End
   Begin VB.TextBox Text_rec 
      Height          =   3015
      Left            =   1440
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   0
      Text            =   "Form2.frx":0006
      Top             =   240
      Width           =   6975
   End
   Begin MSWinsockLib.Winsock Winsock1 
      Left            =   1920
      Top             =   480
      _ExtentX        =   741
      _ExtentY        =   741
      _Version        =   393216
   End
   Begin VB.Label Label5 
      Caption         =   "TIMER(ms)"
      Height          =   255
      Left            =   120
      TabIndex        =   16
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label Label_mode 
      Caption         =   "GPRS MODE"
      Height          =   255
      Left            =   120
      TabIndex        =   11
      Top             =   240
      Width           =   1215
   End
End
Attribute VB_Name = "Form2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()

End Sub

Private Sub Cmd_bulid_Click()
    Dim temp As Integer
    Dim temp_ip As String
    'On Error GoTo err_dis
    'temp = Val(Trim(InputBox("请输入端口号", "GPRS", "8080")))
    Select Case Combo_mode.Text
        Case "UDP SERVER"
            Cmd_open.Enabled = True
            temp = Val(Trim(InputBox("请输入端口号", "GPRS", "8080")))
            Winsock1.Protocol = sckUDPProtocol
            
            Winsock1.LocalPort = temp
            Winsock1.Bind temp
            If Cmd_open.Caption = "启动监听" Then
                Cmd_open.Caption = "停止监听"
                Label1.Caption = "UDP SERVER 已连接"
            End If
        Case "TCP SERVER"
            Cmd_open.Enabled = True
            temp = Val(Trim(InputBox("请输入端口号", "GPRS", "8080")))
            Winsock1.Protocol = sckTCPProtocol
            Winsock1.LocalPort = temp
            Label1.Caption = "TCP SERVER 已连接"
        Case "TCP CLIENT"
            Cmd_open.Caption = "连接GPRS"
            Winsock1.Protocol = sckTCPProtocol
            temp_ip = Trim(InputBox("请输入对方IP地址", "GPRS", "0.0.0.0"))
            Label2.Caption = temp_ip
            Winsock1.RemoteHost = temp_ip
            temp = Val(Trim(InputBox("请输入端口号", "GPRS", "8080")))
            Winsock1.RemotePort = temp
            Label6.Caption = temp
            'Winsock1.Listen
            'Cmd_open.Enabled = False
            
            
        Case "UDP CLIENT"
            
        
            
    End Select
    'Winsock1.LocalPort = 8080
    'Winsock1.Bind 8080
    Debug.Print "port ok"
'err_dis: MsgBox "GPRS error!"
    
End Sub

Private Sub Cmd_open_Click()
    On Error GoTo err1
    Select Case Cmd_open.Caption
        Case "START TO LISTEN"
            Cmd_open.Caption = "STOP TO LISTEN"
            Winsock1.Listen
            Label1.Caption = "TCP SERVER CONNECTED"
        Case "STOP TO LISTEN"
            Cmd_open.Caption = "START TO LISTEN"
            Label1.Caption = "TCP CLIENT CLOSED"
            Winsock1.Close
        Case "CONNECT THE GPRS"
            Cmd_open.Caption = "SHUT DOWN THE GPRS"
            Label1.Caption = "TCP CLIENT CONNECTED"
            Winsock1.Connect
        Case "SHUT DOWN THE GPRS"
            Cmd_open.Caption = "CONNECT THE GPRS"
            Label1.Caption = "TCP CLIENT CLOSED"
            Winsock1.Close
    End Select
err1: MsgBox ("GPRS ERROR!")
End Sub

Private Sub Cmd_send_Click()
        Winsock1.SendData Text_send.Text
End Sub

Private Sub winsock1_close()
    Dim temp As String
    Label1.Caption = "close"
    Winsock1.Close
    Winsock1.Listen
End Sub
Private Sub Winsock1_ConnectionRequest(ByVal requestID As Long)
    If Winsock1.State <> sckClosed Then
      Winsock1.Close
    End If
    Call Winsock1.Accept(requestID)
    'Label3.Caption = Winsock1.RemoteHostIP
    'txtOutput.Text = "Connection from IP address:" & Winsock1.RemoteHostIP & vbCrLf & "Port #:" & Winsock1.RemotePort & vbCrLf & vbCrLf
    Debug.Print "requesid"
    Debug.Print requestID
End Sub
Private Sub Winsock1_DataArrival(ByVal bytesTotal As Long)
    Dim temp As String
    Dim message As String
    Winsock1.GetData message
    Label3.Caption = Winsock1.RemoteHostIP
    Label6.Caption = "port: " & Winsock1.RemotePort
    temp = Time & " : " & message & vbCrLf
    Text_rec.Text = Text_rec.Text & temp
    Text_rec.SelStart = Len(Text_rec.Text)
    Debug.Print "recetiv ok"
End Sub


Private Sub Cmd_cls_rec_Click()
    Text_rec.Text = ""
End Sub

Private Sub Cmd_cls_send_Click()
    Text_send.Text = ""
End Sub

Private Sub Cmd_quit_Click()
    Unload Me
End Sub

Private Sub Form_Load()
    Combo_mode.Text = "PLEASE TO SELECT"
    Cmd_open.Caption = "START TO LISTEN"
    Cmd_cls_rec.Caption = ""
    Text_time.Text = "1000"
    Text_rec.Text = ""
    Text_send.Text = ""
    Cmd_cls_rec.Caption = "CLS THE AREA OF REC"
    With Combo_mode
        .AddItem "TCP SERVER"
        .AddItem "TCP CLIENT"
        .AddItem "UDP SERVER"
        .AddItem "UDP CLIENT"
    End With
    Label2.Caption = "THE IP OF THE OTHER SIDE"
    'Winsock1.Protocol = sckUDPProtocol
    Label4.Caption = "THE PORT OF THE OTHER SIDE"
    'text1.
    Debug.Print "form_load"
End Sub

Private Sub Text1_Change()

End Sub

Private Sub Text_rec_Change()
    'IF
End Sub
