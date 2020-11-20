#include "algo_top_parameters.h"
#include "algo_top.h"
#include <algorithm>
#include <utility>

#include "../../../../include/objects.h"
using namespace std;
using namespace algo;


void unpackInputLink(hls::stream<algo::axiword576> &ilink, Tower towers[TOWERS_IN_ETA/2]) {
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME
#pragma HLS ARRAY_PARTITION variable=towers complete dim=0
#pragma HLS INTERFACE axis port=ilink
#pragma HLS INLINE

  ap_uint<576> word_576b_;

#ifndef __SYNTHESIS__
   //Avoid simulation warnings
  if (ilink.empty()) return;
#endif

  word_576b_ = ilink.read().data;

  towers[0]  = Tower(word_576b_( 31,   0));
  towers[1]  = Tower(word_576b_( 63,  32));
  towers[2]  = Tower(word_576b_( 95,  64));
  towers[3]  = Tower(word_576b_(127,  96));
  towers[4]  = Tower(word_576b_(159, 128));
  towers[5]  = Tower(word_576b_(191, 160));
  towers[6]  = Tower(word_576b_(223, 192));
  towers[7]  = Tower(word_576b_(255, 224));
  towers[8]  = Tower(word_576b_(287, 256));
  towers[9]  = Tower(word_576b_(319, 288));
  towers[10] = Tower(word_576b_(351, 320));
  towers[11] = Tower(word_576b_(383, 352));
  towers[12] = Tower(word_576b_(415, 384));
  towers[13] = Tower(word_576b_(447, 416));
  towers[14] = Tower(word_576b_(479, 448));
  towers[15] = Tower(word_576b_(511, 480));
  towers[16] = Tower(word_576b_(543, 512));

  return;
}

void packOutput(ap_uint<16> a[0], hls::stream<algo::axiword576> &olink){
#pragma HLS PIPELINE II=N_OUTPUT_WORDS_PER_FRAME
#pragma HLS ARRAY_PARTITION variable=a complete dim=0
#pragma HLS INTERFACE axis port=olink
#pragma HLS INLINE

  ap_uint<576> word_576b_;


  word_576b_(15, 0) = (ap_uint<16>) a[0];
  word_576b_(31, 15) = (ap_uint<16>) a[1];
  word_576b_(47, 32) = (ap_uint<16>) a[2];
  word_576b_(63, 48) = (ap_uint<16>) a[3];
  word_576b_(79, 64) = (ap_uint<16>) a[4];
  word_576b_(95, 80) = (ap_uint<16>) a[5];
  word_576b_(111, 96) = (ap_uint<16>) a[6];
  word_576b_(127, 112) = (ap_uint<16>) a[7];
  word_576b_(143, 128) = (ap_uint<16>) a[8];
  word_576b_(159, 144) = (ap_uint<16>) a[9];
  word_576b_(175, 160) = (ap_uint<16>) a[10];
  word_576b_(191, 176) = (ap_uint<16>) a[11];
  word_576b_(207, 192) = (ap_uint<16>) a[12];
  word_576b_(223, 208) = (ap_uint<16>) a[13];
  word_576b_(239, 224) = (ap_uint<16>) a[14];
  word_576b_(255, 240) = (ap_uint<16>) a[15];
  word_576b_(271, 256) = (ap_uint<16>) a[16];
  word_576b_(287, 272) = (ap_uint<16>) a[17];
  word_576b_(303, 288) = (ap_uint<16>) a[18];
  word_576b_(319, 304) = (ap_uint<16>) a[19];
  word_576b_(335, 320) = (ap_uint<16>) a[20];
  word_576b_(351, 336) = (ap_uint<16>) a[21];
  word_576b_(367, 352) = (ap_uint<16>) a[22];
  word_576b_(383, 368) = (ap_uint<16>) a[23];
  word_576b_(575, 384) = 0;
    axiword576 r; r.last = 0; r.user = 0;
  r.data = word_576b_;
  
  olink.write(r);

  return ;
}

void algo_top(hls::stream<axiword576> link_in[N_INPUT_LINKS], hls::stream<axiword576> link_out[N_OUTPUT_LINKS]) {
#pragma HLS INTERFACE axis port=link_in
#pragma HLS INTERFACE axis port=link_out
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME

#pragma HLS ARRAY_PARTITION variable=link_in complete dim=0
#pragma HLS ARRAY_PARTITION variable=link_out complete dim=0


  // Step 1: Unpack links
  // Input is 64 links carrying 32phix34eta towers
  Tower towers[TOWERS_IN_PHI][TOWERS_IN_ETA];
#pragma HLS ARRAY_PARTITION variable=towers complete dim=0
     
  for (size_t ilink = 0; ilink < N_INPUT_LINKS/2; ilink++) {
#pragma LOOP UNROLL
#pragma HLS latency min=1
    size_t iPosEta = ilink;
    size_t iNegEta = ilink+N_INPUT_LINKS/2;
    unpackInputLink(link_in[iNegEta], &towers[ilink][0]);
    unpackInputLink(link_in[iPosEta], &towers[ilink][TOWERS_IN_ETA/2]);
  }

   // Step 2: MET Algo goes here
  ap_uint<16> Exs[24];
#pragma HLS ARRAY_PARTITION variable=Exs complete dim=0
  ap_uint<16> Eys[24];
#pragma HLS ARRAY_PARTITION variable=Eys complete dim=0
  double sinphi[TOWERS_IN_PHI]={0.04362,0.13053,0.21644,0.30071,0.38268,0.46175,0.53730,0.60876,0.67559,0.73728,0.79335,0.84339,
  0.88701,0.92388,0.95372,0.97630,0.99144,0.99905,0.99905,0.99144,0.97630,0.95372,0.92388,0.88701,0.84339,0.79335,0.73728,
  0.67559,0.60876,0.53730,0.46175,0.38268};
#pragma HLS ARRAY_PARTITION variable=sinphi complete dim=0
  double cosphi[TOWERS_IN_PHI]={0.99905,0.99144,0.97630,0.95372,0.92388,0.88701,0.84339,0.79335,0.73728,0.67559,0.60876,0.53730,
		  0.46175,0.38268,0.30071,0.21644,0.13053,0.04362,-0.04362,-0.13053,-0.21644,-0.30071,-0.38268,-0.46175,-0.53730,
		  -0.60876,-0.67559,-0.73728,-0.79335,-0.84339,-0.88701,-0.92388};
#pragma HLS ARRAY_PARTITION variable=cosphi complete dim=0
  for (int b = 4; b < 28; b++) {
#pragma LOOP UNROLL
#pragma HLS latency min=1
	  double Ey;double Ex;
  		ap_uint<16> j;
  		/*double c; double d; double e; double f; double g; double h; double i; double k;
  		double l; double m; double n; double o; double p; double q; double r; double s; double t;
  		double u; double v; double w; double x; double y; double z; double cc; double dd; double ee;
  		double ff; double gg; double hh; double ii; double jj; double kk;
  		c=towers[b][0].tower_et() + towers[b][1].tower_et();
  		d=towers[b][2].tower_et() + towers[b][3].tower_et();
  		e=towers[b][4].tower_et() + towers[b][5].tower_et();
  		f=towers[b][6].tower_et() + towers[b][7].tower_et();
  		g=towers[b][8].tower_et() + towers[b][9].tower_et();
  		h=towers[b][10].tower_et() + towers[b][11].tower_et();
  		i=towers[b][12].tower_et() + towers[b][13].tower_et();
  		k=towers[b][14].tower_et() + towers[b][15].tower_et();
  		l=towers[b][16].tower_et() + towers[b][17].tower_et();
  		m=towers[b][18].tower_et() + towers[b][19].tower_et();
  		n=towers[b][20].tower_et() + towers[b][21].tower_et();
  		o=towers[b][22].tower_et() + towers[b][23].tower_et();
  		p=towers[b][24].tower_et() + towers[b][25].tower_et();
  		q=towers[b][26].tower_et() + towers[b][27].tower_et();
  		r=towers[b][28].tower_et() + towers[b][29].tower_et();
  		s=towers[b][30].tower_et() + towers[b][31].tower_et();
  		t=towers[b][32].tower_et() + towers[b][33].tower_et();
  		u=c+d; v=e+f; w=g+h; x=i+k; y=l+m; z=n+o; cc=p+q; dd=r+s;
  		ee=u+v; ff=w+x; gg=y+z; hh=cc+dd;
  		ii=ee+ff; jj=gg+hh;
  		kk=ii+jj;
  		j=kk+t;*/

  		 j = towers[b][0].tower_et() + towers[b][1].tower_et() + towers[b][2].tower_et() + towers[b][3].tower_et() +
  				 towers[b][4].tower_et() + towers[b][5].tower_et() + towers[b][6].tower_et() + towers[b][7].tower_et() +
				 towers[b][8].tower_et() + towers[b][9].tower_et() + towers[b][10].tower_et() + towers[b][11].tower_et() +
				 towers[b][12].tower_et() + towers[b][13].tower_et() + towers[b][14].tower_et() + towers[b][15].tower_et() +
				 towers[b][16].tower_et() + towers[b][17].tower_et() + towers[b][18].tower_et() + towers[b][19].tower_et() +
				 towers[b][20].tower_et() + towers[b][21].tower_et() + towers[b][22].tower_et() + towers[b][23].tower_et() +
				 towers[b][24].tower_et() + towers[b][25].tower_et() + towers[b][26].tower_et() + towers[b][27].tower_et() +
				 towers[b][28].tower_et() + towers[b][29].tower_et() + towers[b][30].tower_et() + towers[b][31].tower_et() +
				 towers[b][32].tower_et() + towers[b][33].tower_et();
  		Ey = sinphi[b]*j;
  		//cout << Ey << endl;
  		Eys[b-4] = Ey*1000;
  		Ex = cosphi[b]*j;
  		Exs[b-4] = Ex*1000;
  		//cout << Ex <<endl;
  	}
  // Step 3: Pack the outputs

    packOutput(&Exs[0],link_out[0]);
    packOutput(&Eys[0],link_out[1]);
}
