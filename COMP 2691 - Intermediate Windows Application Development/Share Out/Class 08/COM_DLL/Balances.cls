VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Balances"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Private mintCustomerCount As Integer
Private macurBalances(1 To 10) As Currency

' Create a read-only CustomerCount property
Public Property Get CustomerCount() As Integer
    CustomerCount = mintCustomerCount
End Property

' Create a GetBalance method
Public Function GetBalance(CustomerNumber As Integer) As Currency
    GetBalance = macurBalances(CustomerNumber)
End Function

' Initialize the data
Private Sub Class_Initialize()
    Dim intI As Integer
    
    mintCustomerCount = 10
    
    For intI = 1 To 10
        macurBalances(intI) = Int(Rnd(1) * 100000) / 100
    Next intI
    
End Sub
