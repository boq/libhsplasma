/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "pnNetMsg.h"
#include "Debug/hsExceptions.h"

static msgparm_t AllocBasic(unsigned int size, unsigned int count)
{
    msgparm_t msg;
    if (size == 1)
        msg.fData = new uint8_t[count];
    else if (size == 2)
        msg.fData = (uint8_t*)(new uint16_t[count]);
    else if (size == 4)
        msg.fData = (uint8_t*)(new uint32_t[count]);
    else
        throw hsBadParamException(__FILE__, __LINE__, "Bad variable size");
    return msg;
}

msgparm_t* NCAllocMessage(const pnNetMsg* msg)
{
    if (msg == NULL)
        return NULL;

    msgparm_t* data = new msgparm_t[msg->fFieldCount];
    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            if (field->fCount == 0)
                // Single Value
                data[i].fUint = 0;
            else
                // Array Value
                data[i] = AllocBasic(field->fSize, field->fCount);
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
        case kFieldString:
        case kFieldVarCount:
            // Variable array -- to be allocated later
            data[i].fData = NULL;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            // Fixed-size array
            data[i].fData = new uint8_t[field->fSize * field->fCount];
            break;
        }
    }
    return data;
}

void NCFreeMessage(msgparm_t* data, const pnNetMsg* msg)
{
    if (data == NULL)
        return;

    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            if (field->fCount != 0)
                // Array Value
                delete[] data[i].fData;
            break;
        case kFieldVarCount:
            // Value only, do nothing
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
        case kFieldString:
            // Variable array
            delete[] data[i].fData;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            // Fixed-size array
            delete[] data[i].fData;
            break;
        }
    }
    delete[] data;
}

size_t NCMessageSize(const msgparm_t* data, const pnNetMsg* msg)
{
    size_t bufSize = 0;
    unsigned int size = 0;
    unsigned int count = 0;

    for (size_t i=0; i<msg->fFieldCount; i++) {
        const pnNetMsgField* field = &msg->fFields[i];
        switch (field->fType) {
        case kFieldInteger:
        case kFieldFloat:
            if (field->fCount == 0)
                bufSize += field->fSize;
            else
                bufSize += field->fSize * field->fCount;
            break;
        case kFieldString:
            bufSize += sizeof(uint16_t);
            bufSize += plwcslen(data[i].fString) * sizeof(pl_wchar_t);
            break;
        case kFieldVarCount:
            bufSize += sizeof(uint32_t);
            count = data[i].fUint;
            size = field->fSize;
            break;
        case kFieldVarPtr:
        case kFieldRawVarPtr:
            bufSize += count * size;
            count = 0;
            size = 0;
            break;
        case kFieldData:
        case kFieldPtr:
        case kFieldRawData:
        case kFieldRawPtr:
            bufSize += field->fCount * field->fSize;
            break;
        }
    }
    return bufSize;
}

plUuid NCGetUuid(const msgparm_t& field)
{
    plUuid uuid;
    uuid.read(field.fData);
    return uuid;
}

void pnNetAgeInfo::read(const unsigned char* buffer)
{
    fAgeInstanceId.read(buffer);
    buffer += 16;

    fAgeFilename = plString((const pl_wchar_t*)buffer);
    buffer += 64 * sizeof(pl_wchar_t);

    fAgeInstanceName = plString((const pl_wchar_t*)buffer);
    buffer += 64 * sizeof(pl_wchar_t);

    fAgeUserName = plString((const pl_wchar_t*)buffer);
    buffer += 64 * sizeof(pl_wchar_t);

    fDescription = plString((const pl_wchar_t*)buffer);
    buffer += 1024 * sizeof(pl_wchar_t);

    fSequenceNumber = *(uint32_t*)buffer;
    buffer += sizeof(uint32_t);

    fLanguage = *(uint32_t*)buffer;
    buffer += sizeof(uint32_t);

    fPopulation = *(uint32_t*)buffer;
    buffer += sizeof(uint32_t);

    fCurrPopulation = *(uint32_t*)buffer;
    buffer += sizeof(uint32_t);
}

void pnNetAgeInfo::write(unsigned char* buffer)
{
    fAgeInstanceId.write(buffer);
    buffer += 16;

    plString::Wide wsbuf = fAgeFilename.wstr();
    memcpy(buffer, wsbuf.data(), (wsbuf.len() >= 64 ? 63 : wsbuf.len()) * sizeof(pl_wchar_t));
    buffer[63 * sizeof(pl_wchar_t)] = 0;
    buffer += 64 * sizeof(pl_wchar_t);

    wsbuf = fAgeInstanceName.wstr();
    memcpy(buffer, wsbuf.data(), (wsbuf.len() >= 64 ? 63 : wsbuf.len()) * sizeof(pl_wchar_t));
    buffer[63 * sizeof(pl_wchar_t)] = 0;
    buffer += 64 * sizeof(pl_wchar_t);

    wsbuf = fAgeUserName.wstr();
    memcpy(buffer, wsbuf.data(), (wsbuf.len() >= 64 ? 63 : wsbuf.len()) * sizeof(pl_wchar_t));
    buffer[63 * sizeof(pl_wchar_t)] = 0;
    buffer += 64 * sizeof(pl_wchar_t);

    wsbuf = fDescription.wstr();
    memcpy(buffer, wsbuf.data(), (wsbuf.len() >= 1024 ? 1023 : wsbuf.len()) * sizeof(pl_wchar_t));
    buffer[1023 * sizeof(pl_wchar_t)] = 0;
    buffer += 1024 * sizeof(pl_wchar_t);

    *(uint32_t*)buffer = fSequenceNumber;
    buffer += sizeof(uint32_t);

    *(uint32_t*)buffer = fLanguage;
    buffer += sizeof(uint32_t);

    *(uint32_t*)buffer = fPopulation;
    buffer += sizeof(uint32_t);

    *(uint32_t*)buffer = fCurrPopulation;
    buffer += sizeof(uint32_t);
}


#include "Protocol.h"
const char* GetNetErrorString(int errcode)
{
    static const char* s_errText[] = {
        "Success", "Internal Error", "Timeout", "Bad Server Data",
        "Age Not Found", "Connect Failed", "Disconnected", "File Not Found",
        "Old Build ID", "Remote Shutdown", "ODBC Timeout",
        "Account Already Exists", "Player Already Exists", "Account Not Found",
        "Player Not Found", "Invalid Parameter", "Name Lookup Failed",
        "Logged In Elsewhere", "Vault Node Not Found", "Max Players On Account",
        "Authentication Failed", "State Object Not Found", "Login Denied",
        "Circular Reference", "Account Not Activated", "Key Already Used",
        "Key Not Found", "Activation Code Not Found", "Player Name Invalid",
        "Not Supported", "Service Forbidden", "Auth Token Too Old",
        "Must Use GameTap Client", "Too Many Failed Logins",
        "GameTap Connection Failed", "GameTap: Too Many Auth Options",
        "GameTap: Missing Parameter", "GameTap: Server Error", "Account Banned",
        "Kicked By CCR", "Wrong Score Type", "Score: Not Enough Points",
        "Score Already Exists", "No Score Data Found",
        "Invite: No Matching Player", "Invite: Too Many Hoods", "Need To Pay",
        "Server Busy",
    };

    if (errcode < 0)
        return "Pending";
    else if (errcode < kNumNetErrors)
        return s_errText[errcode];
    else
        return "Invalid error code";
}
