VERSION 5.00
Object = "{0C70E593-CABF-4984-B4E2-EA696A8BECE0}#1.0#0"; "GridBook.ocx"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   7170
   ClientLeft      =   60
   ClientTop       =   450
   ClientWidth     =   9675
   LinkTopic       =   "Form1"
   ScaleHeight     =   7170
   ScaleWidth      =   9675
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin GRIDBOOKLibCtl.ReportGrid rptCtrl 
      Height          =   3375
      Left            =   240
      OleObjectBlob   =   "Form1.frx":0000
      TabIndex        =   0
      Top             =   120
      Width           =   9135
   End
   Begin GRIDBOOKLibCtl.ReportGrid rptGrid 
      Height          =   3375
      Left            =   240
      OleObjectBlob   =   "Form1.frx":0024
      TabIndex        =   1
      Top             =   3600
      Width           =   9135
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Function InitSheet(ByVal sheet As Long, ByVal obj As Object)
    With obj
        .Rows(sheet) = 64
        .Cols(sheet) = 32
        .FixedCols(sheet) = 1
        .FixedRows(sheet) = 1
        .ColWidth(sheet, 0) = 40
    End With
End Function
Private Function InitBook(ByVal obj As Object)
    Dim sheet As Long
    With obj
        sheet = .AddSheet("sdfsfds", 1)
        InitSheet sheet, obj
    End With
End Function

Private Sub Form_Load()
    InitBook rptGrid
    InitBook rptCtrl
End Sub
