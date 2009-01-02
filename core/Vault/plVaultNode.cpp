#include "plVaultNode.h"
#include "plVaultNodeTypes.h"
#include <cstring>

/* plVaultBlob */
plVaultBlob::plVaultBlob() : fSize(0), fData(NULL) { }

plVaultBlob::plVaultBlob(const plVaultBlob& init)
           : fSize(init.fSize) {
    fData = new unsigned char[fSize];
    memcpy(fData, init.fData, fSize);
}

plVaultBlob::~plVaultBlob() {
    if (fData != NULL)
        delete[] fData;
}

plVaultBlob& plVaultBlob::operator=(const plVaultBlob& init) {
    setData(init.fSize, init.fData);
    return *this;
}

void plVaultBlob::read(hsStream* S) {
    if (fData != NULL)
        delete[] fData;
    fSize = S->readInt();
    fData = new unsigned char[fSize];
    S->read(fSize, fData);
}

void plVaultBlob::write(hsStream* S) {
    S->writeInt(fSize);
    S->write(fSize, fData);
}

size_t plVaultBlob::getSize() const { return fSize; }
const unsigned char* plVaultBlob::getData() const { return fData; }

void plVaultBlob::setData(size_t size, const unsigned char* data) {
    if (fData != NULL)
        delete[] fData;
    fSize = size;
    fData = new unsigned char[fSize];
    memcpy(fData, data, fSize);
}


/* plVaultNode */
plVaultNode::plVaultNode()
           : fNodeID(0), fOwner(0), fGroup(0), fCreator(0), fNodeType(0),
             fPermissions(plVault::kDefaultPermissions) {
    fInt32[0] = 0;
    fInt32[1] = 0;
    fInt32[2] = 0;
    fInt32[3] = 0;
    fUInt32[0] = 0;
    fUInt32[1] = 0;
    fUInt32[2] = 0;
    fUInt32[3] = 0;
}

plVaultNode::plVaultNode(const plVaultNode& init) {
    copy(init);
}

plVaultNode::~plVaultNode() { }

void plVaultNode::copy(const plVaultNode& init) {
    fFields = init.fFields;
    fNodeID = init.fNodeID;
    fOwner = init.fOwner;
    fGroup = init.fGroup;
    fCreator = init.fCreator;
    fNodeType = init.fNodeType;
    fPermissions = init.fPermissions;
    fAutoTime = init.fAutoTime;
    fModifyTime = init.fModifyTime;
    fCreateAgeTime = init.fCreateAgeTime;
    fCreateAgeGuid = init.fCreateAgeGuid;
    fGuid1 = init.fGuid1;
    fGuid2 = init.fGuid2;
    fCreateAgeName = init.fCreateAgeName;
    fBlob1 = init.fBlob1;
    fBlob2 = init.fBlob2;
    fInt32[0] = init.fInt32[0];
    fInt32[1] = init.fInt32[1];
    fInt32[2] = init.fInt32[2];
    fInt32[3] = init.fInt32[3];
    fUInt32[0] = init.fUInt32[0];
    fUInt32[1] = init.fUInt32[1];
    fUInt32[2] = init.fUInt32[2];
    fUInt32[3] = init.fUInt32[3];
    fString64[0] = init.fString64[0];
    fString64[1] = init.fString64[1];
    fString64[2] = init.fString64[2];
    fString64[3] = init.fString64[3];
    fString64[4] = init.fString64[4];
    fString64[5] = init.fString64[5];
    fIString64[0] = init.fIString64[0];
    fIString64[1] = init.fIString64[1];
    fText[0] = init.fText[0];
    fText[1] = init.fText[1];
}

bool plVaultNode::isValid() const {
    return fNodeID != 0;
}

bool plVaultNode::hasField(unsigned int field) const {
    return fFields[field];
}

void plVaultNode::delField(unsigned int field) {
    fFields[field] = false;
}

void plVaultNode::makeField(unsigned int field) {
    fFields[field] = true;
    switch (field) {
    case kFieldNodeID:
        fNodeID = 0;
        break;
    case kFieldNodeType:
        fNodeType = 0;
        break;
    case kFieldPermissions:
        fPermissions = 0;
        break;
    case kFieldOwner:
        fOwner = 0;
        break;
    case kFieldGroup:
        fGroup = 0;
        break;
    case kFieldAutoTime:
        fAutoTime = plUnifiedTime();
        break;
    case kFieldCreator:
        fCreator = 0;
        break;
    case kFieldModifyTime:
        fModifyTime = plUnifiedTime();
        break;
    case kFieldCreateAgeTime:
        fCreateAgeTime = plUnifiedTime();
        break;
    case kFieldCreateAgeName:
        fCreateAgeName = "";
        break;
    case kFieldCreateAgeGuid:
        fCreateAgeGuid = plServerGuid();
        break;
    case kFieldInt32_1:
        fInt32[0] = 0;
        break;
    case kFieldInt32_2:
        fInt32[1] = 0;
        break;
    case kFieldInt32_3:
        fInt32[2] = 0;
        break;
    case kFieldInt32_4:
        fInt32[3] = 0;
        break;
    case kFieldUInt32_1:
        fUInt32[0] = 0;
        break;
    case kFieldUInt32_2:
        fUInt32[1] = 0;
        break;
    case kFieldUInt32_3:
        fUInt32[2] = 0;
        break;
    case kFieldUInt32_4:
        fUInt32[3] = 0;
        break;
    case kFieldString64_1:
        fString64[0] = "";
        break;
    case kFieldString64_2:
        fString64[1] = "";
        break;
    case kFieldString64_3:
        fString64[2] = "";
        break;
    case kFieldString64_4:
        fString64[3] = "";
        break;
    case kFieldString64_5:
        fString64[4] = "";
        break;
    case kFieldString64_6:
        fString64[5] = "";
        break;
    case kFieldIString64_1:
        fIString64[0] = "";
        break;
    case kFieldIString64_2:
        fIString64[1] = "";
        break;
    case kFieldText_1:
        fText[0] = "";
        break;
    case kFieldText_2:
        fText[1] = "";
        break;
    case kFieldBlob_1:
        fBlob1 = plVaultBlob();
        break;
    case kFieldBlob_2:
        fBlob2 = plVaultBlob();
        break;
    case kFieldGuid_1:
        fGuid1 = plServerGuid();
        break;
    case kFieldGuid_2:
        fGuid2 = plServerGuid();
        break;
    default:
        break;
    }
}

void plVaultNode::read(hsStream* S) {
    fFields.read(S);

    fNodeID = S->readInt();
    fNodeType = S->readByte();
    fPermissions = S->readInt();
    fOwner = S->readInt();
    fGroup = S->readInt();
    fAutoTime.read(S);

    if (fFields[kFieldCreator])
        fCreator = S->readInt();
    if (fFields[kFieldModifyTime])
        fModifyTime.read(S);
    if (fFields[kFieldCreateAgeTime])
        fCreateAgeTime.read(S);
    if (fFields[kFieldCreateAgeName]) {
        size_t len = S->readShort();
        fCreateAgeName = S->readStr(len);
    }
    if (fFields[kFieldCreateAgeGuid])
        fCreateAgeGuid.read(S);
    if (fFields[kFieldInt32_1])
        fInt32[0] = S->readInt();
    if (fFields[kFieldInt32_2])
        fInt32[1] = S->readInt();
    if (fFields[kFieldInt32_3])
        fInt32[2] = S->readInt();
    if (fFields[kFieldInt32_4])
        fInt32[3] = S->readInt();
    if (fFields[kFieldUInt32_1])
        fUInt32[0] = S->readInt();
    if (fFields[kFieldUInt32_2])
        fUInt32[1] = S->readInt();
    if (fFields[kFieldUInt32_3])
        fUInt32[2] = S->readInt();
    if (fFields[kFieldUInt32_4])
        fUInt32[3] = S->readInt();
    if (fFields[kFieldString64_1]) {
        size_t len = S->readShort();
        fString64[0] = S->readStr(len);
    }
    if (fFields[kFieldString64_2]) {
        size_t len = S->readShort();
        fString64[1] = S->readStr(len);
    }
    if (fFields[kFieldString64_3]) {
        size_t len = S->readShort();
        fString64[2] = S->readStr(len);
    }
    if (fFields[kFieldString64_4]) {
        size_t len = S->readShort();
        fString64[3] = S->readStr(len);
    }
    if (fFields[kFieldString64_5]) {
        size_t len = S->readShort();
        fString64[4] = S->readStr(len);
    }
    if (fFields[kFieldString64_6]) {
        size_t len = S->readShort();
        fString64[5] = S->readStr(len);
    }
    if (fFields[kFieldIString64_1]) {
        size_t len = S->readShort();
        fIString64[0] = S->readStr(len);
    }
    if (fFields[kFieldIString64_2]) {
        size_t len = S->readShort();
        fIString64[1] = S->readStr(len);
    }
    if (fFields[kFieldText_1]) {
        size_t len = S->readShort();
        fText[0] = S->readStr(len);
    }
    if (fFields[kFieldText_2]) {
        size_t len = S->readShort();
        fText[1] = S->readStr(len);
    }
    if (fFields[kFieldBlob_1])
        fBlob1.read(S);
    if (fFields[kFieldBlob_2])
        fBlob2.read(S);
    if (fFields[kFieldGuid_1])
        fGuid1.read(S);
    if (fFields[kFieldGuid_2])
        fGuid2.read(S);
}

void plVaultNode::write(hsStream* S) {
    fFields.write(S);

    S->writeInt(fNodeID);
    S->writeByte(fNodeType);
    S->writeInt(fPermissions);
    S->writeInt(fOwner);
    S->writeInt(fGroup);
    fAutoTime.write(S);

    if (fFields[kFieldCreator])
        S->writeInt(fCreator);
    if (fFields[kFieldModifyTime])
        fModifyTime.write(S);
    if (fFields[kFieldCreateAgeTime])
        fCreateAgeTime.write(S);
    if (fFields[kFieldCreateAgeName]) {
        S->writeShort(fCreateAgeName.len());
        S->writeStr(fCreateAgeName);
    }
    if (fFields[kFieldCreateAgeGuid])
        fCreateAgeGuid.write(S);
    if (fFields[kFieldInt32_1])
        S->writeInt(fInt32[0]);
    if (fFields[kFieldInt32_2])
        S->writeInt(fInt32[1]);
    if (fFields[kFieldInt32_3])
        S->writeInt(fInt32[2]);
    if (fFields[kFieldInt32_4])
        S->writeInt(fInt32[3]);
    if (fFields[kFieldUInt32_1])
        S->writeInt(fUInt32[0]);
    if (fFields[kFieldUInt32_2])
        S->writeInt(fUInt32[1]);
    if (fFields[kFieldUInt32_3])
        S->writeInt(fUInt32[2]);
    if (fFields[kFieldUInt32_4])
        S->writeInt(fUInt32[3]);
    if (fFields[kFieldString64_1]) {
        S->writeShort(fString64[0].len());
        S->writeStr(fString64[0]);
    }
    if (fFields[kFieldString64_2]) {
        S->writeShort(fString64[1].len());
        S->writeStr(fString64[1]);
    }
    if (fFields[kFieldString64_3]) {
        S->writeShort(fString64[2].len());
        S->writeStr(fString64[2]);
    }
    if (fFields[kFieldString64_4]) {
        S->writeShort(fString64[3].len());
        S->writeStr(fString64[3]);
    }
    if (fFields[kFieldString64_5]) {
        S->writeShort(fString64[4].len());
        S->writeStr(fString64[4]);
    }
    if (fFields[kFieldString64_6]) {
        S->writeShort(fString64[5].len());
        S->writeStr(fString64[5]);
    }
    if (fFields[kFieldIString64_1]) {
        S->writeShort(fIString64[0].len());
        S->writeStr(fIString64[0]);
    }
    if (fFields[kFieldIString64_2]) {
        S->writeShort(fIString64[1].len());
        S->writeStr(fIString64[1]);
    }
    if (fFields[kFieldText_1]) {
        S->writeShort(fText[0].len());
        S->writeStr(fText[0]);
    }
    if (fFields[kFieldText_2]) {
        S->writeShort(fText[1].len());
        S->writeStr(fText[1]);
    }
    if (fFields[kFieldBlob_1])
        fBlob1.write(S);
    if (fFields[kFieldBlob_2])
        fBlob2.write(S);
    if (fFields[kFieldGuid_1])
        fGuid1.write(S);
    if (fFields[kFieldGuid_2])
        fGuid2.write(S);
}

unsigned int plVaultNode::getNodeID() const {
    return fFields[kFieldNodeID] ? fNodeID : 0;
}

unsigned int plVaultNode::getOwner() const {
    return fFields[kFieldOwner] ? fOwner : 0;
}

unsigned int plVaultNode::getGroup() const {
    return fFields[kFieldGroup] ? fGroup : 0;
}

unsigned int plVaultNode::getCreator() const {
    return fFields[kFieldCreator] ? fCreator : 0;
}

unsigned int plVaultNode::getNodeType() const {
    return fFields[kFieldNodeType] ? fNodeType : 0;
}

unsigned int plVaultNode::getPermissions() const {
    return fFields[kFieldPermissions] ? fPermissions : 0;
}

plUnifiedTime plVaultNode::getAutoTime() const {
    return fFields[kFieldAutoTime] ? fAutoTime : plUnifiedTime();
}

plUnifiedTime plVaultNode::getModifyTime() const {
    return fFields[kFieldModifyTime] ? fModifyTime : plUnifiedTime();
}

plUnifiedTime plVaultNode::getCreateAgeTime() const {
    return fFields[kFieldCreateAgeTime] ? fCreateAgeTime : plUnifiedTime();
}

plServerGuid plVaultNode::getCreateAgeGuid() const {
    return fFields[kFieldCreateAgeGuid] ? fCreateAgeGuid : plServerGuid();
}

plServerGuid plVaultNode::getGuid1() const {
    return fFields[kFieldGuid_1] ? fGuid1 : plServerGuid();
}

plServerGuid plVaultNode::getGuid2() const {
    return fFields[kFieldGuid_2] ? fGuid2 : plServerGuid();
}

plString plVaultNode::getCreateAgeName() const {
    return fFields[kFieldCreateAgeName] ? fCreateAgeName : "";
}

int plVaultNode::getInt32_1() const {
    return fFields[kFieldInt32_1] ? fInt32[0] : 0;
}

int plVaultNode::getInt32_2() const {
    return fFields[kFieldInt32_2] ? fInt32[1] : 0;
}

int plVaultNode::getInt32_3() const {
    return fFields[kFieldInt32_3] ? fInt32[2] : 0;
}

int plVaultNode::getInt32_4() const {
    return fFields[kFieldInt32_4] ? fInt32[3] : 0;
}

unsigned int plVaultNode::getUInt32_1() const {
    return fFields[kFieldUInt32_1] ? fUInt32[0] : 0;
}

unsigned int plVaultNode::getUInt32_2() const {
    return fFields[kFieldUInt32_2] ? fUInt32[1] : 0;
}

unsigned int plVaultNode::getUInt32_3() const {
    return fFields[kFieldUInt32_3] ? fUInt32[2] : 0;
}

unsigned int plVaultNode::getUInt32_4() const {
    return fFields[kFieldUInt32_4] ? fUInt32[3] : 0;
}

plString plVaultNode::getString64_1() const {
    return fFields[kFieldString64_1] ? fString64[0] : "";
}

plString plVaultNode::getString64_2() const {
    return fFields[kFieldString64_2] ? fString64[1] : "";
}

plString plVaultNode::getString64_3() const {
    return fFields[kFieldString64_3] ? fString64[2] : "";
}

plString plVaultNode::getString64_4() const {
    return fFields[kFieldString64_4] ? fString64[3] : "";
}

plString plVaultNode::getString64_5() const {
    return fFields[kFieldString64_5] ? fString64[4] : "";
}

plString plVaultNode::getString64_6() const {
    return fFields[kFieldString64_6] ? fString64[5] : "";
}

plString plVaultNode::getIString64_1() const {
    return fFields[kFieldIString64_1] ? fIString64[0] : "";
}

plString plVaultNode::getIString64_2() const {
    return fFields[kFieldIString64_2] ? fIString64[1] : "";
}

plString plVaultNode::getText_1() const {
    return fFields[kFieldText_1] ? fText[0] : "";
}

plString plVaultNode::getText_2() const {
    return fFields[kFieldText_2] ? fText[1] : "";
}

plVaultBlob plVaultNode::getBlob_1() const {
    return fFields[kFieldBlob_1] ? fBlob1 : plVaultBlob();
}

plVaultBlob plVaultNode::getBlob_2() const {
    return fFields[kFieldBlob_2] ? fBlob2 : plVaultBlob();
}

void plVaultNode::setNodeID(unsigned int id) {
    fFields[kFieldNodeID] = true;
    fNodeID = id;
}

void plVaultNode::setOwner(unsigned int id) {
    fFields[kFieldOwner] = true;
    fOwner = id;
}

void plVaultNode::setGroup(unsigned int id) {
    fFields[kFieldGroup] = true;
    fGroup = id;
}

void plVaultNode::setCreator(unsigned int id) {
    fFields[kFieldCreator] = true;
    fCreator = id;
}

void plVaultNode::setNodeType(unsigned int type) {
    fFields[kFieldNodeType] = true;
    fNodeType = type;
}

void plVaultNode::setPermissions(unsigned int permissions) {
    fFields[kFieldPermissions] = true;
    fPermissions = permissions;
}

void plVaultNode::setAutoTime(const plUnifiedTime& time) {
    fFields[kFieldAutoTime] = true;
    fAutoTime = time;
}

void plVaultNode::setModifyTime(const plUnifiedTime& time) {
    fFields[kFieldModifyTime] = true;
    fModifyTime = time;
}

void plVaultNode::setCreateAgeTime(const plUnifiedTime& time) {
    fFields[kFieldCreateAgeTime] = true;
    fCreateAgeTime = time;
}

void plVaultNode::setCreateAgeGuid(const plServerGuid& guid) {
    fFields[kFieldCreateAgeGuid] = true;
    fCreateAgeGuid = guid;
}

void plVaultNode::setGuid1(const plServerGuid& guid) {
    fFields[kFieldGuid_1] = true;
    fGuid1 = guid;
}

void plVaultNode::setGuid2(const plServerGuid& guid) {
    fFields[kFieldGuid_2] = true;
    fGuid2 = guid;
}

void plVaultNode::setCreateAgeName(const plString& name) {
    fFields[kFieldCreateAgeName] = true;
    fCreateAgeName = name;
}

void plVaultNode::setInt32_1(int value) {
    fFields[kFieldInt32_1] = true;
    fInt32[0] = value;
}

void plVaultNode::setInt32_2(int value) {
    fFields[kFieldInt32_2] = true;
    fInt32[1] = value;
}

void plVaultNode::setInt32_3(int value) {
    fFields[kFieldInt32_3] = true;
    fInt32[2] = value;
}

void plVaultNode::setInt32_4(int value) {
    fFields[kFieldInt32_4] = true;
    fInt32[3] = value;
}

void plVaultNode::setUInt32_1(unsigned int value) {
    fFields[kFieldUInt32_1] = true;
    fUInt32[0] = value;
}

void plVaultNode::setUInt32_2(unsigned int value) {
    fFields[kFieldUInt32_2] = true;
    fUInt32[1] = value;
}

void plVaultNode::setUInt32_3(unsigned int value) {
    fFields[kFieldUInt32_3] = true;
    fUInt32[2] = value;
}

void plVaultNode::setUInt32_4(unsigned int value) {
    fFields[kFieldUInt32_4] = true;
    fUInt32[3] = value;
}

void plVaultNode::setString64_1(const plString& value) {
    fFields[kFieldString64_1] = true;
    fString64[0] = value;
}

void plVaultNode::setString64_2(const plString& value) {
    fFields[kFieldString64_2] = true;
    fString64[1] = value;
}

void plVaultNode::setString64_3(const plString& value) {
    fFields[kFieldString64_3] = true;
    fString64[2] = value;
}

void plVaultNode::setString64_4(const plString& value) {
    fFields[kFieldString64_4] = true;
    fString64[3] = value;
}

void plVaultNode::setString64_5(const plString& value) {
    fFields[kFieldString64_5] = true;
    fString64[4] = value;
}

void plVaultNode::setString64_6(const plString& value) {
    fFields[kFieldString64_6] = true;
    fString64[5] = value;
}

void plVaultNode::setIString64_1(const plString& value) {
    fFields[kFieldIString64_1] = true;
    fIString64[0] = value;
}

void plVaultNode::setIString64_2(const plString& value) {
    fFields[kFieldIString64_2] = true;
    fIString64[1] = value;
}

void plVaultNode::setText_1(const plString& value) {
    fFields[kFieldText_1] = true;
    fText[0] = value;
}

void plVaultNode::setText_2(const plString& value) {
    fFields[kFieldText_2] = true;
    fText[1] = value;
}

void plVaultNode::setBlob_1(const plVaultBlob& value) {
    fFields[kFieldBlob_1] = true;
    fBlob1 = value;
}

void plVaultNode::setBlob_2(const plVaultBlob& value) {
    fFields[kFieldBlob_2] = true;
    fBlob2 = value;
}

plVaultPlayerNode plVaultNode::upcastToPlayerNode() const {
    return plVaultPlayerNode(*this);
}

plVaultAgeNode plVaultNode::upcastToAgeNode() const {
    return plVaultAgeNode(*this);
}

plVaultGameServerNode plVaultNode::upcastToGameServerNode() const {
    return plVaultGameServerNode(*this);
}

plVaultAdminNode plVaultNode::upcastToAdminNode() const {
    return plVaultAdminNode(*this);
}

plVaultServerNode plVaultNode::upcastToServerNode() const {
    return plVaultServerNode(*this);
}

/*
plVaultCCRNode plVaultNode::upcastToCCRNode() const {
    return plVaultCCRNode(*this);
}
*/

plVaultFolderNode plVaultNode::upcastToFolderNode() const {
    return plVaultFolderNode(*this);
}

plVaultPlayerInfoNode plVaultNode::upcastToPlayerInfoNode() const {
    return plVaultPlayerInfoNode(*this);
}

plVaultSystemNode plVaultNode::upcastToSystemNode() const {
    return plVaultSystemNode(*this);
}

plVaultImageNode plVaultNode::upcastToImageNode() const {
    return plVaultImageNode(*this);
}

plVaultTextNoteNode plVaultNode::upcastToTextNoteNode() const {
    return plVaultTextNoteNode(*this);
}

plVaultSDLNode plVaultNode::upcastToSDLNode() const {
    return plVaultSDLNode(*this);
}

plVaultAgeLinkNode plVaultNode::upcastToAgeLinkNode() const {
    return plVaultAgeLinkNode(*this);
}

plVaultChronicleNode plVaultNode::upcastToChronicleNode() const {
    return plVaultChronicleNode(*this);
}

plVaultPlayerInfoListNode plVaultNode::upcastToPlayerInfoListNode() const {
    return plVaultPlayerInfoListNode(*this);
}

plVaultMarkerNode plVaultNode::upcastToMarkerNode() const {
    return plVaultMarkerNode(*this);
}

plVaultAgeInfoNode plVaultNode::upcastToAgeInfoNode() const {
    return plVaultAgeInfoNode(*this);
}

plVaultAgeInfoListNode plVaultNode::upcastToAgeInfoListNode() const {
    return plVaultAgeInfoListNode(*this);
}

plVaultMarkerListNode plVaultNode::upcastToMarkerListNode() const {
    return plVaultMarkerListNode(*this);
}
