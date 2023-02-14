#include <vector>
#include "Riostream.h"
#include <string>
#include <iostream>

//draw a chart of the nuclides with some color scheme
void make_chart_nuclides(){

  gROOT->SetBatch();//in order to have large canvas to generate high-res picture

  //create a canvas of sufficiently large size, here 8000x8000 pixels
  TCanvas *c1 = new TCanvas("canvas","c1",0,0,12000,8000);
  c1->cd();
  c1->SetBorderMode(0);

  //create a 2d histogram to draw the chart in, no axis tick marks
  TH2F *h = new TH2F("h","",75,0,75,50,0,50);
  h->GetXaxis()->SetTickLength(0);
  h->GetYaxis()->SetTickLength(0);
  h->Draw("A");

  //nuclei will be represented by TBox objects at coordinates (N,Z)
  //std::vector< TBox* > boxes;
  string line;
  int N;
  int Z;
  //need some code to color nuclei
  char var;//s == stable, p == proton rich, n == neutron rich, al == alpha decaying 
  TBox *b;

  //I read in data from the files nuclides_table.dat
  ifstream infile;
  infile.open("nuclides_table.dat");
  if(infile.is_open()){
    while(getline(infile,line)){
      if(line.find("#")!=string::npos)
	continue;
      if(sscanf(line.c_str(),"%d %d %c",&Z,&N,&var)==3){//read each line
	if(N<=200 && Z<120){//only interested in certain nuclides here
	  //Construct a new TBox (this is terrible coding)
	  b = new TBox(N*0.5+0.05,Z*0.5+0.05,N*0.5+0.45,Z*0.5+0.45);// memory leak!
	  if(var=='s')//stable nucleus, color it black
	    b->SetFillColor(kBlack);
	  if(var=='p')//proton rich nucleus, make a color
	    b->SetFillColor(TColor::GetColor(245,211,176));
	  if(var=='n')//neutron rich nucleus, make a color
	    b->SetFillColor(TColor::GetColor(226,235,241));
	  if(var=='a')//alpha decaying nucleus, make a color
	    b->SetFillColor(kYellow-7);
	  //Now handle nuclides that the group has studied,
	  //red == TRIPLEX
	  //blue == Others
	  b->Draw("same");
	}
      }
    }
  }
  infile.close();
  //draw lines around the magic numbers
  TLine *line1 = new TLine(8*0.5,1*0.5,8*0.5,17*0.5);
  line1->SetLineColor(TColor::GetColor(14,122,81));
  line1->SetLineWidth(4);
  line1->Draw("same");
  TLine *line2 = new TLine(9*0.5,1*0.5,9*0.5,17*0.5);
  line2->SetLineColor(TColor::GetColor(14,122,81));
  line2->SetLineWidth(4);
  line2->Draw("same");
  TLine *line3 = new TLine(3*0.5,8*0.5,22*0.5,8*0.5);
  line3->SetLineColor(TColor::GetColor(14,122,81));
  line3->SetLineWidth(4);
  line3->Draw("same");
  TLine *line4 = new TLine(3*0.5,9*0.5,22*0.5,9*0.5);
  line4->SetLineColor(TColor::GetColor(14,122,81));
  line4->SetLineWidth(4);
  line4->Draw("same");
  TLine *line5 = new TLine(20*0.5,7*0.5,20*0.5,31*0.5);
  line5->SetLineColor(TColor::GetColor(14,122,81));
  line5->SetLineWidth(4);
  line5->Draw("same");
  TLine *line6 = new TLine(21*0.5,7*0.5,21*0.5,31*0.5);
  line6->SetLineColor(TColor::GetColor(14,122,81));
  line6->SetLineWidth(4);
  line6->Draw("same");
  TLine *line7 = new TLine(13*0.5,20*0.5,45*0.5,20*0.5);
  line7->SetLineColor(TColor::GetColor(14,122,81));
  line7->SetLineWidth(4);
  line7->Draw("same");
  TLine *line8 = new TLine(13*0.5,21*0.5,45*0.5,21*0.5);
  line8->SetLineColor(TColor::GetColor(14,122,81));
  line8->SetLineWidth(4);
  line8->Draw("same");
  TLine *line9 = new TLine(18*0.5,28*0.5,55*0.5,28*0.5);
  line9->SetLineColor(TColor::GetColor(14,122,81));
  line9->SetLineWidth(4);
  line9->Draw("same");
  TLine *line10 = new TLine(18*0.5,29*0.5,55*0.5,29*0.5);
  line10->SetLineColor(TColor::GetColor(14,122,81));
  line10->SetLineWidth(4);
  line10->Draw("same");
  TLine *line11 = new TLine(28*0.5,10*0.5,28*0.5,35*0.5);
  line11->SetLineColor(TColor::GetColor(14,122,81));
  line11->SetLineWidth(4);
  line11->Draw("same");
  TLine *line12 = new TLine(29*0.5,10*0.5,29*0.5,35*0.5);
  line12->SetLineColor(TColor::GetColor(14,122,81));
  line12->SetLineWidth(4);
  line12->Draw("same");
  TLine *line13 = new TLine(48*0.5,50*0.5,90*0.5,50*0.5);
  line13->SetLineColor(TColor::GetColor(14,122,81));
  line13->SetLineWidth(4);
  line13->Draw("same");
  TLine *line14 = new TLine(48*0.5,51*0.5,90*0.5,51*0.5);
  line14->SetLineColor(TColor::GetColor(14,122,81));
  line14->SetLineWidth(4);
  line14->Draw("same");
  TLine *line15 = new TLine(50*0.5,26*0.5,50*0.5,52*0.5);
  line15->SetLineColor(TColor::GetColor(14,122,81));
  line15->SetLineWidth(4);
  line15->Draw("same");
  TLine *line16 = new TLine(51*0.5,26*0.5,51*0.5,52*0.5);
  line16->SetLineColor(TColor::GetColor(14,122,81));
  line16->SetLineWidth(4);
  line16->Draw("same");
  TLine *line17 = new TLine(90*0.5,82*0.5,130*0.5,82*0.5);
  line17->SetLineColor(TColor::GetColor(14,122,81));
  line17->SetLineWidth(4);
  line17->Draw("same");
  TLine *line18 = new TLine(90*0.5,83*0.5,130*0.5,83*0.5);
  line18->SetLineColor(TColor::GetColor(14,122,81));
  line18->SetLineWidth(4);
  line18->Draw("same");
  TLine *line19 = new TLine(82*0.5,45*0.5,82*0.5,75*0.5);
  line19->SetLineColor(TColor::GetColor(14,122,81));
  line19->SetLineWidth(4);
  line19->Draw("same");
  TLine *line20 = new TLine(83*0.5,45*0.5,83*0.5,75*0.5);
  line20->SetLineColor(TColor::GetColor(14,122,81));
  line20->SetLineWidth(4);
  line20->Draw("same");
  TLine *line21 = new TLine(126*0.5,75*0.5,126*0.5,85*0.5);
  line21->SetLineColor(TColor::GetColor(14,122,81));
  line21->SetLineWidth(4);
  line21->Draw("same");
  TLine *line22 = new TLine(127*0.5,75*0.5,127*0.5,85*0.5);
  line22->SetLineColor(TColor::GetColor(14,122,81));
  line22->SetLineWidth(4);
  line22->Draw("same");
  //now save the picture as a png
  if(gROOT->IsBatch())
    c1->Print("chart_of_nuclides.eps");

}
