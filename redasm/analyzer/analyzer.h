#ifndef ANALYZER_H
#define ANALYZER_H

#include <functional>
#include <memory>
#include "../support/dispatcher.h"
#include "../plugins/assembler/assembler.h"
#include "../disassembler/listing/listingdocument.h"
#include "../disassembler/types/symboltable.h"
#include "../disassembler/disassemblerapi.h"
#include "../database/signaturedb.h"

namespace REDasm {

class Analyzer
{
    public:
        Analyzer(DisassemblerAPI* disassembler, const SignatureFiles& signaturefiles);
        virtual ~Analyzer();
        virtual void analyze();

    private:
        void loadSignatures();
        void findTrampolines();
        void findTrampoline(SymbolPtr symbol);
        SymbolPtr findTrampoline_x86(ListingDocument::iterator it);
        SymbolPtr findTrampoline_arm(ListingDocument::iterator it);

    protected:
        Dispatcher<std::string, void(void*)> m_archdispatcher;
        DisassemblerAPI* m_disassembler;
        ListingDocument* m_document;
        const SignatureFiles& m_signaturefiles;
};

}

#endif // ANALYZER_H
