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

//#ifndef __SYNTHESIS__
  // Avoid simulation warnings
  //if (link.empty()) return;
//#endif

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
/*void uil(hls::stream<algo::axiword576> &ilink, ap_fixed<16,10> towers[32]) {
#pragma HLS PIPELINE II=N_WORDS_PER_FRAME
#pragma HLS ARRAY_PARTITION variable=towers complete dim=0
#pragma HLS INTERFACE axis port=ilink
#pragma HLS INLINE

  ap_uint<576> word_576b_;

//#ifndef __SYNTHESIS__
  // Avoid simulation warnings
  //if (link.empty()) return;
//#endif

  word_576b_ = ilink.read().data;

  	towers[0]=word_576b_( 17,   0);
  	towers[1]=word_576b_( 35,  18) ;
	towers[2]=word_576b_( 53,  36) ;
	towers[3]=ap_fixed<16,10>(word_576b_( 71,  54)) ;
	towers[4]=ap_fixed<16,10>(word_576b_( 89,  72)) ;
	towers[5]=word_576b_( 107, 90) ;
	towers[6]=word_576b_( 125, 108) ;
	towers[7]=word_576b_( 143, 126) ;
	towers[8]=word_576b_( 161, 144) ;
	towers[9]=word_576b_( 179, 162) ;
	towers[10]=word_576b_( 197, 180) ;
	towers[11]=word_576b_( 215, 198) ;
	towers[12]=word_576b_( 233, 216) ;
	towers[13]=word_576b_( 251, 234) ;
	towers[14]=word_576b_( 269, 252) ;
	towers[15]=word_576b_( 287, 270) ;
	towers[16]=word_576b_( 305, 288) ;
	towers[17]=word_576b_( 323, 306) ;
	towers[18]=word_576b_( 341, 324) ;
	towers[19]=word_576b_( 359, 342) ;
	towers[20]=word_576b_( 377, 360) ;
	towers[21]=word_576b_( 395, 378) ;
	towers[22]=word_576b_( 413, 396) ;
	towers[23]=word_576b_( 431, 414) ;
  	towers[24]=word_576b_( 449, 432) ;
  	towers[25]=word_576b_( 467, 450) ;
  	towers[26]=word_576b_( 485, 468) ;
  	towers[27]=word_576b_( 503, 486) ;
  	towers[28]=word_576b_( 521, 504) ;
  	towers[29]=word_576b_( 539, 522) ;
  	towers[30]=word_576b_( 557, 540) ;
  	towers[31]=word_576b_( 575, 558) ;

  return;
}*/

void packOutput(double a[32], hls::stream<algo::axiword576> &olink){
#pragma HLS PIPELINE II=N_OUTPUT_WORDS_PER_FRAME
#pragma HLS ARRAY_PARTITION variable=a complete dim=0
#pragma HLS INTERFACE axis port=olink
#pragma HLS INLINE

  ap_uint<576> word_576b_;

  /*word_576b_( 17,   0) = (ap_fixed<16,10,AP_RND>) a[0];
  word_576b_( 35,  18) = (ap_fixed<16,10,AP_RND>) a[1];
  word_576b_( 53,  36) = (ap_fixed<16,10,AP_RND>) a[2];
  word_576b_( 71,  54) = (ap_fixed<16,10,AP_RND>) a[3];
  word_576b_( 89,  72) = (ap_fixed<16,10,AP_RND>) a[4];
  word_576b_( 107, 90) = (ap_fixed<16,10,AP_RND>) a[5];
  word_576b_( 125, 108) = (ap_fixed<16,10,AP_RND>) a[6];
  word_576b_( 143, 126) = (ap_fixed<16,10,AP_RND>) a[7];
  word_576b_( 161, 144) = (ap_fixed<16,10,AP_RND>) a[8];
  word_576b_( 179, 162) = (ap_fixed<16,10,AP_RND>) a[9];
  word_576b_( 197, 180) = (ap_fixed<16,10,AP_RND>) a[10];
  word_576b_( 215, 198) = (ap_fixed<16,10,AP_RND>) a[11];
  word_576b_( 233, 216) = (ap_fixed<16,10,AP_RND>) a[12];
  word_576b_( 251, 234) = (ap_fixed<16,10,AP_RND>) a[13];
  word_576b_( 269, 252) = (ap_fixed<16,10,AP_RND>) a[14];
  word_576b_( 287, 270) = (ap_fixed<16,10,AP_RND>) a[15];
  word_576b_( 305, 288) = (ap_fixed<16,10,AP_RND>) a[16];
  word_576b_( 323, 306) = (ap_fixed<16,10,AP_RND>) a[17];
  word_576b_( 341, 324) = (ap_fixed<16,10,AP_RND>) a[18];
  word_576b_( 359, 342) = (ap_fixed<16,10,AP_RND>) a[19];
  word_576b_( 377, 360) = (ap_fixed<16,10,AP_RND>) a[20];
  word_576b_( 395, 378) = (ap_fixed<16,10,AP_RND>) a[21];
  word_576b_( 413, 396) = (ap_fixed<16,10,AP_RND>) a[22];
  word_576b_( 431, 414) = (ap_fixed<16,10,AP_RND>) a[23];
  word_576b_( 449, 432) = (ap_fixed<16,10,AP_RND>) a[24];
  word_576b_( 467, 450) = (ap_fixed<16,10,AP_RND>) a[25];
  word_576b_( 485, 468) = (ap_fixed<16,10,AP_RND>) a[26];
  word_576b_( 503, 486) = (ap_fixed<16,10,AP_RND>) a[27];
  word_576b_( 521, 504) = (ap_fixed<16,10,AP_RND>) a[28];
  word_576b_( 539, 522) = (ap_fixed<16,10,AP_RND>) a[29];
  word_576b_( 557, 540) = (ap_fixed<16,10,AP_RND>) a[30];
  word_576b_( 575, 558) = (ap_fixed<16,10,AP_RND>) a[31];*/
    axiword576 r; r.last = 0; r.user = 0;
  r.data = word_576b_;
  
  olink.write(r);

  return ;
}
/*double sin(double h)
{
	double ha = h * 3.14159265359 / 180;
	double f = ha * ha * ha / 6;
	double s = ha * ha * ha * ha * ha / 120;
	double d = ha * ha * ha * ha * ha * ha * ha / 5040;
	double co = ha * ha * ha * ha * ha * ha * ha * ha * ha / 362880;
	double j= ha * ha * ha * ha * ha * ha * ha * ha * ha * ha * ha / 39916800;
	double o = ha * ha * ha * ha * ha * ha * ha * ha * ha * ha * ha * ha * ha / 6227020800;
	double out = ha - f + s - d + co - j + o;
	//cout << out << endl;
	return out;
}
double cos(double ha)
{
	double h = ha * 3.14159265359 / 180;
	double f = h * h / 2;
	double s = h * h * h * h / 24;
	double d = h * h * h * h * h * h / 720;
	double co = h * h * h * h * h * h * h * h / 40320;
	double j = h * h * h * h * h * h * h * h * h * h / 3628800;
	double o = h * h * h * h * h * h * h * h * h * h * h * h / 479001600;
	double out = 1 - f + s - d + co - j + o;
	//cout << out << endl;
	return out;
}*/

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
  double a[TOWERS_IN_PHI];
#pragma HLS ARRAY_PARTITION variable=a complete dim=0
  double aa[TOWERS_IN_PHI];
#pragma HLS ARRAY_PARTITION variable=aa complete dim=0
  double sinphi[TOWERS_IN_PHI]={0.04362,0.13053,0.21644,0.30071,0.38268,0.46175,0.53730,0.60876,0.67559,0.73728,0.79335,0.84339,
  0.88701,0.92388,0.95372,0.97630,0.99144,0.99905,0.99905,0.99144,0.97630,0.95372,0.92388,0.88701,0.84339,0.79335,0.73728,
  0.67559,0.60876,0.53730,0.46175,0.38268};
#pragma HLS ARRAY_PARTITION variable=sinphi complete dim=0
  double cosphi[TOWERS_IN_PHI]={0.99905,0.99144,0.97630,0.95372,0.92388,0.88701,0.84339,0.79335,0.73728,0.67559,0.60876,0.53730,
		  0.46175,0.38268,0.30071,0.21644,0.13053,0.04362,-0.04362,-0.13053,-0.21644,-0.30071,-0.38268,-0.46175,-0.53730,
		  -0.60876,-0.67559,-0.73728,-0.79335,-0.84339,-0.88701,-0.92388};
#pragma HLS ARRAY_PARTITION variable=cosphi complete dim=0
  for (int b = 0; b < 32; b++) {

	  double Ey;double Ex;
  		double j;
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
  		a[b] = Ey;
  		Ex = cosphi[b]*j;
  		aa[b] = Ex;
  		//cout << Ex <<endl;
  	}
  // Step 3: Pack the outputs
  	  packOutput(&a[0],link_out[0]);
  	  packOutput(&aa[0],link_out[1]);
//  for (size_t olink = 0; olink < N_OUTPUT_LINKS/2; olink++) {
//#pragma LOOP UNROLL
//#pragma HLS latency min=1
//    size_t iPosEta = olink;
//    size_t iNegEta = olink + (N_OUTPUT_LINKS/2);
//    packOutput(&towers[olink][0], link_out[iNegEta]);
//    packOutput(&towers[olink][TOWERS_IN_ETA/2], link_out[iPosEta]);

}
