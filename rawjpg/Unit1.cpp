//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <memory>
#include <stdio>

//---------------------------------------------------------------------------

#pragma argsused

int pack(AnsiString jpg_FileName, AnsiString raw_FileName="", AnsiString jpgraw_FileName="")
{
    if (raw_FileName.IsEmpty()) raw_FileName = ChangeFileExt(jpg_FileName, ".cr2");
    if (jpgraw_FileName.IsEmpty()) jpgraw_FileName = raw_FileName+".jpg";

    std::auto_ptr<TMemoryStream> jpg_MS(new TMemoryStream);
    std::auto_ptr<TMemoryStream> raw_MS(new TMemoryStream);
    jpg_MS->LoadFromFile(jpg_FileName);
    jpg_MS->Position = jpg_MS->Size;
    raw_MS->LoadFromFile(raw_FileName);
    raw_MS->Position = 0;
    raw_MS->SaveToStream(jpg_MS.get());
    unsigned __int32 size_raw = raw_MS->Size;
    jpg_MS->Write(&size_raw, sizeof(size_raw));
    jpg_MS->Position = 0;
    jpg_MS->SaveToFile(jpgraw_FileName);
    return 0;
}


int unpack(AnsiString rawjpg_FileName, AnsiString jpg_FileName="", AnsiString raw_FileName="")
{                         
    if (raw_FileName.IsEmpty()) ChangeFileExt( ChangeFileExt(rawjpg_FileName,""),".cr2");
    if (jpg_FileName.IsEmpty()) ChangeFileExt(raw_FileName,".jpg");

    std::auto_ptr<TMemoryStream> rawjpg_MS(new TMemoryStream);
    rawjpg_MS->LoadFromFile(rawjpg_FileName);
    unsigned __int32 size_raw;
    rawjpg_MS->Position = rawjpg_MS->Size - sizeof(size_raw);
    rawjpg_MS->Read(&size_raw, sizeof(size_raw));
    std::auto_ptr<TMemoryStream> raw_MS(new TMemoryStream);
    unsigned __int32 size_jpg = rawjpg_MS->Size - sizeof(size_raw) - size_raw;

    raw_MS->Write((void*)((int)rawjpg_MS->Memory+size_jpg), size_raw);
    raw_MS->Position = 0;
    raw_MS->SaveToFile(raw_FileName);
    rawjpg_MS->SetSize(size_jpg);
    rawjpg_MS->SaveToFile(jpg_FileName);
    return 0;
}


void PrintHelp()
{
    printf("    jpgraw -[option] filename\n");
    printf("\n");
    printf("    option:\n");
    printf("        -p  :   pack file JPG + RAW to JPGRAW file\n");
    printf("                filename - it's a name of JPG file.\n");
    printf("                .CR2 file must be placed near .JPG in this folder\n");
    printf("\n");
    printf("        -u  :   unpack JPGRAW file to separate JPG and RAW file\n");
    printf("                filename - it's a name of RAWJPG file.\n");
}

int main(int argc, char* argv[])
{
    if (argc<3) {
        PrintHelp();
        return 0;
    }
    AnsiString key = argv[1];
    if (key=="-p") {
        AnsiString jpg_FileName = "";
        AnsiString raw_FileName = "";
        AnsiString jpgraw_FileName = "";

        if (argc>2) jpg_FileName = argv[2];
        if (argc>3) raw_FileName = argv[3];
        if (argc>4) jpgraw_FileName = argv[4];

        pack(jpg_FileName, raw_FileName, jpgraw_FileName);
    }
    if (key=="-u") {
        AnsiString rawjpg_FileName = "";
        AnsiString raw_FileName = "";
        AnsiString jpg_FileName = "";

        if (argc>2) rawjpg_FileName = argv[2];
        if (argc>3) jpg_FileName = argv[3];
        if (argc>4) raw_FileName = argv[4];
        unpack(rawjpg_FileName, jpg_FileName, raw_FileName);
    }

    return 0;
}
//---------------------------------------------------------------------------
