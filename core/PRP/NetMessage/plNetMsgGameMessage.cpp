#include "plNetMsgGameMessage.h"

/* plNetMsgGameMessage */
plNetMsgGameMessage::plNetMsgGameMessage() : fMessage(NULL) { }

plNetMsgGameMessage::~plNetMsgGameMessage() {
    delete fMessage;
}

void plNetMsgGameMessage::read(hsStream* S, plResManager* mgr) {
    plNetMsgStream::read(S, mgr);

    delete fMessage;
    hsRAMStream* msgStream = getStream();
    fMessage = plMessage::Convert(mgr->ReadCreatable(msgStream));

    if (S->readBool())
        fDeliveryTime.read(S);
}

void plNetMsgGameMessage::write(hsStream* S, plResManager* mgr) {
    hsRAMStream* msgStream = getStream();
    msgStream->setVer(S->getVer());
    msgStream->rewind();
    msgStream->resize(0);
    mgr->WriteCreatable(msgStream, fMessage);

    plNetMsgStream::write(S, mgr);

    if (fDeliveryTime.atEpoch()) {
        S->writeBool(false);
    } else {
        S->writeBool(true);
        fDeliveryTime.write(S);
    }
}

void plNetMsgGameMessage::IPrcWrite(pfPrcHelper* prc) {
    plNetMessage::IPrcWrite(prc);   // Skip raw stream writing

    if (fMessage != NULL) {
        prc->writeSimpleTag("GameMessage");
        fMessage->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("GameMessage");
        prc->writeParam("NULL", "true");
        prc->endTag(true);
    }

    prc->writeSimpleTag("DeliveryTime");
    fDeliveryTime.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgGameMessage::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "GameMessage") {
        delete fMessage;
        if (tag->getParam("NULL", "false").toBool())
            fMessage = NULL;
        else
            fMessage = plMessage::Convert(mgr->prcParseCreatable(tag));
    } else if (tag->getName() == "DeliveryTime") {
        if (tag->hasChildren())
            fDeliveryTime.prcParse(tag->getFirstChild());
    } else {
        // Skip the raw stream
        plNetMessage::IPrcParse(tag, mgr);
    }
}

void plNetMsgGameMessage::setMessage(plMessage* Message) {
    delete fMessage;
    fMessage = Message;
}


/* plNetMsgGameMessageDirected */
void plNetMsgGameMessageDirected::read(hsStream* S, plResManager* mgr) {
    plNetMsgGameMessage::read(S, mgr);

    unsigned char count = S->readByte();
    fReceivers.setSize(count);
    for (size_t i=0; i<count; i++)
        fReceivers[i] = S->readInt();
}

void plNetMsgGameMessageDirected::write(hsStream* S, plResManager* mgr) {
    plNetMsgGameMessage::write(S, mgr);

    S->writeByte(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        S->writeInt(fReceivers[i]);
}

void plNetMsgGameMessageDirected::IPrcWrite(pfPrcHelper* prc) {
    plNetMsgGameMessage::IPrcWrite(prc);

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++) {
        prc->startTag("Receiver");
        prc->writeParam("ID", fReceivers[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}

void plNetMsgGameMessageDirected::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Receivers") {
        fReceivers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            if (child->getName() != "Receiver")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fReceivers[i] = child->getParam("ID", "0").toUint();
            child = child->getNextSibling();
        }
    } else {
        plNetMsgGameMessage::IPrcParse(tag, mgr);
    }
}
