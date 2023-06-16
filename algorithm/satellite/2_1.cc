#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;


struct node{
	double lon;	//longitude
	double lat;	//latitude
	string name;
};

class satellite{
	public:
		satellite();
		~satellite();
		void getspot();
		void show();
		//void findct();
	private:
		node*city;	
};

satellite::satellite(){
	cout<<"start"<<endl;
	city=new node[24];
	city[0].name="Abidjan"; city[0].lon=-4.02; city[0].lat=5.32;
	city[1].name="Accra"; city[1].lon=-0.2; city[1].lat=5.56;
	city[2].name="Asmara"; city[2].lon=15.33; city[2].lat=38.97;
	city[3].name="Balikpapan"; city[3].lon=116.86; city[3].lat=-1.21;
	city[4].name="Bozeman"; city[4].lon=-111.04; city[4].lat=45.68;
	city[5].name="Crystal-Lake"; city[5].lon=-88.33;city[5].lat=42.23;
	city[6].name="Elk-City";city[6].lon=-99.41;city[6].lat=35.4;
	city[7].name="Hanahan";city[7].lon=-80.01;city[7].lat=32.93;
	city[8].name="Iquique";city[8].lon=-69.91;city[8].lat=-20.26;
	city[9].name="Lhasa";city[9].lon=91.13;city[9].lat=26.65;
	city[10].name="Madras";city[10].lon=80.25;city[10].lat=13.06;
	city[11].name="Manaus";city[11].lon=-60.01;city[11].lat=-3.12;
	city[12].name="Mangalore";city[12].lon=75.16;city[12].lat=12.95;
	city[13].name="Minsk";city[13].lon=27.58;city[13].lat=53.9;
	city[14].name="Munchen";city[14].lon=11.54;city[14].lat=48.14;
	city[15].name="Parole";city[15].lon=-76.55;city[15].lat=38.98;
	city[16].name="Recife";city[16].lon=-34.91;city[16].lat=-8.09;
	city[17].name="Rio-de-Janeiro";city[17].lon=-43.46;city[17].lat=-22.72;
	city[18].name="Sarajevo";city[18].lon=18.43;city[18].lat=43.87;
	city[19].name="Wallingford-Center";city[19].lon=-72.82;city[19].lat=41.45;
	city[20].name="Yaounde";city[20].lon=11.51;city[20].lat=3.87;
	city[21].name="北京";city[21].lon=116.39;city[21].lat=39.91;
	city[22].name="南宁";city[22].lon=108.33;city[22].lat=22.8;
	city[23].name="武汉";city[23].lon=114.28;city[23].lat=30.57;
	cout<<"The city name has been written"<<endl;
}

satellite::~satellite(){
	delete [] city;
	cout<<"finish"<<endl;
}

void satellite::show(){
	int n=0;
	while(n<=23){
		cout<<city[n].name<<" longitude:"<<city[n].lon<<" latitude:"<<city[n].lat<<endl;
		n++;
	}
}
/*void satellite::getspot(){
	cout<<"hello"<<endl;
}*/

int main(){
	satellite a;
	a.show();
	return 0;
}
