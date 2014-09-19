//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>

#pragma hdrstop

#include "Unit1.h"
#include "Convertor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

//#define double Extended
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    double Lat = 56.147325;
    double Lon = 93.33532;

    Convertor myConv;
    WGS84 wgs84;
    wgs84.latt = Lat;
    wgs84.longt = Lon;
    wgs84.h = 0;

    myConv.WGS84ToCK42(wgs84);
    GsKr gskr = myConv.CK42ToGsKr(myConv.WGS84ToCK42(wgs84));
    ShowMessage(FloatToStr(gskr.x-5578022.48) + " " + FloatToStr(gskr.y+106797.8));
return;


//    Lat = 57.0 + 17.0/60.0 + 31.086/3600.0; //57° 17 31.086
//    Lon = 113.0 + 17.0/60.0 + 0.491/3600.0; //113° 17 0.491
    double MM = 93;

    MM = MM*M_PI/180.0;
    Lat = Lat*M_PI/180.0;
    Lon = Lon*M_PI/180.0;
    double B = Lat;

    double sinB = sin(B);
    double sin2B = sin(B)*sin(B);
    double sin4B = sin2B*sin2B;
    double sin6B = sin2B*sin2B*sin2B;
    double cosB = cos(B);

    double n = floor((6.0+Lon)/6.0);
    double L = (Lon-(3+6*(n-1)))/57.29577951;
    n=0;
    L=Lon-MM;

    double L2 = L*L;

    double x = 6367558.4968*B-sin(2*B)*(16002.8900+66.9607*sin2B+0.3515*sin4B
        -L2*(1594561.25+5336.535*sin2B+26.790*sin4B+0.149*sin6B
        +L2*(672483.4-811219.9*sin2B+5420.0*sin4B-10.6*sin6B
        +L2*(278194-830174*sin2B+572434*sin4B-16010*sin6B
        +L2*(109500-574700*sin2B+863700*sin4B-398600*sin6B)))));

    double y =
        //(5+10*n)*100000+
        L*cosB *(6378245+21346.1415  *sin2B+107.159*sin4B+0.5977*sin6B
        +L2*(1070204.16-2136826.66*sin2B+17.98  *sin4B-11.99 *sin6B
        +L2*(270806    -1523417  *sin2B+1327645*sin4B-21701 *sin6B
        +L2*(79690    -866190    *sin2B+1730360*sin4B-945460*sin6B))));

    x = x-5578022.48;
    y = y + 106797.8;
    ShowMessage(FloatToStr(x)+" "+FloatToStr(y));

}
//---------------------------------------------------------------------------
//function BLtoXY(B, L) {
//    var B = B * (Math.PI/180);
//    var n = Math.floor((6+L)/6);
//    var l = (L - (3+6*(n-1)))/57.29577951;
//    var x = 6367558.4968*B-Math.sin(2*B)*(16002.8900+66.9607*Math.pow(Math.sin(B),2)+0.3515*Math.pow(Math.sin(B),4)
//        -Math.pow(l,2)*(1594561.25+5336.535*Math.pow(Math.sin(B),2)+26.790*Math.pow(Math.sin(B),4)+0.149 *Math.pow(Math.sin(B),6)
//        +Math.pow(l,2)*(672483.4  -811219.9*Math.pow(Math.sin(B),2)+5420.0*Math.pow(Math.sin(B),4)-10.6  *Math.pow(Math.sin(B),6)
//        +Math.pow(l,2)*(278194    -830174  *Math.pow(Math.sin(B),2)+572437*Math.pow(Math.sin(B),4)-16010 *Math.pow(Math.sin(B),6)
//        +Math.pow(l,2)*(109500    -574700  *Math.pow(Math.sin(B),2)+863700*Math.pow(Math.sin(B),4)-398600*Math.pow(Math.sin(B),6))))));
//    var y = (5+10*n)*Math.pow(10,5)+
//        l*Math.cos(B) *(6378245+21346.1415  *Math.pow(Math.sin(B),2)+107.159*Math.pow(Math.sin(B),4)+0.5977*Math.pow(Math.sin(B),6)
//        +Math.pow(l,2)*(1070204.16-2136826.66*Math.pow(Math.sin(B),2)+17.98  *Math.pow(Math.sin(B),4)-11.99 *Math.pow(Math.sin(B),6)
//        +Math.pow(l,2)*(270806    -1523417  *Math.pow(Math.sin(B),2)+1327645*Math.pow(Math.sin(B),4)-21701 *Math.pow(Math.sin(B),6)
//        +Math.pow(l,2)*(79690    -866190    *Math.pow(Math.sin(B),2)+1730360*Math.pow(Math.sin(B),4)-945460*Math.pow(Math.sin(B),6)))));
//    var res = new Coordinates(x, y);
//    return res;
//}

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
    double Lat = E_grB->Text.ToInt() + E_minB->Text.ToInt()/60.0 + E_secB->Text.ToDouble()/3600;
    double Lon = E_grL->Text.ToInt() + E_minL->Text.ToInt()/60.0 + E_secL->Text.ToDouble()/3600;

    Convertor myConv;
    WGS84 wgs84;
    wgs84.latt = Lat;
    wgs84.longt = Lon;
    wgs84.h = 0;

    myConv.WGS84ToCK42(wgs84);
    GsKr gskr = myConv.CK42ToGsKr(myConv.WGS84ToCK42(wgs84));
    E_x->Text = FloatToStr(gskr.x-5578022.48);
    E_y->Text = FloatToStr(gskr.y+106797.8);

}
//---------------------------------------------------------------------------
