/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 10 11:19:57 2017
 */
/* Compiler settings for C:\work_folder\c++\LGridBook\Export\Com\CLGridBook.idl:
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

const IID IID_ICLBookLib = {0x16C06F17,0xCBA6,0x4C46,{0xB8,0xE9,0x90,0x75,0xD4,0xCE,0xF0,0xEC}};


const IID LIBID_CLGRIDBOOKLib = {0x7B9ED975,0x60B3,0x42E4,{0x9A,0x73,0x5E,0xC9,0xD5,0x60,0xDC,0x71}};


const IID DIID__ICLBookLibEvents = {0x6066F594,0xF213,0x4363,{0x91,0xCC,0x18,0xF3,0xB4,0x46,0x5C,0xE6}};


const CLSID CLSID_CLBookLib = {0xD3D6527B,0xCD33,0x4482,{0x9B,0x7A,0x21,0xC8,0xFF,0x69,0x29,0xA7}};


#ifdef __cplusplus
}
#endif

