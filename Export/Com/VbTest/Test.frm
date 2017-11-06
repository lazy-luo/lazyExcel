VERSION 5.00
Begin VB.Form Test 
   Caption         =   "Form1"
   ClientHeight    =   7875
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   10815
   LinkTopic       =   "Form1"
   LockControls    =   -1  'True
   ScaleHeight     =   7875
   ScaleWidth      =   10815
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin VB.PictureBox pic 
      BorderStyle     =   0  'None
      Height          =   2655
      Index           =   2
      Left            =   120
      ScaleHeight     =   2655
      ScaleWidth      =   10575
      TabIndex        =   2
      Top             =   2400
      Width           =   10575
   End
   Begin VB.PictureBox pic 
      BorderStyle     =   0  'None
      Height          =   2535
      Index           =   1
      Left            =   120
      ScaleHeight     =   2535
      ScaleWidth      =   10575
      TabIndex        =   1
      Top             =   5280
      Width           =   10575
   End
   Begin VB.PictureBox pic 
      BorderStyle     =   0  'None
      Height          =   2055
      Index           =   0
      Left            =   120
      ScaleHeight     =   2055
      ScaleWidth      =   10575
      TabIndex        =   0
      Top             =   120
      Width           =   10575
   End
End
Attribute VB_Name = "Test"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private m_clsBook(0 To 2) As CLBookLib
Private Const ROWS As Long = 65536
Private Const COLS As Long = 256
Private Sub Form_Load()
    Set m_clsBook(0) = New CLBookLib
    Set m_clsBook(1) = New CLBookLib
    Set m_clsBook(2) = New CLBookLib
    InitBook
End Sub
Private Sub InitSheet(ByVal clsBook As CLBookLib, ByVal lngSheet As Long)
    Dim irow As Long
    Dim icol As Long
    
    With clsBook
        For irow = 0 To .ROWS(lngSheet) - 1
            For icol = 0 To .COLS(lngSheet) - 1
                If (irow = 0 Or icol = 0) Then
                    If irow > 0 Then
                        .TextMatrix(lngSheet, irow, icol) = irow
                    ElseIf icol > 0 Then
                        .TextMatrix(lngSheet, irow, icol) = icol
                    End If
                End If
            Next
        Next
        .ColWidth(lngSheet, 0) = 36
    End With
    
End Sub
Private Sub InitBook()
    Dim sheet As Long
    If Not m_clsBook(0) Is Nothing Then
        With m_clsBook(0)
            .AttachWidow pic(0).hWnd
            sheet = .AddSheet("Sheet1", 1)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            InitSheet m_clsBook(0), sheet
            sheet = .AddSheet("Sheet2", 2)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            InitSheet m_clsBook(0), sheet
            sheet = .AddSheet("Sheet3", 3)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            InitSheet m_clsBook(0), sheet
        End With
    End If
    If Not m_clsBook(1) Is Nothing Then
        With m_clsBook(1)
            
            .AttachWidow pic(1).hWnd
            sheet = .AddSheet("Sheet1", 1)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            .FreezeCols(sheet) = 2
            .FreezeRows(sheet) = 3
            InitSheet m_clsBook(0), sheet
            sheet = .AddSheet("Sheet2", 2)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            InitSheet m_clsBook(0), sheet
            sheet = .AddSheet("Sheet3", 3)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            InitSheet m_clsBook(0), sheet
        End With
    End If
    If Not m_clsBook(2) Is Nothing Then
        With m_clsBook(2)
            .AttachWidow pic(2).hWnd
            sheet = .AddSheet("Sheet1", 1)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            InitSheet m_clsBook(0), sheet
            sheet = .AddSheet("Sheet2", 2)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            InitSheet m_clsBook(0), sheet
            sheet = .AddSheet("Sheet3", 3)
            .ROWS(sheet) = ROWS
            .COLS(sheet) = COLS
            .FixedCols(sheet) = 1
            .FixedRows(sheet) = 1
            InitSheet m_clsBook(0), sheet
            .BorderLineStyle(sheet, 6, 5) = FULL_LINE
            
        End With
    End If
End Sub

Private Sub Form_Unload(Cancel As Integer)
    If Not m_clsBook(0) Is Nothing Then
        m_clsBook(0).DeattachWindow
    End If
    If Not m_clsBook(1) Is Nothing Then
        m_clsBook(1).DeattachWindow
    End If
    If Not m_clsBook(2) Is Nothing Then
        m_clsBook(2).DeattachWindow
    End If
End Sub
