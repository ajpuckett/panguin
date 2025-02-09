///////////////////////////////////////////////////////////////////
//  Macro to help with online analysis
//    B. Moffit  Oct. 2003
#ifndef panguinOnline_h
#define panguinOnline_h 1

#include <TTree.h>
#include <TFile.h>
#include <TGButton.h>
#include <TGFrame.h>
#include <TGListBox.h>
#include <TRootEmbeddedCanvas.h>
#include "TGLabel.h"
#include "TGString.h"
#include <vector>
#include <string>
#include <map>
#include <TString.h>
#include <TCut.h>
#include <TTimer.h>
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "panguinOnlineConfig.hh"

#define UPDATETIME 10000

class OnlineGUI {
  TGMainFrame* fMain = nullptr;
  TGHorizontalFrame* fTopframe = nullptr;
  TGVerticalFrame* vframe = nullptr;
  TGListBox* fPageListBox = nullptr;
  TGPictureButton* wile = nullptr;
  TGTextButton* fNow = nullptr; // current time
  TGTextButton* fLastUpdated = nullptr; // plots last updated
  TGTextButton* fRootFileLastUpdated = nullptr; // Root file last updated
  TRootEmbeddedCanvas* fEcanvas = nullptr;
  TGHorizontalFrame* fBottomFrame = nullptr;
  TGHorizontalFrame* hframe = nullptr;
  TGTextButton* fNext = nullptr;
  TGTextButton* fPrev = nullptr;
  TGTextButton* fExit = nullptr;
  TGLabel* fRunNumber = nullptr;
  TGTextButton* fPrint = nullptr;
  TCanvas* fCanvas = nullptr; // Present Embedded canvas
  OnlineConfig fConfig;
  Int_t current_page;
  Int_t current_pad;
  TFile* fRootFile = nullptr;
  TFile* fGoldenFile = nullptr;
  Bool_t doGolden;
  std::vector<TTree*> fRootTree;
  std::vector<Int_t> fTreeEntries;
  std::vector<std::pair<TString, TString> > fileObjects;
  std::vector<std::vector<TString> > treeVars;
  Int_t runNumber;
  TTimer* timer = nullptr;
  TTimer* timerNow = nullptr; // used to update time
  Bool_t fUpdate;
  Bool_t fFileAlive;
  Bool_t fPrintOnly;
  Bool_t fSaveImages;
  TH1* mytemp1d = nullptr;
  TH2* mytemp2d = nullptr;
  TH3* mytemp3d = nullptr;
  TH1* mytemp1d_golden = nullptr;
  //TH2* mytemp2d_golden = nullptr;
  TH3* mytemp3d_golden = nullptr;

  int fVerbosity;

  std::string SubstitutePlaceholders(
    std::string str, const std::string& var = std::string() ) const;

public:
  using cmdmap_t = std::map<std::string, std::string>;
  explicit OnlineGUI( const OnlineConfig& config );
  explicit OnlineGUI( OnlineConfig&& config );
  void CreateGUI( const TGWindow* p, UInt_t w, UInt_t h );
  virtual ~OnlineGUI();
  void DoDraw();
  void DrawPrev();
  void DrawNext();
  void DoListBox( Int_t id );
  void CheckPageButtons();
  // Specific Draw Methods
  Bool_t IsHistogram( const TString& );
  void GetFileObjects();
  void GetTreeVars();
  void GetRootTree();
  UInt_t GetTreeIndex( const TString& );
  UInt_t GetTreeIndexFromName( const TString& );
  void TreeDraw( const cmdmap_t& command );
  void HistDraw( const cmdmap_t& command );
  void MacroDraw( const cmdmap_t& command );
  void LoadDraw( const cmdmap_t& command );
  void LoadLib( const cmdmap_t& command );
  void SaveImage( TObject* o, const cmdmap_t& command ) const;
  void SaveMacroImage( const cmdmap_t& drawcommand );
  void DoDrawClear();
  void TimerUpdate();
  void UpdateCurrentTime();  // update current time
  static void BadDraw( const TString& );
  void CheckRootFile();
  Int_t OpenRootFile();
  void PrintToFile();
  void PrintPages();
  void MyCloseWindow();
  void CloseGUI();
  void SetVerbosity( int ver ) { fVerbosity = ver; }
  ClassDef(OnlineGUI, 0)
};

#endif //panguinOnline_h
