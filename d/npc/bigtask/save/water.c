inherit ITEM;
#include <ansi.h>
int random_place(object me, string dirs);
string *dirs = ({
"/d/xueshan",
"/d/lingtai",
"/d/moon",
"/d/nanhai",
"/d/death",
"/d/pansi",
"/d/jjf",
"/d/sea",
"/d/qujing/wudidong",
"/d/qujing/wuzhuang",
"/d/qujing/kusong",
"/d/qujing/shushan",
"/d/qujing/changan",
"/d/qujing/wuji",
"/d/qujing/baoxiang",
"/d/qujing/tianzhu",
"/d/qujing/nuerguo",
"/d/qujing/yuhua",
});
void create()
{
        set_name(HIR"大水"NOR, ({"water", "shui" }));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一汪水。\n");
                set("unit", "汪");
        }
}
int invocation(int i)
{
        object me=this_object();
        if(!random_place(me, dirs[i]))
        return 0;
        return 1;
}
int random_place(object me, string dirs)
{
        int  j, k;
        object  newob;
        mixed*  file, exit;
        file = get_dir( dirs+"/*.c", -1 );

        if( !sizeof(file) )             return 1;

        for(k=0;k<30;k++) { // try 30 times
           j = random(sizeof(file));
           if( file[j][1] > 0 ) {
             newob=load_object(dirs+"/"+file[j][0]);
             if (newob) {  
               if(newob->query("no_fight") ||
                       newob->query("no_magic") ||
                       !(exit=newob->query("exits")) ||
                       sizeof(exit)<1)
                   continue;
               if(me->move(newob)) {
                   return 1;
               }
             }
           }
        }

        return 0;
}