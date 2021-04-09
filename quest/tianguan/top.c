inherit ROOM;
#include <ansi.h>

void create()
{
string str;     
set("short","大雄宝殿");
str = @LONG
大雄宝殿里金碧辉煌紫气瑞瑞，根根玉柱雕麒麟，殿窗是金钉
银檐，殿顶亦上是金银鸳鸯双双对对，正中有一白玉玛瑙莲花
台。南边有一殿门通往后殿，东西边各有一偏门。
LONG;
str+= "
    这里明显的出口是 "HIG"east"NOR"、"HIG"north"NOR"、"HIG"south"NOR" 和"HIG" west"NOR"。\n";
str+= @LONG    
  佛祖多陀阿伽陀 如来佛(Rulai fo)
  仙童(Xian tong)
  仙童(Xian tong)
LONG;
set("long",str);
set("no_fight",1);
set("outdoors","lingshan");
setup();
}               

void init()
{
object me = this_player();
add_action("do_agree","agree");
if ( !userp(me) 
  || !me->query("新任务/门派挑战/千面怪") 
  || me->add("新任务/门派挑战/num")<9 )
        return;
tell_object(me,"你将各大门派都挑战了一遍，不禁觉得天下之大，舍我其谁。。。。\n\n"); 
if ( !me->query("obstacle/reward") )
        return;
tell_object(me,"如来佛祖在半空哈腰对你说道："+me->query("name")+"，你已将各门派挑战了，本座特许你从头取经，你可愿意(agree)?\n");
}

int do_agree()
{
object me = this_player();
if ( !userp(me) 
  || !me->query("新任务/门派挑战/千面怪") 
  || me->add("新任务/门派挑战/num")<9 )
        return 0;
if ( !me->query("obstacle/reward") )
        return 0;
if ( me->query("新任务/门派挑战/取经注销") )
        return 0;
//每周只能注销1次
if ( time()<me->query("obstacle_cancel")+604800 )
        {write("你本周已经注销过一次，所以本次注销取消。\n");return 1;}
                
me->start_busy(3);
message_vision(CYN"$N"CYN"说道：我愿意。\n"NOR,me);
me->delete("obstacle");
me->delete("wudidong");
me->delete("rulaitask_log");
me->delete("rulaitask");
me->set("新任务/门派挑战/取经注销",1);
me->set("obstacle_cancel",time());
me->save();
message_vision("半空中祥云阵阵，一道金光照在$N身上，径直将之往极乐西天接引去了。。。。\n\n",me);
message_vision("……云中伸出一只巨大的佛手轻轻一翻，只见$N从里面跳出来。\n",me);        
me->move("/d/qujing/lingshan/daxiong");
message_vision("如来佛大袖朝$N一拂，$P立刻好似觉得忘却了什么，一身轻松。。。。\n\n",me);
message("shout",HIY"【小雨西游】如来佛(Rulai fo)："+me->query("name")+HIY"挑战各大门派，自身修为更进一层，本座特许其从头再来，重新取回真经。\n"NOR,users());
("/cmds/usr/quit.c")->main(me,"",1);
return 1;
}

