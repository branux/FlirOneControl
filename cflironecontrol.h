#ifndef CFLIRONECONTROL_H
#define CFLIRONECONTROL_H


#include "stdafx.h"

#include <setupapi.h>
#include <basetyps.h>
#include <assert.h>

#include "tga.h"
#include "cflironereceiver.h"
#include "cflironedriver.h"
#include "craiiccriticalsection.h"

//����������� �����
#define EPS 0.00000001

//����� ���������� Flir One
class CFlirOneControl
{
 protected:
  //-���������� ������-------------------------------------------------------    
  long Delay;//����� ��� ������ ������

  struct SProtected
  {
   CCriticalSection cCriticalSection;//����������� ������ ��� ������� � ������
   CFlirOneReceiver cFlirOneReceiver;//����� ����� ������ �� Flir One
  } sProtected;//���������� ����������

  CFlirOneDriver cFlirOneDriver;//����� ������ � ���������� Flir One

  CEvent cEvent_Exit;//������� ���������� ������
  CWinThread *cWinThread_ProcessingThread;//����� ���������  
  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CFlirOneControl(void);
  //-���������� ������-------------------------------------------------------
  ~CFlirOneControl();
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  bool Open(void);//������������ � ����������
  void Close(void);//����������� �� ����������
  bool Processing(void);//��������� (���������� ������ �������)
  bool LoadColorMap(char *filename);//��������� ����� ������������� �����������
  bool CopyColorImage(unsigned long *image_ptr,unsigned long size,unsigned long &index);//����������� ������������ ����������� � �����
  bool CopyThermalImage(unsigned short *image_ptr,unsigned long size,unsigned long &index);//����������� �������� ����������� � �����
  bool CopyVideoImage(unsigned long *image_ptr,unsigned long size,unsigned long &index);//����������� ����������� � ����������� � �����
  bool CopyColorMap(unsigned char R[256],unsigned char G[256],unsigned char B[256],unsigned long size);//����������� �������

  void AddLog(char *string);//�������� ������ � log-����
  void AddLog(long value);//�������� ����� � log-����
  void StartThread(void);//��������� �����
  void StopThread(void);//���������� �����
};

UINT ProcessingThread(LPVOID pParam);//����� ���������

#endif
