VERSION 5.00
Object = "{248DD890-BB45-11CF-9ABC-0080C7E7B78D}#1.0#0"; "MSWINSCK.OCX"
Begin VB.Form Form2 
   Caption         =   "TCP/UDP ���Դ���"
   ClientHeight    =   6210
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   8505
   LinkTopic       =   "Form2"
   ScaleHeight     =   6210
   ScaleWidth      =   8505
   StartUpPosition =   3  '����ȱʡ
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
      Caption         =   "�Զ�����"
      Height          =   495
      Left            =   120
      TabIndex        =   15
      Top             =   3360
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_cls_rec 
      Caption         =   "��ս�����"
      Height          =   375
      Left            =   120
      TabIndex        =   14
      Top             =   2880
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_quit 
      Caption         =   "�˳�"
      Height          =   375
      Left            =   7440
      TabIndex        =   13
      Top             =   4920
      Width           =   975
   End
   Begin VB.CommandButton Cmd_cls_send 
      Caption         =   "��շ�����"
      Height          =   375
      Left            =   1440
      TabIndex        =   12
      Top             =   4920
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_send 
      Caption         =   "����"
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
      Caption         =   "GPRS ״̬��"
      Height          =   735
      Left            =   0
      TabIndex        =   4
      Top             =   5400
      Width           =   8535
      Begin VB.Label Label6 
         Caption         =   "Label6"
         Height          =   375
         Left            =   5400
         TabIndex        =   18
         Top             =   240
         Width           =   1215
      End
      Begin VB.Label Label4 
         Caption         =   "Label4"
         Height          =   375
         Left            =   4320
         TabIndex        =   8
         Top             =   240
         Width           =   1095
      End
      Begin VB.Label Label3 
         Caption         =   "Label3"
         Height          =   375
         Left            =   2880
         TabIndex        =   7
         Top             =   240
         Width           =   1575
      End
      Begin VB.Label Label2 
         Caption         =   "Label2"
         Height          =   255
         Left            =   1920
         TabIndex        =   6
         Top             =   240
         Width           =   975
      End
      Begin VB.Label Label1 
         Caption         =   "Label1"
         Height          =   255
         Left            =   120
         TabIndex        =   5
         Top             =   240
         Width           =   1575
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
      Caption         =   "��������"
      Height          =   495
      Left            =   120
      TabIndex        =   2
      Top             =   2040
      Width           =   1215
   End
   Begin VB.CommandButton Cmd_bulid 
      Caption         =   "����GPRS"
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
      Caption         =   "��ʱʱ��(ms)"
      Height          =   255
      Left            =   120
      TabIndex        =   16
      Top             =   3960
      Width           =   1215
   End
   Begin VB.Label Label_mode 
      Caption         =   "GPRSģʽ"
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
    'temp = Val(Trim(InputBox("������˿ں�", "GPRS", "8080")))
    Select Case Combo_mode.Text
        Case "UDP SERVER"
            Cmd_open.Enabled = True
            temp = Val(Trim(InputBox("������˿ں�", "GPRS", "8080")))
            Winsock1.Protocol = sckUDPProtocol
            
            Winsock1.LocalPort = temp
            Winsock1.Bind temp
            If Cmd_open.Caption = "��������" Then
                Cmd_open.Caption = "ֹͣ����"
                Label1.Caption = "UDP SERVER ������"
            End If
        Case "TCP SERVER"
            Cmd_open.Enabled = True
            temp = Val(Trim(InputBox("������˿ں�", "GPRS", "8080")))
            Winsock1.Protocol = sckTCPProtocol
            Winsock1.LocalPort = temp
            Label1.Caption = "TCP SERVER ������"
        Case "TCP CLIENT"
            Cmd_open.Caption = "����GPRS"
            Winsock1.Protocol = sckTCPProtocol
            temp_ip = Trim(InputBox("������Է�IP��ַ", "GPRS", "0.0.0.0"))
            Label2.Caption = temp_ip
            Winsock1.RemoteHost = temp_ip
            temp = Val(Trim(InputBox("������˿ں�", "GPRS", "8080")))
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
        Case "��������"
            Cmd_open.Caption = "ֹͣ����"
            Winsock1.Listen
            Label1.Caption = "TCP SERVER ������"
        Case "ֹͣ����"
            Cmd_open.Caption = "��������"
            Label1.Caption = "TCP CLIENT �ѹر�"
            Winsock1.Close
        Case "����GPRS"
            Cmd_open.Caption = "�Ͽ�GPRS"
            Label1.Caption = "TCP CLIENT ������"
            Winsock1.Connect
        Case "�Ͽ�GPRS"
            Cmd_open.Caption = "����GPRS"
            Label1.Caption = "TCP CLIENT �ѹر�"
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
    Combo_mode.Text = "��ѡ��"
    Cmd_open.Caption = "��������"
    Cmd_cls_rec.Caption = ""
    Text_time.Text = "1000"
    Text_rec.Text = ""
    Text_send.Text = ""
    Cmd_cls_rec.Caption = "��ս�����"
    With Combo_mode
        .AddItem "TCP SERVER"
        .AddItem "TCP CLIENT"
        .AddItem "UDP SERVER"
        .AddItem "UDP CLIENT"
    End With
    Label2.Caption = "�Է�IP"
    'Winsock1.Protocol = sckUDPProtocol
    Label4.Caption = "�Է��˿ں�"
    
    Debug.Print "form_load"
End Sub

Private Sub Text1_Change()

End Sub

Private Sub Text_rec_Change()
    'IF
End Sub
