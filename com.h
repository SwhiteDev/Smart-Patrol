#ifndef __COM_TEST_H__
#define __COM_TEST_H__

int CommOpen(void);

int CommDestory(void);

int SetAttribute(COMM_ATTR *pattr);

int GetAttribute(void);

int CommRead(void *pdata, DWORD nbytes);

int CommWrite(void *pdata, DWORD len);

int CommPurge(DWORD dw_flags);