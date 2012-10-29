VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "Primes"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Public Function HighPrime(Max As Long) As Long
        Dim a() As Byte
        Dim lngI As Long
        Dim lngJ As Long
        
        ReDim a(Max)

        ' In the array, 1 indicates a prime,
        ' 0 indicates nonprime. Start by marking multiples
        ' of 2 as nonprime
        For lngI = 0 To Max
            If lngI Mod 2 = 0 And lngI <> 2 Then
                a(lngI) = 0
            Else
                a(lngI) = 1
            End If
        Next lngI
        ' Now execute the usual sieve of erasthones algorithm
        For lngI = 3 To Sqr(Max) Step 2
            If a(lngI) = 1 Then
                ' This is a prime, so eliminate its multiples
                For lngJ = lngI + lngI To Max Step lngI
                    a(lngJ) = 0
                Next lngJ
            End If
        Next lngI
        ' Find the largest prime by working backwards
        For lngI = Max To 1 Step -1
            If a(lngI) = 1 Then
                HighPrime = lngI
                Exit For
            End If
        Next lngI
        
End Function

