TChain* GetChainForTestMode ( const char* treeName ) const;

void getChain()

{

TString txt = "list.txt";


FindTreeNames (txt);


}











void FindTreeNames ( TString file_list ) const
    {

//     if ( file.IsNull() )
//             { cout << "For LOCAL modes the local list of files must be set" << endl; return NULL; }

    if ( gSystem->AccessPathName ( file_list.Data() ) )
            { cout << "File not found: " << file_list.Data() << endl; return NULL; }

    // Open the file
    ifstream in; in.open ( file_list.Data() );
    Int_t count = 0;
    // Read the input list of files and add them to the chain
    TString line;


//     TString streeName ( treeName );


/*


    if ( IsUseMCchain() ) streeName = "TE";

    TChain* chain = new TChain ( streeName );
    TList* friends = new TList();
    TChain* cfriend = 0;

*/


//     TString bpath;
//     TIter nextfriend ( friends );

    while ( in.good() )
            {
            in >> line;

            if ( line.IsNull() || line.BeginsWith ( "#" ) ) continue;

            if ( count++ == 1 ) break; // look only over first file;

            TString file ( line );

            cout << "before" << endl;
            TFile* f = TFile::Open (file.Data());
            cout << "after" << endl;

            if ( f && !f->IsZombie() )
                    {

                    TKey* aod_key = f->FindKey("aodTree");
                    TKey* esd_key = f->FindKey("esdTree");
                    TKey*  te_key = f->FindKey("TE");

                    TString aod_str = aod_key ? aod_key->GetName() : "" ;
                    TString esd_str = esd_key ? esd_key->GetName() : "" ;
                    TString  mc_str =  te_key ?  te_key->GetName() : "" ;

//                     cout << "key name : " << aodkey->GetName() << endl;
                    cout << "key name : " << aod_str.Data() << endl;
                    cout << "key name : " << esd_str.Data() << endl;
                    cout << "key name : " <<  mc_str.Data() << endl;


                    f->Close();


                    }
            else
                    {
                    cout << "GetChainforTestMode :: Skipping un-openable file: << " << file.Data()  << endl;
                    }
            }

    in.close();


// AliAODHandler -> AliAODEvent*   GetAOD() -> AliAODHeader * GetHeader() -> UInt_t    GetPeriodNumber() 





/*


    if ( !chain->GetListOfFiles()->GetEntries() )
            {
            Error ( "GetChainForTestMode", "No file from %s could be opened", fFileForTestMode.Data() );
            delete chain;
            friends->Delete();
            delete friends;
            return NULL;
            }*/

    return;
    }
