// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#include "../../include/fxcrt/fx_basic.h"
#include "fxcrt_qt.h"

#if _FXM_PLATFORM_ == _FXM_PLATFORM_QT_
IFXCRT_FileAccess* FXCRT_FileAccess_Create()
{
    return new CFXCRT_FileAccess_Qt;
}
void FXCRT_Qt_GetFileMode(FX_DWORD dwModes, QIODevice::OpenMode &nFlags, int32_t &nMasks)
{
    if (dwModes & FX_FILEMODE_ReadOnly) {
        nFlags |= QIODevice::ReadOnly;
        nMasks = 0;
    } else {
        nFlags |= QIODevice::ReadWrite;
        if (dwModes & FX_FILEMODE_Truncate) {
            nFlags |= QIODevice::Truncate;
        }
        nMasks = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    }
}
CFXCRT_FileAccess_Qt::CFXCRT_FileAccess_Qt()
{
}
CFXCRT_FileAccess_Qt::~CFXCRT_FileAccess_Qt()
{
    Close();
}
FX_BOOL CFXCRT_FileAccess_Qt::Open(const CFX_ByteStringC& fileName, FX_DWORD dwMode)
{
    m_file.setFileName(QString::fromLocal8Bit(fileName.GetCStr()));
    int32_t nMasks;
    QIODevice::OpenMode nFlags;
    FXCRT_Qt_GetFileMode(dwMode, nFlags, nMasks);
    return m_file.open(nFlags);
}
FX_BOOL CFXCRT_FileAccess_Qt::Open(const CFX_WideStringC& fileName, FX_DWORD dwMode)
{
    return Open(FX_UTF8Encode(fileName), dwMode);
}
void CFXCRT_FileAccess_Qt::Close()
{
    m_file.close();
}
void CFXCRT_FileAccess_Qt::Release()
{
    delete this;
}
FX_FILESIZE CFXCRT_FileAccess_Qt::GetSize() const
{
    return m_file.size();
}
FX_FILESIZE CFXCRT_FileAccess_Qt::GetPosition() const
{
    return m_file.pos();
}
FX_FILESIZE CFXCRT_FileAccess_Qt::SetPosition(FX_FILESIZE pos)
{
    ;
    if (m_file.seek(pos)) {
        return (FX_FILESIZE) - 1;
    }
    return m_file.pos();
}
size_t CFXCRT_FileAccess_Qt::Read(void* pBuffer, size_t szBuffer)
{
    return m_file.read((char*) pBuffer,szBuffer);
}
size_t CFXCRT_FileAccess_Qt::Write(const void* pBuffer, size_t szBuffer)
{
    return m_file.write((char*) pBuffer, szBuffer);
}
size_t CFXCRT_FileAccess_Qt::ReadPos(void* pBuffer, size_t szBuffer, FX_FILESIZE pos)
{
    if (pos >= GetSize()) {
        return 0;
    }
    if (SetPosition(pos) == (FX_FILESIZE) - 1) {
        return 0;
    }
    return Read(pBuffer, szBuffer);
}
size_t CFXCRT_FileAccess_Qt::WritePos(const void* pBuffer, size_t szBuffer, FX_FILESIZE pos)
{
    if (SetPosition(pos) == (FX_FILESIZE) - 1) {
        return 0;
    }
    return Write(pBuffer, szBuffer);
}
FX_BOOL CFXCRT_FileAccess_Qt::Flush()
{
    return m_file.flush();
}
FX_BOOL CFXCRT_FileAccess_Qt::Truncate(FX_FILESIZE szFile)
{
    return m_file.resize(szFile);
}
FX_BOOL FX_File_Exist(const CFX_ByteStringC& fileName)
{
    return access(fileName.GetCStr(), F_OK) > -1;
}
FX_BOOL FX_File_Exist(const CFX_WideStringC& fileName)
{
    return FX_File_Exist(FX_UTF8Encode(fileName));
}
FX_BOOL FX_File_Delete(const CFX_ByteStringC& fileName)
{
    return remove(fileName.GetCStr()) > -1;
}
FX_BOOL FX_File_Delete(const CFX_WideStringC& fileName)
{
    return FX_File_Delete(FX_UTF8Encode(fileName));
}
FX_BOOL FX_File_Copy(const CFX_ByteStringC& fileNameSrc, const CFX_ByteStringC& fileNameDst)
{
    CFXCRT_FileAccess_Qt src, dst;
    if (!src.Open(fileNameSrc, FX_FILEMODE_ReadOnly)) {
        return FALSE;
    }
    FX_FILESIZE size = src.GetSize();
    if (!size) {
        return FALSE;
    }
    if (!dst.Open(fileNameDst, FX_FILEMODE_Truncate)) {
        return FALSE;
    }
    size_t num = 0;
    uint8_t* pBuffer = FX_Alloc(uint8_t, 32768);
    num = src.Read(pBuffer, 32768);
    while (num) {
        if (dst.Write(pBuffer, num) != num) {
            break;
        }
        num = src.Read(pBuffer, 32768);
    }
    FX_Free(pBuffer);
    return TRUE;
}
FX_BOOL FX_File_Copy(const CFX_WideStringC& fileNameSrc, const CFX_WideStringC& fileNameDst)
{
    return FX_File_Copy(FX_UTF8Encode(fileNameSrc), FX_UTF8Encode(fileNameDst));
}
FX_BOOL FX_File_Move(const CFX_ByteStringC& fileNameSrc, const CFX_ByteStringC& fileNameDst)
{
    return rename(fileNameSrc.GetCStr(), fileNameDst.GetCStr());
}
FX_BOOL FX_File_Move(const CFX_WideStringC& fileNameSrc, const CFX_WideStringC& fileNameDst)
{
    return FX_File_Move(FX_UTF8Encode(fileNameSrc), FX_UTF8Encode(fileNameDst));
}
#endif
