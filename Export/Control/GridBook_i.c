/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 10 11:19:53 2017
 */
/* Compiler settings for C:\work_folder\c++\LGridBook\Export\Control\GridBook.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IReportGrid = {0x71BF6F4E,0x0502,0x47E0,{0x80,0xB2,0x3F,0x9F,0x8C,0xC6,0xB9,0xB2}};


const IID LIBID_GRIDBOOKLib = {0x0C70E593,0xCABF,0x4984,{0xB4,0xE2,0xEA,0x69,0x6A,0x8B,0xEC,0xE0}};


const IID DIID__IReportGridEvents = {0x11BC8ADD,0x4696,0x4E09,{0xA5,0xF3,0xA4,0x2E,0xC7,0x0D,0x6C,0x7E}};


const CLSID CLSID_ReportGrid = {0xA7E2631B,0x1E33,0x412D,{0xB4,0xDE,0xF5,0x15,0xD7,0x09,0xAE,0x90}};


#ifdef __cplusplus
}
#endif

