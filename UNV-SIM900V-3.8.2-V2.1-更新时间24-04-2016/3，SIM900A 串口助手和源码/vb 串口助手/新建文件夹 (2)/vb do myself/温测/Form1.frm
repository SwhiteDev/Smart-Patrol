VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5085
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   7260
   LinkTopic       =   "Form1"
   ScaleHeight     =   5085
   ScaleWidth      =   7260
   StartUpPosition =   3  '窗口缺省
   Begin VB.Timer Timer1 
      Left            =   5040
      Top             =   4440
   End
   Begin VB.PictureBox Picture2 
      Height          =   3015
      Left            =   480
      ScaleHeight     =   2955
      ScaleWidth      =   3075
      TabIndex        =   2
      Top             =   240
      Width           =   3135
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Command1"
      Height          =   615
      Left            =   2880
      TabIndex        =   1
      Top             =   4440
      Width           =   975
   End
   Begin VB.PictureBox Picture1 
      Height          =   1095
      Left            =   4200
      ScaleHeight     =   1035
      ScaleWidth      =   2715
      TabIndex        =   0
      Top             =   120
      Width           =   2775
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim temp1, temp2, heng As Integer
Private Sub Command1_Click()
   Picture1.BackColor = vbGreen
   Picture1.Cls

   Picture1.ScaleMode = 3      '像素
   Picture1.Scale (-20, 120)-(110, -20) '定义左上角座标为(-20,120),右下角座标为110,-20)
   
   '设置绘线宽度
   Picture1.DrawWidth = 1

'    绘坐标横线
     Picture1.Line (0, 0)-(110, 0), vbBlack
     Picture1.Line (0, 10)-(100, 10), vbBlack
     Picture1.Line (0, 20)-(100, 20), vbBlack
     Picture1.Line (0, 30)-(100, 30), vbBlack
     Picture1.Line (0, 40)-(100, 40), vbBlack
     Picture1.Line (0, 50)-(100, 50), vbBlack
     Picture1.Line (0, 60)-(100, 60), vbBlack
     Picture1.Line (0, 70)-(100, 70), vbBlack
     Picture1.Line (0, 80)-(100, 80), vbBlack
     Picture1.Line (0, 90)-(100, 90), vbBlack
     Picture1.Line (0, 100)-(100, 100), vbBlack

     '    绘坐标纵线
     Picture1.Line (0, 0)-(0, 120), vbBlack
     Picture1.Line (10, 0)-(10, 100), vbBlack
     Picture1.Line (20, 0)-(20, 100), vbBlack
     Picture1.Line (30, 0)-(30, 100), vbBlack
     Picture1.Line (40, 0)-(40, 100), vbBlack
     Picture1.Line (50, 0)-(50, 100), vbBlack
     Picture1.Line (60, 0)-(60, 100), vbBlack
     Picture1.Line (70, 0)-(70, 100), vbBlack
     Picture1.Line (80, 0)-(80, 100), vbBlack
     Picture1.Line (90, 0)-(90, 100), vbBlack
     Picture1.Line (100, 0)-(100, 100), vbBlack
     Picture1.Line (110, 0)-(110, 100), vbBlack

     '指定位置显示原点O
     Picture1.CurrentX = -5
     Picture1.CurrentY = 0
     Picture1.Print "O"
     
'      指定位置显示1O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 10
     Picture1.Print "1O"
     
     '      指定位置显示2O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 20
     Picture1.Print "2O"
     
     '      指定位置显示3O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 30
     Picture1.Print "3O"
     
     '      指定位置显示4O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 40
     Picture1.Print "4O"
     
     '      指定位置显示5O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 50
     Picture1.Print "5O"
     
     '      指定位置显示6O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 60
     Picture1.Print "6O"
     
     '      指定位置显示7O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 70
     Picture1.Print "7O"
     
     '      指定位置显示8O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 80
     Picture1.Print "8O"
     
     '      指定位置显示9O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 90
     Picture1.Print "9O"
     
     '      指定位置显示10O
     Picture1.CurrentX = -10
     Picture1.CurrentY = 100
     Picture1.Print "10O"
     
     '      指定位置显示1O
     Picture1.CurrentX = 0
     Picture1.CurrentY = 110
     Picture1.Print "效率"

'指定位置显示原点O.2
     Picture1.CurrentX = 10
     Picture1.CurrentY = 0
     Picture1.Print ".2"
     
'      指定位置显示.4
     Picture1.CurrentX = 20
     Picture1.CurrentY = 0
     Picture1.Print ".4"
     
     '      指定位置显示.6
     Picture1.CurrentX = 30
     Picture1.CurrentY = 0
     Picture1.Print ".6"
     
     '      指定位置显示.8
     Picture1.CurrentX = 40
     Picture1.CurrentY = 0
     Picture1.Print ".8"
     
     '      指定位置显示1
     Picture1.CurrentX = 50
     Picture1.CurrentY = 0
     Picture1.Print "1"
     
     '      指定位置显示1.2
     Picture1.CurrentX = 60
     Picture1.CurrentY = 0
     Picture1.Print "1.2"
     
     '      指定位置显示1.4
     Picture1.CurrentX = 70
     Picture1.CurrentY = 0
     Picture1.Print "1.4"
     
     '      指定位置显示1.6
     Picture1.CurrentX = 80
     Picture1.CurrentY = 0
     Picture1.Print "1.6"
     
     '      指定位置显示1.8
     Picture1.CurrentX = 90
     Picture1.CurrentY = 0
     Picture1.Print "1.8"
     
     '      指定位置显示2
     Picture1.CurrentX = 100
     Picture1.CurrentY = 0
     Picture1.Print "2"

End Sub

Private Sub Form_Load()
    Timer1.Enabled = True
    Timer1.Interval = 3000
    heng = 0
    temp2 = 0
End Sub

Private Sub Picture2_Paint()
    Dim i As Integer
    Picture2.AutoRedraw = True
    
    Picture2.Scale (-10, 110)-(110, -10)
    Picture2.CurrentX = -5
    Picture2.CurrentY = 0
    Picture2.Print "O"
    Picture2.Line (0, 0)-(100, 0)
    Picture2.Line (0, 0)-(0, 100)
    For i = 10 To 90 Step 10
        Picture2.Line (i, 0)-(i, 2)
        Picture2.CurrentX = i - 10: Picture2.CurrentY = 0
        Picture2.Print i
    Next i
    For i = 10 To 90 Step 10
        Picture2.Line (0, i)-(2, i)
        Picture2.CurrentY = i: Picture2.CurrentX = -11
        Picture2.Print i
    Next i
    
End Sub

Private Sub Timer1_Timer()
    temp1 = heng
    heng = heng + 10.1
    
    Picture2.Line (temp2, temp1)-(temp2 + 10, heng)
    temp2 = temp2 + 10
End Sub
