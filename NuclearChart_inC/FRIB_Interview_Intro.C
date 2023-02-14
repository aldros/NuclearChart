#include <vector>
#include "Riostream.h"
#include <string>
#include <iostream>

//draw a chart of the nuclides with some color scheme
void FRIB_Interview_Intro(){

  gROOT->SetBatch();//in order to have large canvas to generate high-res picture
  gStyle->SetOptStat(0);
  
  //create a canvas of sufficiently large size, here 8000x4000 pixels
  TCanvas *c1 = new TCanvas("canvas","c1",0,0,8000,4000);
  c1->cd();
  c1->SetBorderMode(0);
  
  int ZMax = 15;
  int NMax = 30;
  int hMax = ZMax;
  Double_t CoefSize = 3.;
  if(hMax<NMax){hMax=NMax;}
  //create a 2d histogram to draw the chart in, no axis tick marks
  TH2F *h = new TH2F("h","",hMax+2,0,hMax+2,0.5*(hMax+2),0,0.5*(hMax+2));
  h->GetXaxis()->SetTickLength(0);
  h->GetYaxis()->SetTickLength(0);
  h->Draw("A");

  //nuclei will be represented by TBox objects at coordinates (N,Z)
  //std::vector< TBox* > boxes;
  string line;
  int N;
  int Z;
  //need some code to color nuclei
  char var;//s == stable, p == proton rich, n == neutron rich
  TBox *b;
  TPaveText *pt;
  Int_t ci = 12345;
  TColor *color = new TColor(ci, 1., 1., 1.);

  //I read in data from the files nuclides_table.dat
  ifstream infile;
  infile.open("nuclides_table.dat");
  if(infile.is_open()){
    while(getline(infile,line)){
      if(line.find("#")!=string::npos)
	continue;
      if(sscanf(line.c_str(),"%d %d %c",&Z,&N,&var)==3){//read each line
	if(N<NMax && Z<ZMax){//only interested in certain nuclides here
	  //Construct a new TBox (this is terrible coding)
	  b = new TBox(N+0.1,Z+0.1,N+0.9,Z+0.9);// memory leak!
	  pt = new TPaveText(N+0.03,Z+0.03,N+0.97,Z+0.97);
	  TString symbol = "";
	  if(Z==0){symbol =  "n";}
	  if(Z==1){symbol =  "H";}
	  if(Z==2){symbol =  "He";}
	  if(Z==3){symbol =  "Li";}
	  if(Z==4){symbol =  "Be";}
	  if(Z==5){symbol =  "B";}
	  if(Z==6){symbol =  "C";}
	  if(Z==7){symbol =  "N";}
	  if(Z==8){symbol =  "O";}
	  if(Z==9){symbol =  "F";}
	  if(Z==10){symbol =  "Ne";}
	  if(Z==11){symbol =  "Na";}
	  if(Z==12){symbol =  "Mg";}
	  if(Z==13){symbol =  "Al";}
	  if(Z==14){symbol =  "Si";}
	  if(Z==15){symbol =  "P";}
	  if(Z==16){symbol =  "S";}
	  if(Z==17){symbol =  "Cl";}
	  if(Z==18){symbol =  "Ar";}
	  if(Z==19){symbol =  "K";}
	  if(Z==20){symbol =  "Ca";}
	  if(Z==21){symbol =  "Sc";}
	  if(Z==22){symbol =  "Ti";}
	  if(Z==23){symbol =  "V";}
	  if(Z==24){symbol =  "Cr";}
	  if(Z==25){symbol =  "Mn";}
	  if(Z==26){symbol =  "Fe";}
	  if(Z==27){symbol =  "Co";}
	  if(Z==28){symbol =  "Ni";}
	  if(Z==29){symbol =  "Cu";}
	  if(Z==30){symbol =  "Zn";}
	  if(Z==31){symbol =  "Ga";}
	  if(Z==32){symbol =  "Ge";}
	  if(Z==33){symbol =  "As";}
	  if(Z==34){symbol =  "Se";}
	  if(Z==35){symbol =  "Br";}
	  if(Z==36){symbol =  "Kr";}
	  if(Z==37){symbol =  "Rb";}
	  if(Z==38){symbol =  "Sr";}
	  if(Z==39){symbol =  "Y";}
	  int A = N+Z;
	  symbol = Form("^{%d}",A)+symbol;
	  //legend
	  if(Z>9 && N==1){
	    symbol = "";
	  }
	  Double_t trans = 0.2;
	  //highlight
	  //Short-range
	  //17B
	  if(Z==5 && A==17){
	    trans = 1;
	  }
	  //8He
	  if(Z==2 && A==8){
	    trans = 1;
	  }
	  //31Ne
	  if(Z==10 && A==31){
	    trans = 1;
	  }
	  //26F
	  if(Z==9 && A==26){
	    trans = 1;
	  }
	  //mid-range
	  if(Z==12 && A==37){
	    trans = 1;
	  }
	  if(Z==12 && A==35){
	    trans = 1;
	  }
	  if(Z==9 && A==29){
	    trans = 1;
	  }
	  if(Z==9 && A==31){
	    trans = 1;
	  }
	  if(Z==10 && A==33){
	    trans = 1;
	  }
	  if(Z==12 && A==39){
	    trans = 1;
	  }
	  if(Z==10 && A==34){
	    trans = 1;
	  }
	  if(Z==11 && A==36){
	    trans = 1;
	  }
	  if(Z==11 && A==37){
	    trans = 1;
	  }
	  //N=20
	  // if(Z<14){
	  //   if(Z>=8 && Z<=20 && N>=10 && N<=22 && N%2==0 && Z%2==0){
	  //     if((Z==8 && N>18) || (Z>=16 && N<12)){

	  //     }else{
	  // 	trans = 1.;
	  //     }
	  //   }
	  // }
	  if(var=='s'){//stable nucleus, color it black
	    // b->SetFillColor(kBlack);
	    // pt->SetFillColor(kBlack);
	    pt->SetFillColorAlpha(kBlack,trans+0.1);
	    TText *t1 = pt->AddText(symbol);
	    t1->SetTextColor(ci);
	    t1->SetTextAlign(22);
	    t1->SetTextSize(CoefSize*0.006);
	  }
	  if(var=='p'){//proton rich nucleus, make a color
	    //b->SetFillColor(TColor::GetColor(245,211,176));
	    //pt->SetFillColor(TColor::GetColor(255,128,128));
	    pt->SetFillColorAlpha(kRed,trans);
	    TText *t1 = pt->AddText(symbol);
	    t1->SetTextAlign(22);
	    t1->SetTextColor(ci);
	    t1->SetTextSize(CoefSize*0.006);
	  }
	  if(var=='n'){//neutron rich nucleus, make a color
	    pt->SetFillColorAlpha(kBlue,trans);
	    //pt->SetFillColor(TColor::GetColor(128,179,255));
	    TText *t1 = pt->AddText(symbol);
	    t1->SetTextAlign(22);
	    t1->SetTextColor(ci);
	    t1->SetTextSize(CoefSize*0.006);
	  }
	  if(var=='u'){//unbound nucleus, make a color
	    //b->SetFillColor(TColor::GetColor(245,211,176));
	    //pt->SetFillColor(TColor::GetColor(245,211,176));
	    pt->SetFillColorAlpha(kOrange,trans);
	    TText *t1 = pt->AddText(symbol);
	    t1->SetTextAlign(22);
	    t1->SetTextColor(TColor::GetColor(140,140,140));
	    if(trans==1){
	      t1->SetTextColor(kBlack);
	    }
	    t1->SetTextSize(CoefSize*0.006);
	  }
	  //Now handle nuclides that I studied,
	  //red == proton-rich
	  //blue == neutron-rich
	  // if(Z==9 && N==19){//28F
	  //   b->SetFillColor(kBlue);
	  // }
	  // if(Z==6 && N==12)//18C
	  //    b->SetFillColor(kBlue);
	  // if(Z==8 && N==12)//20O
	  //   b->SetFillColor(kBlue);
	  // if(Z==23 && N==20)//43V
	  //   b->SetFillColor(kRed);
	  // if(Z==24 && N==38)//62Cr
	  //   b->SetFillColor(kRed);
	  // if(Z==28 && N==30)//58Ni
	  //   b->SetFillColor(kRed);
	  // if(Z==33 && N==37)//70As
	  //   b->SetFillColor(kBlue);
	  // if(Z==34 && N==34)//68Se
	  //   b->SetFillColor(kRed);
	  // if(Z==34 && N==36)//70Se
	  //   b->SetFillColor(kRed);
	  // if(Z==35 && N==35)//70Br
	  //   b->SetFillColor(kRed);
	  // if(Z==36 && N==36)//72Kr
	  //   b->SetFillColor(kRed);
	  // if(Z==36 && N==38)//74Kr
	  //   b->SetFillColor(kRed);
	  // if(Z==37 && N==37)//74Rb
	  //   b->SetFillColor(kRed);
	  // if(Z==38 && N==38)//76Sr
	  //   b->SetFillColor(kBlue);
	  // if(Z==38 && N==40)//78Sr
	  //   b->SetFillColor(kBlue);
	  //b->Draw("same");
	  pt->Draw("same");	  
	  //make 19C split color
	  // Float_t x[] = {13.1,13.1,13.9,13.1};
	  // Float_t y[] = {6.1,6.9,6.9,6.1};
	  // TGraph *p = new TGraph(4,x,y);
	  // p->SetLineColor(kRed);
	  // p->SetFillColor(kRed);
	  // p->Draw("F,same");
	  
	  //make 28F with white square in the middle (unbound)
	  /*
	    Float_t x[] = {19.3,19.3,19.7,19.7};
	    Float_t y[] = {9.3,9.7,9.7,9.3};
	    TGraph *p = new TGraph(4,x,y);
	    p->SetLineColor(0);
	    p->SetFillColor(0);
	    p->Draw("F,same");
	  */
	}
      }
    }
  }
  infile.close();
  //draw lines around the magic numbers
  //N=8
  TLine *line1 = new TLine(8,1,8,ZMax);
  line1->SetLineColor(TColor::GetColor(14,122,81));
  line1->SetLineWidth(4);
  line1->Draw("same");
  TLine *line2 = new TLine(9,1,9,ZMax);
  line2->SetLineColor(TColor::GetColor(14,122,81));
  line2->SetLineWidth(4);
  line2->Draw("same");
  //Z=8
  TLine *line3 = new TLine(3,8,22,8);
  line3->SetLineColor(TColor::GetColor(14,122,81));
  line3->SetLineWidth(4);
  line3->Draw("same");
  TLine *line4 = new TLine(3,9,22,9);
  line4->SetLineColor(TColor::GetColor(14,122,81));
  line4->SetLineWidth(4);
  line4->Draw("same");
  //N=20
  TLine *line5 = new TLine(20,7,20,ZMax);
  line5->SetLineColor(TColor::GetColor(14,122,81));
  line5->SetLineWidth(4);
  line5->Draw("same");
  TLine *line6 = new TLine(21,7,21,ZMax);
  line6->SetLineColor(TColor::GetColor(14,122,81));
  line6->SetLineWidth(4);
  line6->Draw("same");
  //Z=20
  // TLine *line7 = new TLine(13,20,40,20);
  // line7->SetLineColor(TColor::GetColor(14,122,81));
  // line7->SetLineWidth(4);
  // line7->Draw("same");
  // TLine *line8 = new TLine(13,21,40,21);
  // line8->SetLineColor(TColor::GetColor(14,122,81));
  // line8->SetLineWidth(4);
  // line8->Draw("same");
  //Z=28
  // TLine *line9 = new TLine(18,28,48,28);
  // line9->SetLineColor(TColor::GetColor(14,122,81));
  // line9->SetLineWidth(4);
  // line9->Draw("same");
  // TLine *line10 = new TLine(18,29,48,29);
  // line10->SetLineColor(TColor::GetColor(14,122,81));
  // line10->SetLineWidth(4);
  // line10->Draw("same");
  //N=28
  TLine *line11 = new TLine(28,10,28,ZMax);
  line11->SetLineColor(TColor::GetColor(14,122,81));
  line11->SetLineWidth(4);
  line11->Draw("same");
  TLine *line12 = new TLine(29,10,29,ZMax);
  line12->SetLineColor(TColor::GetColor(14,122,81));
  line12->SetLineWidth(4);
  line12->Draw("same");
  //now save the picture as a png
  if(gROOT->IsBatch())
    c1->Print("chart_FRIB_Interview_Intro.png");

}
