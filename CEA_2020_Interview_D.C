#include <vector>
#include "Riostream.h"
#include <string>
#include <iostream>

//draw a chart of the nuclides with some color scheme
void CEA_2020_Interview_D(){

  gROOT->SetBatch();//in order to have large canvas to generate high-res picture
  gStyle->SetOptStat(0);
  
  //create a canvas of sufficiently large size, here 8000x8000 pixels
  TCanvas *c1 = new TCanvas("canvas","c1",0,0,8000,8000);
  c1->cd();
  c1->SetBorderMode(0);

  //create a 2d histogram to draw the chart in, no axis tick marks
  TH2F *h = new TH2F("h","",50,0,50,50,0,50);
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

  //I read in data from the files nuclides_table.dat
  ifstream infile;
  infile.open("nuclides_table.dat");
  if(infile.is_open()){
    while(getline(infile,line)){
      if(line.find("#")!=string::npos)
	continue;
      if(sscanf(line.c_str(),"%d %d %c",&Z,&N,&var)==3){//read each line
	if(N<=45 && Z<39){//only interested in certain nuclides here
	  //Construct a new TBox (this is terrible coding)
	  b = new TBox(N+0.1,Z+0.1,N+0.9,Z+0.9);// memory leak!
	  if(var=='s')//stable nucleus, color it black
	    b->SetFillColor(kBlack);
	  if(var=='p')//proton rich nucleus, make a color
	    b->SetFillColor(TColor::GetColor(245,211,176));
	  if(var=='n'){//neutron rich nucleus, make a color
	    b->SetFillColor(TColor::GetColor(226,235,241));
	  }
	  if(var=='u'){//unbound nucleus, make a color
	    b->SetFillColor(0);
	  }
	  //Now handle nuclides that I studied,
	  //red == proton-rich
	  //blue == neutron-rich
	  if(Z==9 && N==19){//28F
	    b->SetFillColor(kBlue);
	  }
	  // if(Z==3 && N==8)//11Li
	  //   b->SetFillColor(kBlue);
	  // if(Z==5 && N==9)//14B
	  //   b->SetFillColor(kBlue);
	  // if(Z==4 && N==10)//14Be
	  //   b->SetFillColor(kBlue);
	  // if(Z==5 && N==12)//17B
	  //   b->SetFillColor(kBlue);
	  // if(Z==8 && N==17)//25O
	  //   b->SetFillColor(kBlue);
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
	  b->Draw("same");
	  //make 19C split color
	  // Float_t x[] = {13.1,13.1,13.9,13.1};
	  // Float_t y[] = {6.1,6.9,6.9,6.1};
	  // TGraph *p = new TGraph(4,x,y);
	  // p->SetLineColor(kRed);
	  // p->SetFillColor(kRed);
	  // p->Draw("F,same");
	  //make 28F with white square in the middle (unbound)
	  Float_t x[] = {19.3,19.3,19.7,19.7};
	  Float_t y[] = {9.3,9.7,9.7,9.3};
	  TGraph *p = new TGraph(4,x,y);
	  p->SetLineColor(0);
	  p->SetFillColor(0);
	  p->Draw("F,same");
	  // //make 25O with white square in the middle (unbound)
	  // Float_t x1[] = {17.3,17.3,17.7,17.7};
	  // Float_t y1[] = {8.3,8.7,8.7,8.3};
	  // TGraph *p1 = new TGraph(4,x1,y1);
	  // p1->SetLineColor(0);
	  // p1->SetFillColor(0);
	  // p1->Draw("F,same");
	}
      }
    }
  }
  infile.close();
  //draw lines around the magic numbers
  TLine *line1 = new TLine(8,1,8,17);
  line1->SetLineColor(TColor::GetColor(14,122,81));
  line1->SetLineWidth(4);
  line1->Draw("same");
  TLine *line2 = new TLine(9,1,9,17);
  line2->SetLineColor(TColor::GetColor(14,122,81));
  line2->SetLineWidth(4);
  line2->Draw("same");
  TLine *line3 = new TLine(3,8,22,8);
  line3->SetLineColor(TColor::GetColor(14,122,81));
  line3->SetLineWidth(4);
  line3->Draw("same");
  TLine *line4 = new TLine(3,9,22,9);
  line4->SetLineColor(TColor::GetColor(14,122,81));
  line4->SetLineWidth(4);
  line4->Draw("same");
  TLine *line5 = new TLine(20,7,20,31);
  line5->SetLineColor(TColor::GetColor(14,122,81));
  line5->SetLineWidth(4);
  line5->Draw("same");
  TLine *line6 = new TLine(21,7,21,31);
  line6->SetLineColor(TColor::GetColor(14,122,81));
  line6->SetLineWidth(4);
  line6->Draw("same");
  TLine *line7 = new TLine(13,20,40,20);
  line7->SetLineColor(TColor::GetColor(14,122,81));
  line7->SetLineWidth(4);
  line7->Draw("same");
  TLine *line8 = new TLine(13,21,40,21);
  line8->SetLineColor(TColor::GetColor(14,122,81));
  line8->SetLineWidth(4);
  line8->Draw("same");
  TLine *line9 = new TLine(18,28,48,28);
  line9->SetLineColor(TColor::GetColor(14,122,81));
  line9->SetLineWidth(4);
  line9->Draw("same");
  TLine *line10 = new TLine(18,29,48,29);
  line10->SetLineColor(TColor::GetColor(14,122,81));
  line10->SetLineWidth(4);
  line10->Draw("same");
  TLine *line11 = new TLine(28,10,28,35);
  line11->SetLineColor(TColor::GetColor(14,122,81));
  line11->SetLineWidth(4);
  line11->Draw("same");
  TLine *line12 = new TLine(29,10,29,35);
  line12->SetLineColor(TColor::GetColor(14,122,81));
  line12->SetLineWidth(4);
  line12->Draw("same");
  //now save the picture as a png
  if(gROOT->IsBatch())
    c1->Print("chart_CEA_Interview_D.png");

}
