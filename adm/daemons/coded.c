#include <ansi.h>
#define HZK "/adm/etc/点阵/hzk"
#define ASC "/adm/etc/点阵/asc"
#define DEFAULT_FILL WHT"@"
#define DEFAULT_BG " "
#define DEFAULT_FCOLOR ""
#define DEFAULT_BGCOLOR ""
#define AUTO_SIZE 16

string *colours=({
        HIR, HIY, HIW,  YEL, HIB,  MAG, 
        });

string *fillchar=({
        "Q", "@", "&", "#","D", 
        });

varargs string Display(string str, int size, string fill, string bg, string fcolor, string bgcolor)
{
        int offset,sizetemp;
        int *mask = ({0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1});
        int scale;
        string char;
        string *out;
        
        if(!size)
#ifdef AUTO_SIZE
                size = AUTO_SIZE;
#else
                error("TEXT to PIC need size\n");
#endif
        out = allocate(size);
//        out = allocate(12);
        out = map_array(out, (: $1 = "" :));
        size *= 2;

        if(!fill || sizeof(fill) != sizeof(bg)) fill = DEFAULT_FILL;
        if(!fcolor) fcolor = DEFAULT_FCOLOR;
        if(!bg || sizeof(fill) != sizeof(bg)) bg = DEFAULT_BG;
        if(!bgcolor) bgcolor = DEFAULT_BGCOLOR;
        

        for(int k = 0; k < sizeof(str); k++) {
                sizetemp=size;
//              size=24+random(2)*4;
                size=24;

                if(mask[0] & str[k]) {
                        offset = size*( (atoi(sprintf("%d", str[k]))-0xA1)*94 + atoi(sprintf("%d", str[k+1])) - 0xA1 );
                        char = read_bytes(HZK + (size/2), offset, size);
                        k++;
                        scale = 2;
                } else {
                        offset = str[k] * (size/2);
                        char = read_bytes(ASC + (size/2), offset, (size/2));
                        scale = 1;
                }
                
                if(!sizeof(char)) error("TEXT to PIC can't read bytes from character lib\n");
                if(random(2)==0)
                {
                        for(int j=0;j<size/2;j++)
                        {
                                out[j]+=bgcolor+bg;
                        }
                }


                for(int i = 0; i < sizeof(char); i++) {
                switch(random(5))
                {
                        case 0: fill =REV+fcolor+" "NOR+bgcolor;
                                break;
                        case 1: fill =REV+fcolor+" "NOR+bgcolor;
                                break;
                        case 2: fill =REV+fcolor+" "NOR+bgcolor;
                                break;
                        case 3: fill =REV+fcolor+" "NOR+bgcolor;
                                break;
                        case 4: fill =REV+fcolor+" "NOR+bgcolor;
                                break;
                }


                        for(int j = 0; j < 8; j++) {
                                if(mask[j] & char[i]) 
                                        if(random(50)==0)
                                        out[i/scale] += bgcolor + bg;                                        
                                        else
                                        out[i/scale] += fcolor + fill;
                                else 
//                                      if(random(40)==0)
  //                                      out[i/scale] += fcolor + fill;                                        
    //                                    else
                                        out[i/scale] += bgcolor + bg;
                        }
                }

                for(int i = 0; i < sizeof(out); i++) {
                        out[i] = replace_string(out[i], fill + fcolor + fill, fill + fill);
                        out[i] = replace_string(out[i], bg + bgcolor + bg, bg + bg);
                }
                size=sizetemp;
        }
        
        return implode(out, "\n") + NOR;
}

string code_math(object who)
{
        int f,a,b;
        string arg,*bc,*fc;
        if( !who || !interactive(who) )
                return 0;
        a = 1+random(100);
        b = a/2+random(10);
        f = a+b;
        arg = a+"+"+b;
        bc = ({
                HBRED"",HBYEL"",HBBLU"",HBMAG"",HBCYN"",HBWHT"",
                BRED"",BYEL"",BBLU"",BMAG"",BCYN"",
        });
        fc = ({
                RED"",YEL"",BLU"",MAG"",CYN"",WHT"",
                HIR"",HIY"",HIB"",HIM"",HIC"",HIW"",
        });             
        who->set_temp("Code_answer",f);
        return Display(arg,16, 0, " ", fc[random(sizeof(fc))],bc[random(sizeof(bc))]);
} 
